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

#include "Rbdb_Database_internal.h"

#include "Rbdb_Key.h"
#include "Rbdb_Data.h"
#include "Rbdb_DBT.h"
#include "Rbdb_SecondaryKeys.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Database.h"

#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseRecordSettingsController.h"
#include "Rbdb_DatabaseRecordSettingsController_internal.h"

#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"

#include <sys/time.h>
	
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

/******************
*  setKeyData  *
******************/

void Rbdb_Record_setKeyFromRawKey(	Rbdb_Record*		record,
										void*				key_raw,
										uint32_t			key_size )	{

	Rbdb_DBT_setData(	(Rbdb_DBT*) record->key, 
						key_raw,
						key_size );
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
								void*			raw_data,
								u_int32_t		raw_data_size )	{		
	
	record->data->wrapped_bdb_dbt->data	=	raw_data;
	record->data->wrapped_bdb_dbt->size	=	raw_data_size;
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
		return record->key->wrapped_bdb_dbt->size;
	}
	return 0;
}

/**************
*  size  *
**************/

uint32_t Rbdb_Record_dataSize( Rbdb_Record* record )	{		
	

	if ( record != NULL )	{	
		return record->data->wrapped_bdb_dbt->size;
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
		return record->primary_key->wrapped_bdb_dbt->size;
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
*  setObjectData  *
******************/

void Rbdb_Record_setDataFromRawData(	Rbdb_Record*		record,
																			void*				data_raw,
																			uint32_t			data_size )	{

	Rbdb_DBT_setData(	(Rbdb_DBT*) record->data, 
						data_raw,
						data_size );
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

/**********************
*  creationStamp  *
**********************/

struct timeval* Rbdb_Record_creationStamp( Rbdb_Record* record )	{
	
	Rbdb_Database*																		parent_database																	=	record->parent_database;
	Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_Database_settingsController( parent_database );
	Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	struct timeval*	creation_stamp	=	NULL;
	
	if ( Rbdb_DatabaseRecordReadWriteSettingsController_creationStamp( database_record_read_write_settings_controller ) )	{

		creation_stamp	=	& record->data->creation_stamp;

	}
	else {
		
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( record->parent_database->parent_database_controller->parent_environment ),
																			-1,
																			"Rbdb_Record_creationStamp",
																			"Cannot track creation time stamp unless database has creation stamp enabled." );
	}
		
	return creation_stamp;
}

/**********************
*  modificationStamp  *
**********************/

struct timeval* Rbdb_Record_modificationStamp( Rbdb_Record* record )	{
		
	Rbdb_Database*																		parent_database																	=	record->parent_database;
	Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_Database_settingsController( parent_database );
	Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );

	struct timeval*	modification_stamp	=	NULL;
		
	if ( Rbdb_DatabaseRecordReadWriteSettingsController_modificationStamp( database_record_read_write_settings_controller ) )	{

		modification_stamp	=	& record->data->modification_stamp;

	}
	else {
		
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( record->parent_database->parent_database_controller->parent_environment ),
																			-1,
																			"Rbdb_Record_modificationStamp",
																			"Cannot track modification time stamp unless database has modification stamp enabled." );
	}
		
	return modification_stamp;
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
	
	return record;	
}

/*****************************
*  createOrUpdateDataFooter  *
*****************************/

//	a database defines whether it uses record typing
//	if a database is changed to record typing, an expensive conversion is done (all records get a data footer)
//	so we know that when we write data for the first time we do not have a footer yet
//	and we know when we load data we can note we have a footer, 
//	so we can tell whether we have new data based on whether we have a has_footer flag set true
//	we add a footer when we write the first time, we update the footer when we write every time after that
//	if database is converted out of record typing, an expensive conversion is done (all record data footers are removed)
void Rbdb_Record_internal_createOrUpdateDataFooter( Rbdb_Record* record )	{
	
	//	if we don't already have a footer, we need to create one and append it
	if ( ! record->has_footer )	{
	
		Rbdb_Record_internal_createDataFooter( record );

	}
	//	otherwise we need to update modification stamp
	else {
	
		Rbdb_Record_internal_updateDataFooter( record );
		
	}

}

/*********************
*  createDataFooter  *
*********************/

void Rbdb_Record_internal_createDataFooter( Rbdb_Record* record )	{

	//	create a new memory space that holds our data plus our footer
	int		new_size	=	record->data->wrapped_bdb_dbt->size + sizeof( Rbdb_DataFooterCurrentVersion );
	void*	new_data	=	calloc( 1, new_size );

	//	copy data to new memory space
	memcpy(	new_data,
					record->data->wrapped_bdb_dbt->data,
					record->data->wrapped_bdb_dbt->size );
	
	//	allocate footer
	Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )	footer;
	
	//	assign footer values:
	//	* key_type
	footer.key_type		=	record->key->type;
	//	* data_type
	footer.data_type	=	record->data->type;
	//	* creation stamp
	gettimeofday(	& footer.creation_stamp, NULL );
	//	* modification stamp (should be the same, so we copy the values)
	footer.modification_stamp.tv_sec	=	footer.creation_stamp.tv_sec;
	footer.modification_stamp.tv_usec	=	footer.creation_stamp.tv_usec;
	
	//	copy footer after data in new memory space
	memcpy(	new_data + record->data->wrapped_bdb_dbt->size,
					& footer,
					sizeof( Rbdb_DataFooterCurrentVersion ) );
	
	//	set data to new memory space and add footer size to data size
	record->data->wrapped_bdb_dbt->data	=	new_data;	
	record->data->wrapped_bdb_dbt->size	=	new_size;
	
	//	note in our DBT that we have a footer
	record->has_footer = TRUE;

}

