/*
 *		RPDB::RPDB_DatabaseController::RPDB_Database::(RPDB_DatabaseCursorController::RPDB_DatabaseCursor::)RPDB_Record::RPDB_DBT
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DBT.h"
#include "RPDB_DBT_internal.h"

#include "RPDB_Record.h"

#include "RPDB_Environment.h"

#include "RPDB_SettingsController.h"
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

RPDB_DBT* RPDB_DBT_new( RPDB_Record* parent_record )	{
	
	RPDB_DBT*	dbt	=	calloc( 1, sizeof( RPDB_DBT ) );
	
	//	Make call to instantiate local settings controller (assuming we have a parent record to copy settings from)
	//	If we don't have a parent record, settings_controller will be intantiated upon call with default settings
	if ( parent_record != NULL )	{
		
		dbt->parent_record = parent_record;
		
		dbt->settings_controller	= RPDB_Record_settingsController( parent_record );
	}
	
	dbt->wrapped_bdb_dbt = calloc( 1, sizeof( DBT ) );
	
	dbt->size					= & ( dbt->wrapped_bdb_dbt->size );
	dbt->buffer_size			= & ( dbt->wrapped_bdb_dbt->ulen );
	dbt->partial_data_size		= & ( dbt->wrapped_bdb_dbt->dlen );
	dbt->partial_data_offset	= & ( dbt->wrapped_bdb_dbt->doff );
	dbt->raw_data				= & ( dbt->wrapped_bdb_dbt->data );	
	
	return dbt;
}

/***************************
*  free  *
***************************/
void RPDB_DBT_free(	RPDB_DBT** dbt )	{

	if ( ( *dbt )->wrapped_bdb_dbt != NULL )	{
		free( ( *dbt )->wrapped_bdb_dbt );
	}
	
	free( *dbt );
	*dbt	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_DatabaseRecordSettingsController* RPDB_DBT_settingsController(	RPDB_DBT* dbt )	{
	return dbt->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DBT_parentEnvironment(	RPDB_DBT* dbt )	{
	return dbt->parent_record->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DBT_parentDatabase(	RPDB_DBT* dbt )	{
	return dbt->parent_record->parent_database;
}

/***************************************
*  parentRecord  *
***************************************/
RPDB_Record* RPDB_DBT_parentRecord(	RPDB_DBT* dbt )	{
	return dbt->parent_record;
}

/*******************************************************************************************************************************************************************************************
																		Data Accessors
*******************************************************************************************************************************************************************************************/

/*************
*  data  *
*************/

void* RPDB_DBT_data( RPDB_DBT* dbt )	{

	return dbt->wrapped_bdb_dbt->data;
}

/*****************
*  setData  *
*****************/

//	Set data to point to a byte string
void RPDB_DBT_setData(	RPDB_DBT*	dbt, 
						void*		data_raw,
						uint32_t	data_size )	{

	dbt->wrapped_bdb_dbt->data = data_raw;
	dbt->wrapped_bdb_dbt->size = data_size;
}

/*************
*  size  *
*************/

//	Note that applications can determine the length of a record by setting the ulen field 
//	(RPDB_DatabaseRecordSettingsController_dataBufferSize) to 0 and checking the return value in the size field.
uint32_t RPDB_DBT_size( RPDB_DBT* dbt )	{

	return dbt->wrapped_bdb_dbt->size;
}	

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
