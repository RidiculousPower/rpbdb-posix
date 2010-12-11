#ifndef RBDB_ERROR_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_ERROR_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void Rbdb_ErrorSettingsController_internal_errorCallbackMethod(	const DB_ENV*		bdb_environment,
																	const char*			error_prefix,
																	const char*			error_message );

Rbdb_ErrorSettingsController* Rbdb_ErrorSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_ErrorSettingsController* error_settings_controller );

#endif

