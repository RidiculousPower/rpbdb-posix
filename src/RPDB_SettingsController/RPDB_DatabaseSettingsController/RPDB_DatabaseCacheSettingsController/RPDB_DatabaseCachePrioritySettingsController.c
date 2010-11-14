/*
 *		RPDB::Database::Cursor::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseCachePrioritySettingsController.h"

#include "RPDB_RuntimeStorageController.h"

#include "RPDB_DatabaseCachePrioritySettingsController_internal.h"
																								
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_DatabaseCachePrioritySettingsController* RPDB_DatabaseCachePrioritySettingsController_new( RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{

	RPDB_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller = calloc( 1, sizeof( RPDB_DatabaseCachePrioritySettingsController ) );

	database_cache_priority_settings_controller->parent_database_cache_settings_controller = database_cache_settings_controller;

	return database_cache_priority_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseCachePrioritySettingsController_free(	RPDB_DatabaseCachePrioritySettingsController** database_cache_priority_settings_controller )	{

	free( *database_cache_priority_settings_controller );
	*database_cache_priority_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseCachePrioritySettingsController_parentEnvironment(	RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{
	return database_cache_priority_settings_controller->parent_database_cache_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseCachePrioritySettingsController_parentDatabase(	RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{
	return database_cache_priority_settings_controller->parent_database_cache_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************
*  priority  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_priority( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{
	
	RPDB_Database*		database;
	DB_CACHE_PRIORITY	current_cache_priority;
	
	database = database_cache_priority_settings_controller->parent_database_cache_settings_controller->parent_database_settings_controller->parent_database;
	
	if (		database 
			&&	database->wrapped_bdb_database )	{
		database->wrapped_bdb_database->get_priority( database->wrapped_bdb_database, 
																									& current_cache_priority );
	}
	
	return current_cache_priority;
}

/*****************
*  veryLow  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_veryLow( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return RPDB_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

	/*****************
	*  setVeryLow  *
	*****************/

	void RPDB_DatabaseCachePrioritySettingsController_setVeryLow( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		RPDB_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

	/*********************
	*  atLeastVeryLow  *
	*********************/

	DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_isAtLeastVeryLow( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPDB_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

	/*********************
	*  atMostVeryLow  *
	*********************/

	DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_isAtMostVeryLow( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPDB_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

/************
*  low  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_low( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return RPDB_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

	/*************
	*  setLow  *
	*************/

	void RPDB_DatabaseCachePrioritySettingsController_setLow( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		RPDB_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

	/*****************
	*  atLeastLow  *
	*****************/

	DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_isAtLeastLow( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPDB_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

	/*********************
	*  atMostLow  *
	*********************/

	DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_isAtMostLow( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPDB_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

/*****************
*  default  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_default( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return RPDB_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

	/*****************
	*  setDefault  *
	*****************/

	void RPDB_DatabaseCachePrioritySettingsController_setDefault( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		RPDB_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

	/*********************
	*  atLeastDefault  *
	*********************/

	DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_isAtLeastDefault( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPDB_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

	/*********************
	*  atMostDefault  *
	*********************/

	DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_isAtMostDefault( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPDB_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

/*************
*  high  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_high( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return RPDB_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

	/*****************
	*  setHigh  *
	*****************/

	void RPDB_DatabaseCachePrioritySettingsController_setHigh( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		RPDB_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

	/*********************
	*  atLeastHigh  *
	*********************/

	DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_isAtLeastHigh( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPDB_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

	/*********************
	*  atMostHigh  *
	*********************/

	DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_isAtMostHigh( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPDB_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

/*****************
*  veryHigh  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_veryHigh( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return RPDB_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

	/*********************
	*  setVeryHigh  *
	*********************/

	void RPDB_DatabaseCachePrioritySettingsController_setVeryHigh( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		RPDB_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

	/*************************
	*  atLeastVeryHigh  *
	*************************/

	DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_isAtLeastVeryHigh( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPDB_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

	/*********************
	*  atMostVeryHigh  *
	*********************/

	DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_isAtMostVeryHigh( RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPDB_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
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
DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_internal_isAtLeast(	RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller, 
																		DB_CACHE_PRIORITY cache_priority )	{

	return ( cache_priority >= RPDB_DatabaseCachePrioritySettingsController_priority( database_cache_priority_settings_controller ) ? TRUE : FALSE );
}

DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_internal_isAtMost(	RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller, 
																		DB_CACHE_PRIORITY cache_priority )	{

	return ( cache_priority <= RPDB_DatabaseCachePrioritySettingsController_priority( database_cache_priority_settings_controller ) ? TRUE : FALSE );
}

/**************************
*  checkIfPriorityIs  *
**************************/

DB_CACHE_PRIORITY RPDB_DatabaseCachePrioritySettingsController_internal_isPriority(	RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller, 
																		DB_CACHE_PRIORITY cache_priority )	{


	return ( cache_priority == RPDB_DatabaseCachePrioritySettingsController_priority( database_cache_priority_settings_controller ) ? TRUE : FALSE );
}

/**********************
*  setPriorityTo  *
**********************/

void RPDB_DatabaseCachePrioritySettingsController_internal_setPriorityTo(	RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller, 
																			DB_CACHE_PRIORITY								cache_priority )	{

	RPDB_Database*			database;

	database = database_cache_priority_settings_controller->parent_database_cache_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_priority(	database->wrapped_bdb_database, 
														cache_priority );
	}
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseCachePrioritySettingsController* RPDB_DatabaseCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller_copy	=	RPDB_DatabaseCachePrioritySettingsController_new( database_cache_priority_settings_controller->parent_database_cache_settings_controller );

	//	Instances and Pointers
	database_cache_priority_settings_controller_copy->priority	=	database_cache_priority_settings_controller->priority;

	return database_cache_priority_settings_controller_copy;
}

