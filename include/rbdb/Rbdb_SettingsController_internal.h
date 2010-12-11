#ifndef RBDB_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int Rbdb_SettingsController_internal_createFlags(	Rbdb_SettingsController* settings_controller );
int Rbdb_SettingsController_internal_eraseFlags(	Rbdb_SettingsController* settings_controller );
int Rbdb_SettingsController_internal_openFlags(	Rbdb_SettingsController* settings_controller );
int Rbdb_SettingsController_internal_closeFlags(	Rbdb_SettingsController* settings_controller );
void Rbdb_SettingsController_internal_setFlags( Rbdb_SettingsController* settings_controller );

uint32_t Rbdb_SettingsController_internal_getFlags( Rbdb_SettingsController* settings_controller );
		
Rbdb_SettingsController* Rbdb_SettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_SettingsController* settings_controller );
void Rbdb_SettingsController_internal_setVerbosity( Rbdb_SettingsController* settings_controller );

#endif

