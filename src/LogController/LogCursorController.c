/*
 *		RPbdb::LogController::LogCursorController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "LogCursorController.h"
#include "LogCursorController_internal.h"

#include "LogCursor.h"
#include "LogCursor_internal.h"

#include "Environment.h"

#include "Database.h"
#include "Database_internal.h"
#include "DatabaseCursor.h"

#include "Record.h"
#include "Data.h"

#include "RuntimeStorageController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_LogCursorController* RPbdb_LogCursorController_new( RPbdb_LogController* parent_log_controller )	{
	
	RPbdb_LogCursorController*		log_cursor_controller = calloc( 1, sizeof( RPbdb_LogCursorController ) );

	log_cursor_controller->parent_log_controller	=	parent_log_controller;

	RPBDB_RUNTIME_STORAGE( log_cursor_controller,	"log_cursor_controller" );

	return log_cursor_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_LogCursorController_free(	RPbdb_LogCursorController** log_cursor_controller )	{

	if ( ( *log_cursor_controller )->runtime_storage_database != NULL )	{
		RPbdb_Database_free( & ( ( *log_cursor_controller )->runtime_storage_database ) );
	}
	free( *log_cursor_controller );
	*log_cursor_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_LogSettingsController* RPbdb_LogCursorController_settingsController(	RPbdb_LogCursorController* log_cursor_controller )	{
	return log_cursor_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_LogCursorController_parentEnvironment(	RPbdb_LogCursorController* log_cursor_controller )	{
	return log_cursor_controller->parent_log_controller->parent_environment;
}

/*************************
*  closeAllCursors  *
*************************/

void RPbdb_LogCursorController_closeAllCursors( RPbdb_LogCursorController* cursor_controller )	{

	RPbdb_Database_internal_closeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																													(void *(*)(void*)) & RPbdb_LogCursor_close );
}

/*********************
*  freeAllCursors  *
*********************/

void RPbdb_LogCursorController_freeAllCursors( RPbdb_LogCursorController* cursor_controller )	{

	RPbdb_LogCursorController_closeAllCursors( cursor_controller );
	RPbdb_Database_internal_freeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																												(void *(*)(void**)) & RPbdb_LogCursor_internal_freeFromRuntimeStorage );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

