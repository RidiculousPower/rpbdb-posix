/*
 *		Rbdb::Database::Cursor::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseCachePrioritySettingsController.h"

#include "Rbdb_RuntimeStorageController.h"

#include "Rbdb_DatabaseCachePrioritySettingsController_internal.h"
																								
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

Rbdb_DatabaseCachePrioritySettingsController* Rbdb_DatabaseCachePrioritySettingsController_new( Rbdb_DatabaseCacheSettingsController* database_cache_settings_controller )	{

	Rbdb_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseCachePrioritySettingsController ) );

	database_cache_priority_settings_controller->parent_database_cache_settings_controller = database_cache_settings_controller;

	return database_cache_priority_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseCachePrioritySettingsController_free(	Rbdb_DatabaseCachePrioritySettingsController** database_cache_priority_settings_controller )	{

	free( *database_cache_priority_settings_controller );
	*database_cache_priority_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseCachePrioritySettingsController_parentEnvironment(	Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{
	return database_cache_priority_settings_controller->parent_database_cache_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseCachePrioritySettingsController_parentDatabase(	Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{
	return database_cache_priority_settings_controller->parent_database_cache_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************
*  priority  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_priority( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{
	
	Rbdb_Database*		database;
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
DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_veryLow( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

	/*****************
	*  setVeryLow  *
	*****************/

	void Rbdb_DatabaseCachePrioritySettingsController_setVeryLow( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		Rbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

	/*********************
	*  atLeastVeryLow  *
	*********************/

	DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_isAtLeastVeryLow( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return Rbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

	/*********************
	*  atMostVeryLow  *
	*********************/

	DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_isAtMostVeryLow( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return Rbdb_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

/************
*  low  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_low( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

	/*************
	*  setLow  *
	*************/

	void Rbdb_DatabaseCachePrioritySettingsController_setLow( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		Rbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

	/*****************
	*  atLeastLow  *
	*****************/

	DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_isAtLeastLow( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return Rbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

	/*********************
	*  atMostLow  *
	*********************/

	DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_isAtMostLow( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return Rbdb_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

/*****************
*  default  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_default( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

	/*****************
	*  setDefault  *
	*****************/

	void Rbdb_DatabaseCachePrioritySettingsController_setDefault( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		Rbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

	/*********************
	*  atLeastDefault  *
	*********************/

	DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_isAtLeastDefault( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return Rbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

	/*********************
	*  atMostDefault  *
	*********************/

	DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_isAtMostDefault( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return Rbdb_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

/*************
*  high  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_high( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

	/*****************
	*  setHigh  *
	*****************/

	void Rbdb_DatabaseCachePrioritySettingsController_setHigh( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		Rbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

	/*********************
	*  atLeastHigh  *
	*********************/

	DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_isAtLeastHigh( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return Rbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

	/*********************
	*  atMostHigh  *
	*********************/

	DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_isAtMostHigh( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return Rbdb_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

/*****************
*  veryHigh  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_veryHigh( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	return Rbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

	/*********************
	*  setVeryHigh  *
	*********************/

	void Rbdb_DatabaseCachePrioritySettingsController_setVeryHigh( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		Rbdb_DatabaseCachePrioritySettingsController_internal_isPriority( database_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

	/*************************
	*  atLeastVeryHigh  *
	*************************/

	DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_isAtLeastVeryHigh( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return Rbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast( database_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

	/*********************
	*  atMostVeryHigh  *
	*********************/

	DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_isAtMostVeryHigh( Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

		return Rbdb_DatabaseCachePrioritySettingsController_internal_isAtMost( database_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
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
DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast(	Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller, 
																		DB_CACHE_PRIORITY cache_priority )	{

	return ( cache_priority >= Rbdb_DatabaseCachePrioritySettingsController_priority( database_cache_priority_settings_controller ) ? TRUE : FALSE );
}

DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_internal_isAtMost(	Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller, 
																		DB_CACHE_PRIORITY cache_priority )	{

	return ( cache_priority <= Rbdb_DatabaseCachePrioritySettingsController_priority( database_cache_priority_settings_controller ) ? TRUE : FALSE );
}

/**************************
*  checkIfPriorityIs  *
**************************/

DB_CACHE_PRIORITY Rbdb_DatabaseCachePrioritySettingsController_internal_isPriority(	Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller, 
																		DB_CACHE_PRIORITY cache_priority )	{


	return ( cache_priority == Rbdb_DatabaseCachePrioritySettingsController_priority( database_cache_priority_settings_controller ) ? TRUE : FALSE );
}

/**********************
*  setPriorityTo  *
**********************/

void Rbdb_DatabaseCachePrioritySettingsController_internal_setPriorityTo(	Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller, 
																			DB_CACHE_PRIORITY								cache_priority )	{

	Rbdb_Database*			database;

	database = database_cache_priority_settings_controller->parent_database_cache_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_priority(	database->wrapped_bdb_database, 
														cache_priority );
	}
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_DatabaseCachePrioritySettingsController* Rbdb_DatabaseCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller )	{

	Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller_copy	=	Rbdb_DatabaseCachePrioritySettingsController_new( database_cache_priority_settings_controller->parent_database_cache_settings_controller );

	//	Instances and Pointers
	database_cache_priority_settings_controller_copy->priority	=	database_cache_priority_settings_controller->priority;

	return database_cache_priority_settings_controller_copy;
}

