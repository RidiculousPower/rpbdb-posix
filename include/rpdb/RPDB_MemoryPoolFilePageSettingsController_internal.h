#ifndef Rbdb_MEMORY_POOL_FILE_PAGE_SETTINGS_CONTROLLER_INTERNAL
	#define Rbdb_MEMORY_POOL_FILE_PAGE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
	
BOOL		Rbdb_MemoryPoolFilePageSettingsController_internal_retrievePageFromCacheFlags(		Rbdb_MemoryPoolFilePageSettingsController*		memory_pool_file_page_settings_controller );
BOOL		Rbdb_MemoryPoolFilePageSettingsController_internal_writePageToCacheFlags(	Rbdb_MemoryPoolFilePageSettingsController*		memory_pool_file_page_settings_controller );
	
Rbdb_MemoryPoolFilePageSettingsController* Rbdb_MemoryPoolFilePageSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

#endif

