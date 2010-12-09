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

#include "Rbdb_ReplicationSettingsController.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Record.h"

#include "Rbdb_ReplicationController.h"

#include "Rbdb_ReplicationSettingsController_internal.h"
#include "Rbdb_ReplicationElectionSettingsController.h"
#include "Rbdb_ReplicationTimeoutSettingsController.h"
#include "Rbdb_ReplicationVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_ReplicationSettingsController* Rbdb_ReplicationSettingsController_new( Rbdb_SettingsController* settings_controller )	{

	Rbdb_ReplicationSettingsController*		replication_settings_controller = calloc( 1, sizeof( Rbdb_ReplicationSettingsController ) );

	replication_settings_controller->parent_settings_controller = settings_controller;

	return replication_settings_controller;
}


/***************************
*  free  *
***************************/
void Rbdb_ReplicationSettingsController_free(	Rbdb_ReplicationSettingsController** replication_settings_controller )	{

	if ( ( *replication_settings_controller )->additional_start_information != NULL )	{
		Rbdb_Record_free( & ( ( *replication_settings_controller )->additional_start_information ) );
	}
	if ( ( *replication_settings_controller )->timeout_settings_controller != NULL )	{
		Rbdb_ReplicationTimeoutSettingsController_free( & ( ( *replication_settings_controller )->timeout_settings_controller ) );
	}
	if ( ( *replication_settings_controller )->acknowledgement_policy_settings_controller != NULL )	{
		Rbdb_ReplicationElectionSettingsController_free( & ( ( *replication_settings_controller )->acknowledgement_policy_settings_controller ) );
	}
	
	free( *replication_settings_controller );
	*replication_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_ReplicationSettingsController_parentEnvironment(	Rbdb_ReplicationSettingsController* replication_settings_controller )	{
	return replication_settings_controller->parent_settings_controller->parent_environment;
}

/*********
*  on  *
*********/

//	DB_INIT_REP             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int Rbdb_ReplicationSettingsController_on( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->on == TRUE )	{
		return DB_INIT_REP;
	}
	return FALSE;
}

/*************
*  turnOn  *
*************/

void Rbdb_ReplicationSettingsController_turnOn( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	replication_settings_controller->on = TRUE;
}

/*************
*  off  *
*************/

BOOL Rbdb_ReplicationSettingsController_off( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  turnOff  *
*****************/

void Rbdb_ReplicationSettingsController_turnOff( Rbdb_ReplicationSettingsController* replication_settings_controller )	{
	replication_settings_controller->on = FALSE;
}


/*************
*  clientToClientSynchronization  *
*************/

//	Currently, the replication manager framework only supports a single client peer, and the last specified peer is used
int Rbdb_ReplicationSettingsController_clientToClientSynchronization( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->client_to_client_synchronization == TRUE )	{
		return DB_REPMGR_PEER;
	}
	return FALSE;
}

/*****************
*  turnClientToClientSynchronizationOn  *
*****************/

void Rbdb_ReplicationSettingsController_turnClientToClientSynchronizationOn( Rbdb_ReplicationSettingsController* replication_settings_controller )	{
	replication_settings_controller->client_to_client_synchronization = TRUE;
}

/*****************
*  turnClientToClientSynchronizationOff  *
*****************/

void Rbdb_ReplicationSettingsController_turnClientToClientSynchronizationOff( Rbdb_ReplicationSettingsController* replication_settings_controller )	{
	replication_settings_controller->client_to_client_synchronization = FALSE;
}

/*************************
*  singleBulkTransfer  *
*************************/

