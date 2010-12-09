/*
 *		Rbdb::DatabaseController::Database(Primary)::JoinController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseJoinController.h"
#include "Rbdb_DatabaseJoinController_internal.h"

#include "Rbdb_DatabaseJoinCursor.h"

#include "Rbdb_Database.h"
#include "Rbdb_Database_internal.h"
#include "Rbdb_DatabaseCursor.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Record.h"
#include "Rbdb_Data.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseJoinSettingsController.h"
#include "Rbdb_DatabaseJoinSettingsController_internal.h"

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

Rbdb_DatabaseJoinController* Rbdb_DatabaseJoinController_new( Rbdb_Database* parent_database )	{

	Rbdb_DatabaseJoinController*	database_join_controller = calloc( 1, sizeof( Rbdb_DatabaseJoinController ) );

	database_join_controller->parent_database	=	parent_database;

	Rbdb_RUNTIME_STORAGE( database_join_controller, "database_join_controller" );

	return database_join_controller;
}

/*********
*  free  *
*********/

void Rbdb_DatabaseJoinController_free(	Rbdb_DatabaseJoinController** database_join_controller )	{

	//	close and free any cursors
	Rbdb_DatabaseJoinController_freeAllCursors( *database_join_controller );

	//	free runtime storage
	if ( ( *database_join_controller )->runtime_storage_database != NULL )	{
		Rbdb_Database_free( & ( ( *database_join_controller )->runtime_storage_database ) );
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

Rbdb_DatabaseJoinSettingsController* Rbdb_DatabaseJoinController_settingsController(	Rbdb_DatabaseJoinController* database_join_controller )	{

	Rbdb_DatabaseSettingsController*			database_settings_controller			=	Rbdb_Database_settingsController( database_join_controller->parent_database );
	Rbdb_DatabaseJoinSettingsController*	database_join_settings_controller	=	Rbdb_DatabaseSettingsController_joinSettingsController( database_settings_controller );
	
	return database_join_settings_controller;
}

/*******************
*  parentDatabase  *
*******************/

Rbdb_Database* Rbdb_DatabaseJoinController_parentDatabase(	Rbdb_DatabaseJoinController* database_join_controller )	{
	return database_join_controller->parent_database;
}

/**********************
*  parentEnvironment  *
**********************/

Rbdb_Environment* Rbdb_DatabaseJoinController_parentEnvironment(	Rbdb_DatabaseJoinController* database_join_controller )	{
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
Rbdb_DatabaseJoinCursor* Rbdb_DatabaseJoinController_join(	Rbdb_DatabaseJoinController*		join_cursor_controller,
																Rbdb_DatabaseCursor**				cursor_list	)	{
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

	Rbdb_DatabaseJoinCursor*	join_cursor			=	Rbdb_DatabaseJoinCursor_new(	join_cursor_controller	);

	//	Store a reference cursor_list for this join database_cursor
	join_cursor->cursor_list							=	cursor_list;
	join_cursor->wrapped_bdb_cursor_list	=	bdb_cursor_list;
	
	join_cursor->primary_database			=	join_cursor_controller->parent_database;

	join_cursor->primary_database->wrapped_bdb_database->join(	//	Get our primary database reference from the first database_cursor in our list
																join_cursor->primary_database->wrapped_bdb_database,
																bdb_cursor_list,
																&( join_cursor->wrapped_bdb_join_cursor ),
																Rbdb_DatabaseJoinSettingsController_internal_joinFlags( Rbdb_DatabaseSettingsController_joinSettingsController( Rbdb_Database_settingsController( join_cursor->primary_database ) ) ) );
	
	join_cursor->is_open	=	TRUE;
	
	return join_cursor;
}

/********************
*  closeAllCursors  *
********************/

void Rbdb_DatabaseJoinController_closeAllCursors( Rbdb_DatabaseJoinController* database_join_controller )	{

	Rbdb_Database_internal_closeAllStoredRuntimeAddresses(	database_join_controller->runtime_storage_database,
																													(void *(*)(void*)) & Rbdb_DatabaseJoinCursor_close );
}

/*******************
*  freeAllCursors  *
*******************/

void Rbdb_DatabaseJoinController_freeAllCursors( Rbdb_DatabaseJoinController* database_join_controller )	{

	Rbdb_DatabaseJoinController_closeAllCursors( database_join_controller );
	Rbdb_Database_internal_freeAllStoredRuntimeAddresses(	database_join_controller->runtime_storage_database,
																												(void *(*)(void**)) & Rbdb_DatabaseJoinCursor_internal_freeFromRuntimeStorage );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

