/*
 *		Rbdb::RuntimeStorageController
 *
 *
 */

#ifndef RBDB_RUNTIME_STORAGE_CONTROLLER
	#define RBDB_RUNTIME_STORAGE_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_RuntimeStorageController*		Rbdb_RuntimeStorageController_sharedInstance();

	void								Rbdb_RuntimeStorageController_free(	Rbdb_RuntimeStorageController** runtime_storage_controller );
	Rbdb_RuntimeStorageSettingsController*		Rbdb_RuntimeStorageController_settingsController(	Rbdb_RuntimeStorageController*		runtime_storage_controller );
	Rbdb_Environment*			Rbdb_RuntimeStorageController_parentEnvironment(	Rbdb_RuntimeStorageController* runtime_storage_controller );

	Rbdb_RuntimeStorageController*		Rbdb_RuntimeStorageController_internal_initRuntimeEnvironment(						Rbdb_RuntimeStorageController*		runtime_storage_controller );
	void								Rbdb_RuntimeStorageController_internal_initRuntimeStoragesDatabases(					Rbdb_RuntimeStorageController*		runtime_storage_controller );
	void								Rbdb_RuntimeStorageController_internal_initRuntimeStoragesDatabaseAssociations(	Rbdb_RuntimeStorageController*		runtime_storage_controller );
	void								Rbdb_RuntimeStorageController_internal_initRuntimeStoragesCursors(					Rbdb_RuntimeStorageController*		runtime_storage_controller );
	Rbdb_Environment*					Rbdb_RuntimeStorageController_currentWorkingEnvironment(	Rbdb_RuntimeStorageController*		runtime_storage_controller );
	Rbdb_Environment* Rbdb_RuntimeStorageController_requireDefaultEnvironment(	Rbdb_RuntimeStorageController*		runtime_storage_controller );
	void					Rbdb_RuntimeStorageController_setCurrentWorkingEnvironment(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																								Rbdb_Environment*					environment );

	void Rbdb_RuntimeStorageController_internal_initEnvironmentAndDatabaseReferenceDatabases(	Rbdb_RuntimeStorageController*		runtime_storage_controller );
	Rbdb_Environment* Rbdb_RuntimeStorageController_environmentWithName(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																																					char*								environment_name	);

#endif

