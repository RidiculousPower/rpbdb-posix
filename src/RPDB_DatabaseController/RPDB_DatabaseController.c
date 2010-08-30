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

#include "RPDB_RuntimeStorage.h"
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

	char*		database_controller_runtime_storage_name	=	RPDB_DatabaseController_internal_uniqueIdentifier( database_controller );

	//	Initialize our database controller runtime storage
	database_controller->runtime_storage	=	RPDB_RuntimeStorageController_runtimeStorageInEnvironmentWithName(	RPDB_RuntimeStorageController_sharedInstance(), 
																																																							parent_environment,
																																																							database_controller_runtime_storage_name );	
	return database_controller;
}

/*********
*  free  *
*********/

void RPDB_DatabaseController_free(	RPDB_DatabaseController** database_controller )	{
	
	//	close and free all databases
	RPDB_DatabaseController_freeAllDatabases( *database_controller );

	if ( ( *database_controller )->runtime_storage != NULL )	{
		RPDB_RuntimeStorage_free( & ( ( *database_controller )->runtime_storage ) );
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

/*********************
*  databaseWithName  *
*********************/

//	Return a name that has been created or creates it if necessary
RPDB_Database* RPDB_DatabaseController_databaseWithName(	RPDB_DatabaseController*	database_controller, 
																														char*											database_name	)	{
	
	RPDB_Database*	database	=	NULL;

	//	Check and see if cursor_name exists in runtime storage
	//	If it doesn't, we need to create it and store it
	uintptr_t*	raw_key	=	(uintptr_t*) RPDB_RuntimeStorage_retrieveRawKey(	database_controller->runtime_storage,
																																			database_name,
																																			( strlen( database_name ) + 1 ) * sizeof( char ) );
	if ( raw_key != NULL )	{
		//	Set our pointer to our stored address
		database	=	(RPDB_Database*) *raw_key;
	}
	
	return database;
}

/****************
*  newDatabase  *
****************/

//	Create a new database for requested name
RPDB_Database* RPDB_DatabaseController_newDatabase(	RPDB_DatabaseController*	database_controller, 
																										char*											database_name	)	{
	
	RPDB_Database*	database						=	RPDB_Database_new(	database_controller,
																														database_name );

	uintptr_t	database_address	=	(uintptr_t) database;
	
	//	Store pointer to database in runtime storage
	RPDB_RuntimeStorage_insertRawKeyDataPair(	database_controller->runtime_storage,
																						database->name,
																						( strlen( database->name ) + 1 ) * sizeof( char ),
																						& database_address,
																						sizeof( uintptr_t ) );
	return database;
}

/**********************
*  closeAllDatabases  *
**********************/

//	Close all Databases
void RPDB_DatabaseController_closeAllDatabases( RPDB_DatabaseController* database_controller )	{

	RPDB_DatabaseCursor*	runtime_storage_cursor	=	database_controller->runtime_storage->database_cursor;
	
	RPDB_DatabaseCursor_retrieveFirst( runtime_storage_cursor );
	
	RPDB_Record*	record		=	NULL;
	
	RPDB_Database* this_database	=	NULL;
	while ( ( record = RPDB_DatabaseCursor_iterate( runtime_storage_cursor ) ) != NULL )	{
		
		this_database	=	(RPDB_Database*) *(uintptr_t*) RPDB_Record_rawData( record );
		
		RPDB_Database_close( this_database );
	}
	
}

/*********************
*  freeAllDatabases  *
*********************/

//	Free all Databases (close if necessary)
void RPDB_DatabaseController_freeAllDatabases( RPDB_DatabaseController* database_controller )	{

	RPDB_DatabaseCursor*	runtime_storage_cursor	=	database_controller->runtime_storage->database_cursor;
	
	RPDB_DatabaseCursor_retrieveFirst( runtime_storage_cursor );
	
	RPDB_Record*	record		=	NULL;
	
	while ( ( record = RPDB_DatabaseCursor_iterate( runtime_storage_cursor ) ) != NULL )	{
		
		RPDB_Database* this_database	=	(RPDB_Database*) *(uintptr_t*) RPDB_Record_rawData( record );
		
		if ( this_database != NULL )	{
			//	free cursor - function already names proper closing etc.
			RPDB_Database_free( & this_database );
		}		
	}
	
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

/*********************
*  uniqueIdentifier  *
*********************/

char* RPDB_DatabaseController_internal_uniqueIdentifier( RPDB_DatabaseController* database_controller )	{
	
	RPDB_Environment*	parent_environment				=	database_controller->parent_environment;
	char*				parent_environment_name	=	parent_environment->name;
	
	uintptr_t	parent_environment_address				=	(uintptr_t) parent_environment;
	
	char*		parent_environment_address_string		=	calloc( 21, sizeof( char ) );
	sprintf(	parent_environment_address_string,
						"%" PRIxPTR "",			parent_environment_address );
	//	we have one database controller per environment, so using the environment's pointer address (which is always unique)
	//	should suffice
	int			unique_identifier_length			=		strlen( "database_controller"  )
																					+	strlen( RPDB_DELIMITER )
																					+	strlen( parent_environment_name )
																					+	strlen( RPDB_DELIMITER )
																					+	strlen( parent_environment_address_string )
																					+	1;
	char*		unique_identifier		=	calloc( unique_identifier_length , sizeof( char ) );
	
	sprintf(	unique_identifier,
						"%s%s%s%s%s",		"database_controller",
														RPDB_DELIMITER,
														parent_environment_name,
														RPDB_DELIMITER,
														parent_environment_address_string	);
	
	free( parent_environment_address_string );
	parent_environment_address_string	=	NULL;

	return unique_identifier;
}

