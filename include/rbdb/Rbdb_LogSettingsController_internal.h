#ifndef RBDB_LOG_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_LOG_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

BOOL			Rbdb_LogSettingsController_internal_config(				Rbdb_LogSettingsController*		log_settings_controller, 
																		uint32_t							which_flag );
void		Rbdb_LogSettingsController_internal_setConfig(				Rbdb_LogSettingsController*		log_settings_controller, 
																		uint32_t							which_flag,
																		BOOL								on_or_off );
int			Rbdb_LogSettingsController_internal_openFlags(				Rbdb_LogSettingsController*		log_settings_controller );
int			Rbdb_LogSettingsController_internal_closeFlags(			Rbdb_LogSettingsController*		log_settings_controller );
int			Rbdb_LogSettingsController_internal_appendRecordFlags(		Rbdb_LogSettingsController*		log_settings_controller );
void Rbdb_LogSettingsController_internal_setLogConfig( Rbdb_LogSettingsController* log_settings_controller );

Rbdb_LogSettingsController* Rbdb_LogSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_LogSettingsController* log_settings_controller );

#endif

