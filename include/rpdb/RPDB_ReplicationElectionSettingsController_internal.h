#ifndef RPDB_REPLICATION_ELECTION_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_REPLICATION_ELECTION_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  setCurrentAckPolicy  *
*****************************/

void	RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	RPDB_ReplicationElectionSettingsController*	replication_elections_settings_controller,
		   																			int												new_ack_policy	);
int		RPDB_ReplicationElectionSettingsController_internal_currentAckPolicy( 		RPDB_ReplicationElectionSettingsController*	replication_elections_settings_controller );
	
RPDB_ReplicationElectionSettingsController* RPDB_ReplicationElectionSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_ReplicationElectionSettingsController* replication_election_settings_controller );

#endif

