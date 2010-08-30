/*
 *		RPDB::MemoryPoolController::MemoryPoolFile::MemoryPoolFilePageController::MemoryPoolFilePage
 *
 *	
 */

#ifndef RPDB_MEMORY_POOL_FILE_PAGE
	#define RPDB_MEMORY_POOL_FILE_PAGE

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_MemoryPoolFilePage*								RPDB_MemoryPoolFilePage_new(									RPDB_MemoryPoolFilePageController*		memory_pool_file_page_controller );

	void													RPDB_MemoryPoolFilePage_free(	RPDB_MemoryPoolFilePage** memory_pool_file_page );
	RPDB_MemoryPoolFilePageSettingsController*				RPDB_MemoryPoolFilePage_settingsController(	RPDB_MemoryPoolFilePage* memory_pool_file_page );
	RPDB_Environment*								RPDB_MemoryPoolFilePage_parentEnvironment(	RPDB_MemoryPoolFilePage* memory_pool_file_page );

	RPDB_MemoryPoolFilePage*								RPDB_MemoryPoolFilePageController_writePageToCache(			RPDB_MemoryPoolFilePage*				memory_pool_file_page );


#endif

