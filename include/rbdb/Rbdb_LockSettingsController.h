/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef Rbdb_LOCK_SETTINGS_CONTROLLER
	#define Rbdb_LOCK_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_LockSettingsController*						Rbdb_LockSettingsController_new(											Rbdb_SettingsController*				settings_controller );

	void												Rbdb_LockSettingsController_free(											Rbdb_LockSettingsController**			lock_settings_controller );
	Rbdb_Environment*							Rbdb_LockSettingsController_parentEnvironment(					Rbdb_LockSettingsController*			lock_settings_controller );
														
	int												Rbdb_LockSettingsController_on(											Rbdb_LockSettingsController*			lock_settings_controller );
	BOOL												Rbdb_LockSettingsController_off(											Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_turnOn(										Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_turnOff(										Rbdb_LockSettingsController*			lock_settings_controller );
														
	int												Rbdb_LockSettingsController_prohibitLocking(								Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_turnProhibitLockingOn(							Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_turnProhibitLockingOff(						Rbdb_LockSettingsController*			lock_settings_controller );

	int												Rbdb_LockSettingsController_timeoutReturnsDenyNotDeadlock(			Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_turnTimeoutReturnsDenyNotDeadlockOn(		Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_turnTimeoutReturnsDenyNotDeadlockOff(	Rbdb_LockSettingsController*			lock_settings_controller );

	int												Rbdb_LockSettingsController_noWaitingForConflicts(							Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_turnNoWaitingForConflictsOn(					Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_turnNoWaitingForConflictsOff(					Rbdb_LockSettingsController*			lock_settings_controller );

	int												Rbdb_LockSettingsController_lockForEnvironmentNotDatabase(					Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_turnLockForEnvironmentNotDatabaseOn(			Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_turnLockForEnvironmentNotDatabaseOff(			Rbdb_LockSettingsController*			lock_settings_controller );

	int													Rbdb_LockSettingsController_timeout(										Rbdb_LockSettingsController*			lock_settings_controller );
void Rbdb_LockSettingsController_setTimeout(	Rbdb_LockSettingsController* lock_settings_controller,
											 uint32_t	timeout );

	uint8_t*											Rbdb_LockSettingsController_conflictMatrix(								Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_setConflictMatrix(								Rbdb_LockSettingsController*			lock_settings_controller,
																																	uint8_t*								conflict_matrix );
	int													Rbdb_LockSettingsController_maxLockers(									Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_setMaxLockers(									Rbdb_LockSettingsController*			lock_settings_controller, uint32_t max_lockers );

	int													Rbdb_LockSettingsController_maxLocks(										Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_setMaxLocks(									Rbdb_LockSettingsController*			lock_settings_controller, uint32_t max_locks );

	int													Rbdb_LockSettingsController_maxObjects(									Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_setMaxObjects(									Rbdb_LockSettingsController*			lock_settings_controller, uint32_t max_objects );

	int													Rbdb_LockSettingsController_numberOfPartitions(							Rbdb_LockSettingsController*			lock_settings_controller );
	void												Rbdb_LockSettingsController_setNumberOfPartitions(							Rbdb_LockSettingsController*			lock_settings_controller, uint32_t partitions );

	Rbdb_LockDeadlockDetectorSettingsController*		Rbdb_LockSettingsController_deadlockDetectorSettingsController(					Rbdb_LockSettingsController*			lock_settings_controller );

#endif

