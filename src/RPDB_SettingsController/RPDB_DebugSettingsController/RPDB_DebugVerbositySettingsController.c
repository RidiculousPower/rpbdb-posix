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

#include "RPDB_DebugVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DebugVerbositySettingsController* RPDB_DebugVerbositySettingsController_new( RPDB_DebugSettingsController* debug_settings_controller )	{

	RPDB_DebugVerbositySettingsController*		debug_verbosity_settings_controller = calloc( 1, sizeof( RPDB_DebugVerbositySettingsController ) );

	debug_verbosity_settings_controller->parent_debug_settings_controller = debug_settings_controller;

	return debug_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DebugVerbositySettingsController_free(	RPDB_DebugVerbositySettingsController** debug_verbosity_settings_controller )	{

	free( *debug_verbosity_settings_controller );
	*debug_verbosity_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DebugVerbositySettingsController_parentEnvironment(	RPDB_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{
	return debug_verbosity_settings_controller->parent_debug_settings_controller->parent_settings_controller->parent_environment;
}

/*************************************************
*  displayAdditionalInformationDuringRecovery  *
*************************************************/

//	DB_VERB_RECOVERY        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_DebugVerbositySettingsController_displayAdditionalInformationDuringRecovery( RPDB_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{

	if ( debug_verbosity_settings_controller->display_additional_information_during_recovery )	{
		return DB_VERB_RECOVERY;
	}

	return FALSE;	
}

	/*********************************************************
	*  turnDisplayAdditionalInformationDuringRecoveryOn  *
	*********************************************************/

	void RPDB_DebugVerbositySettingsController_turnDisplayAdditionalInformationDuringRecoveryOn( RPDB_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{
		debug_verbosity_settings_controller->display_additional_information_during_recovery = TRUE;
	}

	/*********************************************************
	*  turnDisplayAdditionalInformationDuringRecoveryOff  *
	*********************************************************/

	void RPDB_DebugVerbositySettingsController_turnDisplayAdditionalInformationDuringRecoveryOff( RPDB_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{
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
RPDB_DebugVerbositySettingsController* RPDB_DebugVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{

	RPDB_DebugVerbositySettingsController* debug_verbosity_settings_controller_copy	=	RPDB_DebugVerbositySettingsController_new( debug_verbosity_settings_controller->parent_debug_settings_controller );

	//	Instances and Pointers
	debug_verbosity_settings_controller_copy->display_additional_information_during_recovery	=	debug_verbosity_settings_controller->display_additional_information_during_recovery;

	return debug_verbosity_settings_controller_copy;
}

