/*
 *		RPbdb::RPbdb_SettingsController::RPbdb_ConcurrentDataStoreSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "TransactionSettingsController.h"

#include "Environment.h"
#include "TransactionSettingsController.h"
#include "RuntimeStorageController.h"
#include "Record.h"
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

RPbdb_TransactionSettingsController* RPbdb_TransactionSettingsController_new( RPbdb_SettingsController* settings_controller )	{

	RPbdb_TransactionSettingsController*		transaction_settings_controller = calloc( 1, sizeof( RPbdb_TransactionSettingsController ) );

	transaction_settings_controller->parent_settings_controller = settings_controller;
	
	//	We set callbacks for individual events, so transaction recovery callback method should always be enabled
	//	However, no events are set before the TransactionSettingsController is created, so we can set the callback here,
	//	at least as long as the environment has not been opened
	/*
	if (	RPbdb_Environment_isOpen( environment ) == FALSE 
		&&	environment->wrapped_bdb_database != NULL )	{

		environment->wrapped_bdb_environment->wrapped_bdb_environment->wrapped_bdb_environment->set_app_dispatch(	environment->wrapped_bdb_environment->wrapped_bdb_environment->wrapped_bdb_environment, 
																& RPbdb_TransactionSettingsController_internal_transactionRecoveryCallbackMethod );
	}
	*/
	
	return transaction_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_TransactionSettingsController_free(	RPbdb_TransactionSettingsController** transaction_settings_controller )	{

	free( *transaction_settings_controller );
	*transaction_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_TransactionSettingsController_parentEnvironment(	RPbdb_TransactionSettingsController* transaction_settings_controller )	{
	return transaction_settings_controller->parent_settings_controller->parent_environment;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/**********
*  on  *
**********/

//	DB_INIT_TXN             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
//	Returns DB_INIT_TXN or FALSE
int RPbdb_TransactionSettingsController_on( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
	if ( transaction_settings_controller->on == TRUE )	{
		return DB_INIT_TXN;
	}
	return FALSE;
}

/**********
*  off  *
**********/

//	DB_INIT_TXN             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
//	Doesn't seem like off should return the flag, so TRUE/FALSE
BOOL RPbdb_TransactionSettingsController_off( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
	if ( transaction_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

	/**************
	*  turnOn  *
	**************/

	//	DB_INIT_TXN             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPbdb_TransactionSettingsController_turnOn( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->on = TRUE;
	}

	/**************
	*  turnOff  *
	**************/

	//	DB_INIT_TXN             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	//	Returns DB_INIT_TXN or FALSE
	void RPbdb_TransactionSettingsController_turnOff( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->on = FALSE;
	}

/*****************************
*  prohibitSyncOnWrite  *
*****************************/

//	DB_TXN_WRITE_NOSYNC     http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPbdb_TransactionSettingsController_prohibitSyncOnWrite( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
	if ( transaction_settings_controller->prohibit_sync_on_write == TRUE )	{
		return DB_TXN_WRITE_NOSYNC;
	}
	return FALSE;
}

	/********************************
	*  prohibitSyncOnWriteOn  *
	********************************/

	//	DB_TXN_WRITE_NOSYNC     http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPbdb_TransactionSettingsController_turnProhibitSyncOnWriteTransactionOn( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->prohibit_sync_on_write = TRUE;
	}
	
	/********************************
	*  prohibitSyncOnWriteOff  *
	********************************/

	//	DB_TXN_WRITE_NOSYNC     http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPbdb_TransactionSettingsController_turnProhibitSyncOnWriteTransactionOff( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->prohibit_sync_on_write = FALSE;
	}
	
/********************************************
*  prohibitSyncOnCommitTransaction  *
********************************************/

