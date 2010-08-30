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

	char*		log_cursor_controller_runtime_storage_name	=	RPDB_LogCursorController_internal_uniqueIdentifier( log_cursor_controller );

	//	Initialize our runtime storage for the database_cursor_controller
	log_cursor_controller->runtime_storage	=	RPDB_RuntimeStorageController_runtimeStorageInEnvironmentWithName(	
													RPDB_RuntimeStorageController_sharedInstance(),
													log_cursor_controller->parent_log_controller->parent_environment,
	 												log_cursor_controller_runtime_storage_name );

	return log_cursor_controller;
}

/*************************
*  cursorForName  *
*************************/

RPDB_LogCursor* RPDB_LogCursorController_cursorForName(	RPDB_LogCursorController*		cursor_controller,
 															char*							cursor_name )	{

	RPDB_LogCursor*	database_cursor;

	//	Check and see if cursor_name exists in runtime storage
	//	If it doesn't, we need to create it and store it
	if ( RPDB_RuntimeStorage_rawKeyExists(	cursor_controller->runtime_storage,
											cursor_name,
											( strlen( cursor_name ) + 1 ) * sizeof( char ) ) )	{
													
		database_cursor	=	RPDB_Data_rawData(	RPDB_Record_data(	RPDB_RuntimeStorage_retrieveRawKey(	cursor_controller->runtime_storage,
																											cursor_name,
																											( strlen( cursor_name ) + 1 ) * sizeof( char ) ) ) );
	}
	else	{
	
		//	Create a database_cursor for parent database
		database_cursor	=	RPDB_LogCursor_new( cursor_controller );
	
		uintptr_t		new_cursor_address	=	(uintptr_t) database_cursor;

		//	Store pointer to database_cursor in runtime storage
		RPDB_RuntimeStorage_insertRawKeyDataPair(	cursor_controller->runtime_storage,
													cursor_name,
													( strlen( cursor_name ) + 1 ) * sizeof( char ),
													& new_cursor_address,
													sizeof( uintptr_t ) );
	}
	
	return database_cursor;
}

/*****************************
*  closeCursorForName  *
*****************************/

RPDB_LogCursor* RPDB_LogCursorController_closeCursorForName(	RPDB_LogCursorController*		cursor_controller,
 																	char*							cursor_name )	{
	
	RPDB_LogCursor*	database_cursor	=	RPDB_LogCursorController_cursorForName(	cursor_controller,
																						cursor_name );
	RPDB_LogCursor_close( database_cursor );
	
	return database_cursor;															
}

/*****************************
*  freeCursorForName  *
*****************************/

void RPDB_LogCursorController_freeCursorForName(	RPDB_LogCursorController*		cursor_controller,
 													char*							cursor_name )	{

	RPDB_LogCursor*	database_cursor	=	RPDB_LogCursorController_cursorForName(	cursor_controller,
																				cursor_name );
	RPDB_LogCursor_free( & database_cursor );
	
	RPDB_RuntimeStorage_deleteRecordForRawKey(	cursor_controller->runtime_storage,
												cursor_name,
												( strlen( cursor_name ) + 1 ) * sizeof( char ) );
}

/*****************
*  allCursors  *
*****************/

//	Return a list of database names that have been created and stored in this controller
RPDB_LogCursor** RPDB_LogCursorController_allCursors( RPDB_LogCursorController* cursor_controller )	{

	RPDB_RuntimeStorage_countRecords( cursor_controller->runtime_storage );
	
	RPDB_LogCursor*	this_cursor;
	
	RPDB_LogCursor**	cursor_array	=	calloc(	cursor_controller->runtime_storage->record_count, sizeof( RPDB_LogCursor ) );
	
	int				which_cursor	=	0;
	
	while ( ( this_cursor = (RPDB_LogCursor*) *(uintptr_t*) RPDB_Record_rawData( RPDB_RuntimeStorage_nextRecord( cursor_controller->runtime_storage ) ) ) )	{
		
		cursor_array[ which_cursor ] = this_cursor;
		
		which_cursor++;
	}
	
	return cursor_array;
}

/***************************
*  free  *
***************************/
void RPDB_LogCursorController_free(	RPDB_LogCursorController** log_cursor_controller )	{

	if ( ( *log_cursor_controller )->runtime_storage != NULL )	{
		RPDB_RuntimeStorage_free( & ( ( *log_cursor_controller )->runtime_storage ) );
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

	RPDB_RuntimeStorage_iterate( cursor_controller->runtime_storage );
	
	RPDB_LogCursor*	this_cursor;
	
	while ( ( this_cursor = RPDB_Data_rawData(	RPDB_Record_data(	RPDB_RuntimeStorage_nextRecord( cursor_controller->runtime_storage ) ) ) ) )	{
		
		RPDB_LogCursor_close( this_cursor );
	}
}

/*********************
*  freeAllCursors  *
*********************/

void RPDB_LogCursorController_freeAllCursors( RPDB_LogCursorController* cursor_controller )	{

	RPDB_RuntimeStorage_iterate( cursor_controller->runtime_storage );
	
	RPDB_LogCursor*	this_cursor;
	
	while ( ( this_cursor = RPDB_Data_rawData(	RPDB_Record_data(	RPDB_RuntimeStorage_nextRecord( cursor_controller->runtime_storage ) ) ) ) )	{
		
		RPDB_LogCursor_free( & this_cursor );
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

