/*
 *		RPDB::DatabaseController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseController.h"
#include "RPDB_DatabaseController_internal.h"

#include "RPDB_Database.h"
#include "RPDB_Database_internal.h"
#include "RPDB_DatabaseCursorController.h"
#include "RPDB_DatabaseCursor.h"

#include "RPDB_Environment.h"

#include "RPDB_Record.h"
#include "RPDB_Data.h"

#include "RPDB_RuntimeStorageController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/
	
RPDB_DatabaseController* RPDB_DatabaseController_new( RPDB_Environment* parent_environment )	{

	RPDB_DatabaseController*		database_controller		=	RPDB_DatabaseController_internal_newWithoutRuntimeStorage( parent_environment );

	RPDB_RuntimeStorageController*	runtime_storage_controller;
	RPDB_DatabaseController*	runtime_database_controller	=	RPDB_Environment_databaseController(	runtime_storage_controller->runtime_environment );
	RPDB_Database*	runtime_storage_database	=	RPDB_Database_new(	runtime_database_controller,
																																	"database_controller" );
	database_controller->runtime_storage_database	=	RPDB_Database_internal_initForRuntimeStorage(	runtime_storage_database );

	database_controller->record_number	=	1;

	return database_controller;
}

/*********
*  free  *
*********/

void RPDB_DatabaseController_free(	RPDB_DatabaseController** database_controller )	{
	
	//	close and free all databases
	RPDB_DatabaseController_freeAllDatabases( *database_controller );

	if ( ( *database_controller )->runtime_storage_database != NULL )	{
		RPDB_Database_free( & ( ( *database_controller )->runtime_storage_database ) );
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

RPDB_DatabaseSettingsController* RPDB_DatabaseController_settingsController(	RPDB_DatabaseController* database_controller )	{
	return database_controller->settings_controller;
}

/**********************
*  parentEnvironment  *
**********************/

RPDB_Environment* RPDB_DatabaseController_parentEnvironment(	RPDB_DatabaseController* database_controller )	{
	return database_controller->parent_environment;
}

/*******************************************************************************************************************************************************************************************
															Methods
*******************************************************************************************************************************************************************************************/

/****************
*  newDatabase  *
****************/

//	Create a new database for requested name
RPDB_Database* RPDB_DatabaseController_newDatabase(	RPDB_DatabaseController*	database_controller, 
																										char*											database_name	)	{
	
	RPDB_Database*	database						=	RPDB_Database_new(	database_controller,
																														database_name );

	uintptr_t	database_address	=	(uintptr_t) database;

	RPDB_Database_appendRawData(	database_controller->runtime_storage_database,
																& database_address,
																sizeof( uintptr_t ) );

	database->runtime_identifier	=	database_controller->record_number;

	return database;
}

/**********************
*  closeAllDatabases  *
**********************/

//	Close all Databases
void RPDB_DatabaseController_closeAllDatabases( RPDB_DatabaseController* database_controller )	{
	
	RPDB_Database_internal_closeAllStoredRuntimeAddresses(	database_controller->runtime_storage_database,
																													(void *(*)(void*)) & RPDB_Database_close );
}

/*********************
*  freeAllDatabases  *
*********************/

//	Free all Databases (close if necessary)
void RPDB_DatabaseController_freeAllDatabases( RPDB_DatabaseController* database_controller )	{

	RPDB_Database_internal_freeAllStoredRuntimeAddresses(	database_controller->runtime_storage_database,
																												(void *(*)(void**)) & RPDB_Database_free );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  newWithoutRuntimeStorage  *
*****************************/

RPDB_DatabaseController* RPDB_DatabaseController_internal_newWithoutRuntimeStorage( RPDB_Environment* parent_environment )	{

	RPDB_DatabaseController*		database_controller = calloc( 1, sizeof( RPDB_DatabaseController ) );
	
	database_controller->parent_environment = parent_environment;

	return database_controller;
}

