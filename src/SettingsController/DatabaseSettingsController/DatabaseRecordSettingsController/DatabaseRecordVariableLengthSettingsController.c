/*
 *		RPbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseSettingsVariableRecordController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseRecordVariableLengthSettingsController.h"

#include "DatabaseRecordVariableLengthSettingsController_internal.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

	/*************
	*  new  *
	*************/

RPbdb_DatabaseRecordVariableLengthSettingsController* RPbdb_DatabaseRecordVariableLengthSettingsController_new( RPbdb_DatabaseRecordSettingsController* database_record_settings_controller )	{

	RPbdb_DatabaseRecordVariableLengthSettingsController*	database_record_variable_length_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseRecordVariableLengthSettingsController ) );

	database_record_variable_length_settings_controller->parent_database_record_settings_controller = database_record_settings_controller;

	return database_record_variable_length_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseRecordVariableLengthSettingsController_free(	RPbdb_DatabaseRecordVariableLengthSettingsController** database_record_variable_length_settings_controller )	{

	free( *database_record_variable_length_settings_controller );
	*database_record_variable_length_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseRecordVariableLengthSettingsController_parentEnvironment(	RPbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller )	{
	return database_record_variable_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseRecordVariableLengthSettingsController_parentDatabase(	RPbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller )	{
	return database_record_variable_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
}

	/************************
	*  recordDelimeter  *
	************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_delim.html
int RPbdb_DatabaseRecordVariableLengthSettingsController_delimeterByte( RPbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller )	{

	RPbdb_Database*				database	= database_record_variable_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
	
	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
		
		database->wrapped_bdb_database->get_re_delim(	database->wrapped_bdb_database, 
																									&( database_record_variable_length_settings_controller->delimeter_byte ) );
	}
	
	return database_record_variable_length_settings_controller->delimeter_byte;
}

	/****************************
	*  setRecordDelimeter  *
	****************************/

void RPbdb_DatabaseRecordVariableLengthSettingsController_setDelimeterByte(	RPbdb_DatabaseRecordVariableLengthSettingsController*		database_record_variable_length_settings_controller, 
																																							int													delimeter_byte )	{

	RPbdb_Database*				database	= database_record_variable_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
	
		database->wrapped_bdb_database->set_re_delim(	database->wrapped_bdb_database, 
																									delimeter_byte );
	}
	
	database_record_variable_length_settings_controller->delimeter_byte = delimeter_byte;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseRecordVariableLengthSettingsController* RPbdb_DatabaseRecordVariableLengthSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller )	{

	RPbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller_copy	=	RPbdb_DatabaseRecordVariableLengthSettingsController_new( database_record_variable_length_settings_controller->parent_database_record_settings_controller );

	//	Instances and Pointers
	database_record_variable_length_settings_controller_copy->index_primary	=	database_record_variable_length_settings_controller->index_primary;
	database_record_variable_length_settings_controller_copy->secondary_key_is_immutable	=	database_record_variable_length_settings_controller->secondary_key_is_immutable;
	database_record_variable_length_settings_controller_copy->delimeter_byte	=	database_record_variable_length_settings_controller->delimeter_byte;

	return database_record_variable_length_settings_controller_copy;
}

