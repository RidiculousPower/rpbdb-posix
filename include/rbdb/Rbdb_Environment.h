/*

	Rbdb by Asher (asher at ridiculous power dot com).
	All rights reserved. Licensing for Rbdb is to be construed as an independent extension of licensing for Oracle's Berkeley DB.
	This provides licensing under one of two schemas (as outlined by Oracle: 
	http://www.oracle.com/technology/software/products/berkeley-db/htdocs/licensing.html):
	
	* Open Source (Any distributed software utilizing Rbdb must also distribute its source openly). 
	* Commercial License (Licensing arrangement to be determined, contact Ridiculous Power).
		
	C and Ruby Wrapper for Oracle's (formerly Sleepcat's) Berkeley DB (BDB).  

*/

#ifndef RBDB_ENVIRONMENT
	#define RBDB_ENVIRONMENT

	 /***************
	 *  Includes  *
	 ****************/

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
	
	Rbdb_Environment*								Rbdb_Environment_new(	char*		environment_home_directory );

	void											Rbdb_Environment_free(	Rbdb_Environment** environment );
	
	void											Rbdb_Environment_initDefaults( Rbdb_Environment* environment );
	
	Rbdb_Environment*								Rbdb_Environment_initForStorageInMemory(		Rbdb_Environment*		environment );

	Rbdb_Environment*								Rbdb_Environment_open(							Rbdb_Environment*		environment );
	BOOL											Rbdb_Environment_isOpen( Rbdb_Environment* environment );
	char* Rbdb_Environment_homeDirectory( Rbdb_Environment* environment );
	Rbdb_Environment*								Rbdb_Environment_close(						Rbdb_Environment*		environment );

	Rbdb_Environment*								Rbdb_Environment_erase(						Rbdb_Environment*		environment );
	char*											Rbdb_Environment_name( Rbdb_Environment* environment );
	void Rbdb_Environment_setName(	Rbdb_Environment*		environment,
																		char*								name );


	void											Rbdb_Environment_checkForEnvironmentFailure( Rbdb_Environment* environment );


	Rbdb_ErrorController*				Rbdb_Environment_errorController(				Rbdb_Environment*		environment );
	Rbdb_DatabaseController*			Rbdb_Environment_databaseController(			Rbdb_Environment*		environment );
	Rbdb_LockController*				Rbdb_Environment_lockController(				Rbdb_Environment*		environment );
	Rbdb_MemoryPoolController*			Rbdb_Environment_memoryPoolController(			Rbdb_Environment*		environment );
	Rbdb_MutexController*				Rbdb_Environment_mutexController(				Rbdb_Environment*		environment );
	Rbdb_ReplicationController*		Rbdb_Environment_replicationController(		Rbdb_Environment*		environment );
//	Rbdb_ObjectController*				Rbdb_Environment_objectController(				Rbdb_Environment*		environment );
//	Rbdb_Controller*			Rbdb_Environment_controllerController(			Rbdb_Environment*		environment );
	Rbdb_LogController*				Rbdb_Environment_logController(				Rbdb_Environment*		environment );
	Rbdb_DatabaseSequenceController*	Rbdb_Environment_databaseSequenceController(	Rbdb_Environment*		environment );
//	Rbdb_StatusController*				Rbdb_Environment_statusController(				Rbdb_Environment*		environment );
	Rbdb_TransactionController*		Rbdb_Environment_transactionController(		Rbdb_Environment*		environment );
	Rbdb_RuntimeStorageController*		Rbdb_Environment_runtimeStorageController(		Rbdb_Environment*		environment );

	Rbdb_SettingsController*			Rbdb_Environment_settingsController(			Rbdb_Environment*		environment );

#endif
