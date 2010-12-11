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

#include "RBDB_DBT.h"
#include "RBDB_DBT_internal.h"

#include "Rbdb_Record.h"

#include "Rbdb_Environment.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_DatabaseRecordSettingsController.h"
#include "Rbdb_DatabaseRecordSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RBDB_DBT* RBDB_DBT_new( Rbdb_Record* parent_record )	{
	
	RBDB_DBT*	dbt	=	calloc( 1, sizeof( RBDB_DBT ) );
	
	//	Make call to instantiate local settings controller (assuming we have a parent record to copy settings from)
	//	If we don't have a parent record, settings_controller will be intantiated upon call with default settings
	if ( parent_record != NULL )	{
		
		dbt->parent_record = parent_record;
		
		dbt->settings_controller	= Rbdb_Record_settingsController( parent_record );
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
void RBDB_DBT_free(	RBDB_DBT** dbt )	{

	if ( ( *dbt )->wrapped_bdb_dbt != NULL )	{
		free( ( *dbt )->wrapped_bdb_dbt );
	}
	
	free( *dbt );
	*dbt	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_DatabaseRecordSettingsController* RBDB_DBT_settingsController(	RBDB_DBT* dbt )	{
	return dbt->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* RBDB_DBT_parentEnvironment(	RBDB_DBT* dbt )	{
	return dbt->parent_record->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* RBDB_DBT_parentDatabase(	RBDB_DBT* dbt )	{
	return dbt->parent_record->parent_database;
}

/***************************************
*  parentRecord  *
***************************************/
Rbdb_Record* RBDB_DBT_parentRecord(	RBDB_DBT* dbt )	{
	return dbt->parent_record;
}

/*******************************************************************************************************************************************************************************************
																		Data Accessors
*******************************************************************************************************************************************************************************************/

/*************
*  data  *
*************/

void* RBDB_DBT_data( RBDB_DBT* dbt )	{

	return dbt->wrapped_bdb_dbt->data;
}

/*****************
*  setData  *
*****************/

//	Set data to point to a byte string
void RBDB_DBT_setData(	RBDB_DBT*	dbt, 
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
uint32_t RBDB_DBT_size( RBDB_DBT* dbt )	{

	return dbt->wrapped_bdb_dbt->size;
}	

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
