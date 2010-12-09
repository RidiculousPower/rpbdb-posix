#ifndef Rbdb_REPLICATION_SETTINGS_CONTROLLER_INTERNAL
	#define Rbdb_REPLICATION_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int		Rbdb_ReplicationSettingsController_internal_startFlags(			Rbdb_ReplicationSettingsController* replication_settings_controller );
int		Rbdb_ReplicationSettingsController_internal_syncFlags(				Rbdb_ReplicationSettingsController* replication_settings_controller );
int		Rbdb_ReplicationSettingsController_internal_localSiteFlags(		Rbdb_ReplicationSettingsController* replication_settings_controller );
int		Rbdb_ReplicationSettingsController_internal_callElectionFlags(		Rbdb_ReplicationSettingsController* replication_settings_controller );
int		Rbdb_ReplicationSettingsController_internal_addRemoteSiteFlags(	Rbdb_ReplicationSettingsController* replication_settings_controller );

Rbdb_ReplicationSettingsController* Rbdb_ReplicationSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_ReplicationSettingsController* replication_settings_controller );

#endif

