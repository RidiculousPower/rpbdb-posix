#ifndef RPDB_ERROR_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_ERROR_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void RPDB_ErrorSettingsController_internal_errorCallbackMethod(	const DB_ENV*		bdb_environment,
																	const char*			error_prefix,
																	const char*			error_message );

RPDB_ErrorSettingsController* RPDB_ErrorSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_ErrorSettingsController* error_settings_controller );

#endif

