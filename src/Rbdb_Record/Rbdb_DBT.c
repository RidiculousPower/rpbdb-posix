/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record::RBDB_DBT
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DBT.h"
#include "Rbdb_DBT_internal.h"

#include "Rbdb_Record.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Database.h"

#include "Rbdb_SettingsController.h"
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

Rbdb_DBT* Rbdb_DBT_new( Rbdb_Record* parent_record )	{
	
	Rbdb_DBT*	dbt	=	calloc( 1, sizeof( Rbdb_DBT ) );
	
	//	Make call to instantiate local settings controller (assuming we have a parent record to copy settings from)
	//	If we don't have a parent record, settings_controller will be intantiated upon call with default settings
	if ( parent_record != NULL )	{
		
		dbt->parent_record = parent_record;
		
		dbt->settings_controller	= Rbdb_Record_settingsController( parent_record );
	}
	
	dbt->wrapped_bdb_dbt = calloc( 1, sizeof( DBT ) );
	
	dbt->size									= & ( dbt->wrapped_bdb_dbt->size );
	dbt->buffer_size					= & ( dbt->wrapped_bdb_dbt->ulen );
	dbt->partial_data_size		= & ( dbt->wrapped_bdb_dbt->dlen );
	dbt->partial_data_offset	= & ( dbt->wrapped_bdb_dbt->doff );
	dbt->raw_data							= & ( dbt->wrapped_bdb_dbt->data );	
	
	return dbt;
}

/***************************
*  free  *
***************************/
void Rbdb_DBT_free(	Rbdb_DBT** dbt )	{
	
	free( *dbt );
	*dbt	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_DatabaseRecordSettingsController* Rbdb_DBT_settingsController(	Rbdb_DBT* dbt )	{
	return dbt->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DBT_parentEnvironment(	Rbdb_DBT* dbt )	{
	return dbt->parent_record->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DBT_parentDatabase(	Rbdb_DBT* dbt )	{
	return dbt->parent_record->parent_database;
}

/***************************************
*  parentRecord  *
***************************************/
Rbdb_Record* Rbdb_DBT_parentRecord(	Rbdb_DBT* dbt )	{
	return dbt->parent_record;
}

/*******************************************************************************************************************************************************************************************
																		Data Accessors
*******************************************************************************************************************************************************************************************/

/*************
*  data  *
*************/

void* Rbdb_DBT_data( Rbdb_DBT* dbt )	{

	return dbt->wrapped_bdb_dbt->data;
}

/*****************
*  setData  *
*****************/

//	Set data to point to a byte string
void Rbdb_DBT_setData(	Rbdb_DBT*	dbt, 
												void*		data_raw,
												uint32_t	data_size )	{

	dbt->wrapped_bdb_dbt->data = data_raw;
	dbt->wrapped_bdb_dbt->size = data_size;
}

/*************
*  size  *
*************/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(Rbdb_DatabaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t Rbdb_DBT_size( Rbdb_DBT* dbt )	{

	return ( dbt->wrapped_bdb_dbt != NULL ? dbt->wrapped_bdb_dbt->size : 0 );
}	

/**********************
*  dataType  *
**********************/

Rbdb_DatabaseRecordStorageType Rbdb_DBT_type( Rbdb_DBT* dbt )	{
		
	Rbdb_Database*																		parent_database																	=	dbt->parent_record->parent_database;
	Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_Database_settingsController( parent_database );
	Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );

	Rbdb_DatabaseRecordStorageType	type	=	RbdbType_Raw;
	
	if ( Rbdb_DatabaseRecordReadWriteSettingsController_recordTyping( database_record_read_write_settings_controller ) )	{

		type	=	dbt->type;

	}
	else {
		
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( parent_database->parent_database_controller->parent_environment ),
																			-1,
																			"Rbdb_DBT_type",
																			"Cannot return type unless database has record typing enabled." );
	}
		
	return type;
}

/**********************
*  setDataType  *
**********************/

void Rbdb_DBT_setType(	Rbdb_DBT*												dbt,
												Rbdb_DatabaseRecordStorageType	type)	{
		
	Rbdb_Database*																		parent_database																	=	dbt->parent_record->parent_database;
	Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_Database_settingsController( parent_database );
	Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );

	if ( Rbdb_DatabaseRecordReadWriteSettingsController_recordTyping( database_record_read_write_settings_controller ) )	{

		dbt->type	=	type;

	}
	else {
		
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( parent_database->parent_database_controller->parent_environment ),
																			-1,
																			"Rbdb_DBT_setType",
																			"Cannot set type unless database has record typing enabled." );
	}

}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/******************
*  newFromBDBDBT  *
******************/

Rbdb_DBT* Rbdb_DBT_internal_newFromBDBDBT(	Rbdb_Record*	parent_record, 
																						DBT*					bdb_dbt )	{
	
	Rbdb_DBT*	dbt	=	Rbdb_DBT_new( parent_record );
	
	//	Free our existing DBT
	free( dbt->wrapped_bdb_dbt );
	
	dbt->wrapped_bdb_dbt = bdb_dbt;
	
	return dbt;
}

/************************
*  verifyKeyDataTyping  *
************************/

void Rbdb_DBT_internal_verifyKeyDataTyping(	Rbdb_DBT*												dbt,
																						Rbdb_DatabaseRecordStorageType	type	)	{
	
	if ( dbt->type != type )	{

		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( dbt->parent_record->parent_database->parent_database_controller->parent_environment ),
																			-1,
																			"Rbdb_DBT_internal_verifyKeyDataTyping",
																			"Key/Data type did not match required type." );
		
	}

}


