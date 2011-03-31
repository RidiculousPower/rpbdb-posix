/*
 *		RPbdb::RPbdb_SettingsController::RPbdb_ConcurrentDataStoreSettingsController
 *
 *
 */

#ifndef RPBDB_TRANSACTION_SETTINGS_CONTROLLER
	#define RPBDB_TRANSACTION_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_TransactionSettingsController*													RPbdb_TransactionSettingsController_new(											RPbdb_SettingsController*										settings_controller );
	void																					RPbdb_TransactionSettingsController_free(											RPbdb_TransactionSettingsController**			transaction_settings_controller );
	RPbdb_Environment*																RPbdb_TransactionSettingsController_parentEnvironment(					RPbdb_TransactionSettingsController*	transaction_settings_controller );

	int																					RPbdb_TransactionSettingsController_on(													RPbdb_TransactionSettingsController*	transaction_settings_controller );
	BOOL																				RPbdb_TransactionSettingsController_off(												RPbdb_TransactionSettingsController*	transaction_settings_controller );
	void																				RPbdb_TransactionSettingsController_turnOn(												RPbdb_TransactionSettingsController*	transaction_settings_controller );
	void																				RPbdb_TransactionSettingsController_turnOff(											RPbdb_TransactionSettingsController*	transaction_settings_controller );
			
	int																					RPbdb_TransactionSettingsController_prohibitSyncOnWrite(							RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnProhibitSyncOnWriteTransactionOn(				RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnProhibitSyncOnWriteTransactionOff(				RPbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPbdb_TransactionSettingsController_prohibitSyncOnCommit(					RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnProhibitSyncOnCommitOn(				RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnProhibitSyncOnCommitOff(				RPbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPbdb_TransactionSettingsController_timeoutInMicrosecondsReturnsDenyNotDeadlock(	RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnTimeoutInMicrosecondsReturnsDenyNotDeadlockOn(	RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnTimeoutInMicrosecondsReturnsDenyNotDeadlockOff(	RPbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPbdb_TransactionSettingsController_concurrentDataStoreLocking(						RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnConcurrentDataStoreLockingOn(					RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnConcurrentDataStoreLockingOff(					RPbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPbdb_TransactionSettingsController_snapshotIsolation(								RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnSnapshotIsolationOn(							RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnSnapshotIsolationOff(							RPbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPbdb_TransactionSettingsController_degreeOneIsolation(								RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnDegreeOneIsolationOn(						RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnDegreeOneIsolationOff(						RPbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPbdb_TransactionSettingsController_degreeTwoIsolation(								RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnDegreeTwoIsolationOn(							RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnDegreeTwoIsolationOff(							RPbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPbdb_TransactionSettingsController_encloseAllActivityInTransaction(				RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnEncloseAllActivityInTransactionOn(			RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnEncloseAllActivityInTransactionOff(			RPbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					RPbdb_TransactionSettingsController_environmentalSnapshotIsolation(					RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnEnvironmentalSnapshotIsolationOn(			RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnEnvironmentalSnapshotIsolationOff(			RPbdb_TransactionSettingsController*							transaction_settings_controller );

	int																					RPbdb_TransactionSettingsController_syncOnCommit(									RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnSyncOnCommitOn(								RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnSyncOnCommitOff(							RPbdb_TransactionSettingsController*							transaction_settings_controller );

	int																					RPbdb_TransactionSettingsController_waitForLocks(									RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnWaitForLocksOn(								RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_turnWaitForLocksOff(							RPbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	long																					RPbdb_TransactionSettingsController_maximumNumberOfTransactionsToRecover(			RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_setMaximumNumberOfTransactionsToRecover(		RPbdb_TransactionSettingsController*							transaction_settings_controller,
																																												long															maximum_number_of_transactions_to_recover );
																																																												
	uint32_t																				RPbdb_TransactionSettingsController_timeoutInMicroseconds(							RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_setTimeoutInMicroseconds(						RPbdb_TransactionSettingsController*							transaction_settings_controller, 
																																												uint32_t														timeout_in_microseconds );
																																																												
	uint32_t																				RPbdb_TransactionSettingsController_maxOpen(										RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_setMaxOpen(										RPbdb_TransactionSettingsController*							transaction_settings_controller, 
																																												uint32_t														max_open );
																																																												
	time_t																					RPbdb_TransactionSettingsController_recoveryTimestamp(								RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_setRecoveryTimestamp(							RPbdb_TransactionSettingsController*							transaction_settings_controller, 
																																																											time_t															recovery_timestamp );
/*
	void																					RPbdb_TransactionSettingsController_setRollbackwardCallbackMethod(					RPbdb_TransactionSettingsController*							transaction_settings_controller,
																																												int (*rollbackward_callback_method)(	RPbdb_Environment*					environment,
																																																						RPbdb_Record*			transaction_log_record ) );
	int (*rollbackward_callback_method)(	RPbdb_Environment*				environment,                                                                                                                                                                	
											RPbdb_Record*		transaction_log_record )	RPbdb_TransactionSettingsController_rollbackwardCallbackMethod(						RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_setRollforwardCallbackMethod(					RPbdb_TransactionSettingsController*							transaction_settings_controller,
																																												int (*rollforward_callback_method)(		RPbdb_Environment*					environment,
																																																						RPbdb_Record*			transaction_log_record ) );
	int (*rollforward_callback_method)(	RPbdb_Environment*				environment,                                                                                        				
										RPbdb_Record*		transaction_log_record )		RPbdb_TransactionSettingsController_rollforwardCallbackMethod(						RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_setAbortCallbackMethod(							RPbdb_TransactionSettingsController* 							transaction_settings_controller,
																																												int (*abort_callback_method)(			RPbdb_Environment*					environment,
																																																						RPbdb_Record*			transaction_log_record ) );
	int (*abort_callback_method)(	RPbdb_Environment*				environment,                    	                                                                					
									RPbdb_Record*		transaction_log_record )			RPbdb_TransactionSettingsController_abortCallbackMethod(							RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_setApplyCallbackMethod(							RPbdb_TransactionSettingsController*							transaction_settings_controller,
																																												int (*apply_callback_method)(			RPbdb_Environment*					environment,
																																																						RPbdb_Record*			transaction_log_record ) );
	int (*apply_callback_method)(	RPbdb_Environment*				environment,                		                                                                					                                                    		
									RPbdb_Record*		transaction_log_record )			RPbdb_TransactionSettingsController_applyCallbackMethod(							RPbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					RPbdb_TransactionSettingsController_setPrintCallbackMethod(							RPbdb_TransactionSettingsController*							transaction_settings_controller,
																																												int (*print_callback_method)(			RPbdb_Environment*					environment,

*/
#endif

