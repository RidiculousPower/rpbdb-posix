/*
 *		RPbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorCacheSettingsController
 *		RPbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorCacheSettingsController
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseCursorCacheSettingsController.h"

#include "DatabaseCursorSettingsController.h"
#include "DatabaseCursorCachePrioritySettingsController.h"

#include "DatabaseCursorCacheSettingsController_internal.h"
#include "DatabaseCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_DatabaseCursorCacheSettingsController* RPbdb_DatabaseCursorCacheSettingsController_new( RPbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{

	RPbdb_DatabaseCursorCacheSettingsController*		cursor_cache_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseCursorCacheSettingsController ) );

	cursor_cache_settings_controller->parent_database_cursor_settings_controller = cursor_settings_controller;

	return cursor_cache_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseCursorCacheSettingsController_free(	RPbdb_DatabaseCursorCacheSettingsController** database_cursor_cache_settings_controller )	{

	if ( ( *database_cursor_cache_settings_controller )->priority_settings_controller != NULL )	{
		RPbdb_DatabaseCursorCachePrioritySettingsController_free( & ( ( *database_cursor_cache_settings_controller )->priority_settings_controller ) );
	}
	
	free( *database_cursor_cache_settings_controller );
	*database_cursor_cache_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseCursorCacheSettingsController_parentEnvironment(	RPbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller )	{
	return database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseCursorCacheSettingsController_parentDatabase(	RPbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller )	{
	return database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database;
}

/***************************************
*  parentDatabaseCursor  *
***************************************/
RPbdb_DatabaseCursor* RPbdb_DatabaseCursorCacheSettingsController_parentDatabaseCursor(	RPbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller )	{
	return database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/**************************
*  priorityController  *
**************************/

RPbdb_DatabaseCursorCachePrioritySettingsController* RPbdb_DatabaseCursorCacheSettingsController_priorityController( RPbdb_DatabaseCursorCacheSettingsController* cursor_cache_settings_controller )	{
	
	if ( cursor_cache_settings_controller->priority_settings_controller == NULL )	{
		
		cursor_cache_settings_controller->priority_settings_controller = RPbdb_DatabaseCursorCachePrioritySettingsController_new( cursor_cache_settings_controller );
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
RPbdb_DatabaseCursorCacheSettingsController* RPbdb_DatabaseCursorCacheSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller )	{

	RPbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller_copy	=	RPbdb_DatabaseCursorCacheSettingsController_new( database_cursor_cache_settings_controller->parent_database_cursor_settings_controller );

	//	Instances and Pointers
	database_cursor_cache_settings_controller_copy->max_size_in_bytes	=	database_cursor_cache_settings_controller->max_size_in_bytes;
	database_cursor_cache_settings_controller_copy->number_cache_regions	=	database_cursor_cache_settings_controller->number_cache_regions;

	return database_cursor_cache_settings_controller_copy;
}

