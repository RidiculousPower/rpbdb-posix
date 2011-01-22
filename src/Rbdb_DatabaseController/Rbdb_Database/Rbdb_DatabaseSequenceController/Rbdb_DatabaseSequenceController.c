/*
 *		Rbdb::DatabaseController::Database::DatabaseSequenceController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseSequenceController.h"

#include "Rbdb_Environment.h"
#include "Rbdb_RuntimeStorageController.h"

#include "Rbdb_Database.h"
#include "Rbdb_Database_internal.h"
#include "Rbdb_DatabaseSequence.h"
#include "Rbdb_DatabaseSequence_internal.h"

#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseSequenceSettingsController.h"

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
Rbdb_DatabaseSequenceController* Rbdb_DatabaseSequenceController_new( Rbdb_Database* parent_database )	{
	
	Rbdb_DatabaseSequenceController* database_sequence_controller = calloc( 1, sizeof( Rbdb_DatabaseSequenceController ) );

	RBDB_RUNTIME_STORAGE( database_sequence_controller, "database_sequence_controller" );

	database_sequence_controller->parent_database	= parent_database;

	int		sequence_storage_database_name_length	=	strlen( parent_database->name ) + strlen( "__sequences" ) + 1;
	char*	sequence_storage_database_name	=	calloc( sequence_storage_database_name_length, sizeof( char ) );

	Rbdb_DatabaseController*	database_controller	=	Rbdb_Database_parentDatabaseController( parent_database );
	database_sequence_controller->sequence_storage_database	=	Rbdb_Database_new(	database_controller,
																																								sequence_storage_database_name );

	free( sequence_storage_database_name );
	
	return database_sequence_controller;
}

/*********
*  free  *
*********/
void Rbdb_DatabaseSequenceController_free(	Rbdb_DatabaseSequenceController** database_sequence_controller )	{

	Rbdb_DatabaseSequenceController_freeAllSequences( *database_sequence_controller );

	Rbdb_Database_free( & ( *database_sequence_controller )->sequence_storage_database );

	//	free runtime storage
	if ( ( *database_sequence_controller )->runtime_storage_database != NULL )	{
		Rbdb_Database_free( & ( ( *database_sequence_controller )->runtime_storage_database ) );
	}

	free( *database_sequence_controller );
	*database_sequence_controller = NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_DatabaseSequenceSettingsController* Rbdb_DatabaseSequenceController_settingsController(	Rbdb_DatabaseSequenceController* database_sequence_controller )	{
	return database_sequence_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseSequenceController_parentEnvironment(	Rbdb_DatabaseSequenceController* database_sequence_controller )	{
	return database_sequence_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseSequenceController_parentDatabase(	Rbdb_DatabaseSequenceController* database_sequence_controller )	{
	return database_sequence_controller->parent_database;
}

/**********************
*  closeAllSequences  *
**********************/

void Rbdb_DatabaseSequenceController_closeAllSequences( Rbdb_DatabaseSequenceController* database_sequence_controller )	{

	Rbdb_Database_internal_closeAllStoredRuntimeAddresses(	database_sequence_controller->runtime_storage_database,
																													(void *(*)(void*)) & Rbdb_DatabaseSequence_closeSequence );
	Rbdb_Database_close( database_sequence_controller->sequence_storage_database );
}

/*********************
*  freeAllSequences  *
*********************/

//	free all cursors; close if necessary
void Rbdb_DatabaseSequenceController_freeAllSequences( Rbdb_DatabaseSequenceController* database_sequence_controller )	{
	
	Rbdb_DatabaseSequenceController_closeAllSequences( database_sequence_controller );
	Rbdb_Database_internal_freeAllStoredRuntimeAddresses(	database_sequence_controller->runtime_storage_database,
																												(void *(*)(void**)) & Rbdb_DatabaseSequence_internal_freeFromRuntimeStorage );
}

/*************
*  sequence  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_class.html
Rbdb_DatabaseSequence* Rbdb_DatabaseSequenceController_sequence(	Rbdb_DatabaseSequenceController*	database_sequence_controller,
																																	char*															storage_key )	{
	
	Rbdb_Database_internal_ensureOpen( database_sequence_controller->sequence_storage_database );	
	
	Rbdb_DatabaseSequence*	new_sequence	=	Rbdb_DatabaseSequence_new(	database_sequence_controller,
																																			database_sequence_controller->sequence_storage_database,
																																			storage_key );
	
	return new_sequence;
}

/*******************
*  deleteSequence  *
*******************/

Rbdb_DatabaseSequence* Rbdb_DatabaseSequenceController_deleteSequence(	Rbdb_DatabaseSequenceController*	database_sequence_controller,
																																				char*															storage_key )	{
	
	Rbdb_Database_internal_ensureOpen( database_sequence_controller->sequence_storage_database );	

	Rbdb_DatabaseSequence*	database_sequence	=	Rbdb_DatabaseSequenceController_sequence(	database_sequence_controller,
																																												storage_key );

	Rbdb_DatabaseSequence_deleteSequence( database_sequence );

	return database_sequence;
}

/*******************
*  renameSequence  *
*******************/

Rbdb_DatabaseSequence* Rbdb_DatabaseSequenceController_renameSequence(	Rbdb_DatabaseSequenceController*	database_sequence_controller,
																																				char*															storage_key,
																																				char*															new_storage_key )	{
	
	Rbdb_Database_internal_ensureOpen( database_sequence_controller->sequence_storage_database );	

	Rbdb_DatabaseSequence*	database_sequence	=	Rbdb_DatabaseSequenceController_sequence(	database_sequence_controller,
																																												storage_key );

	Rbdb_DatabaseSequence_renameSequence( database_sequence,
																				new_storage_key );

	return database_sequence;
}

