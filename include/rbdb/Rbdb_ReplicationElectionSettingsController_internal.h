#ifndef RBDB_REPLICATION_ELECTION_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_REPLICATION_ELECTION_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  setCurrentAckPolicy  *
*****************************/

void	Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	Rbdb_ReplicationElectionSettingsController*	replication_elections_settings_controller,
		   																			int												new_ack_policy	);
int		Rbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( 		Rbdb_ReplicationElectionSettingsController*	replication_elections_settings_controller );
	
Rbdb_ReplicationElectionSettingsController* Rbdb_ReplicationElectionSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_ReplicationElectionSettingsController* replication_election_settings_controller );

#endif

