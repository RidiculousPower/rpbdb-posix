/*
 *		RPDB::RPDB_SettingsController::RPDB_ConcurrentDataStoreSettingsController
 *
 *
 */

#ifndef RPDB_TRANSACTION_SETTINGS_CONTROLLER
	#define RPDB_TRANSACTION_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_TransactionSettingsController*													RPDB_TransactionSettingsController_new(											RPDB_SettingsController*										settings_controller );
	void																					RPDB_TransactionSettingsController_free(											RPDB_TransactionSettingsController**			transaction_settings_controller );
	RPDB_Environment*																RPDB_TransactionSettingsController_parentEnvironment(					RPDB_TransactionSettingsController*	transaction_settings_controller );

	int																					RPDB_TransactionSettingsController_on(													RPDB_TransactionSettingsController*	transaction_settings_controller );
	BOOL																				RPDB_TransactionSettingsController_off(												RPDB_TransactionSettingsController*	transaction_settings_controller );
	void																				RPDB_TransactionSettingsController_turnOn(												RPDB_TransactionSettingsController*	transaction_settings_controller );
	void																				RPDB_TransactionSettingsController_turnOff(											RPDB_TransactionSettingsController*	transaction_settings_controller );
			
	int																					RPDB_TransactionSettingsController_prohibitSyncOnWrite(							RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnProhibitSyncOnWriteTransactionOn(				RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnProhibitSyncOnWriteTransactionOff(				RPDB_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPDB_TransactionSettingsController_prohibitSyncOnCommit(					RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnProhibitSyncOnCommitOn(				RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnProhibitSyncOnCommitOff(				RPDB_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPDB_TransactionSettingsController_timeoutInMicrosecondsReturnsDenyNotDeadlock(	RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnTimeoutInMicrosecondsReturnsDenyNotDeadlockOn(	RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnTimeoutInMicrosecondsReturnsDenyNotDeadlockOff(	RPDB_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPDB_TransactionSettingsController_concurrentDataStoreLocking(						RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnConcurrentDataStoreLockingOn(					RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnConcurrentDataStoreLockingOff(					RPDB_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPDB_TransactionSettingsController_snapshotIsolation(								RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnSnapshotIsolationOn(							RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnSnapshotIsolationOff(							RPDB_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPDB_TransactionSettingsController_degreeOneIsolation(								RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnDegreeOneIsolationOn(						RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnDegreeOneIsolationOff(						RPDB_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPDB_TransactionSettingsController_degreeTwoIsolation(								RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnDegreeTwoIsolationOn(							RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnDegreeTwoIsolationOff(							RPDB_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPDB_TransactionSettingsController_encloseAllActivityInTransaction(				RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnEncloseAllActivityInTransactionOn(			RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnEncloseAllActivityInTransactionOff(			RPDB_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPDB_TransactionSettingsController_environmentalSnapshotIsolation(					RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnEnvironmentalSnapshotIsolationOn(			RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnEnvironmentalSnapshotIsolationOff(			RPDB_TransactionSettingsController*							transaction_settings_controller );

	int																					RPDB_TransactionSettingsController_syncOnCommit(									RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnSyncOnCommitOn(								RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnSyncOnCommitOff(							RPDB_TransactionSettingsController*							transaction_settings_controller );

	int																					RPDB_TransactionSettingsController_waitForLocks(									RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnWaitForLocksOn(								RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_turnWaitForLocksOff(							RPDB_TransactionSettingsController*							transaction_settings_controller );
																																																												
	long																					RPDB_TransactionSettingsController_maximumNumberOfTransactionsToRecover(			RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_setMaximumNumberOfTransactionsToRecover(		RPDB_TransactionSettingsController*							transaction_settings_controller,
																																												long															maximum_number_of_transactions_to_recover );
																																																												
	uint32_t																				RPDB_TransactionSettingsController_timeoutInMicroseconds(							RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_setTimeoutInMicroseconds(						RPDB_TransactionSettingsController*							transaction_settings_controller, 
																																												uint32_t														timeout_in_microseconds );
																																																												
	uint32_t																				RPDB_TransactionSettingsController_maxOpen(										RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_setMaxOpen(										RPDB_TransactionSettingsController*							transaction_settings_controller, 
																																												uint32_t														max_open );
																																																												
	time_t*																					RPDB_TransactionSettingsController_recoveryTimestamp(								RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_setRecoveryTimestamp(							RPDB_TransactionSettingsController*							transaction_settings_controller, 
																																												time_t*															recovery_timestamp );
/*
	void																					RPDB_TransactionSettingsController_setRollbackwardCallbackMethod(					RPDB_TransactionSettingsController*							transaction_settings_controller,
																																												int (*rollbackward_callback_method)(	RPDB_Environment*					environment,
																																																						RPDB_Record*			transaction_log_record ) );
	int (*rollbackward_callback_method)(	RPDB_Environment*				environment,                                                                                                                                                                	
											RPDB_Record*		transaction_log_record )	RPDB_TransactionSettingsController_rollbackwardCallbackMethod(						RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_setRollforwardCallbackMethod(					RPDB_TransactionSettingsController*							transaction_settings_controller,
																																												int (*rollforward_callback_method)(		RPDB_Environment*					environment,
																																																						RPDB_Record*			transaction_log_record ) );
	int (*rollforward_callback_method)(	RPDB_Environment*				environment,                                                                                        				
										RPDB_Record*		transaction_log_record )		RPDB_TransactionSettingsController_rollforwardCallbackMethod(						RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_setAbortCallbackMethod(							RPDB_TransactionSettingsController* 							transaction_settings_controller,
																																												int (*abort_callback_method)(			RPDB_Environment*					environment,
																																																						RPDB_Record*			transaction_log_record ) );
	int (*abort_callback_method)(	RPDB_Environment*				environment,                    	                                                                					
									RPDB_Record*		transaction_log_record )			RPDB_TransactionSettingsController_abortCallbackMethod(							RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_setApplyCallbackMethod(							RPDB_TransactionSettingsController*							transaction_settings_controller,
																																												int (*apply_callback_method)(			RPDB_Environment*					environment,
																																																						RPDB_Record*			transaction_log_record ) );
	int (*apply_callback_method)(	RPDB_Environment*				environment,                		                                                                					                                                    		
									RPDB_Record*		transaction_log_record )			RPDB_TransactionSettingsController_applyCallbackMethod(							RPDB_TransactionSettingsController*							transaction_settings_controller );
	void																					RPDB_TransactionSettingsController_setPrintCallbackMethod(							RPDB_TransactionSettingsController*							transaction_settings_controller,
																																												int (*print_callback_method)(			RPDB_Environment*					environment,

*/
#endif

