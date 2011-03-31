#ifndef RPBDB_LOG_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_LOG_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

BOOL			RPbdb_LogSettingsController_internal_config(				RPbdb_LogSettingsController*		log_settings_controller, 
																		uint32_t							which_flag );
void		RPbdb_LogSettingsController_internal_setConfig(				RPbdb_LogSettingsController*		log_settings_controller, 
																		uint32_t							which_flag,
																		BOOL								on_or_off );
int			RPbdb_LogSettingsController_internal_openFlags(				RPbdb_LogSettingsController*		log_settings_controller );
int			RPbdb_LogSettingsController_internal_closeFlags(			RPbdb_LogSettingsController*		log_settings_controller );
int			RPbdb_LogSettingsController_internal_appendRecordFlags(		RPbdb_LogSettingsController*		log_settings_controller );
void RPbdb_LogSettingsController_internal_setLogConfig( RPbdb_LogSettingsController* log_settings_controller );

RPbdb_LogSettingsController* RPbdb_LogSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_LogSettingsController* log_settings_controller );

#endif

