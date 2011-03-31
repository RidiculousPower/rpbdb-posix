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

#include "LockDeadlockDetectorVerbositySettingsController.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_LockDeadlockDetectorVerbositySettingsController* RPbdb_LockDeadlockDetectorVerbositySettingsController_new( RPbdb_LockDeadlockDetectorSettingsController* deadlock_detector_settings_controller )	{

	RPbdb_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller = calloc( 1, sizeof( RPbdb_LockDeadlockDetectorVerbositySettingsController ) );

	lock_deadlock_detector_verbosity_settings_controller->parent_lock_deadlock_detector_settings_controller = deadlock_detector_settings_controller;

	return lock_deadlock_detector_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_LockDeadlockDetectorVerbositySettingsController_free(	RPbdb_LockDeadlockDetectorVerbositySettingsController** lock_deadlock_detector_verbosity_settings_controller )	{

	free( *lock_deadlock_detector_verbosity_settings_controller );
	*lock_deadlock_detector_verbosity_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_LockDeadlockDetectorVerbositySettingsController_parentEnvironment(	RPbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{
	return lock_deadlock_detector_verbosity_settings_controller->parent_lock_deadlock_detector_settings_controller->parent_lock_settings_controller->parent_settings_controller->parent_environment;
}

/*************************************************************
*  displayAdditionalInformationDuringDeadlockDetection  *
*************************************************************/

//	DB_VERB_DEADLOCK        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_LockDeadlockDetectorVerbositySettingsController_displayAdditionalInformationDuringDeadlockDetection( RPbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

	if ( lock_deadlock_detector_verbosity_settings_controller->display_additional_information_during_deadlock_detection )	{
		return DB_VERB_DEADLOCK;
	}
	return FALSE;
}

	/*****************************************************************
	*  turnDisplayAdditionalInformationDuringDeadlockDetectionOn  *
	*****************************************************************/

	void RPbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayAdditionalInformationDuringDeadlockDetectionOn( RPbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

		lock_deadlock_detector_verbosity_settings_controller->display_additional_information_during_deadlock_detection = TRUE;
	}

	/*****************************************************************
	*  turnDisplayAdditionalInformationDuringDeadlockDetectionOff  *
	*****************************************************************/

	void RPbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayAdditionalInformationDuringDeadlockDetectionOff( RPbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

		lock_deadlock_detector_verbosity_settings_controller->display_additional_information_during_deadlock_detection = FALSE;
	}

/*************************************************
*  displayWaitTableDuringDeadlockDetection  *
*************************************************/

//	DB_VERB_WAITSFOR			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_LockDeadlockDetectorVerbositySettingsController_displayWaitTableDuringDeadlockDetection( RPbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

	if ( lock_deadlock_detector_verbosity_settings_controller->display_wait_table_during_deadlock_detection == TRUE )	{
		return DB_VERB_WAITSFOR;
	}

	return FALSE;
}

	/*****************************************************
	*  turnDisplayWaitTableDuringDeadlockDetectionOn  *
	*****************************************************/

	void RPbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayWaitTableDuringDeadlockDetectionOn( RPbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{
		lock_deadlock_detector_verbosity_settings_controller->display_wait_table_during_deadlock_detection = TRUE;
	}

	/*****************************************************
	*  turnDisplayWaitTableDuringDeadlockDetectionOff  *
	*****************************************************/

	void RPbdb_LockDeadlockDetectorVerbositySettingsController_turnDisplayWaitTableDuringDeadlockDetectionOff( RPbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{
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
RPbdb_LockDeadlockDetectorVerbositySettingsController* RPbdb_LockDeadlockDetectorVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

	RPbdb_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller_copy	=	RPbdb_LockDeadlockDetectorVerbositySettingsController_new( lock_deadlock_detector_verbosity_settings_controller->parent_lock_deadlock_detector_settings_controller );

	//	Instances and Pointers
	lock_deadlock_detector_verbosity_settings_controller_copy->display_wait_table_during_deadlock_detection	=	lock_deadlock_detector_verbosity_settings_controller->display_wait_table_during_deadlock_detection;
	lock_deadlock_detector_verbosity_settings_controller_copy->display_additional_information_during_deadlock_detection	=	lock_deadlock_detector_verbosity_settings_controller->display_additional_information_during_deadlock_detection;

	return lock_deadlock_detector_verbosity_settings_controller_copy;
}

