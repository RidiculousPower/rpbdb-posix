#ifndef RBDB_DATABASE_ERROR_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_ERROR_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void									Rbdb_DatabaseErrorSettingsController_internal_errorCallbackMethod(					const DB_ENV*								bdb_environment,
																															const char*									error_prefix_string,
																															const char*									error_message );
Rbdb_DatabaseErrorSettingsController* Rbdb_DatabaseErrorSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseErrorSettingsController* database_error_settings_controller );


#endif

