/*
 *		RPbdb::SettingsController::RuntimeStorageSettingsController
 *
 *
 */

#ifndef RPBDB_RUNTIMESTORAGESETTINGS_CONTROLLER
	#define RPBDB_RUNTIMESTORAGESETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_RuntimeStorageSettingsController* RPbdb_RuntimeStorageSettingsController_new( RPbdb_RuntimeStorageController* parent_runtime_storage_controller );
	void											RPbdb_RuntimeStorageSettingsController_free(									RPbdb_RuntimeStorageSettingsController**		runtime_storage_settings_controller );
	RPbdb_Environment*						RPbdb_RuntimeStorageSettingsController_parentEnvironment(			RPbdb_RuntimeStorageSettingsController*		runtime_storage_settings_controller );

	BOOL											RPbdb_RuntimeStorageSettingsController_storeInApplicationMemory(				RPbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPbdb_RuntimeStorageSettingsController_turnStoreInApplicationMemoryOn(			RPbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPbdb_RuntimeStorageSettingsController_turnStoreInApplicationMemoryOff(			RPbdb_RuntimeStorageSettingsController*		runtime_settings_controller );

	BOOL											RPbdb_RuntimeStorageSettingsController_storeInSystemMemory(						RPbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPbdb_RuntimeStorageSettingsController_turnStoreInSystemMemoryOn(				RPbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPbdb_RuntimeStorageSettingsController_turnStoreInSystemMemoryOff(				RPbdb_RuntimeStorageSettingsController*		runtime_settings_controller );

	BOOL											RPbdb_RuntimeStorageSettingsController_storeOnDisk(								RPbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPbdb_RuntimeStorageSettingsController_turnStoreOnDiskOn(						RPbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPbdb_RuntimeStorageSettingsController_turnStoreOnDiskOff(						RPbdb_RuntimeStorageSettingsController*		runtime_settings_controller );

	BOOL											RPbdb_RuntimeStorageSettingsController_runtimeStorageActivityLogging(			RPbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPbdb_RuntimeStorageSettingsController_turnRuntimeStorageActivityLoggingOn(		RPbdb_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPbdb_RuntimeStorageSettingsController_turnRuntimeStorageActivityLoggingOff(	RPbdb_RuntimeStorageSettingsController*		runtime_settings_controller );

	BOOL RPbdb_RuntimeStorageSettingsController_automaticDefaultEnvironment( RPbdb_RuntimeStorageSettingsController* runtime_settings_controller );
	void RPbdb_RuntimeStorageSettingsController_turnAutomaticDefaultEnvironmentOn( RPbdb_RuntimeStorageSettingsController* runtime_settings_controller );
	void RPbdb_RuntimeStorageSettingsController_turnAutomaticDefaultEnvironmentOff( RPbdb_RuntimeStorageSettingsController* runtime_settings_controller );

	RPbdb_RuntimeStorageSettingsController*			RPbdb_RuntimeStorageController_settingsController(								RPbdb_RuntimeStorageController*				runtime_storage_controller );

#endif

