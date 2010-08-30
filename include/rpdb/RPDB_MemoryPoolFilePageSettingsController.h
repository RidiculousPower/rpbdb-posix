/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPDB_MEMORY_POOL_FILE_PAGE_SETTINGS_CONTROLLER
	#define RPDB_MEMORY_POOL_FILE_PAGE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_MemoryPoolFilePageSettingsController*		RPDB_MemoryPoolFilePageSettingsController_new(															RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void											RPDB_MemoryPoolFilePageSettingsController_free(													RPDB_MemoryPoolFilePageSettingsController** memory_pool_file_page_settings_controller );
	RPDB_Environment*						RPDB_MemoryPoolFilePageSettingsController_parentEnvironment(							RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										RPDB_MemoryPoolFilePageSettingsController_getPageCreatesPageIfDoesNotExist(							RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPDB_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOn(						RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPDB_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOff(						RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										RPDB_MemoryPoolFilePageSettingsController_getPageWritesCopyBeforeEviction(								RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPDB_MemoryPoolFilePageSettingsController_turnGetPageWritesCopyBeforeEvictionOn(						RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPDB_MemoryPoolFilePageSettingsController_turnGetPageWritesCopyBeforeEvictionOff(						RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										RPDB_MemoryPoolFilePageSettingsController_getPageWritesBeforeEvictionWithoutCopy(						RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPDB_MemoryPoolFilePageSettingsController_turnWriteBeforeEvictionButProhibitMultiversionCopyOn(		RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPDB_MemoryPoolFilePageSettingsController_turnWriteBeforeEvictionButProhibitMultiversionCopyOff(		RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										RPDB_MemoryPoolFilePageSettingsController_getPageReturnsLastPage(										RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPDB_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOn(								RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPDB_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOff(								RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

	BOOL										RPDB_MemoryPoolFilePageSettingsController_getPageCreatesNewPage(										RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPDB_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOn(									RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );
	void										RPDB_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOff(								RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller );

#endif

