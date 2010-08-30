/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPDB_LOCK_DEADLOCK_DETECTOR_SETTINGS_CONTROLLER
	#define RPDB_LOCK_DEADLOCK_DETECTOR_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_LockDeadlockDetectorSettingsController*				RPDB_LockDeadlockDetectorSettingsController_new(														RPDB_LockSettingsController*						lock_settings_controller );
	void														RPDB_LockDeadlockDetectorSettingsController_free(										RPDB_LockDeadlockDetectorSettingsController** lock_deadlock_detector_settings_controller );
	RPDB_Environment*									RPDB_LockDeadlockDetectorSettingsController_parentEnvironment(				RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller );
	BOOL														RPDB_LockDeadlockDetectorSettingsController_isDefault(									RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPDB_LockDeadlockDetectorSettingsController_setToDefault(								RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPDB_LockDeadlockDetectorSettingsController_rejectExpired(								RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPDB_LockDeadlockDetectorSettingsController_setToRejectExpired(						RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPDB_LockDeadlockDetectorSettingsController_rejectLockerWithMostLocks(					RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPDB_LockDeadlockDetectorSettingsController_setToRejectLockerWithMostLocks(			RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPDB_LockDeadlockDetectorSettingsController_rejectLockerWithMostWriteLocks(			RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPDB_LockDeadlockDetectorSettingsController_setToRejectLockerWithMostWriteLocks(		RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPDB_LockDeadlockDetectorSettingsController_rejectLockerWithFewestLocks(				RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPDB_LockDeadlockDetectorSettingsController_setToRejectLockerWithFewestLocks(			RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPDB_LockDeadlockDetectorSettingsController_rejectLockerWithFewestWriteLocks(			RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPDB_LockDeadlockDetectorSettingsController_setToRejectLockerWithFewestWriteLocks(	RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPDB_LockDeadlockDetectorSettingsController_rejectLockerWithOldestLock(				RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPDB_LockDeadlockDetectorSettingsController_setToRejectLockerWithOldestLock(			RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPDB_LockDeadlockDetectorSettingsController_rejectLockerWithYoungestLock(				RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPDB_LockDeadlockDetectorSettingsController_setToRejectLockerWithYoungestLock(		RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPDB_LockDeadlockDetectorSettingsController_rejectRandom(								RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPDB_LockDeadlockDetectorSettingsController_setToRejectRandom(						RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	RPDB_LockDeadlockDetectorVerbositySettingsController*		RPDB_LockDeadlockDetectorSettingsController_verbositySettingsController(				RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

#endif

