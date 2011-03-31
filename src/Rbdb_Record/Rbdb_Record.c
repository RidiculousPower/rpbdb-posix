/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_Record.h"
#include "Rbdb_Record_internal.h"

#include <cerialize.h>

#include "Rbdb_Database_internal.h"

#include "Rbdb_Key.h"
#include "Rbdb_Key_internal.h"
#include "Rbdb_Data.h"
#include "Rbdb_Data_internal.h"
#include "Rbdb_DBT.h"
#include "Rbdb_SecondaryKeys.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Database.h"

#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseRecordSettingsController.h"
#include "Rbdb_DatabaseRecordSettingsController_internal.h"

#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_Record* Rbdb_Record_new( Rbdb_Database* parent_database )	{

	Rbdb_Record*	record = Rbdb_Record_internal_newWithoutDBT( parent_database );

	if ( parent_database->runtime_storage_database != NULL )	{
		record->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_database->runtime_storage_database,
																																							(void*) record );
	}

	//	We have one primary key
	record->key = Rbdb_Key_new( record );

	//	We can have multiple secondary keys
	record->primary_key = Rbdb_Key_new( record );

	//	We have one object
	record->data = Rbdb_Data_new( record );

	return record;
}

/*************
*  free  *
*************/

void	Rbdb_Record_free( Rbdb_Record** record )	{

	if ( ( *record )->parent_database->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *record )->parent_database->runtime_storage_database,
																											( *record )->runtime_identifier );
	}
	Rbdb_Record_internal_freeFromRuntimeStorage( record );
}

/***************************
*  freeFromRuntimeStorage  *
***************************/

void	Rbdb_Record_internal_freeFromRuntimeStorage( Rbdb_Record** record )	{

	if ( ( *record )->key != NULL )	{
		
		//	if our primary key is the same as our retrieval key, NULLify it so we don't free it twice
		if ( ( *record )->primary_key == ( *record )->key )	{
			( *record )->primary_key = NULL;
		}
		
		Rbdb_Key_free( & ( ( *record )->key ) );
	}
	if ( ( *record )->primary_key != NULL )	{
		
		Rbdb_Key_free( & ( ( *record )->primary_key ) );
	}
	if ( ( *record )->data != NULL )	{
		
		Rbdb_Data_free( & ( ( *record )->data ) );
	}
	
	if ( ( *record )->settings_controller != NULL )	{
		Rbdb_DatabaseRecordSettingsController_free( & ( ( *record )->settings_controller ) );
	}
	
	free( *record );
	*record	=	NULL;
}

