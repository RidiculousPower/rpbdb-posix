/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPBDB_LOCK_DEADLOCK_DETECTOR_SETTINGS_CONTROLLER
	#define RPBDB_LOCK_DEADLOCK_DETECTOR_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_LockDeadlockDetectorSettingsController*				RPbdb_LockDeadlockDetectorSettingsController_new(														RPbdb_LockSettingsController*						lock_settings_controller );
	void														RPbdb_LockDeadlockDetectorSettingsController_free(										RPbdb_LockDeadlockDetectorSettingsController** lock_deadlock_detector_settings_controller );
	RPbdb_Environment*									RPbdb_LockDeadlockDetectorSettingsController_parentEnvironment(				RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller );
	BOOL														RPbdb_LockDeadlockDetectorSettingsController_isDefault(									RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPbdb_LockDeadlockDetectorSettingsController_setToDefault(								RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPbdb_LockDeadlockDetectorSettingsController_rejectExpired(								RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPbdb_LockDeadlockDetectorSettingsController_setToRejectExpired(						RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPbdb_LockDeadlockDetectorSettingsController_rejectLockerWithMostLocks(					RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithMostLocks(			RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPbdb_LockDeadlockDetectorSettingsController_rejectLockerWithMostWriteLocks(			RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithMostWriteLocks(		RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPbdb_LockDeadlockDetectorSettingsController_rejectLockerWithFewestLocks(				RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithFewestLocks(			RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPbdb_LockDeadlockDetectorSettingsController_rejectLockerWithFewestWriteLocks(			RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithFewestWriteLocks(	RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPbdb_LockDeadlockDetectorSettingsController_rejectLockerWithOldestLock(				RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithOldestLock(			RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPbdb_LockDeadlockDetectorSettingsController_rejectLockerWithYoungestLock(				RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithYoungestLock(		RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														RPbdb_LockDeadlockDetectorSettingsController_rejectRandom(								RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														RPbdb_LockDeadlockDetectorSettingsController_setToRejectRandom(						RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	RPbdb_LockDeadlockDetectorVerbositySettingsController*		RPbdb_LockDeadlockDetectorSettingsController_verbositySettingsController(				RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

#endif

