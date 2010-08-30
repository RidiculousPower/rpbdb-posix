/*
 *		RPDB::SettingsController::RuntimeStorageSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_RuntimeStorageController.h"

#include "RPDB_Environment.h"

#include "RPDB_SettingsController.h"
#include "RPDB_RuntimeStorageSettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_RuntimeStorageSettingsController* RPDB_RuntimeStorageSettingsController_new( RPDB_RuntimeStorageController* parent_runtime_storage_controller )	{
	
	RPDB_RuntimeStorageSettingsController*	runtime_storage_settings_controller	=	calloc( 1, sizeof( RPDB_RuntimeStorageSettingsController ) );
	
	runtime_storage_settings_controller->parent_runtime_storage_controller	=	parent_runtime_storage_controller;
	
	//	Defaults to on
	RPDB_RuntimeStorageSettingsController_turnAutomaticDefaultEnvironmentOn( runtime_storage_settings_controller );
	
	return runtime_storage_settings_controller;	
}

/***************************
*  free  *
***************************/
void RPDB_RuntimeStorageSettingsController_free(	RPDB_RuntimeStorageSettingsController** runtime_storage_settings_controller )	{

	free( *runtime_storage_settings_controller );
	*runtime_storage_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_RuntimeStorageSettingsController_parentEnvironment(	RPDB_RuntimeStorageSettingsController* runtime_storage_settings_controller )	{
	return runtime_storage_settings_controller->parent_settings_controller->parent_environment;
}

/********************************
*  storeInApplicationMemory  *
********************************/

BOOL RPDB_RuntimeStorageSettingsController_storeInApplicationMemory( RPDB_RuntimeStorageSettingsController* runtime_settings_controller )	{
	
	if ( runtime_settings_controller->store_in_application_memory == TRUE )	{
		return TRUE;
	}
	return FALSE;
}

	/************************************
	*  turnStoreInApplicationMemoryOn  *
	************************************/

	void RPDB_RuntimeStorageSettingsController_turnStoreInApplicationMemoryOn( RPDB_RuntimeStorageSettingsController* runtime_settings_controller )	{
		runtime_settings_controller->store_in_application_memory = TRUE;
	}

	/************************************
	*  turnStoreInApplicationMemoryOff  *
	************************************/

	void RPDB_RuntimeStorageSettingsController_turnStoreInApplicationMemoryOff( RPDB_RuntimeStorageSettingsController* runtime_settings_controller )	{
		runtime_settings_controller->store_in_application_memory = FALSE;
	}

/************************
*  storeInSystemMemory  *
************************/

BOOL RPDB_RuntimeStorageSettingsController_storeInSystemMemory( RPDB_RuntimeStorageSettingsController* runtime_settings_controller )	{
	
	if ( runtime_settings_controller->store_in_system_memory == TRUE )	{
		return TRUE;
	}
	return FALSE;
}

	/********************************
	*  turnStoreInSystemMemoryOn  *
	********************************/

	void RPDB_RuntimeStorageSettingsController_turnStoreInSystemMemoryOn( RPDB_RuntimeStorageSettingsController* runtime_settings_controller )	{
		runtime_settings_controller->store_in_system_memory = TRUE;
	}

	/********************************
	*  turnStoreInSystemMemoryOff  *
	********************************/

	void RPDB_RuntimeStorageSettingsController_turnStoreInSystemMemoryOff( RPDB_RuntimeStorageSettingsController* runtime_settings_controller )	{
		runtime_settings_controller->store_in_system_memory = TRUE;
	}

/****************
*  storeOnDisk  *
****************/

BOOL RPDB_RuntimeStorageSettingsController_storeOnDisk( RPDB_RuntimeStorageSettingsController* runtime_settings_controller )	{
	
	if ( runtime_settings_controller->store_on_disk == TRUE )	{
		return TRUE;
	}
	return FALSE;
}

	/************************
	*  turnStoreOnDiskOn  *
	************************/

	void RPDB_RuntimeStorageSettingsController_turnStoreOnDiskOn( RPDB_RuntimeStorageSettingsController* runtime_settings_controller )	{
		runtime_settings_controller->store_on_disk = TRUE;
	}

	/************************
	*  turnStoreOnDiskOff  *
	************************/

	void RPDB_RuntimeStorageSettingsController_turnStoreOnDiskOff( RPDB_RuntimeStorageSettingsController* runtime_settings_controller )	{
		runtime_settings_controller->store_on_disk = FALSE;
	}
	/************************************
	*  automaticDefaultEnvironment  *
	************************************/

	BOOL RPDB_RuntimeStorageSettingsController_automaticDefaultEnvironment( RPDB_RuntimeStorageSettingsController* runtime_settings_controller )	{

		return runtime_settings_controller->automatic_default_environment;
	}

		/****************************************
		*  turnRuntimeStorageActivityLoggingOn  *
		****************************************/

		void RPDB_RuntimeStorageSettingsController_turnAutomaticDefaultEnvironmentOn( RPDB_RuntimeStorageSettingsController* runtime_settings_controller )	{

			runtime_settings_controller->automatic_default_environment = TRUE;
		}

		/********************************************
		*  turnRuntimeStorageActivityLoggingOff  *
		********************************************/

		void RPDB_RuntimeStorageSettingsController_turnAutomaticDefaultEnvironmentOff( RPDB_RuntimeStorageSettingsController* runtime_settings_controller )	{

			runtime_settings_controller->automatic_default_environment = FALSE;
		}





/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_RuntimeStorageSettingsController* RPDB_RuntimeStorageSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_RuntimeStorageSettingsController* runtime_storage_settings_controller )	{

	RPDB_RuntimeStorageSettingsController* runtime_storage_settings_controller_copy	=	RPDB_RuntimeStorageSettingsController_new( runtime_storage_settings_controller->parent_runtime_storage_controller );

	//	Instances and Pointers
	runtime_storage_settings_controller_copy->store_in_system_memory	=	runtime_storage_settings_controller->store_in_system_memory;
	runtime_storage_settings_controller_copy->store_in_application_memory	=	runtime_storage_settings_controller->store_in_application_memory;
	runtime_storage_settings_controller_copy->log_runtime_storage_activity	=	runtime_storage_settings_controller->log_runtime_storage_activity;
	runtime_storage_settings_controller_copy->store_on_disk	=	runtime_storage_settings_controller->store_on_disk;

	return runtime_storage_settings_controller_copy;
}

