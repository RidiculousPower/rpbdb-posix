#ifndef RPDB_MEMORY_POOL_FILE_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_MEMORY_POOL_FILE_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

        													                                                                            						
BOOL															RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast(							RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY cache_priority );
BOOL															RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost(							RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY cache_priority );
        													                                                                                					
BOOL															RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isPriority(						RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY cache_priority );
void														RPDB_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo(						RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY cache_priority );
RPDB_MemoryPoolFileCachePrioritySettingsController* RPDB_MemoryPoolFileCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );

#endif

