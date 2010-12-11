/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RBDB_MEMORY_POOL_FILE_PAGE_SETTINGS_CONTROLLER
	#define RBDB_MEMORY_POOL_FILE_PAGE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_MemoryPoolFilePageSettingsController*		Rbdb_MemoryPoolFilePageSettingsController_new(															Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void											Rbdb_MemoryPoolFilePageSettingsController_free(													Rbdb_MemoryPoolFilePageSettingsController** memory_pool_file_page_settings_controller );
	Rbdb_Environment*						Rbdb_MemoryPoolFilePageSettingsController_parentEnvironment(							Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										Rbdb_MemoryPoolFilePageSettingsController_getPageCreatesPageIfDoesNotExist(							Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										Rbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOn(						Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										Rbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOff(						Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										Rbdb_MemoryPoolFilePageSettingsController_getPageWritesCopyBeforeEviction(								Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										Rbdb_MemoryPoolFilePageSettingsController_turnGetPageWritesCopyBeforeEvictionOn(						Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										Rbdb_MemoryPoolFilePageSettingsController_turnGetPageWritesCopyBeforeEvictionOff(						Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										Rbdb_MemoryPoolFilePageSettingsController_getPageWritesBeforeEvictionWithoutCopy(						Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										Rbdb_MemoryPoolFilePageSettingsController_turnWriteBeforeEvictionButProhibitMultiversionCopyOn(		Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										Rbdb_MemoryPoolFilePageSettingsController_turnWriteBeforeEvictionButProhibitMultiversionCopyOff(		Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										Rbdb_MemoryPoolFilePageSettingsController_getPageReturnsLastPage(										Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										Rbdb_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOn(								Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										Rbdb_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOff(								Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										Rbdb_MemoryPoolFilePageSettingsController_getPageCreatesNewPage(										Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										Rbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOn(									Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										Rbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOff(								Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

#endif

