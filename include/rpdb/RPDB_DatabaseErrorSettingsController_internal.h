#ifndef RPDB_DATABASE_ERROR_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_ERROR_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void									RPDB_DatabaseErrorSettingsController_internal_errorCallbackMethod(					const DB_ENV*								bdb_environment,
																															const char*									error_prefix_string,
																															const char*									error_message );
RPDB_DatabaseErrorSettingsController* RPDB_DatabaseErrorSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseErrorSettingsController* database_error_settings_controller );


#endif

