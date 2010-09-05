/*
 *		RPDB::RuntimeStorageController
 *
 *
 */

#ifndef RPDB_RUNTIME_STORAGE_CONTROLLER
	#define RPDB_RUNTIME_STORAGE_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_RuntimeStorageController*		RPDB_RuntimeStorageController_sharedInstance();

	void								RPDB_RuntimeStorageController_free(	RPDB_RuntimeStorageController** runtime_storage_controller );
	RPDB_RuntimeStorageSettingsController*		RPDB_RuntimeStorageController_settingsController(	RPDB_RuntimeStorageController*		runtime_storage_controller );
	RPDB_Environment*			RPDB_RuntimeStorageController_parentEnvironment(	RPDB_RuntimeStorageController* runtime_storage_controller );

	RPDB_RuntimeStorageController*		RPDB_RuntimeStorageController_internal_initRuntimeEnvironment(						RPDB_RuntimeStorageController*		runtime_storage_controller );
	void								RPDB_RuntimeStorageController_internal_initRuntimeStoragesDatabases(					RPDB_RuntimeStorageController*		runtime_storage_controller );
	void								RPDB_RuntimeStorageController_internal_initRuntimeStoragesDatabaseAssociations(	RPDB_RuntimeStorageController*		runtime_storage_controller );
	void								RPDB_RuntimeStorageController_internal_initRuntimeStoragesCursors(					RPDB_RuntimeStorageController*		runtime_storage_controller );
	RPDB_Environment*					RPDB_RuntimeStorageController_currentWorkingEnvironment(	RPDB_RuntimeStorageController*		runtime_storage_controller );
	RPDB_Environment* RPDB_RuntimeStorageController_requireDefaultEnvironment(	RPDB_RuntimeStorageController*		runtime_storage_controller );
	void					RPDB_RuntimeStorageController_setCurrentWorkingEnvironment(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																								RPDB_Environment*					environment );

	void RPDB_RuntimeStorageController_internal_initEnvironmentAndDatabaseReferenceDatabases(	RPDB_RuntimeStorageController*		runtime_storage_controller );
	RPDB_Environment* RPDB_RuntimeStorageController_environmentWithName(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																																					char*								environment_name	);

#endif

