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

#include "ReplicationSettingsController.h"

#include "Environment.h"

#include "Record.h"

#include "ReplicationController.h"

#include "ReplicationSettingsController_internal.h"
#include "ReplicationElectionSettingsController.h"
#include "ReplicationTimeoutSettingsController.h"
#include "ReplicationVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_ReplicationSettingsController* RPbdb_ReplicationSettingsController_new( RPbdb_SettingsController* settings_controller )	{

	RPbdb_ReplicationSettingsController*		replication_settings_controller = calloc( 1, sizeof( RPbdb_ReplicationSettingsController ) );

	replication_settings_controller->parent_settings_controller = settings_controller;

	return replication_settings_controller;
}


/***************************
*  free  *
***************************/
void RPbdb_ReplicationSettingsController_free(	RPbdb_ReplicationSettingsController** replication_settings_controller )	{

	if ( ( *replication_settings_controller )->additional_start_information != NULL )	{
		RPbdb_Record_free( & ( ( *replication_settings_controller )->additional_start_information ) );
	}
	if ( ( *replication_settings_controller )->timeout_settings_controller != NULL )	{
		RPbdb_ReplicationTimeoutSettingsController_free( & ( ( *replication_settings_controller )->timeout_settings_controller ) );
	}
	if ( ( *replication_settings_controller )->acknowledgement_policy_settings_controller != NULL )	{
		RPbdb_ReplicationElectionSettingsController_free( & ( ( *replication_settings_controller )->acknowledgement_policy_settings_controller ) );
	}
	
	free( *replication_settings_controller );
	*replication_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_ReplicationSettingsController_parentEnvironment(	RPbdb_ReplicationSettingsController* replication_settings_controller )	{
	return replication_settings_controller->parent_settings_controller->parent_environment;
}

/*********
*  on  *
*********/

//	DB_INIT_REP             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPbdb_ReplicationSettingsController_on( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->on == TRUE )	{
		return DB_INIT_REP;
	}
	return FALSE;
}

/*************
*  turnOn  *
*************/

void RPbdb_ReplicationSettingsController_turnOn( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	replication_settings_controller->on = TRUE;
}

/*************
*  off  *
*************/

BOOL RPbdb_ReplicationSettingsController_off( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  turnOff  *
*****************/

void RPbdb_ReplicationSettingsController_turnOff( RPbdb_ReplicationSettingsController* replication_settings_controller )	{
	replication_settings_controller->on = FALSE;
}


/*************
*  clientToClientSynchronization  *
*************/

//	Currently, the replication manager framework only supports a single client peer, and the last specified peer is used
int RPbdb_ReplicationSettingsController_clientToClientSynchronization( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->client_to_client_synchronization == TRUE )	{
		return DB_REPMGR_PEER;
	}
	return FALSE;
}

/*****************
*  turnClientToClientSynchronizationOn  *
*****************/

void RPbdb_ReplicationSettingsController_turnClientToClientSynchronizationOn( RPbdb_ReplicationSettingsController* replication_settings_controller )	{
	replication_settings_controller->client_to_client_synchronization = TRUE;
}

/*****************
*  turnClientToClientSynchronizationOff  *
*****************/

void RPbdb_ReplicationSettingsController_turnClientToClientSynchronizationOff( RPbdb_ReplicationSettingsController* replication_settings_controller )	{
	replication_settings_controller->client_to_client_synchronization = FALSE;
}

/*************************
*  singleBulkTransfer  *
*************************/

//	DB_REP_CONF_BULK				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_config.html
int RPbdb_ReplicationSettingsController_singleBulkTransfer( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->rep_get_config(	environment->wrapped_bdb_environment, 
																DB_REP_CONF_BULK, 
																(int*) &( replication_settings_controller->single_bulk_transfer ) );
	}
	return ( replication_settings_controller->single_bulk_transfer ? DB_REP_CONF_BULK : FALSE );
}

/*********************************
*  turnSingleBulkTransferOn  *
*********************************/

void RPbdb_ReplicationSettingsController_turnSingleBulkTransferOn( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_config(	environment->wrapped_bdb_environment, 
										DB_REP_CONF_BULK, 
										TRUE );
	}
	
	replication_settings_controller->single_bulk_transfer = TRUE;
}

/*********************************
*  turnSingleBulkTransferOff  *
*********************************/

