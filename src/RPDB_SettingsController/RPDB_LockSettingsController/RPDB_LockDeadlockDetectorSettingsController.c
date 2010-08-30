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
 
#include "RPDB_LockDeadlockDetectorSettingsController.h"

#include "RPDB_LockDeadlockDetectorSettingsController.h"
#include "RPDB_LockDeadlockDetectorVerbositySettingsController.h"
#include "RPDB_Environment.h"

#include "RPDB_LockDeadlockDetectorSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_LockDeadlockDetectorSettingsController* RPDB_LockDeadlockDetectorSettingsController_new( RPDB_LockSettingsController* lock_settings_controller )	{

	RPDB_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller = calloc( 1, sizeof( RPDB_LockDeadlockDetectorSettingsController ) );

	lock_deadlock_detector_settings_controller->parent_lock_settings_controller = lock_settings_controller;

	return lock_deadlock_detector_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_LockDeadlockDetectorSettingsController_free(	RPDB_LockDeadlockDetectorSettingsController** lock_deadlock_detector_settings_controller )	{
	if ( ( *lock_deadlock_detector_settings_controller )->verbosity_settings_controller != NULL )	{
		RPDB_LockDeadlockDetectorVerbositySettingsController_free( & ( ( *lock_deadlock_detector_settings_controller )->verbosity_settings_controller ) );
	}

	free( *lock_deadlock_detector_settings_controller );
	*lock_deadlock_detector_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_LockDeadlockDetectorSettingsController_parentEnvironment(	RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return lock_deadlock_detector_settings_controller->parent_lock_settings_controller->parent_settings_controller->parent_environment;
}

/*********************
*  isDefault  *
*********************/

BOOL RPDB_LockDeadlockDetectorSettingsController_isDefault( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPDB_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_DEFAULT );
}

/*********************
*  setToDefault  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_detect.html
void RPDB_LockDeadlockDetectorSettingsController_setToDefault( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPDB_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_DEFAULT );
}

/*****************************
*  rejectExpired  *
*****************************/

BOOL RPDB_LockDeadlockDetectorSettingsController_rejectExpired( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPDB_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_EXPIRE );
}

/*************************
*  turnRejectExpiredOn  *
*************************/

void RPDB_LockDeadlockDetectorSettingsController_setToRejectExpired( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPDB_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_EXPIRE );
}

/*****************************************
*  rejectLockerWithMostLocks  *
*****************************************/

BOOL RPDB_LockDeadlockDetectorSettingsController_rejectLockerWithMostLocks( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPDB_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_MAXLOCKS );
}

/*************************************
*  turnRejectLockerWithMostLocksOn  *
*************************************/

void RPDB_LockDeadlockDetectorSettingsController_setToRejectLockerWithMostLocks( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPDB_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_MAXLOCKS );
}

/*********************************************
*  rejectLockerWithMostWriteLocks  *
*********************************************/

BOOL RPDB_LockDeadlockDetectorSettingsController_rejectLockerWithMostWriteLocks( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPDB_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_MAXWRITE );
}

/*********************************************
*  turnRejectLockerWithMostWriteLocksOn  *
*********************************************/

void RPDB_LockDeadlockDetectorSettingsController_setToRejectLockerWithMostWriteLocks( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPDB_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_MAXWRITE );
}

/*****************************************
*  rejectLockerWithFewestLocks  *
*****************************************/

BOOL RPDB_LockDeadlockDetectorSettingsController_rejectLockerWithFewestLocks( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPDB_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_MINLOCKS );
}

/*****************************************
*  turnRejectLockerWithFewestLocksOn  *
*****************************************/

void RPDB_LockDeadlockDetectorSettingsController_setToRejectLockerWithFewestLocks( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPDB_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_MINLOCKS );
}

/*************************************************
*  rejectLockerWithFewestWriteLocks  *
*************************************************/