//	DB_TXN_NOSYNC           http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPbdb_TransactionSettingsController_prohibitSyncOnCommit( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
	if ( transaction_settings_controller->prohibit_sync_on_commit == TRUE )	{
		return DB_TXN_NOSYNC;
	}
	return FALSE;
}

	/********************************************
	*  prohibitSyncOnCommitTransactionOn  *
	********************************************/

	//	DB_TXN_NOSYNC           http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPbdb_TransactionSettingsController_turnProhibitSyncOnCommitOn( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->prohibit_sync_on_commit = TRUE;
		RPbdb_TransactionSettingsController_turnSyncOnCommitOff( transaction_settings_controller );
	}

	/********************************************
	*  prohibitSyncOnCommitTransactionOff  *
	********************************************/

	//	DB_TXN_NOSYNC           http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPbdb_TransactionSettingsController_turnProhibitSyncOnCommitOff( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->prohibit_sync_on_commit = FALSE;
	}

/****************************************
*  timeoutReturnsDenyNotDeadlock  *
****************************************/

//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPbdb_TransactionSettingsController_timeoutInMicrosecondsReturnsDenyNotDeadlock( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
	if ( transaction_settings_controller->timeout_returns_deny_not_deadlock == TRUE )	{
		return DB_TIME_NOTGRANTED;	
	}
	return FALSE;
}

	/********************************************
	*  timeoutReturnsDenyNotDeadlockOn  *
	********************************************/

	//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPbdb_TransactionSettingsController_turnTimeoutInMicrosecondsReturnsDenyNotDeadlockOn( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->timeout_returns_deny_not_deadlock = TRUE;
	}

	/********************************************
	*  timeoutReturnsDenyNotDeadlockOff  *
	********************************************/

	//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPbdb_TransactionSettingsController_turnTimeoutInMicrosecondsReturnsDenyNotDeadlockOff( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->timeout_returns_deny_not_deadlock = FALSE;
	}

/************************************
*  concurrentDataStoreLocking  *
************************************/

//	DB_INIT_CDB - 			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
//	only other flag allowed concurrently is DB_INIT_MPOOL; multiple reader single write mode
int RPbdb_TransactionSettingsController_concurrentDataStoreLocking( RPbdb_TransactionSettingsController*							transaction_settings_controller )	{
	if ( transaction_settings_controller->concurrent_data_store_locking == TRUE )	{
		return DB_INIT_CDB;
	}
	return FALSE;
}

	/************************************
	*  concurrentDataStoreLockingOn  *
	************************************/

	void RPbdb_TransactionSettingsController_turnConcurrentDataStoreLockingOn( RPbdb_TransactionSettingsController*							transaction_settings_controller )	{
		transaction_settings_controller->concurrent_data_store_locking = TRUE;
	}

	/****************************************
	*  concurrentDataStoreLockingOff  *
	****************************************/

	void RPbdb_TransactionSettingsController_turnConcurrentDataStoreLockingOff( RPbdb_TransactionSettingsController*							transaction_settings_controller )	{
		transaction_settings_controller->concurrent_data_store_locking = FALSE;
	}

/****************************
*  snapshotIsolation  *
****************************/

//	DB_TXN_SNAPSHOT         http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
//	DB_TXN_SNAPSHOT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
int RPbdb_TransactionSettingsController_snapshotIsolation( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->snapshot_isolation == TRUE )	{
		return DB_TXN_SNAPSHOT;
	}

	return FALSE;	
}

	/****************************
	*  snapshotIsolationOn  *
	****************************/

	//	DB_TXN_SNAPSHOT         http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	//	DB_TXN_SNAPSHOT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
	void RPbdb_TransactionSettingsController_turnSnapshotIsolationOn( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->snapshot_isolation = TRUE;
	}

	/********************************
	*  snapshotIsolationOff  *
	********************************/

	//	DB_TXN_SNAPSHOT         http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	//	DB_TXN_SNAPSHOT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
	void RPbdb_TransactionSettingsController_turnSnapshotIsolationOff( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->snapshot_isolation = FALSE;
	}

/************************************
*  degreeOneIsolation  *
************************************/

//	DB_READ_UNCOMMITTED		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
//	This should also make sure that the ThreadSettingsController flag was on with the DB Open
//	http://www.oracle.com/technology/documentation/berkeley-db/db/ref/transapp/read.html
int RPbdb_TransactionSettingsController_degreeOneIsolation( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->degree_one_isolation == TRUE )	{
		return DB_READ_UNCOMMITTED;
	}

	return FALSE;
}

	/****************************************
	*  turnDegreeOneIsolationOn  *
	****************************************/

	void RPbdb_TransactionSettingsController_turnDegreeOneIsolationOn( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->degree_one_isolation = TRUE;
	}

	/****************************************
	*  turnDegreeOneIsolationOff  *
	****************************************/

	void RPbdb_TransactionSettingsController_turnDegreeOneIsolationOff( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->degree_one_isolation = FALSE;
	}

