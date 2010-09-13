/*
 *		RPDB::DatabaseController::Database(Primary)::JoinController::JoinCursor
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseJoinCursor.h"
#include "RPDB_DatabaseJoinCursor_internal.h"

#include "RPDB_DatabaseJoinController.h"
#include "RPDB_DatabaseJoinController_internal.h"

#include "RPDB_Database.h"
#include "RPDB_Database_internal.h"
#include "RPDB_DatabaseCursor.h"

#include "RPDB_Environment.h"

#include "RPDB_Record.h"
#include "RPDB_Key.h"

#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_SettingsController.h"
#include "RPDB_DatabaseJoinSettingsController.h"
#include "RPDB_DatabaseJoinSettingsController_internal.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_DatabaseJoinCursor* RPDB_DatabaseJoinCursor_new( RPDB_DatabaseJoinController* parent_join_controller )	{

	RPDB_DatabaseJoinCursor*		join_cursor = calloc( 1, sizeof( RPDB_DatabaseJoinCursor ) );
	
	if ( parent_join_controller->runtime_storage_database != NULL )	{
		join_cursor->runtime_identifier =	RPDB_Database_internal_storeRuntimeAddress(	parent_join_controller->runtime_storage_database,
																																									(void*) join_cursor );
	}
	
	join_cursor->parent_join_controller = parent_join_controller;
		
	//	Make call to instantiate local settings controller
	join_cursor->settings_controller	=	RPDB_DatabaseJoinSettingsController_internal_copyOfSettingsControllerForInstance( RPDB_DatabaseSettingsController_joinSettingsController( RPDB_Database_settingsController( parent_join_controller->parent_database ) ) );
	
	return join_cursor;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseJoinCursor_free(	RPDB_DatabaseJoinCursor** join_cursor )	{

	if ( ( *join_cursor )->parent_join_controller->runtime_storage_database != NULL )	{
		RPDB_Database_internal_freeStoredRuntimeAddress(	( *join_cursor )->parent_join_controller->runtime_storage_database,
																											( *join_cursor )->runtime_identifier );
	}
	RPDB_DatabaseJoinCursor_internal_freeFromRuntimeStorage( join_cursor );
}

/***************************
*  freeFromRuntimeStorage  *
***************************/
void RPDB_DatabaseJoinCursor_internal_freeFromRuntimeStorage(	RPDB_DatabaseJoinCursor** join_cursor )	{

	//	close self if open
	if ( RPDB_DatabaseJoinCursor_isOpen( *join_cursor ) )	{
		RPDB_DatabaseJoinCursor_close( *join_cursor );
	}

	//	local settings controller
	if ( ( *join_cursor )->settings_controller != NULL )	{
		RPDB_DatabaseJoinSettingsController_free(  & ( ( *join_cursor )->settings_controller ) );
	}

	//	self
	free( *join_cursor );
	*join_cursor	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_DatabaseJoinSettingsController* RPDB_DatabaseJoinCursor_settingsController(	RPDB_DatabaseJoinCursor* join_cursor )	{
	return join_cursor->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseJoinCursor_parentEnvironment(	RPDB_DatabaseJoinCursor* join_cursor )	{
	return join_cursor->parent_join_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabaseJoinController  *
***************************************/
RPDB_DatabaseJoinController* RPDB_DatabaseJoinCursor_parentDatabaseJoinController(	RPDB_DatabaseJoinCursor* join_cursor )	{
	return join_cursor->parent_join_controller;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseJoinCursor_parentDatabase(	RPDB_DatabaseJoinCursor* join_cursor )	{
	return join_cursor->parent_join_controller->parent_database;
}

/******************
*  isOpen  *
******************/

BOOL RPDB_DatabaseJoinCursor_isOpen( RPDB_DatabaseJoinCursor* join_cursor )	{
	
	return join_cursor->is_open;
}

/******************
*  close  *
******************/

void RPDB_DatabaseJoinCursor_close( RPDB_DatabaseJoinCursor* join_cursor )	{
	
	if ( RPDB_DatabaseJoinCursor_isOpen( join_cursor ) )	{
		join_cursor->wrapped_bdb_join_cursor->close( join_cursor->wrapped_bdb_join_cursor );
		join_cursor->is_open	=	FALSE;
	}
}

/******************
*  retrieve  *
******************/

RPDB_Record* RPDB_DatabaseJoinCursor_retrieveKey(	RPDB_DatabaseJoinCursor*	join_cursor,
													RPDB_Key*					key	)	{

	RPDB_Record*		record	=	RPDB_Record_new( join_cursor->primary_database );

	//	Free the empty RPDB_DBT* we allocated
	RPDB_Key_free( & ( record->key ) );

	//	point to the new key
	record->key	=	key;

	join_cursor->wrapped_bdb_join_cursor->get(	join_cursor->wrapped_bdb_join_cursor,
												record->key->wrapped_bdb_dbt->data,
												record->data->wrapped_bdb_dbt->data,
												RPDB_DatabaseJoinSettingsController_internal_retrieveFlags( RPDB_DatabaseSettingsController_joinSettingsController( RPDB_Database_settingsController( join_cursor->primary_database ) ) ) );
	
	return record;
}

/******************************
*  retrieveRecordNumber  *
******************************/

//	Do not use the data value found in all of the cursors as a lookup key for the primary database, 
//	but simply return it in the key parameter instead. The data parameter is left unchanged.
//	For DB_JOIN_ITEM to be specified, the underlying database_cursor must have been returned from the DB->join method.
//	DB_JOIN_ITEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPDB_Record* RPDB_DatabaseJoinCursor_retrievePrimaryKeysForJoinData( RPDB_DatabaseJoinCursor* join_cursor )	{

	//	We return a record that doesn't belong to any database (but rather to a join database_cursor)
	RPDB_Record*	record	=	RPDB_Record_new( NULL );

	join_cursor->wrapped_bdb_join_cursor->get(	join_cursor->wrapped_bdb_join_cursor,
												record->key->wrapped_bdb_dbt->data,
												record->data->wrapped_bdb_dbt->data,
												DB_JOIN_ITEM | RPDB_DatabaseJoinSettingsController_internal_retrieveFlags( RPDB_DatabaseSettingsController_joinSettingsController( RPDB_Database_settingsController( join_cursor->primary_database ) ) ) );	
	return record;
}

/*******************************************************************************************************************************************************************************************
													Iteration
*******************************************************************************************************************************************************************************************/

/****************************
*  iterate  *
****************************/

//	each call to iterate returns a record from the join cursor
RPDB_Record* RPDB_DatabaseJoinCursor_iterate(	RPDB_DatabaseJoinCursor*	database_join_cursor )	{
	
	RPDB_Record*	record	=	RPDB_Record_new( database_join_cursor->primary_database );//RPDB_DatabaseCursor_retrieveCurrent( database_join_cursor->cursor_list[ 0 ] );

	int	error	=	0;
	if ( ( error  = database_join_cursor->wrapped_bdb_join_cursor->get(	database_join_cursor->wrapped_bdb_join_cursor,
																																			record->key->wrapped_bdb_dbt,
																																			record->data->wrapped_bdb_dbt,
																																			RPDB_NO_FLAGS ) ) != 0 ) {
		
		//	If we get here we want no error or DB_NOTFOUND
		if ( error == DB_NOTFOUND )	{
			record->result = FALSE;
		}
		else {
			
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_join_cursor->primary_database->parent_database_controller->parent_environment ), 
																										error, 
																										"RPDB_DatabaseJoinCursor_iterate" );		
		}
	}

	return record;
}
