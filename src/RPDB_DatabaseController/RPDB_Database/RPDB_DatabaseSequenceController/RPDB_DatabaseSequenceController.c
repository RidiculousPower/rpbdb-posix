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

#include "Rbdb_DatabaseSequence.h"

#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseSequenceSettingsController.h"

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

	database_sequence_controller->parent_database	= parent_database;

	return database_sequence_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseSequenceController_free(	Rbdb_DatabaseSequenceController** database_sequence_controller )	{

	free( database_sequence_controller );
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

/********************
*  createSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_class.html
Rbdb_DatabaseSequence* Rbdb_DatabaseSequenceController_createSequence( Rbdb_DatabaseSequenceController* database_sequence_controller )	{
	
	Rbdb_DatabaseSequence*	new_sequence	=	Rbdb_DatabaseSequence_new( database_sequence_controller );
	
	return new_sequence;
}

