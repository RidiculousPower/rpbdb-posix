#ifndef RPBDB_THREAD_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_THREAD_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

	RPbdb_ThreadSettingsController* RPbdb_ThreadSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_ThreadSettingsController* thread_settings_controller );


void		RPbdb_ThreadSettingsController_internal_uniqueThreadIdentifierCallbackMethod(						DB_ENV*				bdb_environment,
			   																									pid_t*				process_id,
			   																									db_threadid_t*		thread_id	);
char*		RPbdb_ThreadSettingsController_internal_formatThreadAndProcessIdentifierForDisplayCallbackMethod(	DB_ENV*				bdb_environment,
	 		  																									pid_t				process_id,
	 		  																									db_threadid_t		thread_id,
	 		  																									char*				string_buffer );
int			RPbdb_ThreadSettingsController_internal_isThreadAliveCallbackMethod(								DB_ENV*				bdb_environment,
   																												pid_t				process_id,
   																												db_threadid_t		thread_id,
   																												uint32_t			flags );


#endif

