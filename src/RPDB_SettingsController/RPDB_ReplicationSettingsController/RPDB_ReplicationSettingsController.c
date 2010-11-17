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

#include "RPDB_ReplicationSettingsController.h"

#include "RPDB_Environment.h"

#include "RPDB_Record.h"

#include "RPDB_ReplicationController.h"

#include "RPDB_ReplicationSettingsController_internal.h"
#include "RPDB_ReplicationElectionSettingsController.h"
#include "RPDB_ReplicationTimeoutSettingsController.h"
#include "RPDB_ReplicationVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_ReplicationSettingsController* RPDB_ReplicationSettingsController_new( RPDB_SettingsController* settings_controller )	{

	RPDB_ReplicationSettingsController*		replication_settings_controller = calloc( 1, sizeof( RPDB_ReplicationSettingsController ) );

	replication_settings_controller->parent_settings_controller = settings_controller;

	return replication_settings_controller;
}


/***************************
*  free  *
***************************/
void RPDB_ReplicationSettingsController_free(	RPDB_ReplicationSettingsController** replication_settings_controller )	{

	if ( ( *replication_settings_controller )->additional_start_information != NULL )	{
		RPDB_Record_free( & ( ( *replication_settings_controller )->additional_start_information ) );
	}
	if ( ( *replication_settings_controller )->timeout_settings_controller != NULL )	{
		RPDB_ReplicationTimeoutSettingsController_free( & ( ( *replication_settings_controller )->timeout_settings_controller ) );
	}
	if ( ( *replication_settings_controller )->acknowledgement_policy_settings_controller != NULL )	{
		RPDB_ReplicationElectionSettingsController_free( & ( ( *replication_settings_controller )->acknowledgement_policy_settings_controller ) );
	}
	
	free( *replication_settings_controller );
	*replication_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_ReplicationSettingsController_parentEnvironment(	RPDB_ReplicationSettingsController* replication_settings_controller )	{
	return replication_settings_controller->parent_settings_controller->parent_environment;
}

/*********
*  on  *
*********/

//	DB_INIT_REP             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPDB_ReplicationSettingsController_on( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->on == TRUE )	{
		return DB_INIT_REP;
	}
	return FALSE;
}

/*************
*  turnOn  *
*************/

void RPDB_ReplicationSettingsController_turnOn( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	replication_settings_controller->on = TRUE;
}

/*************
*  off  *
*************/

BOOL RPDB_ReplicationSettingsController_off( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  turnOff  *
*****************/

void RPDB_ReplicationSettingsController_turnOff( RPDB_ReplicationSettingsController* replication_settings_controller )	{
	replication_settings_controller->on = FALSE;
}


/*************
*  clientToClientSynchronization  *
*************/

//	Currently, the replication manager framework only supports a single client peer, and the last specified peer is used
int RPDB_ReplicationSettingsController_clientToClientSynchronization( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->client_to_client_synchronization == TRUE )	{
		return DB_REPMGR_PEER;
	}
	return FALSE;
}

/*****************
*  turnClientToClientSynchronizationOn  *
*****************/

void RPDB_ReplicationSettingsController_turnClientToClientSynchronizationOn( RPDB_ReplicationSettingsController* replication_settings_controller )	{
	replication_settings_controller->client_to_client_synchronization = TRUE;
}

/*****************
*  turnClientToClientSynchronizationOff  *
*****************/

void RPDB_ReplicationSettingsController_turnClientToClientSynchronizationOff( RPDB_ReplicationSettingsController* replication_settings_controller )	{
	replication_settings_controller->client_to_client_synchronization = FALSE;
}

/*************************
*  singleBulkTransfer  *
*************************/

