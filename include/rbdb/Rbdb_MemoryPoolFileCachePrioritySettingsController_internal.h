#ifndef RBDB_MEMORY_POOL_FILE_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_MEMORY_POOL_FILE_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

        													                                                                            						
BOOL															Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast(							Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY cache_priority );
BOOL															Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost(							Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY cache_priority );
        													                                                                                					
BOOL															Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority(						Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY cache_priority );
void														Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo(						Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY cache_priority );
Rbdb_MemoryPoolFileCachePrioritySettingsController* Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );

#endif

