#ifndef RPBDB_LOCK_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_LOCK_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int		RPbdb_LockSettingsController_internal_openFlags(				RPbdb_LockSettingsController*		lock_settings_controller );
int		RPbdb_LockSettingsController_internal_clearDeadlocksFlags(		RPbdb_LockSettingsController*		lock_settings_controller );
int		RPbdb_LockSettingsController_internal_obtainAndReleaseFlags(	RPbdb_LockSettingsController*		lock_settings_controller );

RPbdb_LockSettingsController* RPbdb_LockSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_LockSettingsController* lock_settings_controller );

#endif

