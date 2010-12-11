#ifndef RBDB_ENVIRONMENT_INTERNAL
#define RBDB_ENVIRONMENT_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
														Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

	void Rbdb_Environment_internal_openWithoutRuntimeStorage( Rbdb_Environment* environment );
	void Rbdb_Environment_internal_initWrappedEnvironment(	Rbdb_Environment*	environment, 
															BOOL				for_runtime_environment );
	int Rbdb_Environment_internal_defaultIsThreadAliveCallback(	DB_ENV*			bdb_environment,
																	pid_t			process_id,
																	db_threadid_t	thread_id,
																	uint32_t		flags );
	char* Rbdb_Environment_internal_errorfilePathForEnvironment( Rbdb_Environment*		environment );

	
#endif

