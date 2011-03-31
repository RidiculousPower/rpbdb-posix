/*
 *		RPbdb::Database::Cursor::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseCachePrioritySettingsController.h"

#include "RuntimeStorageController.h"

#include "DatabaseCachePrioritySettingsController_internal.h"
																								
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_DatabaseCachePrioritySettingsController* RPbdb_DatabaseCachePrioritySettingsController_new( RPbdb_DatabaseCacheSettingsController* database_cache_settings_controller )	{

	RPbdb_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseCachePrioritySettingsController ) );

	database_cache_priority_settings_controller->parent_database_cache_settings_controller = database_cache_settings_controller;

	return database_cache_priority_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseCachePrioritySettingsController_free(	RPbdb_DatabaseCachePrioritySettingsController** database_cache_priority_settings_controller )	{

	free( *database_cache_priority_settings_controller );
	*database_cache_priority_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseCachePrioritySettingsController_parentEnvironment(	RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{
	return database_cache_priority_settings_controller->parent_database_cache_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseCachePrioritySettingsController_parentDatabase(	RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{
	return database_cache_priority_settings_controller->parent_database_cache_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************
*  priority  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_priority( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{
	
	RPbdb_Database*		database;
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
DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_veryLow( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

	/*****************
	*  setVeryLow  *
	*****************/

	void RPbdb_DatabaseCachePrioritySettingsController_setVeryLow( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		RPbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

	/*********************
	*  atLeastVeryLow  *
	*********************/

	DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_isAtLeastVeryLow( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

	/*********************
	*  atMostVeryLow  *
	*********************/

	DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_isAtMostVeryLow( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPbdb_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

/************
*  low  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_low( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

	/*************
	*  setLow  *
	*************/

	void RPbdb_DatabaseCachePrioritySettingsController_setLow( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		RPbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

	/*****************
	*  atLeastLow  *
	*****************/

	DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_isAtLeastLow( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

	/*********************
	*  atMostLow  *
	*********************/

	DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_isAtMostLow( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPbdb_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

/*****************
*  default  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_default( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

	/*****************
	*  setDefault  *
	*****************/

	void RPbdb_DatabaseCachePrioritySettingsController_setDefault( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		RPbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

	/*********************
	*  atLeastDefault  *
	*********************/

	DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_isAtLeastDefault( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

	/*********************
	*  atMostDefault  *
	*********************/

	DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_isAtMostDefault( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPbdb_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

/*************
*  high  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_high( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

	/*****************
	*  setHigh  *
	*****************/

	void RPbdb_DatabaseCachePrioritySettingsController_setHigh( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		RPbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

	/*********************
	*  atLeastHigh  *
	*********************/

	DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_isAtLeastHigh( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

	/*********************
	*  atMostHigh  *
	*********************/

	DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_isAtMostHigh( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPbdb_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

/*****************
*  veryHigh  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_veryHigh( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return RPbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

	/*********************
	*  setVeryHigh  *
	*********************/

	void RPbdb_DatabaseCachePrioritySettingsController_setVeryHigh( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		RPbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

	/*************************
	*  atLeastVeryHigh  *
	*************************/

	DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_isAtLeastVeryHigh( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

	/*********************
	*  atMostVeryHigh  *
	*********************/

	DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_isAtMostVeryHigh( RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return RPbdb_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
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
DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast(	RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller, 
																		DB_CACHE_PRIORITY cache_priority )	{

	return ( cache_priority >= RPbdb_DatabaseCachePrioritySettingsController_priority( database_cache_priority_settings_controller ) ? TRUE : FALSE );
}

DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_internal_isAtMost(	RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller, 
																		DB_CACHE_PRIORITY cache_priority )	{

	return ( cache_priority <= RPbdb_DatabaseCachePrioritySettingsController_priority( database_cache_priority_settings_controller ) ? TRUE : FALSE );
}

/**************************
*  checkIfPriorityIs  *
**************************/

DB_CACHE_PRIORITY RPbdb_DatabaseCachePrioritySettingsController_internal_isPriority(	RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller, 
																		DB_CACHE_PRIORITY cache_priority )	{


	return ( cache_priority == RPbdb_DatabaseCachePrioritySettingsController_priority( database_cache_priority_settings_controller ) ? TRUE : FALSE );
}

/**********************
*  setPriorityTo  *
**********************/

void RPbdb_DatabaseCachePrioritySettingsController_internal_setPriorityTo(	RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller, 
																			DB_CACHE_PRIORITY								cache_priority )	{

	RPbdb_Database*			database;

	database = database_cache_priority_settings_controller->parent_database_cache_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_priority(	database->wrapped_bdb_database, 
														cache_priority );
	}
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseCachePrioritySettingsController* RPbdb_DatabaseCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller_copy	=	RPbdb_DatabaseCachePrioritySettingsController_new( database_cache_priority_settings_controller->parent_database_cache_settings_controller );

	//	Instances and Pointers
	database_cache_priority_settings_controller_copy->priority	=	database_cache_priority_settings_controller->priority;

	return database_cache_priority_settings_controller_copy;
}

