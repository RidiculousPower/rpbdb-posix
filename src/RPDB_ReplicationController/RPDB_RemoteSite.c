/*
 *		RPDB::DatabaseController::Database::DatabaseCursorController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_RemoteSite.h"

#include "RPDB_Database_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_RemoteSite* RPDB_RemoteSite_new( RPDB_ReplicationController* parent_replication_controller )	{

	RPDB_RemoteSite*	remote_site	=	calloc( 1, sizeof( RPDB_RemoteSite ) );
	
	if ( parent_replication_controller->runtime_storage_database != NULL )	{
		remote_site->runtime_identifier =	RPDB_Database_internal_storeRuntimeAddress(	parent_replication_controller->runtime_storage_database,
																																									(void*) remote_site );
	}
	
	remote_site->parent_replication_controller = parent_replication_controller;
	
	return remote_site;
}

/***************************
*  free  *
***************************/
void RPDB_RemoteSite_free(	RPDB_RemoteSite** remote_site )	{

	if ( ( *remote_site )->parent_replication_controller->runtime_storage_database != NULL )	{
		RPDB_Database_internal_freeStoredRuntimeAddress(	( *remote_site )->parent_replication_controller->runtime_storage_database,
																											( *remote_site )->runtime_identifier );
	}

	free( remote_site );
}

/***************************
*  settingsController  *
***************************/
RPDB_ReplicationSettingsController* RPDB_RemoteSite_settingsController(	RPDB_RemoteSite* remote_site )	{
	return remote_site->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_RemoteSite_parentEnvironment(	RPDB_RemoteSite* remote_site )	{
	return remote_site->parent_replication_controller->parent_environment;
}


