/*
 *		RPbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *		RPbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *
 */

#include "DatabaseCursorCachePrioritySettingsController.h"
#include "DatabaseCursorCachePrioritySettingsController_internal.h"
#include "DatabaseCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_DatabaseCursorCachePrioritySettingsController* RPbdb_DatabaseCursorCachePrioritySettingsController_new(		RPbdb_DatabaseCursorCacheSettingsController*				database_cursor_cache_settings_controller )	{

	RPbdb_DatabaseCursorCachePrioritySettingsController*		database_cursor_cache_priority_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseCursorCachePrioritySettingsController ) );

	database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller = database_cursor_cache_settings_controller;

	return database_cursor_cache_priority_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseCursorCachePrioritySettingsController_free(	RPbdb_DatabaseCursorCachePrioritySettingsController** database_cursor_cache_priority_settings_controller )	{

	free( *database_cursor_cache_priority_settings_controller );
	*database_cursor_cache_priority_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseCursorCachePrioritySettingsController_parentEnvironment(	RPbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller )	{
	return database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseCursorCachePrioritySettingsController_parentDatabase(	RPbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller )	{
	return database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database;
}

/***************************************
*  parentDatabaseCursor  *
***************************************/
RPbdb_DatabaseCursor* RPbdb_DatabaseCursorCachePrioritySettingsController_parentDatabaseCursor(	RPbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller )	{
	return database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor;
}

/*****************
*  priority  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPbdb_DatabaseCursorCachePrioritySettingsController_priority( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{
	
	RPbdb_Database*					database;
	
	database = cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_settings_controller->parent_database;
	
	if (		database
			&&	database->wrapped_bdb_database )	{
		
		database->wrapped_bdb_database->get_priority(	database->wrapped_bdb_database, 
																									& cursor_cache_priority_settings_controller->priority );
	}
	
	return cursor_cache_priority_settings_controller->priority;
}

/*****************
*  veryLow  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_veryLow( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

/*****************
*  setVeryLow  *
*****************/

void RPbdb_DatabaseCursorCachePrioritySettingsController_setVeryLow( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	RPbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

/*********************
*  atLeastVeryLow  *
*********************/

BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastVeryLow( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

/*********************
*  atMostVeryLow  *
*********************/

BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_isAtMostVeryLow( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

/************
*  low  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_low( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

/*************
*  setLow  *
*************/

void RPbdb_DatabaseCursorCachePrioritySettingsController_setLow( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	RPbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo( cursor_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

/*****************
*  atLeastLow  *
*****************/

BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastLow( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

/*********************
*  atMostLow  *
*********************/

BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_isAtMostLow( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

/*****************
*  default  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_default( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

/*****************
*  setDefault  *
*****************/

void RPbdb_DatabaseCursorCachePrioritySettingsController_setDefault( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	RPbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo( cursor_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

/*********************
*  atLeastDefault  *
*********************/

BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastDefault( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

/*********************
*  atMostDefault  *
*********************/

BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_isAtMostDefault( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

/*************
*  high  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_high( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

/*****************
*  setHigh  *
*****************/

void RPbdb_DatabaseCursorCachePrioritySettingsController_setHigh( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	RPbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo( cursor_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

/*********************
*  atLeastHigh  *
*********************/

BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastHigh( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

/*********************
*  atMostHigh  *
*********************/

BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_isAtMostHigh( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

/*****************
*  veryHigh  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_veryHigh( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

/*********************
*  setVeryHigh  *
*********************/

void RPbdb_DatabaseCursorCachePrioritySettingsController_setVeryHigh( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	RPbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

/*************************
*  atLeastVeryHigh  *
*************************/

BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastVeryHigh( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

/*********************
*  atMostVeryHigh  *
*********************/

BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_isAtMostVeryHigh( RPbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************
*  isAtLeast  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast(	RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority )	{

	DB_CACHE_PRIORITY	current_priority	=	RPbdb_DatabaseCursorCachePrioritySettingsController_priority( cursor_cache_priority_settings_controller );

	BOOL	is_at_least	=	( ( current_priority >= cache_priority ) ? TRUE : FALSE );

	return is_at_least;
}

/*****************
*  isAtMost  *
*****************/

BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost(	RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority )	{

	DB_CACHE_PRIORITY	current_priority	=	RPbdb_DatabaseCursorCachePrioritySettingsController_priority( cursor_cache_priority_settings_controller );

	BOOL	is_at_most	=	( ( current_priority <= cache_priority ) ? TRUE : FALSE );

	return is_at_most;
}

/**************************
*  checkIfPriorityIs  *
**************************/

BOOL RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority(	RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																							DB_CACHE_PRIORITY										cache_priority )	{

	DB_CACHE_PRIORITY	current_priority	=	RPbdb_DatabaseCursorCachePrioritySettingsController_priority( cursor_cache_priority_settings_controller );

	BOOL	is_equal	=	( ( current_priority == cache_priority ) ? TRUE : FALSE );

	return is_equal;
}

/**********************
*  setPriorityTo  *
**********************/

void RPbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo(	RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY										cache_priority )	{


	RPbdb_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller;
	
	RPbdb_Database*			database	=	NULL;
	if ( database_cursor_settings_controller->parent_database_cursor != NULL )	{
		database	=	database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database;
	}
	if ( database_cursor_settings_controller->parent_database_settings_controller != NULL )	{
		database	=	database_cursor_settings_controller->parent_database_settings_controller->parent_database;
	}

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{

		database->wrapped_bdb_database->set_priority(	database->wrapped_bdb_database, 
																									cache_priority );
	}
	
	cursor_cache_priority_settings_controller->priority	=	cache_priority;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseCursorCachePrioritySettingsController* RPbdb_DatabaseCursorCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller )	{

	RPbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller_copy	=	RPbdb_DatabaseCursorCachePrioritySettingsController_new( database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller );

	//	Instances and Pointers
	database_cursor_cache_priority_settings_controller_copy->priority	=	database_cursor_cache_priority_settings_controller->priority;

	return database_cursor_cache_priority_settings_controller_copy;
}

