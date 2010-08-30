/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_FileVerbositySettingsController.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_FileVerbositySettingsController* RPDB_FileVerbositySettingsController_new( RPDB_FileSettingsController* file_settings_controller )	{

	RPDB_FileVerbositySettingsController*		file_verbosity_settings_controller = calloc( 1, sizeof( RPDB_FileVerbositySettingsController ) );

	file_verbosity_settings_controller->parent_file_settings_controller = file_settings_controller;

	return file_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_FileVerbositySettingsController_free(	RPDB_FileVerbositySettingsController** file_verbosity_settings_controller )	{

	free( *file_verbosity_settings_controller );
	*file_verbosity_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_FileVerbositySettingsController_parentEnvironment(	RPDB_FileVerbositySettingsController* file_verbosity_settings_controller )	{
	return file_verbosity_settings_controller->parent_file_settings_controller->parent_settings_controller->parent_environment;
}

/*************************************************************************
*  displayAdditionalInformationDuringOpenCloseRenameFileOperations  *
*************************************************************************/

//	DB_VERB_FILEOPS         	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_FileVerbositySettingsController_displayAdditionalInformationDuringOpenCloseRenameFileOperations( RPDB_FileVerbositySettingsController* file_verbosity_settings_controller )	{

	if ( file_verbosity_settings_controller->display_additional_information_during_open_close_rename_file_operations )	{
		return DB_VERB_FILEOPS;
	}

	return FALSE;	
}

	/*****************************************************************************
	*  turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOn  *
	*****************************************************************************/

	void RPDB_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOn( RPDB_FileVerbositySettingsController* file_verbosity_settings_controller )	{

		file_verbosity_settings_controller->display_additional_information_during_open_close_rename_file_operations = TRUE;
	}

	/*****************************************************************************
	*  turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOff  *
	*****************************************************************************/

	void RPDB_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOff( RPDB_FileVerbositySettingsController* file_verbosity_settings_controller )	{

		file_verbosity_settings_controller->display_additional_information_during_open_close_rename_file_operations = FALSE;
	}

/*************************************************************
*  displayAdditionalInformationDuringAllFileOperations  *
*************************************************************/

//	DB_VERB_FILEOPS_ALL     	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_FileVerbositySettingsController_displayAdditionalInformationDuringAllFileOperations( RPDB_FileVerbositySettingsController* file_verbosity_settings_controller )	{

	if ( file_verbosity_settings_controller->display_additional_information_during_all_file_operations )	{
		return DB_VERB_FILEOPS_ALL;
	}

	return FALSE;
}

	/*****************************************************************
	*  turnDisplayAdditionalInformationDuringAllFileOperationsOn  *
	*****************************************************************/

	void RPDB_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringAllFileOperationsOn( RPDB_FileVerbositySettingsController* file_verbosity_settings_controller )	{
		file_verbosity_settings_controller->display_additional_information_during_all_file_operations = TRUE;
	}

	/*****************************************************************
	*  turnDisplayAdditionalInformationDuringAllFileOperationsOff  *
	*****************************************************************/

	void RPDB_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringAllFileOperationsOff( RPDB_FileVerbositySettingsController* file_verbosity_settings_controller )	{
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
RPDB_FileVerbositySettingsController* RPDB_FileVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_FileVerbositySettingsController* file_verbosity_settings_controller )	{

	RPDB_FileVerbositySettingsController* file_verbosity_settings_controller_copy	=	RPDB_FileVerbositySettingsController_new( file_verbosity_settings_controller->parent_file_settings_controller );

	//	Instances and Pointers
	file_verbosity_settings_controller_copy->display_additional_information_during_all_file_operations	=	file_verbosity_settings_controller->display_additional_information_during_all_file_operations;
	file_verbosity_settings_controller_copy->display_additional_information_during_open_close_rename_file_operations	=	file_verbosity_settings_controller->display_additional_information_during_open_close_rename_file_operations;

	return file_verbosity_settings_controller_copy;
}

