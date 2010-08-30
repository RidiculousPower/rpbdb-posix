#ifndef RPDB_LOG_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_LOG_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int			RPDB_LogSettingsController_internal_config(				RPDB_LogSettingsController*		log_settings_controller, 
																		uint32_t							which_flag );
void		RPDB_LogSettingsController_internal_setConfig(				RPDB_LogSettingsController*		log_settings_controller, 
																		uint32_t							which_flag,
																		BOOL								on_or_off );
int			RPDB_LogSettingsController_internal_openFlags(				RPDB_LogSettingsController*		log_settings_controller );
int			RPDB_LogSettingsController_internal_closeFlags(			RPDB_LogSettingsController*		log_settings_controller );
int			RPDB_LogSettingsController_internal_appendRecordFlags(		RPDB_LogSettingsController*		log_settings_controller );
void RPDB_LogSettingsController_internal_setLogConfig( RPDB_LogSettingsController* log_settings_controller );

RPDB_LogSettingsController* RPDB_LogSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_LogSettingsController* log_settings_controller );

#endif

