/*
 *		RPDB::DatabaseController
 *
 *
 */

#ifndef RPDB_DATABASE_CONTROLLER
	#define RPDB_DATABASE_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseController*	RPDB_DatabaseController_new(						RPDB_Environment*							parent_environment );

	void						RPDB_DatabaseController_free(	RPDB_DatabaseController** database_controller );
	RPDB_DatabaseSettingsController*	RPDB_DatabaseController_settingsController(	RPDB_DatabaseController* database_controller );
	RPDB_Environment*			RPDB_DatabaseController_parentEnvironment(	RPDB_DatabaseController* database_controller );

	RPDB_Database*				RPDB_DatabaseController_database(			RPDB_DatabaseController*		database_controller, 
																															char*							database_name	);
	RPDB_Database* RPDB_DatabaseController_newDatabase(	RPDB_DatabaseController*	database_controller, 
																											char*											database_name	);
	void							RPDB_DatabaseController_closeAllDatabases(			RPDB_DatabaseController*		database_controller );
	void							RPDB_DatabaseController_freeAllDatabases(			RPDB_DatabaseController*		database_controller );

#endif

