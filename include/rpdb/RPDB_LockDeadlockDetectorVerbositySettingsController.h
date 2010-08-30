/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPDB_LOCK_DEADLOCK_DETECTOR_VERBOSITY_SETTINGS_CONTROLLER
	#define RPDB_LOCK_DEADLOCK_DETECTOR_VERBOSITY_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_LockDeadlockDetectorVerbositySettingsController*	RPDB_LockDeadlockDetectorVerbositySettingsController_new(																RPDB_LockDeadlockDetectorSettingsController*				parent_lock_deadlock_detector_settings_controller );

	void													RPDB_LockDeadlockDetectorVerbositySettingsController_free(																RPDB_LockDeadlockDetectorVerbositySettingsController** lock_deadlock_detector_verbosity_settings_controller );
	RPDB_Environment*								RPDB_LockDeadlockDetectorVerbositySettingsController_parentEnvironment(									RPDB_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller );

	BOOL													RPDB_LockDeadlockDetectorVerbositySettingsController_displayAdditionalInformationDuringDeadlockDetection(				RPDB_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );
	void													RPDB_LockDeadlockDetectorVerbositySettingsController_turnDisplayAdditionalInformationDuringDeadlockDetectionOn(		RPDB_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );
	void													RPDB_LockDeadlockDetectorVerbositySettingsController_turnDisplayAdditionalInformationDuringDeadlockDetectionOff(		RPDB_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );

	BOOL													RPDB_LockDeadlockDetectorVerbositySettingsController_displayWaitTableDuringDeadlockDetection(							RPDB_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );
	void													RPDB_LockDeadlockDetectorVerbositySettingsController_turnDisplayWaitTableDuringDeadlockDetectionOn(					RPDB_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );
	void													RPDB_LockDeadlockDetectorVerbositySettingsController_turnDisplayWaitTableDuringDeadlockDetectionOff(					RPDB_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller );

#endif

