/*
 *		Rbdb_settingsController:Rbdb_DebugSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_DatabaseVerbositySettingsController* Rbdb_DatabaseVerbositySettingsController_new( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_DatabaseVerbositySettingsController*		database_verbosity_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseVerbositySettingsController ) );

	database_verbosity_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseVerbositySettingsController_free(	Rbdb_DatabaseVerbositySettingsController** database_verbosity_settings_controller )	{

	free( *database_verbosity_settings_controller );
	*database_verbosity_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseVerbositySettingsController_parentEnvironment(	Rbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{
	return database_verbosity_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseVerbositySettingsController_parentDatabase(	Rbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{
	return database_verbosity_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************************************************
*  displayAdditionalInformationForDBRegisterFlag  *
*****************************************************/

//	DB_VERB_REGISTER        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
int Rbdb_DatabaseVerbositySettingsController_displayAdditionalInformationForDBRegisterFlag( Rbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{

	if ( database_verbosity_settings_controller->display_additional_information_for_db_register_flag )	{
		return DB_VERB_REGISTER;
	}
	
	return FALSE;
}

	/*************************************************************
	*  turnDisplayAdditionalInformationForDBRegisterFlagOn  *
	*************************************************************/

	void Rbdb_DatabaseVerbositySettingsController_turnDisplayAdditionalInformationForDBRegisterFlagOn( Rbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{

		database_verbosity_settings_controller->display_additional_information_for_db_register_flag = TRUE;
	}

	/*************************************************************
	*  turnDisplayAdditionalInformationForDBRegisterFlagOff  *
	*************************************************************/

	void Rbdb_DatabaseVerbositySettingsController_turnDisplayAdditionalInformationForDBRegisterFlagOff( Rbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{

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
Rbdb_DatabaseVerbositySettingsController* Rbdb_DatabaseVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller )	{

	Rbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller_copy	=	Rbdb_DatabaseVerbositySettingsController_new( database_verbosity_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_verbosity_settings_controller_copy->display_additional_information_for_db_register_flag	=	database_verbosity_settings_controller->display_additional_information_for_db_register_flag;

	return database_verbosity_settings_controller_copy;
}

