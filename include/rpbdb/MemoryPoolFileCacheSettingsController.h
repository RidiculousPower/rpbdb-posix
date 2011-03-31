/*
 *		RPbdb::SettingsController::MemoryPoolSettingsController::MemoryPoolFileSettingsController::MemoryPoolFileCachePrioritySettingsController
 *
 *
 */

#ifndef RPBDB_MEMORY_POOL_FILE_CACHE_SETTINGS_CONTROLLER
	#define RPBDB_MEMORY_POOL_FILE_CACHE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
					
	RPbdb_MemoryPoolFileCacheSettingsController*	RPbdb_MemoryPoolFileCacheSettingsController_new(	RPbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller );

	void													RPbdb_MemoryPoolFileCacheSettingsController_free(	RPbdb_MemoryPoolFileCacheSettingsController** memory_pool_file_cache_settings_controller );
	RPbdb_Environment*								RPbdb_MemoryPoolFileCacheSettingsController_parentEnvironment(	RPbdb_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller );

	RPbdb_MemoryPoolFileCachePrioritySettingsController* RPbdb_MemoryPoolFileCacheSettingsController_prioritySettingsController( RPbdb_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller );

#endif

