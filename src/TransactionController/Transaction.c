/*
 *		RPbdb::TransactionController::Transaction
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Transaction.h"
#include "Transaction_internal.h"

#include "Database_internal.h"

#include "TransactionController.h"
#include "Transaction_internal.h"
#include "TransactionController_internal.h"

#include "Database.h"

#include "Environment.h"

#include "ErrorController.h"

#include "SettingsController.h"
#include "TransactionSettingsController.h"
#include "TransactionSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_Transaction* RPbdb_Transaction_new( RPbdb_TransactionController* parent_transaction_controller )	{

	RPbdb_Transaction*				transaction = RPbdb_Transaction_internal_newWithoutBDBTransaction( parent_transaction_controller );

	if ( parent_transaction_controller->runtime_storage_database != NULL )	{
		transaction->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_transaction_controller->runtime_storage_database,
																																									(void*) transaction );
	}

	//	Make call to instantiate local settings controller
	transaction->settings_controller	=	RPbdb_TransactionSettingsController_internal_copyOfSettingsControllerForInstance( RPbdb_SettingsController_transactionSettingsController( RPbdb_Environment_settingsController( parent_transaction_controller->parent_environment ) ) );

	transaction->is_open	=	FALSE;

	return transaction;
}

/***************************
*  free  *
***************************/

void RPbdb_Transaction_free(	RPbdb_Transaction** transaction )	{
	
	if ( ( *transaction )->parent_transaction_controller->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *transaction )->parent_transaction_controller->runtime_storage_database,
																											( *transaction )->runtime_identifier );
	}
	RPbdb_Transaction_internal_freeFromRuntimeStorage( transaction );
}

/***************************
*  freeFromRuntimeStorage  *
***************************/

