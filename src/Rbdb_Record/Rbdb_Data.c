/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record::RBDB_DBT => Rbdb_Data
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

#include "Rbdb_Environment.h"

#include "Rbdb_Database.h"
#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseRecordSettingsController.h"
#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"
#include "Rbdb_DBT_internal.h"

#include "Rbdb_DBT.h"
	
#include <string.h>
#include <sys/time.h>
	
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

	//	if we have a footer and the size of the data is the size of the footer, return NULL
	void*	raw_data	=	NULL;
	
	if (		! data->has_footer
			||	Rbdb_DBT_size( (Rbdb_DBT*) data ) != sizeof( Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion ) )	)	{

		raw_data	=	Rbdb_DBT_data( (Rbdb_DBT*) data );
	}

	return raw_data;
}

/******************
*  setRawData  *
******************/

void Rbdb_Data_setRawData(	Rbdb_Data*	data,
														void*				data_raw,
														uint32_t		data_size )	{

	//	if we already have data and our data is the size of a footer, we need to copy our data and the footer into a new structure
	if ( data->has_footer )	{
		
		//	allocate new structure
		uint32_t	new_size	=	data_size
												+	sizeof( Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion ) );
		void*			new_data	=	calloc( 1, new_size );
		Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )*	footer	=	Rbdb_Data_internal_footer( data );
		
		//	copy data to new structure
		memcpy(	new_data,
						data_raw,
						data_size );
		//	copy footer
		memcpy(	new_data + data_size,
						footer,
						sizeof( Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion ) ) );
		
		//	assign new data to data
		data_raw	=	new_data;
		data_size	=	new_size;
	}

	Rbdb_DBT_setData(	(Rbdb_DBT*) data,
										data_raw,
										data_size );
}

/*********
*  type  *
*********/

Rbdb_DatabaseRecordStorageType Rbdb_Data_type( Rbdb_Data* data )	{

	Rbdb_DatabaseRecordStorageType	type	=	RbdbType_Raw;

	Rbdb_Database*																		parent_database																	=	data->parent_record->parent_database;
	Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_Database_settingsController( parent_database );
	Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	if ( Rbdb_DatabaseRecordReadWriteSettingsController_recordTyping( database_record_read_write_settings_controller ) )	{

		//	get our footer
		Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )*	footer	=	Rbdb_Data_internal_footer( data );

		type	=	footer->type;
	
	}
	else	{

		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( parent_database->parent_database_controller->parent_environment ),
																			-1,
																			"Rbdb_Data_type",
																			"Cannot return type unless database has record typing or store data typing enabled." );
		
	}

	return type;
}

/******************
*  setType  *
******************/

void Rbdb_Data_setType(	Rbdb_Data*											data,
												Rbdb_DatabaseRecordStorageType	type )	{

	Rbdb_Database*																		parent_database																	=	data->parent_record->parent_database;
	Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_Database_settingsController( parent_database );
	Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	if ( Rbdb_DatabaseRecordReadWriteSettingsController_recordTyping( database_record_read_write_settings_controller ) )	{

		//	get our footer
		Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )*	footer	=	Rbdb_Data_internal_footer( data );

		footer->type	=	type;

		data->has_type = TRUE;
		
		Rbdb_DBT_setType(	(Rbdb_DBT*) data,
											type );
	
	}
	else	{

		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( parent_database->parent_database_controller->parent_environment ),
																			-1,
																			"Rbdb_Data_setType",
																			"Cannot return type unless database has record typing or store data typing enabled." );
		
	}

}

/*************
*  size  *
*************/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(Rbdb_DatabaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t Rbdb_Data_size( Rbdb_Data* data )	{

	//	get the size
	uint32_t	size	=	Rbdb_DBT_size(	(Rbdb_DBT*) data  );
	
	//	if we have a footer, subtract the footer from the size
	Rbdb_Database*																		parent_database																	=	data->parent_record->parent_database;
	Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_Database_settingsController( parent_database );
	Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	if ( Rbdb_DatabaseRecordReadWriteSettingsController_recordTyping( database_record_read_write_settings_controller ) )	{
		size -= sizeof( Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion ) );
	}

	return size;
}	


/**********************
*  creationStamp  *
**********************/

struct timeval* Rbdb_Data_creationStamp( Rbdb_Data* data )	{
	
	Rbdb_Database*																		parent_database																	=	data->parent_record->parent_database;
	Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_Database_settingsController( parent_database );
	Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	struct timeval*	creation_stamp	=	NULL;
	
	if ( Rbdb_DatabaseRecordReadWriteSettingsController_creationStamp( database_record_read_write_settings_controller ) )	{

		Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )*	footer	=	Rbdb_Data_internal_footer( data );

