/*
 *		RPDB:RPDB_SettingsController:RPDB_MemoryPoolSettingsController
 *
 *
 */

#ifndef RPDB_MEMORY_POOL_SETTINGS_CONTROLLER
	#define RPDB_MEMORY_POOL_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_MemoryPoolSettingsController*		RPDB_MemoryPoolSettingsController_new(											RPDB_SettingsController*				settings_controller );
	void									RPDB_MemoryPoolSettingsController_free(									RPDB_MemoryPoolSettingsController** memory_pool_settings_controller );
	RPDB_Environment*				RPDB_MemoryPoolSettingsController_parentEnvironment(			RPDB_MemoryPoolSettingsController* memory_pool_settings_controller );

	int									RPDB_MemoryPoolSettingsController_on(											RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
	BOOL									RPDB_MemoryPoolSettingsController_off(											RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPDB_MemoryPoolSettingsController_turnOn(										RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPDB_MemoryPoolSettingsController_turnOff(										RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );

	int									RPDB_MemoryPoolSettingsController_memoryMapping(								RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPDB_MemoryPoolSettingsController_turnMemoryMappingOn(							RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPDB_MemoryPoolSettingsController_turnMemoryMappingOff(						RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );

	int									RPDB_MemoryPoolSettingsController_doNotWriteToTemporaryBackingFile(			RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPDB_MemoryPoolSettingsController_turnDoNotWriteToTemporaryBackingFileOn(		RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPDB_MemoryPoolSettingsController_turnDoNotWriteToTemporaryBackingFileOff(		RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );

	int									RPDB_MemoryPoolSettingsController_removeFileWithLastReference(					RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPDB_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOn(			RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPDB_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOff(			RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );

	int									RPDB_MemoryPoolSettingsController_pagesizeFactorMismatchShouldFail(			RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPDB_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOn(		RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPDB_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOff(		RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );

	RPDB_MemoryPoolFileSettingsController*	RPDB_MemoryPoolSettingsController_fileSettingsController(						RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
RPDB_MemoryPoolReadWriteSettingsController* RPDB_MemoryPoolSettingsController_readWriteSettingsController( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller );

#endif

