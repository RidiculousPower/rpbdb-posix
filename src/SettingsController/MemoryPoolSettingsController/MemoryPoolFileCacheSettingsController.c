/*
 *		RPbdb::SettingsController::MemoryPoolSettingsController::MemoryPoolFileSettingsController::MemoryPoolFilePageSettingsController::MemoryPoolFilePagePrioritySettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "MemoryPoolFileCacheSettingsController.h"
#include "MemoryPoolFileCachePrioritySettingsController.h"

#include "MemoryPoolFileCacheSettingsController_internal.h"
#include "MemoryPoolFileCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_MemoryPoolFileCacheSettingsController* RPbdb_MemoryPoolFileCacheSettingsController_new( RPbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller )	{

	RPbdb_MemoryPoolFileCacheSettingsController*		memory_pool_file_cache_settings_controller = calloc( 1, sizeof( RPbdb_MemoryPoolFileCacheSettingsController ) );

	memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller = memory_pool_file_settings_controller;

	return memory_pool_file_cache_settings_controller;
}

/***************************
*  free  *
***************************/

void RPbdb_MemoryPoolFileCacheSettingsController_free(	RPbdb_MemoryPoolFileCacheSettingsController** memory_pool_file_cache_settings_controller )	{

	if ( ( *memory_pool_file_cache_settings_controller )->priority_settings_controller != NULL )	{
		RPbdb_MemoryPoolFileCachePrioritySettingsController_free( & ( ( *memory_pool_file_cache_settings_controller )->priority_settings_controller ) );
	}

	free( *memory_pool_file_cache_settings_controller );
	*memory_pool_file_cache_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/

RPbdb_Environment* RPbdb_MemoryPoolFileCacheSettingsController_parentEnvironment(	RPbdb_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller )	{
	return memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/**************************
*  priorityController  *
**************************/

RPbdb_MemoryPoolFileCachePrioritySettingsController* RPbdb_MemoryPoolFileCacheSettingsController_prioritySettingsController( RPbdb_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller )	{
	
	if ( memory_pool_file_cache_settings_controller->priority_settings_controller == NULL )	{
		
		memory_pool_file_cache_settings_controller->priority_settings_controller = RPbdb_MemoryPoolFileCachePrioritySettingsController_new( memory_pool_file_cache_settings_controller );
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

RPbdb_MemoryPoolFileCacheSettingsController* RPbdb_MemoryPoolFileCacheSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller )	{

	RPbdb_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller_copy	=	RPbdb_MemoryPoolFileCacheSettingsController_new( memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller );

	//	Instances and Pointers
	memory_pool_file_cache_settings_controller_copy->priority_settings_controller	=	RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance( memory_pool_file_cache_settings_controller->priority_settings_controller );

	return memory_pool_file_cache_settings_controller_copy;
}

