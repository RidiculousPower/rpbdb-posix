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
 
#include "Rbdb_LockDeadlockDetectorSettingsController.h"

#include "Rbdb_LockDeadlockDetectorSettingsController.h"
#include "Rbdb_LockDeadlockDetectorVerbositySettingsController.h"
#include "Rbdb_Environment.h"

#include "Rbdb_LockDeadlockDetectorSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_LockDeadlockDetectorSettingsController* Rbdb_LockDeadlockDetectorSettingsController_new( Rbdb_LockSettingsController* lock_settings_controller )	{

	Rbdb_LockDeadlockDetectorSettingsController*		lock_deadlock_detector_settings_controller = calloc( 1, sizeof( Rbdb_LockDeadlockDetectorSettingsController ) );

	lock_deadlock_detector_settings_controller->parent_lock_settings_controller = lock_settings_controller;

	return lock_deadlock_detector_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_LockDeadlockDetectorSettingsController_free(	Rbdb_LockDeadlockDetectorSettingsController** lock_deadlock_detector_settings_controller )	{
	if ( ( *lock_deadlock_detector_settings_controller )->verbosity_settings_controller != NULL )	{
		Rbdb_LockDeadlockDetectorVerbositySettingsController_free( & ( ( *lock_deadlock_detector_settings_controller )->verbosity_settings_controller ) );
	}

	free( *lock_deadlock_detector_settings_controller );
	*lock_deadlock_detector_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_LockDeadlockDetectorSettingsController_parentEnvironment(	Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return lock_deadlock_detector_settings_controller->parent_lock_settings_controller->parent_settings_controller->parent_environment;
}

/*********************
*  isDefault  *
*********************/

BOOL Rbdb_LockDeadlockDetectorSettingsController_isDefault( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return Rbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_DEFAULT );
}

/*********************
*  setToDefault  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_detect.html
void Rbdb_LockDeadlockDetectorSettingsController_setToDefault( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	Rbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_DEFAULT );
}

/*****************************
*  rejectExpired  *
*****************************/

BOOL Rbdb_LockDeadlockDetectorSettingsController_rejectExpired( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return Rbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_EXPIRE );
}

/*************************
*  turnRejectExpiredOn  *
*************************/

void Rbdb_LockDeadlockDetectorSettingsController_setToRejectExpired( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	Rbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_EXPIRE );
}

/*****************************************
*  rejectLockerWithMostLocks  *
*****************************************/

BOOL Rbdb_LockDeadlockDetectorSettingsController_rejectLockerWithMostLocks( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return Rbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_MAXLOCKS );
}

/*************************************
*  turnRejectLockerWithMostLocksOn  *
*************************************/

void Rbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithMostLocks( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	Rbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_MAXLOCKS );
}

/*********************************************
*  rejectLockerWithMostWriteLocks  *
*********************************************/

BOOL Rbdb_LockDeadlockDetectorSettingsController_rejectLockerWithMostWriteLocks( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return Rbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_MAXWRITE );
}

/*********************************************
*  turnRejectLockerWithMostWriteLocksOn  *
*********************************************/

void Rbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithMostWriteLocks( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	Rbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_MAXWRITE );
}

/*****************************************
*  rejectLockerWithFewestLocks  *
*****************************************/

BOOL Rbdb_LockDeadlockDetectorSettingsController_rejectLockerWithFewestLocks( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return Rbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_MINLOCKS );
}

/*****************************************
*  turnRejectLockerWithFewestLocksOn  *
*****************************************/

void Rbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithFewestLocks( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	Rbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_MINLOCKS );
}

/*************************************************
*  rejectLockerWithFewestWriteLocks  *
*************************************************/

BOOL Rbdb_LockDeadlockDetectorSettingsController_rejectLockerWithFewestWriteLocks( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return Rbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_MINWRITE );
}

/*********************************************
*  turnRejectLockerWithFewestWriteLocksOn  *
*********************************************/

void Rbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithFewestWriteLocks( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	Rbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_MINWRITE );
}