void RPbdb_ReplicationSettingsController_turnSingleBulkTransferOff( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_config(	environment->wrapped_bdb_environment, 
										DB_REP_CONF_BULK, 
										FALSE );
	}
	
	replication_settings_controller->single_bulk_transfer = FALSE;
}

/*************************************
*  delayNewSyncUntilExplicitCall  *
*************************************/

//	DB_REP_CONF_DELAYCLIENT         http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_config.html
int RPbdb_ReplicationSettingsController_delayNewSyncUntilExplicitCall( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->rep_get_config(	environment->wrapped_bdb_environment, 
																DB_REP_CONF_DELAYCLIENT, 
																(int*) &( replication_settings_controller->delay_new_sync_until_explicit_call ) );
	}
	return ( replication_settings_controller->delay_new_sync_until_explicit_call ? DB_REP_CONF_DELAYCLIENT : FALSE );
}

/*********************************************
*  turnDelayNewSyncUntilExplicitCallOn  *
*********************************************/

void RPbdb_ReplicationSettingsController_turnDelayNewSyncUntilExplicitCallOn( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_config(	environment->wrapped_bdb_environment, 
																DB_REP_CONF_DELAYCLIENT, 
																TRUE );
	}
	
	replication_settings_controller->delay_new_sync_until_explicit_call = TRUE;
}

/*********************************************
*  turnDelayNewSyncUntilExplicitCallOff  *
*********************************************/

void RPbdb_ReplicationSettingsController_turnDelayNewSyncUntilExplicitCallOff( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_config(	environment->wrapped_bdb_environment, 
																DB_REP_CONF_DELAYCLIENT, 
																FALSE );
	}
	
	replication_settings_controller->delay_new_sync_until_explicit_call = FALSE;
}

/*************************
*  useMasterLeases  *
*************************/

//	DB_REP_CONF_LEASE               http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_config.html
int RPbdb_ReplicationSettingsController_useMasterLeases( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->rep_get_config(	environment->wrapped_bdb_environment, 
										DB_REP_CONF_LEASE, 
										(int*) &( replication_settings_controller->use_master_leases ) );
	}

	return ( replication_settings_controller->use_master_leases ? RPBDB_UNITIALIZED : FALSE );
}

/*****************************
*  turnUseMasterLeasesOn  *
*****************************/

void RPbdb_ReplicationSettingsController_turnUseMasterLeasesOn( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_config(	environment->wrapped_bdb_environment,
										DB_REP_CONF_LEASE,
										TRUE );
	}
	
	replication_settings_controller->use_master_leases = TRUE;
}

/*****************************
*  turnUseMasterLeasesOff  *
*****************************/

void RPbdb_ReplicationSettingsController_turnUseMasterLeasesOff( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_config(	environment->wrapped_bdb_environment, 
										DB_REP_CONF_LEASE,
										FALSE );
	}
	
	replication_settings_controller->use_master_leases = FALSE;
}

/*************************************
*  prohibitAutoInitForOldClients  *
*************************************/

//	DB_REP_CONF_NOAUTOINIT          http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_config.html
int RPbdb_ReplicationSettingsController_reinitializeOutdatedClients( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->rep_get_config(	environment->wrapped_bdb_environment,
										DB_REP_CONF_AUTOINIT, 
										(int*) &( replication_settings_controller->prohibit_auto_init_for_old_clients ) );
	}

	return ( replication_settings_controller->prohibit_auto_init_for_old_clients ? DB_REP_CONF_AUTOINIT : FALSE );
}

/*********************************************
*  turnProhibitAutoInitForOldClientsOn  *
*********************************************/

void RPbdb_ReplicationSettingsController_turnReinitializeOutdatedClientsOn( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_config(	environment->wrapped_bdb_environment, 
										DB_REP_CONF_AUTOINIT, 
										TRUE );
	}

	replication_settings_controller->prohibit_auto_init_for_old_clients = TRUE;
}

/*********************************************
*  turnProhibitAutoInitForOldClientsOff  *
*********************************************/

void RPbdb_ReplicationSettingsController_turnReinitializeOutdatedClientsOff( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_config(	environment->wrapped_bdb_environment, 
										DB_REP_CONF_AUTOINIT, 
										FALSE );
	}
	
	replication_settings_controller->prohibit_auto_init_for_old_clients = FALSE;
}

