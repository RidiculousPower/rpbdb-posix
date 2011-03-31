/*
 *		RPbdb::RPbdb_DatabaseController::RPbdb_Database::(RPbdb_DatabaseCursorController::RPbdb_DatabaseCursor::)RPbdb_Record
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Record.h"
#include "Record_internal.h"

#include <cerialize.h>

#include "Database_internal.h"

#include "Key.h"
#include "Key_internal.h"
#include "Data.h"
#include "Data_internal.h"
#include "DBT.h"
#include "SecondaryKeys.h"

#include "Environment.h"

#include "Database.h"

#include "DatabaseSettingsController.h"
#include "DatabaseRecordSettingsController.h"
#include "DatabaseRecordSettingsController_internal.h"

#include "DatabaseRecordReadWriteSettingsController.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_Record* RPbdb_Record_new( RPbdb_Database* parent_database )	{

	RPbdb_Record*	record = RPbdb_Record_internal_newWithoutDBT( parent_database );

	if ( parent_database->runtime_storage_database != NULL )	{
		record->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_database->runtime_storage_database,
																																							(void*) record );
	}

	//	We have one primary key
	record->key = RPbdb_Key_new( record );

	//	We can have multiple secondary keys
	record->primary_key = RPbdb_Key_new( record );

	//	We have one object
	record->data = RPbdb_Data_new( record );

	return record;
}

/*************
*  free  *
*************/

void	RPbdb_Record_free( RPbdb_Record** record )	{

	if ( ( *record )->parent_database->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *record )->parent_database->runtime_storage_database,
																											( *record )->runtime_identifier );
	}
	RPbdb_Record_internal_freeFromRuntimeStorage( record );
}

/***************************
*  freeFromRuntimeStorage  *
***************************/

void	RPbdb_Record_internal_freeFromRuntimeStorage( RPbdb_Record** record )	{

	if ( ( *record )->key != NULL )	{
		
		//	if our primary key is the same as our retrieval key, NULLify it so we don't free it twice
		if ( ( *record )->primary_key == ( *record )->key )	{
			( *record )->primary_key = NULL;
		}
		
		RPbdb_Key_free( & ( ( *record )->key ) );
	}
	if ( ( *record )->primary_key != NULL )	{
		
		RPbdb_Key_free( & ( ( *record )->primary_key ) );
	}
	if ( ( *record )->data != NULL )	{
		
		RPbdb_Data_free( & ( ( *record )->data ) );
	}
	
	if ( ( *record )->settings_controller != NULL )	{
		RPbdb_DatabaseRecordSettingsController_free( & ( ( *record )->settings_controller ) );
	}
	
	free( *record );
	*record	=	NULL;
}

