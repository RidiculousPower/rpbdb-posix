/*
 *		RPbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseSettingsFixedRecordController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseRecordFixedLengthSettingsController.h"

#include "Environment.h"

#include "DatabaseRecordFixedLengthSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPbdb_DatabaseRecordFixedLengthSettingsController* RPbdb_DatabaseRecordFixedLengthSettingsController_new( RPbdb_DatabaseRecordSettingsController* database_record_settings_controller )	{

	RPbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseRecordFixedLengthSettingsController ) );

	database_record_fixed_length_settings_controller->parent_database_record_settings_controller = database_record_settings_controller;

	return database_record_fixed_length_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseRecordFixedLengthSettingsController_free(	RPbdb_DatabaseRecordFixedLengthSettingsController** database_record_fixed_length_settings_controller )	{

	free( *database_record_fixed_length_settings_controller );
	*database_record_fixed_length_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseRecordFixedLengthSettingsController_parentEnvironment(	RPbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{
	return database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseRecordFixedLengthSettingsController_parentDatabase(	RPbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{
	return database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
}

/*********************
*  recordLength  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_len.html
uint32_t RPbdb_DatabaseRecordFixedLengthSettingsController_recordLength( RPbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{
	
	RPbdb_Database*	database	=	database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL
			&&	database_record_fixed_length_settings_controller->record_length == 0 )	{

		database->wrapped_bdb_database->get_re_len(	database->wrapped_bdb_database,
																								&( database_record_fixed_length_settings_controller->record_length ) );
	}
	
	return database_record_fixed_length_settings_controller->record_length;
}

/************************
*  setRecordLength  *
************************/

//	The DB->set_re_len method configures a database, not only operations performed using the specified DB name.
void RPbdb_DatabaseRecordFixedLengthSettingsController_setRecordLength(	RPbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller,
																																				uint32_t											record_length )	{
	
	RPbdb_Database*	database	= database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
	
	database_record_fixed_length_settings_controller->record_length = record_length;
	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_re_len(	database->wrapped_bdb_database, 
																								record_length );	
	}
}

/********************
*  paddingByte  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_pad.html
int RPbdb_DatabaseRecordFixedLengthSettingsController_paddingByte( RPbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{

	RPbdb_Database*	database	= database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{

		database->wrapped_bdb_database->get_re_pad(	database->wrapped_bdb_database, 
													&( database_record_fixed_length_settings_controller->record_padding_byte ) );
	}
	
	return database_record_fixed_length_settings_controller->record_padding_byte;
}

/************************
*  setPaddingByte  *
************************/
	
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_pad.html
void RPbdb_DatabaseRecordFixedLengthSettingsController_setPaddingByte(	RPbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller, 
																	int													record_padding_byte )	{

	RPbdb_Database*	database	= database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_re_pad(	database->wrapped_bdb_database,
																								record_padding_byte );		
	}
	database_record_fixed_length_settings_controller->record_padding_byte = record_padding_byte;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseRecordFixedLengthSettingsController* RPbdb_DatabaseRecordFixedLengthSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{

	RPbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller_copy	=	RPbdb_DatabaseRecordFixedLengthSettingsController_new( database_record_fixed_length_settings_controller->parent_database_record_settings_controller );

	//	Instances and Pointers
	database_record_fixed_length_settings_controller_copy->record_length	=	database_record_fixed_length_settings_controller->record_length;
	database_record_fixed_length_settings_controller_copy->record_padding_byte	=	database_record_fixed_length_settings_controller->record_padding_byte;

	return database_record_fixed_length_settings_controller_copy;
}

