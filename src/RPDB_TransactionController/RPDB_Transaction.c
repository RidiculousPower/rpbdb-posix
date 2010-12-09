/*
 *		Rbdb::TransactionController::Transaction
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_Transaction.h"
#include "Rbdb_Transaction_internal.h"

#include "Rbdb_Database_internal.h"

#include "Rbdb_TransactionController.h"
#include "Rbdb_Transaction_internal.h"
#include "Rbdb_TransactionController_internal.h"

#include "Rbdb_Database.h"

#include "Rbdb_Environment.h"

#include "Rbdb_ErrorController.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_TransactionSettingsController.h"
#include "Rbdb_TransactionSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_Transaction* Rbdb_Transaction_new( Rbdb_TransactionController* parent_transaction_controller )	{

	Rbdb_Transaction*				transaction = Rbdb_Transaction_internal_newWithoutBDBTransaction( parent_transaction_controller );

	if ( parent_transaction_controller->runtime_storage_database != NULL )	{
		transaction->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_transaction_controller->runtime_storage_database,
																																									(void*) transaction );
	}

	//	Make call to instantiate local settings controller
	transaction->settings_controller	=	Rbdb_TransactionSettingsController_internal_copyOfSettingsControllerForInstance( Rbdb_SettingsController_transactionSettingsController( Rbdb_Environment_settingsController( parent_transaction_controller->parent_environment ) ) );

	transaction->is_open	=	FALSE;

	return transaction;
}

/***************************
*  free  *
***************************/

void Rbdb_Transaction_free(	Rbdb_Transaction** transaction )	{
	
	if ( ( *transaction )->parent_transaction_controller->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *transaction )->parent_transaction_controller->runtime_storage_database,
																											( *transaction )->runtime_identifier );
	}
	Rbdb_Transaction_internal_freeFromRuntimeStorage( transaction );
}

/***************************
*  freeFromRuntimeStorage  *
***************************/

