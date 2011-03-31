/*
 *		RPbdb::TransactionController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "TransactionController.h"
#include "TransactionController_internal.h"

#include "Database.h"
#include "Database_internal.h"

#include "Transaction.h"
#include "Transaction_internal.h"

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
	
RPbdb_TransactionController* RPbdb_TransactionController_new( RPbdb_Environment* environment )	{

	RPbdb_TransactionController*		transaction_controller = calloc( 1, sizeof( RPbdb_TransactionController ) );

	transaction_controller->parent_environment = environment;

	transaction_controller->settings_controller	=	RPbdb_SettingsController_transactionSettingsController( RPbdb_Environment_settingsController( environment ) );
	
	uint32_t	max_transactions_open		=	RPbdb_TransactionSettingsController_maxOpen( transaction_controller->settings_controller );
	transaction_controller->transactions	=	calloc( max_transactions_open, sizeof( RPbdb_Transaction* ) );

	return transaction_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_TransactionController_free(	RPbdb_TransactionController** transaction_controller )	{

	if ( ( *transaction_controller )->transactions != NULL )	{
	
		RPbdb_TransactionController_commitAllTransactions( *transaction_controller );
		
		//	Free the array of pointers (now that each pointer has been freed)
		free( ( *transaction_controller )->transactions );
		( *transaction_controller )->transactions	= NULL;
	}
	
	free( *transaction_controller );
	*transaction_controller	=	NULL;
}

/**********************
*  closeAllTransactions  *
**********************/

//	Close all Transactions
void RPbdb_TransactionController_closeAllTransactions( RPbdb_TransactionController* transaction_controller )	{
	
	RPbdb_Database_internal_closeAllStoredRuntimeAddresses(	transaction_controller->runtime_storage_database,
																													(void *(*)(void*)) & RPbdb_Transaction_commit );
}

/*********************
*  freeAllTransactions  *
*********************/

//	Free all Transactions (close if necessary)
void RPbdb_TransactionController_freeAllTransactions( RPbdb_TransactionController* transaction_controller )	{

	RPbdb_Database_internal_freeAllStoredRuntimeAddresses(	transaction_controller->runtime_storage_database,
																												(void *(*)(void**)) & RPbdb_Transaction_internal_freeFromRuntimeStorage );
}