/****************************
*  degreeTwoIsolation  *
****************************/

//	DB_READ_COMMITTED		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
//	http://www.oracle.com/technology/documentation/berkeley-db/db/ref/transapp/read.html
int RPbdb_TransactionSettingsController_degreeTwoIsolation( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->degree_two_isolation == TRUE )	{
		return DB_READ_COMMITTED;
	}
	return FALSE;
}

	/****************************
	*  degreeTwoIsolationOn  *
	****************************/

	void RPbdb_TransactionSettingsController_turnDegreeTwoIsolationOn( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->degree_two_isolation = TRUE;
	}

	/****************************
	*  degreeTwoIsolationOff  *
	****************************/

	void RPbdb_TransactionSettingsController_turnDegreeTwoIsolationOff( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->degree_two_isolation = FALSE;
	}

/**********************************************
*  encloseAllActivityInTransaction  *
**********************************************/

//	DB_AUTO_COMMIT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPbdb_TransactionSettingsController_encloseAllActivityInTransaction( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->enclose_all_activity_in_transaction == TRUE )	{
		return DB_AUTO_COMMIT;	
	}
	return FALSE;
}

	/*****************************************************
	*  turnEncloseAllActivityInTransactionOn  *
	*****************************************************/

	void RPbdb_TransactionSettingsController_turnEncloseAllActivityInTransactionOn( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->enclose_all_activity_in_transaction = TRUE;
	}

	/*****************************************************
	*  turnEncloseAllActivityInTransactionOff  *
	*****************************************************/

	void RPbdb_TransactionSettingsController_turnEncloseAllActivityInTransactionOff( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->enclose_all_activity_in_transaction = FALSE;
	}

/******************************************
*  environmentalSnapshotIsolation  *
******************************************/

//	DB_MULTIVERSION         http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPbdb_TransactionSettingsController_environmentalSnapshotIsolation( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->environmental_snapshot_isolation == TRUE )	{
		return DB_MULTIVERSION;
	}
	return FALSE;
}

	/*********************************************
	*  turnEnvironmentalSnapshotIsolationOn  *
	*********************************************/

	void RPbdb_TransactionSettingsController_turnEnvironmentalSnapshotIsolationOn( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->environmental_snapshot_isolation = TRUE;
	}

	/*********************************************
	*  turnEnvironmentalSnapshotIsolationOff  *
	*********************************************/

	void RPbdb_TransactionSettingsController_turnEnvironmentalSnapshotIsolationOff( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->environmental_snapshot_isolation = FALSE;
	}

/******************************************
*  syncOnCommit  *
******************************************/

//	DB_TXN_SYNC         http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_begin.html
int RPbdb_TransactionSettingsController_syncOnCommit( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->sync_on_commit == TRUE )	{
		return DB_TXN_SYNC;
	}
	return FALSE;
}

	/*********************************************
	*  turnSyncOnCommitOn  *
	*********************************************/

	void RPbdb_TransactionSettingsController_turnSyncOnCommitOn( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->sync_on_commit = TRUE;
	}

	/*********************************************
	*  turnSyncOnCommitOff  *
	*********************************************/

	void RPbdb_TransactionSettingsController_turnSyncOnCommitOff( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->sync_on_commit = FALSE;
	}

/******************************************
*  waitForLocks  *
******************************************/

