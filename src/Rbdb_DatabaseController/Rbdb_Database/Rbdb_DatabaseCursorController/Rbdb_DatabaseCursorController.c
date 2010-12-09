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

#include "Rbdb_DatabaseCursorController.h"
#include "Rbdb_DatabaseCursorController_internal.h"

#include "Rbdb_DatabaseCursor.h"

#include "Rbdb_Database.h"
#include "Rbdb_Database_internal.h"

#include "Rbdb_DatabaseCursor_internal.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Record.h"
#include "Rbdb_Data.h"

#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseCursorSettingsController.h"

#include "Rbdb_RuntimeStorageController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/

Rbdb_DatabaseCursorController* Rbdb_DatabaseCursorController_new( Rbdb_Database* parent_database )	{

	Rbdb_DatabaseCursorController*		database_cursor_controller = Rbdb_DatabaseCursorController_internal_newWithoutRuntimeStorage( parent_database );

	database_cursor_controller->parent_database	=	parent_database;

	Rbdb_RUNTIME_STORAGE( database_cursor_controller, "database_cursor_controller" );
	
 	return database_cursor_controller;
}

/*********
*  free  *
*********/

void Rbdb_DatabaseCursorController_free( Rbdb_DatabaseCursorController** database_cursor_controller )	{

	//	if we have a runtime storage, close and free any cursors
	//	if we don't have a runtime storage, we are a runtime storage and the cursor is freed manually
	if ( ( *database_cursor_controller )->runtime_storage_database != NULL )	{
		Rbdb_DatabaseCursorController_freeAllCursors( *database_cursor_controller );
	}
	
	//	free runtime storage
	if ( ( *database_cursor_controller )->runtime_storage_database != NULL )	{
		Rbdb_Database_free( & ( ( *database_cursor_controller )->runtime_storage_database ) );
	}

	//	free self
	free( *database_cursor_controller );
	*database_cursor_controller		=	NULL;
}

/***********************
*  settingsController  *
***********************/
Rbdb_DatabaseCursorSettingsController* Rbdb_DatabaseCursorController_settingsController(	Rbdb_DatabaseCursorController* database_cursor_controller )	{
	return database_cursor_controller->settings_controller;
}

/**********************
*  parentEnvironment  *
**********************/
Rbdb_Environment* Rbdb_DatabaseCursorController_parentEnvironment(	Rbdb_DatabaseCursorController* database_cursor_controller )	{
	return database_cursor_controller->parent_database->parent_database_controller->parent_environment;
}

/*******************
*  parentDatabase  *
*******************/
Rbdb_Database* Rbdb_DatabaseCursorController_parentDatabase(	Rbdb_DatabaseCursorController* database_cursor_controller )	{
	return database_cursor_controller->parent_database;
}

/***********
*  cursor  *
***********/

//	shorthand function to get a cursor without having to name the name
Rbdb_DatabaseCursor* Rbdb_DatabaseCursorController_cursor( Rbdb_DatabaseCursorController*		cursor_controller )	{
	
	Rbdb_DatabaseCursor*	cursor	=	Rbdb_DatabaseCursor_new( cursor_controller );
	
	return cursor;
}

/********************
*  closeAllCursors  *
********************/

void Rbdb_DatabaseCursorController_closeAllCursors( Rbdb_DatabaseCursorController* cursor_controller )	{

	Rbdb_Database_internal_closeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																													(void *(*)(void*)) & Rbdb_DatabaseCursor_close );
}

/*******************
*  freeAllCursors  *
*******************/

//	free all cursors; close if necessary
void Rbdb_DatabaseCursorController_freeAllCursors( Rbdb_DatabaseCursorController* cursor_controller )	{
	
	Rbdb_DatabaseCursorController_closeAllCursors( cursor_controller );
	Rbdb_Database_internal_freeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																												(void *(*)(void**)) & Rbdb_DatabaseCursor_internal_freeFromRuntimeStorage );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  newWithoutRuntimeStorage  *
*****************************/

Rbdb_DatabaseCursorController* Rbdb_DatabaseCursorController_internal_newWithoutRuntimeStorage( Rbdb_Database* parent_database )	{

	Rbdb_DatabaseCursorController*	cursor_controller	= calloc( 1, sizeof( Rbdb_DatabaseCursorController ) );

	cursor_controller->parent_database	=	parent_database;

	return cursor_controller;
}

