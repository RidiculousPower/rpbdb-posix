/*
 *		RPbdb::RPbdb_DatabaseController::RPbdb_Database::(RPbdb_DatabaseCursorController::RPbdb_DatabaseCursor::)RPbdb_Record::RPBDB_DBT => RPbdb_Data
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Data.h"
#include "Data_internal.h"

#include "Environment.h"

#include "Database.h"
#include "DatabaseSettingsController.h"
#include "DatabaseRecordSettingsController.h"
#include "DatabaseRecordReadWriteSettingsController.h"
#include "DBT_internal.h"

#include "DBT.h"
	
#include <string.h>
#include <sys/time.h>
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_Data* RPbdb_Data_new( RPbdb_Record* parent_record )	{

	return (RPbdb_Data*) RPbdb_DBT_new( parent_record );
}

/***************************
*  free  *
***************************/
void RPbdb_Data_free(	RPbdb_Data** data )	{

	RPbdb_DBT_free( (RPbdb_DBT**) data );
}

/***************************
*  settingsController  *
***************************/
RPbdb_DatabaseRecordSettingsController* RPbdb_Data_settingsController(	RPbdb_Data* data )	{
	return data->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_Data_parentEnvironment(	RPbdb_Data* data )	{
	return data->parent_record->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_Data_parentDatabase(	RPbdb_Data* data )	{
	return data->parent_record->parent_database;
}

/***************************************
*  parentRecord  *
***************************************/
RPbdb_Record* RPbdb_Data_parentRecord(	RPbdb_DatabaseRecordSettingsController* data )	{
	return data->parent_record;
}

/*****************
*  rawData  *
*****************/

void* RPbdb_Data_rawData( RPbdb_Data* data )	{

	return RPbdb_DBT_data( (RPbdb_DBT*) data );
}

/******************
*  setRawData  *
******************/

void RPbdb_Data_setRawData(	RPbdb_Data*	data,
														void*				data_raw,
														uint32_t		data_size )	{

	RPbdb_DBT_setData(	(RPbdb_DBT*) data,
										data_raw,
										data_size );
}

/*********
*  type  *
*********/

CerializeType RPbdb_Data_type( RPbdb_Data* data )	{

	return RPbdb_DBT_type( (RPbdb_DBT*) data );
}

/******************
*  setType  *
******************/

void RPbdb_Data_setType(	RPbdb_Data*				data,
												CerializeType			type )	{

	RPbdb_DBT_setType(	(RPbdb_DBT*) data,
										type );

}

/*************
*  size  *
*************/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(RPbdb_DatabaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t RPbdb_Data_size( RPbdb_Data* data )	{

	return RPbdb_DBT_size(	(RPbdb_DBT*) data );
}	

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