/***************************
*  settingsController  *
***************************/
 
 Rbdb_DatabaseRecordSettingsController* Rbdb_Record_settingsController(	Rbdb_Record* record )	{
	return record->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_Record_parentEnvironment(	Rbdb_Record* record )	{
	return record->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_Record_parentDatabase(	Rbdb_Record* record )	{
	return record->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Record Management Public Methods
*******************************************************************************************************************************************************************************************/

/**************
*  key  *
**************/

Rbdb_Key* Rbdb_Record_key( Rbdb_Record* record )	{

	if ( record != NULL )	{	
		return record->key;
	}
	return NULL;
}

/**************
*  setKey  *
**************/

void Rbdb_Record_setKey(	Rbdb_Record*			record,
							Rbdb_Key*				primary_key )	{

	record->key = primary_key;
}

/**************
*  rawData  *
**************/

void* Rbdb_Record_rawData( Rbdb_Record* record )	{		
	
	if ( record != NULL )	{	
		return record->data->wrapped_bdb_dbt->data;
	}
	return NULL;
}

/*****************
*  setRawData  *
*****************/

void Rbdb_Record_setRawData(	Rbdb_Record*	record,
															void*					raw_data,
															u_int32_t			raw_data_size )	{		
	
	Rbdb_Data_setRawData(	record->key,
												raw_data,
												raw_data_size );
}

/**************
*  rawKey  *
**************/

void* Rbdb_Record_rawKey( Rbdb_Record* record )	{		
	
	if ( record != NULL )	{	
		return record->key->wrapped_bdb_dbt->data;
	}
	return NULL;
}

/*****************
*  setRawKey  *
*****************/

void Rbdb_Record_setRawKey(	Rbdb_Record*	record,
								void*			raw_key,
								u_int32_t		raw_key_size )	{		
	
	Rbdb_Key_setRawData(	record->key,
												raw_key,
												raw_key_size );
}

/**************
*  object  *
**************/

Rbdb_Data* Rbdb_Record_data( Rbdb_Record* record )	{		

	if ( record != NULL )	{	
		return record->data;
	}
	return NULL;
}

/**************
*  size  *
**************/

uint32_t Rbdb_Record_keySize( Rbdb_Record* record )	{		
	
	if ( record != NULL )	{	
		return Rbdb_Key_size( record->key );
	}
	return 0;
}

/**************
*  size  *
**************/

uint32_t Rbdb_Record_dataSize( Rbdb_Record* record )	{		
	

	if ( record != NULL )	{	
		return Rbdb_Data_size( record->data );
	}
	return 0;
}

/******************
*  rawPrimaryKey  *
******************/

void* Rbdb_Record_rawPrimaryKey( Rbdb_Record* record )	{		
	
	if ( record != NULL )	{	
		return record->primary_key->wrapped_bdb_dbt->data;
	}
	return NULL;
}

/*******************
*  primaryKeySize  *
*******************/

uint32_t Rbdb_Record_primaryKeySize( Rbdb_Record* record )	{		
	
	
	if ( record != NULL )	{	
		return Rbdb_Key_size( record->primary_key );
	}
	return 0;
}


/**************
*  setObject  *
**************/

void Rbdb_Record_setData(	Rbdb_Record*			record,
													Rbdb_Data*			primary_object )	{

	record->data = primary_object;
}

/******************
*  primaryKey  *
******************/

Rbdb_Key* Rbdb_Record_primaryKey( Rbdb_Record* record )	{

	if ( record != NULL )	{	
		return record->key;
	}
	return NULL;
}

/**********************
*  retrievalKey  *
**********************/

Rbdb_Key* Rbdb_Record_retrievalKey( Rbdb_Record* record )	{
		
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

void Rbdb_Record_setExistsInDatabase(	Rbdb_Record*	record,
																			BOOL			data_status	)	{

	record->exists_in_database = data_status;
}

/**************
*  status  *
**************/

int Rbdb_Record_existsInDatabase( Rbdb_Record* record )	{
	return record->exists_in_database;
}

/******************
*  setStatus  *
******************/

void Rbdb_Record_setRequiresUpdateToDatabase(	Rbdb_Record*	record,
																							BOOL			data_status	)	{
	record->requires_update_to_database = data_status;
}

/**************
*  status  *
**************/

int Rbdb_Record_requiresUpdateToDatabase( Rbdb_Record* record )	{
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

Rbdb_Record* Rbdb_Record_internal_newWithoutDBT(	Rbdb_Database* parent_database	)	{

	Rbdb_Record*		record = calloc( 1, sizeof( Rbdb_Record ) );
		
	if ( parent_database )	{
	
		record->parent_database = parent_database;
		
		Rbdb_DatabaseSettingsController*				database_settings_controller				=	Rbdb_Database_settingsController( parent_database );
		Rbdb_DatabaseRecordSettingsController*	database_record_settings_controller	=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );

		//	Make call to instantiate local settings controller
		record->settings_controller	=	Rbdb_DatabaseRecordSettingsController_internal_copyOfSettingsControllerForInstance( database_record_settings_controller );
		
	}
	
	return record;
}
	
/*****************************
*  newFromKeyDBTDataDBT  *
*****************************/

Rbdb_Record* Rbdb_Record_internal_newFromKeyDBTDataDBT(	Rbdb_Database* parent_database,
																												DBT*	dbt_key,
																												DBT*	dbt_data	)	{
	
	Rbdb_Record*	record = Rbdb_Record_new( parent_database );
		
	free( record->key->wrapped_bdb_dbt );
	free( record->data->wrapped_bdb_dbt );

	record->key->wrapped_bdb_dbt	= dbt_key;
	record->data->wrapped_bdb_dbt	= dbt_data;

	return record;	
}

/*****************************
*  newFromKeyData  *
*****************************/

Rbdb_Record* Rbdb_Record_internal_newFromKeyData(	Rbdb_Database*	parent_database,
																									Rbdb_Key*				dbt_key,
																									Rbdb_Data*			dbt_data	)	{
	
	Rbdb_Record*	record = Rbdb_Record_internal_newWithoutDBT( parent_database );
	
	if ( dbt_key == NULL )	{
	
		dbt_key	=	Rbdb_Key_new( record );
	}
	
	if ( dbt_data == NULL )	{
		
		dbt_data	=	Rbdb_Data_new( record );
	}
	
	record->key		= dbt_key;
	dbt_key->parent_record	= record;
	record->data			= dbt_data;
	dbt_data->parent_record	= record;
  
  record->primary_key = Rbdb_Key_new( record );
	
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
void Rbdb_Record_internal_createOrUpdateKeyTypeAndDataFooter( Rbdb_Record*	record,
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

