/*
 *		Rbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *		Rbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *
 */

#include "Rbdb_DatabaseCursorCachePrioritySettingsController.h"
#include "Rbdb_DatabaseCursorCachePrioritySettingsController_internal.h"
#include "Rbdb_DatabaseCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

Rbdb_DatabaseCursorCachePrioritySettingsController* Rbdb_DatabaseCursorCachePrioritySettingsController_new(		Rbdb_DatabaseCursorCacheSettingsController*				database_cursor_cache_settings_controller )	{

	Rbdb_DatabaseCursorCachePrioritySettingsController*		database_cursor_cache_priority_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseCursorCachePrioritySettingsController ) );

	database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller = database_cursor_cache_settings_controller;

	return database_cursor_cache_priority_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseCursorCachePrioritySettingsController_free(	Rbdb_DatabaseCursorCachePrioritySettingsController** database_cursor_cache_priority_settings_controller )	{

	free( *database_cursor_cache_priority_settings_controller );
	*database_cursor_cache_priority_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseCursorCachePrioritySettingsController_parentEnvironment(	Rbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller )	{
	return database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseCursorCachePrioritySettingsController_parentDatabase(	Rbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller )	{
	return database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor->parent_database_cursor_controller->parent_database;
}

/***************************************
*  parentDatabaseCursor  *
***************************************/
Rbdb_DatabaseCursor* Rbdb_DatabaseCursorCachePrioritySettingsController_parentDatabaseCursor(	Rbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller )	{
	return database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor;
}

/*****************
*  priority  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY Rbdb_DatabaseCursorCachePrioritySettingsController_priority( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{
	
	Rbdb_Database*					database;
	
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
BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_veryLow( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

/*****************
*  setVeryLow  *
*****************/

void Rbdb_DatabaseCursorCachePrioritySettingsController_setVeryLow( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	Rbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

/*********************
*  atLeastVeryLow  *
*********************/

BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastVeryLow( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

/*********************
*  atMostVeryLow  *
*********************/

BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_isAtMostVeryLow( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

/************
*  low  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_low( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

/*************
*  setLow  *
*************/

void Rbdb_DatabaseCursorCachePrioritySettingsController_setLow( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	Rbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo( cursor_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

/*****************
*  atLeastLow  *
*****************/

BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastLow( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

/*********************
*  atMostLow  *
*********************/

BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_isAtMostLow( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

/*****************
*  default  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_default( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

/*****************
*  setDefault  *
*****************/

void Rbdb_DatabaseCursorCachePrioritySettingsController_setDefault( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	Rbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo( cursor_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

/*********************
*  atLeastDefault  *
*********************/

BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastDefault( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

/*********************
*  atMostDefault  *
*********************/

BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_isAtMostDefault( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

/*************
*  high  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_high( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

/*****************
*  setHigh  *
*****************/

void Rbdb_DatabaseCursorCachePrioritySettingsController_setHigh( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	Rbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo( cursor_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

/*********************
*  atLeastHigh  *
*********************/

BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastHigh( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

/*********************
*  atMostHigh  *
*********************/

BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_isAtMostHigh( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

/*****************
*  veryHigh  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_veryHigh( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

/*********************
*  setVeryHigh  *
*********************/

void Rbdb_DatabaseCursorCachePrioritySettingsController_setVeryHigh( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	Rbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

/*************************
*  atLeastVeryHigh  *
*************************/

BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastVeryHigh( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

/*********************
*  atMostVeryHigh  *
*********************/

BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_isAtMostVeryHigh( Rbdb_DatabaseCursorCachePrioritySettingsController* cursor_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost( cursor_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
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
BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast(	Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority )	{

	DB_CACHE_PRIORITY	current_priority	=	Rbdb_DatabaseCursorCachePrioritySettingsController_priority( cursor_cache_priority_settings_controller );

	BOOL	is_at_least	=	( ( current_priority >= cache_priority ) ? TRUE : FALSE );

	return is_at_least;
}

/*****************
*  isAtMost  *
*****************/

BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost(	Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority )	{

	DB_CACHE_PRIORITY	current_priority	=	Rbdb_DatabaseCursorCachePrioritySettingsController_priority( cursor_cache_priority_settings_controller );

	BOOL	is_at_most	=	( ( current_priority <= cache_priority ) ? TRUE : FALSE );

	return is_at_most;
}

/**************************
*  checkIfPriorityIs  *
**************************/

BOOL Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority(	Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																							DB_CACHE_PRIORITY										cache_priority )	{

	DB_CACHE_PRIORITY	current_priority	=	Rbdb_DatabaseCursorCachePrioritySettingsController_priority( cursor_cache_priority_settings_controller );

	BOOL	is_equal	=	( ( current_priority == cache_priority ) ? TRUE : FALSE );

	return is_equal;
}

/**********************
*  setPriorityTo  *
**********************/

void Rbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo(	Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY										cache_priority )	{


	Rbdb_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller->parent_database_cursor_settings_controller;
	
	Rbdb_Database*			database	=	NULL;
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
Rbdb_DatabaseCursorCachePrioritySettingsController* Rbdb_DatabaseCursorCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller )	{

	Rbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller_copy	=	Rbdb_DatabaseCursorCachePrioritySettingsController_new( database_cursor_cache_priority_settings_controller->parent_database_cursor_cache_settings_controller );

	//	Instances and Pointers
	database_cursor_cache_priority_settings_controller_copy->priority	=	database_cursor_cache_priority_settings_controller->priority;

	return database_cursor_cache_priority_settings_controller_copy;
}

