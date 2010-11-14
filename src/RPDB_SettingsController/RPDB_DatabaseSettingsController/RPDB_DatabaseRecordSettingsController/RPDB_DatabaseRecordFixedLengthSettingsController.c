/*
 *		RPDB::DatabaseController::Database::DatabaseSettingsController::DatabaseSettingsFixedRecordController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseRecordFixedLengthSettingsController.h"

#include "RPDB_Environment.h"

#include "RPDB_DatabaseRecordFixedLengthSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_DatabaseRecordFixedLengthSettingsController* RPDB_DatabaseRecordFixedLengthSettingsController_new( RPDB_DatabaseRecordSettingsController* database_record_settings_controller )	{

	RPDB_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller = calloc( 1, sizeof( RPDB_DatabaseRecordFixedLengthSettingsController ) );

	database_record_fixed_length_settings_controller->parent_database_record_settings_controller = database_record_settings_controller;

	return database_record_fixed_length_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseRecordFixedLengthSettingsController_free(	RPDB_DatabaseRecordFixedLengthSettingsController** database_record_fixed_length_settings_controller )	{

	free( *database_record_fixed_length_settings_controller );
	*database_record_fixed_length_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseRecordFixedLengthSettingsController_parentEnvironment(	RPDB_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{
	return database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseRecordFixedLengthSettingsController_parentDatabase(	RPDB_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{
	return database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
}

/*********************
*  recordLength  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_len.html
uint32_t RPDB_DatabaseRecordFixedLengthSettingsController_recordLength( RPDB_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{
	
	RPDB_Database*	database	=	database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;

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
void RPDB_DatabaseRecordFixedLengthSettingsController_setRecordLength(	RPDB_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller,
																																				uint32_t											record_length )	{
	
	RPDB_Database*	database	= database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
	
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
int RPDB_DatabaseRecordFixedLengthSettingsController_paddingByte( RPDB_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{

	RPDB_Database*	database	= database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;

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
void RPDB_DatabaseRecordFixedLengthSettingsController_setPaddingByte(	RPDB_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller, 
																	int													record_padding_byte )	{

	RPDB_Database*	database	= database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;

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
RPDB_DatabaseRecordFixedLengthSettingsController* RPDB_DatabaseRecordFixedLengthSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{

	RPDB_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller_copy	=	RPDB_DatabaseRecordFixedLengthSettingsController_new( database_record_fixed_length_settings_controller->parent_database_record_settings_controller );

	//	Instances and Pointers
	database_record_fixed_length_settings_controller_copy->record_length	=	database_record_fixed_length_settings_controller->record_length;
	database_record_fixed_length_settings_controller_copy->record_padding_byte	=	database_record_fixed_length_settings_controller->record_padding_byte;

	return database_record_fixed_length_settings_controller_copy;
}

