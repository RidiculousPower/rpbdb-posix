/*
 *		RPbdb_settingsController:RPbdb_DatabaseRecordSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseRecordSettingsController.h"
	#include "DatabaseRecordSettingsController_internal.h"

	#include "DBT.h"

	#include "SettingsController.h"
	#include "MemoryPoolSettingsController.h"
	#include "DatabaseRecordSettingsController.h"
	#include "DatabaseSettingsController.h"
	
	#include "Environment.h"

	#include "DatabaseRecordReadWriteSettingsController.h"
	#include "DatabaseRecordVariableLengthSettingsController.h"
	#include "DatabaseRecordFixedLengthSettingsController.h"

	#include "DatabaseRecordReadWriteSettingsController_internal.h"
	#include "DatabaseRecordVariableLengthSettingsController_internal.h"
	#include "DatabaseRecordFixedLengthSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPbdb_DatabaseRecordSettingsController* RPbdb_DatabaseRecordSettingsController_new( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_DatabaseRecordSettingsController*	database_record_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseRecordSettingsController ) );

	database_record_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_record_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseRecordSettingsController_free(	RPbdb_DatabaseRecordSettingsController** database_record_settings_controller )	{

	if ( ( *database_record_settings_controller )->record_variable_length_settings_controller != NULL )	{
		RPbdb_DatabaseRecordVariableLengthSettingsController_free( & ( ( *database_record_settings_controller )->record_variable_length_settings_controller ) );
	}
	if ( ( *database_record_settings_controller )->record_fixed_length_settings_controller != NULL )	{
		RPbdb_DatabaseRecordFixedLengthSettingsController_free( & ( ( *database_record_settings_controller )->record_fixed_length_settings_controller ) );
	}
	if ( ( *database_record_settings_controller )->record_read_write_settings_controller != NULL )	{
		RPbdb_DatabaseRecordReadWriteSettingsController_free( & ( ( *database_record_settings_controller )->record_read_write_settings_controller ) );
	}

	free( *database_record_settings_controller );
	*database_record_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseRecordSettingsController_parentEnvironment(	RPbdb_DatabaseRecordSettingsController* database_record_settings_controller )	{
	return database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseRecordSettingsController_parentDatabase(	RPbdb_DatabaseRecordSettingsController* database_record_settings_controller )	{
	return database_record_settings_controller->parent_database_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/*****************************
*  fixedRecordController  *
*****************************/

RPbdb_DatabaseRecordFixedLengthSettingsController* RPbdb_DatabaseRecordSettingsController_fixedLengthSettingsController( RPbdb_DatabaseRecordSettingsController*		database_record_settings_controller )	{

	if ( database_record_settings_controller->record_fixed_length_settings_controller == NULL )	{
		database_record_settings_controller->record_fixed_length_settings_controller = RPbdb_DatabaseRecordFixedLengthSettingsController_new( database_record_settings_controller );
	}

	return database_record_settings_controller->record_fixed_length_settings_controller;
}

/*****************************
*  variableRecordController  *
*****************************/

RPbdb_DatabaseRecordVariableLengthSettingsController* RPbdb_DatabaseRecordSettingsController_variableLengthSettingsController( RPbdb_DatabaseRecordSettingsController*		database_record_settings_controller )	{

	if ( database_record_settings_controller->record_variable_length_settings_controller == NULL )	{
		database_record_settings_controller->record_variable_length_settings_controller = RPbdb_DatabaseRecordVariableLengthSettingsController_new( database_record_settings_controller );
	}

	return database_record_settings_controller->record_variable_length_settings_controller;
}

/*************************************
*  readWriteSettingsController  *
*************************************/

RPbdb_DatabaseRecordReadWriteSettingsController*		RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( RPbdb_DatabaseRecordSettingsController*		database_record_settings_controller )	{

	if ( database_record_settings_controller->record_read_write_settings_controller == NULL )	{
		database_record_settings_controller->record_read_write_settings_controller = RPbdb_DatabaseRecordReadWriteSettingsController_new( database_record_settings_controller );
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
RPbdb_DatabaseRecordSettingsController* RPbdb_DatabaseRecordSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseRecordSettingsController* database_record_settings_controller )	{

	RPbdb_DatabaseRecordSettingsController* database_record_settings_controller_copy	=	RPbdb_DatabaseRecordSettingsController_new( database_record_settings_controller->parent_database_settings_controller );

	if ( database_record_settings_controller->record_fixed_length_settings_controller != NULL )	{
		database_record_settings_controller_copy->record_fixed_length_settings_controller									=	RPbdb_DatabaseRecordFixedLengthSettingsController_internal_copyOfSettingsControllerForInstance( database_record_settings_controller->record_fixed_length_settings_controller );
		database_record_settings_controller_copy->record_fixed_length_settings_controller->parent_database_record_settings_controller	=	database_record_settings_controller_copy;
	}
	if ( database_record_settings_controller->record_read_write_settings_controller != NULL )	{
		database_record_settings_controller_copy->record_read_write_settings_controller									=	RPbdb_DatabaseRecordReadWriteSettingsController_internal_copyOfSettingsControllerForInstance( database_record_settings_controller->record_read_write_settings_controller );
		database_record_settings_controller_copy->record_read_write_settings_controller->parent_database_record_settings_controller	=	database_record_settings_controller_copy;
	}
	if ( database_record_settings_controller->record_variable_length_settings_controller != NULL )	{
		database_record_settings_controller_copy->record_variable_length_settings_controller								=	RPbdb_DatabaseRecordVariableLengthSettingsController_internal_copyOfSettingsControllerForInstance( database_record_settings_controller->record_variable_length_settings_controller );
		database_record_settings_controller_copy->record_variable_length_settings_controller->parent_database_record_settings_controller	=	database_record_settings_controller_copy;
	}

	return database_record_settings_controller_copy;
}

