/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef Rbdb_LOCK_DEADLOCK_DETECTOR_VERBOSITY_SETTINGS_CONTROLLER
	#define Rbdb_LOCK_DEADLOCK_DETECTOR_VERBOSITY_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_LockDeadlockDetectorVerbositySettingsController*	Rbdb_LockDeadlockDetectorVerbositySettingsController_new(																Rbdb_LockDeadlockDetectorSettingsController*				parent_lock_deadlock_detector_settings_controller );

	void													Rbdb_LockDeadlockDetectorVerbositySettingsController_free(																Rbdb_LockDeadlockDetectorVerbositySettingsController** lock_deadlock_detector_verbosity_settings_controller );
	Rbdb_Environment*								Rbdb_LockDeadlockDetectorVerbositySettingsController_parentEnvironment(									Rbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller );

	BOOL													Rbdb_LockDeadlockDetectorVerbositySettingsController_displayAdditionalInformationDuringDeadlockDetection(				Rbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );
	void													Rbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayAdditionalInformationDuringDeadlockDetectionOn(		Rbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );
	void													Rbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayAdditionalInformationDuringDeadlockDetectionOff(		Rbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );

	BOOL													Rbdb_LockDeadlockDetectorVerbositySettingsController_displayWaitTableDuringDeadlockDetection(							Rbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );
	void													Rbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayWaitTableDuringDeadlockDetectionOn(					Rbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );
	void													Rbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayWaitTableDuringDeadlockDetectionOff(					Rbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );

#endif

