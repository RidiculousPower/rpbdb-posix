/*
 *		Rbdb::MutexController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_MutexController.h"

#include "Rbdb_Mutex.h"
#include "Rbdb_Mutex_internal.h"

#include "Rbdb_Database.h"
#include "Rbdb_Database_internal.h"
#include "Rbdb_DatabaseCursor.h"

#include "Rbdb_Data.h"
#include "Rbdb_Record.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_MutexSettingsController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_MutexController* Rbdb_MutexController_new( Rbdb_Environment* parent_environment )	{
	
	Rbdb_MutexController*		mutex_controller = calloc( 1, sizeof( Rbdb_MutexController ) );

	mutex_controller->parent_environment = parent_environment;

	return mutex_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_MutexController_free( Rbdb_MutexController** mutex_controller )	{

	if ( ( *mutex_controller )->runtime_storage_database != NULL )	{
		Rbdb_Database_free( & ( ( *mutex_controller )->runtime_storage_database ) );
	}

	free( *mutex_controller );
	*mutex_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_MutexSettingsController* Rbdb_MutexController_settingsController(	Rbdb_MutexController* mutex_controller )	{
	return mutex_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_MutexController_parentEnvironment(	Rbdb_MutexController* mutex_controller )	{
	return mutex_controller->parent_environment;
}

/*********************
*  closeAllMutexes  *
*********************/

void Rbdb_MutexController_closeAllMutexes( Rbdb_MutexController* mutex_controller )	{
	
	Rbdb_Database_internal_closeAllStoredRuntimeAddresses(	mutex_controller->runtime_storage_database,
																													(void *(*)(void*)) & Rbdb_Mutex_close );
}

/*********************
*  freeAllMutexes  *
*********************/

void Rbdb_MutexController_freeAllMutexes( Rbdb_MutexController* mutex_controller )	{

	Rbdb_MutexController_closeAllMutexes( mutex_controller );
	Rbdb_Database_internal_freeAllStoredRuntimeAddresses(	mutex_controller->runtime_storage_database,
																												(void *(*)(void**)) & Rbdb_Mutex_internal_freeFromRuntimeStorage );
}

