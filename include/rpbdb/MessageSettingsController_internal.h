#ifndef RPBDB_MESSAGE_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_MESSAGE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void		RPbdb_MessageSettingsController_internal_messageCallbackMethod(		const DB_ENV*	bdb_environment, 
			   																	const char*		message );
void		RPbdb_MessageSettingsController_internal_eventCallbackMethod(		DB_ENV*			environment, 
			   																	uint32_t		event, 
			   																	void*			event_info );

RPbdb_MessageSettingsController* RPbdb_MessageSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MessageSettingsController* message_settings_controller );
	
#endif

