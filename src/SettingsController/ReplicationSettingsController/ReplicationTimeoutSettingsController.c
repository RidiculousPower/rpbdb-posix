/*
 *		RPbdb::SettingsController::ReplicationTimeoutSettingsController
 *
 *
 */
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "ReplicationTimeoutSettingsController.h"

#include "Environment.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_ReplicationTimeoutSettingsController* RPbdb_ReplicationTimeoutSettingsController_new( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_ReplicationTimeoutSettingsController*	replication_timeout_settings_controller = calloc( 1, sizeof( RPbdb_ReplicationTimeoutSettingsController ) );

	replication_timeout_settings_controller->parent_replication_settings_controller = replication_settings_controller;

	return replication_timeout_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_ReplicationTimeoutSettingsController_free(	RPbdb_ReplicationTimeoutSettingsController** replication_timeout_settings_controller )	{

	free( *replication_timeout_settings_controller );
	*replication_timeout_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_ReplicationTimeoutSettingsController_parentEnvironment(	RPbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{
	return replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
}

/****************
*  timeout  *
****************/

//	DB_REP_ACK_TIMEOUT
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
uint32_t RPbdb_ReplicationTimeoutSettingsController_timeout( RPbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	if (	! replication_timeout_settings_controller->timeout
		&&	environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->rep_get_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_ACK_TIMEOUT, 
																&( replication_timeout_settings_controller->timeout ) );
	}

	return replication_timeout_settings_controller->timeout;
}

/******************
*  setTimeout  *
******************/

void RPbdb_ReplicationTimeoutSettingsController_setTimeout(		RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																uint32_t										timeout )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	replication_timeout_settings_controller->timeout = timeout;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->rep_set_timeout( environment->wrapped_bdb_environment, DB_REP_CHECKPOINT_DELAY, timeout );
	}
}

/**************************************
*  waitTimeBeforeCheckpointWrite  *
**************************************/

//	DB_REP_CHECKPOINT_DELAY
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
uint32_t RPbdb_ReplicationTimeoutSettingsController_waitTimeBeforeCheckpointWrite( RPbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	if (	! replication_timeout_settings_controller->wait_time_before_checkpoint_write
		&&	environment->wrapped_bdb_environment != NULL )	{	
	
		environment->wrapped_bdb_environment->rep_get_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_CHECKPOINT_DELAY, 
																&( replication_timeout_settings_controller->wait_time_before_checkpoint_write ) );
	}

	return replication_timeout_settings_controller->wait_time_before_checkpoint_write;
}

/*****************************************
*  setWaitTimeBeforeCheckpointWrite  *
*****************************************/

void RPbdb_ReplicationTimeoutSettingsController_setWaitTimeBeforeCheckpointWrite(	RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																					uint32_t										wait_time_before_checkpoint_write )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	replication_timeout_settings_controller->wait_time_before_checkpoint_write = wait_time_before_checkpoint_write;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->rep_set_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_CHECKPOINT_DELAY, 
																wait_time_before_checkpoint_write );
	}
}

/*************************************
*  waitTimeBeforeRetryConnection  *
*************************************/

//	DB_REP_CONNECTION_RETRY
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
uint32_t RPbdb_ReplicationTimeoutSettingsController_waitTimeBeforeRetryConnection( RPbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	if (	! replication_timeout_settings_controller->wait_time_before_retry_connection
		&&	environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->rep_get_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_CONNECTION_RETRY, 
																&( replication_timeout_settings_controller->wait_time_before_retry_connection ) );
	}

	return replication_timeout_settings_controller->wait_time_before_retry_connection;
}

/*****************************************
*  setWaitTimeBeforeRetryConnection  *
*****************************************/

void RPbdb_ReplicationTimeoutSettingsController_setWaitTimeBeforeRetryConnection(	RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller,
																					uint32_t										wait_time_before_retry_connection )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	replication_timeout_settings_controller->wait_time_before_retry_connection = wait_time_before_retry_connection;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->rep_set_timeout( environment->wrapped_bdb_environment, DB_REP_CONNECTION_RETRY, wait_time_before_retry_connection );
	}
}

