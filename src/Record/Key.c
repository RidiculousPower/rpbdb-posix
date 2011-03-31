/*
 *		RPbdb::RPbdb_DatabaseController::RPbdb_Database::(RPbdb_DatabaseCursorController::RPbdb_DatabaseCursor::)RPbdb_Record::RPBDB_DBT => RPbdb_Key
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Key.h"
#include "Key_internal.h"

#include "DBT.h"

#include "Record.h"
#include "Environment.h"
#include "Database.h"
#include "DatabaseSettingsController.h"
#include "DatabaseRecordSettingsController.h"
#include "DatabaseRecordReadWriteSettingsController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_Key* RPbdb_Key_new( RPbdb_Record* parent_record )	{

	return (RPbdb_Key*) RPbdb_DBT_new( parent_record );
}

/*********
*  free  *
*********/
void RPbdb_Key_free(	RPbdb_Key** key )	{

	RPbdb_DBT_free( (RPbdb_DBT**) key );
}

/***********************
*  settingsController  *
***********************/

RPbdb_DatabaseRecordSettingsController* RPbdb_Key_settingsController(	RPbdb_Key* key )	{
	return key->settings_controller;
}

/**********************
*  parentEnvironment  *
**********************/

RPbdb_Environment* RPbdb_Key_parentEnvironment(	RPbdb_Key* key )	{
	return key->parent_record->parent_database->parent_database_controller->parent_environment;
}

/*******************
*  parentDatabase  *
*******************/

RPbdb_Database* RPbdb_Key_parentDatabase(	RPbdb_Key* key )	{
	return key->parent_record->parent_database;
}

/*****************
*  parentRecord  *
*****************/

RPbdb_Record* RPbdb_Key_parentRecord(	RPbdb_DatabaseRecordSettingsController* key )	{
	return key->parent_record;
}

/************
*  keyData  *
************/

void* RPbdb_Key_rawData( RPbdb_Key* key )	{

	//	if we have a footer and the size of the data is the size of the footer, return NULL
	void*	raw_data	=	NULL;
	
	if (		! key->has_type
			||	RPbdb_DBT_size( (RPbdb_DBT*) key ) != sizeof( CerializeType )	)	{

		raw_data	=	RPbdb_DBT_data( (RPbdb_DBT*) key );
	}

	return raw_data;
}

/***************
*  setRawData  *
***************/

void RPbdb_Key_setRawData(	RPbdb_Key*		key,
													void*				key_raw,
													uint32_t		key_size )	{

	//	if we have key typing, we need to append the key to the data we are setting
	if ( RPbdb_DBT_size( (RPbdb_DBT*) key ) == sizeof( CerializeType ) )	{
		
		//	allocate new structure
		uint32_t	new_size	=	key_size
												+	sizeof( CerializeType );
		void*			new_data	=	calloc( 1, new_size );
		
		//	copy data and footer to new structure
		memcpy(	new_data,
						key_raw,
						key_size );
		memcpy(	new_data + key_size,
						key->wrapped_bdb_dbt->data,
						sizeof( CerializeType ) );
		
		//	assign new data to data
		key_raw		=	new_data;
		key_size	=	new_size;
	}

	RPbdb_DBT_setData(	(RPbdb_DBT*) key,
										key_raw,
										key_size );
}

/*********
*  type  *
*********/

CerializeType RPbdb_Key_type( RPbdb_Key* key )	{

	return RPbdb_DBT_type(	(RPbdb_DBT*) key );
}

/************
*  setType  *
************/

void RPbdb_Key_setType(	RPbdb_Key*												key,
												CerializeType	type )	{

		RPbdb_DBT_setType(	(RPbdb_DBT*) key,
											type );
	
}

/*********
*  size  *
*********/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(RPbdb_DatabaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t RPbdb_Key_size( RPbdb_Key* key )	{

	return RPbdb_DBT_size( (RPbdb_DBT*) key );
}	

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
