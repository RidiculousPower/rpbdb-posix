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

#include "DatabaseCursorController.h"
#include "DatabaseCursorController_internal.h"

#include "DatabaseCursor.h"

#include "Database.h"
#include "Database_internal.h"

#include "DatabaseCursor_internal.h"

#include "Environment.h"

#include "Record.h"
#include "Data.h"

#include "DatabaseSettingsController.h"
#include "DatabaseCursorSettingsController.h"

#include "RuntimeStorageController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/

RPbdb_DatabaseCursorController* RPbdb_DatabaseCursorController_new( RPbdb_Database* parent_database )	{

	RPbdb_DatabaseCursorController*		database_cursor_controller = RPbdb_DatabaseCursorController_internal_newWithoutRuntimeStorage( parent_database );

	database_cursor_controller->parent_database	=	parent_database;

	RPBDB_RUNTIME_STORAGE( database_cursor_controller, "database_cursor_controller" );
	
 	return database_cursor_controller;
}

/*********
*  free  *
*********/

void RPbdb_DatabaseCursorController_free( RPbdb_DatabaseCursorController** database_cursor_controller )	{

	//	if we have a runtime storage, close and free any cursors
	//	if we don't have a runtime storage, we are a runtime storage and the cursor is freed manually
	if ( ( *database_cursor_controller )->runtime_storage_database != NULL )	{
		RPbdb_DatabaseCursorController_freeAllCursors( *database_cursor_controller );
		RPbdb_Database_free( & ( ( *database_cursor_controller )->runtime_storage_database ) );
	}

	//	free self
	free( *database_cursor_controller );
	*database_cursor_controller		=	NULL;
}

/***********************
*  settingsController  *
***********************/
RPbdb_DatabaseCursorSettingsController* RPbdb_DatabaseCursorController_settingsController(	RPbdb_DatabaseCursorController* database_cursor_controller )	{
	return database_cursor_controller->settings_controller;
}

/**********************
*  parentEnvironment  *
**********************/
RPbdb_Environment* RPbdb_DatabaseCursorController_parentEnvironment(	RPbdb_DatabaseCursorController* database_cursor_controller )	{
	return database_cursor_controller->parent_database->parent_database_controller->parent_environment;
}

/*******************
*  parentDatabase  *
*******************/
RPbdb_Database* RPbdb_DatabaseCursorController_parentDatabase(	RPbdb_DatabaseCursorController* database_cursor_controller )	{
	return database_cursor_controller->parent_database;
}

/***********
*  cursor  *
***********/

//	shorthand function to get a cursor without having to name the name
RPbdb_DatabaseCursor* RPbdb_DatabaseCursorController_cursor( RPbdb_DatabaseCursorController*		cursor_controller )	{
	
	RPbdb_DatabaseCursor*	cursor	=	RPbdb_DatabaseCursor_new( cursor_controller );
	
	return cursor;
}

/********************
*  closeAllCursors  *
********************/

void RPbdb_DatabaseCursorController_closeAllCursors( RPbdb_DatabaseCursorController* cursor_controller )	{

	RPbdb_Database_internal_closeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																													(void *(*)(void*)) & RPbdb_DatabaseCursor_close );
}

/*******************
*  freeAllCursors  *
*******************/

//	free all cursors; close if necessary
void RPbdb_DatabaseCursorController_freeAllCursors( RPbdb_DatabaseCursorController* cursor_controller )	{
	
	RPbdb_DatabaseCursorController_closeAllCursors( cursor_controller );
	RPbdb_Database_internal_freeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																												(void *(*)(void**)) & RPbdb_DatabaseCursor_internal_freeFromRuntimeStorage );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  newWithoutRuntimeStorage  *
*****************************/

RPbdb_DatabaseCursorController* RPbdb_DatabaseCursorController_internal_newWithoutRuntimeStorage( RPbdb_Database* parent_database )	{

	RPbdb_DatabaseCursorController*	cursor_controller	= calloc( 1, sizeof( RPbdb_DatabaseCursorController ) );

	cursor_controller->parent_database	=	parent_database;

	return cursor_controller;
}

