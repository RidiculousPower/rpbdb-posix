#ifndef RPDB_LOCK_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_LOCK_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int		RPDB_LockSettingsController_internal_openFlags(				RPDB_LockSettingsController*		lock_settings_controller );
int		RPDB_LockSettingsController_internal_clearDeadlocksFlags(		RPDB_LockSettingsController*		lock_settings_controller );
int		RPDB_LockSettingsController_internal_obtainAndReleaseFlags(	RPDB_LockSettingsController*		lock_settings_controller );

RPDB_LockSettingsController* RPDB_LockSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_LockSettingsController* lock_settings_controller );

#endif

