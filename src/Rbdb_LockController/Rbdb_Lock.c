/*
 *		Rbdb::LockController::Lock
 *
 *		Reference - http://www.oracle.com/technology/documentation/berkeley-db/db/ref/lock/am_conv.html
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_Lock.h"
#include "Rbdb_Lock_internal.h"

#include "Rbdb_Database_internal.h"

#include "Rbdb_LockController.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Record.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_LockSettingsController.h"
#include "Rbdb_LockSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_Lock* Rbdb_Lock_new( Rbdb_LockController* parent_lock_controller )	{

	Rbdb_Lock*		lock = calloc( 1, sizeof( Rbdb_Lock ) );

	if ( parent_lock_controller->runtime_storage_database != NULL )	{
		lock->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_lock_controller->runtime_storage_database,
																																						(void*) lock );
	}

	lock->parent_lock_controller = parent_lock_controller;

	//	Make call to instantiate local settings controller
	lock->settings_controller	=	Rbdb_LockSettingsController_internal_copyOfSettingsControllerForInstance( Rbdb_SettingsController_lockSettingsController( Rbdb_Environment_settingsController( parent_lock_controller->parent_environment )) );
	
	return lock;

}

/***************************
*  free  *
***************************/

void Rbdb_Lock_free(	Rbdb_Lock** lock )	{

	if ( ( *lock )->parent_lock_controller->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *lock )->parent_lock_controller->runtime_storage_database,
																											( *lock )->runtime_identifier );
	}
	Rbdb_Lock_internal_freeFromRuntimeStorage( lock );
}

/***************************
*  free  *
***************************/

void Rbdb_Lock_internal_freeFromRuntimeStorage(	Rbdb_Lock** lock )	{

	if ( ( *lock )->settings_controller != NULL )	{
		Rbdb_LockSettingsController_free( & ( ( *lock )->settings_controller ) );
	}

	free( *lock );
	*lock	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_LockSettingsController* Rbdb_Lock_settingsController(	Rbdb_Lock* lock )	{
	return lock->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_Lock_parentEnvironment(	Rbdb_Lock* lock )	{
	return lock->parent_lock_controller->parent_environment;
}

/*************
*  lock  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_get.html
Rbdb_Lock* Rbdb_Lock_lock(	Rbdb_Lock*		lock, 
								Rbdb_Record*	record )	{

	Rbdb_Environment*		environment	=	lock->parent_lock_controller->parent_environment;
								
	environment->wrapped_bdb_environment->lock_get(	environment->wrapped_bdb_environment,
							Rbdb_LockController_lockerID( lock->parent_lock_controller ),
							Rbdb_LockSettingsController_internal_openFlags( Rbdb_SettingsController_lockSettingsController( Rbdb_Environment_settingsController( environment ) ) ),
							record->data->wrapped_bdb_dbt->data,
							Rbdb_Lock_internal_lockMode( lock ),
							&( lock->wrapped_bdb_lock ) );
	return lock;
}

/**************
*  unlock  *
**************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_put.html
void Rbdb_Lock_unlock( Rbdb_Lock* lock )	{

	DB_ENV*		environment	=	lock->parent_lock_controller->parent_environment->wrapped_bdb_environment;

	environment->lock_put(	environment,
							&( lock->wrapped_bdb_lock ) );
}

/*****************
*  isReadLock  *
*****************/

BOOL Rbdb_Lock_isReadLock( Rbdb_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_READ )	{
		return TRUE;
	}
	return FALSE;
}

/*********************
*  setToReadLock  *
*********************/

void Rbdb_Lock_setToReadLock( Rbdb_Lock* lock )	{
	
	lock->mode	= DB_LOCK_READ;
}

/*********************
*  isWriteLock  *
*********************/

BOOL Rbdb_Lock_isWriteLock( Rbdb_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_WRITE )	{
		return TRUE;
	}
	return FALSE;
}

/*********************
*  setToWriteLock  *
*********************/

void Rbdb_Lock_setToWriteLock( Rbdb_Lock* lock )	{
	
	lock->mode	= DB_LOCK_WRITE;
}

/*****************************
*  isIntentToWriteLock  *
*****************************/

BOOL Rbdb_Lock_isIntentToWriteLock( Rbdb_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_IWRITE )	{
		return TRUE;
	}
	return FALSE;
}

/*****************************
*  setToIntentToWriteLock  *
*****************************/

void Rbdb_Lock_setToIntentToWriteLock( Rbdb_Lock* lock )	{
	
	lock->mode	= DB_LOCK_IWRITE;
}

/*************************
*  isIntentToReadLock  *
*************************/

BOOL Rbdb_Lock_isIntentToReadLock( Rbdb_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_IREAD )	{
		return TRUE;
	}
	return FALSE;
}

/*****************************
*  setToIntentToReadLock  *
*****************************/

void Rbdb_Lock_setToIntentToReadLock( Rbdb_Lock* lock )	{
	
	lock->mode	= DB_LOCK_IREAD;
}

/*********************************
*  isIntentToReadAndWriteLock  *
*********************************/

BOOL Rbdb_Lock_isIntentToReadAndWriteLock( Rbdb_Lock* lock )	{
	
	if ( lock->mode == DB_LOCK_IWR )	{
		return TRUE;
	}
	return FALSE;
}

/*************************************
*  setToIntentToReadAndWriteLock  *
*************************************/

void Rbdb_Lock_setToIntentToReadAndWriteLock( Rbdb_Lock* lock )	{
	
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

int Rbdb_Lock_internal_lockMode( Rbdb_Lock* lock )	{

	return lock->mode;
}