//	DB_REP_CONF_BULK				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_config.html
int RPDB_ReplicationSettingsController_singleBulkTransfer( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_turnSingleBulkTransferOn( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_turnSingleBulkTransferOff( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int RPDB_ReplicationSettingsController_delayNewSyncUntilExplicitCall( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_turnDelayNewSyncUntilExplicitCallOn( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_turnDelayNewSyncUntilExplicitCallOff( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int RPDB_ReplicationSettingsController_useMasterLeases( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->rep_get_config(	environment->wrapped_bdb_environment, 
										DB_REP_CONF_LEASE, 
										(int*) &( replication_settings_controller->use_master_leases ) );
	}

	return ( replication_settings_controller->use_master_leases ? RPDB_UNITIALIZED : FALSE );
}

/*****************************
*  turnUseMasterLeasesOn  *
*****************************/

void RPDB_ReplicationSettingsController_turnUseMasterLeasesOn( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_turnUseMasterLeasesOff( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int RPDB_ReplicationSettingsController_reinitializeOutdatedClients( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_turnReinitializeOutdatedClientsOn( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_turnReinitializeOutdatedClientsOff( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int RPDB_ReplicationSettingsController_prohibitWait( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_turnProhibitWaitOn( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_turnProhibitWaitOff( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int RPDB_ReplicationSettingsController_requireStrictMajority( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_turnRequireStrictMajorityOn( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_turnRequireStrictMajorityOff( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int RPDB_ReplicationSettingsController_isMaster( RPDB_ReplicationSettingsController* replication_settings_controller )	{
	return ( replication_settings_controller->is_master ? DB_REP_MASTER : FALSE );
}

/*********************
*  setIsMaster  *
*********************/

void RPDB_ReplicationSettingsController_setIsMaster( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int RPDB_ReplicationSettingsController_isClient( RPDB_ReplicationSettingsController* replication_settings_controller )	{
	return ( replication_settings_controller->is_client ? DB_REP_MASTER : FALSE );
}

/*********************
*  setIsClient  *
*********************/

void RPDB_ReplicationSettingsController_setIsClient( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

int RPDB_ReplicationSettingsController_startAsClientOrRallyElection( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	return ( replication_settings_controller->start_as_client_or_rally_election ? DB_REP_ELECTION : FALSE );
}

/*****************
*  setStartAsClientOrRallyElection  *
*****************/

//	DB_REP_ELECTION		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_start.html
void RPDB_ReplicationSettingsController_setStartAsClientOrRallyElection( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
double RPDB_ReplicationSettingsController_limit( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_setLimit(	RPDB_ReplicationSettingsController*	replication_settings_controller, 
																									uint64_t								limit_in_gbytes, 
																									uint64_t								limit_in_bytes )	{

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

char* RPDB_ReplicationSettingsController_host( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	return replication_settings_controller->host;
}

/*****************
*  setHost  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_local_site.html
//	specifies the host identification string and port number for the local system.
void RPDB_ReplicationSettingsController_setHost( RPDB_ReplicationSettingsController* replication_settings_controller, char* host )	{

	replication_settings_controller->host = host;

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;
	
	if (	replication_settings_controller->host 
		&&	replication_settings_controller->port
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->repmgr_set_local_site( environment->wrapped_bdb_environment, 
											replication_settings_controller->host, 
											replication_settings_controller->port, 
											RPDB_ReplicationSettingsController_internal_localSiteFlags( replication_settings_controller ) );
	}
}

/*************
*  port  *
*************/

u_int RPDB_ReplicationSettingsController_port( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	return replication_settings_controller->port;
}

/*****************
*  setPort  *
*****************/

void RPDB_ReplicationSettingsController_setPort(	RPDB_ReplicationSettingsController*		replication_settings_controller,
																									u_int																	port )	{

	replication_settings_controller->port = port;

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;	

	if (	replication_settings_controller->host 
		&&	replication_settings_controller->port
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->repmgr_set_local_site( environment->wrapped_bdb_environment, 
																																	replication_settings_controller->host, 
																																	replication_settings_controller->port, 
																																	RPDB_ReplicationSettingsController_internal_localSiteFlags( replication_settings_controller ) );
	}
}

/*****************
*  siteCount  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_nsites.html
uint32_t RPDB_ReplicationSettingsController_siteCount( RPDB_ReplicationSettingsController* replication_settings_controller )	{
	
	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_setSiteCount(	RPDB_ReplicationSettingsController*	replication_settings_controller, 
														uint32_t								site_count )	{

	replication_settings_controller->site_count = site_count;

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_nsites(	environment->wrapped_bdb_environment, 
										replication_settings_controller->site_count );
	}
}

/*****************************
*  priorityOrderNumber  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_priority.html
uint32_t RPDB_ReplicationSettingsController_priorityOrderNumber( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	if ( ! replication_settings_controller->priority_order_number )	{

		RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
void RPDB_ReplicationSettingsController_setPriorityOrderNumber(	RPDB_ReplicationSettingsController*	replication_settings_controller,
																	uint32_t								priority_order_number)	{

	replication_settings_controller->priority_order_number = priority_order_number;

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_priority(	environment->wrapped_bdb_environment, 
										replication_settings_controller->priority_order_number );
	}
}

/*************************************
*  retransmissionThresholdMinimum  *
*************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_request.html
uint32_t RPDB_ReplicationSettingsController_retransmissionThresholdMinimum( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	if ( ! replication_settings_controller->retransmission_threshold_minimum )	{

		RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_setRetransmissionThresholdMinimum(	RPDB_ReplicationSettingsController*	replication_settings_controller, 
																			uint32_t								retransmission_threshold_minimum )	{

	replication_settings_controller->retransmission_threshold_minimum = retransmission_threshold_minimum;

	if ( replication_settings_controller->retransmission_threshold_minimum && replication_settings_controller->retransmission_threshold_maximum )	{

		RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

uint32_t RPDB_ReplicationSettingsController_retransmissionThresholdMaximum( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	if ( ! replication_settings_controller->retransmission_threshold_minimum )	{

		RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_setRetransmissionThresholdMaximum(	RPDB_ReplicationSettingsController*	replication_settings_controller,
 																			uint32_t								retransmission_threshold_maximum )	{

	replication_settings_controller->retransmission_threshold_minimum = retransmission_threshold_maximum;

	if ( replication_settings_controller->retransmission_threshold_minimum && replication_settings_controller->retransmission_threshold_maximum )	{

		RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

uint32_t RPDB_ReplicationSettingsController_slowestClockValue( RPDB_ReplicationSettingsController* replication_settings_controller )	{
	
	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_ReplicationSettingsController_setSlowestClockValue(	RPDB_ReplicationSettingsController*		replication_settings_controller, 
																															uint32_t															slowest_clock_value )	{

	replication_settings_controller->slowest_clock_value = slowest_clock_value;

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;
	
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
uint32_t RPDB_ReplicationSettingsController_fastestClockSkewValue( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_Environment*	environment = replication_settings_controller->parent_settings_controller->parent_environment;
	
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

void RPDB_ReplicationSettingsController_setFastestClockSkewValue(	RPDB_ReplicationSettingsController*		replication_settings_controller, 
																																	uint32_t															fastest_clock_value )	{

	replication_settings_controller->fastest_clock_value = fastest_clock_value;

	RPDB_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;
	
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

RPDB_ReplicationElectionSettingsController* RPDB_ReplicationSettingsController_electionSettingsController( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->acknowledgement_policy_settings_controller == NULL )	{
	
		replication_settings_controller->acknowledgement_policy_settings_controller = RPDB_ReplicationElectionSettingsController_new( replication_settings_controller );
	}

	return replication_settings_controller->acknowledgement_policy_settings_controller;
}

/*********************************
*  timeoutSettingsController  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
RPDB_ReplicationTimeoutSettingsController* RPDB_ReplicationSettingsController_timeoutSettingsController( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->timeout_settings_controller == NULL )	{
	
		replication_settings_controller->timeout_settings_controller = RPDB_ReplicationTimeoutSettingsController_new( replication_settings_controller );
	}

	return replication_settings_controller->timeout_settings_controller;

}

/*
	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_transport.html
	int RPDB_ReplicationSettingsController_transportCallbackFunction( RPDB_ReplicationSettingsController* replication_settings_controller )	{
	
	}

	void RPDB_ReplicationSettingsController_setTransportCallbackFunction( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	}
*/

/*****************
*  verbositySettingsController  *
*****************/

RPDB_ReplicationVerbositySettingsController* RPDB_ReplicationSettingsController_verbositySettingsController( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->verbosity_settings_controller == NULL )	{
		replication_settings_controller->verbosity_settings_controller = RPDB_ReplicationVerbositySettingsController_new( replication_settings_controller );
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
int RPDB_ReplicationSettingsController_internal_startFlags( RPDB_ReplicationSettingsController* replication_settings_controller )	{
	
	return	RPDB_ReplicationSettingsController_isMaster( replication_settings_controller )
			|	RPDB_ReplicationSettingsController_isClient( replication_settings_controller )
			|	RPDB_ReplicationSettingsController_startAsClientOrRallyElection( replication_settings_controller );
}

/*********************
*  localSiteFlags  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_sync.html
int RPDB_ReplicationSettingsController_internal_localSiteFlags( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	//	Flags currently unused - returns 0
	return RPDB_ReplicationSettingsController_isClient( replication_settings_controller )
			|	RPDB_ReplicationSettingsController_isMaster( replication_settings_controller );
}

/*****************
*  syncFlags  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_sync.html
int RPDB_ReplicationSettingsController_internal_syncFlags( RPDB_ReplicationSettingsController* replication_settings_controller __attribute__((unused)) )	{

	//	Flags currently unused - returns 0
	return RPDB_NO_FLAGS;
}

/*************************
*  callElectionFlags  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_elect.html
int RPDB_ReplicationSettingsController_internal_callElectionFlags( RPDB_ReplicationSettingsController* replication_settings_controller __attribute__((unused)) )	{

	//	Flags currently unused - returns 0
	return RPDB_NO_FLAGS;
}

/*************************
*  addRemoteSiteFlags  *
*************************/

int RPDB_ReplicationSettingsController_internal_addRemoteSiteFlags( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	return RPDB_ReplicationSettingsController_clientToClientSynchronization( replication_settings_controller );

}	

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_ReplicationSettingsController* RPDB_ReplicationSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_ReplicationSettingsController* replication_settings_controller_copy	=	RPDB_ReplicationSettingsController_new( replication_settings_controller->parent_settings_controller );

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

