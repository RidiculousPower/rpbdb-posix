/*
 *		Rbdb::MemoryPoolController::MemoryPoolFile::MemoryPoolFilePageController::MemoryPoolFilePage
 *
 *	
 */

#ifndef Rbdb_MEMORY_POOL_FILE_PAGE
	#define Rbdb_MEMORY_POOL_FILE_PAGE

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_MemoryPoolFilePage*								Rbdb_MemoryPoolFilePage_new(									Rbdb_MemoryPoolFilePageController*		memory_pool_file_page_controller );

	void													Rbdb_MemoryPoolFilePage_free(	Rbdb_MemoryPoolFilePage** memory_pool_file_page );
	Rbdb_MemoryPoolFilePageSettingsController*				Rbdb_MemoryPoolFilePage_settingsController(	Rbdb_MemoryPoolFilePage* memory_pool_file_page );
	Rbdb_Environment*								Rbdb_MemoryPoolFilePage_parentEnvironment(	Rbdb_MemoryPoolFilePage* memory_pool_file_page );

	Rbdb_MemoryPoolFilePage*								Rbdb_MemoryPoolFilePageController_writePageToCache(			Rbdb_MemoryPoolFilePage*				memory_pool_file_page );


#endif

