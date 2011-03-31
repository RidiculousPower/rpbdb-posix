/*
- statistics																	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_stat.html
*/

	#include "RPBDB_LogStatistics.h"
	#include "RPBDB_StatusController.h"

RPBDB_LogStatusController* RPBDB_LogStatusController_new()	{
	
	RPBDB_LogStatusController*		log_status_controller = calloc( 1, sizeof( RPBDB_LogStatusController ) );

	//	Not much that we have to do here - controllers will be lazy-loaded
	return log_status_controller;
}

RPBDB_LogStatistics* RPBDB_LogStatusController_statistics( RPBDB *self )	{
	
}

			/*****************
			*	 openFiles	 *
			*****************/

		//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_archive.html
		char** RPBDB_StatusController_closedFiles( RPBDB_StatusController* status_controller )	{

			char**		file_pointer_list;

			status_controller->parent_environment->wrapped_bdb_environment->log_archive(	status_controller->parent_environment->wrapped_bdb_environment, 
																				&file_pointer_list, 
																				RPBDB_StatusController_internal_openFilesFlags );
			return file_pointer_list;
		}
		
		
		
		
		/*

		//	Get the files that need to be archived

		void
		log_archlist(DB_ENV *dbenv)
		{
			int ret;
			char **begin, **list;

			// Get the list of database files.
			if ((ret = dbenv->log_archive(dbenv,
			    &list, DB_ARCH_ABS | DB_ARCH_DATA)) != 0) {
				dbenv->err(dbenv, ret, "DB_ENV->log_archive: DB_ARCH_DATA");
				exit (1);
			}
			if (list != NULL) {
				for (begin = list; *list != NULL; ++list)
					printf("database file: %s\n", *list);
				free (begin);
			}


			// Get the list of log files.
			if ((ret = dbenv->log_archive(dbenv,
			    &list, DB_ARCH_ABS | DB_ARCH_LOG)) != 0) {
				dbenv->err(dbenv, ret, "DB_ENV->log_archive: DB_ARCH_LOG");
				exit (1);
			}
			if (list != NULL) {
				for (begin = list; *list != NULL; ++list)
					printf("log file: %s\n", *list);
				free (begin);
			}
		}


		*/

	#include "RPBDB_StatusController.h"
	#include "RPBDB_LogStatistics.h"


/***************************
*			free			*
***************************/
void RPBDB_LogStatusController_free(	RPBDB_LogStatusController* log_status_controller )	{

/***************************
*	settingsController	*
***************************/
RPBDB_LogStatusSettingsController* RPBDB_LogStatusController_settingsController(	RPBDB_LogStatusController* log_status_controller )	{
	return log_status_controller->settings_controller;
}

/***************************************
*	parentEnvironment	*
***************************************/
RPBDB_Environment* RPBDB_LogStatusController_parentEnvironment(	RPBDB_LogStatusController* log_status_controller )	{
	return log_status_controller->environment_settings_controller;
}

