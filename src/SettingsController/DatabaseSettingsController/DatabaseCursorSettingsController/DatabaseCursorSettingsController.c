/*
 *		RPbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseCursorSettingsController.h"

#include "DatabaseCursorCacheSettingsController.h"
#include "DatabaseCursorReadWriteSettingsController.h"

#include "DatabaseCursorSettingsController_internal.h"
#include "DatabaseCachePrioritySettingsController_internal.h"
#include "DatabaseCursorReadWriteSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_DatabaseCursorSettingsController* RPbdb_DatabaseCursorSettingsController_new( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_DatabaseCursorSettingsController*		cursor_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseCursorSettingsController ) );

	cursor_settings_controller->parent_database_settings_controller = database_settings_controller;

	return cursor_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseCursorSettingsController_free(	RPbdb_DatabaseCursorSettingsController** database_cursor_settings_controller )	{

	if ( ( *database_cursor_settings_controller )->cache_controller != NULL )	{

		RPbdb_DatabaseCursorCacheSettingsController_free( & ( ( *database_cursor_settings_controller )->cache_controller ) );
	}
	if ( ( *database_cursor_settings_controller )->record_read_write_settings_controller != NULL )	{

		RPbdb_DatabaseCursorReadWriteSettingsController_free( & ( ( *database_cursor_settings_controller )->record_read_write_settings_controller ) );
	}

	free( *database_cursor_settings_controller );
	*database_cursor_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseCursorSettingsController_parentEnvironment(	RPbdb_DatabaseCursorSettingsController* database_cursor_settings_controller )	{
	return database_cursor_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseCursorSettingsController_parentDatabase(	RPbdb_DatabaseCursorSettingsController* database_cursor_settings_controller )	{
	return database_cursor_settings_controller->parent_database_settings_controller->parent_database;
}

/***************************************
*  parentDatabaseCursor  *
***************************************/
RPbdb_DatabaseCursor* RPbdb_DatabaseCursorSettingsController_parentDatabaseCursor(	RPbdb_DatabaseCursorSettingsController* database_cursor_settings_controller )	{
	return database_cursor_settings_controller->parent_database_cursor;
}


/**********************************
*  duplicateRetainsLocation  *
**********************************/

//	DB_POSITION		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_dup.html
BOOL RPbdb_DatabaseCursorSettingsController_duplicateRetainsLocation( RPbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{
	if ( cursor_settings_controller->duplicate_retains_location == TRUE )	{
		return DB_POSITION;
	}
	return FALSE;
}

/**************************************
*  duplicateRetainsLocationOn  *
**************************************/

void RPbdb_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOn( RPbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{
	cursor_settings_controller->duplicate_retains_location = TRUE;
}

/**************************************
*  duplicateRetainsLocationOff  *
**************************************/

void RPbdb_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOff( RPbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{
	cursor_settings_controller->duplicate_retains_location = FALSE;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/****************************
*  cacheController  *
****************************/

RPbdb_DatabaseCursorCacheSettingsController* RPbdb_DatabaseCursorSettingsController_cacheSettingsController( RPbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{

	if ( cursor_settings_controller->cache_controller == NULL )	{
		cursor_settings_controller->cache_controller = RPbdb_DatabaseCursorCacheSettingsController_new( cursor_settings_controller );
	}
	return cursor_settings_controller->cache_controller;
}

/******************************
*  readWriteController  *
******************************/

RPbdb_DatabaseCursorReadWriteSettingsController* RPbdb_DatabaseCursorSettingsController_readWriteSettingsController( RPbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{

	if ( cursor_settings_controller->record_read_write_settings_controller == NULL )	{
		cursor_settings_controller->record_read_write_settings_controller = RPbdb_DatabaseCursorReadWriteSettingsController_new( cursor_settings_controller );
	}
	return cursor_settings_controller->record_read_write_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/**************************
*  countDataItems  *
**************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_count.html
int RPbdb_DatabaseCursorSettingsController_internal_countDataItemsFlags( RPbdb_DatabaseCursorSettingsController* cursor_settings_controller __attribute__((unused)) )	{
	
	//	Currently unused - always returns 0;
	return RPBDB_NO_FLAGS;
}

/************************
*  duplicateFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_dup.html
int RPbdb_DatabaseCursorSettingsController_internal_duplicateFlags( RPbdb_DatabaseCursorSettingsController* cursor_settings_controller __attribute__((unused)) )	{

	//	if DB_POSITION is not returned a duplicate cursor will be identical to a new cursor
	return DB_POSITION;
}	

/************************
*  openFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_dup.html
int RPbdb_DatabaseCursorSettingsController_internal_openFlags( RPbdb_DatabaseCursorSettingsController* cursor_settings_controller __attribute__((unused)) )	{

	//	FIX
	return RPBDB_NO_FLAGS;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseCursorSettingsController* RPbdb_DatabaseCursorSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseCursorSettingsController* database_cursor_settings_controller )	{

	RPbdb_DatabaseCursorSettingsController* database_cursor_settings_controller_copy	=	RPbdb_DatabaseCursorSettingsController_new( database_cursor_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_cursor_settings_controller_copy->duplicate_retains_location	=	database_cursor_settings_controller->duplicate_retains_location;

	return database_cursor_settings_controller_copy;
}

