/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RBDB_REPLICATION_ELECTION_SETTINGS_CONTROLLER
	#define RBDB_REPLICATION_ELECTION_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	Rbdb_ReplicationElectionSettingsController*		Rbdb_ReplicationElectionSettingsController_new(														Rbdb_ReplicationSettingsController*				replication_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_free(														Rbdb_ReplicationElectionSettingsController** replication_election_settings_controller );
	Rbdb_Environment*							Rbdb_ReplicationElectionSettingsController_parentEnvironment(								Rbdb_ReplicationElectionSettingsController* replication_election_settings_controller );

	int													Rbdb_ReplicationElectionSettingsController_numberOfSitesRequiredForElection( 							Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_setNumberOfSitesRequiredForElection(						Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller,
																																								int													number_of_sites_required_for_election	);
																																								
	int													Rbdb_ReplicationElectionSettingsController_numberOfVotesRequiredForElection( 							Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_setNumberOfVotesRequiredForElection(						Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller,
																																								int													number_of_votes_required_for_election	);
														
	BOOL												Rbdb_ReplicationElectionSettingsController_waitForAllClients(											Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_turnWaitForAllClientsOn(									Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_turnWaitForAllClientsOff(									Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												Rbdb_ReplicationElectionSettingsController_waitForAllElectablePeers(									Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_turnWaitForAllElectablePeersOn(								Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_turnWaitForAllElectablePeersOff(							Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												Rbdb_ReplicationElectionSettingsController_neverWait(													Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_turnNeverWaitOn(											Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_turnNeverWaitOff(											Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												Rbdb_ReplicationElectionSettingsController_waitForAtLeastOneClient(									Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneClientOn(								Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneClientOff(								Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												Rbdb_ReplicationElectionSettingsController_waitForAtLeastOneElectablePeer(								Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneElectablePeerOn(						Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneElectablePeerOff(						Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												Rbdb_ReplicationElectionSettingsController_waitForMinimumElectablePeersForDurableElection(				Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_turnWaitForMinimumElectablePeersForDurableElectionOn(		Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												Rbdb_ReplicationElectionSettingsController_turnWaitForMinimumElectablePeersForDurableElectionOff(		Rbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );

#endif

