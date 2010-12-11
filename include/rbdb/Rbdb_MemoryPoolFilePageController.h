/*
 *		Rbdb::MemoryPoolController::MemoryPoolFile::MemoryPoolFilePageController
 *
 *	
 */

#ifndef RBDB_MEMORY_POOL_FILE_PAGE_CONTROLLER
	#define RBDB_MEMORY_POOL_FILE_PAGE_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_MemoryPoolFilePageController*		Rbdb_MemoryPoolFilePageController_new(						Rbdb_MemoryPoolFile*					parent_memory_pool_file );

	void									Rbdb_MemoryPoolFilePageController_free(	Rbdb_MemoryPoolFilePageController** memory_pool_file_page_controller );
	Rbdb_MemoryPoolFilePageSettingsController*		Rbdb_MemoryPoolFilePageController_settingsController(	Rbdb_MemoryPoolFilePageController* memory_pool_file_page_controller );
	Rbdb_Environment*						Rbdb_MemoryPoolFilePageController_parentEnvironment(	Rbdb_MemoryPoolFilePageController* memory_pool_file_page_controller );

	Rbdb_MemoryPoolFilePage*				Rbdb_MemoryPoolFilePageController_retrievePageFromCache(	Rbdb_MemoryPoolFilePageController*		memory_pool_file_page_controller,
	 						 				  															db_pgno_t								page_number_address	);


#endif

