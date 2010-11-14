/*
 *		RPDB::RPDB_SettingsController::RPDB_ConcurrentDataStoreSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_TransactionSettingsController.h"

#include "RPDB_Environment.h"
#include "RPDB_TransactionSettingsController.h"
#include "RPDB_RuntimeStorageController.h"
#include "RPDB_Record.h"
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

RPDB_TransactionSettingsController* RPDB_TransactionSettingsController_new( RPDB_SettingsController* settings_controller )	{

	RPDB_TransactionSettingsController*		transaction_settings_controller = calloc( 1, sizeof( RPDB_TransactionSettingsController ) );

	transaction_settings_controller->parent_settings_controller = settings_controller;
	
	//	We set callbacks for individual events, so transaction recovery callback method should always be enabled
	//	However, no events are set before the TransactionSettingsController is created, so we can set the callback here,
	//	at least as long as the environment has not been opened
	/*
	if (	RPDB_Environment_isOpen( environment ) == FALSE 
		&&	environment->wrapped_bdb_database != NULL )	{

		environment->wrapped_bdb_environment->wrapped_bdb_environment->wrapped_bdb_environment->set_app_dispatch(	environment->wrapped_bdb_environment->wrapped_bdb_environment->wrapped_bdb_environment, 
																& RPDB_TransactionSettingsController_internal_transactionRecoveryCallbackMethod );
	}
	*/
	
	return transaction_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_TransactionSettingsController_free(	RPDB_TransactionSettingsController** transaction_settings_controller )	{

	free( *transaction_settings_controller );
	*transaction_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_TransactionSettingsController_parentEnvironment(	RPDB_TransactionSettingsController* transaction_settings_controller )	{
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
int RPDB_TransactionSettingsController_on( RPDB_TransactionSettingsController* transaction_settings_controller )	{
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
BOOL RPDB_TransactionSettingsController_off( RPDB_TransactionSettingsController* transaction_settings_controller )	{
	if ( transaction_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

	/**************
	*  turnOn  *
	**************/

	//	DB_INIT_TXN             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_TransactionSettingsController_turnOn( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->on = TRUE;
	}

	/**************
	*  turnOff  *
	**************/

	//	DB_INIT_TXN             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	//	Returns DB_INIT_TXN or FALSE
	void RPDB_TransactionSettingsController_turnOff( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->on = FALSE;
	}

/*****************************
*  prohibitSyncOnWrite  *
*****************************/

//	DB_TXN_WRITE_NOSYNC     http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPDB_TransactionSettingsController_prohibitSyncOnWrite( RPDB_TransactionSettingsController* transaction_settings_controller )	{
	if ( transaction_settings_controller->prohibit_sync_on_write == TRUE )	{
		return DB_TXN_WRITE_NOSYNC;
	}
	return FALSE;
}

	/********************************
	*  prohibitSyncOnWriteOn  *
	********************************/

	//	DB_TXN_WRITE_NOSYNC     http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_TransactionSettingsController_turnProhibitSyncOnWriteTransactionOn( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->prohibit_sync_on_write = TRUE;
	}
	
	/********************************
	*  prohibitSyncOnWriteOff  *
	********************************/

	//	DB_TXN_WRITE_NOSYNC     http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_TransactionSettingsController_turnProhibitSyncOnWriteTransactionOff( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->prohibit_sync_on_write = FALSE;
	}
	
/********************************************
*  prohibitSyncOnCommitTransaction  *
********************************************/

//	DB_TXN_NOSYNC           http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPDB_TransactionSettingsController_prohibitSyncOnCommit( RPDB_TransactionSettingsController* transaction_settings_controller )	{
	if ( transaction_settings_controller->prohibit_sync_on_commit == TRUE )	{
		return DB_TXN_NOSYNC;
	}
	return FALSE;
}

	/********************************************
	*  prohibitSyncOnCommitTransactionOn  *
	********************************************/

	//	DB_TXN_NOSYNC           http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_TransactionSettingsController_turnProhibitSyncOnCommitOn( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->prohibit_sync_on_commit = TRUE;
		RPDB_TransactionSettingsController_turnSyncOnCommitOff( transaction_settings_controller );
	}

	/********************************************
	*  prohibitSyncOnCommitTransactionOff  *
	********************************************/

	//	DB_TXN_NOSYNC           http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_TransactionSettingsController_turnProhibitSyncOnCommitOff( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->prohibit_sync_on_commit = FALSE;
	}

/****************************************
*  timeoutReturnsDenyNotDeadlock  *
****************************************/

