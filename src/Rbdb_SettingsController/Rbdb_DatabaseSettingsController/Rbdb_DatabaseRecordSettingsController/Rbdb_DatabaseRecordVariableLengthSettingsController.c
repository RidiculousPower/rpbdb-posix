/*
 *		Rbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseSettingsVariableRecordController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseRecordVariableLengthSettingsController.h"

#include "Rbdb_DatabaseRecordVariableLengthSettingsController_internal.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

	/*************
	*  new  *
	*************/

Rbdb_DatabaseRecordVariableLengthSettingsController* Rbdb_DatabaseRecordVariableLengthSettingsController_new( Rbdb_DatabaseRecordSettingsController* database_record_settings_controller )	{

	Rbdb_DatabaseRecordVariableLengthSettingsController*	database_record_variable_length_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseRecordVariableLengthSettingsController ) );

	database_record_variable_length_settings_controller->parent_database_record_settings_controller = database_record_settings_controller;

	return database_record_variable_length_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseRecordVariableLengthSettingsController_free(	Rbdb_DatabaseRecordVariableLengthSettingsController** database_record_variable_length_settings_controller )	{

	free( *database_record_variable_length_settings_controller );
	*database_record_variable_length_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseRecordVariableLengthSettingsController_parentEnvironment(	Rbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller )	{
	return database_record_variable_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseRecordVariableLengthSettingsController_parentDatabase(	Rbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller )	{
	return database_record_variable_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
}

	/************************
	*  recordDelimeter  *
	************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_delim.html
int Rbdb_DatabaseRecordVariableLengthSettingsController_delimeterByte( Rbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller )	{

	Rbdb_Database*				database	= database_record_variable_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
	
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

void Rbdb_DatabaseRecordVariableLengthSettingsController_setDelimeterByte(	Rbdb_DatabaseRecordVariableLengthSettingsController*		database_record_variable_length_settings_controller, 
																																							int													delimeter_byte )	{

	Rbdb_Database*				database	= database_record_variable_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;

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
Rbdb_DatabaseRecordVariableLengthSettingsController* Rbdb_DatabaseRecordVariableLengthSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller )	{

	Rbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller_copy	=	Rbdb_DatabaseRecordVariableLengthSettingsController_new( database_record_variable_length_settings_controller->parent_database_record_settings_controller );

	//	Instances and Pointers
	database_record_variable_length_settings_controller_copy->index_primary	=	database_record_variable_length_settings_controller->index_primary;
	database_record_variable_length_settings_controller_copy->secondary_key_is_immutable	=	database_record_variable_length_settings_controller->secondary_key_is_immutable;
	database_record_variable_length_settings_controller_copy->delimeter_byte	=	database_record_variable_length_settings_controller->delimeter_byte;

	return database_record_variable_length_settings_controller_copy;
}

