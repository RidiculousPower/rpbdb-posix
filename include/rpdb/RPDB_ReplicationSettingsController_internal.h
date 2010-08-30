#ifndef RPDB_REPLICATION_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_REPLICATION_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int		RPDB_ReplicationSettingsController_internal_startFlags(			RPDB_ReplicationSettingsController* replication_settings_controller );
int		RPDB_ReplicationSettingsController_internal_syncFlags(				RPDB_ReplicationSettingsController* replication_settings_controller );
int		RPDB_ReplicationSettingsController_internal_localSiteFlags(		RPDB_ReplicationSettingsController* replication_settings_controller );
int		RPDB_ReplicationSettingsController_internal_callElectionFlags(		RPDB_ReplicationSettingsController* replication_settings_controller );
int		RPDB_ReplicationSettingsController_internal_addRemoteSiteFlags(	RPDB_ReplicationSettingsController* replication_settings_controller );

RPDB_ReplicationSettingsController* RPDB_ReplicationSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_ReplicationSettingsController* replication_settings_controller );

#endif

