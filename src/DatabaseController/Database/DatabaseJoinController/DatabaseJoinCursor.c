/*
 *		RPbdb::DatabaseController::Database(Primary)::JoinController::JoinCursor
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseJoinCursor.h"
#include "DatabaseJoinCursor_internal.h"

#include "DatabaseJoinController.h"
#include "DatabaseJoinController_internal.h"

#include "Database.h"
#include "Database_internal.h"
#include "DatabaseCursor.h"

#include "Environment.h"

#include "Record.h"
#include "Key.h"

#include "DatabaseSettingsController.h"
#include "SettingsController.h"
#include "DatabaseJoinSettingsController.h"
#include "DatabaseJoinSettingsController_internal.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_DatabaseJoinCursor* RPbdb_DatabaseJoinCursor_new( RPbdb_DatabaseJoinController* parent_join_controller )	{

	RPbdb_DatabaseJoinCursor*		join_cursor = calloc( 1, sizeof( RPbdb_DatabaseJoinCursor ) );
	
	if ( parent_join_controller->runtime_storage_database != NULL )	{
		join_cursor->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_join_controller->runtime_storage_database,
																																									(void*) join_cursor );
	}
	
	join_cursor->parent_join_controller = parent_join_controller;
		
	//	Make call to instantiate local settings controller
	join_cursor->settings_controller	=	RPbdb_DatabaseJoinSettingsController_internal_copyOfSettingsControllerForInstance( RPbdb_DatabaseSettingsController_joinSettingsController( RPbdb_Database_settingsController( parent_join_controller->parent_database ) ) );
	
	return join_cursor;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseJoinCursor_free(	RPbdb_DatabaseJoinCursor** join_cursor )	{

	if ( ( *join_cursor )->parent_join_controller->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *join_cursor )->parent_join_controller->runtime_storage_database,
																											( *join_cursor )->runtime_identifier );
	}
  //  free all cursors
  if ( ( *join_cursor )->cursor_list ) {
    int which_cursor  = 0;
    for ( which_cursor = 0 ; which_cursor < ( *join_cursor )->number_of_cursors ; which_cursor++ )  {
      RPbdb_DatabaseCursor*  this_cursor = ( *join_cursor )->cursor_list[ which_cursor ];
      
      RPbdb_DatabaseCursor_free( & this_cursor );
    }
  }
	RPbdb_DatabaseJoinCursor_internal_freeFromRuntimeStorage( join_cursor );
}

/***************************
*  freeFromRuntimeStorage  *
***************************/
void RPbdb_DatabaseJoinCursor_internal_freeFromRuntimeStorage(	RPbdb_DatabaseJoinCursor** join_cursor )	{

	//	close self if open
	if ( RPbdb_DatabaseJoinCursor_isOpen( *join_cursor ) )	{
		RPbdb_DatabaseJoinCursor_close( *join_cursor );
	}

	//	local settings controller
	if ( ( *join_cursor )->settings_controller != NULL )	{
		RPbdb_DatabaseJoinSettingsController_free(  & ( ( *join_cursor )->settings_controller ) );
	}

	//	self
	free( *join_cursor );
	*join_cursor	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_DatabaseJoinSettingsController* RPbdb_DatabaseJoinCursor_settingsController(	RPbdb_DatabaseJoinCursor* join_cursor )	{
	return join_cursor->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseJoinCursor_parentEnvironment(	RPbdb_DatabaseJoinCursor* join_cursor )	{
	return join_cursor->parent_join_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabaseJoinController  *
***************************************/
RPbdb_DatabaseJoinController* RPbdb_DatabaseJoinCursor_parentDatabaseJoinController(	RPbdb_DatabaseJoinCursor* join_cursor )	{
	return join_cursor->parent_join_controller;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseJoinCursor_parentDatabase(	RPbdb_DatabaseJoinCursor* join_cursor )	{
	return join_cursor->parent_join_controller->parent_database;
}

/******************
*  isOpen  *
******************/

BOOL RPbdb_DatabaseJoinCursor_isOpen( RPbdb_DatabaseJoinCursor* join_cursor )	{
	
	return join_cursor->is_open;
}

/******************
*  close  *
******************/

void RPbdb_DatabaseJoinCursor_close( RPbdb_DatabaseJoinCursor* join_cursor )	{
	
	if ( RPbdb_DatabaseJoinCursor_isOpen( join_cursor ) )	{
    
		join_cursor->wrapped_bdb_join_cursor->close( join_cursor->wrapped_bdb_join_cursor );
		join_cursor->is_open	=	FALSE;
	}

  //  close all associated database cursors
  if ( join_cursor->cursor_list ) {
    int which_cursor  = 0;
    for ( which_cursor = 0 ; which_cursor < join_cursor->number_of_cursors ; which_cursor++ )  {
      RPbdb_DatabaseCursor*  this_cursor = join_cursor->cursor_list[ which_cursor ];
      
      //  BDB already closed and freed its cursor instance when we closed the join cursor
      //  we set now to NULL so we don't re-close/free it (we likely still need to close RPbdb resources)
      this_cursor->wrapped_bdb_cursor = NULL;
      
      RPbdb_DatabaseCursor_close( this_cursor );
    }
  }
}

/******************
*  retrieve  *
******************/

RPbdb_Record* RPbdb_DatabaseJoinCursor_retrieveKey(	RPbdb_DatabaseJoinCursor*	join_cursor,
													RPbdb_Key*					key	)	{

	RPbdb_Record*		record	=	RPbdb_Record_new( join_cursor->primary_database );

	//	Free the empty RPbdb_DBT* we allocated
	RPbdb_Key_free( & ( record->key ) );

	//	point to the new key
	record->key	=	key;

	join_cursor->wrapped_bdb_join_cursor->get(	join_cursor->wrapped_bdb_join_cursor,
												record->key->wrapped_bdb_dbt->data,
												record->data->wrapped_bdb_dbt->data,
												RPbdb_DatabaseJoinSettingsController_internal_retrieveFlags( RPbdb_DatabaseSettingsController_joinSettingsController( RPbdb_Database_settingsController( join_cursor->primary_database ) ) ) );
	
	return record;
}

/******************************
*  retrieveRecordNumber  *
******************************/

//	Do not use the data value found in all of the cursors as a lookup key for the primary database, 
//	but simply return it in the key parameter instead. The data parameter is left unchanged.
//	For DB_JOIN_ITEM to be specified, the underlying database_cursor must have been returned from the DB->join method.
//	DB_JOIN_ITEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPbdb_Record* RPbdb_DatabaseJoinCursor_retrievePrimaryKeysForJoinData( RPbdb_DatabaseJoinCursor* join_cursor )	{

	//	We return a record that doesn't belong to any database (but rather to a join database_cursor)
	RPbdb_Database*	parent_database	=	join_cursor->parent_join_controller->parent_database;
	RPbdb_Record*	record	=	RPbdb_Record_new( parent_database );

	join_cursor->wrapped_bdb_join_cursor->get(	join_cursor->wrapped_bdb_join_cursor,
												record->key->wrapped_bdb_dbt->data,
												record->data->wrapped_bdb_dbt->data,
												DB_JOIN_ITEM | RPbdb_DatabaseJoinSettingsController_internal_retrieveFlags( RPbdb_DatabaseSettingsController_joinSettingsController( RPbdb_Database_settingsController( join_cursor->primary_database ) ) ) );	
	return record;
}

/*******************************************************************************************************************************************************************************************
													Iteration
*******************************************************************************************************************************************************************************************/

/****************************
*  iterate  *
****************************/

//	each call to iterate returns a record from the join cursor
RPbdb_Record* RPbdb_DatabaseJoinCursor_iterate(	RPbdb_DatabaseJoinCursor*	database_join_cursor )	{
	
	RPbdb_Record*	record	=	RPbdb_Record_new( database_join_cursor->primary_database );

	int	error	=	0;
	if ( ( error  = database_join_cursor->wrapped_bdb_join_cursor->get(	database_join_cursor->wrapped_bdb_join_cursor,
																																			record->key->wrapped_bdb_dbt,
																																			record->data->wrapped_bdb_dbt,
																																			RPBDB_NO_FLAGS ) ) != 0 ) {
		
		//	If we get here we want no error or DB_NOTFOUND
		if ( error == DB_NOTFOUND )	{
			record->result = FALSE;
		}
		else {
			
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_join_cursor->primary_database->parent_database_controller->parent_environment ), 
																										error, 
																										"DatabaseJoinCursor_iterate" );		
		}

	}
  else  {
  
    record->result = TRUE;
  }

	return record;
}