/*****************************************
*  rejectLockerWithOldestLock  *
*****************************************/

BOOL Rbdb_LockDeadlockDetectorSettingsController_rejectLockerWithOldestLock( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return Rbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_OLDEST );
}

/*****************************************
*  turnRejectLockerWithOldestLockOn  *
*****************************************/

void Rbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithOldestLock( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	Rbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_OLDEST );
}

/*********************************************
*  rejectLockerWithYoungestLock  *
*********************************************/

BOOL Rbdb_LockDeadlockDetectorSettingsController_rejectLockerWithYoungestLock( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return Rbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_YOUNGEST );
}

/*****************************************
*  turnRejectLockerWithYoungestLockOn  *
*****************************************/

void Rbdb_LockDeadlockDetectorSettingsController_setToRejectLockerWithYoungestLock( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	Rbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_YOUNGEST );
}

/*****************************
*  rejectRandom  *
*****************************/

BOOL Rbdb_LockDeadlockDetectorSettingsController_rejectRandom( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	return Rbdb_LockDeadlockDetectorSettingsController_internal_isSetTo( lock_deadlock_detector_settings_controller, DB_LOCK_RANDOM );
}

/*************************
*  turnRejectRandomOn  *
*************************/

void Rbdb_LockDeadlockDetectorSettingsController_setToRejectRandom( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{
	Rbdb_LockDeadlockDetectorSettingsController_internal_setTo( lock_deadlock_detector_settings_controller, DB_LOCK_RANDOM );
}

/*************************************
*  verbositySettingsController  *
*************************************/

Rbdb_LockDeadlockDetectorVerbositySettingsController* Rbdb_LockDeadlockDetectorSettingsController_verbositySettingsController( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{

	if ( lock_deadlock_detector_settings_controller->verbosity_settings_controller == NULL )	{
	
		lock_deadlock_detector_settings_controller->verbosity_settings_controller = Rbdb_LockDeadlockDetectorVerbositySettingsController_new( lock_deadlock_detector_settings_controller );
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
void Rbdb_LockDeadlockDetectorSettingsController_internal_set( Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{

	Rbdb_Environment*			environment;

	environment = lock_deadlock_detector_settings_controller->parent_lock_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lk_detect(	environment->wrapped_bdb_environment, 
																													&( lock_deadlock_detector_settings_controller->deadlock_settings ) );
	}
}

/*****************
*  isSetTo  *
*****************/

BOOL Rbdb_LockDeadlockDetectorSettingsController_internal_isSetTo(	Rbdb_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller, 
																																		uint32_t										deadlock_settings )	{
	Rbdb_LockDeadlockDetectorSettingsController_internal_set( lock_deadlock_detector_settings_controller );

	if ( lock_deadlock_detector_settings_controller->deadlock_settings == deadlock_settings )	{
		return TRUE;
	}
	return FALSE;
}

/*************
*  setTo  *
*************/

void Rbdb_LockDeadlockDetectorSettingsController_internal_setTo(	Rbdb_LockDeadlockDetectorSettingsController*	lock_deadlock_detector_settings_controller, 
																																	uint32_t										deadlock_settings )	{

	Rbdb_Environment*		environment	= lock_deadlock_detector_settings_controller->parent_lock_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_lk_detect(	environment->wrapped_bdb_environment, 
																													deadlock_settings );
	}
	
	lock_deadlock_detector_settings_controller->deadlock_settings	=	deadlock_settings;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_LockDeadlockDetectorSettingsController* Rbdb_LockDeadlockDetectorSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller )	{

	Rbdb_LockDeadlockDetectorSettingsController* lock_deadlock_detector_settings_controller_copy	=	Rbdb_LockDeadlockDetectorSettingsController_new( lock_deadlock_detector_settings_controller->parent_lock_settings_controller );

	//	Instances and Pointers
	lock_deadlock_detector_settings_controller_copy->deadlock_settings	=	lock_deadlock_detector_settings_controller->deadlock_settings;

	return lock_deadlock_detector_settings_controller_copy;
}

