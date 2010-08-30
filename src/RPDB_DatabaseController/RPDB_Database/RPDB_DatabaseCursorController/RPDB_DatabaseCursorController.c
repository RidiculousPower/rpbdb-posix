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

#include "RPDB_Environment.h"

#include "RPDB_Record.h"
#include "RPDB_Data.h"

#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_DatabaseCursorSettingsController.h"

#include "RPDB_RuntimeStorageController.h"
#include "RPDB_RuntimeStorage.h"

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

	char*	database_cursor_controller_runtime_storage_name	=	RPDB_DatabaseCursorController_internal_uniqueIdentifier( database_cursor_controller );

	RPDB_Environment*	parent_environment	=	parent_database->parent_database_controller->parent_environment;

	//	Initialize our runtime storage for the database_cursor_controller
	database_cursor_controller->runtime_storage		=	RPDB_RuntimeStorageController_runtimeStorageInEnvironmentWithName(	RPDB_RuntimeStorageController_sharedInstance(),
																																parent_environment,
																																database_cursor_controller_runtime_storage_name );
	database_cursor_controller->auto_name_count	=	0;
	
	//	our string got copied by RPDB_RuntimeStorageController_runtimeStorageInEnvironmentWithName, not stored
	//	so we need to free it now
	free( database_cursor_controller_runtime_storage_name );
	
 	return database_cursor_controller;
}

/*********
*  free  *
*********/

