#ifndef RBDB_DATABASE_VERIFICATION_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_VERIFICATION_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void		Rbdb_DatabaseVerificationSettingsController_internal_hasDoneUnorderedCheck( 	Rbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller, 
   																						int												on_or_off );
int		Rbdb_DatabaseVerificationSettingsController_internal_verifyFlags(				Rbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller );
Rbdb_DatabaseVerificationSettingsController* Rbdb_DatabaseVerificationSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller );



#endif