/*********************
*  updateDataFooter  *
*********************/

void Rbdb_Record_internal_updateDataFooter( Rbdb_Record* record )	{

	//	get pointer to the footer in our data
	Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )*	footer	=	Rbdb_Record_internal_dataFooter( record );

	//	get a new modification stamp
	gettimeofday(	& footer->modification_stamp, NULL );
	
	//	update type in case it has changed (same cost to change as to check)
	footer->key_type	=	record->key->type;
	footer->data_type	=	record->data->type;
	
}

/***************
*  dataFooter  *
***************/

//	return footer from a record that currently has a footer, regardless whether it has been written to database
Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )* Rbdb_Record_internal_dataFooter( Rbdb_Record* record )	{

	int	existing_footer_version				=	*(int*)( Rbdb_Record_endOfFooter( record ) - sizeof( int ) );

	//	if our current footer is an old version, update the footer with a new footer
	Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )*	footer	=	NULL;
	if ( existing_footer_version != Rbdb_DataFooterCurrentVersion )	{
		
		footer		=	Rbdb_Record_internal_upgradeFooter( record );
		
	}
	else {
		
		footer		=	Rbdb_Record_endOfFooter( record ) - sizeof( Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion ) );		
	}

	return footer;
}

/******************
*  upgradeFooter  *
******************/

//	return footer from a record that currently has a footer, regardless whether it has been written to database
Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )* Rbdb_Record_internal_upgradeFooter( Rbdb_Record*		record )	{

	Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )*	footer	=	NULL;
	
	int	existing_footer_version;
	//	loop until record is current version
	//	each loop is responsible for updating version by 1
	while ( ( existing_footer_version	=	*(int*)( Rbdb_Record_endOfFooter( record ) - sizeof( int ) ) ) < Rbdb_DataFooterCurrentVersion )	{
	
		switch ( existing_footer_version )	{
			
			case Rbdb_DataFooterCurrentVersion:
				// current - nothing to do
				break;
			
		}

	}

	return footer;

	/*

	code can be adapted when upgrade is necessary - not currently functional, but also not currently needed
	current code incorrectly assumes preprocessor macros will function as needed (they don't)
	
	//	get the old footer
	Rbdb_DataFooterTypeForVersion( existing_footer_version )*	existing_footer	=	Rbdb_Record_endOfFooter( record ) - sizeof( Rbdb_DataFooterTypeForVersion( existing_footer_version ) );
	
	//	copy contents to the new footer
	footer	=	Rbdb_DataFooterCurrentVersionForOldFooter(	existing_footer,
																												existing_footer_version );
																											
	//	replace old footer with new footer:		
	//	if new footer is smaller, we can truncate
	if ( Rbdb_DataFooterCurrentVersion > sizeof( Rbdb_DataFooterTypeForVersion( existing_footer_version ) ) )	{

		//	allocate new data structure that can hold data and new footer
		int			existing_data_size				=	record->data->wrapped_bdb_dbt->size - sizeof( Rbdb_DataFooterTypeForVersion( existing_footer_version ) );
		int			new_data_and_footer_size	= existing_data_size + sizeof( Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion ) );
		void*		new_data	=	calloc( 1, new_data_and_footer_size );
		
		//	copy data
		memcpy(	new_data,
						record->data->wrapped_bdb_dbt->data,
						existing_data_size );

		//	set existing_footer to point to the new location of the footer so we can copy over it
		existing_footer	=	new_data + existing_data_size;
		
		//	and point to new data instead of old data
		record->data->wrapped_bdb_dbt->data	=	new_data;
	}
	
	//	now we have to copy our new footer over to the new data structure
	//	even if we allocated a new structure existing_footer still (now) points to the proper place
	memcpy(	existing_footer,
					footer,
					sizeof( Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion ) ) );

	//	adjust new data size
	record->data->wrapped_bdb_dbt->size -= (	sizeof( Rbdb_DataFooterTypeForVersion( existing_footer_version ) ) 
																					- sizeof( Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion ) ) );
	
	//	update version
	footer->version	=	Rbdb_DataFooterCurrentVersion;
	*/
}


/**********************************
*  addDataFooterToExistingRecord  *
**********************************/

//	add a footer to a record that currently exists in the database but does not currently have one
void Rbdb_Record_internal_addDataFooterToExistingRecord( Rbdb_Record* record __attribute__ ((unused)) )	{

	//	partial write
	//	* from end of current data
	//	* footer data
	//	* size of footer
	/*
	Rbdb_Database_writePartial(	record,
															footer_data,
															sizeof( Rbdb_DataFooter ) )

	*/
}

