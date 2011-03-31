/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPBDB_REPLICATION_ELECTION_SETTINGS_CONTROLLER
	#define RPBDB_REPLICATION_ELECTION_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPbdb_ReplicationElectionSettingsController*		RPbdb_ReplicationElectionSettingsController_new(														RPbdb_ReplicationSettingsController*				replication_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_free(														RPbdb_ReplicationElectionSettingsController** replication_election_settings_controller );
	RPbdb_Environment*							RPbdb_ReplicationElectionSettingsController_parentEnvironment(								RPbdb_ReplicationElectionSettingsController* replication_election_settings_controller );

	int													RPbdb_ReplicationElectionSettingsController_numberOfSitesRequiredForElection( 							RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_setNumberOfSitesRequiredForElection(						RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller,
																																								int													number_of_sites_required_for_election	);
																																								
	int													RPbdb_ReplicationElectionSettingsController_numberOfVotesRequiredForElection( 							RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_setNumberOfVotesRequiredForElection(						RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller,
																																								int													number_of_votes_required_for_election	);
														
	BOOL												RPbdb_ReplicationElectionSettingsController_waitForAllClients(											RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_turnWaitForAllClientsOn(									RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_turnWaitForAllClientsOff(									RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												RPbdb_ReplicationElectionSettingsController_waitForAllElectablePeers(									RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_turnWaitForAllElectablePeersOn(								RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_turnWaitForAllElectablePeersOff(							RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												RPbdb_ReplicationElectionSettingsController_neverWait(													RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_turnNeverWaitOn(											RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_turnNeverWaitOff(											RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												RPbdb_ReplicationElectionSettingsController_waitForAtLeastOneClient(									RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneClientOn(								RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneClientOff(								RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												RPbdb_ReplicationElectionSettingsController_waitForAtLeastOneElectablePeer(								RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneElectablePeerOn(						RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneElectablePeerOff(						RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												RPbdb_ReplicationElectionSettingsController_waitForMinimumElectablePeersForDurableElection(				RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_turnWaitForMinimumElectablePeersForDurableElectionOn(		RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPbdb_ReplicationElectionSettingsController_turnWaitForMinimumElectablePeersForDurableElectionOff(		RPbdb_ReplicationElectionSettingsController*		replication_elections_settings_controller );

#endif