/*************************
*  electionTimeout  *
*************************/

//	DB_REP_ELECTION_TIMEOUT
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
uint32_t RPbdb_ReplicationTimeoutSettingsController_electionTimeout( RPbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	if (	! replication_timeout_settings_controller->election_timeout
		&&	environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->rep_get_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_ELECTION_TIMEOUT, 
																&( replication_timeout_settings_controller->election_timeout ) );
	}

	return replication_timeout_settings_controller->election_timeout;
}

/*************************
*  setElectionTimeout  *
*************************/

void RPbdb_ReplicationTimeoutSettingsController_setElectionTimeout(	RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																	uint32_t										election_timeout )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	replication_timeout_settings_controller->election_timeout = election_timeout;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->rep_set_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_ELECTION_TIMEOUT, 
																election_timeout );
	}
}

/*************************************
*  waitTimeBeforeRetryElection  *
*************************************/

//	DB_REP_ELECTION_RETRY
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
uint32_t RPbdb_ReplicationTimeoutSettingsController_waitTimeBeforeRetryElection( RPbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
	
	if (	! replication_timeout_settings_controller->wait_time_before_retry_election
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->rep_get_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_ELECTION_RETRY, 
																&( replication_timeout_settings_controller->wait_time_before_retry_election ) );
	}

	return replication_timeout_settings_controller->wait_time_before_retry_election;
}

/*****************************************
*  setWaitTimeBeforeRetryElection  *
*****************************************/

void RPbdb_ReplicationTimeoutSettingsController_setWaitTimeBeforeRetryElection(	RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																				uint32_t										wait_time_before_retry_election )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	replication_timeout_settings_controller->wait_time_before_retry_election = wait_time_before_retry_election;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->rep_set_timeout( environment->wrapped_bdb_environment, DB_REP_ELECTION_RETRY, wait_time_before_retry_election );
	}
}

/*****************************************
*  fullElectionParticipationTimeout  *
*****************************************/

//	DB_REP_FULL_ELECTION_TIMEOUT
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
uint32_t RPbdb_ReplicationTimeoutSettingsController_fullElectionParticipationTimeout( RPbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
	
	if (	! replication_timeout_settings_controller->full_election_participation_timeout
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->rep_get_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_FULL_ELECTION_TIMEOUT, 
																&( replication_timeout_settings_controller->full_election_participation_timeout ) );
	}

	return replication_timeout_settings_controller->full_election_participation_timeout;
}

/********************************************
*  setFullElectionParticipationTimeout  *
********************************************/

void RPbdb_ReplicationTimeoutSettingsController_setFullElectionParticipationTimeout(	RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																						uint32_t										full_election_participation_timeout )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	replication_timeout_settings_controller->full_election_participation_timeout = full_election_participation_timeout;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->rep_set_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_FULL_ELECTION_TIMEOUT, 
																full_election_participation_timeout );
	}
}

/*********************************
*  heartbeatMonitorPulse  *
*********************************/

//	DB_REP_HEARTBEAT_MONITOR
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
uint32_t RPbdb_ReplicationTimeoutSettingsController_heartbeatMonitorPulse( RPbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
	
	if (	! replication_timeout_settings_controller->heartbeat_monitor_pulse
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->rep_get_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_HEARTBEAT_MONITOR, 
																&( replication_timeout_settings_controller->heartbeat_monitor_pulse ) );
	}

	return replication_timeout_settings_controller->heartbeat_monitor_pulse;	
}

/*************************************
*  setHeartbeatMonitorPulse  *
*************************************/