void Rbdb_Transaction_internal_freeFromRuntimeStorage( Rbdb_Transaction** transaction )	{
	
	//	If the transaction is still open, commit it
	if ( Rbdb_Transaction_isOpen( *transaction ) )	{
		Rbdb_Transaction_commit( *transaction );
	}

	if ( ( *transaction )->settings_controller != NULL )	{
		Rbdb_TransactionSettingsController_free( & ( ( *transaction )->settings_controller ) );
	}

	free( *transaction );
	*transaction	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_TransactionSettingsController* Rbdb_Transaction_settingsController(	Rbdb_Transaction* transaction )	{
	return transaction->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_Transaction_parentEnvironment(	Rbdb_Transaction* transaction )	{
	return transaction->parent_transaction_controller->parent_environment;
}

/*******************************************************************************************************************************************************************************************
																		Settings
*******************************************************************************************************************************************************************************************/

/*************************
*  isOpen  *
*************************/

BOOL Rbdb_Transaction_isOpen( Rbdb_Transaction* transaction )	{
	return transaction->is_open;
}

/*************************************************
*  closeAllDatabasesOpenedDuringTransaction  *
*************************************************/

void Rbdb_Transaction_closeAllDatabasesOpenedDuringTransaction( Rbdb_Transaction* transaction )	{

	Rbdb_DatabaseOpenedDuringTransaction**	this_database_opened_during_transaction	=	& ( transaction->databases_opened_during_transaction );
	
	while (		this_database_opened_during_transaction != NULL
		   &&	*this_database_opened_during_transaction != NULL )	{
		
		Rbdb_Database*	database	=	( *this_database_opened_during_transaction )->database;
		
		Rbdb_Database_close( database );
		
		if ( ( *this_database_opened_during_transaction )->next != NULL )	{
			this_database_opened_during_transaction	=	& ( ( *this_database_opened_during_transaction )->next );
		}
		else {
			break;
		}
	}
}
	
/*************************
*  name  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_set_name.html
char* Rbdb_Transaction_name( Rbdb_Transaction* transaction )	{
	
	Rbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	if ( transaction->name == NULL )	{
		
		if ( ( connection_error = transaction->wrapped_bdb_transaction->get_name(	transaction->wrapped_bdb_transaction,
																					(const char**) &( transaction->name ) ) ) )	{
			
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
															connection_error, 
															"Rbdb_Transaction_name" );
			return NULL;
		}
	}
	
	return transaction->name;
}

/*************************
*  setName  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_set_name.html
void Rbdb_Transaction_setName(	Rbdb_Transaction*		transaction,
								char*					transaction_name )	{
	
	Rbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	if ( ( connection_error = transaction->wrapped_bdb_transaction->set_name(	transaction->wrapped_bdb_transaction,
																				transaction_name ) ) )	{
		
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
														connection_error, 
														"Rbdb_Transaction_setName" );
	}
	
	transaction->name = transaction_name;
}

/*************************
*  beginTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
Rbdb_Transaction* Rbdb_Transaction_begin( Rbdb_Transaction*		transaction )	{
	
	Rbdb_TransactionController*	transaction_controller	= transaction->parent_transaction_controller;
	Rbdb_Environment*				environment				= transaction_controller->parent_environment;
	
	int	connection_error	= RP_NO_ERROR;	

	//	FIX - make sure transaction is not open or throw error
	if ( Rbdb_Transaction_isOpen( transaction ) )	{
	
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( environment ),
											Rbdb_ERROR_TRANSACTION_OPEN, 
											"Rbdb_Transaction_beginTransaction",
											Rbdb_ERROR_MESSAGE_TRANSACTION_OPEN );
	}

	DB_TXN*	transaction_id	=	NULL;
	if ( environment->transaction_controller != NULL )	{
		transaction_id	=	Rbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	if ( ( connection_error = transaction_controller->parent_environment->wrapped_bdb_environment->txn_begin(	transaction_controller->parent_environment->wrapped_bdb_environment,
																												transaction_id,
																												& ( transaction->wrapped_bdb_transaction ),
																												Rbdb_TransactionSettingsController_internal_beginFlags( Rbdb_SettingsController_transactionSettingsController( Rbdb_Environment_settingsController( environment ) ) ) ) ) ) {
																																										 
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
														connection_error, 
														"Rbdb_Transaction_beginTransaction" );
		return NULL;
	}
	
	transaction_controller->transactions[ transaction_controller->current_transaction_depth ]	=	transaction;
	transaction_controller->current_transaction_depth++;
	
	transaction->is_open	=	TRUE;
	
	return transaction;
}

/********************************
*  beginConcurrentDataStore  *
********************************/

//	for single threaded operations; permits multiple cursors to be grouped under the same locker
//	this way their locks don't conflict because bdb knows it's safe (since the thread isolates them)
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_cdsgroup_begin.html
Rbdb_Transaction* Rbdb_Transaction_beginConcurrentDataStoreGroup( Rbdb_Transaction* transaction )	{
	
	Rbdb_TransactionController*	transaction_controller	= transaction->parent_transaction_controller;
	Rbdb_Environment*				environment				= transaction_controller->parent_environment;
	
	//	FIX - make sure transaction is not open or throw error
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		int	connection_error	= RP_NO_ERROR;	
		if ( ( connection_error = environment->wrapped_bdb_environment->cdsgroup_begin(	environment->wrapped_bdb_environment, 
																						&( transaction->wrapped_bdb_transaction ) ) ) ) {
			
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
															connection_error, 
															"Rbdb_Transaction_beginConcurrentDataStoreGroup" );
			return NULL;
		}
	}
	
	transaction_controller->transactions[ transaction_controller->current_transaction_depth ]	=	transaction;
	transaction_controller->current_transaction_depth++;
	
	transaction->is_open	=	TRUE;

	return transaction;
}

/*************************
*  prepare  *
*************************/

//	Child transactions should never be explicitly prepared. Their fate will be resolved along with their parent's during global recovery.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_prepare.html
Rbdb_Transaction* Rbdb_Transaction_prepare(	Rbdb_Transaction*	transaction,
												//	global_transaction_id is a DB_XIDDATASIZE (currently 128) length array of 8 bit ints
												//	The array is used to identify distributed transactions, which may be relayed 
												//	through multiple centralizing environment nodes to distributed environments.
												u_int8_t			global_transaction_id[]	)	{
	
	Rbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	if ( ( connection_error = transaction->wrapped_bdb_transaction->prepare(	transaction->wrapped_bdb_transaction,
																				global_transaction_id	) ) )	{
		
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
														connection_error, 
														"Rbdb_Transaction_prepare" );
	}
	return transaction;
}

