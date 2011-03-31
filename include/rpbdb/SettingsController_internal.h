#ifndef RPBDB_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int RPbdb_SettingsController_internal_createFlags(	RPbdb_SettingsController* settings_controller );
int RPbdb_SettingsController_internal_eraseFlags(	RPbdb_SettingsController* settings_controller );
int RPbdb_SettingsController_internal_openFlags(	RPbdb_SettingsController* settings_controller );
int RPbdb_SettingsController_internal_closeFlags(	RPbdb_SettingsController* settings_controller );
void RPbdb_SettingsController_internal_setFlags( RPbdb_SettingsController* settings_controller );

uint32_t RPbdb_SettingsController_internal_getFlags( RPbdb_SettingsController* settings_controller );
		
RPbdb_SettingsController* RPbdb_SettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_SettingsController* settings_controller );
void RPbdb_SettingsController_internal_setVerbosity( RPbdb_SettingsController* settings_controller );

#endif

