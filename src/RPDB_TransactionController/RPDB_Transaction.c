/*
 *		RPDB::TransactionController::Transaction
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_Transaction.h"

#include "RPDB_TransactionController.h"
#include "RPDB_Transaction_internal.h"
#include "RPDB_TransactionController_internal.h"

#include "RPDB_Database.h"

#include "RPDB_Environment.h"

#include "RPDB_ErrorController.h"

#include "RPDB_SettingsController.h"
#include "RPDB_TransactionSettingsController.h"
#include "RPDB_TransactionSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_Transaction* RPDB_Transaction_new( RPDB_TransactionController* parent_transaction_controller )	{

	RPDB_Transaction*				transaction = RPDB_Transaction_internal_newWithoutBDBTransaction( parent_transaction_controller );

	//	Make call to instantiate local settings controller
	transaction->settings_controller	=	RPDB_TransactionSettingsController_internal_copyOfSettingsControllerForInstance( RPDB_SettingsController_transactionSettingsController( RPDB_Environment_settingsController( parent_transaction_controller->parent_environment ) ) );

	transaction->is_open	=	FALSE;

	return transaction;
}

/***************************
*  free  *
***************************/
void RPDB_Transaction_free(	RPDB_Transaction** transaction )	{
	
	//	If the transaction is still open, commit it
	if ( RPDB_Transaction_isOpen( *transaction ) )	{
		RPDB_Transaction_commit( *transaction );
	}

	if ( ( *transaction )->settings_controller != NULL )	{
		RPDB_TransactionSettingsController_free( & ( ( *transaction )->settings_controller ) );
	}

	free( *transaction );
	*transaction	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_TransactionSettingsController* RPDB_Transaction_settingsController(	RPDB_Transaction* transaction )	{
	return transaction->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_Transaction_parentEnvironment(	RPDB_Transaction* transaction )	{
	return transaction->parent_transaction_controller->parent_environment;
}

/*******************************************************************************************************************************************************************************************
																		Settings
*******************************************************************************************************************************************************************************************/

/*************************
*  isOpen  *
*************************/

BOOL RPDB_Transaction_isOpen( RPDB_Transaction* transaction )	{
	return transaction->is_open;
}

/*************************************************
*  closeAllDatabasesOpenedDuringTransaction  *
*************************************************/

void RPDB_Transaction_closeAllDatabasesOpenedDuringTransaction( RPDB_Transaction* transaction )	{

	RPDB_DatabaseOpenedDuringTransaction**	this_database_opened_during_transaction	=	& ( transaction->databases_opened_during_transaction );
	
	while (		this_database_opened_during_transaction != NULL
		   &&	*this_database_opened_during_transaction != NULL )	{
		
		RPDB_Database*	database	=	( *this_database_opened_during_transaction )->database;
		
		RPDB_Database_close( database );
		
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
char* RPDB_Transaction_name( RPDB_Transaction* transaction )	{
	
	RPDB_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	if ( transaction->name == NULL )	{
		
		if ( ( connection_error = transaction->wrapped_bdb_transaction->get_name(	transaction->wrapped_bdb_transaction,
																					(const char**) &( transaction->name ) ) ) )	{
			
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
															connection_error, 
															"RPDB_Transaction_name" );
			return NULL;
		}
	}
	
	return transaction->name;
}

/*************************
*  setName  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_set_name.html
void RPDB_Transaction_setName(	RPDB_Transaction*		transaction,
								char*					transaction_name )	{
	
	RPDB_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	if ( ( connection_error = transaction->wrapped_bdb_transaction->set_name(	transaction->wrapped_bdb_transaction,
																				transaction_name ) ) )	{
		
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
														connection_error, 
														"RPDB_Transaction_setName" );
	}
	
	transaction->name = transaction_name;
}

/*************************
*  beginTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
RPDB_Transaction* RPDB_Transaction_begin( RPDB_Transaction*		transaction )	{
	
	RPDB_TransactionController*	transaction_controller	= transaction->parent_transaction_controller;
	RPDB_Environment*				environment				= transaction_controller->parent_environment;
	
	int	connection_error	= RP_NO_ERROR;	

	//	FIX - make sure transaction is not open or throw error
	if ( RPDB_Transaction_isOpen( transaction ) )	{
	
		RPDB_ErrorController_throwError(	RPDB_Environment_errorController( environment ),
											RPDB_ERROR_TRANSACTION_OPEN, 
											"RPDB_Transaction_beginTransaction",
											RPDB_ERROR_MESSAGE_TRANSACTION_OPEN );
	}

	DB_TXN*	transaction_id	=	NULL;
	if ( environment->transaction_controller != NULL )	{
		transaction_id	=	RPDB_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	if ( ( connection_error = transaction_controller->parent_environment->wrapped_bdb_environment->txn_begin(	transaction_controller->parent_environment->wrapped_bdb_environment,
																												transaction_id,
																												& ( transaction->wrapped_bdb_transaction ),
																												RPDB_TransactionSettingsController_internal_beginFlags( RPDB_SettingsController_transactionSettingsController( RPDB_Environment_settingsController( environment ) ) ) ) ) ) {
																																										 
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
														connection_error, 
														"RPDB_Transaction_beginTransaction" );
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
RPDB_Transaction* RPDB_Transaction_beginConcurrentDataStoreGroup( RPDB_Transaction* transaction )	{
	
	RPDB_TransactionController*	transaction_controller	= transaction->parent_transaction_controller;
	RPDB_Environment*				environment				= transaction_controller->parent_environment;
	
	//	FIX - make sure transaction is not open or throw error
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		int	connection_error	= RP_NO_ERROR;	
		if ( ( connection_error = environment->wrapped_bdb_environment->cdsgroup_begin(	environment->wrapped_bdb_environment, 
																						&( transaction->wrapped_bdb_transaction ) ) ) ) {
			
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
															connection_error, 
															"RPDB_Transaction_beginConcurrentDataStoreGroup" );
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
RPDB_Transaction* RPDB_Transaction_prepare(	RPDB_Transaction*	transaction,
												//	global_transaction_id is a DB_XIDDATASIZE (currently 128) length array of 8 bit ints
												//	The array is used to identify distributed transactions, which may be relayed 
												//	through multiple centralizing environment nodes to distributed environments.
												u_int8_t			global_transaction_id[]	)	{
	
	RPDB_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	if ( ( connection_error = transaction->wrapped_bdb_transaction->prepare(	transaction->wrapped_bdb_transaction,
																				global_transaction_id	) ) )	{
		
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
														connection_error, 
														"RPDB_Transaction_prepare" );
	}
	return transaction;
}

/*****************************
*  rollback  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_abort.html
void RPDB_Transaction_rollback( RPDB_Transaction* transaction )	{
	
	RPDB_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	if ( ( connection_error = transaction->wrapped_bdb_transaction->abort( transaction->wrapped_bdb_transaction ) ) )	{
		
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
														connection_error, 
														"RPDB_Transaction_rollback" );
	}

	//	Close all databases associated with transaction
	RPDB_Transaction_closeAllDatabasesOpenedDuringTransaction( transaction );

	transaction->is_open	=	FALSE;
}

/*************************
*  commit  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_commit.html
void RPDB_Transaction_commit( RPDB_Transaction* transaction )	{
	
	RPDB_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	//	Tell our controller that the depth has changed
	transaction->parent_transaction_controller->current_transaction_depth--;
	
	//	Close all databases associated with transaction
	RPDB_Transaction_closeAllDatabasesOpenedDuringTransaction( transaction );
		
	int			connection_error	= 0;
	if ( ( connection_error = transaction->wrapped_bdb_transaction->commit(	transaction->wrapped_bdb_transaction,
																			RPDB_TransactionSettingsController_internal_commitFlags( RPDB_Transaction_settingsController( transaction ) ) ) ) )	{
																			   
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
														connection_error, 
														"RPDB_Transaction_commit" );
	}

	transaction->is_open	=	FALSE;
}

/*************************************
*  discardRecoveredResources  *
*************************************/

//	Any transactions returned by DB_ENV->txn_recover() that are not named by the _current_ global transaction manager should be discarded using DB_TXN->discard().
//	This call may be used only after calls to DB_ENV->txn_recover() when there are multiple global transaction managers recovering transactions in a single Berkeley DB environment. 
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_discard.html
RPDB_Transaction* RPDB_Transaction_discardRecoveredResources( RPDB_Transaction* transaction )	{
	
	RPDB_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	
	if ( ( connection_error = transaction->wrapped_bdb_transaction->discard(	transaction->wrapped_bdb_transaction,
																				RPDB_TransactionSettingsController_internal_discardFlags( RPDB_Transaction_settingsController( transaction ) ) ) ) )	{
																				
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
														connection_error, 
														"RPDB_Transaction_discardRecoveredResources" );
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

RPDB_Transaction* RPDB_Transaction_internal_newWithoutBDBTransaction( RPDB_TransactionController*	parent_transaction_controller )	{

	RPDB_Transaction*				transaction = calloc( 1, sizeof( RPDB_Transaction ) );

	transaction->parent_transaction_controller = parent_transaction_controller;
	
	return transaction;
}

/*********************
*  transactionID  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
DB_TXN* RPDB_Transaction_internal_transactionID( RPDB_Transaction* transaction )	{
	
	RPDB_Environment*		environment = transaction->parent_transaction_controller->parent_environment;
	
	int			connection_error	= 0;
	
	if ( ( connection_error = transaction->wrapped_bdb_transaction->id( transaction->wrapped_bdb_transaction ) ) )	{
		
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
														connection_error, 
														"RPDB_Transaction_transactionID" );
		return NULL;
	}
	
	return transaction->wrapped_bdb_transaction;
}

/*************************************************
*  addDatabaseToListOpenedDuringTransaction  *
*************************************************/

void RPDB_Transaction_internal_addDatabaseToListOpenedDuringTransaction(	RPDB_Transaction*	transaction,
																			RPDB_Database*		database	)	{
	
	RPDB_DatabaseOpenedDuringTransaction*	database_opened_during_transaction	=	calloc( 1, sizeof( RPDB_DatabaseOpenedDuringTransaction ) );
	
	database_opened_during_transaction->database	=	database;

	if ( transaction->databases_opened_during_transaction == NULL )	{
		transaction->databases_opened_during_transaction		=	database_opened_during_transaction;
	}
	else {

		//	Get a pointer to the next empty pointer
		RPDB_DatabaseOpenedDuringTransaction**	next_empty_pointer	=	& transaction->databases_opened_during_transaction;
		if ( transaction->databases_opened_during_transaction != NULL )	{

			while (		( next_empty_pointer = & ( ( *next_empty_pointer )->next ) ) != NULL
					&&	*next_empty_pointer != NULL )	{
					
			}
		}

		*next_empty_pointer	=	database_opened_during_transaction;
	}

}





