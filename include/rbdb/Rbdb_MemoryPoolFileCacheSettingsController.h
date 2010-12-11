/*
 *		Rbdb::SettingsController::MemoryPoolSettingsController::MemoryPoolFileSettingsController::MemoryPoolFileCachePrioritySettingsController
 *
 *
 */

#ifndef RBDB_MEMORY_POOL_FILE_CACHE_SETTINGS_CONTROLLER
	#define RBDB_MEMORY_POOL_FILE_CACHE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
					
	Rbdb_MemoryPoolFileCacheSettingsController*	Rbdb_MemoryPoolFileCacheSettingsController_new(	Rbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller );

	void													Rbdb_MemoryPoolFileCacheSettingsController_free(	Rbdb_MemoryPoolFileCacheSettingsController** memory_pool_file_cache_settings_controller );
	Rbdb_Environment*								Rbdb_MemoryPoolFileCacheSettingsController_parentEnvironment(	Rbdb_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller );

	Rbdb_MemoryPoolFileCachePrioritySettingsController* Rbdb_MemoryPoolFileCacheSettingsController_prioritySettingsController( Rbdb_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller );

#endif

