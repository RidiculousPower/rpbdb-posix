/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef Rbdb_MEMORY_POOL_FILE_SETTINGS_CONTROLLER
	#define Rbdb_MEMORY_POOL_FILE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_MemoryPoolFileSettingsController*		Rbdb_MemoryPoolFileSettingsController_new(											Rbdb_MemoryPoolSettingsController*			memory_pool_settings_controller );

	void										Rbdb_MemoryPoolFileSettingsController_free(										Rbdb_MemoryPoolFileSettingsController** memory_pool_file_settings_controller );
	Rbdb_Environment*					Rbdb_MemoryPoolFileSettingsController_parentEnvironment(				Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );
	int											Rbdb_MemoryPoolFileSettingsController_createWithInitialNullBytesNumbering(			Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										Rbdb_MemoryPoolFileSettingsController_setCreateWithInitialNullBytesNumbering(	Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	int											initial_null_bytes );

	uint8_t*									Rbdb_MemoryPoolFileSettingsController_fileID(										Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void											Rbdb_MemoryPoolFileSettingsController_setFileID(									Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																															uint8_t									file_id[ DB_FILE_ID_LEN ] );

	int											Rbdb_MemoryPoolFileSettingsController_fileType(									Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										Rbdb_MemoryPoolFileSettingsController_setFileType(									Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	int											file_type );

	int											Rbdb_MemoryPoolFileSettingsController_logSequenceNumberOffset(						Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										Rbdb_MemoryPoolFileSettingsController_setLogSequenceNumberOffset(					Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	int32_t										log_sequence_number_offset );

	uint64_t									Rbdb_MemoryPoolFileSettingsController_maxFileSizeInBytes(							Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	long										Rbdb_MemoryPoolFileSettingsController_maxFileSizeInKBytes(							Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	long										Rbdb_MemoryPoolFileSettingsController_maxFileSizeInMBytes(							Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	long										Rbdb_MemoryPoolFileSettingsController_maxFileSizeInGBytes(							Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										Rbdb_MemoryPoolFileSettingsController_setMaxFileSizeInBytes(						Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint64_t									max_file_size_in_bytes );
	void										Rbdb_MemoryPoolFileSettingsController_setMaxFileSizeInKBytes(						Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint32_t									size_in_kbytes );
	void										Rbdb_MemoryPoolFileSettingsController_setMaxFileSizeInMBytes(						Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint32_t									size_in_mbytes );
	void										Rbdb_MemoryPoolFileSettingsController_setMaxFileSizeInGBytes(						Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint32_t									size_in_gbytes );
	uint64_t Rbdb_MemoryPoolFileSettingsController_pageSizeInBytes( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );
	long Rbdb_MemoryPoolFileSettingsController_pageSizeInKBytes( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );
	void Rbdb_MemoryPoolFileSettingsController_setPageSizeInBytes(	Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint64_t																	page_size_in_bytes );
	void Rbdb_MemoryPoolFileSettingsController_setPageSizeInKBytes(	Rbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																	uint32_t 																size_in_kbytes );

	Rbdb_Data*											Rbdb_MemoryPoolFileSettingsController_cookie(										Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller );
	void										Rbdb_MemoryPoolFileSettingsController_setCookie(									Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																														Rbdb_Data*								cookie );

	Rbdb_MemoryPoolFileCacheSettingsController* Rbdb_MemoryPoolFileSettingsController_cacheSettingsController( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );
	Rbdb_MemoryPoolFilePageSettingsController*					Rbdb_MemoryPoolFileSettingsController_pageSettingsController(			Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );

#endif

