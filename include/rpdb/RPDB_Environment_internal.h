#ifndef RPDB_ENVIRONMENT_INTERNAL
#define RPDB_ENVIRONMENT_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
														Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

	void RPDB_Environment_internal_openWithoutRuntimeStorage( RPDB_Environment* environment );
	void RPDB_Environment_internal_initWrappedEnvironment(	RPDB_Environment*	environment, 
															BOOL				for_runtime_environment );
	int RPDB_Environment_internal_defaultIsThreadAliveCallback(	DB_ENV*			bdb_environment,
																	pid_t			process_id,
																	db_threadid_t	thread_id,
																	uint32_t		flags );
	char* RPDB_Environment_internal_uniqueIdentifier( RPDB_Environment* environment );
	
#endif

