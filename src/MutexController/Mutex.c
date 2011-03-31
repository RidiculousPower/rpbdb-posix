/*
 *		RPbdb::MutexController::Mutex
 *
 *	
 */
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
 
#include "Mutex.h"
#include "Mutex_internal.h"

#include "Database_internal.h"

#include "MutexController.h"

#include "Environment.h"

#include "SettingsController.h"
#include "MutexSettingsController.h"
#include "MutexSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_alloc.html
RPbdb_Mutex* RPbdb_Mutex_new( RPbdb_MutexController* parent_mutex_controller )	{

	RPbdb_Mutex*	mutex	=	calloc( 1, sizeof( RPbdb_Mutex ) );

	if ( parent_mutex_controller->runtime_storage_database != NULL )	{
		mutex->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_mutex_controller->runtime_storage_database,
																																						(void*) mutex );
	}

	mutex->parent_mutex_controller = parent_mutex_controller;
	
	//	Make call to instantiate local settings controller
	mutex->settings_controller	=	RPbdb_MutexSettingsController_internal_copyOfSettingsControllerForInstance( RPbdb_SettingsController_mutexSettingsController( RPbdb_Environment_settingsController( parent_mutex_controller->parent_environment ) ) );
	
	return mutex;
}

/***************************
*  free  *
***************************/
void RPbdb_Mutex_free(	RPbdb_Mutex** mutex )	{

	if ( ( *mutex )->parent_mutex_controller->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *mutex )->parent_mutex_controller->runtime_storage_database,
																											( *mutex )->runtime_identifier );
	}
	RPbdb_Mutex_internal_freeFromRuntimeStorage( mutex );
}

/***************************
*  free  *
***************************/
void RPbdb_Mutex_internal_freeFromRuntimeStorage(	RPbdb_Mutex** mutex )	{

	if ( ( *mutex )->settings_controller != NULL )	{
		RPbdb_MutexSettingsController_free( & ( ( *mutex )->settings_controller ) );
	}
	
	free( *mutex );
	*mutex	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_MutexSettingsController* RPbdb_Mutex_settingsController(	RPbdb_Mutex* mutex )	{
	return mutex->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_Mutex_parentEnvironment(	RPbdb_Mutex* mutex )	{
	return mutex->parent_mutex_controller->parent_environment;
}

/*************
*  open  *
*************/

RPbdb_Mutex* RPbdb_Mutex_open( RPbdb_Mutex* mutex )	{

	RPbdb_Environment*		environment	=	mutex->parent_mutex_controller->parent_environment;

	environment->wrapped_bdb_environment->mutex_alloc(	environment->wrapped_bdb_environment,
								RPbdb_MutexSettingsController_internal_openFlags( RPbdb_SettingsController_mutexSettingsController( RPbdb_Environment_settingsController( environment ) ) ),
								&( mutex->wrapped_bdb_mutex ) );	
	return mutex;
}

/*************
*  close  *
*************/

void RPbdb_Mutex_close( RPbdb_Mutex* mutex )	{

	//	we call this function close for consistency - internally we are freeing the mutex
	
	RPbdb_Environment*	environment	=	mutex->parent_mutex_controller->parent_environment;
	
	environment->wrapped_bdb_environment->mutex_free(	environment->wrapped_bdb_environment,
														mutex->wrapped_bdb_mutex );

}

/*************
*  lock  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_lock.html
RPbdb_Mutex* RPbdb_Mutex_lock( RPbdb_Mutex* mutex )	{

	DB_ENV*		environment	=	mutex->parent_mutex_controller->parent_environment->wrapped_bdb_environment;
	
	environment->mutex_lock(	environment,
								mutex->wrapped_bdb_mutex );

	return mutex;
}

/*************
*  unlock  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_unlock.html
RPbdb_Mutex* RPbdb_Mutex_unlock( RPbdb_Mutex* mutex )	{

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

