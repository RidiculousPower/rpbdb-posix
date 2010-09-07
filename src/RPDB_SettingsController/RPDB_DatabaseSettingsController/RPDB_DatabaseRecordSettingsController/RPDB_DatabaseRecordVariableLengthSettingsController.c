/*
 *		RPDB::DatabaseController::Database::DatabaseSettingsController::DatabaseSettingsVariableRecordController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseRecordVariableLengthSettingsController.h"

#include "RPDB_DatabaseRecordVariableLengthSettingsController_internal.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

	/*************
	*  new  *
	*************/

RPDB_DatabaseRecordVariableLengthSettingsController* RPDB_DatabaseRecordVariableLengthSettingsController_new( RPDB_DatabaseRecordSettingsController* database_record_settings_controller )	{

	RPDB_DatabaseRecordVariableLengthSettingsController*	database_record_variable_length_settings_controller = calloc( 1, sizeof( RPDB_DatabaseRecordVariableLengthSettingsController ) );

	database_record_variable_length_settings_controller->parent_database_record_settings_controller = database_record_settings_controller;

	return database_record_variable_length_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseRecordVariableLengthSettingsController_free(	RPDB_DatabaseRecordVariableLengthSettingsController** database_record_variable_length_settings_controller )	{

	free( *database_record_variable_length_settings_controller );
	*database_record_variable_length_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseRecordVariableLengthSettingsController_parentEnvironment(	RPDB_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller )	{
	return database_record_variable_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseRecordVariableLengthSettingsController_parentDatabase(	RPDB_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller )	{
	return database_record_variable_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
}

	/************************
	*  recordDelimeter  *
	************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_delim.html
int RPDB_DatabaseRecordVariableLengthSettingsController_recordDelimeter( RPDB_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller )	{

	RPDB_Database*				database	= database_record_variable_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
	
	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->get_re_delim(	database->wrapped_bdb_database, 
														&( database_record_variable_length_settings_controller->record_delimeter ) );
	}
	
	return database_record_variable_length_settings_controller->record_delimeter;
}

	/****************************
	*  setRecordDelimeter  *
	****************************/

void RPDB_DatabaseRecordVariableLengthSettingsController_setRecordDelimeter(	RPDB_DatabaseRecordVariableLengthSettingsController*		database_record_variable_length_settings_controller, 
																		int													record_delimeter )	{

	RPDB_Database*				database	= database_record_variable_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_re_delim(	database->wrapped_bdb_database, 
														record_delimeter );
	}
	
	database_record_variable_length_settings_controller->record_delimeter = record_delimeter;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseRecordVariableLengthSettingsController* RPDB_DatabaseRecordVariableLengthSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller )	{

	RPDB_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller_copy	=	RPDB_DatabaseRecordVariableLengthSettingsController_new( database_record_variable_length_settings_controller->parent_database_record_settings_controller );

	//	Instances and Pointers
	database_record_variable_length_settings_controller_copy->index_primary	=	database_record_variable_length_settings_controller->index_primary;
	database_record_variable_length_settings_controller_copy->secondary_key_is_immutable	=	database_record_variable_length_settings_controller->secondary_key_is_immutable;
	database_record_variable_length_settings_controller_copy->record_delimeter	=	database_record_variable_length_settings_controller->record_delimeter;

	return database_record_variable_length_settings_controller_copy;
}

