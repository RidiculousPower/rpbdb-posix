/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPDB_MEMORY_POOL_READ_WRITE_SETTINGS_CONTROLLER
	#define RPDB_MEMORY_POOL_READ_WRITE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPDB_MemoryPoolReadWriteSettingsController*	RPDB_MemoryPoolReadWriteSettingsController_new(							RPDB_MemoryPoolSettingsController*					memory_pool_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_free(							RPDB_MemoryPoolReadWriteSettingsController** memory_pool_read_write_settings_controller );
	RPDB_Environment*						RPDB_MemoryPoolReadWriteSettingsController_parentEnvironment(	RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );

	int												RPDB_MemoryPoolReadWriteSettingsController_maxOpenFiles(					RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_setMaxOpenFiles(				RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller,
																																int													max_open_files );
	int												RPDB_MemoryPoolReadWriteSettingsController_maxSequentialWrites(			RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_setMaxSequentialWrites(			RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller, 
																																int													max_sequential_writes );
	int												RPDB_MemoryPoolReadWriteSettingsController_timeToSleepBeforeNextWrite(		RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_setTimeToSleepBeforeNextWrite(	RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller, 
																																db_timeout_t										time_to_sleep_before_next_write );
	int												RPDB_MemoryPoolReadWriteSettingsController_maxMappedDBSize(				RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_setMaxMappedDBSize(				RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller,
																																size_t												max_mapped_db_size );

	BOOL											RPDB_MemoryPoolReadWriteSettingsController_pagefaultSharedRegions(			RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOn(	RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOff(	RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller );

#endif

