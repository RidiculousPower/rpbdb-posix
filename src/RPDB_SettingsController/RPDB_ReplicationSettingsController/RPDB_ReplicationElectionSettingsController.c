/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_ReplicationElectionSettingsController.h"

#include "Rbdb_Environment.h"

#include "Rbdb_ReplicationElectionSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_ReplicationElectionSettingsController*	Rbdb_ReplicationElectionSettingsController_new( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller = calloc( 1, sizeof( Rbdb_ReplicationElectionSettingsController ) );

	replication_elections_settings_controller->parent_replication_settings_controller = replication_settings_controller;

	return replication_elections_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_ReplicationElectionSettingsController_free(	Rbdb_ReplicationElectionSettingsController** replication_election_settings_controller )	{

	free( *replication_election_settings_controller );
	*replication_election_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_ReplicationElectionSettingsController_parentEnvironment(	Rbdb_ReplicationElectionSettingsController* replication_election_settings_controller )	{
	return replication_election_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
}

/*****************************************
*  numberOfSitesRequiredForElection  *
*****************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ALL
int		Rbdb_ReplicationElectionSettingsController_numberOfSitesRequiredForElection( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	return replication_elections_settings_controller->number_of_sites_required_for_election;
}

/*********************************************
*  setNumberOfSitesRequiredForElection  *
*********************************************/

void	Rbdb_ReplicationElectionSettingsController_setNumberOfSitesRequiredForElection(	Rbdb_ReplicationElectionSettingsController*	replication_elections_settings_controller,
 																							int												number_of_sites_required_for_election	)	{

	replication_elections_settings_controller->number_of_sites_required_for_election = number_of_sites_required_for_election;
}

/*****************************************
*  numberOfSitesRequiredForElection  *
*****************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ALL
int		Rbdb_ReplicationElectionSettingsController_numberOfVotesRequiredForElection( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	return replication_elections_settings_controller->number_of_votes_required_for_election;
}

/*********************************************
*  setNumberOfSitesRequiredForElection  *
*********************************************/

void	Rbdb_ReplicationElectionSettingsController_setNumberOfVotesRequiredForElection(	Rbdb_ReplicationElectionSettingsController*	replication_elections_settings_controller,
 																							int												number_of_votes_required_for_election	)	{

	replication_elections_settings_controller->number_of_votes_required_for_election = number_of_votes_required_for_election;
}

/*************************
*  waitForAllClients  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ALL
BOOL	Rbdb_ReplicationElectionSettingsController_waitForAllClients( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_all_clients = ( Rbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_ALL	?
																			TRUE	:
																			FALSE );

	return replication_elections_settings_controller->wait_for_all_clients;
}

	/*********************************
	*  turnWaitForAllClientsOn  *
	*********************************/

	void	Rbdb_ReplicationElectionSettingsController_turnWaitForAllClientsOn( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_all_clients = TRUE;

		Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

	/*********************************
	*  turnWaitForAllClientsOff  *
	*********************************/

	void	Rbdb_ReplicationElectionSettingsController_turnWaitForAllClientsOff( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_all_clients = FALSE;

		Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_NONE );
	}

/*********************************
*  waitForAllElectablePeers  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ALL_PEERS
BOOL	Rbdb_ReplicationElectionSettingsController_waitForAllElectablePeers( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_all_electable_peers = ( Rbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_ALL_PEERS	?
																					TRUE	:
																					FALSE );

	return replication_elections_settings_controller->wait_for_all_electable_peers;
}

	/*************************************
	*  turnWaitForAllElectablePeersOn  *
	*************************************/

	void	Rbdb_ReplicationElectionSettingsController_turnWaitForAllElectablePeersOn( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_all_electable_peers = TRUE;

		Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL_PEERS );
	}

	/****************************************
	*  turnWaitForAllElectablePeersOff  *
	***************************************/

	void	Rbdb_ReplicationElectionSettingsController_turnWaitForAllElectablePeersOff( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_all_electable_peers = FALSE;

		Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*********************
*  waitForNone  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_NONE
BOOL	Rbdb_ReplicationElectionSettingsController_neverWait( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->never_wait = ( Rbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_NONE	?
																					TRUE	:
																					FALSE );

	return replication_elections_settings_controller->never_wait;
}

	/*************************
	*  turnWaitForNoneOn  *
	*************************/

	void	Rbdb_ReplicationElectionSettingsController_turnNeverWaitOn( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->never_wait = TRUE;

		Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_NONE );
	}

	/*************************
	*  turnWaitForNoneOff  *
	*************************/

	void	Rbdb_ReplicationElectionSettingsController_turnNeverWaitOff( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->never_wait = FALSE;

		Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*********************************
*  waitForAtLeastOneClient  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ONE
BOOL	Rbdb_ReplicationElectionSettingsController_waitForAtLeastOneClient( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_at_least_one_client = ( Rbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_ONE	?
																					TRUE	:
																					FALSE );

	return replication_elections_settings_controller->wait_for_at_least_one_client;
}

	/*************************************
	*  turnWaitForAtLeastOneClientOn  *
	*************************************/

	void	Rbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneClientOn( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_at_least_one_client = TRUE;

		Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ONE );
	}

	/*************************************
	*  turnWaitForAtLeastOneClientOff  *
	*************************************/

	void	Rbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneClientOff( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_at_least_one_client = FALSE;

		Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*************************************
*  waitForAtLeastOneElectablePeer  *
*************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_ONE_PEER
BOOL	Rbdb_ReplicationElectionSettingsController_waitForAtLeastOneElectablePeer( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_at_least_one_electable_peer = ( Rbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_ONE_PEER	?
																					TRUE	:
																					FALSE );

	return replication_elections_settings_controller->wait_for_at_least_one_electable_peer;
}

	/*********************************************
	*  turnWaitForAtLeastOneElectablePeerOn  *
	*********************************************/

	void	Rbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneElectablePeerOn( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_at_least_one_electable_peer = TRUE;

		Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ONE_PEER );
	}

	/*********************************************
	*  turnWaitForAtLeastOneElectablePeerOff  *
	*********************************************/

	void	Rbdb_ReplicationElectionSettingsController_turnWaitForAtLeastOneElectablePeerOff( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_at_least_one_electable_peer = FALSE;

		Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*****************************************************
*  waitForMinimumElectablePeersForDurableElection  *
*****************************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_ack_policy.html
//	DB_REPMGR_ACKS_QUORUM
BOOL	Rbdb_ReplicationElectionSettingsController_waitForMinimumElectablePeersForDurableElection( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

	replication_elections_settings_controller->wait_for_minimum_electable_peers_for_durable_election = ( Rbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( replication_elections_settings_controller ) == DB_REPMGR_ACKS_QUORUM	?
																												TRUE	:
																												FALSE );

	return replication_elections_settings_controller->wait_for_minimum_electable_peers_for_durable_election;
}

	/*************************************************************
	*  turnWaitForMinimumElectablePeersForDurableElectionOn  *
	*************************************************************/

	void	Rbdb_ReplicationElectionSettingsController_turnWaitForMinimumElectablePeersForDurableElectionOn( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_minimum_electable_peers_for_durable_election = TRUE;

		Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_QUORUM );

	}

	/*************************************************************
	*  turnWaitForMinimumElectablePeersForDurableElectionOff  *
	*************************************************************/

	void	Rbdb_ReplicationElectionSettingsController_turnWaitForMinimumElectablePeersForDurableElectionOff( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{

		replication_elections_settings_controller->wait_for_minimum_electable_peers_for_durable_election = FALSE;

		Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	replication_elections_settings_controller,
																					DB_REPMGR_ACKS_ALL );
	}