/*********************
*  prohibitWait  *
*********************/

//	DB_REP_CONF_NOWAIT              http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_config.html
int RPbdb_ReplicationSettingsController_prohibitWait( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_get_config(	environment->wrapped_bdb_environment, 
										DB_REP_CONF_NOWAIT, 
										(int*) &( replication_settings_controller->prohibit_wait ) );
	}

	return ( replication_settings_controller->prohibit_wait ? DB_REP_CONF_AUTOINIT : FALSE );
}

/*************************
*  turnProhibitWaitOn  *
*************************/

void RPbdb_ReplicationSettingsController_turnProhibitWaitOn( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->rep_set_config(	environment->wrapped_bdb_environment, 
																DB_REP_CONF_NOWAIT, 
																TRUE );
	}
	
	replication_settings_controller->prohibit_wait = TRUE;
}

/*****************************
*  turnProhibitWaitOff  *
*****************************/

void RPbdb_ReplicationSettingsController_turnProhibitWaitOff( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_config(	environment->wrapped_bdb_environment, 
										DB_REP_CONF_NOWAIT, 
										FALSE );
	}
	
	replication_settings_controller->prohibit_wait = FALSE;
}

/*****************************
*  requireStrictMajority  *
*****************************/

//	DB_REPMGR_CONF_2SITE_STRICT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_config.html
int RPbdb_ReplicationSettingsController_requireStrictMajority( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_get_config(	environment->wrapped_bdb_environment, 
										DB_REPMGR_CONF_2SITE_STRICT,
										(int*) &( replication_settings_controller->require_strict_majority ) );
	}

	return ( replication_settings_controller->require_strict_majority ? DB_REPMGR_CONF_2SITE_STRICT : FALSE );
}

/*************************************
*  turnRequireStrictMajorityOn  *
*************************************/

void RPbdb_ReplicationSettingsController_turnRequireStrictMajorityOn( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_config(	environment->wrapped_bdb_environment, 
										DB_REPMGR_CONF_2SITE_STRICT, 
										TRUE );
	}
	
	replication_settings_controller->require_strict_majority = TRUE;
}

/*************************************
*  turnRequireStrictMajorityOff  *
*************************************/

void RPbdb_ReplicationSettingsController_turnRequireStrictMajorityOff( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_config(	environment->wrapped_bdb_environment, 
										DB_REPMGR_CONF_2SITE_STRICT, 
										FALSE );
	}
	
	replication_settings_controller->require_strict_majority = FALSE;
}

/*****************
*  isMaster  *
*****************/

//	DB_REP_MASTER			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_start.html
int RPbdb_ReplicationSettingsController_isMaster( RPbdb_ReplicationSettingsController* replication_settings_controller )	{
	return ( replication_settings_controller->is_master ? DB_REP_MASTER : FALSE );
}

/*********************
*  setIsMaster  *
*********************/

void RPbdb_ReplicationSettingsController_setIsMaster( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	//	The additional_start_information parameter is an opaque data item that is sent over the communication infrastructure when the client 
	//	comes online (see Connecting to a new site for more information). If no such information is useful, additional_start_information should be NULL.
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_start(	environment->wrapped_bdb_environment, 
								replication_settings_controller->additional_start_information->data->wrapped_bdb_dbt, 
								DB_REP_MASTER );
	}
	
	replication_settings_controller->is_client = FALSE;
	replication_settings_controller->is_master = TRUE;
}

/*****************
*  isClient  *
*****************/

//	DB_REP_CLIENT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_start.html
int RPbdb_ReplicationSettingsController_isClient( RPbdb_ReplicationSettingsController* replication_settings_controller )	{
	return ( replication_settings_controller->is_client ? DB_REP_MASTER : FALSE );
}

/*********************
*  setIsClient  *
*********************/

void RPbdb_ReplicationSettingsController_setIsClient( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	//	The additional_start_information parameter is an opaque data item that is sent over the communication infrastructure when the client 
	//	comes online (see Connecting to a new site for more information). If no such information is useful, additional_start_information should be NULL.
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_start(	environment->wrapped_bdb_environment, 
																											replication_settings_controller->additional_start_information->data->wrapped_bdb_dbt, 
																											DB_REP_CLIENT );
	}
	
	replication_settings_controller->is_client = TRUE;
	replication_settings_controller->is_master = FALSE;
}

