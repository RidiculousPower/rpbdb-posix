/*
 *		RPDB::DatabaseController::Database(Primary)::JoinController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseJoinController.h"
#include "RPDB_DatabaseJoinController_internal.h"

#include "RPDB_DatabaseJoinCursor.h"

#include "RPDB_Database.h"
#include "RPDB_DatabaseCursor.h"

#include "RPDB_Environment.h"

#include "RPDB_Record.h"
#include "RPDB_Data.h"

#include "RPDB_SettingsController.h"
#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_DatabaseJoinSettingsController.h"
#include "RPDB_DatabaseJoinSettingsController_internal.h"

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

RPDB_DatabaseJoinController* RPDB_DatabaseJoinController_new( RPDB_Database* parent_database )	{

	RPDB_DatabaseJoinController*	database_join_controller = calloc( 1, sizeof( RPDB_DatabaseJoinController ) );

	char*		join_controller_runtime_storage_name	=	RPDB_DatabaseJoinController_internal_uniqueIdentifier( database_join_controller );

	RPDB_Environment*	environment	=	parent_database->parent_database_controller->parent_environment;
	
	//	Initialize our runtime storage for the database_cursor_controller
	database_join_controller->runtime_storage	=	RPDB_RuntimeStorageController_runtimeStorageInEnvironmentWithName(	RPDB_RuntimeStorageController_sharedInstance(),
																															environment,
																															join_controller_runtime_storage_name );
	
	return database_join_controller;
}

/*********
*  free  *
*********/

void RPDB_DatabaseJoinController_free(	RPDB_DatabaseJoinController** database_join_controller )	{

	//	close and free any cursors
	RPDB_DatabaseJoinController_freeAllCursors( *database_join_controller );

	//	free runtime storage
	if ( ( *database_join_controller )->runtime_storage != NULL )	{
		RPDB_RuntimeStorage_free( & ( ( *database_join_controller )->runtime_storage ) );
	}

	//	free self
	free( *database_join_controller );
	*database_join_controller	=	NULL;
}

/*******************************************************************************************************************************************************************************************
															Accessor Methods
*******************************************************************************************************************************************************************************************/

/***********************
*  settingsController  *
***********************/

RPDB_DatabaseJoinSettingsController* RPDB_DatabaseJoinController_settingsController(	RPDB_DatabaseJoinController* database_join_controller )	{
	return database_join_controller->settings_controller;
}

/*******************
*  parentDatabase  *
*******************/

RPDB_Database* RPDB_DatabaseJoinController_parentDatabase(	RPDB_DatabaseJoinController* database_join_controller )	{
	return database_join_controller->parent_database;
}

/**********************
*  parentEnvironment  *
**********************/

RPDB_Environment* RPDB_DatabaseJoinController_parentEnvironment(	RPDB_DatabaseJoinController* database_join_controller )	{
	return database_join_controller->parent_database->parent_database_controller->parent_environment;
}

/*******************************************************************************************************************************************************************************************
															Methods
*******************************************************************************************************************************************************************************************/

/*********
*  join  *
*********/

//	FIX - this should be moved into the cursor as open
//	we should then have the join cursor controller operate just like the other cursor controllers

