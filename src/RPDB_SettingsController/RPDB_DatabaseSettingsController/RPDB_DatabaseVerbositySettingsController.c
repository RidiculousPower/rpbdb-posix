/*
 *		RPDB_settingsController:RPDB_DebugSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseVerbositySettingsController* RPDB_DatabaseVerbositySettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseVerbositySettingsController*		database_verbosity_settings_controller = calloc( 1, sizeof( RPDB_DatabaseVerbositySettingsController ) );

	database_verbosity_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseVerbositySettingsController_free(	RPDB_DatabaseVerbositySettingsController** database_verbosity_settings_controller )	{

	free( *database_verbosity_settings_controller );
	*database_verbosity_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseVerbositySettingsController_parentEnvironment(	RPDB_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{
	return database_verbosity_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseVerbositySettingsController_parentDatabase(	RPDB_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{
	return database_verbosity_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************************************************
*  displayAdditionalInformationForDBRegisterFlag  *
*****************************************************/

//	DB_VERB_REGISTER        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
int RPDB_DatabaseVerbositySettingsController_displayAdditionalInformationForDBRegisterFlag( RPDB_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{

	if ( database_verbosity_settings_controller->display_additional_information_for_db_register_flag )	{
		return DB_VERB_REGISTER;
	}
	
	return FALSE;
}

	/*************************************************************
	*  turnDisplayAdditionalInformationForDBRegisterFlagOn  *
	*************************************************************/

	void RPDB_DatabaseVerbositySettingsController_turnDisplayAdditionalInformationForDBRegisterFlagOn( RPDB_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{

		database_verbosity_settings_controller->display_additional_information_for_db_register_flag = TRUE;
	}

	/*************************************************************
	*  turnDisplayAdditionalInformationForDBRegisterFlagOff  *
	*************************************************************/

	void RPDB_DatabaseVerbositySettingsController_turnDisplayAdditionalInformationForDBRegisterFlagOff( RPDB_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{

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
RPDB_DatabaseVerbositySettingsController* RPDB_DatabaseVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{

	RPDB_DatabaseVerbositySettingsController* database_verbosity_settings_controller_copy	=	RPDB_DatabaseVerbositySettingsController_new( database_verbosity_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_verbosity_settings_controller_copy->display_additional_information_for_db_register_flag	=	database_verbosity_settings_controller->display_additional_information_for_db_register_flag;

	return database_verbosity_settings_controller_copy;
}

