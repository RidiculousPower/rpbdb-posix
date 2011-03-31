#ifndef RPBDB_DATABASE_JOIN_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_JOIN_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

BOOL		RPbdb_DatabaseJoinSettingsController_internal_retrieveFlags(	RPbdb_DatabaseJoinSettingsController*		join_settings_controller );
BOOL		RPbdb_DatabaseJoinSettingsController_internal_joinFlags(	RPbdb_DatabaseJoinSettingsController*		join_settings_controller );

RPbdb_DatabaseJoinSettingsController* RPbdb_DatabaseJoinSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseJoinSettingsController* join_settings_controller );
	
#endif

