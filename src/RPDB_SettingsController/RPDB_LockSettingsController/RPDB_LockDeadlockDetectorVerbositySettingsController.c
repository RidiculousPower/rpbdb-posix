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

#include "RPDB_LockDeadlockDetectorVerbositySettingsController.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_LockDeadlockDetectorVerbositySettingsController* RPDB_LockDeadlockDetectorVerbositySettingsController_new( RPDB_LockDeadlockDetectorSettingsController* deadlock_detector_settings_controller )	{

	RPDB_LockDeadlockDetectorVerbositySettingsController*		lock_deadlock_detector_verbosity_settings_controller = calloc( 1, sizeof( RPDB_LockDeadlockDetectorVerbositySettingsController ) );

	lock_deadlock_detector_verbosity_settings_controller->parent_lock_deadlock_detector_settings_controller = deadlock_detector_settings_controller;

	return lock_deadlock_detector_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_LockDeadlockDetectorVerbositySettingsController_free(	RPDB_LockDeadlockDetectorVerbositySettingsController** lock_deadlock_detector_verbosity_settings_controller )	{

	free( *lock_deadlock_detector_verbosity_settings_controller );
	*lock_deadlock_detector_verbosity_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_LockDeadlockDetectorVerbositySettingsController_parentEnvironment(	RPDB_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{
	return lock_deadlock_detector_verbosity_settings_controller->parent_lock_deadlock_detector_settings_controller->parent_lock_settings_controller->parent_settings_controller->parent_environment;
}

/*************************************************************
*  displayAdditionalInformationDuringDeadlockDetection  *
*************************************************************/

//	DB_VERB_DEADLOCK        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_LockDeadlockDetectorVerbositySettingsController_displayAdditionalInformationDuringDeadlockDetection( RPDB_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

	if ( lock_deadlock_detector_verbosity_settings_controller->display_additional_information_during_deadlock_detection )	{
		return DB_VERB_DEADLOCK;
	}
	return FALSE;
}

	/*****************************************************************
	*  turnDisplayAdditionalInformationDuringDeadlockDetectionOn  *
	*****************************************************************/

	void RPDB_LockDeadlockDetectorVerbositySettingsController_turnDisplayAdditionalInformationDuringDeadlockDetectionOn( RPDB_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

		lock_deadlock_detector_verbosity_settings_controller->display_additional_information_during_deadlock_detection = TRUE;
	}

	/*****************************************************************
	*  turnDisplayAdditionalInformationDuringDeadlockDetectionOff  *
	*****************************************************************/

	void RPDB_LockDeadlockDetectorVerbositySettingsController_turnDisplayAdditionalInformationDuringDeadlockDetectionOff( RPDB_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

		lock_deadlock_detector_verbosity_settings_controller->display_additional_information_during_deadlock_detection = FALSE;
	}

/*************************************************
*  displayWaitTableDuringDeadlockDetection  *
*************************************************/

//	DB_VERB_WAITSFOR			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_LockDeadlockDetectorVerbositySettingsController_displayWaitTableDuringDeadlockDetection( RPDB_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

	if ( lock_deadlock_detector_verbosity_settings_controller->display_wait_table_during_deadlock_detection == TRUE )	{
		return DB_VERB_WAITSFOR;
	}

	return FALSE;
}

	/*****************************************************
	*  turnDisplayWaitTableDuringDeadlockDetectionOn  *
	*****************************************************/

	void RPDB_LockDeadlockDetectorVerbositySettingsController_turnDisplayWaitTableDuringDeadlockDetectionOn( RPDB_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{
		lock_deadlock_detector_verbosity_settings_controller->display_wait_table_during_deadlock_detection = TRUE;
	}

	/*****************************************************
	*  turnDisplayWaitTableDuringDeadlockDetectionOff  *
	*****************************************************/

	void RPDB_LockDeadlockDetectorVerbositySettingsController_turnDisplayWaitTableDuringDeadlockDetectionOff( RPDB_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{
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
RPDB_LockDeadlockDetectorVerbositySettingsController* RPDB_LockDeadlockDetectorVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller )	{

	RPDB_LockDeadlockDetectorVerbositySettingsController* lock_deadlock_detector_verbosity_settings_controller_copy	=	RPDB_LockDeadlockDetectorVerbositySettingsController_new( lock_deadlock_detector_verbosity_settings_controller->parent_lock_deadlock_detector_settings_controller );

	//	Instances and Pointers
	lock_deadlock_detector_verbosity_settings_controller_copy->display_wait_table_during_deadlock_detection	=	lock_deadlock_detector_verbosity_settings_controller->display_wait_table_during_deadlock_detection;
	lock_deadlock_detector_verbosity_settings_controller_copy->display_additional_information_during_deadlock_detection	=	lock_deadlock_detector_verbosity_settings_controller->display_additional_information_during_deadlock_detection;

	return lock_deadlock_detector_verbosity_settings_controller_copy;
}

