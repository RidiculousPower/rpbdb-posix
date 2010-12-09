/*
 *		Rbdb::DatabaseController::Database::DatabaseCursorController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_RemoteSite.h"

#include "Rbdb_Database_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

Rbdb_RemoteSite* Rbdb_RemoteSite_new( Rbdb_ReplicationController* parent_replication_controller )	{

	Rbdb_RemoteSite*	remote_site	=	calloc( 1, sizeof( Rbdb_RemoteSite ) );
	
	if ( parent_replication_controller->runtime_storage_database != NULL )	{
		remote_site->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_replication_controller->runtime_storage_database,
																																									(void*) remote_site );
	}
	
	remote_site->parent_replication_controller = parent_replication_controller;
	
	return remote_site;
}

/***************************
*  free  *
***************************/
void Rbdb_RemoteSite_free(	Rbdb_RemoteSite** remote_site )	{

	if ( ( *remote_site )->parent_replication_controller->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *remote_site )->parent_replication_controller->runtime_storage_database,
																											( *remote_site )->runtime_identifier );
	}

	free( remote_site );
}

/***************************
*  settingsController  *
***************************/
Rbdb_ReplicationSettingsController* Rbdb_RemoteSite_settingsController(	Rbdb_RemoteSite* remote_site )	{
	return remote_site->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_RemoteSite_parentEnvironment(	Rbdb_RemoteSite* remote_site )	{
	return remote_site->parent_replication_controller->parent_environment;
}


