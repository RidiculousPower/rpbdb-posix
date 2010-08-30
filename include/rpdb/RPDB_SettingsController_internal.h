#ifndef RPDB_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int RPDB_SettingsController_internal_createFlags(	RPDB_SettingsController* settings_controller );
int RPDB_SettingsController_internal_eraseFlags(	RPDB_SettingsController* settings_controller );
int RPDB_SettingsController_internal_openFlags(	RPDB_SettingsController* settings_controller );
int RPDB_SettingsController_internal_closeFlags(	RPDB_SettingsController* settings_controller );
void RPDB_SettingsController_internal_setFlags( RPDB_SettingsController* settings_controller );

uint32_t RPDB_SettingsController_internal_getFlags( RPDB_SettingsController* settings_controller );
		
RPDB_SettingsController* RPDB_SettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_SettingsController* settings_controller );
void RPDB_SettingsController_internal_setVerbosity( RPDB_SettingsController* settings_controller );

#endif

