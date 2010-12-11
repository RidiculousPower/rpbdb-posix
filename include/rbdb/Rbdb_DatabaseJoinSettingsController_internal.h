#ifndef RBDB_DATABASE_JOIN_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_JOIN_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

BOOL		Rbdb_DatabaseJoinSettingsController_internal_retrieveFlags(	Rbdb_DatabaseJoinSettingsController*		join_settings_controller );
BOOL		Rbdb_DatabaseJoinSettingsController_internal_joinFlags(	Rbdb_DatabaseJoinSettingsController*		join_settings_controller );

Rbdb_DatabaseJoinSettingsController* Rbdb_DatabaseJoinSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseJoinSettingsController* join_settings_controller );
	
#endif

