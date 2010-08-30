/*
 *		RPDB::ReplicationController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_ReplicationController.h"

#include "RPDB_RemoteSite.h"

#include "RPDB_Environment.h"

#include "RPDB_LogSequenceNumber.h"

#include "RPDB_Record.h"

#include "RPDB_SettingsController.h"
#include "RPDB_ReplicationSettingsController.h"
#include "RPDB_ReplicationSettingsController_internal.h"
#include "RPDB_ReplicationElectionSettingsController.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_ReplicationController* RPDB_ReplicationController_new( RPDB_Environment* environment )	{
	
	RPDB_ReplicationController*		replication_controller = calloc( 1, sizeof( RPDB_ReplicationController ) );

	replication_controller->parent_environment = environment;
	
	RPDB_ReplicationController_initReplicationID( replication_controller );

	return replication_controller;
}

/***************************
*  free  *
***************************/
void RPDB_ReplicationController_free(	RPDB_ReplicationController** replication_controller )	{

	free( *replication_controller );
	*replication_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_ReplicationSettingsController* RPDB_ReplicationController_settingsController(	RPDB_ReplicationController* replication_controller )	{
	return replication_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_ReplicationController_parentEnvironment(	RPDB_ReplicationController* replication_controller )	{
	return replication_controller->parent_environment;
}

/*************************
*  initReplicationID  *
*************************/

//	We need to keep a track of existing replication environments and assign each of them a unique ID
//	Each replication controller needs unique IDs for every environment with which it replicates;
//	multiple environmental replication controllers may have different unique IDs for the same remote environments.
//	So A may see B, C, D wheras B might refer to A, C, D as E, F, G. This is acceptable, but not required.
RPDB_ReplicationController* RPDB_ReplicationController_initReplicationID(	RPDB_ReplicationController*	replication_controller )	{

	return replication_controller;
}

/*************
*  start  *
*************/

//	In addition to specified message processing threads, the replication manager creates and manages a few of its own threads of control.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_start.html
RPDB_ReplicationController* RPDB_ReplicationController_start(	RPDB_ReplicationController*	replication_controller,
 																int								number_of_threads_for_message_processing	)	{
	
	RPDB_Environment*	environment	= replication_controller->parent_environment;
	
	environment->wrapped_bdb_environment->repmgr_start(	environment->wrapped_bdb_environment,
								number_of_threads_for_message_processing,
								RPDB_ReplicationSettingsController_internal_startFlags( RPDB_SettingsController_replicationSettingsController( RPDB_Environment_settingsController( environment ) ) ) );

	return replication_controller;
}

/*********************
*  processMessage  *
*********************/

//	If DB_ENV->rep_process_message method returns DB_REP_NOTPERM then the ret_lsnp parameter will contain the log sequence number 
//	of this permanent log message that could not be written to disk. If DB_ENV->rep_process_message method returns DB_REP_ISPERM 
//	then the ret_lsnp parameter will contain largest log sequence number of the permanent records that are now written to disk 
//	as a result of processing this message. In all other cases the value of ret_lsnp is undefined.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_message.html
void RPDB_ReplicationController_processMessage(	RPDB_ReplicationController*		replication_controller,
 													RPDB_Record*						control_record,
													RPDB_Record*						replication_record	)	{
	
	DB_ENV*	environment	= replication_controller->parent_environment->wrapped_bdb_environment;
	
	//	return_lsn will only be defined for DB_REP_ISPERM and DB_REP_NOTPERM
	RPDB_LogSequenceNumber*	return_lsn	= RPDB_LogSequenceNumber_new( NULL );
	
	switch (	environment->rep_process_message(	environment,
													control_record->data->wrapped_bdb_dbt,
													replication_record->data->wrapped_bdb_dbt,
													replication_controller->replication_environment_id,
													return_lsn->wrapped_bdb_log_sequence_number ) )	{

		//	The DB_ENV->rep_process_message method will return DB_REP_DUPMASTER if the replication group has more than one master. 
		//	The application should reconfigure itself as a client by calling the DB_ENV->rep_start method, and then call for an election by calling DB_ENV->rep_elect.
		case DB_REP_DUPMASTER:

			//	return_lsn is undefined in this case
			RPDB_LogSequenceNumber_free( & return_lsn );

			//	Reconfigure as client
			//	RPDB_ReplicationSettingsController_setIsClient()
			//	RPDB_ReplicationController_start() - how many threads? do we have to do anything special to re-start?
			
			//	Call callback method for additional processing of duplicate masters pre-election

			//	Call for election
			RPDB_ReplicationController_callElection( replication_controller );
			
			//	Call callback method for additional processing of duplicate masters post-election

			break;

		//	The DB_ENV->rep_process_message method will return DB_REP_HOLDELECTION if an election is needed. 
		//	The application should call for an election by calling DB_ENV->rep_elect.
		case DB_REP_HOLDELECTION:

			//	return_lsn is undefined in this case
			RPDB_LogSequenceNumber_free( & return_lsn );

			//	Call callback method for additional processing prior to election

			//	Call for election
			RPDB_ReplicationController_callElection( replication_controller );

			//	Call callback method for additional processing post election

			break;
			
		//	The DB_ENV->rep_process_message method will return DB_REP_IGNORE if this message cannot be processed. 
		//	This is an indication that this message is irrelevant to the current replication state (for example, an old message from a previous generation 
		//	arrives and is processed late).
		case DB_REP_IGNORE:

			//	return_lsn is undefined in this case
			RPDB_LogSequenceNumber_free( & return_lsn );
			
			//	Call callback method for processing for messages that are to be ignored
			
			break;
		
		//	The DB_ENV->rep_process_message method will return DB_REP_ISPERM if processing this message results in the processing of records that are permanent. 
		//	The maximum LSN of the permanent records stored is returned.
		case DB_REP_ISPERM:

//			RPDB_LogSequenceNumber*	lsn_for_largest_permanent_record_written = return_lsn;

			//	Call callback method for processing of messages relating to processing of permanent records

			break;
		
		//	The DB_ENV->rep_process_message method will return DB_REP_JOIN_FAILURE if a new master has been chosen but the client is unable to synchronize 
		//	with the new master (possibly because the client has been configured with the DB_REP_CONF_NOAUTOINIT flag to turn-off automatic internal initialization).
		case DB_REP_JOIN_FAILURE:

			//	return_lsn is undefined in this case
			RPDB_LogSequenceNumber_free( & return_lsn );

			//	Call callback method for post-election synchronization failure

			break;
		
		//	The DB_ENV->rep_process_message method will return DB_REP_NEWSITE if the system received contact information from a new environment. 
		//	The rec parameter contains the opaque data specified in the cdata parameter to the DB_ENV->rep_start. 
		//	The application should take whatever action is needed to establish a communication channel with this new environment.
		case DB_REP_NEWSITE:
	
			//	return_lsn is undefined in this case
			RPDB_LogSequenceNumber_free( & return_lsn );
		
			//	Call callback to establish communication channel with new environment
			
			break;

		//	The DB_ENV->rep_process_message method will return DB_REP_NOTPERM if a message carrying a DB_REP_PERMANENT flag was processed successfully, 
		//	but was not written to disk. The LSN of this record is returned. The application should take whatever action is deemed necessary 
		//	to retain its recoverability characteristics.
		case DB_REP_NOTPERM:
			
//			RPDB_LogSequenceNumber*	lsn_for_unwritable_permanent_record = return_lsn;
			
			//	Call callback to retain recoverability characteristics
			
			break;
			
		//	Otherwise, we have some sort of error
		default:
			
			//	return_lsn is undefined in this case
			RPDB_LogSequenceNumber_free( & return_lsn );
			
			//	Call error function to resolve the error
			
			break;
	}
}

/*************
*  sync  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_sync.html
void RPDB_ReplicationController_sync( RPDB_ReplicationController* replication_controller )	{

	RPDB_Environment*	environment	= replication_controller->parent_environment;

	environment->wrapped_bdb_environment->rep_sync(	environment->wrapped_bdb_environment,
							RPDB_ReplicationSettingsController_internal_syncFlags( RPDB_SettingsController_replicationSettingsController(RPDB_Environment_settingsController(environment)) ) );
}

/*********************
*  callElection  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_elect.html
void RPDB_ReplicationController_callElection( RPDB_ReplicationController* replication_controller )	{
	
	RPDB_Environment*	environment	= replication_controller->parent_environment;

	environment->wrapped_bdb_environment->rep_elect(	environment->wrapped_bdb_environment,
							RPDB_ReplicationElectionSettingsController_numberOfSitesRequiredForElection(
								RPDB_ReplicationSettingsController_electionSettingsController(
								RPDB_SettingsController_replicationSettingsController(
									RPDB_Environment_settingsController( environment ) ) ) ),
							RPDB_ReplicationElectionSettingsController_numberOfVotesRequiredForElection(
									 RPDB_ReplicationSettingsController_electionSettingsController(
										RPDB_SettingsController_replicationSettingsController(
											RPDB_Environment_settingsController( environment ) ) ) ),
							RPDB_ReplicationSettingsController_internal_callElectionFlags( RPDB_SettingsController_replicationSettingsController( RPDB_Environment_settingsController( environment ) ) ) );
}

/*********************
*  addRemoteSite  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_remote_site.html
RPDB_RemoteSite* RPDB_ReplicationController_addRemoteSite(	RPDB_ReplicationController*	replication_controller,
 																char*							remote_host,
																u_int							remote_port	)	{
	
	RPDB_Environment*	environment	= replication_controller->parent_environment;
	
	RPDB_RemoteSite*	remote_site	= RPDB_RemoteSite_new( replication_controller );
	
	remote_site->host	= remote_host;
	remote_site->port	= remote_port;
	
	environment->wrapped_bdb_environment->repmgr_add_remote_site(	environment->wrapped_bdb_environment,
											remote_site->host,
											remote_site->port,
											&( remote_site->replication_environment_id ),
											RPDB_ReplicationSettingsController_internal_addRemoteSiteFlags( RPDB_SettingsController_replicationSettingsController( RPDB_Environment_settingsController( environment ) ) ) );
	return remote_site;
}

/*****************
*  siteList  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_site_list.html
RPDB_RemoteSite** RPDB_ReplicationController_siteList( RPDB_ReplicationController* replication_controller )	{
	
	DB_ENV*				environment				= replication_controller->parent_environment->wrapped_bdb_environment;
	
	DB_REPMGR_SITE**	bdb_remote_site_list	=	NULL;

	u_int				site_iterator;
	
	environment->repmgr_site_list(	environment,
									&( replication_controller->site_count ),
									bdb_remote_site_list );
	
	replication_controller->remote_site_list	=	calloc(	replication_controller->site_count, sizeof( RPDB_RemoteSite ) );

	//	Copy information over to our RPDB structs
	for ( site_iterator = 0 ; site_iterator < replication_controller->site_count ; site_iterator++ )	{
		
		//	Temporary pointers inside our arrays
		RPDB_RemoteSite*	this_remote_site			= replication_controller->remote_site_list[		site_iterator ];
		DB_REPMGR_SITE*		this_bdb_remote_site		= bdb_remote_site_list[	site_iterator ];
		
		this_remote_site->replication_environment_id	=	this_bdb_remote_site->eid;
		this_remote_site->host							=	this_bdb_remote_site->host;
		this_remote_site->port							=	this_bdb_remote_site->port;
		//	Assumes that status options are either DB_REPMGR_CONNECTED or DB_REPMGR_DISCONNECTED
		this_remote_site->connected						=	( this_bdb_remote_site->port == DB_REPMGR_CONNECTED ?	TRUE : FALSE );
	}
						
	return replication_controller->remote_site_list;
}




