#ifndef RPBDB_ERROR_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_ERROR_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void RPbdb_ErrorSettingsController_internal_errorCallbackMethod(	const DB_ENV*		bdb_environment,
																	const char*			error_prefix,
																	const char*			error_message );

RPbdb_ErrorSettingsController* RPbdb_ErrorSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_ErrorSettingsController* error_settings_controller );

#endif

