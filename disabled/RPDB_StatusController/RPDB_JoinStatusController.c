RPBDB_JoinStatusController* RPBDB_JoinStatusController_new()	{
	
	RPBDB_JoinStatusController*		join_status_controller = calloc( 1, sizeof( RPBDB_JoinStatusController ) );

	return join_status_controller;
}



/***************************
*			free			*
***************************/
void RPBDB_JoinStatusController_free(	RPBDB_JoinStatusController* join_status_controller )	{

/***************************
*	settingsController	*
***************************/
RPBDB_JoinStatusSettingsController* RPBDB_JoinStatusController_settingsController(	RPBDB_JoinStatusController* join_status_controller )	{
	return join_status_controller->settings_controller;
}

/***************************************
*	parentEnvironment	*
***************************************/
RPBDB_Environment* RPBDB_JoinStatusController_parentEnvironment(	RPBDB_JoinStatusController* join_status_controller )	{
	return join_status_controller->environment_settings_controller;
}