//	The curslist parameter contains a NULL terminated array of cursors. Each database_cursor must have been initialized to refer to the key 
//	on which the underlying database should be joined. Typically, this initialization is done by a DBcursor->get call with the 
//	DB_SET flag specified. Once the cursors have been passed as part of a curslist, they should not be accessed or modified until 
//	the newly created join database_cursor has been closed, or else inconsistent results may be returned.
//
//	the best join performance normally results from sorting the cursors from the one that refers to the least number of data items 
//	to the one that refers to the most. By default, DB->join does this sort on behalf of its caller.
//
//	For the returned join database_cursor to be used in a transaction-protected manner, the cursors listed in curslist must have been created within the context of the same transaction.
//
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
//	Assumes that all cursors in list have the same primary database (the first will be used)
//
//	Join cursors have the same name as the Database database_cursor that was used to initalize them
RPDB_DatabaseJoinCursor* RPDB_DatabaseJoinController_join(	RPDB_DatabaseJoinController*		join_cursor_controller,
																char*								join_cursor_name,
																RPDB_DatabaseCursor**				cursor_list	)	{
	//	Make sure we're joining something
	if ( cursor_list[ 0 ] == NULL )	{
		
		return NULL;
	}
	
	//	Since we've wrapped BDB we have to convert back and forth between DBC* arrays

	//	Count how many cursors
	int		number_of_cursors	=	0;
	while( cursor_list[ ++number_of_cursors ] != NULL );

	DBC**	bdb_cursor_list	=	(DBC**) calloc( number_of_cursors + 1, sizeof( DBC* ) );
	
	//	Now we can actually construct our array
	int	which_cursor = 0;
	while( cursor_list[ which_cursor ] != NULL )	{
		
		bdb_cursor_list[ which_cursor ]	=	cursor_list[ which_cursor ]->wrapped_bdb_cursor;
		
		which_cursor++;
	}
	//	Terminate the array with NULL
	bdb_cursor_list[ which_cursor ] = NULL;

	RPDB_DatabaseJoinCursor*	join_cursor			=	RPDB_DatabaseJoinController_cursorForName(	join_cursor_controller,
																										join_cursor_name	);

	//	Store a reference cursor_list for this join database_cursor
	join_cursor->cursor_list				=	cursor_list;
	join_cursor->wrapped_bdb_cursor_list	=	bdb_cursor_list;
	
	join_cursor->primary_database			=	join_cursor_controller->parent_database;

	join_cursor->primary_database->wrapped_bdb_database->join(	//	Get our primary database reference from the first database_cursor in our list
																join_cursor->primary_database->wrapped_bdb_database,
																bdb_cursor_list,
																&( join_cursor->wrapped_bdb_join_cursor ),
																RPDB_DatabaseJoinSettingsController_internal_joinFlags( RPDB_DatabaseSettingsController_joinSettingsController( RPDB_Database_settingsController( join_cursor->primary_database ) ) ) );
	
	join_cursor->is_open	=	TRUE;
	
	return join_cursor;
}

/********************
*  cursorForName  *
********************/

RPDB_DatabaseJoinCursor* RPDB_DatabaseJoinController_cursorForName(	RPDB_DatabaseJoinController*		database_join_controller,
																		char*						join_cursor_name )	{

	RPDB_DatabaseJoinCursor*	database_cursor;

	//	Check and see if join_cursor_name exists in runtime storage
	//	If it doesn't, we need to create it and store it
	if ( RPDB_RuntimeStorage_rawKeyExists(	database_join_controller->runtime_storage,
											join_cursor_name,
											( strlen( join_cursor_name ) + 1 ) * sizeof( char ) ) )	{
													
		database_cursor	=	RPDB_Data_rawData(	RPDB_Record_data(	RPDB_RuntimeStorage_retrieveRawKey(	database_join_controller->runtime_storage,
																											join_cursor_name,
																											( strlen( join_cursor_name ) + 1 ) * sizeof( char ) ) ) );
	}
	else	{
	
		//	Create a database_cursor for parent database
		database_cursor	=	RPDB_DatabaseJoinCursor_new( database_join_controller );
		
		database_cursor->name	=	strdup( join_cursor_name );
		
		uintptr_t		new_cursor_address	=	(uintptr_t) database_cursor;

		//	Store pointer to database_cursor in runtime storage
		RPDB_RuntimeStorage_insertRawKeyDataPair(	database_join_controller->runtime_storage,
													join_cursor_name,
													( strlen( join_cursor_name ) + 1 ) * sizeof( char ),
													& new_cursor_address,
													sizeof( uintptr_t ) );
	}
	
	return database_cursor;
}

/*************************
*  closeCursorForName  *
*************************/

RPDB_DatabaseJoinCursor* RPDB_DatabaseJoinController_closeCursorForName(	RPDB_DatabaseJoinController*		database_join_controller,
 																char*						join_cursor_name )	{
	
	RPDB_DatabaseJoinCursor*	database_cursor	=	RPDB_DatabaseJoinController_cursorForName(	database_join_controller,
																			join_cursor_name );
	RPDB_DatabaseJoinCursor_close( database_cursor );
	
	return database_cursor;															
}

/************************
*  freeCursorForName  *
************************/

void RPDB_DatabaseJoinController_freeCursorForName(	RPDB_DatabaseJoinController*		database_join_controller,
 												char*						join_cursor_name )	{

	RPDB_DatabaseJoinCursor*	database_cursor	=	RPDB_DatabaseJoinController_cursorForName(	database_join_controller,
																			join_cursor_name );
	RPDB_DatabaseJoinCursor_free( & database_cursor );
	
	RPDB_RuntimeStorage_deleteRecordForRawKey(	database_join_controller->runtime_storage,
												join_cursor_name,
												( strlen( join_cursor_name ) + 1 ) * sizeof( char ) );
}