/*****************************************************
*  setSiteIsNowReplicationClientCallbackMethod  *
*****************************************************/
/*
void Rbdb_MessageSettingsController_setSiteIsNowReplicationClientCallbackMethod(	Rbdb_MessageSettingsController*								message_settings_controller,
 																					void *(site_is_now_replication_client_callback_method)( Rbdb_Environment*	environment ) )	{

	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;
	
	message_settings_controller->site_is_now_replication_client_callback_method = site_is_now_replication_client_callback_method;
	//	Make sure we have our internal callback enabled
	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& Rbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*************************************************
*  siteIsNowReplicationClientCallbackMethod  *
*************************************************/
/*
void *(site_is_now_replication_client_callback_method)( Rbdb_Environment*	environment ) Rbdb_MessageSettingsController_siteIsNowReplicationClientCallbackMethod(	Rbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->site_is_now_replication_client_callback_method;
}
*/
/*****************************************************
*  setSiteWonReplicationElectionCallbackMethod  *
*****************************************************/
/*
void Rbdb_MessageSettingsController_setSiteWonReplicationElectionCallbackMethod(	Rbdb_MessageSettingsController*								message_settings_controller,
 																					void *(site_won_replication_election_callback_method)( Rbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;

	message_settings_controller->site_won_replication_election_callback_method = site_won_replication_election_callback_method;
	//	Make sure we have our internal callback enabled
	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& Rbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*************************************************
*  siteWonReplicationElectionCallbackMethod  *
*************************************************/
/*
void *(site_won_replication_election_callback_method)( Rbdb_Environment*	environment ) Rbdb_MessageSettingsController_siteWonReplicationElectionCallbackMethod(	Rbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->site_won_replication_election_callback_method;
}
*/
/*********************************************************
*  setSiteIsNowMasterOfReplicationGroupCallbackMethod  *
*********************************************************/
/*
void Rbdb_MessageSettingsController_setSiteIsNowMasterOfReplicationGroupCallbackMethod(	Rbdb_MessageSettingsController*		message_settings_controller,
 																							void *(site_is_now_master_of_replication_group_callback_method)( Rbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;
	
	message_settings_controller->site_is_now_master_of_replication_group_callback_method = site_is_now_master_of_replication_group_callback_method;
	//	Make sure we have our internal callback enabled
	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& Rbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*********************************************************
*  siteIsNowMasterOfReplicationGroupCallbackMethod  *
*********************************************************/
/*
void *(site_is_now_master_of_replication_group_callback_method)( Rbdb_Environment*	environment ) Rbdb_MessageSettingsController_siteIsNowMasterOfReplicationGroupCallbackMethod(	Rbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->site_is_now_master_of_replication_group_callback_method;
}
*/
/*****************************************************
*  setReplicationGroupHasNewMasterCallbackMethod  *
*****************************************************/
/*
void Rbdb_MessageSettingsController_setReplicationGroupHasNewMasterCallbackMethod(	Rbdb_MessageSettingsController*									message_settings_controller,
 																					void *(replication_group_has_new_master_callback_method)( Rbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;
	
	message_settings_controller->replication_group_has_new_master_callback_method = replication_group_has_new_master_callback_method;
	//	Make sure we have our internal callback enabled

	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& Rbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*************************************************
*  replicationGroupHasNewMasterCallbackMethod  *
*************************************************/
/*
void *(replication_group_has_new_master_callback_method)( Rbdb_Environment*	environment ) Rbdb_MessageSettingsController_replicationGroupHasNewMasterCallbackMethod(	Rbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->replication_group_has_new_master_callback_method;
}
*/
/*********************************************************
*  setReplicationAcknowledgementFailedCallbackMethod  *
*********************************************************/
/*
void Rbdb_MessageSettingsController_setReplicationAcknowledgementFailedCallbackMethod(	Rbdb_MessageSettingsController*									message_settings_controller,
 																						void *(replication_acknowledgement_failed_callback_method)( Rbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;
	
	message_settings_controller->replication_acknowledgement_failed_callback_method = replication_acknowledgement_failed_callback_method;
	//	Make sure we have our internal callback enabled

	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& Rbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*****************************************************
*  replicationAcknowledgementFailedCallbackMethod  *
*****************************************************/
/*
void *(replication_acknowledgement_failed_callback_method)( Rbdb_Environment*	environment ) Rbdb_MessageSettingsController_replicationAcknowledgementFailedCallbackMethod(	Rbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->replication_acknowledgement_failed_callback_method;
}
*/
/*****************************************************
*  setReplicationStartupCompletedCallbackMethod  *
*****************************************************/
/*
void Rbdb_MessageSettingsController_setReplicationStartupCompletedCallbackMethod(	Rbdb_MessageSettingsController*								message_settings_controller,
 																					void *(replication_startup_completed_callback_method)( Rbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;
	
	message_settings_controller->replication_startup_completed_callback_method = replication_startup_completed_callback_method;
	//	Make sure we have our internal callback enabled

	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& Rbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*************************************************
*  replicationStartupCompletedCallbackMethod  *
*************************************************/
/*
void *(replication_startup_completed_callback_method)( Rbdb_Environment*	environment ) Rbdb_MessageSettingsController_replicationStartupCompletedCallbackMethod(	Rbdb_MessageSettingsController*		message_settings_controller )	{
	
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

void Rbdb_ReplicationElectionSettingsController_internal_setCurrentAckPolicy(	Rbdb_ReplicationElectionSettingsController*	replication_elections_settings_controller,
 																				int												new_ack_policy	)	{
	
	Rbdb_Environment*	environment = replication_elections_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	replication_elections_settings_controller->current_ack_policy = new_ack_policy;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->repmgr_set_ack_policy(	environment->wrapped_bdb_environment, 
																		new_ack_policy );
	}
}

/*************************
*  currentAckPolicy  *
*************************/

int Rbdb_ReplicationElectionSettingsController_internal_currentAckPolicy( Rbdb_ReplicationElectionSettingsController* replication_elections_settings_controller )	{
	
	Rbdb_Environment*	environment = replication_elections_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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
Rbdb_ReplicationElectionSettingsController* Rbdb_ReplicationElectionSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_ReplicationElectionSettingsController* replication_election_settings_controller )	{

	Rbdb_ReplicationElectionSettingsController* replication_election_settings_controller_copy	=	Rbdb_ReplicationElectionSettingsController_new( replication_election_settings_controller->parent_replication_settings_controller );

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

