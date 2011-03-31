/*
 *		RPbdb::MemoryPoolController::MemoryPoolFile::MemoryPoolFilePageController::MemoryPoolFilePage
 *
 *	
 */

#ifndef RPBDB_MEMORY_POOL_FILE_PAGE
	#define RPBDB_MEMORY_POOL_FILE_PAGE

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_MemoryPoolFilePage*								RPbdb_MemoryPoolFilePage_new(									RPbdb_MemoryPoolFilePageController*		memory_pool_file_page_controller );

	void													RPbdb_MemoryPoolFilePage_free(	RPbdb_MemoryPoolFilePage** memory_pool_file_page );
	RPbdb_MemoryPoolFilePageSettingsController*				RPbdb_MemoryPoolFilePage_settingsController(	RPbdb_MemoryPoolFilePage* memory_pool_file_page );
	RPbdb_Environment*								RPbdb_MemoryPoolFilePage_parentEnvironment(	RPbdb_MemoryPoolFilePage* memory_pool_file_page );

	RPbdb_MemoryPoolFilePage*								RPbdb_MemoryPoolFilePageController_writePageToCache(			RPbdb_MemoryPoolFilePage*				memory_pool_file_page );


#endif

