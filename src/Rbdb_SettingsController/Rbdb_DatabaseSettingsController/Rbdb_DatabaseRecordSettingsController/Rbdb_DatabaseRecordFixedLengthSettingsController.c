/*
 *		Rbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseSettingsFixedRecordController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseRecordFixedLengthSettingsController.h"

#include "Rbdb_Environment.h"

#include "Rbdb_DatabaseRecordFixedLengthSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
Rbdb_DatabaseRecordFixedLengthSettingsController* Rbdb_DatabaseRecordFixedLengthSettingsController_new( Rbdb_DatabaseRecordSettingsController* database_record_settings_controller )	{

	Rbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseRecordFixedLengthSettingsController ) );

	database_record_fixed_length_settings_controller->parent_database_record_settings_controller = database_record_settings_controller;

	return database_record_fixed_length_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseRecordFixedLengthSettingsController_free(	Rbdb_DatabaseRecordFixedLengthSettingsController** database_record_fixed_length_settings_controller )	{

	free( *database_record_fixed_length_settings_controller );
	*database_record_fixed_length_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseRecordFixedLengthSettingsController_parentEnvironment(	Rbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{
	return database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseRecordFixedLengthSettingsController_parentDatabase(	Rbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{
	return database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
}

/*********************
*  recordLength  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_len.html
uint32_t Rbdb_DatabaseRecordFixedLengthSettingsController_recordLength( Rbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{
	
	Rbdb_Database*	database	=	database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;

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
void Rbdb_DatabaseRecordFixedLengthSettingsController_setRecordLength(	Rbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller,
																																				uint32_t											record_length )	{
	
	Rbdb_Database*	database	= database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
	
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
int Rbdb_DatabaseRecordFixedLengthSettingsController_paddingByte( Rbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{

	Rbdb_Database*	database	= database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;

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
void Rbdb_DatabaseRecordFixedLengthSettingsController_setPaddingByte(	Rbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller, 
																	int													record_padding_byte )	{

	Rbdb_Database*	database	= database_record_fixed_length_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;

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
Rbdb_DatabaseRecordFixedLengthSettingsController* Rbdb_DatabaseRecordFixedLengthSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller )	{

	Rbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller_copy	=	Rbdb_DatabaseRecordFixedLengthSettingsController_new( database_record_fixed_length_settings_controller->parent_database_record_settings_controller );

	//	Instances and Pointers
	database_record_fixed_length_settings_controller_copy->record_length	=	database_record_fixed_length_settings_controller->record_length;
	database_record_fixed_length_settings_controller_copy->record_padding_byte	=	database_record_fixed_length_settings_controller->record_padding_byte;

	return database_record_fixed_length_settings_controller_copy;
}

