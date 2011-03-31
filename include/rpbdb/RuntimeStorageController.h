/*
 *		RPbdb::RuntimeStorageController
 *
 *
 */

#ifndef RPBDB_RUNTIME_STORAGE_CONTROLLER
	#define RPBDB_RUNTIME_STORAGE_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_RuntimeStorageController*		RPbdb_RuntimeStorageController_sharedInstance();

	void								RPbdb_RuntimeStorageController_free(	RPbdb_RuntimeStorageController** runtime_storage_controller );
	RPbdb_RuntimeStorageSettingsController*		RPbdb_RuntimeStorageController_settingsController(	RPbdb_RuntimeStorageController*		runtime_storage_controller );
	RPbdb_Environment*			RPbdb_RuntimeStorageController_parentEnvironment(	RPbdb_RuntimeStorageController* runtime_storage_controller );

	RPbdb_RuntimeStorageController*		RPbdb_RuntimeStorageController_internal_initRuntimeEnvironment(						RPbdb_RuntimeStorageController*		runtime_storage_controller );
	void								RPbdb_RuntimeStorageController_internal_initRuntimeStoragesDatabases(					RPbdb_RuntimeStorageController*		runtime_storage_controller );
	void								RPbdb_RuntimeStorageController_internal_initRuntimeStoragesDatabaseAssociations(	RPbdb_RuntimeStorageController*		runtime_storage_controller );
	void								RPbdb_RuntimeStorageController_internal_initRuntimeStoragesCursors(					RPbdb_RuntimeStorageController*		runtime_storage_controller );
	RPbdb_Environment*					RPbdb_RuntimeStorageController_currentWorkingEnvironment(	RPbdb_RuntimeStorageController*		runtime_storage_controller );
	RPbdb_Environment* RPbdb_RuntimeStorageController_requireDefaultEnvironment(	RPbdb_RuntimeStorageController*		runtime_storage_controller );
	void					RPbdb_RuntimeStorageController_setCurrentWorkingEnvironment(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																								RPbdb_Environment*					environment );

	void RPbdb_RuntimeStorageController_internal_initEnvironmentAndDatabaseReferenceDatabases(	RPbdb_RuntimeStorageController*		runtime_storage_controller );
	RPbdb_Environment* RPbdb_RuntimeStorageController_environmentWithName(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																																					char*								environment_name	);

#endif

