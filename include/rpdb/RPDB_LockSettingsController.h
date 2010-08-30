/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPDB_LOCK_SETTINGS_CONTROLLER
	#define RPDB_LOCK_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_LockSettingsController*						RPDB_LockSettingsController_new(											RPDB_SettingsController*				settings_controller );

	void												RPDB_LockSettingsController_free(											RPDB_LockSettingsController**			lock_settings_controller );
	RPDB_Environment*							RPDB_LockSettingsController_parentEnvironment(					RPDB_LockSettingsController*			lock_settings_controller );
														
	int												RPDB_LockSettingsController_on(											RPDB_LockSettingsController*			lock_settings_controller );
	BOOL												RPDB_LockSettingsController_off(											RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_turnOn(										RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_turnOff(										RPDB_LockSettingsController*			lock_settings_controller );
														
	int												RPDB_LockSettingsController_prohibitLocking(								RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_turnProhibitLockingOn(							RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_turnProhibitLockingOff(						RPDB_LockSettingsController*			lock_settings_controller );

	int												RPDB_LockSettingsController_timeoutReturnsReturnDenyNotDeadlock(			RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_turnTimeoutReturnsReturnDenyNotDeadlockOn(		RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_turnTimeoutReturnsReturnDenyNotDeadlockOff(	RPDB_LockSettingsController*			lock_settings_controller );

	int												RPDB_LockSettingsController_noWaitingForConflicts(							RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_turnNoWaitingForConflictsOn(					RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_turnNoWaitingForConflictsOff(					RPDB_LockSettingsController*			lock_settings_controller );

	int												RPDB_LockSettingsController_lockForEnvironmentNotDatabase(					RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_turnLockForEnvironmentNotDatabaseOn(			RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_turnLockForEnvironmentNotDatabaseOff(			RPDB_LockSettingsController*			lock_settings_controller );

	int													RPDB_LockSettingsController_timeout(										RPDB_LockSettingsController*			lock_settings_controller );
void RPDB_LockSettingsController_setTimeout(	RPDB_LockSettingsController* lock_settings_controller,
											 uint32_t	timeout );

	uint8_t*											RPDB_LockSettingsController_conflictMatrix(								RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_setConflictMatrix(								RPDB_LockSettingsController*			lock_settings_controller,
																																	uint8_t*								conflict_matrix );
	int													RPDB_LockSettingsController_maxLockers(									RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_setMaxLockers(									RPDB_LockSettingsController*			lock_settings_controller, uint32_t max_lockers );

	int													RPDB_LockSettingsController_maxLocks(										RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_setMaxLocks(									RPDB_LockSettingsController*			lock_settings_controller, uint32_t max_locks );

	int													RPDB_LockSettingsController_maxObjects(									RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_setMaxObjects(									RPDB_LockSettingsController*			lock_settings_controller, uint32_t max_objects );

	int													RPDB_LockSettingsController_numberOfPartitions(							RPDB_LockSettingsController*			lock_settings_controller );
	void												RPDB_LockSettingsController_setNumberOfPartitions(							RPDB_LockSettingsController*			lock_settings_controller, uint32_t partitions );

	RPDB_LockDeadlockDetectorSettingsController*		RPDB_LockSettingsController_deadlockDetectorSettingsController(					RPDB_LockSettingsController*			lock_settings_controller );

#endif

