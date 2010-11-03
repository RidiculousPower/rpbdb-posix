/*
 *		RPDB::SettingsController::MemoryPoolSettingsController::MemoryPoolFileSettingsController::MemoryPoolFilePageSettingsController::MemoryPoolFilePagePrioritySettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MemoryPoolFileCacheSettingsController.h"
#include "RPDB_MemoryPoolFileCachePrioritySettingsController.h"

#include "RPDB_MemoryPoolFileCacheSettingsController_internal.h"
#include "RPDB_MemoryPoolFileCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_MemoryPoolFileCacheSettingsController* RPDB_MemoryPoolFileCacheSettingsController_new( RPDB_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller )	{

	RPDB_MemoryPoolFileCacheSettingsController*		memory_pool_file_cache_settings_controller = calloc( 1, sizeof( RPDB_MemoryPoolFileCacheSettingsController ) );

	memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller = memory_pool_file_settings_controller;

	return memory_pool_file_cache_settings_controller;
}

/***************************
*  free  *
***************************/

void RPDB_MemoryPoolFileCacheSettingsController_free(	RPDB_MemoryPoolFileCacheSettingsController** memory_pool_file_cache_settings_controller )	{

	if ( ( *memory_pool_file_cache_settings_controller )->priority_settings_controller != NULL )	{
		RPDB_MemoryPoolFileCachePrioritySettingsController_free( & ( ( *memory_pool_file_cache_settings_controller )->priority_settings_controller ) );
	}

	free( *memory_pool_file_cache_settings_controller );
	*memory_pool_file_cache_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/

RPDB_Environment* RPDB_MemoryPoolFileCacheSettingsController_parentEnvironment(	RPDB_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller )	{
	return memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/**************************
*  priorityController  *
**************************/

RPDB_MemoryPoolFileCachePrioritySettingsController* RPDB_MemoryPoolFileCacheSettingsController_prioritySettingsController( RPDB_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller )	{
	
	if ( memory_pool_file_cache_settings_controller->priority_settings_controller == NULL )	{
		
		memory_pool_file_cache_settings_controller->priority_settings_controller = RPDB_MemoryPoolFileCachePrioritySettingsController_new( memory_pool_file_cache_settings_controller );
	}
	return memory_pool_file_cache_settings_controller->priority_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/

RPDB_MemoryPoolFileCacheSettingsController* RPDB_MemoryPoolFileCacheSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller )	{

	RPDB_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller_copy	=	RPDB_MemoryPoolFileCacheSettingsController_new( memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller );

	//	Instances and Pointers
	memory_pool_file_cache_settings_controller_copy->priority_settings_controller	=	RPDB_MemoryPoolFileCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance( memory_pool_file_cache_settings_controller->priority_settings_controller );

	return memory_pool_file_cache_settings_controller_copy;
}

