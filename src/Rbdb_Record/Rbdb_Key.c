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
#include "Rbdb_Key_internal.h"

#include "Rbdb_DBT.h"

#include "Rbdb_Record.h"
#include "Rbdb_Environment.h"
#include "Rbdb_Database.h"
#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseRecordSettingsController.h"
#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"

#include <string.h>

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

/*********
*  free  *
*********/
void Rbdb_Key_free(	Rbdb_Key** key )	{

	Rbdb_DBT_free( (Rbdb_DBT**) key );
}

/***********************
*  settingsController  *
***********************/

Rbdb_DatabaseRecordSettingsController* Rbdb_Key_settingsController(	Rbdb_Key* key )	{
	return key->settings_controller;
}

/**********************
*  parentEnvironment  *
**********************/

Rbdb_Environment* Rbdb_Key_parentEnvironment(	Rbdb_Key* key )	{
	return key->parent_record->parent_database->parent_database_controller->parent_environment;
}

/*******************
*  parentDatabase  *
*******************/

Rbdb_Database* Rbdb_Key_parentDatabase(	Rbdb_Key* key )	{
	return key->parent_record->parent_database;
}

/*****************
*  parentRecord  *
*****************/

Rbdb_Record* Rbdb_Key_parentRecord(	Rbdb_DatabaseRecordSettingsController* key )	{
	return key->parent_record;
}

/************
*  keyData  *
************/

void* Rbdb_Key_rawData( Rbdb_Key* key )	{

	//	if we have a footer and the size of the data is the size of the footer, return NULL
	void*	raw_data	=	NULL;
	
	if (		! key->has_type
			||	Rbdb_DBT_size( (Rbdb_DBT*) key ) != sizeof( CerializeType )	)	{

		raw_data	=	Rbdb_DBT_data( (Rbdb_DBT*) key );
	}

	return raw_data;
}

/***************
*  setRawData  *
***************/

void Rbdb_Key_setRawData(	Rbdb_Key*		key,
													void*				key_raw,
													uint32_t		key_size )	{

	//	if we have key typing, we need to append the key to the data we are setting
	if ( Rbdb_DBT_size( (Rbdb_DBT*) key ) == sizeof( CerializeType ) )	{
		
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

	Rbdb_DBT_setData(	(Rbdb_DBT*) key,
										key_raw,
										key_size );
}

/*********
*  type  *
*********/

CerializeType Rbdb_Key_type( Rbdb_Key* key )	{

	return Rbdb_DBT_type(	(Rbdb_DBT*) key );
}

/************
*  setType  *
************/

void Rbdb_Key_setType(	Rbdb_Key*												key,
												CerializeType	type )	{

		Rbdb_DBT_setType(	(Rbdb_DBT*) key,
											type );
	
}

/*********
*  size  *
*********/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(Rbdb_DatabaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t Rbdb_Key_size( Rbdb_Key* key )	{

	return Rbdb_DBT_size( (Rbdb_DBT*) key );
}	

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
