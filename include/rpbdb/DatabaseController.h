/*
 *		RPbdb::DatabaseController
 *
 *
 */

#ifndef RPBDB_DATABASE_CONTROLLER
	#define RPBDB_DATABASE_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseController*	RPbdb_DatabaseController_new(						RPbdb_Environment*							parent_environment );

	void						RPbdb_DatabaseController_free(	RPbdb_DatabaseController** database_controller );
	RPbdb_DatabaseSettingsController*	RPbdb_DatabaseController_settingsController(	RPbdb_DatabaseController* database_controller );
	RPbdb_Environment*			RPbdb_DatabaseController_parentEnvironment(	RPbdb_DatabaseController* database_controller );

	RPbdb_Database*				RPbdb_DatabaseController_database(			RPbdb_DatabaseController*		database_controller, 
																															char*							database_name	);
	RPbdb_Database* RPbdb_DatabaseController_newDatabase(	RPbdb_DatabaseController*	database_controller, 
																											char*											database_name	);
	void							RPbdb_DatabaseController_closeAllDatabases(			RPbdb_DatabaseController*		database_controller );
	void							RPbdb_DatabaseController_freeAllDatabases(			RPbdb_DatabaseController*		database_controller );

#endif

