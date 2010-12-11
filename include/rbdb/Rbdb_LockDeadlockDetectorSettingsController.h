/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RBDB_LOCK_DEADLOCK_DETECTOR_SETTINGS_CONTROLLER
	#define RBDB_LOCK_DEADLOCK_DETECTOR_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_LockDeadlockDetectorSettingsController*				Rbdb_LockDeadlockDetectorSettingsController_new(														Rbdb_LockSettingsController*						lock_settings_controller );
	void														Rbdb_LockDeadlockDetectorSettingsController_free(										Rbdb_LockDeadlockDetectorSettingsController** lock_deadlock_detector_settings_controller );
	Rbdb_Environment*									Rbdb_LockDeadlockDetectorSettingsController_parentEnvironment(				Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller );
	BOOL														Rbdb_LockDeadlockDetectorSettingsController_isDefault(									Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														Rbdb_LockDeadlockDetectorSettingsController_setToDefault(								Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														Rbdb_LockDeadlockDetectorSettingsController_rejectExpired(								Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														Rbdb_LockDeadlockDetectorSettingsController_setToRejectExpired(						Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														Rbdb_LockDeadlockDetectorSettingsController_rejectLockerWithMostLocks(					Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														Rbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithMostLocks(			Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														Rbdb_LockDeadlockDetectorSettingsController_rejectLockerWithMostWriteLocks(			Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														Rbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithMostWriteLocks(		Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														Rbdb_LockDeadlockDetectorSettingsController_rejectLockerWithFewestLocks(				Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														Rbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithFewestLocks(			Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														Rbdb_LockDeadlockDetectorSettingsController_rejectLockerWithFewestWriteLocks(			Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														Rbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithFewestWriteLocks(	Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														Rbdb_LockDeadlockDetectorSettingsController_rejectLockerWithOldestLock(				Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														Rbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithOldestLock(			Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														Rbdb_LockDeadlockDetectorSettingsController_rejectLockerWithYoungestLock(				Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														Rbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithYoungestLock(		Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	BOOL														Rbdb_LockDeadlockDetectorSettingsController_rejectRandom(								Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );
	void														Rbdb_LockDeadlockDetectorSettingsController_setToRejectRandom(						Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

	Rbdb_LockDeadlockDetectorVerbositySettingsController*		Rbdb_LockDeadlockDetectorSettingsController_verbositySettingsController(				Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller );

#endif

