/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_ReplicationElectionSettingsController.h"

#include "RPDB_Environment.h"

#include "RPDB_ReplicationElectionSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_ReplicationElectionSettingsController*	RPDB_ReplicationElectionSettingsController_new( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller = calloc( 1, sizeof( RPDB_ReplicationElectionSettingsController ) );

	replication_elections_settings_controller->parent_replication_settings_controller = replication_settings_controller;

	return replication_elections_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_ReplicationElectionSettingsController_free(	RPDB_ReplicationElectionSettingsController** replication_election_settings_controller )	{

	free( *replication_election_settings_controller );
	*replication_election_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_ReplicationElectionSettingsController_parentEnvironment(	RPDB_ReplicationElectionSettingsController* replication_election_settings_controller )	{
	return replication_election_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
}

/*****************************************
*  numberOfSitesRequiredForElection  *
*****************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ALL
int		RPDB_ReplicationElectionSettingsController_numberOfSitesRequiredForElection( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	return replication_elections_settings_controller->number_of_sites_required_for_election;
}

/*********************************************
*  setNumberOfSitesRequiredForElection  *
*********************************************/

void	RPDB_ReplicationElectionSettingsController_setNumberOfSitesRequiredForElection(	RPDB_ReplicationElectionSettingsController*	replication_elections_settings_controller,
 																							int												number_of_sites_required_for_election	)	{

	replication_elections_settings_controller->number_of_sites_required_for_election = number_of_sites_required_for_election;
}

/*****************************************
*  numberOfSitesRequiredForElection  *
*****************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ALL
int		RPDB_ReplicationElectionSettingsController_numberOfVotesRequiredForElection( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	return replication_elections_settings_controller->number_of_votes_required_for_election;
}

/*********************************************
*  setNumberOfSitesRequiredForElection  *
*********************************************/

void	RPDB_ReplicationElectionSettingsController_setNumberOfVotesRequiredForElection(	RPDB_ReplicationElectionSettingsController*	replication_elections_settings_controller,
 																							int												number_of_votes_required_for_election	)	{

	replication_elections_settings_controller->number_of_votes_required_for_election = number_of_votes_required_for_election;
}

/*************************
*  waitForAllClients  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ALL
BOOL	RPDB_ReplicationElectionSettingsController_waitForAllClients( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_all_clients = ( RPDB_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_ALL	?
																			TRUE	:
																			FALSE );

	return replication_elections_settings_controller->wait_for_all_clients;
}

	/*********************************
	*  turnWaitForAllClientsOn  *
	*********************************/

	void	RPDB_ReplicationElectionSettingsController_turnWaitForAllClientsOn( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_all_clients = TRUE;

		RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

	/*********************************
	*  turnWaitForAllClientsOff  *
	*********************************/

	void	RPDB_ReplicationElectionSettingsController_turnWaitForAllClientsOff( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_all_clients = FALSE;

		RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_NONE );
	}

/*********************************
*  waitForAllElectablePeers  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ALL_PEERS
BOOL	RPDB_ReplicationElectionSettingsController_waitForAllElectablePeers( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_all_electable_peers = ( RPDB_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_ALL_PEERS	?
																					TRUE	:
																					FALSE );

	return replication_elections_settings_controller->wait_for_all_electable_peers;
}

	/*************************************
	*  turnWaitForAllElectablePeersOn  *
	*************************************/

	void	RPDB_ReplicationElectionSettingsController_turnWaitForAllElectablePeersOn( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_all_electable_peers = TRUE;

		RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL_PEERS );
	}

	/****************************************
	*  turnWaitForAllElectablePeersOff  *
	***************************************/

	void	RPDB_ReplicationElectionSettingsController_turnWaitForAllElectablePeersOff( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_all_electable_peers = FALSE;

		RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*********************
*  waitForNone  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_NONE
BOOL	RPDB_ReplicationElectionSettingsController_neverWait( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->never_wait = ( RPDB_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_NONE	?
																					TRUE	:
																					FALSE );

	return replication_elections_settings_controller->never_wait;
}

	/*************************
	*  turnWaitForNoneOn  *
	*************************/

	void	RPDB_ReplicationElectionSettingsController_turnNeverWaitOn( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->never_wait = TRUE;

		RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_NONE );
	}

	/*************************
	*  turnWaitForNoneOff  *
	*************************/

	void	RPDB_ReplicationElectionSettingsController_turnNeverWaitOff( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->never_wait = FALSE;

		RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*********************************
*  waitForAtLeastOneClient  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ONE
BOOL	RPDB_ReplicationElectionSettingsController_waitForAtLeastOneClient( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_at_least_one_client = ( RPDB_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_ONE	?
																					TRUE	:
																					FALSE );

	return replication_elections_settings_controller->wait_for_at_least_one_client;
}

	/*************************************
	*  turnWaitForAtLeastOneClientOn  *
	*************************************/

	void	RPDB_ReplicationElectionSettingsController_turnWaitForAtLeastOneClientOn( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_at_least_one_client = TRUE;

		RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ONE );
	}

	/*************************************
	*  turnWaitForAtLeastOneClientOff  *
	*************************************/

	void	RPDB_ReplicationElectionSettingsController_turnWaitForAtLeastOneClientOff( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_at_least_one_client = FALSE;

		RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*************************************
*  waitForAtLeastOneElectablePeer  *
*************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ONE_PEER
BOOL	RPDB_ReplicationElectionSettingsController_waitForAtLeastOneElectablePeer( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_at_least_one_electable_peer = ( RPDB_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_ONE_PEER	?
																					TRUE	:
																					FALSE );

	return replication_elections_settings_controller->wait_for_at_least_one_electable_peer;
}

	/*********************************************
	*  turnWaitForAtLeastOneElectablePeerOn  *
	*********************************************/

	void	RPDB_ReplicationElectionSettingsController_turnWaitForAtLeastOneElectablePeerOn( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_at_least_one_electable_peer = TRUE;

		RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ONE_PEER );
	}

	/*********************************************
	*  turnWaitForAtLeastOneElectablePeerOff  *
	*********************************************/

	void	RPDB_ReplicationElectionSettingsController_turnWaitForAtLeastOneElectablePeerOff( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_at_least_one_electable_peer = FALSE;

		RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*****************************************************
*  waitForMinimumElectablePeersForDurableElection  *
*****************************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_QUORUM
BOOL	RPDB_ReplicationElectionSettingsController_waitForMinimumElectablePeersForDurableElection( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_minimum_electable_peers_for_durable_election = ( RPDB_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_QUORUM	?
																												TRUE	:
																												FALSE );

	return replication_elections_settings_controller->wait_for_minimum_electable_peers_for_durable_election;
}

	/*************************************************************
	*  turnWaitForMinimumElectablePeersForDurableElectionOn  *
	*************************************************************/

	void	RPDB_ReplicationElectionSettingsController_turnWaitForMinimumElectablePeersForDurableElectionOn( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_minimum_electable_peers_for_durable_election = TRUE;

		RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_QUORUM );

	}

	/*************************************************************
	*  turnWaitForMinimumElectablePeersForDurableElectionOff  *
	*************************************************************/

	void	RPDB_ReplicationElectionSettingsController_turnWaitForMinimumElectablePeersForDurableElectionOff( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_minimum_electable_peers_for_durable_election = FALSE;

		RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  setCurrentAckPolicy  *
*****************************/

void RPDB_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	RPDB_ReplicationElectionSettingsController*	replication_elections_settings_controller,
 																				int												new_ack_policy	)	{
	
	RPDB_Environment*	environment = replication_elections_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	replication_elections_settings_controller->current_ack_policy = new_ack_policy;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->repmgr_set_ack_policy(	environment->wrapped_bdb_environment, 
																		new_ack_policy );
	}
}

