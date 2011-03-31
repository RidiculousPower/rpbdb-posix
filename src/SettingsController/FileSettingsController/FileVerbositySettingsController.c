/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "FileVerbositySettingsController.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_FileVerbositySettingsController* RPbdb_FileVerbositySettingsController_new( RPbdb_FileSettingsController* file_settings_controller )	{

	RPbdb_FileVerbositySettingsController*		file_verbosity_settings_controller = calloc( 1, sizeof( RPbdb_FileVerbositySettingsController ) );

	file_verbosity_settings_controller->parent_file_settings_controller = file_settings_controller;

	return file_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_FileVerbositySettingsController_free(	RPbdb_FileVerbositySettingsController** file_verbosity_settings_controller )	{

	free( *file_verbosity_settings_controller );
	*file_verbosity_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_FileVerbositySettingsController_parentEnvironment(	RPbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{
	return file_verbosity_settings_controller->parent_file_settings_controller->parent_settings_controller->parent_environment;
}

/*************************************************************************
*  displayAdditionalInformationDuringOpenCloseRenameFileOperations  *
*************************************************************************/

//	DB_VERB_FILEOPS         	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_FileVerbositySettingsController_displayAdditionalInformationDuringOpenCloseRenameFileOperations( RPbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{

	if ( file_verbosity_settings_controller->display_additional_information_during_open_close_rename_file_operations )	{
		return DB_VERB_FILEOPS;
	}

	return FALSE;	
}

	/*****************************************************************************
	*  turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOn  *
	*****************************************************************************/

	void RPbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOn( RPbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{

		file_verbosity_settings_controller->display_additional_information_during_open_close_rename_file_operations = TRUE;
	}

	/*****************************************************************************
	*  turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOff  *
	*****************************************************************************/

	void RPbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOff( RPbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{

		file_verbosity_settings_controller->display_additional_information_during_open_close_rename_file_operations = FALSE;
	}

/*************************************************************
*  displayAdditionalInformationDuringAllFileOperations  *
*************************************************************/

//	DB_VERB_FILEOPS_ALL     	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_FileVerbositySettingsController_displayAdditionalInformationDuringAllFileOperations( RPbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{

	if ( file_verbosity_settings_controller->display_additional_information_during_all_file_operations )	{
		return DB_VERB_FILEOPS_ALL;
	}

	return FALSE;
}

	/*****************************************************************
	*  turnDisplayAdditionalInformationDuringAllFileOperationsOn  *
	*****************************************************************/

	void RPbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringAllFileOperationsOn( RPbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{
		file_verbosity_settings_controller->display_additional_information_during_all_file_operations = TRUE;
	}

	/*****************************************************************
	*  turnDisplayAdditionalInformationDuringAllFileOperationsOff  *
	*****************************************************************/

	void RPbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringAllFileOperationsOff( RPbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{
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
RPbdb_FileVerbositySettingsController* RPbdb_FileVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_FileVerbositySettingsController* file_verbosity_settings_controller )	{

	RPbdb_FileVerbositySettingsController* file_verbosity_settings_controller_copy	=	RPbdb_FileVerbositySettingsController_new( file_verbosity_settings_controller->parent_file_settings_controller );

	//	Instances and Pointers
	file_verbosity_settings_controller_copy->display_additional_information_during_all_file_operations	=	file_verbosity_settings_controller->display_additional_information_during_all_file_operations;
	file_verbosity_settings_controller_copy->display_additional_information_during_open_close_rename_file_operations	=	file_verbosity_settings_controller->display_additional_information_during_open_close_rename_file_operations;

	return file_verbosity_settings_controller_copy;
}

