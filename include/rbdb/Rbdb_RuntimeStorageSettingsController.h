/*
 *		Rbdb::SettingsController::RuntimeStorageSettingsController
 *
 *
 */

#ifndef RBDB_RUNTIMESTORAGESETTINGS_CONTROLLER
	#define RBDB_RUNTIMESTORAGESETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_RuntimeStorageSettingsController* Rbdb_RuntimeStorageSettingsController_new( Rbdb_RuntimeStorageController* parent_runtime_storage_controller );
	void											Rbdb_RuntimeStorageSettingsController_free(									Rbdb_RuntimeStorageSettingsController**		runtime_storage_settings_controller );
	Rbdb_Environment*						Rbdb_RuntimeStorageSettingsController_parentEnvironment(			Rbdb_RuntimeStorageSettingsController*		runtime_storage_settings_controller );

	BOOL											Rbdb_RuntimeStorageSettingsController_storeInApplicationMemory(				Rbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											Rbdb_RuntimeStorageSettingsController_turnStoreInApplicationMemoryOn(			Rbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											Rbdb_RuntimeStorageSettingsController_turnStoreInApplicationMemoryOff(			Rbdb_RuntimeStorageSettingsController*		runtime_settings_controller );

	BOOL											Rbdb_RuntimeStorageSettingsController_storeInSystemMemory(						Rbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											Rbdb_RuntimeStorageSettingsController_turnStoreInSystemMemoryOn(				Rbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											Rbdb_RuntimeStorageSettingsController_turnStoreInSystemMemoryOff(				Rbdb_RuntimeStorageSettingsController*		runtime_settings_controller );

	BOOL											Rbdb_RuntimeStorageSettingsController_storeOnDisk(								Rbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											Rbdb_RuntimeStorageSettingsController_turnStoreOnDiskOn(						Rbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											Rbdb_RuntimeStorageSettingsController_turnStoreOnDiskOff(						Rbdb_RuntimeStorageSettingsController*		runtime_settings_controller );

	BOOL											Rbdb_RuntimeStorageSettingsController_runtimeStorageActivityLogging(			Rbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											Rbdb_RuntimeStorageSettingsController_turnRuntimeStorageActivityLoggingOn(		Rbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											Rbdb_RuntimeStorageSettingsController_turnRuntimeStorageActivityLoggingOff(	Rbdb_RuntimeStorageSettingsController*		runtime_settings_controller );

	BOOL Rbdb_RuntimeStorageSettingsController_automaticDefaultEnvironment( Rbdb_RuntimeStorageSettingsController* runtime_settings_controller );
	void Rbdb_RuntimeStorageSettingsController_turnAutomaticDefaultEnvironmentOn( Rbdb_RuntimeStorageSettingsController* runtime_settings_controller );
	void Rbdb_RuntimeStorageSettingsController_turnAutomaticDefaultEnvironmentOff( Rbdb_RuntimeStorageSettingsController* runtime_settings_controller );

	Rbdb_RuntimeStorageSettingsController*			Rbdb_RuntimeStorageController_settingsController(								Rbdb_RuntimeStorageController*				runtime_storage_controller );

#endif

