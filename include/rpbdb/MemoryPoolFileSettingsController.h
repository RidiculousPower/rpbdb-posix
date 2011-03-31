/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPBDB_MEMORY_POOL_FILE_SETTINGS_CONTROLLER
	#define RPBDB_MEMORY_POOL_FILE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_MemoryPoolFileSettingsController*		RPbdb_MemoryPoolFileSettingsController_new(											RPbdb_MemoryPoolSettingsController*			memory_pool_settings_controller );

	void										RPbdb_MemoryPoolFileSettingsController_free(										RPbdb_MemoryPoolFileSettingsController** memory_pool_file_settings_controller );
	RPbdb_Environment*					RPbdb_MemoryPoolFileSettingsController_parentEnvironment(				RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );
	int											RPbdb_MemoryPoolFileSettingsController_createWithInitialNullBytesNumbering(			RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										RPbdb_MemoryPoolFileSettingsController_setCreateWithInitialNullBytesNumbering(	RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	int											initial_null_bytes );

	uint8_t*									RPbdb_MemoryPoolFileSettingsController_fileID(										RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void											RPbdb_MemoryPoolFileSettingsController_setFileID(									RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																															uint8_t									file_id[ DB_FILE_ID_LEN ] );

	int											RPbdb_MemoryPoolFileSettingsController_fileType(									RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										RPbdb_MemoryPoolFileSettingsController_setFileType(									RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	int											file_type );

	int											RPbdb_MemoryPoolFileSettingsController_logSequenceNumberOffset(						RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										RPbdb_MemoryPoolFileSettingsController_setLogSequenceNumberOffset(					RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	int32_t										log_sequence_number_offset );

	uint64_t									RPbdb_MemoryPoolFileSettingsController_maxFileSizeInBytes(							RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	long										RPbdb_MemoryPoolFileSettingsController_maxFileSizeInKBytes(							RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	long										RPbdb_MemoryPoolFileSettingsController_maxFileSizeInMBytes(							RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	long										RPbdb_MemoryPoolFileSettingsController_maxFileSizeInGBytes(							RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										RPbdb_MemoryPoolFileSettingsController_setMaxFileSizeInBytes(						RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint64_t									max_file_size_in_bytes );
	void										RPbdb_MemoryPoolFileSettingsController_setMaxFileSizeInKBytes(						RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint32_t									size_in_kbytes );
	void										RPbdb_MemoryPoolFileSettingsController_setMaxFileSizeInMBytes(						RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint32_t									size_in_mbytes );
	void										RPbdb_MemoryPoolFileSettingsController_setMaxFileSizeInGBytes(						RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint32_t									size_in_gbytes );
	uint64_t RPbdb_MemoryPoolFileSettingsController_pageSizeInBytes( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );
	long RPbdb_MemoryPoolFileSettingsController_pageSizeInKBytes( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );
	void RPbdb_MemoryPoolFileSettingsController_setPageSizeInBytes(	RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint64_t																	page_size_in_bytes );
	void RPbdb_MemoryPoolFileSettingsController_setPageSizeInKBytes(	RPbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																	uint32_t 																size_in_kbytes );

	RPbdb_Data*											RPbdb_MemoryPoolFileSettingsController_cookie(										RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										RPbdb_MemoryPoolFileSettingsController_setCookie(									RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																														RPbdb_Data*								cookie );

	RPbdb_MemoryPoolFileCacheSettingsController* RPbdb_MemoryPoolFileSettingsController_cacheSettingsController( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );
	RPbdb_MemoryPoolFilePageSettingsController*					RPbdb_MemoryPoolFileSettingsController_pageSettingsController(			RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );

#endif

