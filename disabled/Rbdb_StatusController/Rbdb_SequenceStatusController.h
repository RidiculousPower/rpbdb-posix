/*
- statistics																	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_stat.html
*/

RPBDB_DatabaseSequenceStatusController* RPBDB_DatabaseSequenceStatusController_new()	{
	
	RPBDB_DatabaseSequenceStatusController*		sequence_status_controller = calloc( 1, sizeof( RPBDB_DatabaseSequenceStatusController ) );

	//	Not much that we have to do here - controllers will be lazy-loaded
	return sequence_status_controller;
}

RPBDB_DatabaseSequenceStatistics* RPBDB_DatabaseSequenceStatusController_statistics( RPBDB *self )	{
	
}
void RPBDB_SequenceStatusController_free(	RPBDB_SequenceStatusController* sequence_status_controller );
RPBDB_SequenceStatusSettingsController* RPBDB_SequenceStatusController_settingsController(	RPBDB_SequenceStatusController* sequence_status_controller );
RPBDB_Environment* RPBDB_SequenceStatusController_parentEnvironment(	RPBDB_SequenceStatusController* sequence_status_controller );