//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPDB_TransactionSettingsController_timeoutInMicrosecondsReturnsDenyNotDeadlock( RPDB_TransactionSettingsController* transaction_settings_controller )	{
	if ( transaction_settings_controller->timeout_returns_deny_not_deadlock == TRUE )	{
		return DB_TIME_NOTGRANTED;	
	}
	return FALSE;
}

	/********************************************
	*  timeoutReturnsDenyNotDeadlockOn  *
	********************************************/

	//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_TransactionSettingsController_turnTimeoutInMicrosecondsReturnsDenyNotDeadlockOn( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->timeout_returns_deny_not_deadlock = TRUE;
	}

	/********************************************
	*  timeoutReturnsDenyNotDeadlockOff  *
	********************************************/

	//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_TransactionSettingsController_turnTimeoutInMicrosecondsReturnsDenyNotDeadlockOff( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->timeout_returns_deny_not_deadlock = FALSE;
	}

/************************************
*  concurrentDataStoreLocking  *
************************************/

//	DB_INIT_CDB - 			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
//	only other flag allowed concurrently is DB_INIT_MPOOL; multiple reader single write mode
int RPDB_TransactionSettingsController_concurrentDataStoreLocking( RPDB_TransactionSettingsController*							transaction_settings_controller )	{
	if ( transaction_settings_controller->concurrent_data_store_locking == TRUE )	{
		return DB_INIT_CDB;
	}
	return FALSE;
}

	/************************************
	*  concurrentDataStoreLockingOn  *
	************************************/

	void RPDB_TransactionSettingsController_turnConcurrentDataStoreLockingOn( RPDB_TransactionSettingsController*							transaction_settings_controller )	{
		transaction_settings_controller->concurrent_data_store_locking = TRUE;
	}

	/****************************************
	*  concurrentDataStoreLockingOff  *
	****************************************/

	void RPDB_TransactionSettingsController_turnConcurrentDataStoreLockingOff( RPDB_TransactionSettingsController*							transaction_settings_controller )	{
		transaction_settings_controller->concurrent_data_store_locking = FALSE;
	}

/****************************
*  snapshotIsolation  *
****************************/

//	DB_TXN_SNAPSHOT         http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
//	DB_TXN_SNAPSHOT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
int RPDB_TransactionSettingsController_snapshotIsolation( RPDB_TransactionSettingsController* transaction_settings_controller )	{

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
	void RPDB_TransactionSettingsController_turnSnapshotIsolationOn( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->snapshot_isolation = TRUE;
	}

	/********************************
	*  snapshotIsolationOff  *
	********************************/

	//	DB_TXN_SNAPSHOT         http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	//	DB_TXN_SNAPSHOT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
	void RPDB_TransactionSettingsController_turnSnapshotIsolationOff( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->snapshot_isolation = FALSE;
	}

/************************************
*  degreeOneIsolation  *
************************************/

//	DB_READ_UNCOMMITTED		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
//	This should also make sure that the ThreadSettingsController flag was on with the DB Open
//	http://www.oracle.com/technology/documentation/berkeley-db/db/ref/transapp/read.html
int RPDB_TransactionSettingsController_degreeOneIsolation( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->degree_one_isolation == TRUE )	{
		return DB_READ_UNCOMMITTED;
	}

	return FALSE;
}

	/****************************************
	*  turnDegreeOneIsolationOn  *
	****************************************/

	void RPDB_TransactionSettingsController_turnDegreeOneIsolationOn( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->degree_one_isolation = TRUE;
	}

	/****************************************
	*  turnDegreeOneIsolationOff  *
	****************************************/

	void RPDB_TransactionSettingsController_turnDegreeOneIsolationOff( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->degree_one_isolation = FALSE;
	}

/****************************
*  degreeTwoIsolation  *
****************************/

//	DB_READ_COMMITTED		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
//	http://www.oracle.com/technology/documentation/berkeley-db/db/ref/transapp/read.html
int RPDB_TransactionSettingsController_degreeTwoIsolation( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->degree_two_isolation == TRUE )	{
		return DB_READ_COMMITTED;
	}
	return FALSE;
}

	/****************************
	*  degreeTwoIsolationOn  *
	****************************/

	void RPDB_TransactionSettingsController_turnDegreeTwoIsolationOn( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->degree_two_isolation = TRUE;
	}

	/****************************
	*  degreeTwoIsolationOff  *
	****************************/

	void RPDB_TransactionSettingsController_turnDegreeTwoIsolationOff( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->degree_two_isolation = FALSE;
	}

