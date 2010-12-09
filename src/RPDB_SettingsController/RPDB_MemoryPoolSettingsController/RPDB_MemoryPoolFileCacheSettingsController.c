/*
 *		Rbdb::SettingsController::MemoryPoolSettingsController::MemoryPoolFileSettingsController::MemoryPoolFilePageSettingsController::MemoryPoolFilePagePrioritySettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_MemoryPoolFileCacheSettingsController.h"
#include "Rbdb_MemoryPoolFileCachePrioritySettingsController.h"

#include "Rbdb_MemoryPoolFileCacheSettingsController_internal.h"
#include "Rbdb_MemoryPoolFileCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

Rbdb_MemoryPoolFileCacheSettingsController* Rbdb_MemoryPoolFileCacheSettingsController_new( Rbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller )	{

	Rbdb_MemoryPoolFileCacheSettingsController*		memory_pool_file_cache_settings_controller = calloc( 1, sizeof( Rbdb_MemoryPoolFileCacheSettingsController ) );

	memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller = memory_pool_file_settings_controller;

	return memory_pool_file_cache_settings_controller;
}

/***************************
*  free  *
***************************/

void Rbdb_MemoryPoolFileCacheSettingsController_free(	Rbdb_MemoryPoolFileCacheSettingsController** memory_pool_file_cache_settings_controller )	{

	if ( ( *memory_pool_file_cache_settings_controller )->priority_settings_controller != NULL )	{
		Rbdb_MemoryPoolFileCachePrioritySettingsController_free( & ( ( *memory_pool_file_cache_settings_controller )->priority_settings_controller ) );
	}

	free( *memory_pool_file_cache_settings_controller );
	*memory_pool_file_cache_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/

Rbdb_Environment* Rbdb_MemoryPoolFileCacheSettingsController_parentEnvironment(	Rbdb_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller )	{
	return memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/**************************
*  priorityController  *
**************************/

Rbdb_MemoryPoolFileCachePrioritySettingsController* Rbdb_MemoryPoolFileCacheSettingsController_prioritySettingsController( Rbdb_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller )	{
	
	if ( memory_pool_file_cache_settings_controller->priority_settings_controller == NULL )	{
		
		memory_pool_file_cache_settings_controller->priority_settings_controller = Rbdb_MemoryPoolFileCachePrioritySettingsController_new( memory_pool_file_cache_settings_controller );
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

Rbdb_MemoryPoolFileCacheSettingsController* Rbdb_MemoryPoolFileCacheSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller )	{

	Rbdb_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller_copy	=	Rbdb_MemoryPoolFileCacheSettingsController_new( memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller );

	//	Instances and Pointers
	memory_pool_file_cache_settings_controller_copy->priority_settings_controller	=	Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance( memory_pool_file_cache_settings_controller->priority_settings_controller );

	return memory_pool_file_cache_settings_controller_copy;
}

