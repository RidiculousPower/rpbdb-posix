/*
 *		Rbdb::DatabaseController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseController.h"
#include "Rbdb_DatabaseController_internal.h"

#include "Rbdb_Database.h"
#include "Rbdb_Database_internal.h"
#include "Rbdb_DatabaseCursorController.h"
#include "Rbdb_DatabaseCursor.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Record.h"
#include "Rbdb_Data.h"

#include "Rbdb_RuntimeStorageController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/
	
Rbdb_DatabaseController* Rbdb_DatabaseController_new( Rbdb_Environment* parent_environment )	{

	Rbdb_DatabaseController*		database_controller		=	Rbdb_DatabaseController_internal_newWithoutRuntimeStorage( parent_environment );

	database_controller->parent_environment	=	parent_environment;

	RBDB_RUNTIME_STORAGE( database_controller, "database_controller" );

	return database_controller;
}

/*********
*  free  *
*********/

void Rbdb_DatabaseController_free(	Rbdb_DatabaseController** database_controller )	{
	
	//	close and free all databases
	Rbdb_DatabaseController_freeAllDatabases( *database_controller );

	if ( ( *database_controller )->runtime_storage_database != NULL )	{
		Rbdb_Database_free( & ( ( *database_controller )->runtime_storage_database ) );
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

Rbdb_DatabaseSettingsController* Rbdb_DatabaseController_settingsController(	Rbdb_DatabaseController* database_controller )	{
	return database_controller->settings_controller;
}

/**********************
*  parentEnvironment  *
**********************/

Rbdb_Environment* Rbdb_DatabaseController_parentEnvironment(	Rbdb_DatabaseController* database_controller )	{
	return database_controller->parent_environment;
}

/*******************************************************************************************************************************************************************************************
															Methods
*******************************************************************************************************************************************************************************************/

/****************
*  newDatabase  *
****************/

//	Create a new database for requested name
Rbdb_Database* Rbdb_DatabaseController_newDatabase(	Rbdb_DatabaseController*	database_controller, 
																										char*											database_name	)	{
	
	Rbdb_Database*	database						=	Rbdb_Database_new(	database_controller,
																														database_name );

	return database;
}

/**********************
*  closeAllDatabases  *
**********************/

//	Close all Databases
void Rbdb_DatabaseController_closeAllDatabases( Rbdb_DatabaseController* database_controller )	{
	
	Rbdb_Database_internal_closeAllStoredRuntimeAddresses(	database_controller->runtime_storage_database,
																													(void *(*)(void*)) & Rbdb_Database_close );
}

/*********************
*  freeAllDatabases  *
*********************/

//	Free all Databases (close if necessary)
void Rbdb_DatabaseController_freeAllDatabases( Rbdb_DatabaseController* database_controller )	{

	Rbdb_Database_internal_freeAllStoredRuntimeAddresses(	database_controller->runtime_storage_database,
																												(void *(*)(void**)) & Rbdb_Database_internal_freeFromRuntimeStorage );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  newWithoutRuntimeStorage  *
*****************************/

Rbdb_DatabaseController* Rbdb_DatabaseController_internal_newWithoutRuntimeStorage( Rbdb_Environment* parent_environment )	{

	Rbdb_DatabaseController*		database_controller = calloc( 1, sizeof( Rbdb_DatabaseController ) );
	
	database_controller->parent_environment = parent_environment;

	return database_controller;
}

