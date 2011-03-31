#ifndef RPBDB_MEMORY_POOL_FILE_PAGE_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_MEMORY_POOL_FILE_PAGE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
	
BOOL		RPbdb_MemoryPoolFilePageSettingsController_internal_retrievePageFromCacheFlags(		RPbdb_MemoryPoolFilePageSettingsController*		memory_pool_file_page_settings_controller );
BOOL		RPbdb_MemoryPoolFilePageSettingsController_internal_writePageToCacheFlags(	RPbdb_MemoryPoolFilePageSettingsController*		memory_pool_file_page_settings_controller );
	
RPbdb_MemoryPoolFilePageSettingsController* RPbdb_MemoryPoolFilePageSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

#endif