void RPDB_DatabaseCursorController_free( RPDB_DatabaseCursorController** database_cursor_controller )	{

	//	if we have a runtime storage, close and free any cursors
	//	if we don't have a runtime storage, we are a runtime storage and the cursor is freed manually
	if ( ( *database_cursor_controller )->runtime_storage != NULL )	{
		RPDB_DatabaseCursorController_freeAllCursors( *database_cursor_controller );
	}
	
	//	free runtime storage
	if ( ( *database_cursor_controller )->runtime_storage != NULL )	{
		RPDB_RuntimeStorage_free( & ( ( *database_cursor_controller )->runtime_storage ) );
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

/********************
*  cursorForName  *
********************/

RPDB_DatabaseCursor* RPDB_DatabaseCursorController_cursorForName(	RPDB_DatabaseCursorController*		cursor_controller,
																																	char*															cursor_name )	{

	RPDB_DatabaseCursor*	database_cursor	=	NULL;
	
	int	cursor_name_size	=	( strlen( cursor_name) + 1 ) * sizeof( char );

	//	Check and see if cursor_name exists in runtime storage
	//	If it doesn't, we need to create it and store it
	if ( RPDB_RuntimeStorage_rawKeyExists(	cursor_controller->runtime_storage,
																					cursor_name,
																					cursor_name_size ) )	{

		//	we already checked if data exists so it's safe to dereference
		database_cursor	=	(RPDB_DatabaseCursor*) *(uintptr_t*) RPDB_Record_rawData(	RPDB_RuntimeStorage_retrieveRawKey(	cursor_controller->runtime_storage,
																																								cursor_name,
																																								cursor_name_size ) );
	}
	else	{
	
		//	Create a database_cursor for parent database
		database_cursor				=	RPDB_DatabaseCursor_new( cursor_controller );
		database_cursor->name		=	strdup( cursor_name );
		
		uintptr_t		new_cursor_address	=	(uintptr_t) database_cursor;
		
		//	Store pointer to database_cursor in runtime storage
		RPDB_RuntimeStorage_insertRawKeyDataPair(	cursor_controller->runtime_storage,
																							cursor_name,
																							cursor_name_size,
																							& new_cursor_address,
																							sizeof( uintptr_t ) );
	}
	
	return database_cursor;
}

/***********
*  cursor  *
***********/

//	shorthand function to get a cursor without having to name the name
RPDB_DatabaseCursor* RPDB_DatabaseCursorController_cursor( RPDB_DatabaseCursorController*		cursor_controller )	{
	
	//	generate cursor name - RPDB_DATABASE_CURSOR_DEFAULT_HANDLE + "_" + cursor_controller->auto_name_count
	char*	cursor_name	=	calloc( strlen( RPDB_DATABASE_CURSOR_DEFAULT_HANDLE ) + strlen( RPDB_DATABASE_CURSOR_HANDLE_DELIMETER ) + 6, sizeof( char ) );

	sprintf( cursor_name, "%s%s%i",	RPDB_DATABASE_CURSOR_DEFAULT_HANDLE, 
																	RPDB_DATABASE_CURSOR_HANDLE_DELIMETER,
																	++cursor_controller->auto_name_count  );

	//	open a new cursor with name
	RPDB_DatabaseCursor*	return_cursor	=	RPDB_DatabaseCursorController_cursorForName(	cursor_controller,
																																											cursor_name );

	free( cursor_name );

	return return_cursor;
}

/*************************
*  closeCursorForName  *
*************************/

RPDB_DatabaseCursorController* RPDB_DatabaseCursorController_closeCursorForName(	RPDB_DatabaseCursorController*		cursor_controller,
																																									char*															cursor_name )	{
	
	RPDB_DatabaseCursor*	database_cursor	=	RPDB_DatabaseCursorController_cursorForName(	cursor_controller,
																																												cursor_name );
	RPDB_DatabaseCursor_close( database_cursor );
	
	return cursor_controller;															
}

/************************
*  freeCursorForName  *
************************/

void RPDB_DatabaseCursorController_freeCursorForName(	RPDB_DatabaseCursorController*		cursor_controller,
																											char*															cursor_name )	{

	RPDB_DatabaseCursor*	database_cursor	=	RPDB_DatabaseCursorController_cursorForName(	cursor_controller,
																																												cursor_name );
	RPDB_DatabaseCursor_free( & database_cursor );
	
	RPDB_RuntimeStorage_deleteRecordForRawKey(	cursor_controller->runtime_storage,
																							cursor_name,
																							( strlen( cursor_name ) + 1 ) * sizeof( char ) );
}

/***************
*  allCursors  *
***************/

//	Return a list of database names that have been created and stored in this controller
RPDB_DatabaseCursor** RPDB_DatabaseCursorController_allCursors( RPDB_DatabaseCursorController* cursor_controller )	{

	RPDB_RuntimeStorage_countRecords( cursor_controller->runtime_storage );
	
	RPDB_DatabaseCursor*	this_cursor;
	
	RPDB_DatabaseCursor**	cursor_array	=	calloc(	cursor_controller->runtime_storage->record_count, sizeof( RPDB_DatabaseCursor ) );
	
	int				which_cursor	=	0;
	
	while ( ( this_cursor = (RPDB_DatabaseCursor*) *(uintptr_t*) RPDB_Record_rawData( RPDB_RuntimeStorage_nextRecord( cursor_controller->runtime_storage ) ) ) )	{
		
		cursor_array[ which_cursor ] = this_cursor;
		
		which_cursor++;
	}
	
	return cursor_array;
}

/********************
*  closeAllCursors  *
********************/

void RPDB_DatabaseCursorController_closeAllCursors( RPDB_DatabaseCursorController* cursor_controller )	{

	//	our cursor controller in runtime storage doesn't have runtime storage, cursors are closed manually
	if (	cursor_controller 
		&&	cursor_controller->runtime_storage )	{

		RPDB_RuntimeStorage_iterate( cursor_controller->runtime_storage );
		
		RPDB_DatabaseCursor*	this_cursor = NULL;
		
		void*	raw_data	=	NULL;
		while ( ( raw_data	=	RPDB_Record_rawData(	RPDB_RuntimeStorage_nextRecord( cursor_controller->runtime_storage ) ) ) != NULL )	{

			this_cursor = (RPDB_DatabaseCursor*) *(uintptr_t*) raw_data;
			
			RPDB_DatabaseCursor_close( this_cursor );			
		}
	}
}

/*******************
*  freeAllCursors  *
*******************/

//	free all cursors; close if necessary
void RPDB_DatabaseCursorController_freeAllCursors( RPDB_DatabaseCursorController* cursor_controller )	{
	
	RPDB_DatabaseCursor*	runtime_storage_cursor	=	cursor_controller->runtime_storage->database_cursor;
	
	RPDB_DatabaseCursor_retrieveFirst( runtime_storage_cursor );
	
	RPDB_Record*	record		=	NULL;
	
	while ( ( record = RPDB_DatabaseCursor_iterate( runtime_storage_cursor ) ) != NULL )	{
		
		RPDB_DatabaseCursor* this_cursor	=	(RPDB_DatabaseCursor*) *(uintptr_t*) RPDB_Record_rawData( record );
		
		if ( this_cursor != NULL )	{
			//	free cursor - function already names proper closing etc.
			RPDB_DatabaseCursor_free( & this_cursor );
		}
		
		RPDB_DatabaseCursor_deleteCurrentRecord( runtime_storage_cursor );
	}
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

/*********************
*  uniqueIdentifier  *
*********************/

char* RPDB_DatabaseCursorController_internal_uniqueIdentifier( RPDB_DatabaseCursorController* database_cursor_controller )	{
	
	RPDB_Database*	parent_database					=	database_cursor_controller->parent_database;
	char*						parent_database_name		=	parent_database->name;
	
	uintptr_t		parent_database_address	=	(uintptr_t) parent_database;
	
	char*		parent_database_address_string		=	calloc( 21, sizeof( char ) );
	sprintf(	parent_database_address_string,
						"%" PRIxPTR "",			parent_database_address );
	
	//	we have a name to identify our database cursor instance, which guarantees that names
	//	will always be unique for storage
	int			unique_identifier_length			=		strlen( "database_cursor_controller"  ) 
																					+	strlen( RPDB_DELIMITER )
																					+	strlen( parent_database_name )
																					+	strlen( RPDB_DELIMITER )
																					+	strlen( parent_database_address_string )
																					+	1;
	char*		unique_identifier					=	calloc( unique_identifier_length, sizeof( char ) );
	
	sprintf(	unique_identifier,
						"%s%s%s%s%s",		"database_cursor_controller",
														RPDB_DELIMITER,
														parent_database_name,
														RPDB_DELIMITER,
														parent_database_address_string	);
	
	free( parent_database_address_string );
	parent_database_address_string	=	NULL;
	
	return unique_identifier;
}
