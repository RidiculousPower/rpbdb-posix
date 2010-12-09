/*
 *		Rbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorCacheSettingsController
 *		Rbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorCacheSettingsController
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseCursorCacheSettingsController.h"

#include "Rbdb_DatabaseCursorSettingsController.h"
#include "Rbdb_DatabaseCursorCachePrioritySettingsController.h"

#include "Rbdb_DatabaseCursorCacheSettingsController_internal.h"
#include "Rbdb_DatabaseCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

Rbdb_DatabaseCursorCacheSettingsController* Rbdb_DatabaseCursorCacheSettingsController_new( Rbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{

	Rbdb_DatabaseCursorCacheSettingsController*		cursor_cache_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseCursorCacheSettingsController ) );

	cursor_cache_settings_controller->parent_database_cursor_settings_controller = cursor_settings_controller;

	return cursor_cache_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseCursorCacheSettingsController_free(	Rbdb_DatabaseCursorCacheSettingsController** database_cursor_cache_settings_controller )	{

	if ( ( *database_cursor_cache_settings_controller )->priority_settings_controller != NULL )	{
		Rbdb_DatabaseCursorCachePrioritySettingsController_free( & ( ( *database_cursor_cache_settings_controller )->priority_settings_controller ) );
	}
	
	free( *database_cursor_cache_settings_controller );
	*database_cursor_cache_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseCursorCacheSettingsController_parentEnvironment(	Rbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller )	{
	return database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseCursorCacheSettingsController_parentDatabase(	Rbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller )	{
	return database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database;
}

/***************************************
*  parentDatabaseCursor  *
***************************************/
Rbdb_DatabaseCursor* Rbdb_DatabaseCursorCacheSettingsController_parentDatabaseCursor(	Rbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller )	{
	return database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/**************************
*  priorityController  *
**************************/

Rbdb_DatabaseCursorCachePrioritySettingsController* Rbdb_DatabaseCursorCacheSettingsController_priorityController( Rbdb_DatabaseCursorCacheSettingsController* cursor_cache_settings_controller )	{
	
	if ( cursor_cache_settings_controller->priority_settings_controller == NULL )	{
		
		cursor_cache_settings_controller->priority_settings_controller = Rbdb_DatabaseCursorCachePrioritySettingsController_new( cursor_cache_settings_controller );
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
Rbdb_DatabaseCursorCacheSettingsController* Rbdb_DatabaseCursorCacheSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller )	{

	Rbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller_copy	=	Rbdb_DatabaseCursorCacheSettingsController_new( database_cursor_cache_settings_controller->parent_database_cursor_settings_controller );

	//	Instances and Pointers
	database_cursor_cache_settings_controller_copy->max_size_in_bytes	=	database_cursor_cache_settings_controller->max_size_in_bytes;
	database_cursor_cache_settings_controller_copy->number_cache_regions	=	database_cursor_cache_settings_controller->number_cache_regions;

	return database_cursor_cache_settings_controller_copy;
}

