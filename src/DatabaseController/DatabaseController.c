/*
 *		RPbdb::DatabaseController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseController.h"
#include "DatabaseController_internal.h"

#include "Database.h"
#include "Database_internal.h"
#include "DatabaseCursorController.h"
#include "DatabaseCursor.h"

#include "Environment.h"

#include "Record.h"
#include "Data.h"

#include "RuntimeStorageController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/
	
RPbdb_DatabaseController* RPbdb_DatabaseController_new( RPbdb_Environment* parent_environment )	{

	RPbdb_DatabaseController*		database_controller		=	RPbdb_DatabaseController_internal_newWithoutRuntimeStorage( parent_environment );

	database_controller->parent_environment	=	parent_environment;

	RPBDB_RUNTIME_STORAGE( database_controller, "database_controller" );

	return database_controller;
}

/*********
*  free  *
*********/

void RPbdb_DatabaseController_free(	RPbdb_DatabaseController** database_controller )	{
	
	//	close and free all databases
	RPbdb_DatabaseController_freeAllDatabases( *database_controller );

	if ( ( *database_controller )->runtime_storage_database != NULL )	{
		RPbdb_Database_free( & ( ( *database_controller )->runtime_storage_database ) );
	}

	free( *database_controller );
	*database_controller	=	NULL;
}

/*******************************************************************************************************************************************************************************************
															Accessor Methods
*******************************************************************************************************************************************************************************************/

/***********************
*  settingsController  *
***********************/

RPbdb_DatabaseSettingsController* RPbdb_DatabaseController_settingsController(	RPbdb_DatabaseController* database_controller )	{
	return database_controller->settings_controller;
}

/**********************
*  parentEnvironment  *
**********************/

RPbdb_Environment* RPbdb_DatabaseController_parentEnvironment(	RPbdb_DatabaseController* database_controller )	{
	return database_controller->parent_environment;
}

/*******************************************************************************************************************************************************************************************
															Methods
*******************************************************************************************************************************************************************************************/

/****************
*  newDatabase  *
****************/

//	Create a new database for requested name
RPbdb_Database* RPbdb_DatabaseController_newDatabase(	RPbdb_DatabaseController*	database_controller, 
																										char*											database_name	)	{
	
	RPbdb_Database*	database						=	RPbdb_Database_new(	database_controller,
																														database_name );

	return database;
}

/**********************
*  closeAllDatabases  *
**********************/

//	Close all Databases
void RPbdb_DatabaseController_closeAllDatabases( RPbdb_DatabaseController* database_controller )	{
	
	RPbdb_Database_internal_closeAllStoredRuntimeAddresses(	database_controller->runtime_storage_database,
																													(void *(*)(void*)) & RPbdb_Database_close );
}

/*********************
*  freeAllDatabases  *
*********************/

//	Free all Databases (close if necessary)
void RPbdb_DatabaseController_freeAllDatabases( RPbdb_DatabaseController* database_controller )	{

	RPbdb_Database_internal_freeAllStoredRuntimeAddresses(	database_controller->runtime_storage_database,
																												(void *(*)(void**)) & RPbdb_Database_internal_freeFromRuntimeStorage );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  newWithoutRuntimeStorage  *
*****************************/

RPbdb_DatabaseController* RPbdb_DatabaseController_internal_newWithoutRuntimeStorage( RPbdb_Environment* parent_environment )	{

	RPbdb_DatabaseController*		database_controller = calloc( 1, sizeof( RPbdb_DatabaseController ) );
	
	database_controller->parent_environment = parent_environment;

	return database_controller;
}

