/*
 *		RPDB::MutexController::Mutex
 *
 *	
 */
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
 
#include "RPDB_Mutex.h"
#include "RPDB_Mutex_internal.h"

#include "RPDB_Database_internal.h"

#include "RPDB_MutexController.h"

#include "RPDB_Environment.h"

#include "RPDB_SettingsController.h"
#include "RPDB_MutexSettingsController.h"
#include "RPDB_MutexSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_alloc.html
RPDB_Mutex* RPDB_Mutex_new( RPDB_MutexController* parent_mutex_controller )	{

	RPDB_Mutex*	mutex	=	calloc( 1, sizeof( RPDB_Mutex ) );

	if ( parent_mutex_controller->runtime_storage_database != NULL )	{
		mutex->runtime_identifier =	RPDB_Database_internal_storeRuntimeAddress(	parent_mutex_controller->runtime_storage_database,
																																						(void*) mutex );
	}

	mutex->parent_mutex_controller = parent_mutex_controller;
	
	//	Make call to instantiate local settings controller
	mutex->settings_controller	=	RPDB_MutexSettingsController_internal_copyOfSettingsControllerForInstance( RPDB_SettingsController_mutexSettingsController( RPDB_Environment_settingsController( parent_mutex_controller->parent_environment ) ) );
	
	return mutex;
}

/***************************
*  free  *
***************************/
void RPDB_Mutex_free(	RPDB_Mutex** mutex )	{

	if ( ( *mutex )->parent_mutex_controller->runtime_storage_database != NULL )	{
		RPDB_Database_internal_freeStoredRuntimeAddress(	( *mutex )->parent_mutex_controller->runtime_storage_database,
																											( *mutex )->runtime_identifier );
	}
	RPDB_Mutex_internal_freeFromRuntimeStorage( mutex );
}

/***************************
*  free  *
***************************/
void RPDB_Mutex_internal_freeFromRuntimeStorage(	RPDB_Mutex** mutex )	{

	if ( ( *mutex )->settings_controller != NULL )	{
		RPDB_MutexSettingsController_free( & ( ( *mutex )->settings_controller ) );
	}
	
	free( *mutex );
	*mutex	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_MutexSettingsController* RPDB_Mutex_settingsController(	RPDB_Mutex* mutex )	{
	return mutex->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_Mutex_parentEnvironment(	RPDB_Mutex* mutex )	{
	return mutex->parent_mutex_controller->parent_environment;
}

/*************
*  open  *
*************/

RPDB_Mutex* RPDB_Mutex_open( RPDB_Mutex* mutex )	{

	RPDB_Environment*		environment	=	mutex->parent_mutex_controller->parent_environment;

	environment->wrapped_bdb_environment->mutex_alloc(	environment->wrapped_bdb_environment,
								RPDB_MutexSettingsController_internal_openFlags( RPDB_SettingsController_mutexSettingsController( RPDB_Environment_settingsController( environment ) ) ),
								&( mutex->wrapped_bdb_mutex ) );	
	return mutex;
}

/*************
*  close  *
*************/

void RPDB_Mutex_close( RPDB_Mutex* mutex )	{

	//	we call this function close for consistency - internally we are freeing the mutex
	
	RPDB_Environment*	environment	=	mutex->parent_mutex_controller->parent_environment;
	
	environment->wrapped_bdb_environment->mutex_free(	environment->wrapped_bdb_environment,
														mutex->wrapped_bdb_mutex );

}

/*************
*  lock  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_lock.html
RPDB_Mutex* RPDB_Mutex_lock( RPDB_Mutex* mutex )	{

	DB_ENV*		environment	=	mutex->parent_mutex_controller->parent_environment->wrapped_bdb_environment;
	
	environment->mutex_lock(	environment,
								mutex->wrapped_bdb_mutex );

	return mutex;
}

/*************
*  unlock  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_unlock.html
RPDB_Mutex* RPDB_Mutex_unlock( RPDB_Mutex* mutex )	{

	DB_ENV*		environment	=	mutex->parent_mutex_controller->parent_environment->wrapped_bdb_environment;
	
	environment->mutex_unlock(	environment,
								mutex->wrapped_bdb_mutex );

	return mutex;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

