/*
 *		Rbdb::DatabaseController
 *
 *
 */

#ifndef Rbdb_DATABASE_CONTROLLER
	#define Rbdb_DATABASE_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseController*	Rbdb_DatabaseController_new(						Rbdb_Environment*							parent_environment );

	void						Rbdb_DatabaseController_free(	Rbdb_DatabaseController** database_controller );
	Rbdb_DatabaseSettingsController*	Rbdb_DatabaseController_settingsController(	Rbdb_DatabaseController* database_controller );
	Rbdb_Environment*			Rbdb_DatabaseController_parentEnvironment(	Rbdb_DatabaseController* database_controller );

	Rbdb_Database*				Rbdb_DatabaseController_database(			Rbdb_DatabaseController*		database_controller, 
																															char*							database_name	);
	Rbdb_Database* Rbdb_DatabaseController_newDatabase(	Rbdb_DatabaseController*	database_controller, 
																											char*											database_name	);
	void							Rbdb_DatabaseController_closeAllDatabases(			Rbdb_DatabaseController*		database_controller );
	void							Rbdb_DatabaseController_freeAllDatabases(			Rbdb_DatabaseController*		database_controller );

#endif

