#ifndef RPDB_DATABASE_JOIN_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_JOIN_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

BOOL		RPDB_DatabaseJoinSettingsController_internal_retrieveFlags(	RPDB_DatabaseJoinSettingsController*		join_settings_controller );
BOOL		RPDB_DatabaseJoinSettingsController_internal_joinFlags(	RPDB_DatabaseJoinSettingsController*		join_settings_controller );

RPDB_DatabaseJoinSettingsController* RPDB_DatabaseJoinSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseJoinSettingsController* join_settings_controller );
	
#endif

