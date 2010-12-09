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

#include "Rbdb_LockDeadlockDetectorVerbositySettingsController.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_LockDeadlockDetectorVerbositySettingsController* Rbdb_LockDeadlockDetectorVerbositySettingsController_new( Rbdb_LockDeadlockDetectorSettingsController* deadlock_detector_settings_controller )	{

	Rbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller = calloc( 1, sizeof( Rbdb_LockDeadlockDetectorVerbositySettingsController ) );

	lock_deadlock_detector_verbosity_settings_controller->parent_lock_deadlock_detector_settings_controller = deadlock_detector_settings_controller;

	return lock_deadlock_detector_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_LockDeadlockDetectorVerbositySettingsController_free(	Rbdb_LockDeadlockDetectorVerbositySettingsController** lock_deadlock_detector_verbosity_settings_controller )	{

	free( *lock_deadlock_detector_verbosity_settings_controller );
	*lock_deadlock_detector_verbosity_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_LockDeadlockDetectorVerbositySettingsController_parentEnvironment(	Rbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{
	return lock_deadlock_detector_verbosity_settings_controller->parent_lock_deadlock_detector_settings_controller->parent_lock_settings_controller->parent_settings_controller->parent_environment;
}

/*************************************************************
*  displayAdditionalInformationDuringDeadlockDetection  *
*************************************************************/

//	DB_VERB_DEADLOCK        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_LockDeadlockDetectorVerbositySettingsController_displayAdditionalInformationDuringDeadlockDetection( Rbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

	if ( lock_deadlock_detector_verbosity_settings_controller->display_additional_information_during_deadlock_detection )	{
		return DB_VERB_DEADLOCK;
	}
	return FALSE;
}

	/*****************************************************************
	*  turnDisplayAdditionalInformationDuringDeadlockDetectionOn  *
	*****************************************************************/

	void Rbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayAdditionalInformationDuringDeadlockDetectionOn( Rbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

		lock_deadlock_detector_verbosity_settings_controller->display_additional_information_during_deadlock_detection = TRUE;
	}

	/*****************************************************************
	*  turnDisplayAdditionalInformationDuringDeadlockDetectionOff  *
	*****************************************************************/

	void Rbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayAdditionalInformationDuringDeadlockDetectionOff( Rbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

		lock_deadlock_detector_verbosity_settings_controller->display_additional_information_during_deadlock_detection = FALSE;
	}

/*************************************************
*  displayWaitTableDuringDeadlockDetection  *
*************************************************/

//	DB_VERB_WAITSFOR			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_LockDeadlockDetectorVerbositySettingsController_displayWaitTableDuringDeadlockDetection( Rbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

	if ( lock_deadlock_detector_verbosity_settings_controller->display_wait_table_during_deadlock_detection == TRUE )	{
		return DB_VERB_WAITSFOR;
	}

	return FALSE;
}

	/*****************************************************
	*  turnDisplayWaitTableDuringDeadlockDetectionOn  *
	*****************************************************/

	void Rbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayWaitTableDuringDeadlockDetectionOn( Rbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{
		lock_deadlock_detector_verbosity_settings_controller->display_wait_table_during_deadlock_detection = TRUE;
	}

	/*****************************************************
	*  turnDisplayWaitTableDuringDeadlockDetectionOff  *
	*****************************************************/

	void Rbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayWaitTableDuringDeadlockDetectionOff( Rbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{
		lock_deadlock_detector_verbosity_settings_controller->display_wait_table_during_deadlock_detection = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_LockDeadlockDetectorVerbositySettingsController* Rbdb_LockDeadlockDetectorVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

	Rbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller_copy	=	Rbdb_LockDeadlockDetectorVerbositySettingsController_new( lock_deadlock_detector_verbosity_settings_controller->parent_lock_deadlock_detector_settings_controller );

	//	Instances and Pointers
	lock_deadlock_detector_verbosity_settings_controller_copy->display_wait_table_during_deadlock_detection	=	lock_deadlock_detector_verbosity_settings_controller->display_wait_table_during_deadlock_detection;
	lock_deadlock_detector_verbosity_settings_controller_copy->display_additional_information_during_deadlock_detection	=	lock_deadlock_detector_verbosity_settings_controller->display_additional_information_during_deadlock_detection;

	return lock_deadlock_detector_verbosity_settings_controller_copy;
}

