/*
 *		RPBDB::Database::DatabaseStatusController::DatabaseStatusCompactController
 *
 *
 */

	#include "RPBDB_DatabaseStatusController.h"

	/****************
	*	Prototypes	*
	****************/
	
			/*************
			*	 new	 *
			*************/

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*	 new	 *
*************/

RPBDB_DatabaseStatusCompactController* RPBDB_DatabaseStatusCompactController_new( RPBDB_DatabaseStatusController* database_status_controller )	{

	RPBDB_DatabaseStatusCompactController*		database_status_compact_controller = calloc( 1, sizeof( RPBDB_DatabaseStatusCompactController );

	database_status_controller->database_status_compact_controller = database_status_compact_controller;

	return database_status_compact_controller;
}

/*****************
*	 deadlocks	 *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
uint32_t RPBDB_DatabaseStatusCompactController_deadlocks( RPBDB_DatabaseStatusController* database_status_controller )	{
	
	return database_status_controller->compact_status->compact_deadlock;
}

/*********************
*	 pagesExamined	 *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
uint32_t RPBDB_DatabaseStatusCompactController_pagesExamined( RPBDB_DatabaseStatusController* database_status_controller )	{

	return database_status_controller->compact_status->compact_pages_examine;
}

/******************
*	 pagesFreed	  *
******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
uint32_t RPBDB_DatabaseStatusCompactController_pagesFreed( RPBDB_DatabaseStatusController* database_status_controller )	{

	return database_status_controller->compact_status->compact_pages_free;
}

/*********************
*	 levelsRemoved	 *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
uint32_t RPBDB_DatabaseStatusCompactController_levelsRemoved( RPBDB_DatabaseStatusController* database_status_controller )	{

	return database_status_controller->compact_status->compact_levels;
}

/**********************
*	 pagesTruncated	  *
**********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
uint32_t RPBDB_DatabaseStatusCompactController_pagesTruncated( RPBDB_DatabaseStatusController* database_status_controller )	{

	return database_status_controller->compact_status->compact_pages_truncated;
}


	#include "RPBDB_DatabaseStatusController.h"


/***************************
*			free			*
***************************/
void RPBDB_DatabaseStatusCompactController_free(	RPBDB_DatabaseStatusCompactController* database_status_compact_controller )	{

/***************************
*	settingsController	*
***************************/
RPBDB_DatabaseStatusCompactSettingsController* RPBDB_DatabaseStatusCompactController_settingsController(	RPBDB_DatabaseStatusCompactController* database_status_compact_controller )	{
	return database_status_compact_controller->settings_controller;
}

/***************************************
*	parentEnvironment	*
***************************************/
RPBDB_Environment* RPBDB_DatabaseStatusCompactController_parentEnvironment(	RPBDB_DatabaseStatusCompactController* database_status_compact_controller )	{
	return database_status_compact_controller->environment_settings_controller;
}

