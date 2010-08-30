/*

	RPDB by Asher (asher at ridiculous power dot com).
	All rights reserved. Licensing for RPDB is to be construed as an independent extension of licensing for Oracle's Berkeley DB.
	This provides licensing under one of two schemas (as outlined by Oracle: 
	http://www.oracle.com/technology/software/products/berkeley-db/htdocs/licensing.html):
	
	* Open Source (Any distributed software utilizing RPDB must also distribute its source openly). 
	* Commercial License (Licensing arrangement to be determined, contact Ridiculous Power).
		
	C and Ruby Wrapper for Oracle's (formerly Sleepcat's) Berkeley DB (BDB).  

*/

#ifndef RPDB_ENVIRONMENT
	#define RPDB_ENVIRONMENT

	 /***************
	 *  Includes  *
	 ****************/

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
	
	RPDB_Environment*								RPDB_Environment_new(							char*		environment_name,
																									char*		environment_home_directory );

	void											RPDB_Environment_free(	RPDB_Environment** environment );
	
	void											RPDB_Environment_initDefaults( RPDB_Environment* environment );
	
	RPDB_Environment*								RPDB_Environment_initForStorageInMemory(		RPDB_Environment*		environment );

	RPDB_Environment*								RPDB_Environment_open(							RPDB_Environment*		environment );
	BOOL											RPDB_Environment_isOpen( RPDB_Environment* environment );
	char* RPDB_Environment_homeDirectory( RPDB_Environment* environment );
	RPDB_Environment*								RPDB_Environment_close(						RPDB_Environment*		environment );

	RPDB_Environment*								RPDB_Environment_erase(						RPDB_Environment*		environment );
	char*											RPDB_Environment_name( RPDB_Environment* environment );
	void RPDB_Environment_setName(	RPDB_Environment*		environment,
																		char*								name );


	void											RPDB_Environment_checkForEnvironmentFailure( RPDB_Environment* environment );


	RPDB_ErrorController*				RPDB_Environment_errorController(				RPDB_Environment*		environment );
	RPDB_DatabaseController*			RPDB_Environment_databaseController(			RPDB_Environment*		environment );
	RPDB_LockController*				RPDB_Environment_lockController(				RPDB_Environment*		environment );
	RPDB_MemoryPoolController*			RPDB_Environment_memoryPoolController(			RPDB_Environment*		environment );
	RPDB_MutexController*				RPDB_Environment_mutexController(				RPDB_Environment*		environment );
	RPDB_ReplicationController*		RPDB_Environment_replicationController(		RPDB_Environment*		environment );
//	RPDB_ObjectController*				RPDB_Environment_objectController(				RPDB_Environment*		environment );
//	RPDB_Controller*			RPDB_Environment_controllerController(			RPDB_Environment*		environment );
	RPDB_LogController*				RPDB_Environment_logController(				RPDB_Environment*		environment );
	RPDB_DatabaseSequenceController*	RPDB_Environment_databaseSequenceController(	RPDB_Environment*		environment );
//	RPDB_StatusController*				RPDB_Environment_statusController(				RPDB_Environment*		environment );
	RPDB_TransactionController*		RPDB_Environment_transactionController(		RPDB_Environment*		environment );
	RPDB_RuntimeStorageController*		RPDB_Environment_runtimeStorageController(		RPDB_Environment*		environment );

	RPDB_SettingsController*			RPDB_Environment_settingsController(			RPDB_Environment*		environment );

#endif
