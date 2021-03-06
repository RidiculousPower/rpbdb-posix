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

#include "DebugVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_DebugVerbositySettingsController* RPbdb_DebugVerbositySettingsController_new( RPbdb_DebugSettingsController* debug_settings_controller )	{

	RPbdb_DebugVerbositySettingsController*		debug_verbosity_settings_controller = calloc( 1, sizeof( RPbdb_DebugVerbositySettingsController ) );

	debug_verbosity_settings_controller->parent_debug_settings_controller = debug_settings_controller;

	return debug_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DebugVerbositySettingsController_free(	RPbdb_DebugVerbositySettingsController** debug_verbosity_settings_controller )	{

	free( *debug_verbosity_settings_controller );
	*debug_verbosity_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DebugVerbositySettingsController_parentEnvironment(	RPbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{
	return debug_verbosity_settings_controller->parent_debug_settings_controller->parent_settings_controller->parent_environment;
}

/*************************************************
*  displayAdditionalInformationDuringRecovery  *
*************************************************/

//	DB_VERB_RECOVERY        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_DebugVerbositySettingsController_displayAdditionalInformationDuringRecovery( RPbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{

	if ( debug_verbosity_settings_controller->display_additional_information_during_recovery )	{
		return DB_VERB_RECOVERY;
	}

	return FALSE;	
}

	/*********************************************************
	*  turnDisplayAdditionalInformationDuringRecoveryOn  *
	*********************************************************/

	void RPbdb_DebugVerbositySettingsController_turnDisplayAdditionalInformationDuringRecoveryOn( RPbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{
		debug_verbosity_settings_controller->display_additional_information_during_recovery = TRUE;
	}

	/*********************************************************
	*  turnDisplayAdditionalInformationDuringRecoveryOff  *
	*********************************************************/

	void RPbdb_DebugVerbositySettingsController_turnDisplayAdditionalInformationDuringRecoveryOff( RPbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{
		debug_verbosity_settings_controller->display_additional_information_during_recovery = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DebugVerbositySettingsController* RPbdb_DebugVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{

	RPbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller_copy	=	RPbdb_DebugVerbositySettingsController_new( debug_verbosity_settings_controller->parent_debug_settings_controller );

	//	Instances and Pointers
	debug_verbosity_settings_controller_copy->display_additional_information_during_recovery	=	debug_verbosity_settings_controller->display_additional_information_during_recovery;

	return debug_verbosity_settings_controller_copy;
}

