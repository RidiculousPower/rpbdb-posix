/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPBDB_LOCK_SETTINGS_CONTROLLER
	#define RPBDB_LOCK_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_LockSettingsController*						RPbdb_LockSettingsController_new(											RPbdb_SettingsController*				settings_controller );

	void												RPbdb_LockSettingsController_free(											RPbdb_LockSettingsController**			lock_settings_controller );
	RPbdb_Environment*							RPbdb_LockSettingsController_parentEnvironment(					RPbdb_LockSettingsController*			lock_settings_controller );
														
	int												RPbdb_LockSettingsController_on(											RPbdb_LockSettingsController*			lock_settings_controller );
	BOOL												RPbdb_LockSettingsController_off(											RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_turnOn(										RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_turnOff(										RPbdb_LockSettingsController*			lock_settings_controller );
														
	int												RPbdb_LockSettingsController_prohibitLocking(								RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_turnProhibitLockingOn(							RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_turnProhibitLockingOff(						RPbdb_LockSettingsController*			lock_settings_controller );

	int												RPbdb_LockSettingsController_timeoutReturnsDenyNotDeadlock(			RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_turnTimeoutReturnsDenyNotDeadlockOn(		RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_turnTimeoutReturnsDenyNotDeadlockOff(	RPbdb_LockSettingsController*			lock_settings_controller );

	int												RPbdb_LockSettingsController_noWaitingForConflicts(							RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_turnNoWaitingForConflictsOn(					RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_turnNoWaitingForConflictsOff(					RPbdb_LockSettingsController*			lock_settings_controller );

	int												RPbdb_LockSettingsController_lockForEnvironmentNotDatabase(					RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_turnLockForEnvironmentNotDatabaseOn(			RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_turnLockForEnvironmentNotDatabaseOff(			RPbdb_LockSettingsController*			lock_settings_controller );

	int													RPbdb_LockSettingsController_timeout(										RPbdb_LockSettingsController*			lock_settings_controller );
void RPbdb_LockSettingsController_setTimeout(	RPbdb_LockSettingsController* lock_settings_controller,
											 uint32_t	timeout );

	uint8_t*											RPbdb_LockSettingsController_conflictMatrix(								RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_setConflictMatrix(								RPbdb_LockSettingsController*			lock_settings_controller,
																																	uint8_t*								conflict_matrix );
	int													RPbdb_LockSettingsController_maxLockers(									RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_setMaxLockers(									RPbdb_LockSettingsController*			lock_settings_controller, uint32_t max_lockers );

	int													RPbdb_LockSettingsController_maxLocks(										RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_setMaxLocks(									RPbdb_LockSettingsController*			lock_settings_controller, uint32_t max_locks );

	int													RPbdb_LockSettingsController_maxObjects(									RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_setMaxObjects(									RPbdb_LockSettingsController*			lock_settings_controller, uint32_t max_objects );

	int													RPbdb_LockSettingsController_numberOfPartitions(							RPbdb_LockSettingsController*			lock_settings_controller );
	void												RPbdb_LockSettingsController_setNumberOfPartitions(							RPbdb_LockSettingsController*			lock_settings_controller, uint32_t partitions );

	RPbdb_LockDeadlockDetectorSettingsController*		RPbdb_LockSettingsController_deadlockDetectorSettingsController(					RPbdb_LockSettingsController*			lock_settings_controller );

#endif

