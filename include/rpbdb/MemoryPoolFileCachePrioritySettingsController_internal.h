#ifndef RPBDB_MEMORY_POOL_FILE_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_MEMORY_POOL_FILE_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

        													                                                                            						
BOOL															RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast(							RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY cache_priority );
BOOL															RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost(							RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY cache_priority );
        													                                                                                					
BOOL															RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority(						RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY cache_priority );
void														RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo(						RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY cache_priority );
RPbdb_MemoryPoolFileCachePrioritySettingsController* RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );

#endif

