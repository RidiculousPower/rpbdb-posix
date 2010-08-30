#ifndef RPDB_THREAD_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_THREAD_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

	RPDB_ThreadSettingsController* RPDB_ThreadSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_ThreadSettingsController* thread_settings_controller );


void		RPDB_ThreadSettingsController_internal_uniqueThreadIdentifierCallbackMethod(						DB_ENV*				bdb_environment,
			   																									pid_t*				process_id,
			   																									db_threadid_t*		thread_id	);
char*		RPDB_ThreadSettingsController_internal_formatThreadAndProcessIdentifierForDisplayCallbackMethod(	DB_ENV*				bdb_environment,
	 		  																									pid_t				process_id,
	 		  																									db_threadid_t		thread_id,
	 		  																									char*				string_buffer );
int			RPDB_ThreadSettingsController_internal_isThreadAliveCallbackMethod(								DB_ENV*				bdb_environment,
   																												pid_t				process_id,
   																												db_threadid_t		thread_id,
   																												uint32_t			flags );


#endif