/*****************
*  startAsClientOrRallyElection  *
*****************/

int RPbdb_ReplicationSettingsController_startAsClientOrRallyElection( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	return ( replication_settings_controller->start_as_client_or_rally_election ? DB_REP_ELECTION : FALSE );
}

/*****************
*  setStartAsClientOrRallyElection  *
*****************/

//	DB_REP_ELECTION		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_start.html
void RPbdb_ReplicationSettingsController_setStartAsClientOrRallyElection( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	replication_settings_controller->is_client = TRUE;
	replication_settings_controller->is_master = FALSE;

	//	The additional_start_information parameter is an opaque data item that is sent over the communication infrastructure when the client 
	//	comes online (see Connecting to a new site for more information). If no such information is useful, additional_start_information should be NULL.
	if ( environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->rep_start(	environment->wrapped_bdb_environment, 
								replication_settings_controller->additional_start_information->data->wrapped_bdb_dbt, 
								DB_REP_ELECTION );
	}
	
	//	Presumably once we start we need to get election results to update client/master settings

	replication_settings_controller->start_as_client_or_rally_election = DB_REP_ELECTION;
}

/*************
*  limit  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_limit.html
double RPbdb_ReplicationSettingsController_limit( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	uint32_t	gigabytes, bytes;

	uint32_t	bytes_in_gigabyte	=	( 1024 * 1024 * 1024 );

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_get_limit(	environment->wrapped_bdb_environment, 
																													& gigabytes, 
																													& bytes );

		replication_settings_controller->limit_in_gbytes = gigabytes;
		replication_settings_controller->limit_in_bytes			= bytes;
	}
	
	double	total_bytes	=	( replication_settings_controller->limit_in_gbytes * bytes_in_gigabyte )
											+ replication_settings_controller->limit_in_bytes;

	return total_bytes;
}

/*****************
*  setLimit  *
*****************/

void RPbdb_ReplicationSettingsController_setLimit(	RPbdb_ReplicationSettingsController*	replication_settings_controller, 
																									uint64_t								limit_in_gbytes, 
																									uint64_t								limit_in_bytes )	{

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	uint32_t	bytes_in_gigabyte	=	( 1024 * 1024 * 1024 );
	uint32_t	byte_remainder		=	limit_in_bytes % bytes_in_gigabyte;
	uint32_t	total_gigabytes		=	limit_in_gbytes + ( ( limit_in_bytes - byte_remainder ) / bytes_in_gigabyte );

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->rep_set_limit(	environment->wrapped_bdb_environment, 
																													total_gigabytes, 
																													byte_remainder );
	}
	
	replication_settings_controller->limit_in_gbytes		= total_gigabytes;
	replication_settings_controller->limit_in_bytes				= byte_remainder;
}

/*************
*  host  *
*************/

char* RPbdb_ReplicationSettingsController_host( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	return replication_settings_controller->host;
}

/*****************
*  setHost  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_local_site.html
//	specifies the host identification string and port number for the local system.
void RPbdb_ReplicationSettingsController_setHost( RPbdb_ReplicationSettingsController* replication_settings_controller, char* host )	{

	replication_settings_controller->host = host;

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;
	
	if (	replication_settings_controller->host 
		&&	replication_settings_controller->port
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->repmgr_set_local_site( environment->wrapped_bdb_environment, 
											replication_settings_controller->host, 
											replication_settings_controller->port, 
											RPbdb_ReplicationSettingsController_internal_localSiteFlags( replication_settings_controller ) );
	}
}

/*************
*  port  *
*************/

u_int RPbdb_ReplicationSettingsController_port( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	return replication_settings_controller->port;
}

/*****************
*  setPort  *
*****************/

void RPbdb_ReplicationSettingsController_setPort(	RPbdb_ReplicationSettingsController*		replication_settings_controller,
																									u_int																	port )	{

	replication_settings_controller->port = port;

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;	

	if (	replication_settings_controller->host 
		&&	replication_settings_controller->port
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->repmgr_set_local_site( environment->wrapped_bdb_environment, 
																																	replication_settings_controller->host, 
																																	replication_settings_controller->port, 
																																	RPbdb_ReplicationSettingsController_internal_localSiteFlags( replication_settings_controller ) );
	}
}

