#ifndef RPDB_MESSAGE_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_MESSAGE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void		RPDB_MessageSettingsController_internal_messageCallbackMethod(		const DB_ENV*	bdb_environment, 
			   																	const char*		message );
void		RPDB_MessageSettingsController_internal_eventCallbackMethod(		DB_ENV*			environment, 
			   																	uint32_t		event, 
			   																	void*			event_info );

RPDB_MessageSettingsController* RPDB_MessageSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MessageSettingsController* message_settings_controller );
	
#endif

