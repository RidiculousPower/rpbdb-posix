/*
 *		RPDB::TransactionController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_TransactionController.h"
#include "RPDB_TransactionController_internal.h"

#include "RPDB_Transaction.h"
#include "RPDB_Transaction_internal.h"

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
	
RPDB_TransactionController* RPDB_TransactionController_new( RPDB_Environment* environment )	{

	RPDB_TransactionController*		transaction_controller = calloc( 1, sizeof( RPDB_TransactionController ) );

	transaction_controller->parent_environment = environment;

	transaction_controller->settings_controller	=	RPDB_SettingsController_transactionSettingsController( RPDB_Environment_settingsController( environment ) );
	
	uint32_t	max_transactions_open		=	RPDB_TransactionSettingsController_maxOpen( transaction_controller->settings_controller );
	transaction_controller->transactions	=	calloc( max_transactions_open, sizeof( RPDB_Transaction* ) );

	return transaction_controller;
}

/***************************
*  free  *
***************************/
void RPDB_TransactionController_free(	RPDB_TransactionController** transaction_controller )	{

	if ( ( *transaction_controller )->transactions != NULL )	{
	
		RPDB_TransactionController_commitAllTransactions( *transaction_controller );
		
		//	Free the array of pointers (now that each pointer has been freed)
		free( ( *transaction_controller )->transactions );
		( *transaction_controller )->transactions	= NULL;
	}
	
	free( *transaction_controller );
	*transaction_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_TransactionSettingsController* RPDB_TransactionController_settingsController(	RPDB_TransactionController* transaction_controller )	{
	return transaction_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_TransactionController_parentEnvironment(	RPDB_TransactionController* transaction_controller )	{
	return transaction_controller->parent_environment;
}

/*******************************************************************************************************************************************************************************************
																		Actions
*******************************************************************************************************************************************************************************************/

/*************************
*  beginTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
RPDB_Transaction* RPDB_TransactionController_beginTransaction( RPDB_TransactionController* transaction_controller )	{

	RPDB_Transaction*	new_transaction	=	RPDB_Transaction_new( transaction_controller );
	
	return RPDB_Transaction_begin( new_transaction );
}

/*************************
*  currentTransaction  *
*************************/

RPDB_Transaction* RPDB_TransactionController_currentTransaction( RPDB_TransactionController* transaction_controller )	{

	if ( transaction_controller->current_transaction_depth == 0 )	{
		return NULL;
	}
	return transaction_controller->transactions[ transaction_controller->current_transaction_depth - 1 ];
}
	
/*************************
*  commitTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
void RPDB_TransactionController_commitTransaction( RPDB_TransactionController* transaction_controller )	{
	
	//	Commit transaction
	RPDB_Transaction_commit( RPDB_TransactionController_currentTransaction( transaction_controller ) );
}

/*************************
*  commitAllTransactions  *
*************************/

void RPDB_TransactionController_commitAllTransactions( RPDB_TransactionController* transaction_controller )	{
	
	//	Walk backwards through transactions to close them
	//	If they weren't aborted (meaning they're still open) we commit them
	uint32_t	max_transactions_open		=	RPDB_TransactionSettingsController_maxOpen( RPDB_TransactionController_settingsController( transaction_controller) );
	for ( /*  max_transactions_open  */ ; max_transactions_open > 0 ; max_transactions_open-- )	{
		if ( transaction_controller->transactions[ max_transactions_open - 1 ] != NULL )	{
			RPDB_Transaction_free( & ( transaction_controller->transactions[ max_transactions_open - 1 ] ) );
		}
	}
}

/*************************
*  rollbackTransaction  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_id.html
void RPDB_TransactionController_rollbackTransaction( RPDB_TransactionController* transaction_controller )	{
	
	RPDB_Transaction_rollback( RPDB_TransactionController_currentTransaction( transaction_controller ) );
}

/********************************
*  beginConcurrentDataStore  *
********************************/

//	for single threaded operations; permits multiple cursors to be grouped under the same locker
//	this way their locks don't conflict because bdb knows it's safe (since the thread isolates them)
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_cdsgroup_begin.html
RPDB_Transaction* RPDB_TransactionController_beginConcurrentDataStoreGroup( RPDB_TransactionController* transaction_controller )	{

	RPDB_Transaction*	new_transaction	=	RPDB_Transaction_new( transaction_controller );
	
	return RPDB_Transaction_beginConcurrentDataStoreGroup( new_transaction );	
}

/********************************
*  endConcurrentDataStore  *
********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_cdsgroup_begin.html
void RPDB_TransactionController_endConcurrentDataStoreGroup( RPDB_TransactionController* transaction_controller )	{
	return RPDB_TransactionController_commitTransaction( transaction_controller );
}

/*****************************
*  recoverTransactions  *
*****************************/

//	The DB_ENV->txn_recover method should only be called after the environment has been recovered.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_recover.html
RPDB_Transaction** RPDB_TransactionController_recoverTransactions( RPDB_TransactionController* transaction_controller )	{

	RPDB_Environment*		environment = transaction_controller->parent_environment;

	RPDB_Transaction**		transaction_array	=	NULL;
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
																							RPDB_TransactionSettingsController_maximumNumberOfTransactionsToRecover(
																								RPDB_SettingsController_transactionSettingsController(
																									RPDB_Environment_settingsController( environment ) ) ),
																							&( transaction_controller->maximum_number_of_transactions_to_recover ),
																							RPDB_TransactionSettingsController_internal_recoverFlags(
																								RPDB_SettingsController_transactionSettingsController(
																									RPDB_Environment_settingsController( environment ) ) ) ) ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
															connection_error, 
															"RPDB_TransactionController_recoverTransactions" );
		}
		
		//	FIX
		/*
		if ( transaction_controller->prepared_transactions_to_recover != NULL )	{
			//	Perhaps we should insert a callback here?
		}
		*/
		
		transaction_array = calloc(	transaction_controller->maximum_number_of_transactions_to_recover, sizeof( RPDB_Transaction ));
														
		u_int32_t		transaction_iterator;
		
		//	Now translate the preplist array into an array of RPDB_Transaction
		for ( transaction_iterator = 0 ; transaction_iterator < transaction_controller->maximum_number_of_transactions_to_recover ; transaction_iterator++ )	{
			
			RPDB_Transaction*	transaction_to_recover;
			
			transaction_to_recover = RPDB_Transaction_internal_newWithoutBDBTransaction(	transaction_controller );
			
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
void RPDB_TransactionController_commitCheckpoint( RPDB_TransactionController*	transaction_controller )	{
	
	RPDB_Environment*		environment = transaction_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		//	If the kbyte parameter is non-zero, a checkpoint will be done if more than kbyte kilobytes of log data have been written since the last checkpoint.
		//	If the min parameter is non-zero, a checkpoint will be done if more than min minutes have passed since the last checkpoint.	
		int			connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_checkpoint(	environment->wrapped_bdb_environment,
																					   0,
																					   0,
																					   RPDB_TransactionSettingsController_internal_commitCheckpointFlags( RPDB_SettingsController_transactionSettingsController( RPDB_Environment_settingsController( environment ) ) ) ) ) )	{
																																							  
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
															connection_error, 
															"RPDB_TransactionController_commitCheckpoint" );
		}
	}
}

