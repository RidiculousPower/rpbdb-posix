/*
 *		RPbdb::MutexController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "MutexController.h"

#include "Mutex.h"
#include "Mutex_internal.h"

#include "Database.h"
#include "Database_internal.h"
#include "DatabaseCursor.h"

#include "Data.h"
#include "Record.h"

#include "SettingsController.h"
#include "MutexSettingsController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_MutexController* RPbdb_MutexController_new( RPbdb_Environment* parent_environment )	{
	
	RPbdb_MutexController*		mutex_controller = calloc( 1, sizeof( RPbdb_MutexController ) );

	mutex_controller->parent_environment = parent_environment;

	return mutex_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_MutexController_free( RPbdb_MutexController** mutex_controller )	{

	if ( ( *mutex_controller )->runtime_storage_database != NULL )	{
		RPbdb_Database_free( & ( ( *mutex_controller )->runtime_storage_database ) );
	}

	free( *mutex_controller );
	*mutex_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_MutexSettingsController* RPbdb_MutexController_settingsController(	RPbdb_MutexController* mutex_controller )	{
	return mutex_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MutexController_parentEnvironment(	RPbdb_MutexController* mutex_controller )	{
	return mutex_controller->parent_environment;
}

/*********************
*  closeAllMutexes  *
*********************/

void RPbdb_MutexController_closeAllMutexes( RPbdb_MutexController* mutex_controller )	{
	
	RPbdb_Database_internal_closeAllStoredRuntimeAddresses(	mutex_controller->runtime_storage_database,
																													(void *(*)(void*)) & RPbdb_Mutex_close );
}

/*********************
*  freeAllMutexes  *
*********************/

void RPbdb_MutexController_freeAllMutexes( RPbdb_MutexController* mutex_controller )	{

	RPbdb_MutexController_closeAllMutexes( mutex_controller );
	RPbdb_Database_internal_freeAllStoredRuntimeAddresses(	mutex_controller->runtime_storage_database,
																												(void *(*)(void**)) & RPbdb_Mutex_internal_freeFromRuntimeStorage );
}

