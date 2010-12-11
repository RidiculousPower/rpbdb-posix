#ifndef RBDB_LOCK_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_LOCK_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int		Rbdb_LockSettingsController_internal_openFlags(				Rbdb_LockSettingsController*		lock_settings_controller );
int		Rbdb_LockSettingsController_internal_clearDeadlocksFlags(		Rbdb_LockSettingsController*		lock_settings_controller );
int		Rbdb_LockSettingsController_internal_obtainAndReleaseFlags(	Rbdb_LockSettingsController*		lock_settings_controller );

Rbdb_LockSettingsController* Rbdb_LockSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_LockSettingsController* lock_settings_controller );

#endif

