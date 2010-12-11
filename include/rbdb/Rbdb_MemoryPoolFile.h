/*
 *		Rbdb::MemoryPoolController::MemoryPoolFile
 *
 *
 */
 
#ifndef RBDB_MEMORY_POOL_FILE
	#define RBDB_MEMORY_POOL_FILE

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_MemoryPoolFile*		Rbdb_MemoryPoolFile_new(					Rbdb_MemoryPoolFileController*				parent_memory_pool_file_controller );

	void						Rbdb_MemoryPoolFile_free(	Rbdb_MemoryPoolFile** memory_pool_file );
	Rbdb_Environment*					Rbdb_MemoryPoolFile_parentEnvironment(	Rbdb_MemoryPoolFile* memory_pool_file );

	void						Rbdb_MemoryPoolFile_sync(					Rbdb_MemoryPoolFile*						memory_pool_file );
	void						Rbdb_MemoryPoolFile_close(					Rbdb_MemoryPoolFile*						memory_pool_file );

	Rbdb_MemoryPoolFileSettingsController*						Rbdb_MemoryPoolFile_settingsController(	Rbdb_MemoryPoolFile*						memory_pool_file );

#endif