//	DB_TXN_WAIT         http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_begin.html
int RPbdb_TransactionSettingsController_waitForLocks( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->wait_for_locks == TRUE )	{
		return DB_TXN_WAIT;
	}
	return FALSE;
}

	/*********************************************
	*  turnSyncOnCommitOn  *
	*********************************************/

	void RPbdb_TransactionSettingsController_turnWaitForLocksOn( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->wait_for_locks = TRUE;
	}

	/*********************************************
	*  turnSyncOnCommitOff  *
	*********************************************/

	void RPbdb_TransactionSettingsController_turnWaitForLocksOff( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->wait_for_locks = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/************************************************
*  maximumNumberOfTransactionsToRecover  *
************************************************/

long RPbdb_TransactionSettingsController_maximumNumberOfTransactionsToRecover( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
	
	return transaction_settings_controller->maximum_number_of_transactions_to_recover;
}

/****************************************************
*  setMaximumNumberOfTransactionsToRecover  *
****************************************************/

void RPbdb_TransactionSettingsController_setMaximumNumberOfTransactionsToRecover(	RPbdb_TransactionSettingsController*	transaction_settings_controller,
																					long									maximum_number_of_transactions_to_recover )	{

	transaction_settings_controller->maximum_number_of_transactions_to_recover = maximum_number_of_transactions_to_recover;
}

/****************
*  timeout  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_timeout.html
uint32_t RPbdb_TransactionSettingsController_timeoutInMicroseconds( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	RPbdb_Environment*		environment = transaction_settings_controller->parent_settings_controller->parent_environment;

	//	an unsigned 32-bit number of microseconds, limiting the maximum timeout to roughly 71 minutes.
	
	//	If we already have timeout stored in the settings controller then we know we've asked for it from the DB;
	//	Otherwise we need to ask the DB for it. 
	//	If it gets updated after we asked, the local record of it also got updated; we know we are always up to date.
	if ( environment->wrapped_bdb_environment != NULL )	{	
			
		environment->wrapped_bdb_environment->get_timeout( environment->wrapped_bdb_environment, &( transaction_settings_controller->timeout_in_microseconds ), DB_SET_TXN_TIMEOUT );
	}
	
	return transaction_settings_controller->timeout_in_microseconds;
}

/********************
*  setTimeout  *
********************/

//	DB_SET_TXN_TIMEOUT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_timeout.html
void RPbdb_TransactionSettingsController_setTimeoutInMicroseconds(	RPbdb_TransactionSettingsController*	transaction_settings_controller, 
																	uint32_t								timeout_in_microseconds )	{

	RPbdb_Environment*		environment = transaction_settings_controller->parent_settings_controller->parent_environment;

	transaction_settings_controller->timeout_in_microseconds = timeout_in_microseconds;
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_timeout( environment->wrapped_bdb_environment, timeout_in_microseconds, DB_SET_TXN_TIMEOUT );
	}
}

/****************
*  maxOpen  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_tx_max.html
uint32_t RPbdb_TransactionSettingsController_maxOpen( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	RPbdb_Environment*		environment = transaction_settings_controller->parent_settings_controller->parent_environment;

	//	If we already have timeout stored in the settings controller then we know we've asked for it from the DB;
	//	Otherwise we need to ask the DB for it. 
	//	If it gets updated after we asked, the local record of it also got updated; we know we are always up to date.
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_tx_max( environment->wrapped_bdb_environment, &( transaction_settings_controller->max_open ) );
	}
	
	return transaction_settings_controller->max_open;
}

/********************
*  setMaxOpen  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_tx_max.html
void RPbdb_TransactionSettingsController_setMaxOpen(	RPbdb_TransactionSettingsController*	transaction_settings_controller, 
														uint32_t								max_open )	{

	RPbdb_Environment*		environment = transaction_settings_controller->parent_settings_controller->parent_environment;

	transaction_settings_controller->max_open = max_open;
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_tx_max( environment->wrapped_bdb_environment, max_open );
	}
}

/********************
*  timestamp  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_tx_timestamp.html
time_t RPbdb_TransactionSettingsController_recoveryTimestamp( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	RPbdb_Environment*		environment = transaction_settings_controller->parent_settings_controller->parent_environment;

	//	If we already have timeout stored in the settings controller then we know we've asked for it from the DB;
	//	Otherwise we need to ask the DB for it. 
	//	If it gets updated after we asked, the local record of it also got updated; we know we are always up to date.
	if (	transaction_settings_controller->recovery_timestamp
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_tx_timestamp(	environment->wrapped_bdb_environment, 
																														& transaction_settings_controller->recovery_timestamp );
	}
	
	return transaction_settings_controller->recovery_timestamp;
}

/********************
*  setTimestamp  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_tx_timestamp.html
void RPbdb_TransactionSettingsController_setRecoveryTimestamp(	RPbdb_TransactionSettingsController*	transaction_settings_controller, 
																															time_t									recovery_timestamp )	{

	RPbdb_Environment*		environment = transaction_settings_controller->parent_settings_controller->parent_environment;
	
	transaction_settings_controller->recovery_timestamp = recovery_timestamp;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->set_tx_timestamp(	environment->wrapped_bdb_environment, 
																														& transaction_settings_controller->recovery_timestamp );
	}
}

/*******************************************************************************************************************************************************************************************
																		Callback Public Methods
*******************************************************************************************************************************************************************************************/

