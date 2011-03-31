#ifndef RPBDB_REPLICATION_ELECTION_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_REPLICATION_ELECTION_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  setCurrentAckPolicy  *
*****************************/

void	RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	RPbdb_ReplicationElectionSettingsController*	replication_elections_settings_controller,
		   																			int												new_ack_policy	);
int		RPbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( 		RPbdb_ReplicationElectionSettingsController*	replication_elections_settings_controller );
	
RPbdb_ReplicationElectionSettingsController* RPbdb_ReplicationElectionSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_ReplicationElectionSettingsController* replication_election_settings_controller );

#endif

