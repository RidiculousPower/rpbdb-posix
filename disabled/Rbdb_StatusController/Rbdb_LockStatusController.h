/*
- (statistics) statistics														//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_stat.html
*/

RPBDB_LockStatusController* RPBDB_LockStatusController_new()	{
	
	RPBDB_LockStatusController*		lock_status_controller = calloc( 1, sizeof( RPBDB_LockStatusController ) );

	return lock_status_controller;
}

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_stat.html
RPBDB_LockStatistics* RPBDB_LockStatusController_statistics( RPBDB *self )	{
	
}

void RPBDB_LockStatusController_free(	RPBDB_LockStatusController* lock_status_controller );
RPBDB_LockStatusSettingsController* RPBDB_LockStatusController_settingsController(	RPBDB_LockStatusController* lock_status_controller );
RPBDB_Environment* RPBDB_LockStatusController_parentEnvironment(	RPBDB_LockStatusController* lock_status_controller );
