#ifndef Rbdb_LOCK_DEADLOCK_DETECTOR_SETTINGS_CONTROLLER_INTERNAL
	#define Rbdb_LOCK_DEADLOCK_DETECTOR_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void	Rbdb_LockDeadlockDetectorSettingsController_internal_set(			Rbdb_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller );
BOOL		Rbdb_LockDeadlockDetectorSettingsController_internal_isSetTo(		Rbdb_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller,
 																			uint32_t										deadlock_settings );
void	Rbdb_LockDeadlockDetectorSettingsController_internal_setTo(		Rbdb_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller, 
																			uint32_t										deadlock_settings );

Rbdb_LockDeadlockDetectorSettingsController* Rbdb_LockDeadlockDetectorSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller );

#endif

