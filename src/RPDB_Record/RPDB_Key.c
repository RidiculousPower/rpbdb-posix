/*
 *		RPDB::RPDB_DatabaseController::RPDB_Database::(RPDB_DatabaseCursorController::RPDB_DatabaseCursor::)RPDB_Record::RPDB_DBT => RPDB_Key
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_Key.h"

#include "RPDB_DBT.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_Key* RPDB_Key_new( RPDB_Record* parent_record )	{

	return (RPDB_Key*) RPDB_DBT_new( parent_record );
}

/***************************
*  free  *
***************************/
void RPDB_Key_free(	RPDB_Key** key )	{

	RPDB_DBT_free( (RPDB_DBT**) key );
}

/***************************
*  settingsController  *
***************************/
RPDB_DatabaseRecordSettingsController* RPDB_Key_settingsController(	RPDB_Key* key )	{
	return key->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_Key_parentEnvironment(	RPDB_Key* key )	{
	return key->parent_record->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_Key_parentDatabase(	RPDB_Key* dbt )	{
	return dbt->parent_record->parent_database;
}

/***************************************
*  parentRecord  *
***************************************/
RPDB_Record* RPDB_Key_parentRecord(	RPDB_DatabaseRecordSettingsController* key )	{
	return key->parent_record;
}

/*****************
*  keyData  *
*****************/

void* RPDB_Key_keyData( RPDB_Key* key )	{

	return RPDB_DBT_data( (RPDB_DBT*) key );
}

/******************
*  setKeyData  *
******************/

void RPDB_Key_setKeyData(	RPDB_Key*	key,
							void*		key_raw,
							uint32_t	key_size )	{

	RPDB_DBT_setData(	(RPDB_DBT*) key,
						key_raw,
						key_size );
}

/*************
*  size  *
*************/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(RPDB_DatabaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t RPDB_Key_size( RPDB_Key* data )	{

	return RPDB_DBT_size(	(RPDB_DBT*) data  );
}	

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPDB_Key* RPDB_Key_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	RPDB_Record*	parent_record, 
											DBT*			bdb_dbt )	{
	
	RPDB_Key*	key	=	RPDB_Key_new( parent_record );
	
	//	Free our existing DBT
	free( key->wrapped_bdb_dbt );
	
	key->wrapped_bdb_dbt = bdb_dbt;
	
	return key;
}



