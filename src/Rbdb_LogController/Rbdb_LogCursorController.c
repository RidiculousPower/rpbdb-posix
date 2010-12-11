/*
 *		Rbdb::LogController::LogCursorController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_LogCursorController.h"
#include "Rbdb_LogCursorController_internal.h"

#include "Rbdb_LogCursor.h"
#include "Rbdb_LogCursor_internal.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Database.h"
#include "Rbdb_Database_internal.h"
#include "Rbdb_DatabaseCursor.h"

#include "Rbdb_Record.h"
#include "Rbdb_Data.h"

#include "Rbdb_RuntimeStorageController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

Rbdb_LogCursorController* Rbdb_LogCursorController_new( Rbdb_LogController* parent_log_controller )	{
	
	Rbdb_LogCursorController*		log_cursor_controller = calloc( 1, sizeof( Rbdb_LogCursorController ) );

	log_cursor_controller->parent_log_controller	=	parent_log_controller;

	RBDB_RUNTIME_STORAGE( log_cursor_controller,	"log_cursor_controller" );

	return log_cursor_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_LogCursorController_free(	Rbdb_LogCursorController** log_cursor_controller )	{

	if ( ( *log_cursor_controller )->runtime_storage_database != NULL )	{
		Rbdb_Database_free( & ( ( *log_cursor_controller )->runtime_storage_database ) );
	}
	free( *log_cursor_controller );
	*log_cursor_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_LogSettingsController* Rbdb_LogCursorController_settingsController(	Rbdb_LogCursorController* log_cursor_controller )	{
	return log_cursor_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_LogCursorController_parentEnvironment(	Rbdb_LogCursorController* log_cursor_controller )	{
	return log_cursor_controller->parent_log_controller->parent_environment;
}

/*************************
*  closeAllCursors  *
*************************/

void Rbdb_LogCursorController_closeAllCursors( Rbdb_LogCursorController* cursor_controller )	{

	Rbdb_Database_internal_closeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																													(void *(*)(void*)) & Rbdb_LogCursor_close );
}

/*********************
*  freeAllCursors  *
*********************/

void Rbdb_LogCursorController_freeAllCursors( Rbdb_LogCursorController* cursor_controller )	{

	Rbdb_LogCursorController_closeAllCursors( cursor_controller );
	Rbdb_Database_internal_freeAllStoredRuntimeAddresses(	cursor_controller->runtime_storage_database,
																												(void *(*)(void**)) & Rbdb_LogCursor_internal_freeFromRuntimeStorage );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