/***************************
*  settingsController  *
***************************/
RPbdb_TransactionSettingsController* RPbdb_TransactionController_settingsController(	RPbdb_TransactionController* transaction_controller )	{
	return transaction_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_TransactionController_parentEnvironment(	RPbdb_TransactionController* transaction_controller )	{
	return transaction_controller->parent_environment;
}

/*******************************************************************************************************************************************************************************************
																		Actions
*******************************************************************************************************************************************************************************************/

/*************************
*  beginTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
RPbdb_Transaction* RPbdb_TransactionController_beginTransaction( RPbdb_TransactionController* transaction_controller )	{

	RPbdb_Transaction*	new_transaction	=	RPbdb_Transaction_new( transaction_controller );
	
	return RPbdb_Transaction_begin( new_transaction );
}

/*************************
*  currentTransaction  *
*************************/

RPbdb_Transaction* RPbdb_TransactionController_currentTransaction( RPbdb_TransactionController* transaction_controller )	{

	if ( transaction_controller->current_transaction_depth == 0 )	{
		return NULL;
	}
	return transaction_controller->transactions[ transaction_controller->current_transaction_depth - 1 ];
}
	
/*************************
*  commitTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
void RPbdb_TransactionController_commitTransaction( RPbdb_TransactionController* transaction_controller )	{
	
	//	Commit transaction
	RPbdb_Transaction_commit( RPbdb_TransactionController_currentTransaction( transaction_controller ) );
}

/*************************
*  commitAllTransactions  *
*************************/

void RPbdb_TransactionController_commitAllTransactions( RPbdb_TransactionController* transaction_controller )	{
	
	//	Walk backwards through transactions to close them
	//	If they weren't aborted (meaning they're still open) we commit them
	uint32_t	max_transactions_open		=	RPbdb_TransactionSettingsController_maxOpen( RPbdb_TransactionController_settingsController( transaction_controller) );
	for ( /*  max_transactions_open  */ ; max_transactions_open > 0 ; max_transactions_open-- )	{
		if ( transaction_controller->transactions[ max_transactions_open - 1 ] != NULL )	{
			RPbdb_Transaction_free( & ( transaction_controller->transactions[ max_transactions_open - 1 ] ) );
		}
	}
}

/*************************
*  rollbackTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
void RPbdb_TransactionController_rollbackTransaction( RPbdb_TransactionController* transaction_controller )	{
	
	RPbdb_Transaction_rollback( RPbdb_TransactionController_currentTransaction( transaction_controller ) );
}

/********************************
*  beginConcurrentDataStore  *
********************************/

//	for single threaded operations; permits multiple cursors to be grouped under the same locker
//	this way their locks don't conflict because bdb knows it's safe (since the thread isolates them)
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_cdsgroup_begin.html
RPbdb_Transaction* RPbdb_TransactionController_beginConcurrentDataStoreGroup( RPbdb_TransactionController* transaction_controller )	{

	RPbdb_Transaction*	new_transaction	=	RPbdb_Transaction_new( transaction_controller );
	
	return RPbdb_Transaction_beginConcurrentDataStoreGroup( new_transaction );	
}

/********************************
*  endConcurrentDataStore  *
********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_cdsgroup_begin.html
void RPbdb_TransactionController_endConcurrentDataStoreGroup( RPbdb_TransactionController* transaction_controller )	{
	return RPbdb_TransactionController_commitTransaction( transaction_controller );
}

/*****************************
*  recoverTransactions  *
*****************************/

//	The DB_ENV->txn_recover method should only be called after the environment has been recovered.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_recover.html
RPbdb_Transaction** RPbdb_TransactionController_recoverTransactions( RPbdb_TransactionController* transaction_controller )	{

	RPbdb_Environment*		environment = transaction_controller->parent_environment;

	RPbdb_Transaction**		transaction_array	=	NULL;
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		DB_PREPLIST				transaction_recover_prep_list[ transaction_controller->maximum_number_of_transactions_to_recover ];

		//	On return from DB_ENV->txn_recover, the preplist parameter will be filled in with a list of transactions 
		//	that must be resolved by the application (committed, aborted or discarded). 
		//	The preplist parameter is a structure of type DB_PREPLIST.
		//	The following DB_PREPLIST fields will be filled in:
		//	
		//		The transaction name for the transaction.
		//		DB_TXN * txn;
		//
		//		u_int8_t gid[DB_XIDDATASIZE];
		//		The global transaction ID for the transaction. The global transaction ID is the one specified when the transaction was prepared. The application is responsible for ensuring uniqueness among global transaction IDs.
		int			connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_recover(	environment->wrapped_bdb_environment,
																							transaction_recover_prep_list,
																							RPbdb_TransactionSettingsController_maximumNumberOfTransactionsToRecover(
																								RPbdb_SettingsController_transactionSettingsController(
																									RPbdb_Environment_settingsController( environment ) ) ),
																							&( transaction_controller->maximum_number_of_transactions_to_recover ),
																							RPbdb_TransactionSettingsController_internal_recoverFlags(
																								RPbdb_SettingsController_transactionSettingsController(
																									RPbdb_Environment_settingsController( environment ) ) ) ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
															connection_error, 
															"TransactionController_recoverTransactions" );
		}
		
		//	FIX
		/*
		if ( transaction_controller->prepared_transactions_to_recover != NULL )	{
			//	Perhaps we should insert a callback here?
		}
		*/
		
		transaction_array = calloc(	transaction_controller->maximum_number_of_transactions_to_recover, sizeof( RPbdb_Transaction ));
														
		u_int32_t		transaction_iterator;
		
		//	Now translate the preplist array into an array of RPbdb_Transaction
		for ( transaction_iterator = 0 ; transaction_iterator < transaction_controller->maximum_number_of_transactions_to_recover ; transaction_iterator++ )	{
			
			RPbdb_Transaction*	transaction_to_recover;
			
			transaction_to_recover = RPbdb_Transaction_internal_newWithoutBDBTransaction(	transaction_controller );
			
			transaction_to_recover->wrapped_bdb_transaction		=	transaction_recover_prep_list[ transaction_iterator ].txn;		
			transaction_to_recover->global_id					=	*( transaction_recover_prep_list[ transaction_iterator ].gid );

			transaction_array[ transaction_iterator ] = transaction_to_recover;
		}
	}
		
	return transaction_array;
}	

/*******************************************************************************************************************************************************************************************
																Checkpoint
*******************************************************************************************************************************************************************************************/

