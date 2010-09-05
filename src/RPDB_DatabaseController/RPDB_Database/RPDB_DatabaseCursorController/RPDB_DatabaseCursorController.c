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

#include "RPDB_DatabaseCursorController.h"
#include "RPDB_DatabaseCursorController_internal.h"

#include "RPDB_DatabaseCursor.h"

#include "RPDB_Database.h"
#include "RPDB_Database_internal.h"

#include "RPDB_Environment.h"

#include "RPDB_Record.h"
#include "RPDB_Data.h"

#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_DatabaseCursorSettingsController.h"

#include "RPDB_RuntimeStorageController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/

RPDB_DatabaseCursorController* RPDB_DatabaseCursorController_new( RPDB_Database* parent_database )	{

	RPDB_DatabaseCursorController*		database_cursor_controller = RPDB_DatabaseCursorController_internal_newWithoutRuntimeStorage( parent_database );

	//	We have one DatabaseCursor controller for every Database instance, which tracks all DatabaseCursors that have been opened on the given instance
	//	Each DatabaseCursorController owns a RuntimeStorage, where it stores references to each DatabaseCursor.
	//	This RuntimeStorage itself has to be stored in the RuntimeStorageController, which means it needs a unique identifier.

	//	We already have the unique environment name (environment_name.environment_address), which distinguishes the environment instance
	//	We need a name that will be unique for this Environment
	//	We can add database_name.database_address, which identifies both which database, and which database instance
	//	The address alone would be sufficient, but the name makes it readable for debugging.

	RPDB_RuntimeStorageController*	runtime_storage_controller	=	RPDB_RuntimeStorageController_sharedInstance();
	RPDB_DatabaseController*	database_controller	=	RPDB_Environment_databaseController(	runtime_storage_controller->runtime_environment );
	RPDB_Database*	runtime_storage_database	=	RPDB_Database_new(	database_controller,
																																	"database_cursor_controller" );
	database_cursor_controller->runtime_storage_database	=	RPDB_Database_internal_initForRuntimeStorage(	runtime_storage_database );
	
 	return database_cursor_controller;
}

/*********
*  free  *
*********/

void RPDB_DatabaseCursorController_free( RPDB_DatabaseCursorController** database_cursor_controller )	{

	//	if we have a runtime storage, close and free any cursors
	//	if we don't have a runtime storage, we are a runtime storage and the cursor is freed manually
	if ( ( *database_cursor_controller )->runtime_storage_database != NULL )	{
		RPDB_DatabaseCursorController_freeAllCursors( *database_cursor_controller );
	}
	
	//	free runtime storage
	if ( ( *database_cursor_controller )->runtime_storage_database != NULL )	{
		RPDB_Database_free( & ( ( *database_cursor_controller )->runtime_storage_database ) );
	}

	//	free self
	free( *database_cursor_controller );
	*database_cursor_controller		=	NULL;
}

/***********************
*  settingsController  *
***********************/
RPDB_DatabaseCursorSettingsController* RPDB_DatabaseCursorController_settingsController(	RPDB_DatabaseCursorController* database_cursor_controller )	{
	return database_cursor_controller->settings_controller;
}

/**********************
*  parentEnvironment  *
**********************/
RPDB_Environment* RPDB_DatabaseCursorController_parentEnvironment(	RPDB_DatabaseCursorController* database_cursor_controller )	{
	return database_cursor_controller->parent_database->parent_database_controller->parent_environment;
}

/*******************
*  parentDatabase  *
*******************/
RPDB_Database* RPDB_DatabaseCursorController_parentDatabase(	RPDB_DatabaseCursorController* database_cursor_controller )	{
	return database_cursor_controller->parent_database;
}

/***********
*  cursor  *
***********/

//	shorthand function to get a cursor without having to name the name
RPDB_DatabaseCursor* RPDB_DatabaseCursorController_cursor( RPDB_DatabaseCursorController*		cursor_controller )	{
	
	RPDB_DatabaseCursor*	cursor	=	RPDB_DatabaseCursor_new( cursor_controller );
	
	return cursor;
}

/********************
*  closeAllCursors  *
********************/

void RPDB_DatabaseCursorController_closeAllCursors( RPDB_DatabaseCursorController* cursor_controller )	{

	RPDB_Database_internal_closeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																													(void *(*)(void*)) & RPDB_DatabaseCursor_close );
}

/*******************
*  freeAllCursors  *
*******************/

//	free all cursors; close if necessary
void RPDB_DatabaseCursorController_freeAllCursors( RPDB_DatabaseCursorController* cursor_controller )	{
	
	RPDB_Database_internal_freeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																													(void *(*)(void**)) & RPDB_DatabaseCursor_free );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  newWithoutRuntimeStorage  *
*****************************/

RPDB_DatabaseCursorController* RPDB_DatabaseCursorController_internal_newWithoutRuntimeStorage( RPDB_Database* parent_database )	{

	RPDB_DatabaseCursorController*	cursor_controller	= calloc( 1, sizeof( RPDB_DatabaseCursorController ) );

	cursor_controller->parent_database	=	parent_database;

	return cursor_controller;
}

