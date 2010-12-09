/*
 *		Rbdb::TransactionController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_TransactionController.h"
#include "Rbdb_TransactionController_internal.h"

#include "Rbdb_Database.h"
#include "Rbdb_Database_internal.h"

#include "Rbdb_Transaction.h"
#include "Rbdb_Transaction_internal.h"

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
	
Rbdb_TransactionController* Rbdb_TransactionController_new( Rbdb_Environment* environment )	{

	Rbdb_TransactionController*		transaction_controller = calloc( 1, sizeof( Rbdb_TransactionController ) );

	transaction_controller->parent_environment = environment;

	transaction_controller->settings_controller	=	Rbdb_SettingsController_transactionSettingsController( Rbdb_Environment_settingsController( environment ) );
	
	uint32_t	max_transactions_open		=	Rbdb_TransactionSettingsController_maxOpen( transaction_controller->settings_controller );
	transaction_controller->transactions	=	calloc( max_transactions_open, sizeof( Rbdb_Transaction* ) );

	return transaction_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_TransactionController_free(	Rbdb_TransactionController** transaction_controller )	{

	if ( ( *transaction_controller )->transactions != NULL )	{
	
		Rbdb_TransactionController_commitAllTransactions( *transaction_controller );
		
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
void Rbdb_TransactionController_closeAllTransactions( Rbdb_TransactionController* transaction_controller )	{
	
	Rbdb_Database_internal_closeAllStoredRuntimeAddresses(	transaction_controller->runtime_storage_database,
																													(void *(*)(void*)) & Rbdb_Transaction_commit );
}

/*********************
*  freeAllTransactions  *
*********************/

//	Free all Transactions (close if necessary)
void Rbdb_TransactionController_freeAllTransactions( Rbdb_TransactionController* transaction_controller )	{

	Rbdb_Database_internal_freeAllStoredRuntimeAddresses(	transaction_controller->runtime_storage_database,
																												(void *(*)(void**)) & Rbdb_Transaction_internal_freeFromRuntimeStorage );
}

