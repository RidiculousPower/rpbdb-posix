#ifndef RPBDB_DATABASE_VERIFICATION_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_VERIFICATION_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void		RPbdb_DatabaseVerificationSettingsController_internal_hasDoneUnorderedCheck( 	RPbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller, 
   																						int												on_or_off );
int		RPbdb_DatabaseVerificationSettingsController_internal_verifyFlags(				RPbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller );
RPbdb_DatabaseVerificationSettingsController* RPbdb_DatabaseVerificationSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller );



#endif

