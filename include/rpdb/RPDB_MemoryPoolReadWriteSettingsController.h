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
	void											RPDB_MemoryPoolReadWriteSettingsController_free(							RPDB_MemoryPoolReadWriteSettingsController** memory_pool_record_read_write_settings_controller );
	RPDB_Environment*						RPDB_MemoryPoolReadWriteSettingsController_parentEnvironment(	RPDB_MemoryPoolReadWriteSettingsController* memory_pool_record_read_write_settings_controller );

	int												RPDB_MemoryPoolReadWriteSettingsController_maxOpenFiles(					RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_setMaxOpenFiles(				RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller,
																																int													max_open_files );
	int												RPDB_MemoryPoolReadWriteSettingsController_maxSequentialWrites(			RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_setMaxSequentialWrites(			RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller, 
																																int													max_sequential_writes );
	int												RPDB_MemoryPoolReadWriteSettingsController_timeToSleepBeforeNextWrite(		RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_setTimeToSleepBeforeNextWrite(	RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller, 
																																db_timeout_t										time_to_sleep_before_next_write );
	size_t										RPDB_MemoryPoolReadWriteSettingsController_maxMappedDatabaseSize(				RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_setMaxMappedDatabaseSize(				RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller,
																																size_t												max_mapped_db_size );

	BOOL											RPDB_MemoryPoolReadWriteSettingsController_pagefaultSharedRegions(			RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOn(	RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											RPDB_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOff(	RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );

int RPDB_MemoryPoolReadWriteSettingsController_useSystemMemoryForStorage( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnUseSystemMemoryForStorageOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnUseSystemMemoryForStorageOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int RPDB_MemoryPoolReadWriteSettingsController_applicationHasExclusiveAccess( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int RPDB_MemoryPoolReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int RPDB_MemoryPoolReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int RPDB_MemoryPoolReadWriteSettingsController_applicationAllocatesMemory( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int RPDB_MemoryPoolReadWriteSettingsController_databaseFreesMemory( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int RPDB_MemoryPoolReadWriteSettingsController_doNotWriteToTemporaryBackingFile( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPDB_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );

BOOL RPDB_MemoryPoolReadWriteSettingsController_isInMemoryEnvironment( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );

#endif

