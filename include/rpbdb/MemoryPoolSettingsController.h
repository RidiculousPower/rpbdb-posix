/*
 *		RPbdb:RPbdb_SettingsController:RPbdb_MemoryPoolSettingsController
 *
 *
 */

#ifndef RPBDB_MEMORY_POOL_SETTINGS_CONTROLLER
	#define RPBDB_MEMORY_POOL_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_MemoryPoolSettingsController*		RPbdb_MemoryPoolSettingsController_new(											RPbdb_SettingsController*				settings_controller );
	void									RPbdb_MemoryPoolSettingsController_free(									RPbdb_MemoryPoolSettingsController** memory_pool_settings_controller );
	RPbdb_Environment*				RPbdb_MemoryPoolSettingsController_parentEnvironment(			RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller );

	int									RPbdb_MemoryPoolSettingsController_on(											RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	BOOL									RPbdb_MemoryPoolSettingsController_off(											RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPbdb_MemoryPoolSettingsController_turnOn(										RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPbdb_MemoryPoolSettingsController_turnOff(										RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );

	int									RPbdb_MemoryPoolSettingsController_memoryMapping(								RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPbdb_MemoryPoolSettingsController_turnMemoryMappingOn(							RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPbdb_MemoryPoolSettingsController_turnMemoryMappingOff(						RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );

	int									RPbdb_MemoryPoolSettingsController_doNotWriteToTemporaryBackingFile(			RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPbdb_MemoryPoolSettingsController_turnDoNotWriteToTemporaryBackingFileOn(		RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPbdb_MemoryPoolSettingsController_turnDoNotWriteToTemporaryBackingFileOff(		RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );

	int									RPbdb_MemoryPoolSettingsController_removeFileWithLastReference(					RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPbdb_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOn(			RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPbdb_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOff(			RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );

	int									RPbdb_MemoryPoolSettingsController_pagesizeFactorMismatchShouldFail(			RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPbdb_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOn(		RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									RPbdb_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOff(		RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );

	RPbdb_MemoryPoolFileSettingsController*	RPbdb_MemoryPoolSettingsController_fileSettingsController(						RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
RPbdb_MemoryPoolReadWriteSettingsController* RPbdb_MemoryPoolSettingsController_readWriteSettingsController( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller );

#endif

