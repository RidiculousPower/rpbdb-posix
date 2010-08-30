/*
 *		RPDB::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorCacheSettingsController
 *		RPDB::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorCacheSettingsController
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseCursorCacheSettingsController.h"

#include "RPDB_DatabaseCursorSettingsController.h"
#include "RPDB_DatabaseCursorCachePrioritySettingsController.h"

#include "RPDB_DatabaseCursorCacheSettingsController_internal.h"
#include "RPDB_DatabaseCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_DatabaseCursorCacheSettingsController* RPDB_DatabaseCursorCacheSettingsController_new( RPDB_DatabaseCursorSettingsController* cursor_settings_controller )	{

	RPDB_DatabaseCursorCacheSettingsController*		cursor_cache_settings_controller = calloc( 1, sizeof( RPDB_DatabaseCursorCacheSettingsController ) );

	cursor_cache_settings_controller->parent_database_cursor_settings_controller = cursor_settings_controller;

	return cursor_cache_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseCursorCacheSettingsController_free(	RPDB_DatabaseCursorCacheSettingsController** database_cursor_cache_settings_controller )	{

	if ( ( *database_cursor_cache_settings_controller )->priority_settings_controller != NULL )	{
		RPDB_DatabaseCursorCachePrioritySettingsController_free( & ( ( *database_cursor_cache_settings_controller )->priority_settings_controller ) );
	}
	
	free( *database_cursor_cache_settings_controller );
	*database_cursor_cache_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseCursorCacheSettingsController_parentEnvironment(	RPDB_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller )	{
	return database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseCursorCacheSettingsController_parentDatabase(	RPDB_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller )	{
	return database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database;
}

/***************************************
*  parentDatabaseCursor  *
***************************************/
RPDB_DatabaseCursor* RPDB_DatabaseCursorCacheSettingsController_parentDatabaseCursor(	RPDB_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller )	{
	return database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/**************************
*  priorityController  *
**************************/

RPDB_DatabaseCursorCachePrioritySettingsController* RPDB_DatabaseCursorCacheSettingsController_priorityController( RPDB_DatabaseCursorCacheSettingsController* cursor_cache_settings_controller )	{
	
	if ( cursor_cache_settings_controller->priority_settings_controller == NULL )	{
		
		cursor_cache_settings_controller->priority_settings_controller = RPDB_DatabaseCursorCachePrioritySettingsController_new( cursor_cache_settings_controller );
	}
	return cursor_cache_settings_controller->priority_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseCursorCacheSettingsController* RPDB_DatabaseCursorCacheSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller )	{

	RPDB_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller_copy	=	RPDB_DatabaseCursorCacheSettingsController_new( database_cursor_cache_settings_controller->parent_database_cursor_settings_controller );

	//	Instances and Pointers
	database_cursor_cache_settings_controller_copy->max_size_in_bytes	=	database_cursor_cache_settings_controller->max_size_in_bytes;
	database_cursor_cache_settings_controller_copy->number_cache_regions	=	database_cursor_cache_settings_controller->number_cache_regions;

	return database_cursor_cache_settings_controller_copy;
}

