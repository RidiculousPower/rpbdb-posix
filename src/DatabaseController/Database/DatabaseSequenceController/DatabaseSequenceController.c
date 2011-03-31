/*
 *		RPbdb::DatabaseController::Database::DatabaseSequenceController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseSequenceController.h"

#include "Environment.h"
#include "RuntimeStorageController.h"

#include "Database.h"
#include "Database_internal.h"
#include "DatabaseSequence.h"
#include "DatabaseSequence_internal.h"

#include "DatabaseSettingsController.h"
#include "DatabaseSequenceSettingsController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  * 
********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_class.html
RPbdb_DatabaseSequenceController* RPbdb_DatabaseSequenceController_new( RPbdb_Database* parent_database )	{
	
	RPbdb_DatabaseSequenceController* database_sequence_controller = calloc( 1, sizeof( RPbdb_DatabaseSequenceController ) );

	RPBDB_RUNTIME_STORAGE( database_sequence_controller, "database_sequence_controller" );

	database_sequence_controller->parent_database	= parent_database;

  //  create new name var for database and copy contents into new var
	int		sequence_storage_database_name_length	=	strlen( parent_database->name ) + strlen( "__sequences" ) + 1;
	char*	sequence_storage_database_name	=	calloc( sequence_storage_database_name_length, sizeof( char ) );
  strcpy( sequence_storage_database_name, parent_database->name );
  char* end_of_parent_db_name_ptr = (void*) sequence_storage_database_name + strlen( parent_database->name );
  strcpy( end_of_parent_db_name_ptr, "__sequences" );

	RPbdb_DatabaseController*	database_controller	=	RPbdb_Database_parentDatabaseController( parent_database );
	database_sequence_controller->sequence_storage_database	=	RPbdb_Database_new(	database_controller,
																																								sequence_storage_database_name );

	free( sequence_storage_database_name );
	
	return database_sequence_controller;
}

/*********
*  free  *
*********/
void RPbdb_DatabaseSequenceController_free(	RPbdb_DatabaseSequenceController** database_sequence_controller )	{

	RPbdb_DatabaseSequenceController_freeAllSequences( *database_sequence_controller );

	RPbdb_Database_free( & ( *database_sequence_controller )->sequence_storage_database );

	//	free runtime storage
	if ( ( *database_sequence_controller )->runtime_storage_database != NULL )	{
		RPbdb_Database_free( & ( ( *database_sequence_controller )->runtime_storage_database ) );
	}

	free( *database_sequence_controller );
	*database_sequence_controller = NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_DatabaseSequenceSettingsController* RPbdb_DatabaseSequenceController_settingsController(	RPbdb_DatabaseSequenceController* database_sequence_controller )	{
	return database_sequence_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseSequenceController_parentEnvironment(	RPbdb_DatabaseSequenceController* database_sequence_controller )	{
	return database_sequence_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseSequenceController_parentDatabase(	RPbdb_DatabaseSequenceController* database_sequence_controller )	{
	return database_sequence_controller->parent_database;
}

/**********************
*  closeAllSequences  *
**********************/

void RPbdb_DatabaseSequenceController_closeAllSequences( RPbdb_DatabaseSequenceController* database_sequence_controller )	{

	RPbdb_Database_internal_closeAllStoredRuntimeAddresses(	database_sequence_controller->runtime_storage_database,
																													(void *(*)(void*)) & RPbdb_DatabaseSequence_closeSequence );
	RPbdb_Database_close( database_sequence_controller->sequence_storage_database );
}

/*********************
*  freeAllSequences  *
*********************/

//	free all cursors; close if necessary
void RPbdb_DatabaseSequenceController_freeAllSequences( RPbdb_DatabaseSequenceController* database_sequence_controller )	{
	
	RPbdb_DatabaseSequenceController_closeAllSequences( database_sequence_controller );
	RPbdb_Database_internal_freeAllStoredRuntimeAddresses(	database_sequence_controller->runtime_storage_database,
																												(void *(*)(void**)) & RPbdb_DatabaseSequence_internal_freeFromRuntimeStorage );
}

/*************
*  sequence  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_class.html
RPbdb_DatabaseSequence* RPbdb_DatabaseSequenceController_sequence(	RPbdb_DatabaseSequenceController*	database_sequence_controller,
																																	char*															storage_key )	{
	
	RPbdb_Database_internal_ensureOpen( database_sequence_controller->sequence_storage_database );	
	
	RPbdb_DatabaseSequence*	new_sequence	=	RPbdb_DatabaseSequence_new(	database_sequence_controller,
																																			database_sequence_controller->sequence_storage_database,
																																			storage_key );
	
	return new_sequence;
}

/*******************
*  deleteSequence  *
*******************/

RPbdb_DatabaseSequence* RPbdb_DatabaseSequenceController_deleteSequence(	RPbdb_DatabaseSequenceController*	database_sequence_controller,
																																				char*															storage_key )	{
	
	RPbdb_Database_internal_ensureOpen( database_sequence_controller->sequence_storage_database );	

	RPbdb_DatabaseSequence*	database_sequence	=	RPbdb_DatabaseSequenceController_sequence(	database_sequence_controller,
																																												storage_key );

	RPbdb_DatabaseSequence_deleteSequence( database_sequence );

	return database_sequence;
}

/*******************
*  renameSequence  *
*******************/

RPbdb_DatabaseSequence* RPbdb_DatabaseSequenceController_renameSequence(	RPbdb_DatabaseSequenceController*	database_sequence_controller,
																																				char*															storage_key,
																																				char*															new_storage_key )	{
	
	RPbdb_Database_internal_ensureOpen( database_sequence_controller->sequence_storage_database );	

	RPbdb_DatabaseSequence*	database_sequence	=	RPbdb_DatabaseSequenceController_sequence(	database_sequence_controller,
																																												storage_key );

	RPbdb_DatabaseSequence_renameSequence( database_sequence,
																				new_storage_key );

	return database_sequence;
}

