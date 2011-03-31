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
 
#include "LockDeadlockDetectorSettingsController.h"

#include "LockDeadlockDetectorSettingsController.h"
#include "LockDeadlockDetectorVerbositySettingsController.h"
#include "Environment.h"

#include "LockDeadlockDetectorSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_LockDeadlockDetectorSettingsController* RPbdb_LockDeadlockDetectorSettingsController_new( RPbdb_LockSettingsController* lock_settings_controller )	{

	RPbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller = calloc( 1, sizeof( RPbdb_LockDeadlockDetectorSettingsController ) );

	lock_deadlock_detector_settings_controller->parent_lock_settings_controller = lock_settings_controller;

	return lock_deadlock_detector_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_LockDeadlockDetectorSettingsController_free(	RPbdb_LockDeadlockDetectorSettingsController** lock_deadlock_detector_settings_controller )	{
	if ( ( *lock_deadlock_detector_settings_controller )->verbosity_settings_controller != NULL )	{
		RPbdb_LockDeadlockDetectorVerbositySettingsController_free( & ( ( *lock_deadlock_detector_settings_controller )->verbosity_settings_controller ) );
	}

	free( *lock_deadlock_detector_settings_controller );
	*lock_deadlock_detector_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_LockDeadlockDetectorSettingsController_parentEnvironment(	RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return lock_deadlock_detector_settings_controller->parent_lock_settings_controller->parent_settings_controller->parent_environment;
}

/*********************
*  isDefault  *
*********************/

BOOL RPbdb_LockDeadlockDetectorSettingsController_isDefault( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_DEFAULT );
}

/*********************
*  setToDefault  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_detect.html
void RPbdb_LockDeadlockDetectorSettingsController_setToDefault( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_DEFAULT );
}

/*****************************
*  rejectExpired  *
*****************************/

BOOL RPbdb_LockDeadlockDetectorSettingsController_rejectExpired( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_EXPIRE );
}

/*************************
*  turnRejectExpiredOn  *
*************************/

void RPbdb_LockDeadlockDetectorSettingsController_setToRejectExpired( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_EXPIRE );
}

/*****************************************
*  rejectLockerWithMostLocks  *
*****************************************/

BOOL RPbdb_LockDeadlockDetectorSettingsController_rejectLockerWithMostLocks( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_MAXLOCKS );
}

/*************************************
*  turnRejectLockerWithMostLocksOn  *
*************************************/

void RPbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithMostLocks( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_MAXLOCKS );
}

/*********************************************
*  rejectLockerWithMostWriteLocks  *
*********************************************/

BOOL RPbdb_LockDeadlockDetectorSettingsController_rejectLockerWithMostWriteLocks( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_MAXWRITE );
}

/*********************************************
*  turnRejectLockerWithMostWriteLocksOn  *
*********************************************/

void RPbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithMostWriteLocks( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_MAXWRITE );
}

/*****************************************
*  rejectLockerWithFewestLocks  *
*****************************************/

BOOL RPbdb_LockDeadlockDetectorSettingsController_rejectLockerWithFewestLocks( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_MINLOCKS );
}

/*****************************************
*  turnRejectLockerWithFewestLocksOn  *
*****************************************/

void RPbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithFewestLocks( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_MINLOCKS );
}

/*************************************************
*  rejectLockerWithFewestWriteLocks  *
*************************************************/

BOOL RPbdb_LockDeadlockDetectorSettingsController_rejectLockerWithFewestWriteLocks( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_MINWRITE );
}

/*********************************************
*  turnRejectLockerWithFewestWriteLocksOn  *
*********************************************/

void RPbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithFewestWriteLocks( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_MINWRITE );
}

/*****************************************
*  rejectLockerWithOldestLock  *
*****************************************/

BOOL RPbdb_LockDeadlockDetectorSettingsController_rejectLockerWithOldestLock( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_OLDEST );
}

/*****************************************
*  turnRejectLockerWithOldestLockOn  *
*****************************************/

void RPbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithOldestLock( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_OLDEST );
}

/*********************************************
*  rejectLockerWithYoungestLock  *
*********************************************/

BOOL RPbdb_LockDeadlockDetectorSettingsController_rejectLockerWithYoungestLock( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_YOUNGEST );
}

/*****************************************
*  turnRejectLockerWithYoungestLockOn  *
*****************************************/

void RPbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithYoungestLock( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_YOUNGEST );
}

/*****************************
*  rejectRandom  *
*****************************/

BOOL RPbdb_LockDeadlockDetectorSettingsController_rejectRandom( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_RANDOM );
}

/*************************
*  turnRejectRandomOn  *
*************************/

void RPbdb_LockDeadlockDetectorSettingsController_setToRejectRandom( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_RANDOM );
}

/*************************************
*  verbositySettingsController  *
*************************************/

RPbdb_LockDeadlockDetectorVerbositySettingsController* RPbdb_LockDeadlockDetectorSettingsController_verbositySettingsController( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{

	if ( lock_deadlock_detector_settings_controller->verbosity_settings_controller == NULL )	{
	
		lock_deadlock_detector_settings_controller->verbosity_settings_controller = RPbdb_LockDeadlockDetectorVerbositySettingsController_new( lock_deadlock_detector_settings_controller );
	}
	
	return lock_deadlock_detector_settings_controller->verbosity_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  set  *
*************/

//	sets lock detection by making call internally
void RPbdb_LockDeadlockDetectorSettingsController_internal_set( RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{

	RPbdb_Environment*			environment;

	environment = lock_deadlock_detector_settings_controller->parent_lock_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lk_detect(	environment->wrapped_bdb_environment, 
																													&( lock_deadlock_detector_settings_controller->deadlock_settings ) );
	}
}

/*****************
*  isSetTo  *
*****************/

BOOL RPbdb_LockDeadlockDetectorSettingsController_internal_isSetTo(	RPbdb_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller, 
																																		uint32_t										deadlock_settings )	{
	RPbdb_LockDeadlockDetectorSettingsController_internal_set( lock_deadlock_detector_settings_controller );

	if ( lock_deadlock_detector_settings_controller->deadlock_settings == deadlock_settings )	{
		return TRUE;
	}
	return FALSE;
}

/*************
*  setTo  *
*************/

void RPbdb_LockDeadlockDetectorSettingsController_internal_setTo(	RPbdb_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller, 
																																	uint32_t										deadlock_settings )	{

	RPbdb_Environment*		environment	= lock_deadlock_detector_settings_controller->parent_lock_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_lk_detect(	environment->wrapped_bdb_environment, 
																													deadlock_settings );
	}
	
	lock_deadlock_detector_settings_controller->deadlock_settings	=	deadlock_settings;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_LockDeadlockDetectorSettingsController* RPbdb_LockDeadlockDetectorSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{

	RPbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller_copy	=	RPbdb_LockDeadlockDetectorSettingsController_new( lock_deadlock_detector_settings_controller->parent_lock_settings_controller );

	//	Instances and Pointers
	lock_deadlock_detector_settings_controller_copy->deadlock_settings	=	lock_deadlock_detector_settings_controller->deadlock_settings;

	return lock_deadlock_detector_settings_controller_copy;
}