/*****************
*  siteCount  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_nsites.html
uint32_t RPbdb_ReplicationSettingsController_siteCount( RPbdb_ReplicationSettingsController* replication_settings_controller )	{
	
	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if (	! replication_settings_controller->site_count
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_get_nsites(	environment->wrapped_bdb_environment, 
										&( replication_settings_controller->site_count ) );
	}

	return replication_settings_controller->site_count;
}

/*********************
*  setSiteCount  *
*********************/

void RPbdb_ReplicationSettingsController_setSiteCount(	RPbdb_ReplicationSettingsController*	replication_settings_controller, 
														uint32_t								site_count )	{

	replication_settings_controller->site_count = site_count;

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_nsites(	environment->wrapped_bdb_environment, 
										replication_settings_controller->site_count );
	}
}

/*****************************
*  priorityOrderNumber  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_priority.html
uint32_t RPbdb_ReplicationSettingsController_priorityOrderNumber( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( ! replication_settings_controller->priority_order_number )	{

		RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

		if ( environment->wrapped_bdb_environment != NULL )	{

			environment->wrapped_bdb_environment->rep_get_priority(	environment->wrapped_bdb_environment, 
											&( replication_settings_controller->priority_order_number ) );
		}
	}

	return replication_settings_controller->priority_order_number;
}

/*****************************
*  setPriorityOrderNumber  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_priority.html
void RPbdb_ReplicationSettingsController_setPriorityOrderNumber(	RPbdb_ReplicationSettingsController*	replication_settings_controller,
																	uint32_t								priority_order_number)	{

	replication_settings_controller->priority_order_number = priority_order_number;

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_priority(	environment->wrapped_bdb_environment, 
										replication_settings_controller->priority_order_number );
	}
}

/*************************************
*  retransmissionThresholdMinimum  *
*************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_request.html
uint32_t RPbdb_ReplicationSettingsController_retransmissionThresholdMinimum( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( ! replication_settings_controller->retransmission_threshold_minimum )	{

		RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

		if ( environment->wrapped_bdb_environment != NULL )	{

			environment->wrapped_bdb_environment->rep_get_request(	environment->wrapped_bdb_environment, 
											&( replication_settings_controller->retransmission_threshold_minimum ), 
											&( replication_settings_controller->retransmission_threshold_maximum ) );
		}
	}

	return replication_settings_controller->retransmission_threshold_minimum;
}

/*****************************************
*  setRetransmissionThresholdMinimum  *
*****************************************/

void RPbdb_ReplicationSettingsController_setRetransmissionThresholdMinimum(	RPbdb_ReplicationSettingsController*	replication_settings_controller, 
																			uint32_t								retransmission_threshold_minimum )	{

	replication_settings_controller->retransmission_threshold_minimum = retransmission_threshold_minimum;

	if ( replication_settings_controller->retransmission_threshold_minimum && replication_settings_controller->retransmission_threshold_maximum )	{

		RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

		if ( environment->wrapped_bdb_environment != NULL )	{

			environment->wrapped_bdb_environment->rep_set_request(	environment->wrapped_bdb_environment, 
											replication_settings_controller->retransmission_threshold_minimum, 
											replication_settings_controller->retransmission_threshold_maximum );
		}
	}
}

/*************************************
*  retransmissionThresholdMaximum  *
*************************************/

uint32_t RPbdb_ReplicationSettingsController_retransmissionThresholdMaximum( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( ! replication_settings_controller->retransmission_threshold_minimum )	{

		RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

		if ( environment->wrapped_bdb_environment != NULL )	{

			environment->wrapped_bdb_environment->rep_get_request(	environment->wrapped_bdb_environment, 
																	&( replication_settings_controller->retransmission_threshold_minimum ), 
																	&( replication_settings_controller->retransmission_threshold_maximum ) );
		}
	}

	return replication_settings_controller->retransmission_threshold_minimum;
}

/*****************************************
*  setRetransmissionThresholdMaximum  *
*****************************************/

