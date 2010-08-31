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

#include "RPDB_Environment.h"

#include "RPDB_Database.h"
#include "RPDB_Database_internal.h"
#include "RPDB_DatabaseCursor.h"

#include "RPDB_Record.h"
#include "RPDB_Data.h"

#include "RPDB_RuntimeStorageController.h"
#include "RPDB_RuntimeStorage.h"

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

	RPDB_RuntimeStorageController*	runtime_storage_controller;
	RPDB_DatabaseController*	database_controller	=	RPDB_Environment_databaseController(	runtime_storage_controller->runtime_environment );
	RPDB_Database*	runtime_storage_database	=	RPDB_Database_new(	database_controller,
																																	"log_cursor_controller" );
	log_cursor_controller->runtime_storage_database	=	RPDB_Database_internal_initForRuntimeStorage(	runtime_storage_database );

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

	RPDB_DatabaseCursorController*	runtime_storage_cursor_controller	=	RPDB_Database_cursorController( cursor_controller->runtime_storage_database );
	RPDB_DatabaseCursor*	cursor	=	RPDB_DatabaseCursor_new( runtime_storage_cursor_controller );
	RPDB_Record*	record	=	NULL;
	while ( ( record = RPDB_DatabaseCursor_retrieveNext( cursor ) ) != NULL )	{
		RPDB_LogCursor* this_log_cursor	=	(RPDB_LogCursor*) *(uintptr_t*) RPDB_Record_rawData( record );
		RPDB_LogCursor_close( this_log_cursor );
	}
	RPDB_DatabaseCursor_close( cursor );
	RPDB_DatabaseCursor_free( & cursor );
}

/*********************
*  freeAllCursors  *
*********************/

void RPDB_LogCursorController_freeAllCursors( RPDB_LogCursorController* cursor_controller )	{

	RPDB_Record*	record		=	NULL;	
	while ( ( record = RPDB_Database_shiftQueue( cursor_controller->runtime_storage_database ) ) != NULL )	{
		
		RPDB_LogCursor*	this_log_cursor	=	(RPDB_LogCursor*) *(uintptr_t*) RPDB_Record_rawData( record );
		
		RPDB_LogCursor_free( & this_log_cursor );
	}	
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/


/*********************
*  uniqueIdentifier  *
*********************/

char* RPDB_LogCursorController_internal_uniqueIdentifier( RPDB_LogCursorController* log_cursor_controller )	{
	
	RPDB_Environment*	parent_environment			=	log_cursor_controller->parent_log_controller->parent_environment;
	char*				parent_environment_name	=	parent_environment->name;

	uintptr_t	parent_environment_address			=	(uintptr_t) parent_environment;
	
	char*		parent_environment_address_string		=	calloc( 21, sizeof( char ) );
	sprintf(	parent_environment_address_string,
						"%" PRIxPTR "",			parent_environment_address );
	
	//	we have one database controller per environment, so using the environment's pointer address (which is always unique)
	//	should suffice
	int			unique_identifier_length			=		strlen( "log_cursor_controller"  ) 
														+	strlen( RPDB_DELIMITER )
														+	strlen( parent_environment_name )
														+	strlen( RPDB_DELIMITER )
														+	strlen( parent_environment_address_string )
														+	1;
	char*		unique_identifier					=	calloc( unique_identifier_length, sizeof( char ) );
	
	sprintf(	unique_identifier,
				"%s%s%s%s%s",		"log_cursor_controller",
									RPDB_DELIMITER,
									parent_environment_name,
									RPDB_DELIMITER,
									parent_environment_address_string	);
	
	free( parent_environment_address_string );
	parent_environment_address_string	=	NULL;
	
	return unique_identifier;
}

