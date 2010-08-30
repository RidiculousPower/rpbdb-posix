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

#include "RPDB_DatabaseFixedRecordSettingsController.h"

#include "RPDB_Environment.h"

#include "RPDB_DatabaseFixedRecordSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_DatabaseFixedRecordSettingsController* RPDB_DatabaseFixedRecordSettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseFixedRecordSettingsController*		database_fixed_record_settings_controller = calloc( 1, sizeof( RPDB_DatabaseFixedRecordSettingsController ) );

	database_fixed_record_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_fixed_record_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseFixedRecordSettingsController_free(	RPDB_DatabaseFixedRecordSettingsController** database_fixed_record_settings_controller )	{

	free( *database_fixed_record_settings_controller );
	*database_fixed_record_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseFixedRecordSettingsController_parentEnvironment(	RPDB_DatabaseFixedRecordSettingsController* database_fixed_record_settings_controller )	{
	return database_fixed_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseFixedRecordSettingsController_parentDatabase(	RPDB_DatabaseFixedRecordSettingsController* database_fixed_record_settings_controller )	{
	return database_fixed_record_settings_controller->parent_database_settings_controller->parent_database;
}

/*********************
*  recordLength  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_len.html
uint32_t RPDB_DatabaseFixedRecordSettingsController_recordLength( RPDB_DatabaseFixedRecordSettingsController* database_fixed_record_settings_controller )	{
	
	DB*					database;
	
	database = database_fixed_record_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	
	if ( database_fixed_record_settings_controller->record_length == 0 )	{
		database->get_re_len(	database,
								&( database_fixed_record_settings_controller->record_length ) );
	}
	
	return database_fixed_record_settings_controller->record_length;
}

/************************
*  setRecordLength  *
************************/

//	The DB->set_re_len method configures a database, not only operations performed using the specified DB name.
void RPDB_DatabaseFixedRecordSettingsController_setRecordLength(	RPDB_DatabaseFixedRecordSettingsController*		database_fixed_record_settings_controller,
																	uint32_t											record_length )	{
	
	RPDB_Database*	database	= database_fixed_record_settings_controller->parent_database_settings_controller->parent_database;
	
	database_fixed_record_settings_controller->record_length = record_length;
	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_re_len(	database->wrapped_bdb_database, 
													record_length );	
	}
}

/********************
*  paddingByte  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_pad.html
int RPDB_DatabaseFixedRecordSettingsController_paddingByte( RPDB_DatabaseFixedRecordSettingsController* database_fixed_record_settings_controller )	{

	RPDB_Database*	database	= database_fixed_record_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{

		database->wrapped_bdb_database->get_re_pad(	database->wrapped_bdb_database, 
													&( database_fixed_record_settings_controller->record_padding_byte ) );
	}
	
	return database_fixed_record_settings_controller->record_padding_byte;
}

/************************
*  setPaddingByte  *
************************/
	
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_pad.html
void RPDB_DatabaseFixedRecordSettingsController_setPaddingByte(	RPDB_DatabaseFixedRecordSettingsController*		database_fixed_record_settings_controller, 
																	int													record_padding_byte )	{

	RPDB_Database*	database	= database_fixed_record_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_re_pad(	database->wrapped_bdb_database,
													record_padding_byte );		
	}
	database_fixed_record_settings_controller->record_padding_byte = record_padding_byte;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseFixedRecordSettingsController* RPDB_DatabaseFixedRecordSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseFixedRecordSettingsController* database_fixed_record_settings_controller )	{

	RPDB_DatabaseFixedRecordSettingsController* database_fixed_record_settings_controller_copy	=	RPDB_DatabaseFixedRecordSettingsController_new( database_fixed_record_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_fixed_record_settings_controller_copy->record_length	=	database_fixed_record_settings_controller->record_length;
	database_fixed_record_settings_controller_copy->record_padding_byte	=	database_fixed_record_settings_controller->record_padding_byte;

	return database_fixed_record_settings_controller_copy;
}