/***************************
*  settingsController  *
***************************/
Rbdb_TransactionSettingsController* Rbdb_TransactionController_settingsController(	Rbdb_TransactionController* transaction_controller )	{
	return transaction_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_TransactionController_parentEnvironment(	Rbdb_TransactionController* transaction_controller )	{
	return transaction_controller->parent_environment;
}

/*******************************************************************************************************************************************************************************************
																		Actions
*******************************************************************************************************************************************************************************************/

/*************************
*  beginTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
Rbdb_Transaction* Rbdb_TransactionController_beginTransaction( Rbdb_TransactionController* transaction_controller )	{

	Rbdb_Transaction*	new_transaction	=	Rbdb_Transaction_new( transaction_controller );
	
	return Rbdb_Transaction_begin( new_transaction );
}

/*************************
*  currentTransaction  *
*************************/

Rbdb_Transaction* Rbdb_TransactionController_currentTransaction( Rbdb_TransactionController* transaction_controller )	{

	if ( transaction_controller->current_transaction_depth == 0 )	{
		return NULL;
	}
	return transaction_controller->transactions[ transaction_controller->current_transaction_depth - 1 ];
}
	
/*************************
*  commitTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
void Rbdb_TransactionController_commitTransaction( Rbdb_TransactionController* transaction_controller )	{
	
	//	Commit transaction
	Rbdb_Transaction_commit( Rbdb_TransactionController_currentTransaction( transaction_controller ) );
}

/*************************
*  commitAllTransactions  *
*************************/

void Rbdb_TransactionController_commitAllTransactions( Rbdb_TransactionController* transaction_controller )	{
	
	//	Walk backwards through transactions to close them
	//	If they weren't aborted (meaning they're still open) we commit them
	uint32_t	max_transactions_open		=	Rbdb_TransactionSettingsController_maxOpen( Rbdb_TransactionController_settingsController( transaction_controller) );
	for ( /*  max_transactions_open  */ ; max_transactions_open > 0 ; max_transactions_open-- )	{
		if ( transaction_controller->transactions[ max_transactions_open - 1 ] != NULL )	{
			Rbdb_Transaction_free( & ( transaction_controller->transactions[ max_transactions_open - 1 ] ) );
		}
	}
}

/*************************
*  rollbackTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
void Rbdb_TransactionController_rollbackTransaction( Rbdb_TransactionController* transaction_controller )	{
	
	Rbdb_Transaction_rollback( Rbdb_TransactionController_currentTransaction( transaction_controller ) );
}

/********************************
*  beginConcurrentDataStore  *
********************************/

//	for single threaded operations; permits multiple cursors to be grouped under the same locker
//	this way their locks don't conflict because bdb knows it's safe (since the thread isolates them)
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_cdsgroup_begin.html
Rbdb_Transaction* Rbdb_TransactionController_beginConcurrentDataStoreGroup( Rbdb_TransactionController* transaction_controller )	{

	Rbdb_Transaction*	new_transaction	=	Rbdb_Transaction_new( transaction_controller );
	
	return Rbdb_Transaction_beginConcurrentDataStoreGroup( new_transaction );	
}

/********************************
*  endConcurrentDataStore  *
********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_cdsgroup_begin.html
void Rbdb_TransactionController_endConcurrentDataStoreGroup( Rbdb_TransactionController* transaction_controller )	{
	return Rbdb_TransactionController_commitTransaction( transaction_controller );
}

/*****************************
*  recoverTransactions  *
*****************************/

//	The DB_ENV->txn_recover method should only be called after the environment has been recovered.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_recover.html
Rbdb_Transaction** Rbdb_TransactionController_recoverTransactions( Rbdb_TransactionController* transaction_controller )	{

	Rbdb_Environment*		environment = transaction_controller->parent_environment;

	Rbdb_Transaction**		transaction_array	=	NULL;
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
																							Rbdb_TransactionSettingsController_maximumNumberOfTransactionsToRecover(
																								Rbdb_SettingsController_transactionSettingsController(
																									Rbdb_Environment_settingsController( environment ) ) ),
																							&( transaction_controller->maximum_number_of_transactions_to_recover ),
																							Rbdb_TransactionSettingsController_internal_recoverFlags(
																								Rbdb_SettingsController_transactionSettingsController(
																									Rbdb_Environment_settingsController( environment ) ) ) ) ) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
															connection_error, 
															"Rbdb_TransactionController_recoverTransactions" );
		}
		
		//	FIX
		/*
		if ( transaction_controller->prepared_transactions_to_recover != NULL )	{
			//	Perhaps we should insert a callback here?
		}
		*/
		
		transaction_array = calloc(	transaction_controller->maximum_number_of_transactions_to_recover, sizeof( Rbdb_Transaction ));
														
		u_int32_t		transaction_iterator;
		
		//	Now translate the preplist array into an array of Rbdb_Transaction
		for ( transaction_iterator = 0 ; transaction_iterator < transaction_controller->maximum_number_of_transactions_to_recover ; transaction_iterator++ )	{
			
			Rbdb_Transaction*	transaction_to_recover;
			
			transaction_to_recover = Rbdb_Transaction_internal_newWithoutBDBTransaction(	transaction_controller );
			
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
void Rbdb_TransactionController_commitCheckpoint( Rbdb_TransactionController*	transaction_controller )	{
	
	Rbdb_Environment*		environment = transaction_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		//	If the kbyte parameter is non-zero, a checkpoint will be done if more than kbyte kilobytes of log data have been written since the last checkpoint.
		//	If the min parameter is non-zero, a checkpoint will be done if more than min minutes have passed since the last checkpoint.	
		int			connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_checkpoint(	environment->wrapped_bdb_environment,
																					   0,
																					   0,
																					   Rbdb_TransactionSettingsController_internal_commitCheckpointFlags( Rbdb_SettingsController_transactionSettingsController( Rbdb_Environment_settingsController( environment ) ) ) ) ) )	{
																																							  
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
															connection_error, 
															"Rbdb_TransactionController_commitCheckpoint" );
		}
	}
}

