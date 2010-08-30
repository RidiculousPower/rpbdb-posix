#ifndef RPDB_LOCK_DEADLOCK_DETECTOR_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_LOCK_DEADLOCK_DETECTOR_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void	RPDB_LockDeadlockDetectorSettingsController_internal_set(			RPDB_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller );
BOOL		RPDB_LockDeadlockDetectorSettingsController_internal_isSetTo(		RPDB_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller,
 																			uint32_t										deadlock_settings );
void	RPDB_LockDeadlockDetectorSettingsController_internal_setTo(		RPDB_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller, 
																			uint32_t										deadlock_settings );

RPDB_LockDeadlockDetectorSettingsController* RPDB_LockDeadlockDetectorSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller );

#endif

