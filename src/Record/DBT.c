/*
 *		RPbdb::RPbdb_DatabaseController::RPbdb_Database::(RPbdb_DatabaseCursorController::RPbdb_DatabaseCursor::)RPbdb_Record::RPBDB_DBT
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include <cerialize.h>

#include "DBT.h"
#include "DBT_internal.h"

#include "Record.h"

#include "Environment.h"

#include "Database.h"

#include "SettingsController.h"
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

RPbdb_DBT* RPbdb_DBT_new( RPbdb_Record* parent_record )	{
	
	RPbdb_DBT*	dbt	=	calloc( 1, sizeof( RPbdb_DBT ) );
	
	//	Make call to instantiate local settings controller (assuming we have a parent record to copy settings from)
	//	If we don't have a parent record, settings_controller will be intantiated upon call with default settings
	if ( parent_record != NULL )	{
		
		dbt->parent_record = parent_record;
		
		dbt->settings_controller	= RPbdb_Record_settingsController( parent_record );
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
void RPbdb_DBT_free(	RPbdb_DBT** dbt )	{
	
	free( *dbt );
	*dbt	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_DatabaseRecordSettingsController* RPbdb_DBT_settingsController(	RPbdb_DBT* dbt )	{
	return dbt->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DBT_parentEnvironment(	RPbdb_DBT* dbt )	{
	return dbt->parent_record->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DBT_parentDatabase(	RPbdb_DBT* dbt )	{
	return dbt->parent_record->parent_database;
}

/***************************************
*  parentRecord  *
***************************************/
RPbdb_Record* RPbdb_DBT_parentRecord(	RPbdb_DBT* dbt )	{
	return dbt->parent_record;
}

/*******************************************************************************************************************************************************************************************
																		Data Accessors
*******************************************************************************************************************************************************************************************/

/*************
*  data  *
*************/

void* RPbdb_DBT_data( RPbdb_DBT* dbt )	{

	return dbt->wrapped_bdb_dbt->data;
}

/*****************
*  setData  *
*****************/

//	Set data to point to a byte string
void RPbdb_DBT_setData(	RPbdb_DBT*	dbt, 
												void*		data_raw,
												uint32_t	data_size )	{

	dbt->wrapped_bdb_dbt->data = data_raw;
	dbt->wrapped_bdb_dbt->size = data_size;
}

/*************
*  size  *
*************/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(RPbdb_DatabaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t RPbdb_DBT_size( RPbdb_DBT* dbt )	{

	return ( dbt->wrapped_bdb_dbt != NULL ? dbt->wrapped_bdb_dbt->size : 0 );
}	

/**********************
*  dataType  *
**********************/

CerializeType RPbdb_DBT_type( RPbdb_DBT* dbt )	{
		
	RPbdb_Database*																		parent_database																	=	dbt->parent_record->parent_database;
	RPbdb_DatabaseSettingsController*									database_settings_controller										=	RPbdb_Database_settingsController( parent_database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );

	CerializeType	type	=	CerializeType_Raw;
	
	if ( RPbdb_DatabaseRecordReadWriteSettingsController_recordTyping( database_record_read_write_settings_controller ) )	{

		type	=	dbt->type;

	}
	else {
		
		RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( parent_database->parent_database_controller->parent_environment ),
																			-1,
																			"DBT_type",
																			"Cannot return type unless database has record typing enabled." );
	}
		
	return type;
}

/**********************
*  setDataType  *
**********************/

void RPbdb_DBT_setType(	RPbdb_DBT*												dbt,
												CerializeType	type)	{
		
	RPbdb_Database*																		parent_database																	=	dbt->parent_record->parent_database;
	RPbdb_DatabaseSettingsController*									database_settings_controller										=	RPbdb_Database_settingsController( parent_database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );

	if ( RPbdb_DatabaseRecordReadWriteSettingsController_recordTyping( database_record_read_write_settings_controller ) )	{

		dbt->type	=	type;

	}
	else {
		
		RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( parent_database->parent_database_controller->parent_environment ),
																			-1,
																			"DBT_setType",
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

RPbdb_DBT* RPbdb_DBT_internal_newFromBDBDBT(	RPbdb_Record*	parent_record, 
																						DBT*					bdb_dbt )	{
	
	RPbdb_DBT*	dbt	=	RPbdb_DBT_new( parent_record );
	
	//	Free our existing DBT
	free( dbt->wrapped_bdb_dbt );
	
	dbt->wrapped_bdb_dbt = bdb_dbt;
	
	return dbt;
}

/************************
*  verifyKeyDataTyping  *
************************/

void RPbdb_DBT_internal_verifyKeyDataTyping(	RPbdb_DBT*												dbt,
																						CerializeType	type	)	{
	
	CerializedData*	cerialized_data	=	CerializedData_new(	& dbt->wrapped_bdb_dbt->data,
																												dbt->wrapped_bdb_dbt->size );
	
	
	if ( CerializedData_type( cerialized_data ) != type )	{

		RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( dbt->parent_record->parent_database->parent_database_controller->parent_environment ),
																			-1,
																			"DBT_internal_verifyKeyDataTyping",
																			"Key/Data type did not match required type." );
		
	}

}