/*************************************************
*  commitCheckpointIfSufficientWrittenData  *
*************************************************/

void Rbdb_TransactionController_commitCheckpointIfSufficientWrittenData(	Rbdb_TransactionController*	transaction_controller,
																			uint32_t						minimum_written_data_for_checkpoint_in_k )	{
	
	Rbdb_Environment*				environment = transaction_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		//	If the kbyte parameter is non-zero, a checkpoint will be done if more than kbyte kilobytes of log data have been written since the last checkpoint.
		int			connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_checkpoint(	environment->wrapped_bdb_environment,
																						minimum_written_data_for_checkpoint_in_k,
																						0,
																						Rbdb_TransactionSettingsController_internal_commitCheckpointFlags( Rbdb_SettingsController_transactionSettingsController( Rbdb_Environment_settingsController( environment ) ) ) ) ) )	{
		  
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
															connection_error, 
															"Rbdb_TransactionController_commitCheckpoint" );
	  }
	}
}

/*************************************************
*  commitCheckpointIfSufficientTimeElapsed  *
*************************************************/

void Rbdb_TransactionController_commitCheckpointIfSufficientTimeElapsed(	Rbdb_TransactionController*	transaction_controller,
																			uint32_t						minimum_time_for_checkpoint_in_minutes )	{
	
	Rbdb_Environment*		environment = transaction_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		//	If the min parameter is non-zero, a checkpoint will be done if more than min minutes have passed since the last checkpoint.	
		int			connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_checkpoint(	environment->wrapped_bdb_environment,
																						0,
																						minimum_time_for_checkpoint_in_minutes,
																						Rbdb_TransactionSettingsController_internal_commitCheckpointFlags( Rbdb_SettingsController_transactionSettingsController( Rbdb_Environment_settingsController( environment ) ) ) ) ) )	{
																																							  
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
															connection_error, 
															"Rbdb_TransactionController_commitCheckpoint" );
		}
	}
}

/*************************************************************
*  commitCheckpointIfSufficientWrittenDataOrTimeElapsed  *
*************************************************************/

void Rbdb_TransactionController_commitCheckpointIfSufficientWrittenDataOrTimeElapsed(	Rbdb_TransactionController*	transaction_controller,
																						uint32_t						minimum_written_data_for_checkpoint_in_k,
																						uint32_t						minimum_time_for_checkpoint_in_minutes )	{
	
	Rbdb_Environment*		environment = transaction_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		//	If the kbyte parameter is non-zero, a checkpoint will be done if more than kbyte kilobytes of log data have been written since the last checkpoint.
		//	If the min parameter is non-zero, a checkpoint will be done if more than min minutes have passed since the last checkpoint.	
		int					connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_checkpoint(	environment->wrapped_bdb_environment,
																						minimum_written_data_for_checkpoint_in_k,
																						minimum_time_for_checkpoint_in_minutes,
																						Rbdb_TransactionSettingsController_internal_commitCheckpointFlags( Rbdb_SettingsController_transactionSettingsController( Rbdb_Environment_settingsController( environment ) ) ) ) ) )	{
																																							  
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
															connection_error, 
															"Rbdb_TransactionController_commitCheckpoint" );
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
DB_TXN* Rbdb_TransactionController_internal_currentTransactionID( Rbdb_TransactionController* transaction_controller )	{

	//	If we aren't currently in a transaction, we return NULL
	if (	transaction_controller != NULL
		&&	transaction_controller->current_transaction_depth )	{
	
		Rbdb_Transaction*	transaction	=	Rbdb_TransactionController_currentTransaction( transaction_controller );
		return transaction->wrapped_bdb_transaction;
	}
	
	return NULL;
}