void RPbdb_ReplicationSettingsController_setRetransmissionThresholdMaximum(	RPbdb_ReplicationSettingsController*	replication_settings_controller,
 																			uint32_t								retransmission_threshold_maximum )	{

	replication_settings_controller->retransmission_threshold_minimum = retransmission_threshold_maximum;

	if ( replication_settings_controller->retransmission_threshold_minimum && replication_settings_controller->retransmission_threshold_maximum )	{

		RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

		if ( environment->wrapped_bdb_environment != NULL )	{

			environment->wrapped_bdb_environment->rep_set_request(	environment->wrapped_bdb_environment, 
											replication_settings_controller->retransmission_threshold_minimum, 
											replication_settings_controller->retransmission_threshold_maximum );
		}
	}
}

/*************************
*  slowestClockValue  *
*************************/

uint32_t RPbdb_ReplicationSettingsController_slowestClockValue( RPbdb_ReplicationSettingsController* replication_settings_controller )	{
	
	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if (	! replication_settings_controller->slowest_clock_value
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_get_clockskew(	environment->wrapped_bdb_environment, 
										&( replication_settings_controller->slowest_clock_value ), 
										&( replication_settings_controller->fastest_clock_value ) );
	}

	return replication_settings_controller->slowest_clock_value;
}

/*****************************
*  setSlowestClockValue  *
*****************************/

void RPbdb_ReplicationSettingsController_setSlowestClockValue(	RPbdb_ReplicationSettingsController*		replication_settings_controller, 
																															uint32_t															slowest_clock_value )	{

	replication_settings_controller->slowest_clock_value = slowest_clock_value;

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;
	
	if (	replication_settings_controller->slowest_clock_value 
		&&	replication_settings_controller->fastest_clock_value
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_clockskew(	environment->wrapped_bdb_environment, 
																															replication_settings_controller->slowest_clock_value, 
																															replication_settings_controller->fastest_clock_value );
	}
}

/*****************************
*  fastestClockSkewValue  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_clockskew.html
uint32_t RPbdb_ReplicationSettingsController_fastestClockSkewValue( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_Environment*	environment = replication_settings_controller->parent_settings_controller->parent_environment;
	
	if (	! replication_settings_controller->fastest_clock_value
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_get_clockskew(	environment->wrapped_bdb_environment, 
																															&( replication_settings_controller->slowest_clock_value ), 
																															&( replication_settings_controller->fastest_clock_value ) );
	}

	return replication_settings_controller->fastest_clock_value;
}

/*********************************
*  setFastestClockSkewValue  *
*********************************/

void RPbdb_ReplicationSettingsController_setFastestClockSkewValue(	RPbdb_ReplicationSettingsController*		replication_settings_controller, 
																																	uint32_t															fastest_clock_value )	{

	replication_settings_controller->fastest_clock_value = fastest_clock_value;

	RPbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;
	
	if (	replication_settings_controller->slowest_clock_value 
		&&	replication_settings_controller->fastest_clock_value
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_clockskew(	environment->wrapped_bdb_environment, 
																															replication_settings_controller->slowest_clock_value, 
																															replication_settings_controller->fastest_clock_value );
	}
}

/*************************************************
*  acknowledgementPolicySettingsController  *
*************************************************/

RPbdb_ReplicationElectionSettingsController* RPbdb_ReplicationSettingsController_electionSettingsController( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->acknowledgement_policy_settings_controller == NULL )	{
	
		replication_settings_controller->acknowledgement_policy_settings_controller = RPbdb_ReplicationElectionSettingsController_new( replication_settings_controller );
	}

	return replication_settings_controller->acknowledgement_policy_settings_controller;
}

/*********************************
*  timeoutSettingsController  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
RPbdb_ReplicationTimeoutSettingsController* RPbdb_ReplicationSettingsController_timeoutSettingsController( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->timeout_settings_controller == NULL )	{
	
		replication_settings_controller->timeout_settings_controller = RPbdb_ReplicationTimeoutSettingsController_new( replication_settings_controller );
	}

	return replication_settings_controller->timeout_settings_controller;

}

/*
	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_transport.html
	int RPbdb_ReplicationSettingsController_transportCallbackFunction( RPbdb_ReplicationSettingsController* replication_settings_controller )	{
	
	}

	void RPbdb_ReplicationSettingsController_setTransportCallbackFunction( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	}
*/

/*****************
*  verbositySettingsController  *
*****************/