/**********************************************
*  encloseAllActivityInTransaction  *
**********************************************/

//	DB_AUTO_COMMIT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPDB_TransactionSettingsController_encloseAllActivityInTransaction( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->enclose_all_activity_in_transaction == TRUE )	{
		return DB_AUTO_COMMIT;	
	}
	return FALSE;
}

	/*****************************************************
	*  turnEncloseAllActivityInTransactionOn  *
	*****************************************************/

	void RPDB_TransactionSettingsController_turnEncloseAllActivityInTransactionOn( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->enclose_all_activity_in_transaction = TRUE;
	}

	/*****************************************************
	*  turnEncloseAllActivityInTransactionOff  *
	*****************************************************/

	void RPDB_TransactionSettingsController_turnEncloseAllActivityInTransactionOff( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->enclose_all_activity_in_transaction = FALSE;
	}

/******************************************
*  environmentalSnapshotIsolation  *
******************************************/

//	DB_MULTIVERSION         http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPDB_TransactionSettingsController_environmentalSnapshotIsolation( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->environmental_snapshot_isolation == TRUE )	{
		return DB_MULTIVERSION;
	}
	return FALSE;
}

	/*********************************************
	*  turnEnvironmentalSnapshotIsolationOn  *
	*********************************************/

	void RPDB_TransactionSettingsController_turnEnvironmentalSnapshotIsolationOn( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->environmental_snapshot_isolation = TRUE;
	}

	/*********************************************
	*  turnEnvironmentalSnapshotIsolationOff  *
	*********************************************/

	void RPDB_TransactionSettingsController_turnEnvironmentalSnapshotIsolationOff( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->environmental_snapshot_isolation = FALSE;
	}

/******************************************
*  syncOnCommit  *
******************************************/

//	DB_TXN_SYNC         http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_begin.html
int RPDB_TransactionSettingsController_syncOnCommit( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->sync_on_commit == TRUE )	{
		return DB_TXN_SYNC;
	}
	return FALSE;
}

	/*********************************************
	*  turnSyncOnCommitOn  *
	*********************************************/

	void RPDB_TransactionSettingsController_turnSyncOnCommitOn( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->sync_on_commit = TRUE;
	}

	/*********************************************
	*  turnSyncOnCommitOff  *
	*********************************************/

	void RPDB_TransactionSettingsController_turnSyncOnCommitOff( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->sync_on_commit = FALSE;
	}

/******************************************
*  waitForLocks  *
******************************************/