void RPbdb_ReplicationTimeoutSettingsController_setHeartbeatMonitorPulse(	RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																			uint32_t										heartbeat_monitor_pulse )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	replication_timeout_settings_controller->heartbeat_monitor_pulse = heartbeat_monitor_pulse;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->rep_set_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_HEARTBEAT_MONITOR, 
																heartbeat_monitor_pulse );
	}
}

/*********************************
*  heartbeatBroadcastPulse  *
*********************************/

//	DB_REP_HEARTBEAT_SEND
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
uint32_t RPbdb_ReplicationTimeoutSettingsController_heartbeatBroadcastPulse( RPbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
	
	if (	! replication_timeout_settings_controller->heartbeat_broadcast_pulse
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->rep_get_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_HEARTBEAT_SEND, 
																&( replication_timeout_settings_controller->heartbeat_broadcast_pulse ) );
	}

	return replication_timeout_settings_controller->heartbeat_broadcast_pulse;
}

/*************************************
*  setHeartbeatBroadcastPulse  *
*************************************/

void RPbdb_ReplicationTimeoutSettingsController_setHeartbeatBroadcastPulse(	RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																			uint32_t										heartbeat_broadcast_pulse )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	replication_timeout_settings_controller->heartbeat_broadcast_pulse = heartbeat_broadcast_pulse;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->rep_set_timeout( environment->wrapped_bdb_environment, DB_REP_HEARTBEAT_SEND, heartbeat_broadcast_pulse );
	}
}

/*********************
*  leaseTimeout  *
*********************/

//	DB_REP_LEASE_TIMEOUT
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
uint32_t RPbdb_ReplicationTimeoutSettingsController_leaseTimeout( RPbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
	
	if (	! replication_timeout_settings_controller->lease_timeout
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->rep_get_timeout(	environment->wrapped_bdb_environment, 
																DB_REP_LEASE_TIMEOUT, 
																&( replication_timeout_settings_controller->lease_timeout ) );
	}

	return replication_timeout_settings_controller->lease_timeout;
}

/************************
*  setLeaseTimeout  *
************************/

void RPbdb_ReplicationTimeoutSettingsController_setLeaseTimeout( RPbdb_ReplicationTimeoutSettingsController*	replication_timeout_settings_controller,
																uint32_t										lease_timeout )	{

	RPbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

	replication_timeout_settings_controller->lease_timeout = lease_timeout;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->rep_set_timeout( environment->wrapped_bdb_environment, DB_REP_LEASE_TIMEOUT, lease_timeout );
	}
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_ReplicationTimeoutSettingsController* RPbdb_ReplicationTimeoutSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	RPbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller_copy	=	RPbdb_ReplicationTimeoutSettingsController_new( replication_timeout_settings_controller->parent_replication_settings_controller );

	//	Instances and Pointers
	replication_timeout_settings_controller_copy->wait_time_before_checkpoint_write	=	replication_timeout_settings_controller->wait_time_before_checkpoint_write;
	replication_timeout_settings_controller_copy->wait_time_before_retry_election	=	replication_timeout_settings_controller->wait_time_before_retry_election;
	replication_timeout_settings_controller_copy->timeout	=	replication_timeout_settings_controller->timeout;
	replication_timeout_settings_controller_copy->heartbeat_broadcast_pulse	=	replication_timeout_settings_controller->heartbeat_broadcast_pulse;
	replication_timeout_settings_controller_copy->full_election_participation_timeout	=	replication_timeout_settings_controller->full_election_participation_timeout;
	replication_timeout_settings_controller_copy->wait_time_before_retry_connection	=	replication_timeout_settings_controller->wait_time_before_retry_connection;
	replication_timeout_settings_controller_copy->lease_timeout	=	replication_timeout_settings_controller->lease_timeout;
	replication_timeout_settings_controller_copy->election_timeout	=	replication_timeout_settings_controller->election_timeout;
	replication_timeout_settings_controller_copy->heartbeat_monitor_pulse	=	replication_timeout_settings_controller->heartbeat_monitor_pulse;

	return replication_timeout_settings_controller_copy;
}

