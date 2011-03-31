/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPBDB_MEMORY_POOL_FILE_PAGE_SETTINGS_CONTROLLER
	#define RPBDB_MEMORY_POOL_FILE_PAGE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_MemoryPoolFilePageSettingsController*		RPbdb_MemoryPoolFilePageSettingsController_new(															RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void											RPbdb_MemoryPoolFilePageSettingsController_free(													RPbdb_MemoryPoolFilePageSettingsController** memory_pool_file_page_settings_controller );
	RPbdb_Environment*						RPbdb_MemoryPoolFilePageSettingsController_parentEnvironment(							RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										RPbdb_MemoryPoolFilePageSettingsController_getPageCreatesPageIfDoesNotExist(							RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOn(						RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOff(						RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										RPbdb_MemoryPoolFilePageSettingsController_getPageWritesCopyBeforeEviction(								RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPbdb_MemoryPoolFilePageSettingsController_turnGetPageWritesCopyBeforeEvictionOn(						RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPbdb_MemoryPoolFilePageSettingsController_turnGetPageWritesCopyBeforeEvictionOff(						RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										RPbdb_MemoryPoolFilePageSettingsController_getPageWritesBeforeEvictionWithoutCopy(						RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPbdb_MemoryPoolFilePageSettingsController_turnWriteBeforeEvictionButProhibitMultiversionCopyOn(		RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPbdb_MemoryPoolFilePageSettingsController_turnWriteBeforeEvictionButProhibitMultiversionCopyOff(		RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										RPbdb_MemoryPoolFilePageSettingsController_getPageReturnsLastPage(										RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPbdb_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOn(								RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPbdb_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOff(								RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										RPbdb_MemoryPoolFilePageSettingsController_getPageCreatesNewPage(										RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOn(									RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOff(								RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

#endif

