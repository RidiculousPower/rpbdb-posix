#ifndef RPBDB_REPLICATION_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_REPLICATION_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int		RPbdb_ReplicationSettingsController_internal_startFlags(			RPbdb_ReplicationSettingsController* replication_settings_controller );
int		RPbdb_ReplicationSettingsController_internal_syncFlags(				RPbdb_ReplicationSettingsController* replication_settings_controller );
int		RPbdb_ReplicationSettingsController_internal_localSiteFlags(		RPbdb_ReplicationSettingsController* replication_settings_controller );
int		RPbdb_ReplicationSettingsController_internal_callElectionFlags(		RPbdb_ReplicationSettingsController* replication_settings_controller );
int		RPbdb_ReplicationSettingsController_internal_addRemoteSiteFlags(	RPbdb_ReplicationSettingsController* replication_settings_controller );

RPbdb_ReplicationSettingsController* RPbdb_ReplicationSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_ReplicationSettingsController* replication_settings_controller );

#endif

