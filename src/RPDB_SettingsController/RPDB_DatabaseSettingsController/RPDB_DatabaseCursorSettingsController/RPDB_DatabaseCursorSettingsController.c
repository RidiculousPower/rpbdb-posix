/*
 *		RPDB::DatabaseController::Database::CursorController::Cursor::CursorSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseCursorSettingsController.h"

#include "RPDB_DatabaseCursorCacheSettingsController.h"
#include "RPDB_DatabaseCursorReadWriteSettingsController.h"

#include "RPDB_DatabaseCursorSettingsController_internal.h"
#include "RPDB_DatabaseCachePrioritySettingsController_internal.h"
#include "RPDB_DatabaseCursorReadWriteSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_DatabaseCursorSettingsController* RPDB_DatabaseCursorSettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseCursorSettingsController*		cursor_settings_controller = calloc( 1, sizeof( RPDB_DatabaseCursorSettingsController ) );

	cursor_settings_controller->parent_database_settings_controller = database_settings_controller;

	return cursor_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseCursorSettingsController_free(	RPDB_DatabaseCursorSettingsController** database_cursor_settings_controller )	{

	if ( ( *database_cursor_settings_controller )->cache_controller != NULL )	{

		RPDB_DatabaseCursorCacheSettingsController_free( & ( ( *database_cursor_settings_controller )->cache_controller ) );
	}
	if ( ( *database_cursor_settings_controller )->read_write_settings_controller != NULL )	{

		RPDB_DatabaseCursorReadWriteSettingsController_free( & ( ( *database_cursor_settings_controller )->read_write_settings_controller ) );
	}

	free( *database_cursor_settings_controller );
	*database_cursor_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseCursorSettingsController_parentEnvironment(	RPDB_DatabaseCursorSettingsController* database_cursor_settings_controller )	{
	return database_cursor_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseCursorSettingsController_parentDatabase(	RPDB_DatabaseCursorSettingsController* database_cursor_settings_controller )	{
	return database_cursor_settings_controller->parent_database_settings_controller->parent_database;
}

/***************************************
*  parentDatabaseCursor  *
***************************************/
RPDB_DatabaseCursor* RPDB_DatabaseCursorSettingsController_parentDatabaseCursor(	RPDB_DatabaseCursorSettingsController* database_cursor_settings_controller )	{
	return database_cursor_settings_controller->parent_database_cursor;
}


/**********************************
*  duplicateRetainsLocation  *
**********************************/

//	DB_POSITION		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_dup.html
BOOL RPDB_DatabaseCursorSettingsController_duplicateRetainsLocation( RPDB_DatabaseCursorSettingsController* cursor_settings_controller )	{
	if ( cursor_settings_controller->duplicate_retains_location == TRUE )	{
		return DB_POSITION;
	}
	return FALSE;
}

/**************************************
*  duplicateRetainsLocationOn  *
**************************************/

void RPDB_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOn( RPDB_DatabaseCursorSettingsController* cursor_settings_controller )	{
	cursor_settings_controller->duplicate_retains_location = TRUE;
}

/**************************************
*  duplicateRetainsLocationOff  *
**************************************/

void RPDB_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOff( RPDB_DatabaseCursorSettingsController* cursor_settings_controller )	{
	cursor_settings_controller->duplicate_retains_location = FALSE;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/****************************
*  cacheController  *
****************************/

RPDB_DatabaseCursorCacheSettingsController* RPDB_DatabaseCursorSettingsController_cacheSettingsController( RPDB_DatabaseCursorSettingsController* cursor_settings_controller )	{

	if ( cursor_settings_controller->cache_controller == NULL )	{
		cursor_settings_controller->cache_controller = RPDB_DatabaseCursorCacheSettingsController_new( cursor_settings_controller );
	}
	return cursor_settings_controller->cache_controller;
}

/******************************
*  readWriteController  *
******************************/

RPDB_DatabaseCursorReadWriteSettingsController* RPDB_DatabaseCursorSettingsController_readWriteSettingsController( RPDB_DatabaseCursorSettingsController* cursor_settings_controller )	{

	if ( cursor_settings_controller->read_write_settings_controller == NULL )	{
		cursor_settings_controller->read_write_settings_controller = RPDB_DatabaseCursorReadWriteSettingsController_new( cursor_settings_controller );
	}
	return cursor_settings_controller->read_write_settings_controller;
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
int RPDB_DatabaseCursorSettingsController_internal_countDataItemsFlags( RPDB_DatabaseCursorSettingsController* cursor_settings_controller __attribute__((unused)) )	{
	
	//	Currently unused - always returns 0;
	return RPDB_NO_FLAGS;
}

/************************
*  duplicateFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_dup.html
int RPDB_DatabaseCursorSettingsController_internal_duplicateFlags( RPDB_DatabaseCursorSettingsController* cursor_settings_controller __attribute__((unused)) )	{

	//	if DB_POSITION is not returned a duplicate cursor will be identical to a new cursor
	return DB_POSITION;
}	

/************************
*  openFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_dup.html
int RPDB_DatabaseCursorSettingsController_internal_openFlags( RPDB_DatabaseCursorSettingsController* cursor_settings_controller __attribute__((unused)) )	{

	//	FIX
	return RPDB_NO_FLAGS;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseCursorSettingsController* RPDB_DatabaseCursorSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseCursorSettingsController* database_cursor_settings_controller )	{

	RPDB_DatabaseCursorSettingsController* database_cursor_settings_controller_copy	=	RPDB_DatabaseCursorSettingsController_new( database_cursor_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_cursor_settings_controller_copy->duplicate_retains_location	=	database_cursor_settings_controller->duplicate_retains_location;

	return database_cursor_settings_controller_copy;
}