/*****************************
*  rollback  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_abort.html
void Rbdb_Transaction_rollback( Rbdb_Transaction* transaction )	{
	
	Rbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	if ( ( connection_error = transaction->wrapped_bdb_transaction->abort( transaction->wrapped_bdb_transaction ) ) )	{
		
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
														connection_error, 
														"Rbdb_Transaction_rollback" );
	}

	//	Close all databases associated with transaction
	Rbdb_Transaction_closeAllDatabasesOpenedDuringTransaction( transaction );

	transaction->is_open	=	FALSE;
}

/*************************
*  commit  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_commit.html
void Rbdb_Transaction_commit( Rbdb_Transaction* transaction )	{
	
	Rbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	//	Tell our controller that the depth has changed
	transaction->parent_transaction_controller->current_transaction_depth--;
	
	//	Close all databases associated with transaction
	Rbdb_Transaction_closeAllDatabasesOpenedDuringTransaction( transaction );
		
	int			connection_error	= 0;
	if ( ( connection_error = transaction->wrapped_bdb_transaction->commit(	transaction->wrapped_bdb_transaction,
																			Rbdb_TransactionSettingsController_internal_commitFlags( Rbdb_Transaction_settingsController( transaction ) ) ) ) )	{
																			   
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
														connection_error, 
														"Rbdb_Transaction_commit" );
	}

	transaction->is_open	=	FALSE;
}

/*************************************
*  discardRecoveredResources  *
*************************************/

//	Any transactions returned by DB_ENV->txn_recover() that are not named by the _current_ global transaction manager should be discarded using DB_TXN->discard().
//	This call may be used only after calls to DB_ENV->txn_recover() when there are multiple global transaction managers recovering transactions in a single Berkeley DB environment. 
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_discard.html
Rbdb_Transaction* Rbdb_Transaction_discardRecoveredResources( Rbdb_Transaction* transaction )	{
	
	Rbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	
	if ( ( connection_error = transaction->wrapped_bdb_transaction->discard(	transaction->wrapped_bdb_transaction,
																				Rbdb_TransactionSettingsController_internal_discardFlags( Rbdb_Transaction_settingsController( transaction ) ) ) ) )	{
																				
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
														connection_error, 
														"Rbdb_Transaction_discardRecoveredResources" );
	}

	transaction->is_open	=	FALSE;

	return transaction;
}


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*********************************
*  newWithoutBDBTransaction  *
*********************************/

Rbdb_Transaction* Rbdb_Transaction_internal_newWithoutBDBTransaction( Rbdb_TransactionController*	parent_transaction_controller )	{

	Rbdb_Transaction*				transaction = calloc( 1, sizeof( Rbdb_Transaction ) );

	transaction->parent_transaction_controller = parent_transaction_controller;
	
	return transaction;
}

/*********************
*  transactionID  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
DB_TXN* Rbdb_Transaction_internal_transactionID( Rbdb_Transaction* transaction )	{
	
	Rbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	
	if ( ( connection_error = transaction->wrapped_bdb_transaction->id( transaction->wrapped_bdb_transaction ) ) )	{
		
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
														connection_error, 
														"Rbdb_Transaction_transactionID" );
		return NULL;
	}
	
	return transaction->wrapped_bdb_transaction;
}

/*************************************************
*  addDatabaseToListOpenedDuringTransaction  *
*************************************************/

void Rbdb_Transaction_internal_addDatabaseToListOpenedDuringTransaction(	Rbdb_Transaction*	transaction,
																			Rbdb_Database*		database	)	{
	
	Rbdb_DatabaseOpenedDuringTransaction*	database_opened_during_transaction	=	calloc( 1, sizeof( Rbdb_DatabaseOpenedDuringTransaction ) );
	
	database_opened_during_transaction->database	=	database;

	if ( transaction->databases_opened_during_transaction == NULL )	{
		transaction->databases_opened_during_transaction		=	database_opened_during_transaction;
	}
	else {

		//	Get a pointer to the next empty pointer
		Rbdb_DatabaseOpenedDuringTransaction**	next_empty_pointer	=	& transaction->databases_opened_during_transaction;
		if ( transaction->databases_opened_during_transaction != NULL )	{

			while (		( next_empty_pointer = & ( ( *next_empty_pointer )->next ) ) != NULL
					&&	*next_empty_pointer != NULL )	{
					
			}
		}

		*next_empty_pointer	=	database_opened_during_transaction;
	}

}





