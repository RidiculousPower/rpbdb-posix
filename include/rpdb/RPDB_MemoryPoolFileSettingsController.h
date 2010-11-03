/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPDB_MEMORY_POOL_FILE_SETTINGS_CONTROLLER
	#define RPDB_MEMORY_POOL_FILE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_MemoryPoolFileSettingsController*		RPDB_MemoryPoolFileSettingsController_new(											RPDB_MemoryPoolSettingsController*			memory_pool_settings_controller );

	void										RPDB_MemoryPoolFileSettingsController_free(										RPDB_MemoryPoolFileSettingsController** memory_pool_file_settings_controller );
	RPDB_Environment*					RPDB_MemoryPoolFileSettingsController_parentEnvironment(				RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );
	int											RPDB_MemoryPoolFileSettingsController_createWithNumberInitialNullBytes(			RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										RPDB_MemoryPoolFileSettingsController_setReturnsCreateWithNumberInitialNullBytes(	RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	int											initial_null_bytes );

	uint8_t*											RPDB_MemoryPoolFileSettingsController_fileID(										RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void											RPDB_MemoryPoolFileSettingsController_setFileID(									RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint8_t*									file_id );

	int											RPDB_MemoryPoolFileSettingsController_fileType(									RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										RPDB_MemoryPoolFileSettingsController_setFileType(									RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	int											file_type );

	int											RPDB_MemoryPoolFileSettingsController_logSequenceNumberOffset(						RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										RPDB_MemoryPoolFileSettingsController_setLogSequenceNumberOffset(					RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	int32_t										log_sequence_number_offset );

	uint64_t									RPDB_MemoryPoolFileSettingsController_maxFileSizeInBytes(							RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	long										RPDB_MemoryPoolFileSettingsController_maxFileSizeInKBytes(							RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	long										RPDB_MemoryPoolFileSettingsController_maxFileSizeInMBytes(							RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	long										RPDB_MemoryPoolFileSettingsController_maxFileSizeInGBytes(							RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										RPDB_MemoryPoolFileSettingsController_setMaxFileSizeInBytes(						RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint64_t									max_file_size_in_bytes );
	void										RPDB_MemoryPoolFileSettingsController_setMaxFileSizeInKBytes(						RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint32_t									size_in_kbytes );
	void										RPDB_MemoryPoolFileSettingsController_setMaxFileSizeInMBytes(						RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint32_t									size_in_mbytes );
	void										RPDB_MemoryPoolFileSettingsController_setMaxFileSizeInGBytes(						RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint32_t									size_in_gbytes );
	uint64_t RPDB_MemoryPoolFileSettingsController_pageSizeInBytes( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );
	long RPDB_MemoryPoolFileSettingsController_pageSizeInKBytes( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );
	void RPDB_MemoryPoolFileSettingsController_setPageSizeInBytes(	RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint64_t																	page_size_in_bytes );
	void RPDB_MemoryPoolFileSettingsController_setPageSizeInKBytes(	RPDB_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																	uint32_t 																size_in_kbytes );

	RPDB_Record*											RPDB_MemoryPoolFileSettingsController_cookie(										RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										RPDB_MemoryPoolFileSettingsController_setCookie(									RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	RPDB_Record*								cookie );

	RPDB_MemoryPoolFileCacheSettingsController* RPDB_MemoryPoolFileSettingsController_cacheSettingsController( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );
	RPDB_MemoryPoolFilePageSettingsController*					RPDB_MemoryPoolFileSettingsController_pageSettingsController(			RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );

#endif

