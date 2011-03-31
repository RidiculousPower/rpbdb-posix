#ifndef RPBDB_LOCK_DEADLOCK_DETECTOR_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_LOCK_DEADLOCK_DETECTOR_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void	RPbdb_LockDeadlockDetectorSettingsController_internal_set(			RPbdb_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller );
BOOL		RPbdb_LockDeadlockDetectorSettingsController_internal_isSetTo(		RPbdb_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller,
 																			uint32_t										deadlock_settings );
void	RPbdb_LockDeadlockDetectorSettingsController_internal_setTo(		RPbdb_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller, 
																			uint32_t										deadlock_settings );

RPbdb_LockDeadlockDetectorSettingsController* RPbdb_LockDeadlockDetectorSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller );

#endif

