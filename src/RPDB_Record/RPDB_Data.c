/*
 *		RPDB::RPDB_DatabaseController::RPDB_Database::(RPDB_DatabaseCursorController::RPDB_DatabaseCursor::)RPDB_Record::RPDB_DBT => RPDB_Data
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_Data.h"
#include "RPDB_Data_internal.h"

#include "RPDB_DBT.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_Data* RPDB_Data_new( RPDB_Record* parent_record )	{

	return (RPDB_Data*) RPDB_DBT_new( parent_record );
}

/***************************
*  free  *
***************************/
void RPDB_Data_free(	RPDB_Data** data )	{

	RPDB_DBT_free( (RPDB_DBT**) data );
}

/***************************
*  settingsController  *
***************************/
RPDB_DatabaseRecordSettingsController* RPDB_Data_settingsController(	RPDB_Data* data )	{
	return data->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_Data_parentEnvironment(	RPDB_Data* data )	{
	return data->parent_record->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_Data_parentDatabase(	RPDB_Data* data )	{
	return data->parent_record->parent_database;
}

/***************************************
*  parentRecord  *
***************************************/
RPDB_Record* RPDB_Data_parentRecord(	RPDB_DatabaseRecordSettingsController* data )	{
	return data->parent_record;
}

/*****************
*  rawData  *
*****************/

void* RPDB_Data_rawData( RPDB_Data* data )	{

	return RPDB_DBT_data( (RPDB_DBT*) data );
}

/******************
*  setRawData  *
******************/

void RPDB_Data_setRawData(	RPDB_Data*	data,
							void*		data_raw,
							uint32_t	data_size )	{

	RPDB_DBT_setData(	(RPDB_DBT*) data,
						data_raw,
						data_size );
}

/*************
*  size  *
*************/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(RPDB_DatabaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t RPDB_Data_size( RPDB_Data* data )	{

	return RPDB_DBT_size(	(RPDB_DBT*) data  );
}	

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPDB_Data* RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	RPDB_Record*	parent_record, 
																																																					DBT*			bdb_dbt )	{
	
	RPDB_Data*	data	=	RPDB_Data_new( parent_record );
	
	//	Free our existing DBT
	free( data->wrapped_bdb_dbt );
	
	data->wrapped_bdb_dbt = bdb_dbt;
	
	return data;
}
