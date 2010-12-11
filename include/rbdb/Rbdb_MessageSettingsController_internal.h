#ifndef RBDB_MESSAGE_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_MESSAGE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void		Rbdb_MessageSettingsController_internal_messageCallbackMethod(		const DB_ENV*	bdb_environment, 
			   																	const char*		message );
void		Rbdb_MessageSettingsController_internal_eventCallbackMethod(		DB_ENV*			environment, 
			   																	uint32_t		event, 
			   																	void*			event_info );

Rbdb_MessageSettingsController* Rbdb_MessageSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MessageSettingsController* message_settings_controller );
	
#endif

