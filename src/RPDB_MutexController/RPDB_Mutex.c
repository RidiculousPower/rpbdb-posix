/*
 *		Rbdb::MutexController::Mutex
 *
 *	
 */
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
 
#include "Rbdb_Mutex.h"
#include "Rbdb_Mutex_internal.h"

#include "Rbdb_Database_internal.h"

#include "Rbdb_MutexController.h"

#include "Rbdb_Environment.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_MutexSettingsController.h"
#include "Rbdb_MutexSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_alloc.html
Rbdb_Mutex* Rbdb_Mutex_new( Rbdb_MutexController* parent_mutex_controller )	{

	Rbdb_Mutex*	mutex	=	calloc( 1, sizeof( Rbdb_Mutex ) );

	if ( parent_mutex_controller->runtime_storage_database != NULL )	{
		mutex->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_mutex_controller->runtime_storage_database,
																																						(void*) mutex );
	}

	mutex->parent_mutex_controller = parent_mutex_controller;
	
	//	Make call to instantiate local settings controller
	mutex->settings_controller	=	Rbdb_MutexSettingsController_internal_copyOfSettingsControllerForInstance( Rbdb_SettingsController_mutexSettingsController( Rbdb_Environment_settingsController( parent_mutex_controller->parent_environment ) ) );
	
	return mutex;
}

/***************************
*  free  *
***************************/
void Rbdb_Mutex_free(	Rbdb_Mutex** mutex )	{

	if ( ( *mutex )->parent_mutex_controller->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *mutex )->parent_mutex_controller->runtime_storage_database,
																											( *mutex )->runtime_identifier );
	}
	Rbdb_Mutex_internal_freeFromRuntimeStorage( mutex );
}

/***************************
*  free  *
***************************/
void Rbdb_Mutex_internal_freeFromRuntimeStorage(	Rbdb_Mutex** mutex )	{

	if ( ( *mutex )->settings_controller != NULL )	{
		Rbdb_MutexSettingsController_free( & ( ( *mutex )->settings_controller ) );
	}
	
	free( *mutex );
	*mutex	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_MutexSettingsController* Rbdb_Mutex_settingsController(	Rbdb_Mutex* mutex )	{
	return mutex->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_Mutex_parentEnvironment(	Rbdb_Mutex* mutex )	{
	return mutex->parent_mutex_controller->parent_environment;
}

/*************
*  open  *
*************/

Rbdb_Mutex* Rbdb_Mutex_open( Rbdb_Mutex* mutex )	{

	Rbdb_Environment*		environment	=	mutex->parent_mutex_controller->parent_environment;

	environment->wrapped_bdb_environment->mutex_alloc(	environment->wrapped_bdb_environment,
								Rbdb_MutexSettingsController_internal_openFlags( Rbdb_SettingsController_mutexSettingsController( Rbdb_Environment_settingsController( environment ) ) ),
								&( mutex->wrapped_bdb_mutex ) );	
	return mutex;
}

/*************
*  close  *
*************/

void Rbdb_Mutex_close( Rbdb_Mutex* mutex )	{

	//	we call this function close for consistency - internally we are freeing the mutex
	
	Rbdb_Environment*	environment	=	mutex->parent_mutex_controller->parent_environment;
	
	environment->wrapped_bdb_environment->mutex_free(	environment->wrapped_bdb_environment,
														mutex->wrapped_bdb_mutex );

}

/*************
*  lock  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_lock.html
Rbdb_Mutex* Rbdb_Mutex_lock( Rbdb_Mutex* mutex )	{

	DB_ENV*		environment	=	mutex->parent_mutex_controller->parent_environment->wrapped_bdb_environment;
	
	environment->mutex_lock(	environment,
								mutex->wrapped_bdb_mutex );

	return mutex;
}

/*************
*  unlock  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_unlock.html
Rbdb_Mutex* Rbdb_Mutex_unlock( Rbdb_Mutex* mutex )	{

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