/*************************
*  commitCheckpoint  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_checkpoint.html
void RPbdb_TransactionController_commitCheckpoint( RPbdb_TransactionController*	transaction_controller )	{
	
	RPbdb_Environment*		environment = transaction_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		//	If the kbyte parameter is non-zero, a checkpoint will be done if more than kbyte kilobytes of log data have been written since the last checkpoint.
		//	If the min parameter is non-zero, a checkpoint will be done if more than min minutes have passed since the last checkpoint.	
		int			connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_checkpoint(	environment->wrapped_bdb_environment,
																					   0,
																					   0,
																					   RPbdb_TransactionSettingsController_internal_commitCheckpointFlags( RPbdb_SettingsController_transactionSettingsController( RPbdb_Environment_settingsController( environment ) ) ) ) ) )	{
																																							  
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
															connection_error, 
															"TransactionController_commitCheckpoint" );
		}
	}
}

/*************************************************
*  commitCheckpointIfSufficientWrittenData  *
*************************************************/

void RPbdb_TransactionController_commitCheckpointIfSufficientWrittenData(	RPbdb_TransactionController*	transaction_controller,
																			uint32_t						minimum_written_data_for_checkpoint_in_k )	{
	
	RPbdb_Environment*				environment = transaction_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		//	If the kbyte parameter is non-zero, a checkpoint will be done if more than kbyte kilobytes of log data have been written since the last checkpoint.
		int			connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_checkpoint(	environment->wrapped_bdb_environment,
																						minimum_written_data_for_checkpoint_in_k,
																						0,
																						RPbdb_TransactionSettingsController_internal_commitCheckpointFlags( RPbdb_SettingsController_transactionSettingsController( RPbdb_Environment_settingsController( environment ) ) ) ) ) )	{
		  
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
															connection_error, 
															"TransactionController_commitCheckpoint" );
	  }
	}
}

/*************************************************
*  commitCheckpointIfSufficientTimeElapsed  *
*************************************************/

void RPbdb_TransactionController_commitCheckpointIfSufficientTimeElapsed(	RPbdb_TransactionController*	transaction_controller,
																			uint32_t						minimum_time_for_checkpoint_in_minutes )	{
	
	RPbdb_Environment*		environment = transaction_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		//	If the min parameter is non-zero, a checkpoint will be done if more than min minutes have passed since the last checkpoint.	
		int			connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_checkpoint(	environment->wrapped_bdb_environment,
																						0,
																						minimum_time_for_checkpoint_in_minutes,
																						RPbdb_TransactionSettingsController_internal_commitCheckpointFlags( RPbdb_SettingsController_transactionSettingsController( RPbdb_Environment_settingsController( environment ) ) ) ) ) )	{
																																							  
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
															connection_error, 
															"TransactionController_commitCheckpoint" );
		}
	}
}

/*************************************************************
*  commitCheckpointIfSufficientWrittenDataOrTimeElapsed  *
*************************************************************/

void RPbdb_TransactionController_commitCheckpointIfSufficientWrittenDataOrTimeElapsed(	RPbdb_TransactionController*	transaction_controller,
																						uint32_t						minimum_written_data_for_checkpoint_in_k,
																						uint32_t						minimum_time_for_checkpoint_in_minutes )	{
	
	RPbdb_Environment*		environment = transaction_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		//	If the kbyte parameter is non-zero, a checkpoint will be done if more than kbyte kilobytes of log data have been written since the last checkpoint.
		//	If the min parameter is non-zero, a checkpoint will be done if more than min minutes have passed since the last checkpoint.	
		int					connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_checkpoint(	environment->wrapped_bdb_environment,
																						minimum_written_data_for_checkpoint_in_k,
																						minimum_time_for_checkpoint_in_minutes,
																						RPbdb_TransactionSettingsController_internal_commitCheckpointFlags( RPbdb_SettingsController_transactionSettingsController( RPbdb_Environment_settingsController( environment ) ) ) ) ) )	{
																																							  
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
															connection_error, 
															"TransactionController_commitCheckpoint" );
		}	
	}
}


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************************
*  currentTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_checkpoint.html
DB_TXN* RPbdb_TransactionController_internal_currentTransactionID( RPbdb_TransactionController* transaction_controller )	{

	//	If we aren't currently in a transaction, we return NULL
	if (	transaction_controller != NULL
		&&	transaction_controller->current_transaction_depth )	{
	
		RPbdb_Transaction*	transaction	=	RPbdb_TransactionController_currentTransaction( transaction_controller );
		return transaction->wrapped_bdb_transaction;
	}
	
	return NULL;
}

