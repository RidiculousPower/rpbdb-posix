/*
 *		RPDB::LockController::Lock
 *
 *		Reference - http://www.oracle.com/technology/documentation/berkeley-db/db/ref/lock/am_conv.html
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_Lock.h"
#include "RPDB_Lock_internal.h"

#include "RPDB_LockController.h"

#include "RPDB_Environment.h"

#include "RPDB_Record.h"

#include "RPDB_SettingsController.h"
#include "RPDB_LockSettingsController.h"
#include "RPDB_LockSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_Lock* RPDB_Lock_new( RPDB_LockController* parent_lock_controller )	{

	RPDB_Lock*		lock = calloc( 1, sizeof( RPDB_Lock ) );

	lock->parent_lock_controller = parent_lock_controller;

	//	Make call to instantiate local settings controller
	lock->settings_controller	=	RPDB_LockSettingsController_internal_copyOfSettingsControllerForInstance( RPDB_SettingsController_lockSettingsController( RPDB_Environment_settingsController( parent_lock_controller->parent_environment )) );
	
	return lock;

}

/***************************
*  free  *
***************************/
void RPDB_Lock_free(	RPDB_Lock** lock )	{
	if ( ( *lock )->settings_controller != NULL )	{
		RPDB_LockSettingsController_free( & ( ( *lock )->settings_controller ) );
	}

	free( *lock );
	*lock	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_LockSettingsController* RPDB_Lock_settingsController(	RPDB_Lock* lock )	{
	return lock->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_Lock_parentEnvironment(	RPDB_Lock* lock )	{
	return lock->parent_lock_controller->parent_environment;
}

/*************
*  lock  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_get.html
RPDB_Lock* RPDB_Lock_lock(	RPDB_Lock*		lock, 
								RPDB_Record*	record )	{

	RPDB_Environment*		environment	=	lock->parent_lock_controller->parent_environment;
								
	environment->wrapped_bdb_environment->lock_get(	environment->wrapped_bdb_environment,
							RPDB_LockController_lockerID( lock->parent_lock_controller ),
							RPDB_LockSettingsController_internal_openFlags( RPDB_SettingsController_lockSettingsController( RPDB_Environment_settingsController( environment ) ) ),
							record->data->wrapped_bdb_dbt->data,
							RPDB_Lock_internal_lockMode( lock ),
							&( lock->wrapped_bdb_lock ) );
	return lock;
}

/**************
*  unlock  *
**************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_put.html
void RPDB_Lock_unlock( RPDB_Lock* lock )	{

	DB_ENV*		environment	=	lock->parent_lock_controller->parent_environment->wrapped_bdb_environment;

	environment->lock_put(	environment,
							&( lock->wrapped_bdb_lock ) );
}

/*****************
*  isReadLock  *
*****************/

BOOL RPDB_Lock_isReadLock( RPDB_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_READ )	{
		return TRUE;
	}
	return FALSE;
}

/*********************
*  setToReadLock  *
*********************/

void RPDB_Lock_setToReadLock( RPDB_Lock* lock )	{
	
	lock->mode	= DB_LOCK_READ;
}

/*********************
*  isWriteLock  *
*********************/

BOOL RPDB_Lock_isWriteLock( RPDB_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_WRITE )	{
		return TRUE;
	}
	return FALSE;
}

/*********************
*  setToWriteLock  *
*********************/

void RPDB_Lock_setToWriteLock( RPDB_Lock* lock )	{
	
	lock->mode	= DB_LOCK_WRITE;
}

/*****************************
*  isIntentToWriteLock  *
*****************************/

BOOL RPDB_Lock_isIntentToWriteLock( RPDB_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_IWRITE )	{
		return TRUE;
	}
	return FALSE;
}

/*****************************
*  setToIntentToWriteLock  *
*****************************/

void RPDB_Lock_setToIntentToWriteLock( RPDB_Lock* lock )	{
	
	lock->mode	= DB_LOCK_IWRITE;
}

/*************************
*  isIntentToReadLock  *
*************************/

BOOL RPDB_Lock_isIntentToReadLock( RPDB_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_IREAD )	{
		return TRUE;
	}
	return FALSE;
}

/*****************************
*  setToIntentToReadLock  *
*****************************/

void RPDB_Lock_setToIntentToReadLock( RPDB_Lock* lock )	{
	
	lock->mode	= DB_LOCK_IREAD;
}

/*********************************
*  isIntentToReadAndWriteLock  *
*********************************/

BOOL RPDB_Lock_isIntentToReadAndWriteLock( RPDB_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_IWR )	{
		return TRUE;
	}
	return FALSE;
}

/*************************************
*  setToIntentToReadAndWriteLock  *
*************************************/

void RPDB_Lock_setToIntentToReadAndWriteLock( RPDB_Lock* lock )	{
	
	lock->mode	= DB_LOCK_IWR;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************************
*  lockMode  *
*****************************/

int RPDB_Lock_internal_lockMode( RPDB_Lock* lock )	{

	return lock->mode;
}
