/*
- statistics														//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_stat.html
- managerStatistics													//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_stat.html
*/

	#include "RPBDB_ReplicationStatistics.h"
	#include "RPBDB_ReplicationManagerStatistics.h"

RPBDB_ReplicationStatusController* RPBDB_ReplicationStatusController_new()	{
	
	RPBDB_ReplicationStatusController*		replication_status_controller = calloc( 1, sizeof( RPBDB_ReplicationStatusController ) );

	//	Not much that we have to do here - controllers will be lazy-loaded
	return replication_status_controller;
}

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/rep_stat.html
RPBDB_ReplicationStatistics* RPBDB_ReplicationStatusController_statistics( RPBDB *self )	{
	
}

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/repmgr_stat.html
RPBDB_ReplicationManagerStatistics* RPBDB_ReplicationStatusController_managerStatistics( RPBDB *self )	{
	
}	


	#include "RPBDB_ReplicationStatistics.h"
	#include "RPBDB_ReplicationManagerStatistics.h"


/***************************
*			free			*
***************************/
void RPBDB_ReplicationStatusController_free(	RPBDB_ReplicationStatusController* replication_status_controller )	{

/***************************
*	settingsController	*
***************************/
RPBDB_ReplicationStatusSettingsController* RPBDB_ReplicationStatusController_settingsController(	RPBDB_ReplicationStatusController* replication_status_controller )	{
	return replication_status_controller->settings_controller;
}

/***************************************
*	parentEnvironment	*
***************************************/
RPBDB_Environment* RPBDB_ReplicationStatusController_parentEnvironment(	RPBDB_ReplicationStatusController* replication_status_controller )	{
	return replication_status_controller->environment_settings_controller;
}