//	DB_TXN_WAIT         http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_begin.html
int RPDB_TransactionSettingsController_waitForLocks( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	if ( transaction_settings_controller->wait_for_locks == TRUE )	{
		return DB_TXN_WAIT;
	}
	return FALSE;
}

	/*********************************************
	*  turnSyncOnCommitOn  *
	*********************************************/

	void RPDB_TransactionSettingsController_turnWaitForLocksOn( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->wait_for_locks = TRUE;
	}

	/*********************************************
	*  turnSyncOnCommitOff  *
	*********************************************/

	void RPDB_TransactionSettingsController_turnWaitForLocksOff( RPDB_TransactionSettingsController* transaction_settings_controller )	{
		transaction_settings_controller->wait_for_locks = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/************************************************
*  maximumNumberOfTransactionsToRecover  *
************************************************/

long RPDB_TransactionSettingsController_maximumNumberOfTransactionsToRecover( RPDB_TransactionSettingsController* transaction_settings_controller )	{
	
	return transaction_settings_controller->maximum_number_of_transactions_to_recover;
}

/****************************************************
*  setMaximumNumberOfTransactionsToRecover  *
****************************************************/

void RPDB_TransactionSettingsController_setMaximumNumberOfTransactionsToRecover(	RPDB_TransactionSettingsController*	transaction_settings_controller,
																					long									maximum_number_of_transactions_to_recover )	{

	transaction_settings_controller->maximum_number_of_transactions_to_recover = maximum_number_of_transactions_to_recover;
}

/****************
*  timeout  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_timeout.html
uint32_t RPDB_TransactionSettingsController_timeoutInMicroseconds( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	RPDB_Environment*		environment = transaction_settings_controller->parent_settings_controller->parent_environment;

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
void RPDB_TransactionSettingsController_setTimeoutInMicroseconds(	RPDB_TransactionSettingsController*	transaction_settings_controller, 
																	uint32_t								timeout_in_microseconds )	{

	RPDB_Environment*		environment = transaction_settings_controller->parent_settings_controller->parent_environment;

	transaction_settings_controller->timeout_in_microseconds = timeout_in_microseconds;
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_timeout( environment->wrapped_bdb_environment, timeout_in_microseconds, DB_SET_TXN_TIMEOUT );
	}
}

/****************
*  maxOpen  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_tx_max.html
uint32_t RPDB_TransactionSettingsController_maxOpen( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	RPDB_Environment*		environment = transaction_settings_controller->parent_settings_controller->parent_environment;

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
void RPDB_TransactionSettingsController_setMaxOpen(	RPDB_TransactionSettingsController*	transaction_settings_controller, 
														uint32_t								max_open )	{

	RPDB_Environment*		environment = transaction_settings_controller->parent_settings_controller->parent_environment;

	transaction_settings_controller->max_open = max_open;
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_tx_max( environment->wrapped_bdb_environment, max_open );
	}
}

/********************
*  timestamp  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_tx_timestamp.html
time_t RPDB_TransactionSettingsController_recoveryTimestamp( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	RPDB_Environment*		environment = transaction_settings_controller->parent_settings_controller->parent_environment;

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
void RPDB_TransactionSettingsController_setRecoveryTimestamp(	RPDB_TransactionSettingsController*	transaction_settings_controller, 
																															time_t									recovery_timestamp )	{

	RPDB_Environment*		environment = transaction_settings_controller->parent_settings_controller->parent_environment;
	
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
void RPDB_TransactionSettingsController_setRollbackwardCallbackMethod(	RPDB_TransactionSettingsController*						transaction_settings_controller,
																		int (*rollbackward_callback_method)(	RPDB_Environment*				environment->wrapped_bdb_environment,
																												RPDB_Record*		transaction_log_record ) )	{
																													
	transaction_settings_controller->roll_backward_callback_method = roll_backward_callback_method;
}
*/
/************************************
*  rollbackwardCallbackMethod  *
************************************/
/*
int (*rollbackward_callback_method)(	RPDB_Environment*				environment->wrapped_bdb_environment,
										RPDB_Record*		transaction_log_record ) RPDB_TransactionSettingsController_rollbackwardCallbackMethod( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	return transaction_settings_controller->roll_backward_callback_method;
}
*/
/****************************************
*  setRollforwardCallbackMethod  *
****************************************/
/*
void RPDB_TransactionSettingsController_setRollforwardCallbackMethod(	RPDB_TransactionSettingsController*					transaction_settings_controller,
																		int (*rollforward_callback_method)(	RPDB_Environment*				environment->wrapped_bdb_environment,
																											RPDB_Record*		transaction_log_record ) )	{
																													
	transaction_settings_controller->roll_forward_callback_method = roll_forward_callback_method;																							
}
*/
/************************************
*  rollforwardCallbackMethod  *
************************************/
/*
int (*rollforward_callback_method)(	RPDB_Environment*				environment->wrapped_bdb_environment,
									RPDB_Record*		transaction_log_record ) RPDB_TransactionSettingsController_rollforwardCallbackMethod( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	return transaction_settings_controller->roll_forward_callback_method;
}
*/
/********************************
*  setAbortCallbackMethod  *
********************************/
/*
void RPDB_TransactionSettingsController_setAbortCallbackMethod(	RPDB_TransactionSettingsController* 						transaction_settings_controller,
																	int (*abort_callback_method)(	RPDB_Environment*						environment->wrapped_bdb_environment,
																									RPDB_Record*				transaction_log_record ) )	{
																													
	transaction_settings_controller->abort_callback_method = abort_callback_method;																							
}
*/
/********************************
*  abortCallbackMethod  *
********************************/
/*
int (*abort_callback_method)(	RPDB_Environment*				environment->wrapped_bdb_environment,
								RPDB_Record*		transaction_log_record ) RPDB_TransactionSettingsController_abortCallbackMethod( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	return transaction_settings_controller->abort_callback_method;
}
*/
/********************************
*  setApplyCallbackMethod  *
********************************/
/*
void RPDB_TransactionSettingsController_setApplyCallbackMethod(	RPDB_TransactionSettingsController*				transaction_settings_controller,
																	int (*apply_callback_method)(	RPDB_Environment*				environment->wrapped_bdb_environment,
																									RPDB_Record*		transaction_log_record ) )	{
																													
	transaction_settings_controller->apply_callback_method = apply_callback_method;																							
}
*/
/********************************
*  applyCallbackMethod  *
********************************/
/*
int (*apply_callback_method)(	RPDB_Environment*				environment->wrapped_bdb_environment,
								RPDB_Record*		transaction_log_record ) RPDB_TransactionSettingsController_applyCallbackMethod( RPDB_TransactionSettingsController* transaction_settings_controller )	{

	return transaction_settings_controller->apply_callback_method;
}
*/
/********************************
*  setPrintCallbackMethod  *
********************************/
/*
void RPDB_TransactionSettingsController_setPrintCallbackMethod(	RPDB_TransactionSettingsController*				transaction_settings_controller,
																	int (*print_callback_method)(	RPDB_Environment*				environment->wrapped_bdb_environment,
																									RPDB_Record*		transaction_log_record ) )	{
					
	transaction_settings_controller->print_callback_method = print_callback_method;																							
}
*/
/********************************
*  printCallbackMethod  *
********************************/
/*
int (*print_callback_method)(	RPDB_Environment*				environment->wrapped_bdb_environment,
								RPDB_Record*		transaction_log_record ) RPDB_TransactionSettingsController_printCallbackMethod( RPDB_TransactionSettingsController* transaction_settings_controller )	{

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
int RPDB_TransactionSettingsController_internal_transactionRecoveryCallbackMethod(	DB_ENV*			bdb_environment->wrapped_bdb_environment, 
																					DBT*			transaction_log_record, 
																					DB_LSN*			lsn, 
																					db_recops		recovery_operation )	{
	
	RPDB_Environment*									environment				= RPDB_RuntimeStorageController_environmentForBDBEnvironment( bdb_environment );
	RPDB_Record*							transaction_log_record	= RPDB_Record_newFromRawKeyDBTDataPair(	lsn,
																												transaction_log_record );

	RPDB_TransactionSettingsController*	transaction_settings_controller	=	RPDB_SettingsController_transactionSettingsController(
																					RPDB_Environment_settingsController( environment ) );

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
int RPDB_TransactionSettingsController_internal_beginFlags( RPDB_TransactionSettingsController* transaction_settings_controller )	{
	
	return RPDB_TransactionSettingsController_degreeTwoIsolation( transaction_settings_controller )
			|	RPDB_TransactionSettingsController_degreeOneIsolation( transaction_settings_controller )
			|	RPDB_TransactionSettingsController_prohibitSyncOnCommit( transaction_settings_controller )
			|	RPDB_TransactionSettingsController_waitForLocks( transaction_settings_controller )
			|	RPDB_TransactionSettingsController_snapshotIsolation( transaction_settings_controller )
			|	RPDB_TransactionSettingsController_syncOnCommit( transaction_settings_controller )
			|	RPDB_TransactionSettingsController_waitForLocks( transaction_settings_controller )
			|	RPDB_TransactionSettingsController_prohibitSyncOnWrite( transaction_settings_controller );
}

/************************
*  discardFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_discard.html
int RPDB_TransactionSettingsController_internal_discardFlags( RPDB_TransactionSettingsController* transaction_settings_controller __attribute__((unused)) )	{
	
	//	Currently unused
	return RPDB_NO_FLAGS;
}

/************************
*  commitFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_commit.html
int RPDB_TransactionSettingsController_internal_commitFlags( RPDB_TransactionSettingsController* transaction_settings_controller )	{
	
	return	RPDB_TransactionSettingsController_prohibitSyncOnCommit( transaction_settings_controller )
			|	RPDB_TransactionSettingsController_syncOnCommit( transaction_settings_controller );
}

/********************************
*  commitCheckpointFlags  *
********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_checkpoint.html
int RPDB_TransactionSettingsController_internal_commitCheckpointFlags( RPDB_TransactionSettingsController* transaction_settings_controller __attribute__((unused)) )	{
	
	//	we need to add a forceCheckpoint function instead of this flag
	//	FIX
	
	//	We have one flag - DB_FORCE - which has its own function
	//	Otherwise, we have no flags; this function is here only in the case future support of other flags becomes relevant. 
	return RPDB_NO_FLAGS;
}

/************************
*  recoverFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_recover.html
int RPDB_TransactionSettingsController_internal_recoverFlags( RPDB_TransactionSettingsController* transaction_settings_controller )	{
	
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
RPDB_TransactionSettingsController* RPDB_TransactionSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_TransactionSettingsController* transaction_settings_controller )	{

	RPDB_TransactionSettingsController* transaction_settings_controller_copy	=	RPDB_TransactionSettingsController_new( transaction_settings_controller->parent_settings_controller );

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