		creation_stamp	=	& footer->creation_stamp;

	}
	else {
		
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( data->parent_record->parent_database->parent_database_controller->parent_environment ),
																			-1,
																			"Rbdb_Data_creationStamp",
																			"Cannot track creation time stamp unless database has creation stamp enabled." );
	}
		
	return creation_stamp;
}

/**********************
*  modificationStamp  *
**********************/

struct timeval* Rbdb_Data_modificationStamp( Rbdb_Data* data )	{
		
	Rbdb_Database*																		parent_database																	=	data->parent_record->parent_database;
	Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_Database_settingsController( parent_database );
	Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );

	struct timeval*	modification_stamp	=	NULL;
		
	if ( Rbdb_DatabaseRecordReadWriteSettingsController_modificationStamp( database_record_read_write_settings_controller ) )	{

		Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )*	footer	=	Rbdb_Data_internal_footer( data );

		modification_stamp	=	& footer->modification_stamp;

	}
	else {
		
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( data->parent_record->parent_database->parent_database_controller->parent_environment ),
																			-1,
																			"Rbdb_Data_modificationStamp",
																			"Cannot track modification time stamp unless database has modification stamp enabled." );
	}
		
	return modification_stamp;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )* Rbdb_Data_internal_footer( Rbdb_Data* data )	{

	Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )*	footer	=	NULL;
	
	int*	existing_footer_version				=	(int*)( Rbdb_Data_endOfFooter( data ) - sizeof( int ) );

	//	if our current footer is an old version, update the footer with a new footer
	if ( *existing_footer_version != Rbdb_DataFooterCurrentVersion )	{
		
		footer		=	Rbdb_Data_internal_upgradeFooter( data );
		
	}
	else {
		
		footer		=	Rbdb_Data_endOfFooter( data ) - sizeof( Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion ) );		
	}

	return footer;
}

/*********************
*  createDataFooter  *
*********************/

void Rbdb_Data_internal_createFooter( Rbdb_Data* data )	{

	//	create a new memory space that holds our data plus our footer
	int		new_size	=	data->wrapped_bdb_dbt->size + sizeof( Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion ) );
	void*	new_data	=	calloc( 1, new_size );

	//	copy data to new memory space
	memcpy(	new_data,
					data->wrapped_bdb_dbt->data,
					data->wrapped_bdb_dbt->size );
	
	//	allocate footer
	Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )	footer;
	//	note version for recovery
	footer.version	=	Rbdb_DataFooterCurrentVersion;

	//	assign footer values:
	//	we copy key and data regardless because they will get set to 0 if not used, which is RbdbType_Raw
	//	* type
	footer.type	=	data->type;
	
	//	* creation stamp
	gettimeofday(	& footer.creation_stamp, NULL );
	//	* modification stamp (should be the same, so we copy the values)
	footer.modification_stamp.tv_sec	=	footer.creation_stamp.tv_sec;
	footer.modification_stamp.tv_usec	=	footer.creation_stamp.tv_usec;
	
	//	copy footer after data in new memory space
	memcpy(	new_data + data->wrapped_bdb_dbt->size,
					& footer,
					sizeof( Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion ) ) );
	
	//	set data to new memory space and add footer size to data size
	data->wrapped_bdb_dbt->data	=	new_data;	
	data->wrapped_bdb_dbt->size	=	new_size;
		
	//	note in our DBT that we have a footer
	data->has_footer = TRUE;

}

/*********************
*  updateDataFooter  *
*********************/

void Rbdb_Data_internal_updateFooter( Rbdb_Data* data )	{

	//	get pointer to the footer in our data
	Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )*	footer	=	Rbdb_Data_internal_footer( data );

	//	get a new modification stamp
	gettimeofday(	& footer->modification_stamp, NULL );
		
}

/******************
*  upgradeFooter  *
******************/

//	return footer from a record that currently has a footer, regardless whether it has been written to database
Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )* Rbdb_Data_internal_upgradeFooter( Rbdb_Data*		data )	{

	Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )*	footer	=	NULL;
	
	int	existing_footer_version;
	//	loop until record is current version
	//	each loop is responsible for updating version by 1
	while ( ( existing_footer_version	=	*(int*)( Rbdb_Data_endOfFooter( data ) - sizeof( int ) ) ) < Rbdb_DataFooterCurrentVersion )	{
	
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
	Rbdb_DataFooterTypeForVersion( existing_footer_version )*	existing_footer	=	Rbdb_Data_endOfFooter( record ) - sizeof( Rbdb_DataFooterTypeForVersion( existing_footer_version ) );
	
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
void Rbdb_Data_internal_addDataFooterToExistingRecord( Rbdb_Data* data __attribute__ ((unused)) )	{

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

