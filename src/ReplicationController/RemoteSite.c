/*
 *		RPbdb::DatabaseController::Database::DatabaseCursorController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RemoteSite.h"

#include "Database_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_RemoteSite* RPbdb_RemoteSite_new( RPbdb_ReplicationController* parent_replication_controller )	{

	RPbdb_RemoteSite*	remote_site	=	calloc( 1, sizeof( RPbdb_RemoteSite ) );
	
	if ( parent_replication_controller->runtime_storage_database != NULL )	{
		remote_site->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_replication_controller->runtime_storage_database,
																																									(void*) remote_site );
	}
	
	remote_site->parent_replication_controller = parent_replication_controller;
	
	return remote_site;
}

/***************************
*  free  *
***************************/
void RPbdb_RemoteSite_free(	RPbdb_RemoteSite** remote_site )	{

	if ( ( *remote_site )->parent_replication_controller->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *remote_site )->parent_replication_controller->runtime_storage_database,
																											( *remote_site )->runtime_identifier );
	}

	free( remote_site );
}

/***************************
*  settingsController  *
***************************/
RPbdb_ReplicationSettingsController* RPbdb_RemoteSite_settingsController(	RPbdb_RemoteSite* remote_site )	{
	return remote_site->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_RemoteSite_parentEnvironment(	RPbdb_RemoteSite* remote_site )	{
	return remote_site->parent_replication_controller->parent_environment;
}


