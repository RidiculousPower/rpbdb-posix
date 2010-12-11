/*
 *		Rbdb:Rbdb_SettingsController:Rbdb_MemoryPoolSettingsController
 *
 *
 */

#ifndef RBDB_MEMORY_POOL_SETTINGS_CONTROLLER
	#define RBDB_MEMORY_POOL_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_MemoryPoolSettingsController*		Rbdb_MemoryPoolSettingsController_new(											Rbdb_SettingsController*				settings_controller );
	void									Rbdb_MemoryPoolSettingsController_free(									Rbdb_MemoryPoolSettingsController** memory_pool_settings_controller );
	Rbdb_Environment*				Rbdb_MemoryPoolSettingsController_parentEnvironment(			Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller );

	int									Rbdb_MemoryPoolSettingsController_on(											Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	BOOL									Rbdb_MemoryPoolSettingsController_off(											Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									Rbdb_MemoryPoolSettingsController_turnOn(										Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									Rbdb_MemoryPoolSettingsController_turnOff(										Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );

	int									Rbdb_MemoryPoolSettingsController_memoryMapping(								Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									Rbdb_MemoryPoolSettingsController_turnMemoryMappingOn(							Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									Rbdb_MemoryPoolSettingsController_turnMemoryMappingOff(						Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );

	int									Rbdb_MemoryPoolSettingsController_doNotWriteToTemporaryBackingFile(			Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									Rbdb_MemoryPoolSettingsController_turnDoNotWriteToTemporaryBackingFileOn(		Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									Rbdb_MemoryPoolSettingsController_turnDoNotWriteToTemporaryBackingFileOff(		Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );

	int									Rbdb_MemoryPoolSettingsController_removeFileWithLastReference(					Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									Rbdb_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOn(			Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									Rbdb_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOff(			Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );

	int									Rbdb_MemoryPoolSettingsController_pagesizeFactorMismatchShouldFail(			Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									Rbdb_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOn(		Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
	void									Rbdb_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOff(		Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );

	Rbdb_MemoryPoolFileSettingsController*	Rbdb_MemoryPoolSettingsController_fileSettingsController(						Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
Rbdb_MemoryPoolReadWriteSettingsController* Rbdb_MemoryPoolSettingsController_readWriteSettingsController( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller );

#endif