/*************************
*  currentAckPolicy  *
*************************/

int RPDB_ReplicationElectionSettingsController_internal_currentAckPolicy( RPDB_ReplicationElectionSettingsController* replication_elections_settings_controller )	{
	
	RPDB_Environment*	environment = replication_elections_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	if (	replication_elections_settings_controller->current_ack_policy == 0
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->repmgr_get_ack_policy(	environment->wrapped_bdb_environment, 
																		&( replication_elections_settings_controller->current_ack_policy ) );
	}

	return replication_elections_settings_controller->current_ack_policy;
}


/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_ReplicationElectionSettingsController* RPDB_ReplicationElectionSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_ReplicationElectionSettingsController* replication_election_settings_controller )	{

	RPDB_ReplicationElectionSettingsController* replication_election_settings_controller_copy	=	RPDB_ReplicationElectionSettingsController_new( replication_election_settings_controller->parent_replication_settings_controller );

	//	Instances and Pointers
	replication_election_settings_controller_copy->wait_for_all_clients	=	replication_election_settings_controller->wait_for_all_clients;
	replication_election_settings_controller_copy->number_of_sites_required_for_election	=	replication_election_settings_controller->number_of_sites_required_for_election;
	replication_election_settings_controller_copy->current_ack_policy	=	replication_election_settings_controller->current_ack_policy;
	replication_election_settings_controller_copy->wait_for_at_least_one_client	=	replication_election_settings_controller->wait_for_at_least_one_client;
	replication_election_settings_controller_copy->wait_for_all_electable_peers	=	replication_election_settings_controller->wait_for_all_electable_peers;
	replication_election_settings_controller_copy->wait_for_minimum_electable_peers_for_durable_election	=	replication_election_settings_controller->wait_for_minimum_electable_peers_for_durable_election;
	replication_election_settings_controller_copy->never_wait	=	replication_election_settings_controller->never_wait;
	replication_election_settings_controller_copy->number_of_votes_required_for_election	=	replication_election_settings_controller->number_of_votes_required_for_election;
	replication_election_settings_controller_copy->wait_for_at_least_one_electable_peer	=	replication_election_settings_controller->wait_for_at_least_one_electable_peer;

	return replication_election_settings_controller_copy;
}

