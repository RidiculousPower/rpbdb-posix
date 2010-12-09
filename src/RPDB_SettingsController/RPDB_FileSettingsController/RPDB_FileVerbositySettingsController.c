/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_FileVerbositySettingsController.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_FileVerbositySettingsController* Rbdb_FileVerbositySettingsController_new( Rbdb_FileSettingsController* file_settings_controller )	{

	Rbdb_FileVerbositySettingsController*		file_verbosity_settings_controller = calloc( 1, sizeof( Rbdb_FileVerbositySettingsController ) );

	file_verbosity_settings_controller->parent_file_settings_controller = file_settings_controller;

	return file_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_FileVerbositySettingsController_free(	Rbdb_FileVerbositySettingsController** file_verbosity_settings_controller )	{

	free( *file_verbosity_settings_controller );
	*file_verbosity_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_FileVerbositySettingsController_parentEnvironment(	Rbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{
	return file_verbosity_settings_controller->parent_file_settings_controller->parent_settings_controller->parent_environment;
}

/*************************************************************************
*  displayAdditionalInformationDuringOpenCloseRenameFileOperations  *
*************************************************************************/

//	DB_VERB_FILEOPS         	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_FileVerbositySettingsController_displayAdditionalInformationDuringOpenCloseRenameFileOperations( Rbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{

	if ( file_verbosity_settings_controller->display_additional_information_during_open_close_rename_file_operations )	{
		return DB_VERB_FILEOPS;
	}

	return FALSE;	
}

	/*****************************************************************************
	*  turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOn  *
	*****************************************************************************/

	void Rbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOn( Rbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{

		file_verbosity_settings_controller->display_additional_information_during_open_close_rename_file_operations = TRUE;
	}

	/*****************************************************************************
	*  turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOff  *
	*****************************************************************************/

	void Rbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOff( Rbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{

		file_verbosity_settings_controller->display_additional_information_during_open_close_rename_file_operations = FALSE;
	}

/*************************************************************
*  displayAdditionalInformationDuringAllFileOperations  *
*************************************************************/

//	DB_VERB_FILEOPS_ALL     	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_FileVerbositySettingsController_displayAdditionalInformationDuringAllFileOperations( Rbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{

	if ( file_verbosity_settings_controller->display_additional_information_during_all_file_operations )	{
		return DB_VERB_FILEOPS_ALL;
	}

	return FALSE;
}

	/*****************************************************************
	*  turnDisplayAdditionalInformationDuringAllFileOperationsOn  *
	*****************************************************************/

	void Rbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringAllFileOperationsOn( Rbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{
		file_verbosity_settings_controller->display_additional_information_during_all_file_operations = TRUE;
	}

	/*****************************************************************
	*  turnDisplayAdditionalInformationDuringAllFileOperationsOff  *
	*****************************************************************/

	void Rbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringAllFileOperationsOff( Rbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{
		file_verbosity_settings_controller->display_additional_information_during_all_file_operations = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_FileVerbositySettingsController* Rbdb_FileVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{

	Rbdb_FileVerbositySettingsController* file_verbosity_settings_controller_copy	=	Rbdb_FileVerbositySettingsController_new( file_verbosity_settings_controller->parent_file_settings_controller );

	//	Instances and Pointers
	file_verbosity_settings_controller_copy->display_additional_information_during_all_file_operations	=	file_verbosity_settings_controller->display_additional_information_during_all_file_operations;
	file_verbosity_settings_controller_copy->display_additional_information_during_open_close_rename_file_operations	=	file_verbosity_settings_controller->display_additional_information_during_open_close_rename_file_operations;

	return file_verbosity_settings_controller_copy;
}

