/*
* (databases_array) all (implied)
- (databases_array) active
- (databases_array) inactive		
*/

RPBDB_StatusDatabaseController* RPBDB_StatusDatabaseController_new()	{
	
	RPBDB_StatusDatabaseController*		status_database_controller = calloc( 1, sizeof( RPBDB_StatusDatabaseController ) );

	//	Not much that we have to do here - controllers will be lazy-loaded
	return status_database_controller;
}

RPBDB_Database** RPBDB_StatusDatabaseController_all( RPBDB *self )	{
	
}

RPBDB_Database** RPBDB_StatusDatabaseController_active( RPBDB *self )	{
	
}

RPBDB_Database** RPBDB_StatusDatabaseController_inactive( RPBDB *self )	{
	
}void RPBDB_StatusDatabaseController_free(	RPBDB_StatusDatabaseController* status_database_controller );
RPBDB_StatusDatabaseSettingsController* RPBDB_StatusDatabaseController_settingsController(	RPBDB_StatusDatabaseController* status_database_controller );
RPBDB_Environment* RPBDB_StatusDatabaseController_parentEnvironment(	RPBDB_StatusDatabaseController* status_database_controller );
