/*
 *		RPDB::SettingsController::RuntimeStorageSettingsController
 *
 *
 */

#ifndef RPDB_RUNTIMESTORAGESETTINGS_CONTROLLER
	#define RPDB_RUNTIMESTORAGESETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_RuntimeStorageSettingsController* RPDB_RuntimeStorageSettingsController_new( RPDB_RuntimeStorageController* parent_runtime_storage_controller );
	void											RPDB_RuntimeStorageSettingsController_free(									RPDB_RuntimeStorageSettingsController**		runtime_storage_settings_controller );
	RPDB_Environment*						RPDB_RuntimeStorageSettingsController_parentEnvironment(			RPDB_RuntimeStorageSettingsController*		runtime_storage_settings_controller );

	BOOL											RPDB_RuntimeStorageSettingsController_storeInApplicationMemory(				RPDB_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPDB_RuntimeStorageSettingsController_turnStoreInApplicationMemoryOn(			RPDB_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPDB_RuntimeStorageSettingsController_turnStoreInApplicationMemoryOff(			RPDB_RuntimeStorageSettingsController*		runtime_settings_controller );

	BOOL											RPDB_RuntimeStorageSettingsController_storeInSystemMemory(						RPDB_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPDB_RuntimeStorageSettingsController_turnStoreInSystemMemoryOn(				RPDB_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPDB_RuntimeStorageSettingsController_turnStoreInSystemMemoryOff(				RPDB_RuntimeStorageSettingsController*		runtime_settings_controller );

	BOOL											RPDB_RuntimeStorageSettingsController_storeOnDisk(								RPDB_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPDB_RuntimeStorageSettingsController_turnStoreOnDiskOn(						RPDB_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPDB_RuntimeStorageSettingsController_turnStoreOnDiskOff(						RPDB_RuntimeStorageSettingsController*		runtime_settings_controller );

	BOOL											RPDB_RuntimeStorageSettingsController_runtimeStorageActivityLogging(			RPDB_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPDB_RuntimeStorageSettingsController_turnRuntimeStorageActivityLoggingOn(		RPDB_RuntimeStorageSettingsController*		runtime_settings_controller );
	void											RPDB_RuntimeStorageSettingsController_turnRuntimeStorageActivityLoggingOff(	RPDB_RuntimeStorageSettingsController*		runtime_settings_controller );

	BOOL RPDB_RuntimeStorageSettingsController_automaticDefaultEnvironment( RPDB_RuntimeStorageSettingsController* runtime_settings_controller );
	void RPDB_RuntimeStorageSettingsController_turnAutomaticDefaultEnvironmentOn( RPDB_RuntimeStorageSettingsController* runtime_settings_controller );
	void RPDB_RuntimeStorageSettingsController_turnAutomaticDefaultEnvironmentOff( RPDB_RuntimeStorageSettingsController* runtime_settings_controller );

	RPDB_RuntimeStorageSettingsController*			RPDB_RuntimeStorageController_settingsController(								RPDB_RuntimeStorageController*				runtime_storage_controller );

#endif

