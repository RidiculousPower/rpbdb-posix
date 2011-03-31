#ifndef RPBDB_ENVIRONMENT_INTERNAL
#define RPBDB_ENVIRONMENT_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
														Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

	void RPbdb_Environment_internal_openWithoutRuntimeStorage( RPbdb_Environment* environment );
	void RPbdb_Environment_internal_initWrappedEnvironment(	RPbdb_Environment*	environment, 
															BOOL				for_runtime_environment );
	int RPbdb_Environment_internal_defaultIsThreadAliveCallback(	DB_ENV*			bdb_environment,
																	pid_t			process_id,
																	db_threadid_t	thread_id,
																	uint32_t		flags );
	char* RPbdb_Environment_internal_errorfilePathForEnvironment( RPbdb_Environment*		environment );

	
#endif

