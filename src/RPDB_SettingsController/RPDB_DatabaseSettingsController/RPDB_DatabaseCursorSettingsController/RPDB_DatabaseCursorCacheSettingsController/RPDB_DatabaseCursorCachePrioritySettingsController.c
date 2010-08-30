/*
 *		RPDB::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *		RPDB::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *
 */

#include "RPDB_DatabaseCursorCachePrioritySettingsController.h"
#include "RPDB_DatabaseCursorCachePrioritySettingsController_internal.h"
#include "RPDB_DatabaseCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_DatabaseCursorCachePrioritySettingsController* RPDB_DatabaseCursorCachePrioritySettingsController_new(		RPDB_DatabaseCursorCacheSettingsController*				database_cursor_cache_settings_controller )	{

	RPDB_DatabaseCursorCachePrioritySettingsController*		database_cursor_cache_priority_settings_controller = calloc( 1, sizeof( RPDB_DatabaseCursorCachePrioritySettingsController ) );

	database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller = database_cursor_cache_settings_controller;

	return database_cursor_cache_priority_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseCursorCachePrioritySettingsController_free(	RPDB_DatabaseCursorCachePrioritySettingsController** database_cursor_cache_priority_settings_controller )	{

	free( *database_cursor_cache_priority_settings_controller );
	*database_cursor_cache_priority_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseCursorCachePrioritySettingsController_parentEnvironment(	RPDB_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller )	{
	return database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseCursorCachePrioritySettingsController_parentDatabase(	RPDB_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller )	{
	return database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database;
}

/***************************************
*  parentDatabaseCursor  *
***************************************/
RPDB_DatabaseCursor* RPDB_DatabaseCursorCachePrioritySettingsController_parentDatabaseCursor(	RPDB_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller )	{
	return database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor;
}

/*****************
*  priority  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPDB_DatabaseCursorCachePrioritySettingsController_priority( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{
	
	RPDB_Database*					database;
	DB_CACHE_PRIORITY	current_cache_priority;
	
	database = cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_settings_controller->parent_database;
	
	database->wrapped_bdb_database->get_priority(	database->wrapped_bdb_database, 
												 & current_cache_priority );
	
	return current_cache_priority;
}

/*****************
*  veryLow  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPDB_DatabaseCursorCachePrioritySettingsController_veryLow( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

/*****************
*  setVeryLow  *
*****************/

void RPDB_DatabaseCursorCachePrioritySettingsController_setVeryLow( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	RPDB_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

/*********************
*  atLeastVeryLow  *
*********************/

BOOL RPDB_DatabaseCursorCachePrioritySettingsController_isAtLeastVeryLow( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

/*********************
*  atMostVeryLow  *
*********************/

BOOL RPDB_DatabaseCursorCachePrioritySettingsController_isAtMostVeryLow( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

/************
*  low  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPDB_DatabaseCursorCachePrioritySettingsController_low( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

/*************
*  setLow  *
*************/

void RPDB_DatabaseCursorCachePrioritySettingsController_setLow( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	RPDB_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

/*****************
*  atLeastLow  *
*****************/

BOOL RPDB_DatabaseCursorCachePrioritySettingsController_isAtLeastLow( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

/*********************
*  atMostLow  *
*********************/

BOOL RPDB_DatabaseCursorCachePrioritySettingsController_isAtMostLow( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

/*****************
*  default  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPDB_DatabaseCursorCachePrioritySettingsController_default( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

/*****************
*  setDefault  *
*****************/

void RPDB_DatabaseCursorCachePrioritySettingsController_setDefault( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	RPDB_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

/*********************
*  atLeastDefault  *
*********************/

BOOL RPDB_DatabaseCursorCachePrioritySettingsController_isAtLeastDefault( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

/*********************
*  atMostDefault  *
*********************/

BOOL RPDB_DatabaseCursorCachePrioritySettingsController_isAtMostDefault( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

/*************
*  high  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPDB_DatabaseCursorCachePrioritySettingsController_high( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

/*****************
*  setHigh  *
*****************/

void RPDB_DatabaseCursorCachePrioritySettingsController_setHigh( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	RPDB_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

/*********************
*  atLeastHigh  *
*********************/

BOOL RPDB_DatabaseCursorCachePrioritySettingsController_isAtLeastHigh( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

/*********************
*  atMostHigh  *
*********************/

BOOL RPDB_DatabaseCursorCachePrioritySettingsController_isAtMostHigh( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

/*****************
*  veryHigh  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPDB_DatabaseCursorCachePrioritySettingsController_veryHigh( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

/*********************
*  setVeryHigh  *
*********************/

void RPDB_DatabaseCursorCachePrioritySettingsController_setVeryHigh( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	RPDB_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

/*************************
*  atLeastVeryHigh  *
*************************/

BOOL RPDB_DatabaseCursorCachePrioritySettingsController_isAtLeastVeryHigh( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

/*********************
*  atMostVeryHigh  *
*********************/

BOOL RPDB_DatabaseCursorCachePrioritySettingsController_isAtMostVeryHigh( RPDB_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************
*  atLeast  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast(	RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																			DB_CACHE_PRIORITY										cache_priority )	{

	return ( cache_priority >= RPDB_DatabaseCursorCachePrioritySettingsController_priority( cursor_cache_priority_settings_controller ) ? TRUE : FALSE );
}

BOOL RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtMost(	RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																			DB_CACHE_PRIORITY										cache_priority )	{

	return ( cache_priority <= RPDB_DatabaseCursorCachePrioritySettingsController_priority( cursor_cache_priority_settings_controller ) ? TRUE : FALSE );
}

/**************************
*  checkIfPriorityIs  *
**************************/

BOOL RPDB_DatabaseCursorCachePrioritySettingsController_internal_isPriority(	RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																				DB_CACHE_PRIORITY										cache_priority )	{

	return ( cache_priority == RPDB_DatabaseCursorCachePrioritySettingsController_priority( cursor_cache_priority_settings_controller ) ? TRUE : FALSE );
}

/**********************
*  setPriorityTo  *
**********************/

void RPDB_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo(	RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																					DB_CACHE_PRIORITY										cache_priority )	{

	RPDB_Database*			database;

	database = cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_settings_controller->parent_database;
	
	if ( database->wrapped_bdb_database != NULL )	{

		database->wrapped_bdb_database->set_priority(	database->wrapped_bdb_database, 
														cache_priority );
	}
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseCursorCachePrioritySettingsController* RPDB_DatabaseCursorCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller )	{

	RPDB_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller_copy	=	RPDB_DatabaseCursorCachePrioritySettingsController_new( database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller );

	//	Instances and Pointers
	database_cursor_cache_priority_settings_controller_copy->priority	=	database_cursor_cache_priority_settings_controller->priority;

	return database_cursor_cache_priority_settings_controller_copy;
}

