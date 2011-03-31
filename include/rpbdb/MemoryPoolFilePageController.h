/*
 *		RPbdb::MemoryPoolController::MemoryPoolFile::MemoryPoolFilePageController
 *
 *	
 */

#ifndef RPBDB_MEMORY_POOL_FILE_PAGE_CONTROLLER
	#define RPBDB_MEMORY_POOL_FILE_PAGE_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_MemoryPoolFilePageController*		RPbdb_MemoryPoolFilePageController_new(						RPbdb_MemoryPoolFile*					parent_memory_pool_file );

	void									RPbdb_MemoryPoolFilePageController_free(	RPbdb_MemoryPoolFilePageController** memory_pool_file_page_controller );
	RPbdb_MemoryPoolFilePageSettingsController*		RPbdb_MemoryPoolFilePageController_settingsController(	RPbdb_MemoryPoolFilePageController* memory_pool_file_page_controller );
	RPbdb_Environment*						RPbdb_MemoryPoolFilePageController_parentEnvironment(	RPbdb_MemoryPoolFilePageController* memory_pool_file_page_controller );

	RPbdb_MemoryPoolFilePage*				RPbdb_MemoryPoolFilePageController_retrievePageFromCache(	RPbdb_MemoryPoolFilePageController*		memory_pool_file_page_controller,
	 						 				  															db_pgno_t								page_number_address	);


#endif

