/*
 *		RPbdb::LockController::Lock
 *
 *		Reference - http://www.oracle.com/technology/documentation/berkeley-db/db/ref/lock/am_conv.html
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Lock.h"
#include "Lock_internal.h"

#include "Database_internal.h"

#include "LockController.h"

#include "Environment.h"

#include "Record.h"

#include "SettingsController.h"
#include "LockSettingsController.h"
#include "LockSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_Lock* RPbdb_Lock_new( RPbdb_LockController* parent_lock_controller )	{

	RPbdb_Lock*		lock = calloc( 1, sizeof( RPbdb_Lock ) );

	if ( parent_lock_controller->runtime_storage_database != NULL )	{
		lock->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_lock_controller->runtime_storage_database,
																																						(void*) lock );
	}

	lock->parent_lock_controller = parent_lock_controller;

	//	Make call to instantiate local settings controller
	lock->settings_controller	=	RPbdb_LockSettingsController_internal_copyOfSettingsControllerForInstance( RPbdb_SettingsController_lockSettingsController( RPbdb_Environment_settingsController( parent_lock_controller->parent_environment )) );
	
	return lock;

}

/***************************
*  free  *
***************************/

void RPbdb_Lock_free(	RPbdb_Lock** lock )	{

	if ( ( *lock )->parent_lock_controller->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *lock )->parent_lock_controller->runtime_storage_database,
																											( *lock )->runtime_identifier );
	}
	RPbdb_Lock_internal_freeFromRuntimeStorage( lock );
}

/***************************
*  free  *
***************************/

void RPbdb_Lock_internal_freeFromRuntimeStorage(	RPbdb_Lock** lock )	{

	if ( ( *lock )->settings_controller != NULL )	{
		RPbdb_LockSettingsController_free( & ( ( *lock )->settings_controller ) );
	}

	free( *lock );
	*lock	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_LockSettingsController* RPbdb_Lock_settingsController(	RPbdb_Lock* lock )	{
	return lock->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_Lock_parentEnvironment(	RPbdb_Lock* lock )	{
	return lock->parent_lock_controller->parent_environment;
}

/*************
*  lock  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_get.html
RPbdb_Lock* RPbdb_Lock_lock(	RPbdb_Lock*		lock, 
								RPbdb_Record*	record )	{

	RPbdb_Environment*		environment	=	lock->parent_lock_controller->parent_environment;
								
	environment->wrapped_bdb_environment->lock_get(	environment->wrapped_bdb_environment,
							RPbdb_LockController_lockerID( lock->parent_lock_controller ),
							RPbdb_LockSettingsController_internal_openFlags( RPbdb_SettingsController_lockSettingsController( RPbdb_Environment_settingsController( environment ) ) ),
							record->data->wrapped_bdb_dbt->data,
							RPbdb_Lock_internal_lockMode( lock ),
							&( lock->wrapped_bdb_lock ) );
	return lock;
}

/**************
*  unlock  *
**************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_put.html
void RPbdb_Lock_unlock( RPbdb_Lock* lock )	{

	DB_ENV*		environment	=	lock->parent_lock_controller->parent_environment->wrapped_bdb_environment;

	environment->lock_put(	environment,
							&( lock->wrapped_bdb_lock ) );
}

/*****************
*  isReadLock  *
*****************/

BOOL RPbdb_Lock_isReadLock( RPbdb_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_READ )	{
		return TRUE;
	}
	return FALSE;
}

/*********************
*  setToReadLock  *
*********************/

void RPbdb_Lock_setToReadLock( RPbdb_Lock* lock )	{
	
	lock->mode	= DB_LOCK_READ;
}

/*********************
*  isWriteLock  *
*********************/

BOOL RPbdb_Lock_isWriteLock( RPbdb_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_WRITE )	{
		return TRUE;
	}
	return FALSE;
}

/*********************
*  setToWriteLock  *
*********************/

void RPbdb_Lock_setToWriteLock( RPbdb_Lock* lock )	{
	
	lock->mode	= DB_LOCK_WRITE;
}

/*****************************
*  isIntentToWriteLock  *
*****************************/

BOOL RPbdb_Lock_isIntentToWriteLock( RPbdb_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_IWRITE )	{
		return TRUE;
	}
	return FALSE;
}

/*****************************
*  setToIntentToWriteLock  *
*****************************/

void RPbdb_Lock_setToIntentToWriteLock( RPbdb_Lock* lock )	{
	
	lock->mode	= DB_LOCK_IWRITE;
}

/*************************
*  isIntentToReadLock  *
*************************/

BOOL RPbdb_Lock_isIntentToReadLock( RPbdb_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_IREAD )	{
		return TRUE;
	}
	return FALSE;
}

/*****************************
*  setToIntentToReadLock  *
*****************************/

void RPbdb_Lock_setToIntentToReadLock( RPbdb_Lock* lock )	{
	
	lock->mode	= DB_LOCK_IREAD;
}

/*********************************
*  isIntentToReadAndWriteLock  *
*********************************/

BOOL RPbdb_Lock_isIntentToReadAndWriteLock( RPbdb_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_IWR )	{
		return TRUE;
	}
	return FALSE;
}

/*************************************
*  setToIntentToReadAndWriteLock  *
*************************************/

void RPbdb_Lock_setToIntentToReadAndWriteLock( RPbdb_Lock* lock )	{
	
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

int RPbdb_Lock_internal_lockMode( RPbdb_Lock* lock )	{

	return lock->mode;
}
