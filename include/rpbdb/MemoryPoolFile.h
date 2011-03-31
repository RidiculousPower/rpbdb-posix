/*
 *		RPbdb::MemoryPoolController::MemoryPoolFile
 *
 *
 */
 
#ifndef RPBDB_MEMORY_POOL_FILE
	#define RPBDB_MEMORY_POOL_FILE

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_MemoryPoolFile*		RPbdb_MemoryPoolFile_new(					RPbdb_MemoryPoolFileController*				parent_memory_pool_file_controller );

	void						RPbdb_MemoryPoolFile_free(	RPbdb_MemoryPoolFile** memory_pool_file );
	RPbdb_Environment*					RPbdb_MemoryPoolFile_parentEnvironment(	RPbdb_MemoryPoolFile* memory_pool_file );

	void						RPbdb_MemoryPoolFile_sync(					RPbdb_MemoryPoolFile*						memory_pool_file );
	void						RPbdb_MemoryPoolFile_close(					RPbdb_MemoryPoolFile*						memory_pool_file );

	RPbdb_MemoryPoolFileSettingsController*						RPbdb_MemoryPoolFile_settingsController(	RPbdb_MemoryPoolFile*						memory_pool_file );

#endif

