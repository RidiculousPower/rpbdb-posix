/*
 *		RPDB::DatabaseController::Database::DatabaseSequenceController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseSequenceController.h"

#include "RPDB_DatabaseSequence.h"

#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_DatabaseSequenceSettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  * 
********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_class.html
RPDB_DatabaseSequenceController* RPDB_DatabaseSequenceController_new( RPDB_Database* parent_database )	{
	
	RPDB_DatabaseSequenceController* database_sequence_controller = calloc( 1, sizeof( RPDB_DatabaseSequenceController ) );

	database_sequence_controller->parent_database	= parent_database;

	return database_sequence_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseSequenceController_free(	RPDB_DatabaseSequenceController** database_sequence_controller )	{

	free( database_sequence_controller );
}

/***************************
*  settingsController  *
***************************/
RPDB_DatabaseSequenceSettingsController* RPDB_DatabaseSequenceController_settingsController(	RPDB_DatabaseSequenceController* database_sequence_controller )	{
	return database_sequence_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseSequenceController_parentEnvironment(	RPDB_DatabaseSequenceController* database_sequence_controller )	{
	return database_sequence_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseSequenceController_parentDatabase(	RPDB_DatabaseSequenceController* database_sequence_controller )	{
	return database_sequence_controller->parent_database;
}

/********************
*  createSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_class.html
RPDB_DatabaseSequence* RPDB_DatabaseSequenceController_createSequence( RPDB_DatabaseSequenceController* database_sequence_controller )	{
	
	RPDB_DatabaseSequence*	new_sequence	=	RPDB_DatabaseSequence_new( database_sequence_controller );
	
	return new_sequence;
}

