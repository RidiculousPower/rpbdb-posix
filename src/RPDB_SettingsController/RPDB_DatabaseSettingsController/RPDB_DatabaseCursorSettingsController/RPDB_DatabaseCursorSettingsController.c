/*
 *		Rbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseCursorSettingsController.h"

#include "Rbdb_DatabaseCursorCacheSettingsController.h"
#include "Rbdb_DatabaseCursorReadWriteSettingsController.h"

#include "Rbdb_DatabaseCursorSettingsController_internal.h"
#include "Rbdb_DatabaseCachePrioritySettingsController_internal.h"
#include "Rbdb_DatabaseCursorReadWriteSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

Rbdb_DatabaseCursorSettingsController* Rbdb_DatabaseCursorSettingsController_new( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_DatabaseCursorSettingsController*		cursor_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseCursorSettingsController ) );

	cursor_settings_controller->parent_database_settings_controller = database_settings_controller;

	return cursor_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseCursorSettingsController_free(	Rbdb_DatabaseCursorSettingsController** database_cursor_settings_controller )	{

	if ( ( *database_cursor_settings_controller )->cache_controller != NULL )	{

		Rbdb_DatabaseCursorCacheSettingsController_free( & ( ( *database_cursor_settings_controller )->cache_controller ) );
	}
	if ( ( *database_cursor_settings_controller )->record_read_write_settings_controller != NULL )	{

		Rbdb_DatabaseCursorReadWriteSettingsController_free( & ( ( *database_cursor_settings_controller )->record_read_write_settings_controller ) );
	}

	free( *database_cursor_settings_controller );
	*database_cursor_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseCursorSettingsController_parentEnvironment(	Rbdb_DatabaseCursorSettingsController* database_cursor_settings_controller )	{
	return database_cursor_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseCursorSettingsController_parentDatabase(	Rbdb_DatabaseCursorSettingsController* database_cursor_settings_controller )	{
	return database_cursor_settings_controller->parent_database_settings_controller->parent_database;
}

/***************************************
*  parentDatabaseCursor  *
***************************************/
Rbdb_DatabaseCursor* Rbdb_DatabaseCursorSettingsController_parentDatabaseCursor(	Rbdb_DatabaseCursorSettingsController* database_cursor_settings_controller )	{
	return database_cursor_settings_controller->parent_database_cursor;
}


/**********************************
*  duplicateRetainsLocation  *
**********************************/

//	DB_POSITION		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_dup.html
BOOL Rbdb_DatabaseCursorSettingsController_duplicateRetainsLocation( Rbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{
	if ( cursor_settings_controller->duplicate_retains_location == TRUE )	{
		return DB_POSITION;
	}
	return FALSE;
}

/**************************************
*  duplicateRetainsLocationOn  *
**************************************/

void Rbdb_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOn( Rbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{
	cursor_settings_controller->duplicate_retains_location = TRUE;
}

/**************************************
*  duplicateRetainsLocationOff  *
**************************************/

void Rbdb_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOff( Rbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{
	cursor_settings_controller->duplicate_retains_location = FALSE;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/****************************
*  cacheController  *
****************************/

Rbdb_DatabaseCursorCacheSettingsController* Rbdb_DatabaseCursorSettingsController_cacheSettingsController( Rbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{

	if ( cursor_settings_controller->cache_controller == NULL )	{
		cursor_settings_controller->cache_controller = Rbdb_DatabaseCursorCacheSettingsController_new( cursor_settings_controller );
	}
	return cursor_settings_controller->cache_controller;
}

/******************************
*  readWriteController  *
******************************/

Rbdb_DatabaseCursorReadWriteSettingsController* Rbdb_DatabaseCursorSettingsController_readWriteSettingsController( Rbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{

	if ( cursor_settings_controller->record_read_write_settings_controller == NULL )	{
		cursor_settings_controller->record_read_write_settings_controller = Rbdb_DatabaseCursorReadWriteSettingsController_new( cursor_settings_controller );
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
int Rbdb_DatabaseCursorSettingsController_internal_countDataItemsFlags( Rbdb_DatabaseCursorSettingsController* cursor_settings_controller __attribute__((unused)) )	{
	
	//	Currently unused - always returns 0;
	return Rbdb_NO_FLAGS;
}

/************************
*  duplicateFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_dup.html
int Rbdb_DatabaseCursorSettingsController_internal_duplicateFlags( Rbdb_DatabaseCursorSettingsController* cursor_settings_controller __attribute__((unused)) )	{

	//	if DB_POSITION is not returned a duplicate cursor will be identical to a new cursor
	return DB_POSITION;
}	

/************************
*  openFlags  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_dup.html
int Rbdb_DatabaseCursorSettingsController_internal_openFlags( Rbdb_DatabaseCursorSettingsController* cursor_settings_controller __attribute__((unused)) )	{

	//	FIX
	return Rbdb_NO_FLAGS;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_DatabaseCursorSettingsController* Rbdb_DatabaseCursorSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseCursorSettingsController* database_cursor_settings_controller )	{

	Rbdb_DatabaseCursorSettingsController* database_cursor_settings_controller_copy	=	Rbdb_DatabaseCursorSettingsController_new( database_cursor_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_cursor_settings_controller_copy->duplicate_retains_location	=	database_cursor_settings_controller->duplicate_retains_location;

	return database_cursor_settings_controller_copy;
}

