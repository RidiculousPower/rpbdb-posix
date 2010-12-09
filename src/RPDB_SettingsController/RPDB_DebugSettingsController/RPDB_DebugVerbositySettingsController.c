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

#include "Rbdb_DebugVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_DebugVerbositySettingsController* Rbdb_DebugVerbositySettingsController_new( Rbdb_DebugSettingsController* debug_settings_controller )	{

	Rbdb_DebugVerbositySettingsController*		debug_verbosity_settings_controller = calloc( 1, sizeof( Rbdb_DebugVerbositySettingsController ) );

	debug_verbosity_settings_controller->parent_debug_settings_controller = debug_settings_controller;

	return debug_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DebugVerbositySettingsController_free(	Rbdb_DebugVerbositySettingsController** debug_verbosity_settings_controller )	{

	free( *debug_verbosity_settings_controller );
	*debug_verbosity_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DebugVerbositySettingsController_parentEnvironment(	Rbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{
	return debug_verbosity_settings_controller->parent_debug_settings_controller->parent_settings_controller->parent_environment;
}

/*************************************************
*  displayAdditionalInformationDuringRecovery  *
*************************************************/

//	DB_VERB_RECOVERY        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_DebugVerbositySettingsController_displayAdditionalInformationDuringRecovery( Rbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{

	if ( debug_verbosity_settings_controller->display_additional_information_during_recovery )	{
		return DB_VERB_RECOVERY;
	}

	return FALSE;	
}

	/*********************************************************
	*  turnDisplayAdditionalInformationDuringRecoveryOn  *
	*********************************************************/

	void Rbdb_DebugVerbositySettingsController_turnDisplayAdditionalInformationDuringRecoveryOn( Rbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{
		debug_verbosity_settings_controller->display_additional_information_during_recovery = TRUE;
	}

	/*********************************************************
	*  turnDisplayAdditionalInformationDuringRecoveryOff  *
	*********************************************************/

	void Rbdb_DebugVerbositySettingsController_turnDisplayAdditionalInformationDuringRecoveryOff( Rbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{
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
Rbdb_DebugVerbositySettingsController* Rbdb_DebugVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller )	{

	Rbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller_copy	=	Rbdb_DebugVerbositySettingsController_new( debug_verbosity_settings_controller->parent_debug_settings_controller );

	//	Instances and Pointers
	debug_verbosity_settings_controller_copy->display_additional_information_during_recovery	=	debug_verbosity_settings_controller->display_additional_information_during_recovery;

	return debug_verbosity_settings_controller_copy;
}