/***************
*  allCursors  *
***************/

//	Return a list of database names that have been created and stored in this controller
RPDB_DatabaseJoinCursor** RPDB_DatabaseJoinController_allCursors( RPDB_DatabaseJoinController* database_join_controller )	{

	RPDB_RuntimeStorage_countRecords( database_join_controller->runtime_storage );
	
	RPDB_DatabaseJoinCursor*	this_cursor;
	
	RPDB_DatabaseJoinCursor**	cursor_array	=	calloc(	database_join_controller->runtime_storage->record_count, sizeof( RPDB_DatabaseJoinCursor ) );
	
	int				which_cursor	=	0;
	
	while ( ( this_cursor = (RPDB_DatabaseJoinCursor*) *(uintptr_t*) RPDB_Record_rawData( RPDB_RuntimeStorage_nextRecord( database_join_controller->runtime_storage ) ) ) )	{
		
		cursor_array[ which_cursor ] = this_cursor;
		
		which_cursor++;
	}
	
	return cursor_array;
}

/********************
*  closeAllCursors  *
********************/

void RPDB_DatabaseJoinController_closeAllCursors( RPDB_DatabaseJoinController* database_join_controller )	{

	//	our cursor controller in runtime storage doesn't have runtime storage, cursors are closed manually
	if (	database_join_controller 
		&&	database_join_controller->runtime_storage )	{
		
		RPDB_RuntimeStorage_iterate( database_join_controller->runtime_storage );
		
		RPDB_DatabaseJoinCursor*	this_cursor = NULL;
		
		void*	raw_data	=	NULL;
		while ( ( raw_data	=	RPDB_Record_rawData(	RPDB_RuntimeStorage_nextRecord( database_join_controller->runtime_storage ) ) ) != NULL )	{
			
			this_cursor = (RPDB_DatabaseJoinCursor*) *(uintptr_t*) raw_data;
			
			RPDB_DatabaseJoinCursor_close( this_cursor );			
		}
	}

}

/*******************
*  freeAllCursors  *
*******************/

void RPDB_DatabaseJoinController_freeAllCursors( RPDB_DatabaseJoinController* database_join_controller )	{

	RPDB_DatabaseCursor*	runtime_storage_cursor	=	database_join_controller->runtime_storage->database_cursor;
	
	RPDB_DatabaseCursor_retrieveFirst( runtime_storage_cursor );
	
	RPDB_Record*	record		=	NULL;
	
	while ( ( record = RPDB_DatabaseCursor_iterate( runtime_storage_cursor ) ) != NULL )	{
		
		RPDB_DatabaseJoinCursor* this_cursor	=	(RPDB_DatabaseJoinCursor*) *(uintptr_t*) RPDB_Record_rawData( record );
		
		if ( this_cursor != NULL )	{
			//	free cursor - function already names proper closing etc.
			RPDB_DatabaseJoinCursor_free( & this_cursor );
		}
		
		RPDB_DatabaseCursor_deleteCurrentRecord( runtime_storage_cursor );
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

char* RPDB_DatabaseJoinController_internal_uniqueIdentifier( RPDB_DatabaseJoinController* database_join_controller )	{
	
	RPDB_Database*	parent_database					=	database_join_controller->parent_database;
	char*			parent_database_name			=	parent_database->name;
	
	uintptr_t	parent_database_address	=	(uintptr_t) parent_database;

	char*		parent_database_address_string		=	calloc( 21, sizeof( char ) );
	sprintf(	parent_database_address_string,
						"%" PRIxPTR "",			parent_database_address );

	//	we have a name to identify our database cursor instance, which guarantees that names
	//	will always be unique for storage
	int			unique_identifier_length			=		strlen( "database_join_controller"  ) 
														+	strlen( RPDB_DELIMITER )
														+	strlen( parent_database_name )
														+	strlen( RPDB_DELIMITER )
														+	strlen( parent_database_address_string )
														+	1;
	char*		unique_identifier					=	calloc( unique_identifier_length, sizeof( char ) );
		
	sprintf(	unique_identifier,
				"%s%s%s%s%s",		"database_join_controller",
									RPDB_DELIMITER,
									parent_database_name,
									RPDB_DELIMITER,
									parent_database_address_string	);
	
	free( parent_database_address_string );
	parent_database_address_string	=	NULL;
	
	return unique_identifier;
}
