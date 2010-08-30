/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPDB_REPLICATION_ELECTION_SETTINGS_CONTROLLER
	#define RPDB_REPLICATION_ELECTION_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPDB_ReplicationElectionSettingsController*		RPDB_ReplicationElectionSettingsController_new(														RPDB_ReplicationSettingsController*				replication_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_free(														RPDB_ReplicationElectionSettingsController** replication_election_settings_controller );
	RPDB_Environment*							RPDB_ReplicationElectionSettingsController_parentEnvironment(								RPDB_ReplicationElectionSettingsController* replication_election_settings_controller );

	int													RPDB_ReplicationElectionSettingsController_numberOfSitesRequiredForElection( 							RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_setNumberOfSitesRequiredForElection(						RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller,
																																								int													number_of_sites_required_for_election	);
																																								
	int													RPDB_ReplicationElectionSettingsController_numberOfVotesRequiredForElection( 							RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_setNumberOfVotesRequiredForElection(						RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller,
																																								int													number_of_votes_required_for_election	);
														
	BOOL												RPDB_ReplicationElectionSettingsController_waitForAllClients(											RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_turnWaitForAllClientsOn(									RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_turnWaitForAllClientsOff(									RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												RPDB_ReplicationElectionSettingsController_waitForAllElectablePeers(									RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_turnWaitForAllElectablePeersOn(								RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_turnWaitForAllElectablePeersOff(							RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												RPDB_ReplicationElectionSettingsController_neverWait(													RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_turnNeverWaitOn(											RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_turnNeverWaitOff(											RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												RPDB_ReplicationElectionSettingsController_waitForAtLeastOneClient(									RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_turnWaitForAtLeastOneClientOn(								RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_turnWaitForAtLeastOneClientOff(								RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												RPDB_ReplicationElectionSettingsController_waitForAtLeastOneElectablePeer(								RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_turnWaitForAtLeastOneElectablePeerOn(						RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_turnWaitForAtLeastOneElectablePeerOff(						RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
														
	BOOL												RPDB_ReplicationElectionSettingsController_waitForMinimumElectablePeersForDurableElection(				RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_turnWaitForMinimumElectablePeersForDurableElectionOn(		RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );
	void												RPDB_ReplicationElectionSettingsController_turnWaitForMinimumElectablePeersForDurableElectionOff(		RPDB_ReplicationElectionSettingsController*		replication_elections_settings_controller );

#endif

