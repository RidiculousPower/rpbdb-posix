/*
 *		Rbdb::DatabaseController::Database(Primary)::JoinController::JoinCursor
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseJoinCursor.h"
#include "Rbdb_DatabaseJoinCursor_internal.h"

#include "Rbdb_DatabaseJoinController.h"
#include "Rbdb_DatabaseJoinController_internal.h"

#include "Rbdb_Database.h"
#include "Rbdb_Database_internal.h"
#include "Rbdb_DatabaseCursor.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Record.h"
#include "Rbdb_Key.h"

#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_SettingsController.h"
#include "Rbdb_DatabaseJoinSettingsController.h"
#include "Rbdb_DatabaseJoinSettingsController_internal.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

Rbdb_DatabaseJoinCursor* Rbdb_DatabaseJoinCursor_new( Rbdb_DatabaseJoinController* parent_join_controller )	{

	Rbdb_DatabaseJoinCursor*		join_cursor = calloc( 1, sizeof( Rbdb_DatabaseJoinCursor ) );
	
	if ( parent_join_controller->runtime_storage_database != NULL )	{
		join_cursor->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_join_controller->runtime_storage_database,
																																									(void*) join_cursor );
	}
	
	join_cursor->parent_join_controller = parent_join_controller;
		
	//	Make call to instantiate local settings controller
	join_cursor->settings_controller	=	Rbdb_DatabaseJoinSettingsController_internal_copyOfSettingsControllerForInstance( Rbdb_DatabaseSettingsController_joinSettingsController( Rbdb_Database_settingsController( parent_join_controller->parent_database ) ) );
	
	return join_cursor;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseJoinCursor_free(	Rbdb_DatabaseJoinCursor** join_cursor )	{

	if ( ( *join_cursor )->parent_join_controller->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *join_cursor )->parent_join_controller->runtime_storage_database,
																											( *join_cursor )->runtime_identifier );
	}
	Rbdb_DatabaseJoinCursor_internal_freeFromRuntimeStorage( join_cursor );
}

/***************************
*  freeFromRuntimeStorage  *
***************************/
void Rbdb_DatabaseJoinCursor_internal_freeFromRuntimeStorage(	Rbdb_DatabaseJoinCursor** join_cursor )	{

	//	close self if open
	if ( Rbdb_DatabaseJoinCursor_isOpen( *join_cursor ) )	{
		Rbdb_DatabaseJoinCursor_close( *join_cursor );
	}

	//	local settings controller
	if ( ( *join_cursor )->settings_controller != NULL )	{
		Rbdb_DatabaseJoinSettingsController_free(  & ( ( *join_cursor )->settings_controller ) );
	}

	//	self
	free( *join_cursor );
	*join_cursor	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_DatabaseJoinSettingsController* Rbdb_DatabaseJoinCursor_settingsController(	Rbdb_DatabaseJoinCursor* join_cursor )	{
	return join_cursor->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseJoinCursor_parentEnvironment(	Rbdb_DatabaseJoinCursor* join_cursor )	{
	return join_cursor->parent_join_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabaseJoinController  *
***************************************/
Rbdb_DatabaseJoinController* Rbdb_DatabaseJoinCursor_parentDatabaseJoinController(	Rbdb_DatabaseJoinCursor* join_cursor )	{
	return join_cursor->parent_join_controller;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseJoinCursor_parentDatabase(	Rbdb_DatabaseJoinCursor* join_cursor )	{
	return join_cursor->parent_join_controller->parent_database;
}

/******************
*  isOpen  *
******************/

BOOL Rbdb_DatabaseJoinCursor_isOpen( Rbdb_DatabaseJoinCursor* join_cursor )	{
	
	return join_cursor->is_open;
}

/******************
*  close  *
******************/

void Rbdb_DatabaseJoinCursor_close( Rbdb_DatabaseJoinCursor* join_cursor )	{
	
	if ( Rbdb_DatabaseJoinCursor_isOpen( join_cursor ) )	{
		join_cursor->wrapped_bdb_join_cursor->close( join_cursor->wrapped_bdb_join_cursor );
		join_cursor->is_open	=	FALSE;
	}
}

/******************
*  retrieve  *
******************/

Rbdb_Record* Rbdb_DatabaseJoinCursor_retrieveKey(	Rbdb_DatabaseJoinCursor*	join_cursor,
													Rbdb_Key*					key	)	{

	Rbdb_Record*		record	=	Rbdb_Record_new( join_cursor->primary_database );

	//	Free the empty RBDB_DBT* we allocated
	Rbdb_Key_free( & ( record->key ) );

	//	point to the new key
	record->key	=	key;

	join_cursor->wrapped_bdb_join_cursor->get(	join_cursor->wrapped_bdb_join_cursor,
												record->key->wrapped_bdb_dbt->data,
												record->data->wrapped_bdb_dbt->data,
												Rbdb_DatabaseJoinSettingsController_internal_retrieveFlags( Rbdb_DatabaseSettingsController_joinSettingsController( Rbdb_Database_settingsController( join_cursor->primary_database ) ) ) );
	
	return record;
}

/******************************
*  retrieveRecordNumber  *
******************************/

//	Do not use the data value found in all of the cursors as a lookup key for the primary database, 
//	but simply return it in the key parameter instead. The data parameter is left unchanged.
//	For DB_JOIN_ITEM to be specified, the underlying database_cursor must have been returned from the DB->join method.
//	DB_JOIN_ITEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
Rbdb_Record* Rbdb_DatabaseJoinCursor_retrievePrimaryKeysForJoinData( Rbdb_DatabaseJoinCursor* join_cursor )	{

	//	We return a record that doesn't belong to any database (but rather to a join database_cursor)
	Rbdb_Database*	parent_database	=	join_cursor->parent_join_controller->parent_database;
	Rbdb_Record*	record	=	Rbdb_Record_new( parent_database );

	join_cursor->wrapped_bdb_join_cursor->get(	join_cursor->wrapped_bdb_join_cursor,
												record->key->wrapped_bdb_dbt->data,
												record->data->wrapped_bdb_dbt->data,
												DB_JOIN_ITEM | Rbdb_DatabaseJoinSettingsController_internal_retrieveFlags( Rbdb_DatabaseSettingsController_joinSettingsController( Rbdb_Database_settingsController( join_cursor->primary_database ) ) ) );	
	return record;
}

/*******************************************************************************************************************************************************************************************
													Iteration
*******************************************************************************************************************************************************************************************/

/****************************
*  iterate  *
****************************/

//	each call to iterate returns a record from the join cursor
Rbdb_Record* Rbdb_DatabaseJoinCursor_iterate(	Rbdb_DatabaseJoinCursor*	database_join_cursor )	{
	
	Rbdb_Record*	record	=	Rbdb_Record_new( database_join_cursor->primary_database );//Rbdb_DatabaseCursor_retrieveCurrent( database_join_cursor->cursor_list[ 0 ] );

	int	error	=	0;
	if ( ( error  = database_join_cursor->wrapped_bdb_join_cursor->get(	database_join_cursor->wrapped_bdb_join_cursor,
																																			record->key->wrapped_bdb_dbt,
																																			record->data->wrapped_bdb_dbt,
																																			RBDB_NO_FLAGS ) ) != 0 ) {
		
		//	If we get here we want no error or DB_NOTFOUND
		if ( error == DB_NOTFOUND )	{
			record->result = FALSE;
		}
		else {
			
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_join_cursor->primary_database->parent_database_controller->parent_environment ), 
																										error, 
																										"Rbdb_DatabaseJoinCursor_iterate" );		
		}
	}

	return record;
}
