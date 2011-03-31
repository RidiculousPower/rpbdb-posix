/*
 *		RPbdb::SettingsController::DatabaseSettingsController::DatabaseCompactSettingsController
 *		RPbdb::DatabaseController::Database::SettingsController::CompactSettingsController
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseCompactSettingsController.h"

	#include "Environment.h"
	#include "ErrorController.h"
	#include "DatabaseRecordReadWriteSettingsController.h"
	
	#include "DatabaseRecordReadWriteSettingsController_internal.h"
	#include "DatabaseCompactSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_DatabaseCompactSettingsController* RPbdb_DatabaseCompactSettingsController_new( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_DatabaseCompactSettingsController*		database_compact_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseCompactSettingsController ) );

	database_compact_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_compact_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseCompactSettingsController_free(	RPbdb_DatabaseCompactSettingsController** database_compact_settings_controller )	{

	free( *database_compact_settings_controller );
	*database_compact_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseCompactSettingsController_parentEnvironment(	RPbdb_DatabaseCompactSettingsController* database_compact_settings_controller )	{
	return database_compact_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseCompactSettingsController_parentDatabase(	RPbdb_DatabaseCompactSettingsController* database_compact_settings_controller )	{
	return database_compact_settings_controller->parent_database_settings_controller->parent_database;
}

/*********************
*  fillPercent  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, the goal for filling pages, specified as a percentage between 1 and 100. 
//	Any page in a Btree or Recno databases not at or above this percentage full will be considered for compaction. 
//	The default behavior is to consider every page for compaction, regardless of its page fill percentage.
int RPbdb_DatabaseCompactSettingsController_fillPercent( RPbdb_DatabaseCompactSettingsController* database_compact_settings_controller )	{

	return database_compact_settings_controller->fill_percent;
}

/*************************
*  setFillPercent  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, the goal for filling pages, specified as a percentage between 1 and 100. 
//	Any page in a Btree or Recno databases not at or above this percentage full will be considered for compaction. 
//	The default behavior is to consider every page for compaction, regardless of its page fill percentage.
void RPbdb_DatabaseCompactSettingsController_setFillPercent(	RPbdb_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																int											fill_percent )	{

	if ( fill_percent < 1 || fill_percent > 100 )	{
		RPbdb_ErrorController_throwError( RPbdb_Environment_errorController( database_compact_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ), 
									RP_ERROR_PERCENT_OUT_OF_BOUNDS, 
										 "DatabaseCompactSettingsController_setFillPercent", 
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
int RPbdb_DatabaseCompactSettingsController_maxPagesToCompact( RPbdb_DatabaseCompactSettingsController* database_compact_settings_controller )	{

	return database_compact_settings_controller->max_pages_to_compact;
}

/*****************************
*  setMaxPagesToCompact  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, the call will return after that number of pages have been freed.
void RPbdb_DatabaseCompactSettingsController_setMaxPagesToCompact(	RPbdb_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																	int											max_pages_to_compact )	{

	database_compact_settings_controller->max_pages_to_compact = max_pages_to_compact;
}

/****************
*  timeout  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, and no txnid parameter was specified, the lock timeout set for implicit transactions, in microseconds.
db_timeout_t RPbdb_DatabaseCompactSettingsController_timeout( RPbdb_DatabaseCompactSettingsController* database_compact_settings_controller )	{

	return database_compact_settings_controller->timeout;
}

/********************
*  setTimeout  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, and no txnid parameter was specified, the lock timeout set for implicit transactions, in microseconds.
void RPbdb_DatabaseCompactSettingsController_setTimeout(	RPbdb_DatabaseCompactSettingsController*			database_compact_settings_controller, 
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
RPbdb_DatabaseCompactSettingsController* RPbdb_DatabaseCompactSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseCompactSettingsController* database_compact_settings_controller )	{

	RPbdb_DatabaseCompactSettingsController* database_compact_settings_controller_copy	=	RPbdb_DatabaseCompactSettingsController_new( database_compact_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_compact_settings_controller_copy->fill_percent	=	database_compact_settings_controller->fill_percent;
	database_compact_settings_controller_copy->timeout	=	database_compact_settings_controller->timeout;
	database_compact_settings_controller_copy->max_pages_to_compact	=	database_compact_settings_controller->max_pages_to_compact;

	return database_compact_settings_controller_copy;
}