/***************************
*  settingsController  *
***************************/
 
 RPbdb_DatabaseRecordSettingsController* RPbdb_Record_settingsController(	RPbdb_Record* record )	{
	return record->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_Record_parentEnvironment(	RPbdb_Record* record )	{
	return record->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_Record_parentDatabase(	RPbdb_Record* record )	{
	return record->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Record Management Public Methods
*******************************************************************************************************************************************************************************************/

/**************
*  key  *
**************/

RPbdb_Key* RPbdb_Record_key( RPbdb_Record* record )	{

	if ( record != NULL )	{	
		return record->key;
	}
	return NULL;
}

/**************
*  setKey  *
**************/

void RPbdb_Record_setKey(	RPbdb_Record*			record,
							RPbdb_Key*				primary_key )	{

	record->key = primary_key;
}

/**************
*  rawData  *
**************/

void* RPbdb_Record_rawData( RPbdb_Record* record )	{		
	
	if ( record != NULL )	{	
		return record->data->wrapped_bdb_dbt->data;
	}
	return NULL;
}

/*****************
*  setRawData  *
*****************/

void RPbdb_Record_setRawData(	RPbdb_Record*	record,
															void*					raw_data,
															u_int32_t			raw_data_size )	{		
	
	RPbdb_Data_setRawData(	record->key,
												raw_data,
												raw_data_size );
}

/**************
*  rawKey  *
**************/

void* RPbdb_Record_rawKey( RPbdb_Record* record )	{		
	
	if ( record != NULL )	{	
		return record->key->wrapped_bdb_dbt->data;
	}
	return NULL;
}

/*****************
*  setRawKey  *
*****************/

void RPbdb_Record_setRawKey(	RPbdb_Record*	record,
								void*			raw_key,
								u_int32_t		raw_key_size )	{		
	
	RPbdb_Key_setRawData(	record->key,
												raw_key,
												raw_key_size );
}

/**************
*  object  *
**************/

RPbdb_Data* RPbdb_Record_data( RPbdb_Record* record )	{		

	if ( record != NULL )	{	
		return record->data;
	}
	return NULL;
}

/**************
*  size  *
**************/

uint32_t RPbdb_Record_keySize( RPbdb_Record* record )	{		
	
	if ( record != NULL )	{	
		return RPbdb_Key_size( record->key );
	}
	return 0;
}

/**************
*  size  *
**************/

uint32_t RPbdb_Record_dataSize( RPbdb_Record* record )	{		
	

	if ( record != NULL )	{	
		return RPbdb_Data_size( record->data );
	}
	return 0;
}

/******************
*  rawPrimaryKey  *
******************/

void* RPbdb_Record_rawPrimaryKey( RPbdb_Record* record )	{		
	
	if ( record != NULL )	{	
		return record->primary_key->wrapped_bdb_dbt->data;
	}
	return NULL;
}

/*******************
*  primaryKeySize  *
*******************/

uint32_t RPbdb_Record_primaryKeySize( RPbdb_Record* record )	{		
	
	
	if ( record != NULL )	{	
		return RPbdb_Key_size( record->primary_key );
	}
	return 0;
}


/**************
*  setObject  *
**************/

void RPbdb_Record_setData(	RPbdb_Record*			record,
													RPbdb_Data*			primary_object )	{

	record->data = primary_object;
}

/******************
*  primaryKey  *
******************/

RPbdb_Key* RPbdb_Record_primaryKey( RPbdb_Record* record )	{

	if ( record != NULL )	{	
		return record->key;
	}
	return NULL;
}

/**********************
*  retrievalKey  *
**********************/

RPbdb_Key* RPbdb_Record_retrievalKey( RPbdb_Record* record )	{
		
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

void RPbdb_Record_setExistsInDatabase(	RPbdb_Record*	record,
																			BOOL			data_status	)	{

	record->exists_in_database = data_status;
}

/**************
*  status  *
**************/

int RPbdb_Record_existsInDatabase( RPbdb_Record* record )	{
	return record->exists_in_database;
}

/******************
*  setStatus  *
******************/

void RPbdb_Record_setRequiresUpdateToDatabase(	RPbdb_Record*	record,
																							BOOL			data_status	)	{
	record->requires_update_to_database = data_status;
}

/**************
*  status  *
**************/

int RPbdb_Record_requiresUpdateToDatabase( RPbdb_Record* record )	{
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

RPbdb_Record* RPbdb_Record_internal_newWithoutDBT(	RPbdb_Database* parent_database	)	{

	RPbdb_Record*		record = calloc( 1, sizeof( RPbdb_Record ) );
		
	if ( parent_database )	{
	
		record->parent_database = parent_database;
		
		RPbdb_DatabaseSettingsController*				database_settings_controller				=	RPbdb_Database_settingsController( parent_database );
		RPbdb_DatabaseRecordSettingsController*	database_record_settings_controller	=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );

		//	Make call to instantiate local settings controller
		record->settings_controller	=	RPbdb_DatabaseRecordSettingsController_internal_copyOfSettingsControllerForInstance( database_record_settings_controller );
		
	}
	
	return record;
}
	
/*****************************
*  newFromKeyDBTDataDBT  *
*****************************/

RPbdb_Record* RPbdb_Record_internal_newFromKeyDBTDataDBT(	RPbdb_Database* parent_database,
																												DBT*	dbt_key,
																												DBT*	dbt_data	)	{
	
	RPbdb_Record*	record = RPbdb_Record_new( parent_database );
		
	free( record->key->wrapped_bdb_dbt );
	free( record->data->wrapped_bdb_dbt );

	record->key->wrapped_bdb_dbt	= dbt_key;
	record->data->wrapped_bdb_dbt	= dbt_data;

	return record;	
}

/*****************************
*  newFromKeyData  *
*****************************/

RPbdb_Record* RPbdb_Record_internal_newFromKeyData(	RPbdb_Database*	parent_database,
																									RPbdb_Key*				dbt_key,
																									RPbdb_Data*			dbt_data	)	{
	
	RPbdb_Record*	record = RPbdb_Record_internal_newWithoutDBT( parent_database );
	
	if ( dbt_key == NULL )	{
	
		dbt_key	=	RPbdb_Key_new( record );
	}
	
	if ( dbt_data == NULL )	{
		
		dbt_data	=	RPbdb_Data_new( record );
	}
	
	record->key		= dbt_key;
	dbt_key->parent_record	= record;
	record->data			= dbt_data;
	dbt_data->parent_record	= record;
  
  record->primary_key = RPbdb_Key_new( record );
	
	return record;	
}

/***************************************
*  createOrUpdateKeyTypeAndDataFooter  *
***************************************/

//	a database defines whether it uses record typing
//	if a database is changed to record typing, an expensive conversion is done (all records get a data footer)
//	so we know that when we write data for the first time we do not have a footer yet
//	and we know when we load data we can note we have a footer, 
//	so we can tell whether we have new data based on whether we have a has_footer flag set true
//	we add a footer when we write the first time, we update the footer when we write every time after that
//	if database is converted out of record typing, an expensive conversion is done (all record data footers are removed)
void RPbdb_Record_internal_createOrUpdateKeyTypeAndDataFooter( RPbdb_Record*	record,
																															BOOL					prepare_data_in_record )	{

  //  we are always handling at least a key and possibly a data
  
  //  first, our key
	CerializedData*	cerialized_key	=	CerializedData_new( & record->key->wrapped_bdb_dbt->data,
                                                        record->key->wrapped_bdb_dbt->size );	
	
  //  if our key doesn't already have a type footer, create it
	if ( ! CerializedData_internal_hasTypeFooter( cerialized_key ) )	{
		CerializedData_internal_createTypeFooter( cerialized_key );
	}

  //  set key type - we permit type changes, so we write every time
	CerializedData_setType( cerialized_key, record->key->type );
  
  //  update size in our record since we added a type footer
	record->key->wrapped_bdb_dbt->size = cerialized_key->size;
	
  //  it is possible we need to prepare our data for either a type footer or data footer
  //  a data footer adds time created/modified stamps to type specification
	if ( prepare_data_in_record )	{

    //  our data
    CerializedData*	cerialized_data	=	CerializedData_new( & record->data->wrapped_bdb_dbt->data,
                                                          record->data->wrapped_bdb_dbt->size );	

    //  if data is set for footer, prepare data footer
    if ( record->data->has_footer ) {

      if ( CerializedData_internal_hasDataFooter( cerialized_data ) )	{
        CerializedData_internal_updateDataFooter( cerialized_data );
      }
      else {
        CerializedData_internal_createDataFooter( cerialized_data );
      }
    
    }
    //  otherwise, prepare type footer
    else if ( ! CerializedData_internal_hasTypeFooter( cerialized_data ) )	{

      CerializedData_internal_createTypeFooter( cerialized_data );

    }

    //  set data type - we permit type changes, so we write every time
		CerializedData_setType( cerialized_data, record->data->type );

    //  update size in our record since we added a type or data footer
		record->data->wrapped_bdb_dbt->size = cerialized_data->size;
		
	}
	
}

