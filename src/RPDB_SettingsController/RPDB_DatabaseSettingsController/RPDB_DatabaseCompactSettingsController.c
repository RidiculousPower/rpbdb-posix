/*
 *		RPDB::SettingsController::DatabaseSettingsController::DatabaseCompactSettingsController
 *		RPDB::DatabaseController::Database::SettingsController::CompactSettingsController
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseCompactSettingsController.h"

	#include "RPDB_Environment.h"
	#include "RPDB_ErrorController.h"
	#include "RPDB_DatabaseReadWriteSettingsController.h"
	
	#include "RPDB_DatabaseReadWriteSettingsController_internal.h"
	#include "RPDB_DatabaseCompactSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseCompactSettingsController* RPDB_DatabaseCompactSettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseCompactSettingsController*		database_compact_settings_controller = calloc( 1, sizeof( RPDB_DatabaseCompactSettingsController ) );

	database_compact_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_compact_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseCompactSettingsController_free(	RPDB_DatabaseCompactSettingsController** database_compact_settings_controller )	{

	free( *database_compact_settings_controller );
	*database_compact_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseCompactSettingsController_parentEnvironment(	RPDB_DatabaseCompactSettingsController* database_compact_settings_controller )	{
	return database_compact_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseCompactSettingsController_parentDatabase(	RPDB_DatabaseCompactSettingsController* database_compact_settings_controller )	{
	return database_compact_settings_controller->parent_database_settings_controller->parent_database;
}

/*********************
*  fillPercent  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, the goal for filling pages, specified as a percentage between 1 and 100. 
//	Any page in a Btree or Recno databases not at or above this percentage full will be considered for compaction. 
//	The default behavior is to consider every page for compaction, regardless of its page fill percentage.
int RPDB_DatabaseCompactSettingsController_fillPercent( RPDB_DatabaseCompactSettingsController* database_compact_settings_controller )	{

	return database_compact_settings_controller->fill_percent;
}

/*************************
*  setFillPercent  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, the goal for filling pages, specified as a percentage between 1 and 100. 
//	Any page in a Btree or Recno databases not at or above this percentage full will be considered for compaction. 
//	The default behavior is to consider every page for compaction, regardless of its page fill percentage.
void RPDB_DatabaseCompactSettingsController_setFillPercent(	RPDB_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																int											fill_percent )	{

	if ( fill_percent < 1 || fill_percent > 100 )	{
		RPDB_ErrorController_throwError( RPDB_Environment_errorController( database_compact_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ), 
									RP_ERROR_PERCENT_OUT_OF_BOUNDS, 
										 "RPDB_DatabaseCompactSettingsController_setFillPercent", 
										 "Percent must be 0-100." );
		return;
	}

	database_compact_settings_controller->fill_percent = fill_percent;
}

/*************************
*  maxPagesToCompact  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, the call will return after that number of pages have been freed.
int RPDB_DatabaseCompactSettingsController_maxPagesToCompact( RPDB_DatabaseCompactSettingsController* database_compact_settings_controller )	{

	return database_compact_settings_controller->max_pages_to_compact;
}

/*****************************
*  setMaxPagesToCompact  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, the call will return after that number of pages have been freed.
void RPDB_DatabaseCompactSettingsController_setMaxPagesToCompact(	RPDB_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																	int											max_pages_to_compact )	{

	database_compact_settings_controller->max_pages_to_compact = max_pages_to_compact;
}

/****************
*  timeout  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, and no txnid parameter was specified, the lock timeout set for implicit transactions, in microseconds.
db_timeout_t RPDB_DatabaseCompactSettingsController_timeout( RPDB_DatabaseCompactSettingsController* database_compact_settings_controller )	{

	return database_compact_settings_controller->timeout;
}

/********************
*  setTimeout  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, and no txnid parameter was specified, the lock timeout set for implicit transactions, in microseconds.
void RPDB_DatabaseCompactSettingsController_setTimeout(	RPDB_DatabaseCompactSettingsController*			database_compact_settings_controller, 
															int													timeout )	{

	database_compact_settings_controller->timeout = timeout;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseCompactSettingsController* RPDB_DatabaseCompactSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseCompactSettingsController* database_compact_settings_controller )	{

	RPDB_DatabaseCompactSettingsController* database_compact_settings_controller_copy	=	RPDB_DatabaseCompactSettingsController_new( database_compact_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_compact_settings_controller_copy->fill_percent	=	database_compact_settings_controller->fill_percent;
	database_compact_settings_controller_copy->timeout	=	database_compact_settings_controller->timeout;
	database_compact_settings_controller_copy->max_pages_to_compact	=	database_compact_settings_controller->max_pages_to_compact;

	return database_compact_settings_controller_copy;
}

