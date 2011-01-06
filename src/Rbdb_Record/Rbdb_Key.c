/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record::RBDB_DBT => Rbdb_Key
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_Key.h"

#include "Rbdb_DBT.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_Key* Rbdb_Key_new( Rbdb_Record* parent_record )	{

	return (Rbdb_Key*) Rbdb_DBT_new( parent_record );
}

/***************************
*  free  *
***************************/
void Rbdb_Key_free(	Rbdb_Key** key )	{

	Rbdb_DBT_free( (Rbdb_DBT**) key );
}

/***************************
*  settingsController  *
***************************/

Rbdb_DatabaseRecordSettingsController* Rbdb_Key_settingsController(	Rbdb_Key* key )	{
	return key->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/

Rbdb_Environment* Rbdb_Key_parentEnvironment(	Rbdb_Key* key )	{
	return key->parent_record->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/

Rbdb_Database* Rbdb_Key_parentDatabase(	Rbdb_Key* dbt )	{
	return dbt->parent_record->parent_database;
}

/***************************************
*  parentRecord  *
***************************************/

Rbdb_Record* Rbdb_Key_parentRecord(	Rbdb_DatabaseRecordSettingsController* key )	{
	return key->parent_record;
}

/*****************
*  keyData  *
*****************/

void* Rbdb_Key_rawData( Rbdb_Key* key )	{

	return Rbdb_DBT_data( (Rbdb_DBT*) key );
}

/******************
*  setRawData  *
******************/

void Rbdb_Key_setRawData(	Rbdb_Key*		key,
													void*				key_raw,
													uint32_t		key_size )	{

	Rbdb_DBT_setData(	(Rbdb_DBT*) key,
										key_raw,
										key_size );
}

/*****************
*  type  *
*****************/

Rbdb_DatabaseRecordStorageType Rbdb_Key_type( Rbdb_Key* key )	{

	return Rbdb_DBT_type( (Rbdb_DBT*) key );
}

/******************
*  setType  *
******************/

void Rbdb_Key_setType(	Rbdb_Key*												key,
												Rbdb_DatabaseRecordStorageType	type )	{

	Rbdb_DBT_setType(	(Rbdb_DBT*) key,
										type );
}

/*************
*  size  *
*************/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(Rbdb_DatabaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t Rbdb_Key_size( Rbdb_Key* data )	{

	return Rbdb_DBT_size(	(Rbdb_DBT*) data  );
}	