BOOL RPDB_LockDeadlockDetectorSettingsController_rejectLockerWithFewestWriteLocks( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPDB_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_MINWRITE );
}

/*********************************************
*  turnRejectLockerWithFewestWriteLocksOn  *
*********************************************/

void RPDB_LockDeadlockDetectorSettingsController_setToRejectLockerWithFewestWriteLocks( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPDB_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_MINWRITE );
}

/*****************************************
*  rejectLockerWithOldestLock  *
*****************************************/

BOOL RPDB_LockDeadlockDetectorSettingsController_rejectLockerWithOldestLock( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPDB_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_OLDEST );
}

/*****************************************
*  turnRejectLockerWithOldestLockOn  *
*****************************************/

void RPDB_LockDeadlockDetectorSettingsController_setToRejectLockerWithOldestLock( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPDB_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_OLDEST );
}

/*********************************************
*  rejectLockerWithYoungestLock  *
*********************************************/

BOOL RPDB_LockDeadlockDetectorSettingsController_rejectLockerWithYoungestLock( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPDB_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_YOUNGEST );
}

/*****************************************
*  turnRejectLockerWithYoungestLockOn  *
*****************************************/

void RPDB_LockDeadlockDetectorSettingsController_setToRejectLockerWithYoungestLock( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPDB_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_YOUNGEST );
}

/*****************************
*  rejectRandom  *
*****************************/

BOOL RPDB_LockDeadlockDetectorSettingsController_rejectRandom( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return RPDB_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_RANDOM );
}

/*************************
*  turnRejectRandomOn  *
*************************/

void RPDB_LockDeadlockDetectorSettingsController_setToRejectRandom( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	RPDB_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_RANDOM );
}

/*************************************
*  verbositySettingsController  *
*************************************/

RPDB_LockDeadlockDetectorVerbositySettingsController* RPDB_LockDeadlockDetectorSettingsController_verbositySettingsController( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{

	if ( lock_deadlock_detector_settings_controller->verbosity_settings_controller == NULL )	{
	
		lock_deadlock_detector_settings_controller->verbosity_settings_controller = RPDB_LockDeadlockDetectorVerbositySettingsController_new( lock_deadlock_detector_settings_controller );
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
void RPDB_LockDeadlockDetectorSettingsController_internal_set( RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{

	RPDB_Environment*			environment;

	environment = lock_deadlock_detector_settings_controller->parent_lock_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lk_detect(	environment->wrapped_bdb_environment, 
																&( lock_deadlock_detector_settings_controller->deadlock_settings ) );
	}
}

/*****************
*  isSetTo  *
*****************/

BOOL RPDB_LockDeadlockDetectorSettingsController_internal_isSetTo(	RPDB_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller, 
																	uint32_t										deadlock_settings )	{
	RPDB_LockDeadlockDetectorSettingsController_internal_set( lock_deadlock_detector_settings_controller );

	if ( lock_deadlock_detector_settings_controller->deadlock_settings == deadlock_settings )	{
		return TRUE;
	}
	return FALSE;
}

/*************
*  setTo  *
*************/

void RPDB_LockDeadlockDetectorSettingsController_internal_setTo(	RPDB_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller, 
																	uint32_t										deadlock_settings )	{

	RPDB_Environment*		environment	= lock_deadlock_detector_settings_controller->parent_lock_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_lk_detect(	environment->wrapped_bdb_environment, 
																deadlock_settings );
	}
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_LockDeadlockDetectorSettingsController* RPDB_LockDeadlockDetectorSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{

	RPDB_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller_copy	=	RPDB_LockDeadlockDetectorSettingsController_new( lock_deadlock_detector_settings_controller->parent_lock_settings_controller );

	//	Instances and Pointers
	lock_deadlock_detector_settings_controller_copy->deadlock_settings	=	lock_deadlock_detector_settings_controller->deadlock_settings;

	return lock_deadlock_detector_settings_controller_copy;
}

