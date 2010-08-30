#ifndef RPDB_MEMORY_POOL_FILE_PAGE_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_MEMORY_POOL_FILE_PAGE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
	
BOOL		RPDB_MemoryPoolFilePageSettingsController_internal_retrievePageFromCacheFlags(		RPDB_MemoryPoolFilePageSettingsController*		memory_pool_file_page_settings_controller );
BOOL		RPDB_MemoryPoolFilePageSettingsController_internal_writePageToCacheFlags(	RPDB_MemoryPoolFilePageSettingsController*		memory_pool_file_page_settings_controller );
	
RPDB_MemoryPoolFilePageSettingsController* RPDB_MemoryPoolFilePageSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

#endif

