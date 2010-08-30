/*
 *		RPDB::MemoryPoolController::MemoryPoolFile
 *
 *
 */
 
#ifndef RPDB_MEMORY_POOL_FILE
	#define RPDB_MEMORY_POOL_FILE

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_MemoryPoolFile*		RPDB_MemoryPoolFile_new(					RPDB_MemoryPoolFileController*				parent_memory_pool_file_controller );

	void						RPDB_MemoryPoolFile_free(	RPDB_MemoryPoolFile** memory_pool_file );
	RPDB_MemoryPoolFileSettingsController*		RPDB_MemoryPoolFile_settingsController(	RPDB_MemoryPoolFile* memory_pool_file );
	RPDB_Environment*					RPDB_MemoryPoolFile_parentEnvironment(	RPDB_MemoryPoolFile* memory_pool_file );

	void						RPDB_MemoryPoolFile_sync(					RPDB_MemoryPoolFile*						memory_pool_file );
	void						RPDB_MemoryPoolFile_close(					RPDB_MemoryPoolFile*						memory_pool_file );

	RPDB_MemoryPoolFileSettingsController*						RPDB_MemoryPoolFile_settingsController(	RPDB_MemoryPoolFile*						memory_pool_file );

#endif