RPbdb_ReplicationVerbositySettingsController* RPbdb_ReplicationSettingsController_verbositySettingsController( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->verbosity_settings_controller == NULL )	{
		replication_settings_controller->verbosity_settings_controller = RPbdb_ReplicationVerbositySettingsController_new( replication_settings_controller );
	}
	return replication_settings_controller->verbosity_settings_controller;
}	

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************
*  startFlags  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_start.html
int RPbdb_ReplicationSettingsController_internal_startFlags( RPbdb_ReplicationSettingsController* replication_settings_controller )	{
	
	return	RPbdb_ReplicationSettingsController_isMaster( replication_settings_controller )
			|	RPbdb_ReplicationSettingsController_isClient( replication_settings_controller )
			|	RPbdb_ReplicationSettingsController_startAsClientOrRallyElection( replication_settings_controller );
}

/*********************
*  localSiteFlags  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_sync.html
int RPbdb_ReplicationSettingsController_internal_localSiteFlags( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	//	Flags currently unused - returns 0
	return RPbdb_ReplicationSettingsController_isClient( replication_settings_controller )
			|	RPbdb_ReplicationSettingsController_isMaster( replication_settings_controller );
}

/*****************
*  syncFlags  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_sync.html
int RPbdb_ReplicationSettingsController_internal_syncFlags( RPbdb_ReplicationSettingsController* replication_settings_controller __attribute__((unused)) )	{

	//	Flags currently unused - returns 0
	return RPBDB_NO_FLAGS;
}

/*************************
*  callElectionFlags  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_elect.html
int RPbdb_ReplicationSettingsController_internal_callElectionFlags( RPbdb_ReplicationSettingsController* replication_settings_controller __attribute__((unused)) )	{

	//	Flags currently unused - returns 0
	return RPBDB_NO_FLAGS;
}

/*************************
*  addRemoteSiteFlags  *
*************************/

int RPbdb_ReplicationSettingsController_internal_addRemoteSiteFlags( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	return RPbdb_ReplicationSettingsController_clientToClientSynchronization( replication_settings_controller );

}	

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_ReplicationSettingsController* RPbdb_ReplicationSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_ReplicationSettingsController* replication_settings_controller_copy	=	RPbdb_ReplicationSettingsController_new( replication_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	replication_settings_controller_copy->fastest_clock_value	=	replication_settings_controller->fastest_clock_value;
	replication_settings_controller_copy->single_bulk_transfer	=	replication_settings_controller->single_bulk_transfer;
	replication_settings_controller_copy->priority_order_number	=	replication_settings_controller->priority_order_number;
	replication_settings_controller_copy->site_count	=	replication_settings_controller->site_count;
	replication_settings_controller_copy->port	=	replication_settings_controller->port;
	replication_settings_controller_copy->limit_in_bytes	=	replication_settings_controller->limit_in_bytes;
	replication_settings_controller_copy->is_master	=	replication_settings_controller->is_master;
	replication_settings_controller_copy->prohibit_wait	=	replication_settings_controller->prohibit_wait;
	replication_settings_controller_copy->limit_in_gbytes	=	replication_settings_controller->limit_in_gbytes;
	replication_settings_controller_copy->is_client	=	replication_settings_controller->is_client;
	replication_settings_controller_copy->retransmission_threshold_maximum	=	replication_settings_controller->retransmission_threshold_maximum;
	replication_settings_controller_copy->prohibit_auto_init_for_old_clients	=	replication_settings_controller->prohibit_auto_init_for_old_clients;
	replication_settings_controller_copy->host	=	replication_settings_controller->host;
	replication_settings_controller_copy->start_as_client_or_rally_election	=	replication_settings_controller->start_as_client_or_rally_election;
	replication_settings_controller_copy->use_master_leases	=	replication_settings_controller->use_master_leases;
	replication_settings_controller_copy->retransmission_threshold_minimum	=	replication_settings_controller->retransmission_threshold_minimum;
	replication_settings_controller_copy->delay_new_sync_until_explicit_call	=	replication_settings_controller->delay_new_sync_until_explicit_call;
	replication_settings_controller_copy->on	=	replication_settings_controller->on;
	replication_settings_controller_copy->slowest_clock_value	=	replication_settings_controller->slowest_clock_value;
	replication_settings_controller_copy->require_strict_majority	=	replication_settings_controller->require_strict_majority;
	replication_settings_controller_copy->client_to_client_synchronization	=	replication_settings_controller->client_to_client_synchronization;

	return replication_settings_controller_copy;
}

