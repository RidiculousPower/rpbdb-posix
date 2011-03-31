/*

	RPbdb by Asher (asher at ridiculous power dot com).
	All rights reserved. Licensing for RPbdb is to be construed as an independent extension of licensing for Oracle's Berkeley DB.
	This provides licensing under one of two schemas (as outlined by Oracle: 
	http://www.oracle.com/technology/software/products/berkeley-db/htdocs/licensing.html):
	
	* Open Source (Any distributed software utilizing RPbdb must also distribute its source openly). 
	* Commercial License (Licensing arrangement to be determined, contact Ridiculous Power).
		
	C and Ruby Wrapper for Oracle's (formerly Sleepcat's) Berkeley DB (BDB).  

*/

#ifndef RPBDB_ENVIRONMENT
	#define RPBDB_ENVIRONMENT

	 /***************
	 *  Includes  *
	 ****************/

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
	
	RPbdb_Environment*								RPbdb_Environment_new(	char*		environment_home_directory );

	void											RPbdb_Environment_free(	RPbdb_Environment** environment );
	
	void											RPbdb_Environment_initDefaults( RPbdb_Environment* environment );
	
	RPbdb_Environment*								RPbdb_Environment_initForStorageInMemory(		RPbdb_Environment*		environment );

	RPbdb_Environment*								RPbdb_Environment_open(							RPbdb_Environment*		environment );
	BOOL											RPbdb_Environment_isOpen( RPbdb_Environment* environment );
	char* RPbdb_Environment_homeDirectory( RPbdb_Environment* environment );
	RPbdb_Environment*								RPbdb_Environment_close(						RPbdb_Environment*		environment );

	RPbdb_Environment*								RPbdb_Environment_erase(						RPbdb_Environment*		environment );
	char*											RPbdb_Environment_name( RPbdb_Environment* environment );
	void RPbdb_Environment_setName(	RPbdb_Environment*		environment,
																		char*								name );


	void											RPbdb_Environment_checkForEnvironmentFailure( RPbdb_Environment* environment );


	RPbdb_ErrorController*				RPbdb_Environment_errorController(				RPbdb_Environment*		environment );
	RPbdb_DatabaseController*			RPbdb_Environment_databaseController(			RPbdb_Environment*		environment );
	RPbdb_LockController*				RPbdb_Environment_lockController(				RPbdb_Environment*		environment );
	RPbdb_MemoryPoolController*			RPbdb_Environment_memoryPoolController(			RPbdb_Environment*		environment );
	RPbdb_MutexController*				RPbdb_Environment_mutexController(				RPbdb_Environment*		environment );
	RPbdb_ReplicationController*		RPbdb_Environment_replicationController(		RPbdb_Environment*		environment );
//	RPbdb_ObjectController*				RPbdb_Environment_objectController(				RPbdb_Environment*		environment );
//	RPbdb_Controller*			RPbdb_Environment_controllerController(			RPbdb_Environment*		environment );
	RPbdb_LogController*				RPbdb_Environment_logController(				RPbdb_Environment*		environment );
	RPbdb_DatabaseSequenceController*	RPbdb_Environment_databaseSequenceController(	RPbdb_Environment*		environment );
//	RPbdb_StatusController*				RPbdb_Environment_statusController(				RPbdb_Environment*		environment );
	RPbdb_TransactionController*		RPbdb_Environment_transactionController(		RPbdb_Environment*		environment );
	RPbdb_RuntimeStorageController*		RPbdb_Environment_runtimeStorageController(		RPbdb_Environment*		environment );

	RPbdb_SettingsController*			RPbdb_Environment_settingsController(			RPbdb_Environment*		environment );

#endif