/****************************************
*  setRollbackwardCallbackMethod  *
****************************************/
/*
void RPbdb_TransactionSettingsController_setRollbackwardCallbackMethod(	RPbdb_TransactionSettingsController*						transaction_settings_controller,
																		int (*rollbackward_callback_method)(	RPbdb_Environment*				environment->wrapped_bdb_environment,
																												RPbdb_Record*		transaction_log_record ) )	{
																													
	transaction_settings_controller->roll_backward_callback_method = roll_backward_callback_method;
}
*/
/************************************
*  rollbackwardCallbackMethod  *
************************************/
/*
int (*rollbackward_callback_method)(	RPbdb_Environment*				environment->wrapped_bdb_environment,
										RPbdb_Record*		transaction_log_record ) RPbdb_TransactionSettingsController_rollbackwardCallbackMethod( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	return transaction_settings_controller->roll_backward_callback_method;
}
*/
/****************************************
*  setRollforwardCallbackMethod  *
****************************************/
/*
void RPbdb_TransactionSettingsController_setRollforwardCallbackMethod(	RPbdb_TransactionSettingsController*					transaction_settings_controller,
																		int (*rollforward_callback_method)(	RPbdb_Environment*				environment->wrapped_bdb_environment,
																											RPbdb_Record*		transaction_log_record ) )	{
																													
	transaction_settings_controller->roll_forward_callback_method = roll_forward_callback_method;																							
}
*/
/************************************
*  rollforwardCallbackMethod  *
************************************/
/*
int (*rollforward_callback_method)(	RPbdb_Environment*				environment->wrapped_bdb_environment,
									RPbdb_Record*		transaction_log_record ) RPbdb_TransactionSettingsController_rollforwardCallbackMethod( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	return transaction_settings_controller->roll_forward_callback_method;
}
*/
/********************************
*  setAbortCallbackMethod  *
********************************/
/*
void RPbdb_TransactionSettingsController_setAbortCallbackMethod(	RPbdb_TransactionSettingsController* 						transaction_settings_controller,
																	int (*abort_callback_method)(	RPbdb_Environment*						environment->wrapped_bdb_environment,
																									RPbdb_Record*				transaction_log_record ) )	{
																													
	transaction_settings_controller->abort_callback_method = abort_callback_method;																							
}
*/
/********************************
*  abortCallbackMethod  *
********************************/
/*
int (*abort_callback_method)(	RPbdb_Environment*				environment->wrapped_bdb_environment,
								RPbdb_Record*		transaction_log_record ) RPbdb_TransactionSettingsController_abortCallbackMethod( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	return transaction_settings_controller->abort_callback_method;
}
*/
/********************************
*  setApplyCallbackMethod  *
********************************/
/*
void RPbdb_TransactionSettingsController_setApplyCallbackMethod(	RPbdb_TransactionSettingsController*				transaction_settings_controller,
																	int (*apply_callback_method)(	RPbdb_Environment*				environment->wrapped_bdb_environment,
																									RPbdb_Record*		transaction_log_record ) )	{
																													
	transaction_settings_controller->apply_callback_method = apply_callback_method;																							
}
*/
/********************************
*  applyCallbackMethod  *
********************************/
/*
int (*apply_callback_method)(	RPbdb_Environment*				environment->wrapped_bdb_environment,
								RPbdb_Record*		transaction_log_record ) RPbdb_TransactionSettingsController_applyCallbackMethod( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	return transaction_settings_controller->apply_callback_method;
}
*/
/********************************
*  setPrintCallbackMethod  *
********************************/
/*
void RPbdb_TransactionSettingsController_setPrintCallbackMethod(	RPbdb_TransactionSettingsController*				transaction_settings_controller,
																	int (*print_callback_method)(	RPbdb_Environment*				environment->wrapped_bdb_environment,
																									RPbdb_Record*		transaction_log_record ) )	{
					
	transaction_settings_controller->print_callback_method = print_callback_method;																							
}
*/
/********************************
*  printCallbackMethod  *
********************************/
/*
int (*print_callback_method)(	RPbdb_Environment*				environment->wrapped_bdb_environment,
								RPbdb_Record*		transaction_log_record ) RPbdb_TransactionSettingsController_printCallbackMethod( RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	return transaction_settings_controller->print_callback_method;
}
*/
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_app_dispatch.html
//	From http://www.oracle.com/technology/documentation/berkeley-db/db/ref/apprec/intro.html
//	The recovery functions must not use Berkeley DB methods to access data in the environment as there is no way to coordinate these accesses with either the aborting transaction or the updates done by recovery or replication.)
int RPbdb_TransactionSettingsController_internal_transactionRecoveryCallbackMethod(	DB_ENV*			bdb_environment->wrapped_bdb_environment, 
																					DBT*			transaction_log_record, 
																					DB_LSN*			lsn, 
																					db_recops		recovery_operation )	{
	
	RPbdb_Environment*									environment				= RPbdb_RuntimeStorageController_environmentForBDBEnvironment( bdb_environment );
	RPbdb_Record*							transaction_log_record	= RPbdb_Record_newFromRawKeyDBTDataPair(	lsn,
																												transaction_log_record );

	RPbdb_TransactionSettingsController*	transaction_settings_controller	=	RPbdb_SettingsController_transactionSettingsController(
																					RPbdb_Environment_settingsController( environment ) );

	switch ( recovery_operation )	{
		
		case DB_TXN_BACKWARD_ROLL:
			if ( transaction_settings_controller->roll_backward_callback_method != NULL )	{
				return *( transaction_settings_controller->roll_backward_callback_method )(	environment->wrapped_bdb_environment,
																								transaction_log_record );
			}
			break;
		
		case DB_TXN_FORWARD_ROLL:
			if ( transaction_settings_controller->roll_forward_callback_method != NULL )	{
				return *( transaction_settings_controller->roll_forward_callback_method )(	environment->wrapped_bdb_environment,
																							transaction_log_record );
			}
			break;
		
		case DB_TXN_ABORT:
			if ( transaction_settings_controller->abort_callback_method != NULL )	{
				return *( transaction_settings_controller->abort_callback_method )(	environment->wrapped_bdb_environment,
																					transaction_log_record );
			}
			break;
		
		case DB_TXN_APPLY:
			if ( transaction_settings_controller->apply_callback_method != NULL )	{
				return *( transaction_settings_controller->apply_callback_method )(	environment->wrapped_bdb_environment,
																					transaction_log_record );
			}
			break;
		
		case DB_TXN_PRINT:
			if ( transaction_settings_controller->print_callback_method != NULL )	{
				return *( transaction_settings_controller->print_callback_method )(	environment->wrapped_bdb_environment,
																					transaction_log_record );
			}
			break;
	}
	//	Should never get here
	return FALSE;
}
*/
/************************
*  beginFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_discard.html
int RPbdb_TransactionSettingsController_internal_beginFlags( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
	
	return RPbdb_TransactionSettingsController_degreeTwoIsolation( transaction_settings_controller )
			|	RPbdb_TransactionSettingsController_degreeOneIsolation( transaction_settings_controller )
			|	RPbdb_TransactionSettingsController_prohibitSyncOnCommit( transaction_settings_controller )
			|	RPbdb_TransactionSettingsController_waitForLocks( transaction_settings_controller )
			|	RPbdb_TransactionSettingsController_snapshotIsolation( transaction_settings_controller )
			|	RPbdb_TransactionSettingsController_syncOnCommit( transaction_settings_controller )
			|	RPbdb_TransactionSettingsController_waitForLocks( transaction_settings_controller )
			|	RPbdb_TransactionSettingsController_prohibitSyncOnWrite( transaction_settings_controller );
}

/************************
*  discardFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_discard.html
int RPbdb_TransactionSettingsController_internal_discardFlags( RPbdb_TransactionSettingsController* transaction_settings_controller __attribute__((unused)) )	{
	
	//	Currently unused
	return RPBDB_NO_FLAGS;
}

/************************
*  commitFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_commit.html
int RPbdb_TransactionSettingsController_internal_commitFlags( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
	
	return	RPbdb_TransactionSettingsController_prohibitSyncOnCommit( transaction_settings_controller )
			|	RPbdb_TransactionSettingsController_syncOnCommit( transaction_settings_controller );
}

/********************************
*  commitCheckpointFlags  *
********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_checkpoint.html
int RPbdb_TransactionSettingsController_internal_commitCheckpointFlags( RPbdb_TransactionSettingsController* transaction_settings_controller __attribute__((unused)) )	{
	
	//	we need to add a forceCheckpoint function instead of this flag
	//	FIX
	
	//	We have one flag - DB_FORCE - which has its own function
	//	Otherwise, we have no flags; this function is here only in the case future support of other flags becomes relevant. 
	return RPBDB_NO_FLAGS;
}

/************************
*  recoverFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_recover.html
int RPbdb_TransactionSettingsController_internal_recoverFlags( RPbdb_TransactionSettingsController* transaction_settings_controller )	{
	
	if ( transaction_settings_controller->started_transaction_recover == FALSE )	{
		return DB_FIRST;
	}
	else	{
		return DB_NEXT;
	}

}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_TransactionSettingsController* RPbdb_TransactionSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_TransactionSettingsController* transaction_settings_controller )	{

	RPbdb_TransactionSettingsController* transaction_settings_controller_copy	=	RPbdb_TransactionSettingsController_new( transaction_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	transaction_settings_controller_copy->environmental_snapshot_isolation	=	transaction_settings_controller->environmental_snapshot_isolation;
	transaction_settings_controller_copy->timeout_in_microseconds	=	transaction_settings_controller->timeout_in_microseconds;
	transaction_settings_controller_copy->wait_for_locks	=	transaction_settings_controller->wait_for_locks;
	transaction_settings_controller_copy->recovery_timestamp	=	transaction_settings_controller->recovery_timestamp;
	transaction_settings_controller_copy->prohibit_sync_on_write	=	transaction_settings_controller->prohibit_sync_on_write;
	transaction_settings_controller_copy->degree_one_isolation	=	transaction_settings_controller->degree_one_isolation;
	transaction_settings_controller_copy->concurrent_data_store_locking	=	transaction_settings_controller->concurrent_data_store_locking;
	transaction_settings_controller_copy->started_transaction_recover	=	transaction_settings_controller->started_transaction_recover;
	transaction_settings_controller_copy->max_open	=	transaction_settings_controller->max_open;
	transaction_settings_controller_copy->maximum_number_of_transactions_to_recover	=	transaction_settings_controller->maximum_number_of_transactions_to_recover;
	transaction_settings_controller_copy->enclose_all_activity_in_transaction	=	transaction_settings_controller->enclose_all_activity_in_transaction;
	transaction_settings_controller_copy->degree_two_isolation	=	transaction_settings_controller->degree_two_isolation;
	transaction_settings_controller_copy->snapshot_isolation	=	transaction_settings_controller->snapshot_isolation;
	transaction_settings_controller_copy->enclose_db_open_in_transaction	=	transaction_settings_controller->enclose_db_open_in_transaction;
	transaction_settings_controller_copy->timeout_returns_deny_not_deadlock	=	transaction_settings_controller->timeout_returns_deny_not_deadlock;
	transaction_settings_controller_copy->sync_on_commit	=	transaction_settings_controller->sync_on_commit;
	transaction_settings_controller_copy->prohibit_sync_on_commit	=	transaction_settings_controller->prohibit_sync_on_commit;

	return transaction_settings_controller_copy;
}