//	DB_REP_CONF_BULK				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_config.html
int Rbdb_ReplicationSettingsController_singleBulkTransfer( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_turnSingleBulkTransferOn( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_turnSingleBulkTransferOff( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int Rbdb_ReplicationSettingsController_delayNewSyncUntilExplicitCall( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_turnDelayNewSyncUntilExplicitCallOn( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_turnDelayNewSyncUntilExplicitCallOff( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int Rbdb_ReplicationSettingsController_useMasterLeases( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->rep_get_config(	environment->wrapped_bdb_environment, 
										DB_REP_CONF_LEASE, 
										(int*) &( replication_settings_controller->use_master_leases ) );
	}

	return ( replication_settings_controller->use_master_leases ? Rbdb_UNITIALIZED : FALSE );
}

/*****************************
*  turnUseMasterLeasesOn  *
*****************************/

void Rbdb_ReplicationSettingsController_turnUseMasterLeasesOn( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_turnUseMasterLeasesOff( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int Rbdb_ReplicationSettingsController_reinitializeOutdatedClients( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_turnReinitializeOutdatedClientsOn( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_turnReinitializeOutdatedClientsOff( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int Rbdb_ReplicationSettingsController_prohibitWait( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_turnProhibitWaitOn( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_turnProhibitWaitOff( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int Rbdb_ReplicationSettingsController_requireStrictMajority( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_turnRequireStrictMajorityOn( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_turnRequireStrictMajorityOff( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int Rbdb_ReplicationSettingsController_isMaster( Rbdb_ReplicationSettingsController* replication_settings_controller )	{
	return ( replication_settings_controller->is_master ? DB_REP_MASTER : FALSE );
}

/*********************
*  setIsMaster  *
*********************/

void Rbdb_ReplicationSettingsController_setIsMaster( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
int Rbdb_ReplicationSettingsController_isClient( Rbdb_ReplicationSettingsController* replication_settings_controller )	{
	return ( replication_settings_controller->is_client ? DB_REP_MASTER : FALSE );
}

/*********************
*  setIsClient  *
*********************/

void Rbdb_ReplicationSettingsController_setIsClient( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

int Rbdb_ReplicationSettingsController_startAsClientOrRallyElection( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	return ( replication_settings_controller->start_as_client_or_rally_election ? DB_REP_ELECTION : FALSE );
}

/*****************
*  setStartAsClientOrRallyElection  *
*****************/

//	DB_REP_ELECTION		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_start.html
void Rbdb_ReplicationSettingsController_setStartAsClientOrRallyElection( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
double Rbdb_ReplicationSettingsController_limit( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_setLimit(	Rbdb_ReplicationSettingsController*	replication_settings_controller, 
																									uint64_t								limit_in_gbytes, 
																									uint64_t								limit_in_bytes )	{

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

char* Rbdb_ReplicationSettingsController_host( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	return replication_settings_controller->host;
}

/*****************
*  setHost  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_local_site.html
//	specifies the host identification string and port number for the local system.
void Rbdb_ReplicationSettingsController_setHost( Rbdb_ReplicationSettingsController* replication_settings_controller, char* host )	{

	replication_settings_controller->host = host;

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;
	
	if (	replication_settings_controller->host 
		&&	replication_settings_controller->port
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->repmgr_set_local_site( environment->wrapped_bdb_environment, 
											replication_settings_controller->host, 
											replication_settings_controller->port, 
											Rbdb_ReplicationSettingsController_internal_localSiteFlags( replication_settings_controller ) );
	}
}

/*************
*  port  *
*************/

u_int Rbdb_ReplicationSettingsController_port( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	return replication_settings_controller->port;
}

/*****************
*  setPort  *
*****************/

void Rbdb_ReplicationSettingsController_setPort(	Rbdb_ReplicationSettingsController*		replication_settings_controller,
																									u_int																	port )	{

	replication_settings_controller->port = port;

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;	

	if (	replication_settings_controller->host 
		&&	replication_settings_controller->port
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->repmgr_set_local_site( environment->wrapped_bdb_environment, 
																																	replication_settings_controller->host, 
																																	replication_settings_controller->port, 
																																	Rbdb_ReplicationSettingsController_internal_localSiteFlags( replication_settings_controller ) );
	}
}

/*****************
*  siteCount  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_nsites.html
uint32_t Rbdb_ReplicationSettingsController_siteCount( Rbdb_ReplicationSettingsController* replication_settings_controller )	{
	
	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_setSiteCount(	Rbdb_ReplicationSettingsController*	replication_settings_controller, 
														uint32_t								site_count )	{

	replication_settings_controller->site_count = site_count;

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_nsites(	environment->wrapped_bdb_environment, 
										replication_settings_controller->site_count );
	}
}

/*****************************
*  priorityOrderNumber  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_priority.html
uint32_t Rbdb_ReplicationSettingsController_priorityOrderNumber( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( ! replication_settings_controller->priority_order_number )	{

		Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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
void Rbdb_ReplicationSettingsController_setPriorityOrderNumber(	Rbdb_ReplicationSettingsController*	replication_settings_controller,
																	uint32_t								priority_order_number)	{

	replication_settings_controller->priority_order_number = priority_order_number;

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->rep_set_priority(	environment->wrapped_bdb_environment, 
										replication_settings_controller->priority_order_number );
	}
}

/*************************************
*  retransmissionThresholdMinimum  *
*************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_request.html
uint32_t Rbdb_ReplicationSettingsController_retransmissionThresholdMinimum( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( ! replication_settings_controller->retransmission_threshold_minimum )	{

		Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_setRetransmissionThresholdMinimum(	Rbdb_ReplicationSettingsController*	replication_settings_controller, 
																			uint32_t								retransmission_threshold_minimum )	{

	replication_settings_controller->retransmission_threshold_minimum = retransmission_threshold_minimum;

	if ( replication_settings_controller->retransmission_threshold_minimum && replication_settings_controller->retransmission_threshold_maximum )	{

		Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

uint32_t Rbdb_ReplicationSettingsController_retransmissionThresholdMaximum( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( ! replication_settings_controller->retransmission_threshold_minimum )	{

		Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_setRetransmissionThresholdMaximum(	Rbdb_ReplicationSettingsController*	replication_settings_controller,
 																			uint32_t								retransmission_threshold_maximum )	{

	replication_settings_controller->retransmission_threshold_minimum = retransmission_threshold_maximum;

	if ( replication_settings_controller->retransmission_threshold_minimum && replication_settings_controller->retransmission_threshold_maximum )	{

		Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

uint32_t Rbdb_ReplicationSettingsController_slowestClockValue( Rbdb_ReplicationSettingsController* replication_settings_controller )	{
	
	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;

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

void Rbdb_ReplicationSettingsController_setSlowestClockValue(	Rbdb_ReplicationSettingsController*		replication_settings_controller, 
																															uint32_t															slowest_clock_value )	{

	replication_settings_controller->slowest_clock_value = slowest_clock_value;

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;
	
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
uint32_t Rbdb_ReplicationSettingsController_fastestClockSkewValue( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_Environment*	environment = replication_settings_controller->parent_settings_controller->parent_environment;
	
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

void Rbdb_ReplicationSettingsController_setFastestClockSkewValue(	Rbdb_ReplicationSettingsController*		replication_settings_controller, 
																																	uint32_t															fastest_clock_value )	{

	replication_settings_controller->fastest_clock_value = fastest_clock_value;

	Rbdb_Environment*		environment = replication_settings_controller->parent_settings_controller->parent_environment;
	
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

Rbdb_ReplicationElectionSettingsController* Rbdb_ReplicationSettingsController_electionSettingsController( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->acknowledgement_policy_settings_controller == NULL )	{
	
		replication_settings_controller->acknowledgement_policy_settings_controller = Rbdb_ReplicationElectionSettingsController_new( replication_settings_controller );
	}

	return replication_settings_controller->acknowledgement_policy_settings_controller;
}

/*********************************
*  timeoutSettingsController  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_timeout.html
Rbdb_ReplicationTimeoutSettingsController* Rbdb_ReplicationSettingsController_timeoutSettingsController( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->timeout_settings_controller == NULL )	{
	
		replication_settings_controller->timeout_settings_controller = Rbdb_ReplicationTimeoutSettingsController_new( replication_settings_controller );
	}

	return replication_settings_controller->timeout_settings_controller;

}

/*
	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_transport.html
	int Rbdb_ReplicationSettingsController_transportCallbackFunction( Rbdb_ReplicationSettingsController* replication_settings_controller )	{
	
	}

	void Rbdb_ReplicationSettingsController_setTransportCallbackFunction( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	}
*/

/*****************
*  verbositySettingsController  *
*****************/

Rbdb_ReplicationVerbositySettingsController* Rbdb_ReplicationSettingsController_verbositySettingsController( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	if ( replication_settings_controller->verbosity_settings_controller == NULL )	{
		replication_settings_controller->verbosity_settings_controller = Rbdb_ReplicationVerbositySettingsController_new( replication_settings_controller );
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
int Rbdb_ReplicationSettingsController_internal_startFlags( Rbdb_ReplicationSettingsController* replication_settings_controller )	{
	
	return	Rbdb_ReplicationSettingsController_isMaster( replication_settings_controller )
			|	Rbdb_ReplicationSettingsController_isClient( replication_settings_controller )
			|	Rbdb_ReplicationSettingsController_startAsClientOrRallyElection( replication_settings_controller );
}

/*********************
*  localSiteFlags  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_sync.html
int Rbdb_ReplicationSettingsController_internal_localSiteFlags( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	//	Flags currently unused - returns 0
	return Rbdb_ReplicationSettingsController_isClient( replication_settings_controller )
			|	Rbdb_ReplicationSettingsController_isMaster( replication_settings_controller );
}

/*****************
*  syncFlags  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_sync.html
int Rbdb_ReplicationSettingsController_internal_syncFlags( Rbdb_ReplicationSettingsController* replication_settings_controller __attribute__((unused)) )	{

	//	Flags currently unused - returns 0
	return Rbdb_NO_FLAGS;
}

/*************************
*  callElectionFlags  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_elect.html
int Rbdb_ReplicationSettingsController_internal_callElectionFlags( Rbdb_ReplicationSettingsController* replication_settings_controller __attribute__((unused)) )	{

	//	Flags currently unused - returns 0
	return Rbdb_NO_FLAGS;
}

/*************************
*  addRemoteSiteFlags  *
*************************/

int Rbdb_ReplicationSettingsController_internal_addRemoteSiteFlags( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	return Rbdb_ReplicationSettingsController_clientToClientSynchronization( replication_settings_controller );

}	

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_ReplicationSettingsController* Rbdb_ReplicationSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_ReplicationSettingsController* replication_settings_controller_copy	=	Rbdb_ReplicationSettingsController_new( replication_settings_controller->parent_settings_controller );

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

