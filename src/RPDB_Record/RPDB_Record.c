/*
 *		RPDB::RPDB_DatabaseController::RPDB_Database::(RPDB_DatabaseCursorController::RPDB_DatabaseCursor::)RPDB_Record
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_Record.h"
#include "RPDB_Record_internal.h"

#include "RPDB_Key.h"
#include "RPDB_Data.h"
#include "RPDB_DBT.h"
#include "RPDB_SecondaryKeys.h"

#include "RPDB_Environment.h"

#include "RPDB_Database.h"

#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_DatabaseRecordSettingsController.h"
#include "RPDB_DatabaseRecordSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_Record* RPDB_Record_new( RPDB_Database* parent_database )	{

	RPDB_Record*	record = RPDB_Record_internal_newWithoutDBT( parent_database );

	//	We have one primary key
	record->key = RPDB_Key_new( record );

	//	We can have multiple secondary keys
	record->primary_key = RPDB_Key_new( record );

	//	We have one object
	record->data = RPDB_Data_new( record );

	return record;
}

void	RPDB_Record_free( RPDB_Record** record )	{

	if ( ( *record )->key != NULL )	{
		
		//	if our primary key is the same as our retrieval key, NULLify it so we don't free it twice
		if ( ( *record )->primary_key == ( *record )->key )	{
			( *record )->primary_key = NULL;
		}
		
		RPDB_Key_free( & ( ( *record )->key ) );
	}
	if ( ( *record )->primary_key != NULL )	{
		
		RPDB_Key_free( & ( ( *record )->primary_key ) );
	}
	if ( ( *record )->data != NULL )	{
		
		RPDB_Data_free( & ( ( *record )->data ) );
	}
	
	if ( ( *record )->settings_controller != NULL )	{
		RPDB_DatabaseRecordSettingsController_free( & ( ( *record )->settings_controller ) );
	}
	
	free( *record );
	*record	=	NULL;
}

/***************************
*  settingsController  *
***************************/
 
 RPDB_DatabaseRecordSettingsController* RPDB_Record_settingsController(	RPDB_Record* record )	{
	return record->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_Record_parentEnvironment(	RPDB_Record* record )	{
	return record->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_Record_parentDatabase(	RPDB_Record* record )	{
	return record->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Record Management Public Methods
*******************************************************************************************************************************************************************************************/

/**************
*  key  *
**************/

RPDB_Key* RPDB_Record_key( RPDB_Record* record )	{

	if ( record != NULL )	{	
		return record->key;
	}
	return NULL;
}

/**************
*  setKey  *
**************/

void RPDB_Record_setKey(	RPDB_Record*			record,
							RPDB_Key*				primary_key )	{

	record->key = primary_key;
}

/******************
*  setKeyData  *
******************/

void RPDB_Record_setKeyFromRawKey(	RPDB_Record*		record,
										void*				key_raw,
										uint32_t			key_size )	{

	RPDB_DBT_setData(	(RPDB_DBT*) record->key, 
						key_raw,
						key_size );
}


/**************
*  rawData  *
**************/

void* RPDB_Record_rawData( RPDB_Record* record )	{		
	
	if ( record != NULL )	{	
		return record->data->wrapped_bdb_dbt->data;
	}
	return NULL;
}

/*****************
*  setRawData  *
*****************/

void RPDB_Record_setRawData(	RPDB_Record*	record,
								void*			raw_data,
								u_int32_t		raw_data_size )	{		
	
	record->data->wrapped_bdb_dbt->data	=	raw_data;
	record->data->wrapped_bdb_dbt->size	=	raw_data_size;
}

/**************
*  rawKey  *
**************/

void* RPDB_Record_rawKey( RPDB_Record* record )	{		
	
	if ( record != NULL )	{	
		return record->key->wrapped_bdb_dbt->data;
	}
	return NULL;
}

/*****************
*  setRawKey  *
*****************/

void RPDB_Record_setRawKey(	RPDB_Record*	record,
								void*			raw_key,
								u_int32_t		raw_key_size )	{		
	
	record->key->wrapped_bdb_dbt->data	=	raw_key;
	record->key->wrapped_bdb_dbt->size	=	raw_key_size;
}

/**************
*  object  *
**************/

RPDB_Data* RPDB_Record_data( RPDB_Record* record )	{		

	if ( record != NULL )	{	
		return record->data;
	}
	return NULL;
}

/**************
*  size  *
**************/

uint32_t RPDB_Record_keySize( RPDB_Record* record )	{		
	
	
	if ( record != NULL )	{	
		return record->key->wrapped_bdb_dbt->size;
	}
	return 0;
}

/**************
*  size  *
**************/

uint32_t RPDB_Record_dataSize( RPDB_Record* record )	{		
	

	if ( record != NULL )	{	
		return record->data->wrapped_bdb_dbt->size;
	}
	return 0;
}

/**************
*  setObject  *
**************/

void RPDB_Record_setData(	RPDB_Record*			record,
							RPDB_Data*			primary_object )	{

	record->data = primary_object;
}

/******************
*  setObjectData  *
******************/

void RPDB_Record_setDataFromRawData(	RPDB_Record*		record,
										void*				data_raw,
										uint32_t			data_size )	{

	RPDB_DBT_setData(	(RPDB_DBT*) record->data, 
						data_raw,
						data_size );
}

/******************
*  primaryKey  *
******************/

RPDB_Key* RPDB_Record_primaryKey( RPDB_Record* record )	{

	if ( record != NULL )	{	
		return record->key;
	}
	return NULL;
}

/**********************
*  retrievalKey  *
**********************/

RPDB_Key* RPDB_Record_retrievalKey( RPDB_Record* record )	{
		
	if ( record != NULL )	{	
		return record->key;
	}
	return NULL;
}

/*******************************************************************************************************************************************************************************************
																		Retrieval Status Public Methods
*******************************************************************************************************************************************************************************************/

//	Functions to watch whether record has been retrieved/inserted from DB

//	FIX - these require being hooked up more appropriately

/******************
*  setStatus  *
******************/

void RPDB_Record_setExistsInDatabase(	RPDB_Record*	record,
										BOOL			data_status	)	{

	record->exists_in_database = data_status;
}

/**************
*  status  *
**************/

int RPDB_Record_existsInDatabase( RPDB_Record* record )	{
	return record->exists_in_database;
}

/******************
*  setStatus  *
******************/

void RPDB_Record_setRequiresUpdateToDatabase(	RPDB_Record*	record,
												BOOL			data_status	)	{
	record->requires_update_to_database = data_status;
}

/**************
*  status  *
**************/

int RPDB_Record_requiresUpdateToDatabase( RPDB_Record* record )	{
	return record->requires_update_to_database;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  newWithoutDBT  *
*****************************/

RPDB_Record* RPDB_Record_internal_newWithoutDBT(	RPDB_Database* parent_database	)	{

	RPDB_Record*		record = calloc( 1, sizeof( RPDB_Record ) );
		
	if ( parent_database )	{
	
		record->parent_database = parent_database;

		//	Make call to instantiate local settings controller
		record->settings_controller	=	RPDB_DatabaseRecordSettingsController_internal_copyOfSettingsControllerForInstance( RPDB_DatabaseSettingsController_recordSettingsController( RPDB_Database_settingsController( parent_database ) ) );
		
	}
	
	return record;
}
	
/*****************************
*  newFromKeyDBTDataDBT  *
*****************************/

RPDB_Record* RPDB_Record_internal_newFromKeyDBTDataDBT(	RPDB_Database* parent_database,
														DBT*	dbt_key,
														DBT*	dbt_data	)	{
	
	RPDB_Record*	record = RPDB_Record_new( parent_database );
		
	free( record->key->wrapped_bdb_dbt );
	free( record->data->wrapped_bdb_dbt );

	record->key->wrapped_bdb_dbt	= dbt_key;
	record->data->wrapped_bdb_dbt			= dbt_data;

	return record;	
}

/*****************************
*  newFromKeyData  *
*****************************/

RPDB_Record* RPDB_Record_internal_newFromKeyData(	RPDB_Database* parent_database,
													RPDB_Key*	dbt_key,
													RPDB_Data*	dbt_data	)	{
	
	RPDB_Record*	record = RPDB_Record_internal_newWithoutDBT( parent_database );
	
	if ( dbt_key == NULL )	{
	
		dbt_key	=	RPDB_Key_new( record );
	}
	
	if ( dbt_data == NULL )	{
		
		dbt_data	=	RPDB_Data_new( record );
	}
	
	record->key		= dbt_key;
	dbt_key->parent_record	= record;
	record->data			= dbt_data;
	dbt_data->parent_record	= record;
	
	return record;	
}
