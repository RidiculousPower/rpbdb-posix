#ifndef RPDB_DATABASE_VERIFICATION_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_VERIFICATION_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void		RPDB_DatabaseVerificationSettingsController_internal_hasDoneUnorderedCheck( 	RPDB_DatabaseVerificationSettingsController*	database_verification_settings_controller, 
   																						int												on_or_off );
int		RPDB_DatabaseVerificationSettingsController_internal_verifyFlags(				RPDB_DatabaseVerificationSettingsController*	database_verification_settings_controller );
RPDB_DatabaseVerificationSettingsController* RPDB_DatabaseVerificationSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller );



#endif

