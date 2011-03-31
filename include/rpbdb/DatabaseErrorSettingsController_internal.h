#ifndef RPBDB_DATABASE_ERROR_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_ERROR_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void									RPbdb_DatabaseErrorSettingsController_internal_errorCallbackMethod(					const DB_ENV*								bdb_environment,
																															const char*									error_prefix_string,
																															const char*									error_message );
RPbdb_DatabaseErrorSettingsController* RPbdb_DatabaseErrorSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseErrorSettingsController* database_error_settings_controller );


#endif

