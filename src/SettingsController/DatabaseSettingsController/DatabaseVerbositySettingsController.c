/*
 *		RPbdb_settingsController:RPbdb_DebugSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_DatabaseVerbositySettingsController* RPbdb_DatabaseVerbositySettingsController_new( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_DatabaseVerbositySettingsController*		database_verbosity_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseVerbositySettingsController ) );

	database_verbosity_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseVerbositySettingsController_free(	RPbdb_DatabaseVerbositySettingsController** database_verbosity_settings_controller )	{

	free( *database_verbosity_settings_controller );
	*database_verbosity_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseVerbositySettingsController_parentEnvironment(	RPbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{
	return database_verbosity_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseVerbositySettingsController_parentDatabase(	RPbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{
	return database_verbosity_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************************************************
*  displayAdditionalInformationForDBRegisterFlag  *
*****************************************************/

//	DB_VERB_REGISTER        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
int RPbdb_DatabaseVerbositySettingsController_displayAdditionalInformationForDBRegisterFlag( RPbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{

	if ( database_verbosity_settings_controller->display_additional_information_for_db_register_flag )	{
		return DB_VERB_REGISTER;
	}
	
	return FALSE;
}

	/*************************************************************
	*  turnDisplayAdditionalInformationForDBRegisterFlagOn  *
	*************************************************************/

	void RPbdb_DatabaseVerbositySettingsController_turnDisplayAdditionalInformationForDBRegisterFlagOn( RPbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{

		database_verbosity_settings_controller->display_additional_information_for_db_register_flag = TRUE;
	}

	/*************************************************************
	*  turnDisplayAdditionalInformationForDBRegisterFlagOff  *
	*************************************************************/

	void RPbdb_DatabaseVerbositySettingsController_turnDisplayAdditionalInformationForDBRegisterFlagOff( RPbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{

		database_verbosity_settings_controller->display_additional_information_for_db_register_flag = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseVerbositySettingsController* RPbdb_DatabaseVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{

	RPbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller_copy	=	RPbdb_DatabaseVerbositySettingsController_new( database_verbosity_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_verbosity_settings_controller_copy->display_additional_information_for_db_register_flag	=	database_verbosity_settings_controller->display_additional_information_for_db_register_flag;

	return database_verbosity_settings_controller_copy;
}

