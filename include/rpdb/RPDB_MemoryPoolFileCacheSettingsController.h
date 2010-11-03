/*
 *		RPDB::SettingsController::MemoryPoolSettingsController::MemoryPoolFileSettingsController::MemoryPoolFileCachePrioritySettingsController
 *
 *
 */

#ifndef RPDB_MEMORY_POOL_FILE_CACHE_SETTINGS_CONTROLLER
	#define RPDB_MEMORY_POOL_FILE_CACHE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
					
	RPDB_MemoryPoolFileCacheSettingsController*	RPDB_MemoryPoolFileCacheSettingsController_new(	RPDB_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller );

	void													RPDB_MemoryPoolFileCacheSettingsController_free(	RPDB_MemoryPoolFileCacheSettingsController** memory_pool_file_cache_settings_controller );
	RPDB_Environment*								RPDB_MemoryPoolFileCacheSettingsController_parentEnvironment(	RPDB_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller );

	RPDB_MemoryPoolFileCachePrioritySettingsController* RPDB_MemoryPoolFileCacheSettingsController_prioritySettingsController( RPDB_MemoryPoolFileCacheSettingsController* memory_pool_file_cache_settings_controller );

#endif

