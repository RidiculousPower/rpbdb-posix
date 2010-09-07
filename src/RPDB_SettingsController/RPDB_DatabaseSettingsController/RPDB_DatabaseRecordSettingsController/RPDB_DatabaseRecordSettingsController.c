/*
 *		RPDB_settingsController:RPDB_DatabaseRecordSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseRecordSettingsController.h"
	#include "RPDB_DatabaseRecordSettingsController_internal.h"

	#include "RPDB_DBT.h"

	#include "RPDB_SettingsController.h"
	#include "RPDB_MemoryPoolSettingsController.h"
	#include "RPDB_DatabaseRecordSettingsController.h"
	#include "RPDB_DatabaseSettingsController.h"
	
	#include "RPDB_Environment.h"

	#include "RPDB_DatabaseRecordReadWriteSettingsController.h"
	#include "RPDB_DatabaseRecordVariableLengthSettingsController.h"
	#include "RPDB_DatabaseRecordFixedLengthSettingsController.h"

	#include "RPDB_DatabaseRecordReadWriteSettingsController_internal.h"
	#include "RPDB_DatabaseRecordVariableLengthSettingsController_internal.h"
	#include "RPDB_DatabaseRecordFixedLengthSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_DatabaseRecordSettingsController* RPDB_DatabaseRecordSettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseRecordSettingsController*	database_record_settings_controller = calloc( 1, sizeof( RPDB_DatabaseRecordSettingsController ) );

	database_record_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_record_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseRecordSettingsController_free(	RPDB_DatabaseRecordSettingsController** database_record_settings_controller )	{

	if ( ( *database_record_settings_controller )->record_variable_length_settings_controller != NULL )	{
		RPDB_DatabaseRecordVariableLengthSettingsController_free( & ( ( *database_record_settings_controller )->record_variable_length_settings_controller ) );
	}
	if ( ( *database_record_settings_controller )->record_fixed_length_settings_controller != NULL )	{
		RPDB_DatabaseRecordFixedLengthSettingsController_free( & ( ( *database_record_settings_controller )->record_fixed_length_settings_controller ) );
	}
	if ( ( *database_record_settings_controller )->record_read_write_settings_controller != NULL )	{
		RPDB_DatabaseRecordReadWriteSettingsController_free( & ( ( *database_record_settings_controller )->record_read_write_settings_controller ) );
	}

	free( *database_record_settings_controller );
	*database_record_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseRecordSettingsController_parentEnvironment(	RPDB_DatabaseRecordSettingsController* database_record_settings_controller )	{
	return database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseRecordSettingsController_parentDatabase(	RPDB_DatabaseRecordSettingsController* database_record_settings_controller )	{
	return database_record_settings_controller->parent_database_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/*****************************
*  fixedRecordController  *
*****************************/

RPDB_DatabaseRecordFixedLengthSettingsController* RPDB_DatabaseRecordSettingsController_fixedLengthSettingsController( RPDB_DatabaseRecordSettingsController*		database_record_settings_controller )	{

	if ( database_record_settings_controller->record_fixed_length_settings_controller == NULL )	{
		database_record_settings_controller->record_fixed_length_settings_controller = RPDB_DatabaseRecordFixedLengthSettingsController_new( database_record_settings_controller );
	}

	return database_record_settings_controller->record_fixed_length_settings_controller;
}

/*****************************
*  variableRecordController  *
*****************************/

RPDB_DatabaseRecordVariableLengthSettingsController* RPDB_DatabaseRecordSettingsController_variableLengthSettingsController( RPDB_DatabaseRecordSettingsController*		database_record_settings_controller )	{

	if ( database_record_settings_controller->record_variable_length_settings_controller == NULL )	{
		database_record_settings_controller->record_variable_length_settings_controller = RPDB_DatabaseRecordVariableLengthSettingsController_new( database_record_settings_controller );
	}

	return database_record_settings_controller->record_variable_length_settings_controller;
}

/*************************************
*  readWriteSettingsController  *
*************************************/

RPDB_DatabaseRecordReadWriteSettingsController*		RPDB_DatabaseRecordSettingsController_readWriteSettingsController( RPDB_DatabaseRecordSettingsController*		database_record_settings_controller )	{

	if ( database_record_settings_controller->record_read_write_settings_controller == NULL )	{
		database_record_settings_controller->record_read_write_settings_controller = RPDB_DatabaseRecordReadWriteSettingsController_new( database_record_settings_controller );
	}

	return database_record_settings_controller->record_read_write_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseRecordSettingsController* RPDB_DatabaseRecordSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseRecordSettingsController* database_record_settings_controller )	{

	RPDB_DatabaseRecordSettingsController* database_record_settings_controller_copy	=	RPDB_DatabaseRecordSettingsController_new( database_record_settings_controller->parent_database_settings_controller );

	if ( database_record_settings_controller->record_fixed_length_settings_controller != NULL )	{
		database_record_settings_controller->record_fixed_length_settings_controller									=	RPDB_DatabaseRecordFixedLengthSettingsController_internal_copyOfSettingsControllerForInstance( database_record_settings_controller->record_fixed_length_settings_controller );
		database_record_settings_controller->record_fixed_length_settings_controller->parent_database_record_settings_controller	=	database_record_settings_controller_copy;
	}
	if ( database_record_settings_controller->record_read_write_settings_controller != NULL )	{
		database_record_settings_controller->record_read_write_settings_controller									=	RPDB_DatabaseRecordReadWriteSettingsController_internal_copyOfSettingsControllerForInstance( database_record_settings_controller->record_read_write_settings_controller );
		database_record_settings_controller->record_read_write_settings_controller->parent_database_record_settings_controller	=	database_record_settings_controller_copy;
	}
	if ( database_record_settings_controller->record_variable_length_settings_controller != NULL )	{
		database_record_settings_controller->record_variable_length_settings_controller								=	RPDB_DatabaseRecordVariableLengthSettingsController_internal_copyOfSettingsControllerForInstance( database_record_settings_controller->record_variable_length_settings_controller );
		database_record_settings_controller->record_variable_length_settings_controller->parent_database_record_settings_controller	=	database_record_settings_controller_copy;
	}

	return database_record_settings_controller_copy;
}

