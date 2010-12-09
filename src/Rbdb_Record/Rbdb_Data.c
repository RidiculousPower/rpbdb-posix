/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record::Rbdb_DBT => Rbdb_Data
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_Data.h"
#include "Rbdb_Data_internal.h"

#include "Rbdb_DBT.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_Data* Rbdb_Data_new( Rbdb_Record* parent_record )	{

	return (Rbdb_Data*) Rbdb_DBT_new( parent_record );
}

/***************************
*  free  *
***************************/
void Rbdb_Data_free(	Rbdb_Data** data )	{

	Rbdb_DBT_free( (Rbdb_DBT**) data );
}

/***************************
*  settingsController  *
***************************/
Rbdb_DatabaseRecordSettingsController* Rbdb_Data_settingsController(	Rbdb_Data* data )	{
	return data->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_Data_parentEnvironment(	Rbdb_Data* data )	{
	return data->parent_record->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_Data_parentDatabase(	Rbdb_Data* data )	{
	return data->parent_record->parent_database;
}

/***************************************
*  parentRecord  *
***************************************/
Rbdb_Record* Rbdb_Data_parentRecord(	Rbdb_DatabaseRecordSettingsController* data )	{
	return data->parent_record;
}

/*****************
*  rawData  *
*****************/

void* Rbdb_Data_rawData( Rbdb_Data* data )	{

	return Rbdb_DBT_data( (Rbdb_DBT*) data );
}

/******************
*  setRawData  *
******************/

void Rbdb_Data_setRawData(	Rbdb_Data*	data,
							void*		data_raw,
							uint32_t	data_size )	{

	Rbdb_DBT_setData(	(Rbdb_DBT*) data,
						data_raw,
						data_size );
}

/*************
*  size  *
*************/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(Rbdb_DatabaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t Rbdb_Data_size( Rbdb_Data* data )	{

	return Rbdb_DBT_size(	(Rbdb_DBT*) data  );
}	

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

Rbdb_Data* Rbdb_Data_internal_newrb_Rbdb_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	Rbdb_Record*	parent_record, 
																																																					DBT*			bdb_dbt )	{
	
	Rbdb_Data*	data	=	Rbdb_Data_new( parent_record );
	
	//	Free our existing DBT
	free( data->wrapped_bdb_dbt );
	
	data->wrapped_bdb_dbt = bdb_dbt;
	
	return data;
}
