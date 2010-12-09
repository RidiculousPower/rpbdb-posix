/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef Rbdb_MEMORY_POOL_READ_WRITE_SETTINGS_CONTROLLER
	#define Rbdb_MEMORY_POOL_READ_WRITE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	Rbdb_MemoryPoolReadWriteSettingsController*	Rbdb_MemoryPoolReadWriteSettingsController_new(							Rbdb_MemoryPoolSettingsController*					memory_pool_settings_controller );
	void											Rbdb_MemoryPoolReadWriteSettingsController_free(							Rbdb_MemoryPoolReadWriteSettingsController** memory_pool_record_read_write_settings_controller );
	Rbdb_Environment*						Rbdb_MemoryPoolReadWriteSettingsController_parentEnvironment(	Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_record_read_write_settings_controller );

	int												Rbdb_MemoryPoolReadWriteSettingsController_maxOpenFiles(					Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											Rbdb_MemoryPoolReadWriteSettingsController_setMaxOpenFiles(				Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller,
																																int													max_open_files );
	int												Rbdb_MemoryPoolReadWriteSettingsController_maxSequentialWrites(			Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											Rbdb_MemoryPoolReadWriteSettingsController_setMaxSequentialWrites(			Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller, 
																																int													max_sequential_writes );
	int												Rbdb_MemoryPoolReadWriteSettingsController_timeToSleepBeforeNextWrite(		Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											Rbdb_MemoryPoolReadWriteSettingsController_setTimeToSleepBeforeNextWrite(	Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller, 
																																db_timeout_t										time_to_sleep_before_next_write );
	size_t										Rbdb_MemoryPoolReadWriteSettingsController_maxMappedDatabaseSize(				Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											Rbdb_MemoryPoolReadWriteSettingsController_setMaxMappedDatabaseSize(				Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller,
																																size_t												max_mapped_db_size );

	BOOL											Rbdb_MemoryPoolReadWriteSettingsController_pagefaultSharedRegions(			Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											Rbdb_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOn(	Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );
	void											Rbdb_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOff(	Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_record_read_write_settings_controller );

int Rbdb_MemoryPoolReadWriteSettingsController_useSystemMemoryForStorage( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnUseSystemMemoryForStorageOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnUseSystemMemoryForStorageOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int Rbdb_MemoryPoolReadWriteSettingsController_applicationHasExclusiveAccess( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int Rbdb_MemoryPoolReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int Rbdb_MemoryPoolReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int Rbdb_MemoryPoolReadWriteSettingsController_applicationAllocatesMemory( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int Rbdb_MemoryPoolReadWriteSettingsController_databaseFreesMemory( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
int Rbdb_MemoryPoolReadWriteSettingsController_doNotWriteToTemporaryBackingFile( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );

BOOL Rbdb_MemoryPoolReadWriteSettingsController_isInMemoryEnvironment( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller );

#endif

