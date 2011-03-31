/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "ReplicationElectionSettingsController.h"

#include "Environment.h"

#include "ReplicationElectionSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_ReplicationElectionSettingsController*	RPbdb_ReplicationElectionSettingsController_new( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller = calloc( 1, sizeof( RPbdb_ReplicationElectionSettingsController ) );

	replication_elections_settings_controller->parent_replication_settings_controller = replication_settings_controller;

	return replication_elections_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_ReplicationElectionSettingsController_free(	RPbdb_ReplicationElectionSettingsController** replication_election_settings_controller )	{

	free( *replication_election_settings_controller );
	*replication_election_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_ReplicationElectionSettingsController_parentEnvironment(	RPbdb_ReplicationElectionSettingsController* replication_election_settings_controller )	{
	return replication_election_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
}

/*****************************************
*  numberOfSitesRequiredForElection  *
*****************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ALL
int		RPbdb_ReplicationElectionSettingsController_numberOfSitesRequiredForElection( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	return replication_elections_settings_controller->number_of_sites_required_for_election;
}

/*********************************************
*  setNumberOfSitesRequiredForElection  *
*********************************************/

void	RPbdb_ReplicationElectionSettingsController_setNumberOfSitesRequiredForElection(	RPbdb_ReplicationElectionSettingsController*	replication_elections_settings_controller,
 																							int												number_of_sites_required_for_election	)	{

	replication_elections_settings_controller->number_of_sites_required_for_election = number_of_sites_required_for_election;
}

/*****************************************
*  numberOfSitesRequiredForElection  *
*****************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ALL
int		RPbdb_ReplicationElectionSettingsController_numberOfVotesRequiredForElection( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	return replication_elections_settings_controller->number_of_votes_required_for_election;
}

/*********************************************
*  setNumberOfSitesRequiredForElection  *
*********************************************/

void	RPbdb_ReplicationElectionSettingsController_setNumberOfVotesRequiredForElection(	RPbdb_ReplicationElectionSettingsController*	replication_elections_settings_controller,
 																							int												number_of_votes_required_for_election	)	{

	replication_elections_settings_controller->number_of_votes_required_for_election = number_of_votes_required_for_election;
}

/*************************
*  waitForAllClients  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ALL
BOOL	RPbdb_ReplicationElectionSettingsController_waitForAllClients( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_all_clients = ( RPbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_ALL	?
																			TRUE	:
																			FALSE );

	return replication_elections_settings_controller->wait_for_all_clients;
}

	/*********************************
	*  turnWaitForAllClientsOn  *
	*********************************/

	void	RPbdb_ReplicationElectionSettingsController_turnWaitForAllClientsOn( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_all_clients = TRUE;

		RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

	/*********************************
	*  turnWaitForAllClientsOff  *
	*********************************/

	void	RPbdb_ReplicationElectionSettingsController_turnWaitForAllClientsOff( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_all_clients = FALSE;

		RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_NONE );
	}

/*********************************
*  waitForAllElectablePeers  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ALL_PEERS
BOOL	RPbdb_ReplicationElectionSettingsController_waitForAllElectablePeers( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_all_electable_peers = ( RPbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_ALL_PEERS	?
																					TRUE	:
																					FALSE );

	return replication_elections_settings_controller->wait_for_all_electable_peers;
}

	/*************************************
	*  turnWaitForAllElectablePeersOn  *
	*************************************/

	void	RPbdb_ReplicationElectionSettingsController_turnWaitForAllElectablePeersOn( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_all_electable_peers = TRUE;

		RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL_PEERS );
	}

	/****************************************
	*  turnWaitForAllElectablePeersOff  *
	***************************************/

	void	RPbdb_ReplicationElectionSettingsController_turnWaitForAllElectablePeersOff( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_all_electable_peers = FALSE;

		RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*********************
*  waitForNone  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_NONE
BOOL	RPbdb_ReplicationElectionSettingsController_neverWait( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->never_wait = ( RPbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_NONE	?
																					TRUE	:
																					FALSE );

	return replication_elections_settings_controller->never_wait;
}

	/*************************
	*  turnWaitForNoneOn  *
	*************************/

	void	RPbdb_ReplicationElectionSettingsController_turnNeverWaitOn( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->never_wait = TRUE;

		RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_NONE );
	}

	/*************************
	*  turnWaitForNoneOff  *
	*************************/

	void	RPbdb_ReplicationElectionSettingsController_turnNeverWaitOff( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->never_wait = FALSE;

		RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*********************************
*  waitForAtLeastOneClient  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ONE
BOOL	RPbdb_ReplicationElectionSettingsController_waitForAtLeastOneClient( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_at_least_one_client = ( RPbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_ONE	?
																					TRUE	:
																					FALSE );

	return replication_elections_settings_controller->wait_for_at_least_one_client;
}

	/*************************************
	*  turnWaitForAtLeastOneClientOn  *
	*************************************/

	void	RPbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneClientOn( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_at_least_one_client = TRUE;

		RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ONE );
	}

	/*************************************
	*  turnWaitForAtLeastOneClientOff  *
	*************************************/

	void	RPbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneClientOff( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_at_least_one_client = FALSE;

		RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*************************************
*  waitForAtLeastOneElectablePeer  *
*************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ONE_PEER
BOOL	RPbdb_ReplicationElectionSettingsController_waitForAtLeastOneElectablePeer( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_at_least_one_electable_peer = ( RPbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_ONE_PEER	?
																					TRUE	:
																					FALSE );

	return replication_elections_settings_controller->wait_for_at_least_one_electable_peer;
}

	/*********************************************
	*  turnWaitForAtLeastOneElectablePeerOn  *
	*********************************************/

	void	RPbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneElectablePeerOn( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_at_least_one_electable_peer = TRUE;

		RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ONE_PEER );
	}

	/*********************************************
	*  turnWaitForAtLeastOneElectablePeerOff  *
	*********************************************/

	void	RPbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneElectablePeerOff( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_at_least_one_electable_peer = FALSE;

		RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*****************************************************
*  waitForMinimumElectablePeersForDurableElection  *
*****************************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_QUORUM
BOOL	RPbdb_ReplicationElectionSettingsController_waitForMinimumElectablePeersForDurableElection( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_minimum_electable_peers_for_durable_election = ( RPbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_QUORUM	?
																												TRUE	:
																												FALSE );

	return replication_elections_settings_controller->wait_for_minimum_electable_peers_for_durable_election;
}

	/*************************************************************
	*  turnWaitForMinimumElectablePeersForDurableElectionOn  *
	*************************************************************/

	void	RPbdb_ReplicationElectionSettingsController_turnWaitForMinimumElectablePeersForDurableElectionOn( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_minimum_electable_peers_for_durable_election = TRUE;

		RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_QUORUM );

	}

	/*************************************************************
	*  turnWaitForMinimumElectablePeersForDurableElectionOff  *
	*************************************************************/

	void	RPbdb_ReplicationElectionSettingsController_turnWaitForMinimumElectablePeersForDurableElectionOff( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_minimum_electable_peers_for_durable_election = FALSE;

		RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*****************************************************
*  setSiteIsNowReplicationClientCallbackMethod  *
*****************************************************/
/*
void RPbdb_MessageSettingsController_setSiteIsNowReplicationClientCallbackMethod(	RPbdb_MessageSettingsController*								message_settings_controller,
 																					void *(site_is_now_replication_client_callback_method)( RPbdb_Environment*	environment ) )	{

	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;
	
	message_settings_controller->site_is_now_replication_client_callback_method = site_is_now_replication_client_callback_method;
	//	Make sure we have our internal callback enabled
	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& RPbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*************************************************
*  siteIsNowReplicationClientCallbackMethod  *
*************************************************/
/*
void *(site_is_now_replication_client_callback_method)( RPbdb_Environment*	environment ) RPbdb_MessageSettingsController_siteIsNowReplicationClientCallbackMethod(	RPbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->site_is_now_replication_client_callback_method;
}
*/
/*****************************************************
*  setSiteWonReplicationElectionCallbackMethod  *
*****************************************************/
/*
void RPbdb_MessageSettingsController_setSiteWonReplicationElectionCallbackMethod(	RPbdb_MessageSettingsController*								message_settings_controller,
 																					void *(site_won_replication_election_callback_method)( RPbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;

	message_settings_controller->site_won_replication_election_callback_method = site_won_replication_election_callback_method;
	//	Make sure we have our internal callback enabled
	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& RPbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*************************************************
*  siteWonReplicationElectionCallbackMethod  *
*************************************************/
/*
void *(site_won_replication_election_callback_method)( RPbdb_Environment*	environment ) RPbdb_MessageSettingsController_siteWonReplicationElectionCallbackMethod(	RPbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->site_won_replication_election_callback_method;
}
*/
/*********************************************************
*  setSiteIsNowMasterOfReplicationGroupCallbackMethod  *
*********************************************************/
/*
void RPbdb_MessageSettingsController_setSiteIsNowMasterOfReplicationGroupCallbackMethod(	RPbdb_MessageSettingsController*		message_settings_controller,
 																							void *(site_is_now_master_of_replication_group_callback_method)( RPbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;
	
	message_settings_controller->site_is_now_master_of_replication_group_callback_method = site_is_now_master_of_replication_group_callback_method;
	//	Make sure we have our internal callback enabled
	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& RPbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*********************************************************
*  siteIsNowMasterOfReplicationGroupCallbackMethod  *
*********************************************************/
/*
void *(site_is_now_master_of_replication_group_callback_method)( RPbdb_Environment*	environment ) RPbdb_MessageSettingsController_siteIsNowMasterOfReplicationGroupCallbackMethod(	RPbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->site_is_now_master_of_replication_group_callback_method;
}
*/
/*****************************************************
*  setReplicationGroupHasNewMasterCallbackMethod  *
*****************************************************/
/*
void RPbdb_MessageSettingsController_setReplicationGroupHasNewMasterCallbackMethod(	RPbdb_MessageSettingsController*									message_settings_controller,
 																					void *(replication_group_has_new_master_callback_method)( RPbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;
	
	message_settings_controller->replication_group_has_new_master_callback_method = replication_group_has_new_master_callback_method;
	//	Make sure we have our internal callback enabled

	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& RPbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*************************************************
*  replicationGroupHasNewMasterCallbackMethod  *
*************************************************/
/*
void *(replication_group_has_new_master_callback_method)( RPbdb_Environment*	environment ) RPbdb_MessageSettingsController_replicationGroupHasNewMasterCallbackMethod(	RPbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->replication_group_has_new_master_callback_method;
}
*/
/*********************************************************
*  setReplicationAcknowledgementFailedCallbackMethod  *
*********************************************************/
/*
void RPbdb_MessageSettingsController_setReplicationAcknowledgementFailedCallbackMethod(	RPbdb_MessageSettingsController*									message_settings_controller,
 																						void *(replication_acknowledgement_failed_callback_method)( RPbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;
	
	message_settings_controller->replication_acknowledgement_failed_callback_method = replication_acknowledgement_failed_callback_method;
	//	Make sure we have our internal callback enabled

	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& RPbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*****************************************************
*  replicationAcknowledgementFailedCallbackMethod  *
*****************************************************/
/*
void *(replication_acknowledgement_failed_callback_method)( RPbdb_Environment*	environment ) RPbdb_MessageSettingsController_replicationAcknowledgementFailedCallbackMethod(	RPbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->replication_acknowledgement_failed_callback_method;
}
*/
/*****************************************************
*  setReplicationStartupCompletedCallbackMethod  *
*****************************************************/
/*
void RPbdb_MessageSettingsController_setReplicationStartupCompletedCallbackMethod(	RPbdb_MessageSettingsController*								message_settings_controller,
 																					void *(replication_startup_completed_callback_method)( RPbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;
	
	message_settings_controller->replication_startup_completed_callback_method = replication_startup_completed_callback_method;
	//	Make sure we have our internal callback enabled

	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& RPbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*************************************************
*  replicationStartupCompletedCallbackMethod  *
*************************************************/
/*
void *(replication_startup_completed_callback_method)( RPbdb_Environment*	environment ) RPbdb_MessageSettingsController_replicationStartupCompletedCallbackMethod(	RPbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->replication_startup_completed_callback_method;
}
*/

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  setCurrentAckPolicy  *
*****************************/

void RPbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	RPbdb_ReplicationElectionSettingsController*	replication_elections_settings_controller,
 																				int												new_ack_policy	)	{
	
	RPbdb_Environment*	environment = replication_elections_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	replication_elections_settings_controller->current_ack_policy = new_ack_policy;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->repmgr_set_ack_policy(	environment->wrapped_bdb_environment, 
																		new_ack_policy );
	}
}

/*************************
*  currentAckPolicy  *
*************************/

int RPbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( RPbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{
	
	RPbdb_Environment*	environment = replication_elections_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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
RPbdb_ReplicationElectionSettingsController* RPbdb_ReplicationElectionSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_ReplicationElectionSettingsController* replication_election_settings_controller )	{

	RPbdb_ReplicationElectionSettingsController* replication_election_settings_controller_copy	=	RPbdb_ReplicationElectionSettingsController_new( replication_election_settings_controller->parent_replication_settings_controller );

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

