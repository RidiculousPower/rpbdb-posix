/*
- (statistics) statistics														//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_stat.html
*/

	#include "RPBDB_LockStatistics.h"

RPBDB_LockStatusController* RPBDB_LockStatusController_new()	{
	
	RPBDB_LockStatusController*		lock_status_controller = calloc( 1, sizeof( RPBDB_LockStatusController ) );

	return lock_status_controller;
}

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_stat.html
RPBDB_LockStatistics* RPBDB_LockStatusController_statistics( RPBDB *self )	{
	
}


	#include "RPBDB_LockStatistics.h"


/***************************
*			free			*
***************************/
void RPBDB_LockStatusController_free(	RPBDB_LockStatusController* lock_status_controller )	{

/***************************
*	settingsController	*
***************************/
RPBDB_LockStatusSettingsController* RPBDB_LockStatusController_settingsController(	RPBDB_LockStatusController* lock_status_controller )	{
	return lock_status_controller->settings_controller;
}

/***************************************
*	parentEnvironment	*
***************************************/
RPBDB_Environment* RPBDB_LockStatusController_parentEnvironment(	RPBDB_LockStatusController* lock_status_controller )	{
	return lock_status_controller->environment_settings_controller;
}

