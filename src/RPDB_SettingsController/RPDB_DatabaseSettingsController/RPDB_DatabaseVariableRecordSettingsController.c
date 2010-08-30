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

#include "RPDB_DatabaseVariableRecordSettingsController.h"

#include "RPDB_DatabaseVariableRecordSettingsController_internal.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

	/*************
	*  new  *
	*************/

RPDB_DatabaseVariableRecordSettingsController* RPDB_DatabaseVariableRecordSettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseVariableRecordSettingsController*	database_variable_record_settings_controller = calloc( 1, sizeof( RPDB_DatabaseVariableRecordSettingsController ) );

	database_variable_record_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_variable_record_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseVariableRecordSettingsController_free(	RPDB_DatabaseVariableRecordSettingsController** database_variable_record_settings_controller )	{

	free( *database_variable_record_settings_controller );
	*database_variable_record_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseVariableRecordSettingsController_parentEnvironment(	RPDB_DatabaseVariableRecordSettingsController* database_variable_record_settings_controller )	{
	return database_variable_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseVariableRecordSettingsController_parentDatabase(	RPDB_DatabaseVariableRecordSettingsController* database_variable_record_settings_controller )	{
	return database_variable_record_settings_controller->parent_database_settings_controller->parent_database;
}

	/************************
	*  recordDelimeter  *
	************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_delim.html
int RPDB_DatabaseVariableRecordSettingsController_recordDelimeter( RPDB_DatabaseVariableRecordSettingsController* database_variable_record_settings_controller )	{

	RPDB_Database*				database	= database_variable_record_settings_controller->parent_database_settings_controller->parent_database;
	
	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->get_re_delim(	database->wrapped_bdb_database, 
														&( database_variable_record_settings_controller->record_delimeter ) );
	}
	
	return database_variable_record_settings_controller->record_delimeter;
}

	/****************************
	*  setRecordDelimeter  *
	****************************/

void RPDB_DatabaseVariableRecordSettingsController_setRecordDelimeter(	RPDB_DatabaseVariableRecordSettingsController*		database_variable_record_settings_controller, 
																		int													record_delimeter )	{

	RPDB_Database*				database	= database_variable_record_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_re_delim(	database->wrapped_bdb_database, 
														record_delimeter );
	}
	
	database_variable_record_settings_controller->record_delimeter = record_delimeter;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseVariableRecordSettingsController* RPDB_DatabaseVariableRecordSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseVariableRecordSettingsController* database_variable_record_settings_controller )	{

	RPDB_DatabaseVariableRecordSettingsController* database_variable_record_settings_controller_copy	=	RPDB_DatabaseVariableRecordSettingsController_new( database_variable_record_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_variable_record_settings_controller_copy->index_primary	=	database_variable_record_settings_controller->index_primary;
	database_variable_record_settings_controller_copy->secondary_key_is_immutable	=	database_variable_record_settings_controller->secondary_key_is_immutable;
	database_variable_record_settings_controller_copy->record_delimeter	=	database_variable_record_settings_controller->record_delimeter;

	return database_variable_record_settings_controller_copy;
}

