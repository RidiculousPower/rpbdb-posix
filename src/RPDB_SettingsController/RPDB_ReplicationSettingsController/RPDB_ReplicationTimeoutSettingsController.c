/*
 *		Rbdb::SettingsController::ReplicationTimeoutSettingsController
 *
 *
 */
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_ReplicationTimeoutSettingsController.h"

#include "Rbdb_Environment.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

Rbdb_ReplicationTimeoutSettingsController* Rbdb_ReplicationTimeoutSettingsController_new( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_ReplicationTimeoutSettingsController*	replication_timeout_settings_controller = calloc( 1, sizeof( Rbdb_ReplicationTimeoutSettingsController ) );

	replication_timeout_settings_controller->parent_replication_settings_controller = replication_settings_controller;

	return replication_timeout_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_ReplicationTimeoutSettingsController_free(	Rbdb_ReplicationTimeoutSettingsController** replication_timeout_settings_controller )	{

	free( *replication_timeout_settings_controller );
	*replication_timeout_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_ReplicationTimeoutSettingsController_parentEnvironment(	Rbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{
	return replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
}

/****************
*  timeout  *
****************/

//	DB_REP_ACK_TIMEOUT
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
uint32_t Rbdb_ReplicationTimeoutSettingsController_timeout( Rbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationTimeoutSettingsController_setTimeout(		Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																uint32_t										timeout )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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
uint32_t Rbdb_ReplicationTimeoutSettingsController_waitTimeBeforeCheckpointWrite( Rbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationTimeoutSettingsController_setWaitTimeBeforeCheckpointWrite(	Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																					uint32_t										wait_time_before_checkpoint_write )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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
uint32_t Rbdb_ReplicationTimeoutSettingsController_waitTimeBeforeRetryConnection( Rbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationTimeoutSettingsController_setWaitTimeBeforeRetryConnection(	Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller,
																					uint32_t										wait_time_before_retry_connection )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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
uint32_t Rbdb_ReplicationTimeoutSettingsController_electionTimeout( Rbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationTimeoutSettingsController_setElectionTimeout(	Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																	uint32_t										election_timeout )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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
uint32_t Rbdb_ReplicationTimeoutSettingsController_waitTimeBeforeRetryElection( Rbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
	
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

void Rbdb_ReplicationTimeoutSettingsController_setWaitTimeBeforeRetryElection(	Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																				uint32_t										wait_time_before_retry_election )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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
uint32_t Rbdb_ReplicationTimeoutSettingsController_fullElectionParticipationTimeout( Rbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
	
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

void Rbdb_ReplicationTimeoutSettingsController_setFullElectionParticipationTimeout(	Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																						uint32_t										full_election_participation_timeout )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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
uint32_t Rbdb_ReplicationTimeoutSettingsController_heartbeatMonitorPulse( Rbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
	
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

void Rbdb_ReplicationTimeoutSettingsController_setHeartbeatMonitorPulse(	Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																			uint32_t										heartbeat_monitor_pulse )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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
uint32_t Rbdb_ReplicationTimeoutSettingsController_heartbeatBroadcastPulse( Rbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
	
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

void Rbdb_ReplicationTimeoutSettingsController_setHeartbeatBroadcastPulse(	Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																			uint32_t										heartbeat_broadcast_pulse )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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
uint32_t Rbdb_ReplicationTimeoutSettingsController_leaseTimeout( Rbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
	
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

void Rbdb_ReplicationTimeoutSettingsController_setLeaseTimeout( Rbdb_ReplicationTimeoutSettingsController*	replication_timeout_settings_controller,
																uint32_t										lease_timeout )	{

	Rbdb_Environment*	environment = replication_timeout_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;

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
Rbdb_ReplicationTimeoutSettingsController* Rbdb_ReplicationTimeoutSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller )	{

	Rbdb_ReplicationTimeoutSettingsController* replication_timeout_settings_controller_copy	=	Rbdb_ReplicationTimeoutSettingsController_new( replication_timeout_settings_controller->parent_replication_settings_controller );

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

