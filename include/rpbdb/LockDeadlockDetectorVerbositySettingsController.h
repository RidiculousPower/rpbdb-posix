/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPBDB_LOCK_DEADLOCK_DETECTOR_VERBOSITY_SETTINGS_CONTROLLER
	#define RPBDB_LOCK_DEADLOCK_DETECTOR_VERBOSITY_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_LockDeadlockDetectorVerbositySettingsController*	RPbdb_LockDeadlockDetectorVerbositySettingsController_new(																RPbdb_LockDeadlockDetectorSettingsController*				parent_lock_deadlock_detector_settings_controller );

	void													RPbdb_LockDeadlockDetectorVerbositySettingsController_free(																RPbdb_LockDeadlockDetectorVerbositySettingsController** lock_deadlock_detector_verbosity_settings_controller );
	RPbdb_Environment*								RPbdb_LockDeadlockDetectorVerbositySettingsController_parentEnvironment(									RPbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller );

	BOOL													RPbdb_LockDeadlockDetectorVerbositySettingsController_displayAdditionalInformationDuringDeadlockDetection(				RPbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );
	void													RPbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayAdditionalInformationDuringDeadlockDetectionOn(		RPbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );
	void													RPbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayAdditionalInformationDuringDeadlockDetectionOff(		RPbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );

	BOOL													RPbdb_LockDeadlockDetectorVerbositySettingsController_displayWaitTableDuringDeadlockDetection(							RPbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );
	void													RPbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayWaitTableDuringDeadlockDetectionOn(					RPbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );
	void													RPbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayWaitTableDuringDeadlockDetectionOff(					RPbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );

#endif

