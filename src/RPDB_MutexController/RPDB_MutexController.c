/*
 *		RPDB::MutexController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MutexController.h"

#include "RPDB_Mutex.h"
#include "RPDB_Mutex_internal.h"

#include "RPDB_Database.h"
#include "RPDB_Database_internal.h"
#include "RPDB_DatabaseCursor.h"

#include "RPDB_Data.h"
#include "RPDB_Record.h"

#include "RPDB_SettingsController.h"
#include "RPDB_MutexSettingsController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_MutexController* RPDB_MutexController_new( RPDB_Environment* parent_environment )	{
	
	RPDB_MutexController*		mutex_controller = calloc( 1, sizeof( RPDB_MutexController ) );

	mutex_controller->parent_environment = parent_environment;

	return mutex_controller;
}

/***************************
*  free  *
***************************/
void RPDB_MutexController_free( RPDB_MutexController** mutex_controller )	{

	if ( ( *mutex_controller )->runtime_storage_database != NULL )	{
		RPDB_Database_free( & ( ( *mutex_controller )->runtime_storage_database ) );
	}

	free( *mutex_controller );
	*mutex_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_MutexSettingsController* RPDB_MutexController_settingsController(	RPDB_MutexController* mutex_controller )	{
	return mutex_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MutexController_parentEnvironment(	RPDB_MutexController* mutex_controller )	{
	return mutex_controller->parent_environment;
}

/*********************
*  closeAllMutexes  *
*********************/

void RPDB_MutexController_closeAllMutexes( RPDB_MutexController* mutex_controller )	{
	
	RPDB_Database_internal_closeAllStoredRuntimeAddresses(	mutex_controller->runtime_storage_database,
																													(void *(*)(void*)) & RPDB_Mutex_close );
}

/*********************
*  freeAllMutexes  *
*********************/

void RPDB_MutexController_freeAllMutexes( RPDB_MutexController* mutex_controller )	{

	RPDB_MutexController_closeAllMutexes( mutex_controller );
	RPDB_Database_internal_freeAllStoredRuntimeAddresses(	mutex_controller->runtime_storage_database,
																												(void *(*)(void**)) & RPDB_Mutex_internal_freeFromRuntimeStorage );
}

