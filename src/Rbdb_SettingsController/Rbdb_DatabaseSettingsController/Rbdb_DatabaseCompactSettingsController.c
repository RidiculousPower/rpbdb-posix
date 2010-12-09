/*
 *		Rbdb::SettingsController::DatabaseSettingsController::DatabaseCompactSettingsController
 *		Rbdb::DatabaseController::Database::SettingsController::CompactSettingsController
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseCompactSettingsController.h"

	#include "Rbdb_Environment.h"
	#include "Rbdb_ErrorController.h"
	#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"
	
	#include "Rbdb_DatabaseRecordReadWriteSettingsController_internal.h"
	#include "Rbdb_DatabaseCompactSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_DatabaseCompactSettingsController* Rbdb_DatabaseCompactSettingsController_new( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_DatabaseCompactSettingsController*		database_compact_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseCompactSettingsController ) );

	database_compact_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_compact_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseCompactSettingsController_free(	Rbdb_DatabaseCompactSettingsController** database_compact_settings_controller )	{

	free( *database_compact_settings_controller );
	*database_compact_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseCompactSettingsController_parentEnvironment(	Rbdb_DatabaseCompactSettingsController* database_compact_settings_controller )	{
	return database_compact_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseCompactSettingsController_parentDatabase(	Rbdb_DatabaseCompactSettingsController* database_compact_settings_controller )	{
	return database_compact_settings_controller->parent_database_settings_controller->parent_database;
}

/*********************
*  fillPercent  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, the goal for filling pages, specified as a percentage between 1 and 100. 
//	Any page in a Btree or Recno databases not at or above this percentage full will be considered for compaction. 
//	The default behavior is to consider every page for compaction, regardless of its page fill percentage.
int Rbdb_DatabaseCompactSettingsController_fillPercent( Rbdb_DatabaseCompactSettingsController* database_compact_settings_controller )	{

	return database_compact_settings_controller->fill_percent;
}

/*************************
*  setFillPercent  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, the goal for filling pages, specified as a percentage between 1 and 100. 
//	Any page in a Btree or Recno databases not at or above this percentage full will be considered for compaction. 
//	The default behavior is to consider every page for compaction, regardless of its page fill percentage.
void Rbdb_DatabaseCompactSettingsController_setFillPercent(	Rbdb_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																int											fill_percent )	{

	if ( fill_percent < 1 || fill_percent > 100 )	{
		Rbdb_ErrorController_throwError( Rbdb_Environment_errorController( database_compact_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ), 
									RP_ERROR_PERCENT_OUT_OF_BOUNDS, 
										 "Rbdb_DatabaseCompactSettingsController_setFillPercent", 
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
int Rbdb_DatabaseCompactSettingsController_maxPagesToCompact( Rbdb_DatabaseCompactSettingsController* database_compact_settings_controller )	{

	return database_compact_settings_controller->max_pages_to_compact;
}

/*****************************
*  setMaxPagesToCompact  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, the call will return after that number of pages have been freed.
void Rbdb_DatabaseCompactSettingsController_setMaxPagesToCompact(	Rbdb_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																	int											max_pages_to_compact )	{

	database_compact_settings_controller->max_pages_to_compact = max_pages_to_compact;
}

/****************
*  timeout  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, and no txnid parameter was specified, the lock timeout set for implicit transactions, in microseconds.
db_timeout_t Rbdb_DatabaseCompactSettingsController_timeout( Rbdb_DatabaseCompactSettingsController* database_compact_settings_controller )	{

	return database_compact_settings_controller->timeout;
}

/********************
*  setTimeout  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	If non-zero, and no txnid parameter was specified, the lock timeout set for implicit transactions, in microseconds.
void Rbdb_DatabaseCompactSettingsController_setTimeout(	Rbdb_DatabaseCompactSettingsController*			database_compact_settings_controller, 
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
Rbdb_DatabaseCompactSettingsController* Rbdb_DatabaseCompactSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseCompactSettingsController* database_compact_settings_controller )	{

	Rbdb_DatabaseCompactSettingsController* database_compact_settings_controller_copy	=	Rbdb_DatabaseCompactSettingsController_new( database_compact_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_compact_settings_controller_copy->fill_percent	=	database_compact_settings_controller->fill_percent;
	database_compact_settings_controller_copy->timeout	=	database_compact_settings_controller->timeout;
	database_compact_settings_controller_copy->max_pages_to_compact	=	database_compact_settings_controller->max_pages_to_compact;

	return database_compact_settings_controller_copy;
}

