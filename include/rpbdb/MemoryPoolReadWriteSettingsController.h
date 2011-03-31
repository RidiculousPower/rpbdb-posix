/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPBDB_MEMORY_POOL_READ_WRITE_SETTINGS_CONTROLLER
	#define RPBDB_MEMORY_POOL_READ_WRITE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPbdb_MemoryPoolReadWriteSettingsController*	RPbdb_MemoryPoolReadWriteSettingsController_new(							RPbdb_MemoryPoolSettingsController*					memory_pool_settings_controller );
	void											RPbdb_MemoryPoolReadWriteSettingsController_free(							RPbdb_MemoryPoolReadWriteSettingsController** memory_pool_record_read_write_settings_controller );
	RPbdb_Environment*						RPbdb_MemoryPoolReadWriteSettingsController_parentEnvironment(	RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_record_read_write_settings_controller );

	int												RPbdb_MemoryPoolReadWriteSettingsController_maxOpenFiles(					RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											RPbdb_MemoryPoolReadWriteSettingsController_setMaxOpenFiles(				RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller,
																																int													max_open_files );
	int												RPbdb_MemoryPoolReadWriteSettingsController_maxSequentialWrites(			RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											RPbdb_MemoryPoolReadWriteSettingsController_setMaxSequentialWrites(			RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller, 
																																int													max_sequential_writes );
	int												RPbdb_MemoryPoolReadWriteSettingsController_timeToSleepBeforeNextWrite(		RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											RPbdb_MemoryPoolReadWriteSettingsController_setTimeToSleepBeforeNextWrite(	RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller, 
																																db_timeout_t										time_to_sleep_before_next_write );
	size_t										RPbdb_MemoryPoolReadWriteSettingsController_maxMappedDatabaseSize(				RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											RPbdb_MemoryPoolReadWriteSettingsController_setMaxMappedDatabaseSize(				RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller,
																																size_t												max_mapped_db_size );

	BOOL											RPbdb_MemoryPoolReadWriteSettingsController_pagefaultSharedRegions(			RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											RPbdb_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOn(	RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											RPbdb_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOff(	RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );

int RPbdb_MemoryPoolReadWriteSettingsController_useSystemMemoryForStorage( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnUseSystemMemoryForStorageOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnUseSystemMemoryForStorageOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int RPbdb_MemoryPoolReadWriteSettingsController_applicationHasExclusiveAccess( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int RPbdb_MemoryPoolReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int RPbdb_MemoryPoolReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int RPbdb_MemoryPoolReadWriteSettingsController_applicationAllocatesMemory( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int RPbdb_MemoryPoolReadWriteSettingsController_databaseFreesMemory( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int RPbdb_MemoryPoolReadWriteSettingsController_doNotWriteToTemporaryBackingFile( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );

BOOL RPbdb_MemoryPoolReadWriteSettingsController_isInMemoryEnvironment( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );

#endif

