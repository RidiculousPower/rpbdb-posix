#ifndef RBDB_THREAD_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_THREAD_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

	Rbdb_ThreadSettingsController* Rbdb_ThreadSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_ThreadSettingsController* thread_settings_controller );


void		Rbdb_ThreadSettingsController_internal_uniqueThreadIdentifierCallbackMethod(						DB_ENV*				bdb_environment,
			   																									pid_t*				process_id,
			   																									db_threadid_t*		thread_id	);
char*		Rbdb_ThreadSettingsController_internal_formatThreadAndProcessIdentifierForDisplayCallbackMethod(	DB_ENV*				bdb_environment,
	 		  																									pid_t				process_id,
	 		  																									db_threadid_t		thread_id,
	 		  																									char*				string_buffer );
int			Rbdb_ThreadSettingsController_internal_isThreadAliveCallbackMethod(								DB_ENV*				bdb_environment,
   																												pid_t				process_id,
   																												db_threadid_t		thread_id,
   																												uint32_t			flags );


#endif