void RPbdb_Transaction_internal_freeFromRuntimeStorage( RPbdb_Transaction** transaction )	{
	
	//	If the transaction is still open, commit it
	if ( RPbdb_Transaction_isOpen( *transaction ) )	{
		RPbdb_Transaction_commit( *transaction );
	}

	if ( ( *transaction )->settings_controller != NULL )	{
		RPbdb_TransactionSettingsController_free( & ( ( *transaction )->settings_controller ) );
	}

	free( *transaction );
	*transaction	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_TransactionSettingsController* RPbdb_Transaction_settingsController(	RPbdb_Transaction* transaction )	{
	return transaction->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_Transaction_parentEnvironment(	RPbdb_Transaction* transaction )	{
	return transaction->parent_transaction_controller->parent_environment;
}

/*******************************************************************************************************************************************************************************************
																		Settings
*******************************************************************************************************************************************************************************************/

/*************************
*  isOpen  *
*************************/

BOOL RPbdb_Transaction_isOpen( RPbdb_Transaction* transaction )	{
	return transaction->is_open;
}

/*************************************************
*  closeAllDatabasesOpenedDuringTransaction  *
*************************************************/

void RPbdb_Transaction_closeAllDatabasesOpenedDuringTransaction( RPbdb_Transaction* transaction )	{

	RPbdb_DatabaseOpenedDuringTransaction**	this_database_opened_during_transaction	=	& ( transaction->databases_opened_during_transaction );
	
	while (		this_database_opened_during_transaction != NULL
		   &&	*this_database_opened_during_transaction != NULL )	{
		
		RPbdb_Database*	database	=	( *this_database_opened_during_transaction )->database;
		
		RPbdb_Database_close( database );
		
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
char* RPbdb_Transaction_name( RPbdb_Transaction* transaction )	{
	
	RPbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	if ( transaction->name == NULL )	{
		
		if ( ( connection_error = transaction->wrapped_bdb_transaction->get_name(	transaction->wrapped_bdb_transaction,
																					(const char**) &( transaction->name ) ) ) )	{
			
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
															connection_error, 
															"Transaction_name" );
			return NULL;
		}
	}
	
	return transaction->name;
}

/*************************
*  setName  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_set_name.html
void RPbdb_Transaction_setName(	RPbdb_Transaction*		transaction,
								char*					transaction_name )	{
	
	RPbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	if ( ( connection_error = transaction->wrapped_bdb_transaction->set_name(	transaction->wrapped_bdb_transaction,
																				transaction_name ) ) )	{
		
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
														connection_error, 
														"Transaction_setName" );
	}
	
	transaction->name = transaction_name;
}

/*************************
*  beginTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
RPbdb_Transaction* RPbdb_Transaction_begin( RPbdb_Transaction*		transaction )	{
	
	RPbdb_TransactionController*	transaction_controller	= transaction->parent_transaction_controller;
	RPbdb_Environment*				environment				= transaction_controller->parent_environment;
	
	int	connection_error	= RP_NO_ERROR;	

	//	FIX - make sure transaction is not open or throw error
	if ( RPbdb_Transaction_isOpen( transaction ) )	{
	
		RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( environment ),
											RPBDB_ERROR_TRANSACTION_OPEN, 
											"Transaction_beginTransaction",
											RPBDB_ERROR_MESSAGE_TRANSACTION_OPEN );
	}

	DB_TXN*	transaction_id	=	NULL;
	if ( environment->transaction_controller != NULL )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	if ( ( connection_error = transaction_controller->parent_environment->wrapped_bdb_environment->txn_begin(	transaction_controller->parent_environment->wrapped_bdb_environment,
																												transaction_id,
																												& ( transaction->wrapped_bdb_transaction ),
																												RPbdb_TransactionSettingsController_internal_beginFlags( RPbdb_SettingsController_transactionSettingsController( RPbdb_Environment_settingsController( environment ) ) ) ) ) ) {
																																										 
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
														connection_error, 
														"Transaction_beginTransaction" );
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
RPbdb_Transaction* RPbdb_Transaction_beginConcurrentDataStoreGroup( RPbdb_Transaction* transaction )	{
	
	RPbdb_TransactionController*	transaction_controller	= transaction->parent_transaction_controller;
	RPbdb_Environment*				environment				= transaction_controller->parent_environment;
	
	//	FIX - make sure transaction is not open or throw error
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		int	connection_error	= RP_NO_ERROR;	
		if ( ( connection_error = environment->wrapped_bdb_environment->cdsgroup_begin(	environment->wrapped_bdb_environment, 
																						&( transaction->wrapped_bdb_transaction ) ) ) ) {
			
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
															connection_error, 
															"Transaction_beginConcurrentDataStoreGroup" );
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
RPbdb_Transaction* RPbdb_Transaction_prepare(	RPbdb_Transaction*	transaction,
												//	global_transaction_id is a DB_XIDDATASIZE (currently 128) length array of 8 bit ints
												//	The array is used to identify distributed transactions, which may be relayed 
												//	through multiple centralizing environment nodes to distributed environments.
												u_int8_t			global_transaction_id[]	)	{
	
	RPbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	if ( ( connection_error = transaction->wrapped_bdb_transaction->prepare(	transaction->wrapped_bdb_transaction,
																				global_transaction_id	) ) )	{
		
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
														connection_error, 
														"Transaction_prepare" );
	}
	return transaction;
}

/*****************************
*  rollback  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_abort.html
void RPbdb_Transaction_rollback( RPbdb_Transaction* transaction )	{
	
	RPbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	if ( ( connection_error = transaction->wrapped_bdb_transaction->abort( transaction->wrapped_bdb_transaction ) ) )	{
		
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
														connection_error, 
														"Transaction_rollback" );
	}

	//	Close all databases associated with transaction
	RPbdb_Transaction_closeAllDatabasesOpenedDuringTransaction( transaction );

	transaction->is_open	=	FALSE;
}

/*************************
*  commit  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_commit.html
void RPbdb_Transaction_commit( RPbdb_Transaction* transaction )	{
	
	RPbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	//	Tell our controller that the depth has changed
	transaction->parent_transaction_controller->current_transaction_depth--;
	
	//	Close all databases associated with transaction
	RPbdb_Transaction_closeAllDatabasesOpenedDuringTransaction( transaction );
		
	int			connection_error	= 0;
	if ( ( connection_error = transaction->wrapped_bdb_transaction->commit(	transaction->wrapped_bdb_transaction,
																			RPbdb_TransactionSettingsController_internal_commitFlags( RPbdb_Transaction_settingsController( transaction ) ) ) ) )	{
																			   
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
														connection_error, 
														"Transaction_commit" );
	}

	transaction->is_open	=	FALSE;
}

/*************************************
*  discardRecoveredResources  *
*************************************/

//	Any transactions returned by DB_ENV->txn_recover() that are not named by the _current_ global transaction manager should be discarded using DB_TXN->discard().
//	This call may be used only after calls to DB_ENV->txn_recover() when there are multiple global transaction managers recovering transactions in a single Berkeley DB environment. 
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_discard.html
RPbdb_Transaction* RPbdb_Transaction_discardRecoveredResources( RPbdb_Transaction* transaction )	{
	
	RPbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	
	if ( ( connection_error = transaction->wrapped_bdb_transaction->discard(	transaction->wrapped_bdb_transaction,
																				RPbdb_TransactionSettingsController_internal_discardFlags( RPbdb_Transaction_settingsController( transaction ) ) ) ) )	{
																				
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
														connection_error, 
														"Transaction_discardRecoveredResources" );
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

RPbdb_Transaction* RPbdb_Transaction_internal_newWithoutBDBTransaction( RPbdb_TransactionController*	parent_transaction_controller )	{

	RPbdb_Transaction*				transaction = calloc( 1, sizeof( RPbdb_Transaction ) );

	transaction->parent_transaction_controller = parent_transaction_controller;
	
	return transaction;
}

/*********************
*  transactionID  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
DB_TXN* RPbdb_Transaction_internal_transactionID( RPbdb_Transaction* transaction )	{
	
	RPbdb_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	
	if ( ( connection_error = transaction->wrapped_bdb_transaction->id( transaction->wrapped_bdb_transaction ) ) )	{
		
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
														connection_error, 
														"Transaction_transactionID" );
		return NULL;
	}
	
	return transaction->wrapped_bdb_transaction;
}

/*************************************************
*  addDatabaseToListOpenedDuringTransaction  *
*************************************************/

void RPbdb_Transaction_internal_addDatabaseToListOpenedDuringTransaction(	RPbdb_Transaction*	transaction,
																			RPbdb_Database*		database	)	{
	
	RPbdb_DatabaseOpenedDuringTransaction*	database_opened_during_transaction	=	calloc( 1, sizeof( RPbdb_DatabaseOpenedDuringTransaction ) );
	
	database_opened_during_transaction->database	=	database;

	if ( transaction->databases_opened_during_transaction == NULL )	{
		transaction->databases_opened_during_transaction		=	database_opened_during_transaction;
	}
	else {

		//	Get a pointer to the next empty pointer
		RPbdb_DatabaseOpenedDuringTransaction**	next_empty_pointer	=	& transaction->databases_opened_during_transaction;
		if ( transaction->databases_opened_during_transaction != NULL )	{

			while (		( next_empty_pointer = & ( ( *next_empty_pointer )->next ) ) != NULL
					&&	*next_empty_pointer != NULL )	{
					
			}
		}

		*next_empty_pointer	=	database_opened_during_transaction;
	}

}





