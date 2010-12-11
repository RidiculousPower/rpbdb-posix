/*
 *		Rbdb::Rbdb_SettingsController::Rbdb_ConcurrentDataStoreSettingsController
 *
 *
 */

#ifndef RBDB_TRANSACTION_SETTINGS_CONTROLLER
	#define RBDB_TRANSACTION_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_TransactionSettingsController*													Rbdb_TransactionSettingsController_new(											Rbdb_SettingsController*										settings_controller );
	void																					Rbdb_TransactionSettingsController_free(											Rbdb_TransactionSettingsController**			transaction_settings_controller );
	Rbdb_Environment*																Rbdb_TransactionSettingsController_parentEnvironment(					Rbdb_TransactionSettingsController*	transaction_settings_controller );

	int																					Rbdb_TransactionSettingsController_on(													Rbdb_TransactionSettingsController*	transaction_settings_controller );
	BOOL																				Rbdb_TransactionSettingsController_off(												Rbdb_TransactionSettingsController*	transaction_settings_controller );
	void																				Rbdb_TransactionSettingsController_turnOn(												Rbdb_TransactionSettingsController*	transaction_settings_controller );
	void																				Rbdb_TransactionSettingsController_turnOff(											Rbdb_TransactionSettingsController*	transaction_settings_controller );
			
	int																					Rbdb_TransactionSettingsController_prohibitSyncOnWrite(							Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnProhibitSyncOnWriteTransactionOn(				Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnProhibitSyncOnWriteTransactionOff(				Rbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					Rbdb_TransactionSettingsController_prohibitSyncOnCommit(					Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnProhibitSyncOnCommitOn(				Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnProhibitSyncOnCommitOff(				Rbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					Rbdb_TransactionSettingsController_timeoutInMicrosecondsReturnsDenyNotDeadlock(	Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnTimeoutInMicrosecondsReturnsDenyNotDeadlockOn(	Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnTimeoutInMicrosecondsReturnsDenyNotDeadlockOff(	Rbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					Rbdb_TransactionSettingsController_concurrentDataStoreLocking(						Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnConcurrentDataStoreLockingOn(					Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnConcurrentDataStoreLockingOff(					Rbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					Rbdb_TransactionSettingsController_snapshotIsolation(								Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnSnapshotIsolationOn(							Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnSnapshotIsolationOff(							Rbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					Rbdb_TransactionSettingsController_degreeOneIsolation(								Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnDegreeOneIsolationOn(						Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnDegreeOneIsolationOff(						Rbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					Rbdb_TransactionSettingsController_degreeTwoIsolation(								Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnDegreeTwoIsolationOn(							Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnDegreeTwoIsolationOff(							Rbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					Rbdb_TransactionSettingsController_encloseAllActivityInTransaction(				Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnEncloseAllActivityInTransactionOn(			Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnEncloseAllActivityInTransactionOff(			Rbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	int																					Rbdb_TransactionSettingsController_environmentalSnapshotIsolation(					Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnEnvironmentalSnapshotIsolationOn(			Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnEnvironmentalSnapshotIsolationOff(			Rbdb_TransactionSettingsController*							transaction_settings_controller );

	int																					Rbdb_TransactionSettingsController_syncOnCommit(									Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnSyncOnCommitOn(								Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnSyncOnCommitOff(							Rbdb_TransactionSettingsController*							transaction_settings_controller );

	int																					Rbdb_TransactionSettingsController_waitForLocks(									Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnWaitForLocksOn(								Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_turnWaitForLocksOff(							Rbdb_TransactionSettingsController*							transaction_settings_controller );
																																																												
	long																					Rbdb_TransactionSettingsController_maximumNumberOfTransactionsToRecover(			Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_setMaximumNumberOfTransactionsToRecover(		Rbdb_TransactionSettingsController*							transaction_settings_controller,
																																												long															maximum_number_of_transactions_to_recover );
																																																												
	uint32_t																				Rbdb_TransactionSettingsController_timeoutInMicroseconds(							Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_setTimeoutInMicroseconds(						Rbdb_TransactionSettingsController*							transaction_settings_controller, 
																																												uint32_t														timeout_in_microseconds );
																																																												
	uint32_t																				Rbdb_TransactionSettingsController_maxOpen(										Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_setMaxOpen(										Rbdb_TransactionSettingsController*							transaction_settings_controller, 
																																												uint32_t														max_open );
																																																												
	time_t																					Rbdb_TransactionSettingsController_recoveryTimestamp(								Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_setRecoveryTimestamp(							Rbdb_TransactionSettingsController*							transaction_settings_controller, 
																																																											time_t															recovery_timestamp );
/*
	void																					Rbdb_TransactionSettingsController_setRollbackwardCallbackMethod(					Rbdb_TransactionSettingsController*							transaction_settings_controller,
																																												int (*rollbackward_callback_method)(	Rbdb_Environment*					environment,
																																																						Rbdb_Record*			transaction_log_record ) );
	int (*rollbackward_callback_method)(	Rbdb_Environment*				environment,                                                                                                                                                                	
											Rbdb_Record*		transaction_log_record )	Rbdb_TransactionSettingsController_rollbackwardCallbackMethod(						Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_setRollforwardCallbackMethod(					Rbdb_TransactionSettingsController*							transaction_settings_controller,
																																												int (*rollforward_callback_method)(		Rbdb_Environment*					environment,
																																																						Rbdb_Record*			transaction_log_record ) );
	int (*rollforward_callback_method)(	Rbdb_Environment*				environment,                                                                                        				
										Rbdb_Record*		transaction_log_record )		Rbdb_TransactionSettingsController_rollforwardCallbackMethod(						Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_setAbortCallbackMethod(							Rbdb_TransactionSettingsController* 							transaction_settings_controller,
																																												int (*abort_callback_method)(			Rbdb_Environment*					environment,
																																																						Rbdb_Record*			transaction_log_record ) );
	int (*abort_callback_method)(	Rbdb_Environment*				environment,                    	                                                                					
									Rbdb_Record*		transaction_log_record )			Rbdb_TransactionSettingsController_abortCallbackMethod(							Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_setApplyCallbackMethod(							Rbdb_TransactionSettingsController*							transaction_settings_controller,
																																												int (*apply_callback_method)(			Rbdb_Environment*					environment,
																																																						Rbdb_Record*			transaction_log_record ) );
	int (*apply_callback_method)(	Rbdb_Environment*				environment,                		                                                                					                                                    		
									Rbdb_Record*		transaction_log_record )			Rbdb_TransactionSettingsController_applyCallbackMethod(							Rbdb_TransactionSettingsController*							transaction_settings_controller );
	void																					Rbdb_TransactionSettingsController_setPrintCallbackMethod(							Rbdb_TransactionSettingsController*							transaction_settings_controller,
																																												int (*print_callback_method)(			Rbdb_Environment*					environment,

*/
#endif

