/*
 *		RPDB::MemoryPoolController::MemoryPoolFile::MemoryPoolFilePageController
 *
 *	
 */

#ifndef RPDB_MEMORY_POOL_FILE_PAGE_CONTROLLER
	#define RPDB_MEMORY_POOL_FILE_PAGE_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_MemoryPoolFilePageController*		RPDB_MemoryPoolFilePageController_new(						RPDB_MemoryPoolFile*					parent_memory_pool_file );

	void									RPDB_MemoryPoolFilePageController_free(	RPDB_MemoryPoolFilePageController** memory_pool_file_page_controller );
	RPDB_MemoryPoolFilePageSettingsController*		RPDB_MemoryPoolFilePageController_settingsController(	RPDB_MemoryPoolFilePageController* memory_pool_file_page_controller );
	RPDB_Environment*						RPDB_MemoryPoolFilePageController_parentEnvironment(	RPDB_MemoryPoolFilePageController* memory_pool_file_page_controller );

	RPDB_MemoryPoolFilePage*				RPDB_MemoryPoolFilePageController_retrievePageFromCache(	RPDB_MemoryPoolFilePageController*		memory_pool_file_page_controller,
	 						 				  															db_pgno_t								page_number_address	);


#endif

