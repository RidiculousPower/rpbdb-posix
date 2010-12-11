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

#include "RBDB_DBT.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_Key* Rbdb_Key_new( Rbdb_Record* parent_record )	{

	return (Rbdb_Key*) RBDB_DBT_new( parent_record );
}

/***************************
*  free  *
***************************/
void Rbdb_Key_free(	Rbdb_Key** key )	{

	RBDB_DBT_free( (RBDB_DBT**) key );
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

void* Rbdb_Key_keyData( Rbdb_Key* key )	{

	return RBDB_DBT_data( (RBDB_DBT*) key );
}

/******************
*  setKeyData  *
******************/

void Rbdb_Key_setKeyData(	Rbdb_Key*	key,
							void*		key_raw,
							uint32_t	key_size )	{

	RBDB_DBT_setData(	(RBDB_DBT*) key,
						key_raw,
						key_size );
}

/*************
*  size  *
*************/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(Rbdb_DatabaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t Rbdb_Key_size( Rbdb_Key* data )	{

	return RBDB_DBT_size(	(RBDB_DBT*) data  );
}	

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

Rbdb_Key* Rbdb_Key_internal_newrb_Rbdb_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	Rbdb_Record*	parent_record, 
											DBT*			bdb_dbt )	{
	
	Rbdb_Key*	key	=	Rbdb_Key_new( parent_record );
	
	//	Free our existing DBT
	free( key->wrapped_bdb_dbt );
	
	key->wrapped_bdb_dbt = bdb_dbt;
	
	return key;
}



