/*
 *		Rbdb_settingsController:Rbdb_DatabaseRecordSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseRecordSettingsController.h"
	#include "Rbdb_DatabaseRecordSettingsController_internal.h"

	#include "Rbdb_DBT.h"

	#include "Rbdb_SettingsController.h"
	#include "Rbdb_MemoryPoolSettingsController.h"
	#include "Rbdb_DatabaseRecordSettingsController.h"
	#include "Rbdb_DatabaseSettingsController.h"
	
	#include "Rbdb_Environment.h"

	#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"
	#include "Rbdb_DatabaseRecordVariableLengthSettingsController.h"
	#include "Rbdb_DatabaseRecordFixedLengthSettingsController.h"

	#include "Rbdb_DatabaseRecordReadWriteSettingsController_internal.h"
	#include "Rbdb_DatabaseRecordVariableLengthSettingsController_internal.h"
	#include "Rbdb_DatabaseRecordFixedLengthSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
Rbdb_DatabaseRecordSettingsController* Rbdb_DatabaseRecordSettingsController_new( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_DatabaseRecordSettingsController*	database_record_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseRecordSettingsController ) );

	database_record_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_record_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseRecordSettingsController_free(	Rbdb_DatabaseRecordSettingsController** database_record_settings_controller )	{

	if ( ( *database_record_settings_controller )->record_variable_length_settings_controller != NULL )	{
		Rbdb_DatabaseRecordVariableLengthSettingsController_free( & ( ( *database_record_settings_controller )->record_variable_length_settings_controller ) );
	}
	if ( ( *database_record_settings_controller )->record_fixed_length_settings_controller != NULL )	{
		Rbdb_DatabaseRecordFixedLengthSettingsController_free( & ( ( *database_record_settings_controller )->record_fixed_length_settings_controller ) );
	}
	if ( ( *database_record_settings_controller )->record_read_write_settings_controller != NULL )	{
		Rbdb_DatabaseRecordReadWriteSettingsController_free( & ( ( *database_record_settings_controller )->record_read_write_settings_controller ) );
	}

	free( *database_record_settings_controller );
	*database_record_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseRecordSettingsController_parentEnvironment(	Rbdb_DatabaseRecordSettingsController* database_record_settings_controller )	{
	return database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseRecordSettingsController_parentDatabase(	Rbdb_DatabaseRecordSettingsController* database_record_settings_controller )	{
	return database_record_settings_controller->parent_database_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/*****************************
*  fixedRecordController  *
*****************************/

Rbdb_DatabaseRecordFixedLengthSettingsController* Rbdb_DatabaseRecordSettingsController_fixedLengthSettingsController( Rbdb_DatabaseRecordSettingsController*		database_record_settings_controller )	{

	if ( database_record_settings_controller->record_fixed_length_settings_controller == NULL )	{
		database_record_settings_controller->record_fixed_length_settings_controller = Rbdb_DatabaseRecordFixedLengthSettingsController_new( database_record_settings_controller );
	}

	return database_record_settings_controller->record_fixed_length_settings_controller;
}

/*****************************
*  variableRecordController  *
*****************************/

Rbdb_DatabaseRecordVariableLengthSettingsController* Rbdb_DatabaseRecordSettingsController_variableLengthSettingsController( Rbdb_DatabaseRecordSettingsController*		database_record_settings_controller )	{

	if ( database_record_settings_controller->record_variable_length_settings_controller == NULL )	{
		database_record_settings_controller->record_variable_length_settings_controller = Rbdb_DatabaseRecordVariableLengthSettingsController_new( database_record_settings_controller );
	}

	return database_record_settings_controller->record_variable_length_settings_controller;
}

/*************************************
*  readWriteSettingsController  *
*************************************/

Rbdb_DatabaseRecordReadWriteSettingsController*		Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( Rbdb_DatabaseRecordSettingsController*		database_record_settings_controller )	{

	if ( database_record_settings_controller->record_read_write_settings_controller == NULL )	{
		database_record_settings_controller->record_read_write_settings_controller = Rbdb_DatabaseRecordReadWriteSettingsController_new( database_record_settings_controller );
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
Rbdb_DatabaseRecordSettingsController* Rbdb_DatabaseRecordSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseRecordSettingsController* database_record_settings_controller )	{

	Rbdb_DatabaseRecordSettingsController* database_record_settings_controller_copy	=	Rbdb_DatabaseRecordSettingsController_new( database_record_settings_controller->parent_database_settings_controller );

	if ( database_record_settings_controller->record_fixed_length_settings_controller != NULL )	{
		database_record_settings_controller_copy->record_fixed_length_settings_controller									=	Rbdb_DatabaseRecordFixedLengthSettingsController_internal_copyOfSettingsControllerForInstance( database_record_settings_controller->record_fixed_length_settings_controller );
		database_record_settings_controller_copy->record_fixed_length_settings_controller->parent_database_record_settings_controller	=	database_record_settings_controller_copy;
	}
	if ( database_record_settings_controller->record_read_write_settings_controller != NULL )	{
		database_record_settings_controller_copy->record_read_write_settings_controller									=	Rbdb_DatabaseRecordReadWriteSettingsController_internal_copyOfSettingsControllerForInstance( database_record_settings_controller->record_read_write_settings_controller );
		database_record_settings_controller_copy->record_read_write_settings_controller->parent_database_record_settings_controller	=	database_record_settings_controller_copy;
	}
	if ( database_record_settings_controller->record_variable_length_settings_controller != NULL )	{
		database_record_settings_controller_copy->record_variable_length_settings_controller								=	Rbdb_DatabaseRecordVariableLengthSettingsController_internal_copyOfSettingsControllerForInstance( database_record_settings_controller->record_variable_length_settings_controller );
		database_record_settings_controller_copy->record_variable_length_settings_controller->parent_database_record_settings_controller	=	database_record_settings_controller_copy;
	}

	return database_record_settings_controller_copy;
}

