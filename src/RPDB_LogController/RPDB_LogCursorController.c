/*
 *		RPDB::LogController::LogCursorController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_LogCursorController.h"
#include "RPDB_LogCursorController_internal.h"

#include "RPDB_LogCursor.h"
#include "RPDB_LogCursor_internal.h"

#include "RPDB_Environment.h"

#include "RPDB_Database.h"
#include "RPDB_Database_internal.h"
#include "RPDB_DatabaseCursor.h"

#include "RPDB_Record.h"
#include "RPDB_Data.h"

#include "RPDB_RuntimeStorageController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_LogCursorController* RPDB_LogCursorController_new( RPDB_LogController* parent_log_controller )	{
	
	RPDB_LogCursorController*		log_cursor_controller = calloc( 1, sizeof( RPDB_LogCursorController ) );

	log_cursor_controller->parent_log_controller	=	parent_log_controller;

	RPDB_RUNTIME_STORAGE( log_cursor_controller,	"log_cursor_controller" );

	return log_cursor_controller;
}

/***************************
*  free  *
***************************/
void RPDB_LogCursorController_free(	RPDB_LogCursorController** log_cursor_controller )	{

	if ( ( *log_cursor_controller )->runtime_storage_database != NULL )	{
		RPDB_Database_free( & ( ( *log_cursor_controller )->runtime_storage_database ) );
	}
	free( *log_cursor_controller );
	*log_cursor_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_LogSettingsController* RPDB_LogCursorController_settingsController(	RPDB_LogCursorController* log_cursor_controller )	{
	return log_cursor_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_LogCursorController_parentEnvironment(	RPDB_LogCursorController* log_cursor_controller )	{
	return log_cursor_controller->parent_log_controller->parent_environment;
}

/*************************
*  closeAllCursors  *
*************************/

void RPDB_LogCursorController_closeAllCursors( RPDB_LogCursorController* cursor_controller )	{

	RPDB_Database_internal_closeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																													(void *(*)(void*)) & RPDB_LogCursor_close );
}

/*********************
*  freeAllCursors  *
*********************/

void RPDB_LogCursorController_freeAllCursors( RPDB_LogCursorController* cursor_controller )	{

	RPDB_LogCursorController_closeAllCursors( cursor_controller );
	RPDB_Database_internal_freeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																												(void *(*)(void**)) & RPDB_LogCursor_internal_freeFromRuntimeStorage );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

