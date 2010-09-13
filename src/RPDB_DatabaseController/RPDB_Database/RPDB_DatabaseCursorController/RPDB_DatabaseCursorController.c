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

#include "RPDB_DatabaseCursor_internal.h"

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

	database_cursor_controller->parent_database	=	parent_database;

	RPDB_RUNTIME_STORAGE( database_cursor_controller, "database_cursor_controller" );
	
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
	
	RPDB_DatabaseCursorController_closeAllCursors( cursor_controller );
	RPDB_Database_internal_freeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																												(void *(*)(void**)) & RPDB_DatabaseCursor_internal_freeFromRuntimeStorage );
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

