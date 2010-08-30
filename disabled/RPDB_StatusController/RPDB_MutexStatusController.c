/*
- statistics																	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_stat.html
*/

	#include "RPBDB_MutexStatistics.h"

RPBDB_MutexStatusController* RPBDB_MutexStatusController_new()	{
	
	RPBDB_MutexStatusController*		mutex_status_controller = calloc( 1, sizeof( RPBDB_MutexStatusController ) );

	//	Not much that we have to do here - controllers will be lazy-loaded
	return mutex_status_controller;
}

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_stat.html
RPBDB_MutexStatistics* RPBDB_MutexStatusController_statistics( RPBDB *self )	{
	
}

	#include "RPBDB_MutexStatistics.h"


/***************************
*			free			*
***************************/
void RPBDB_MutexStatusController_free(	RPBDB_MutexStatusController* mutex_status_controller )	{

/***************************
*	settingsController	*
***************************/
RPBDB_MutexStatusSettingsController* RPBDB_MutexStatusController_settingsController(	RPBDB_MutexStatusController* mutex_status_controller )	{
	return mutex_status_controller->settings_controller;
}

/***************************************
*	parentEnvironment	*
***************************************/
RPBDB_Environment* RPBDB_MutexStatusController_parentEnvironment(	RPBDB_MutexStatusController* mutex_status_controller )	{
	return mutex_status_controller->environment_settings_controller;
}