/*************************************************
*  commitCheckpointIfSufficientWrittenData  *
*************************************************/

void RPDB_TransactionController_commitCheckpointIfSufficientWrittenData(	RPDB_TransactionController*	transaction_controller,
																			uint32_t						minimum_written_data_for_checkpoint_in_k )	{
	
	RPDB_Environment*				environment = transaction_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		//	If the kbyte parameter is non-zero, a checkpoint will be done if more than kbyte kilobytes of log data have been written since the last checkpoint.
		int			connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_checkpoint(	environment->wrapped_bdb_environment,
																						minimum_written_data_for_checkpoint_in_k,
																						0,
																						RPDB_TransactionSettingsController_internal_commitCheckpointFlags( RPDB_SettingsController_transactionSettingsController( RPDB_Environment_settingsController( environment ) ) ) ) ) )	{
		  
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
															connection_error, 
															"RPDB_TransactionController_commitCheckpoint" );
	  }
	}
}

/*************************************************
*  commitCheckpointIfSufficientTimeElapsed  *
*************************************************/

void RPDB_TransactionController_commitCheckpointIfSufficientTimeElapsed(	RPDB_TransactionController*	transaction_controller,
																			uint32_t						minimum_time_for_checkpoint_in_minutes )	{
	
	RPDB_Environment*		environment = transaction_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		//	If the min parameter is non-zero, a checkpoint will be done if more than min minutes have passed since the last checkpoint.	
		int			connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_checkpoint(	environment->wrapped_bdb_environment,
																						0,
																						minimum_time_for_checkpoint_in_minutes,
																						RPDB_TransactionSettingsController_internal_commitCheckpointFlags( RPDB_SettingsController_transactionSettingsController( RPDB_Environment_settingsController( environment ) ) ) ) ) )	{
																																							  
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
															connection_error, 
															"RPDB_TransactionController_commitCheckpoint" );
		}
	}
}

/*************************************************************
*  commitCheckpointIfSufficientWrittenDataOrTimeElapsed  *
*************************************************************/

void RPDB_TransactionController_commitCheckpointIfSufficientWrittenDataOrTimeElapsed(	RPDB_TransactionController*	transaction_controller,
																						uint32_t						minimum_written_data_for_checkpoint_in_k,
																						uint32_t						minimum_time_for_checkpoint_in_minutes )	{
	
	RPDB_Environment*		environment = transaction_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		//	If the kbyte parameter is non-zero, a checkpoint will be done if more than kbyte kilobytes of log data have been written since the last checkpoint.
		//	If the min parameter is non-zero, a checkpoint will be done if more than min minutes have passed since the last checkpoint.	
		int					connection_error	= RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->txn_checkpoint(	environment->wrapped_bdb_environment,
																						minimum_written_data_for_checkpoint_in_k,
																						minimum_time_for_checkpoint_in_minutes,
																						RPDB_TransactionSettingsController_internal_commitCheckpointFlags( RPDB_SettingsController_transactionSettingsController( RPDB_Environment_settingsController( environment ) ) ) ) ) )	{
																																							  
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
															connection_error, 
															"RPDB_TransactionController_commitCheckpoint" );
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
DB_TXN* RPDB_TransactionController_internal_currentTransactionID( RPDB_TransactionController* transaction_controller )	{

	//	If we aren't currently in a transaction, we return NULL
	if (	transaction_controller != NULL
		&&	transaction_controller->current_transaction_depth )	{
	
		RPDB_Transaction*	transaction	=	RPDB_TransactionController_currentTransaction( transaction_controller );
		return transaction->wrapped_bdb_transaction;
	}
	
	return NULL;
}

