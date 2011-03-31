/*
 *		RPbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeRecnoSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseTypeRecnoSettingsController.h"

#include "Environment.h"
#include "ErrorController.h"
#include "DatabaseTypeSettingsController.h"
#include "DatabaseSettingsController.h"
#include "Database.h"
#include "Record.h"

#include "DatabaseTypeRecnoSettingsController_internal.h"
#include "RuntimeStorageController_internal.h"
#include "Record_internal.h"

#include "DatabaseTypeSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_DatabaseTypeRecnoSettingsController* RPbdb_DatabaseTypeRecnoSettingsController_new( RPbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller )	{

	RPbdb_DatabaseTypeRecnoSettingsController*		database_type_recno_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseTypeRecnoSettingsController ) );

	database_type_recno_settings_controller->parent_database_type_settings_controller = parent_database_type_settings_controller;

	return database_type_recno_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseTypeRecnoSettingsController_free(	RPbdb_DatabaseTypeRecnoSettingsController** database_type_recno_settings_controller )	{

	free( *database_type_recno_settings_controller );
	*database_type_recno_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseTypeRecnoSettingsController_parentEnvironment(	RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	return database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseTypeRecnoSettingsController_parentDatabase(	RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	return database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/*************************
*  recordRenumbering  *
*************************/

//	DB_RENUMBER				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPbdb_DatabaseTypeRecnoSettingsController_recordRenumbering( RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{

	if ( database_type_recno_settings_controller->record_renumbering )	{

		return DB_RENUMBER;
	}

	return FALSE;
}

	/*********************************
	*  turnRecordRenumberingOn  *
	*********************************/

	void RPbdb_DatabaseTypeRecnoSettingsController_turnRecordRenumberingOn( RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
		database_type_recno_settings_controller->record_renumbering = TRUE;
	}

	/*********************************
	*  turnRecordRenumberingOff  *
	*********************************/

	void RPbdb_DatabaseTypeRecnoSettingsController_turnRecordRenumberingOff( RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
		database_type_recno_settings_controller->record_renumbering = FALSE;
	}

/*****************
*  snapshot  *
*****************/

//	DB_SNAPSHOT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPbdb_DatabaseTypeRecnoSettingsController_snapshotIsolation( RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{

	if ( database_type_recno_settings_controller->snapshot_isolation )	{
	
		return DB_SNAPSHOT;
	}
	
	return FALSE;
}

	/*********************************
	*  turnSnapshotIsolationOn  *
	*********************************/

	void RPbdb_DatabaseTypeRecnoSettingsController_turnSnapshotIsolationOn( RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
		database_type_recno_settings_controller->snapshot_isolation = TRUE;
	}

	/*********************************
	*  turnSnapshotIsolationOff  *
	*********************************/

	void RPbdb_DatabaseTypeRecnoSettingsController_turnSnapshotIsolationOff( RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
		database_type_recno_settings_controller->snapshot_isolation = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/******************
*  sourceFile  *
******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_source.html
char* RPbdb_DatabaseTypeRecnoSettingsController_sourceFile( RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
	int		connection_error	= 0;
	RPbdb_Database*		database	=	database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	if (	database_type_recno_settings_controller->source_file_path == NULL
		&&	database->wrapped_bdb_database != NULL )	{
		
		//	Get the record number source
		if ( ( connection_error = database->wrapped_bdb_database->get_re_source(	database->wrapped_bdb_database, 
															(const char**) &( database_type_recno_settings_controller->source_file_path ) ) ) )	{
		
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"DatabaseTypeRecnoSettingsController_sourceFile" );
		}
	}
	
	return database_type_recno_settings_controller->source_file_path;
}

/*********************
*  setSourceFile  *
*********************/

void RPbdb_DatabaseTypeRecnoSettingsController_setSourceFile(	RPbdb_DatabaseTypeRecnoSettingsController*	database_type_recno_settings_controller,
																char*										file_path )	{
	
	RPbdb_Database*	database	= database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{

		int		connection_error	= RP_NO_ERROR;
		//	Set the record number source
		if ( ( connection_error = database->wrapped_bdb_database->set_re_source(	database->wrapped_bdb_database,
																					file_path )  ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"DatabaseTypeRecnoSettingsController_setSourceFile" );
		}
	}

	database_type_recno_settings_controller->source_file_path = file_path;	
}	

/*******************************************************************************************************************************************************************************************
																		Callback Public Methods
*******************************************************************************************************************************************************************************************/

/*********************************
*  setAppendCallbackMethod  *
*********************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_append_recno.html
void RPbdb_DatabaseTypeRecnoSettingsController_setAppendCallbackMethod(	RPbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller,
 																		int (*append_callback_method)(	RPbdb_Database*		database,
																										RPbdb_Record*		record ) )	{

 RPbdb_Database*	database	= database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;

	int			connection_error	= 0;

	if ( ( connection_error = database->set_append_recno(	database, 
															( database_type_recno_settings_controller->append_callback_method == NULL ?
															 	NULL :
																& RPbdb_DatabaseTypeHashSettingsController_internal_appendCallbackMethod ) ) )	{

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"DatabaseTypeRecnoSettingsController_appendCallbackMethod" );
	}

	database_type_recno_settings_controller->append_callback_method = append_callback_method;
}
*/
/*****************************
*  appendCallbackMethod  *
*****************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_append_recno.html
void (*append_callback_method)(	RPbdb_Database*		database,
								RPbdb_Record*		record ) RPbdb_DatabaseTypeRecnoSettingsController_appendCallback( RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{

	return database_type_recno_settings_controller->append_callback_method;
}
*/
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/****************************
*  appendCallbackMethod  *
****************************/
/*
int RPbdb_DatabaseTypeRecnoSettingsController_internal_appendCallbackMethod(	DB*				bdb_database, 
																				DBT*			bdb_data, 
																				db_recno_t		record_number )	{
	
	RPbdb_Database*	database	=	RPbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );
	
	RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller = RPbdb_DatabaseTypeSettingsController_recnoSettingsController(
																							RPbdb_DatabaseSettingsController_typeSettingsController( 
																								RPbdb_Database_settingsController( database ) );
	RPbdb_Record*	record		=	RPbdb_Record_internal_newFromRawKeyDBTDataPair( & record_number,
																					bdb_data );
	
	*( database_type_recno_settings_controller->append_callback_method )(	database,
																			record );
																			
	//	Returns "no error" even if there was an error (this is never seen by user)
	//	Error checking is done outside of return values (with reference to Error Controller)
	return RP_NO_ERROR;
}

*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseTypeRecnoSettingsController* RPbdb_DatabaseTypeRecnoSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{

	RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller_copy	=	RPbdb_DatabaseTypeRecnoSettingsController_new( database_type_recno_settings_controller->parent_database_type_settings_controller );

	//	Instances and Pointers
	database_type_recno_settings_controller_copy->record_renumbering	=	database_type_recno_settings_controller->record_renumbering;
	database_type_recno_settings_controller_copy->source_file_path	=	database_type_recno_settings_controller->source_file_path;
	database_type_recno_settings_controller_copy->snapshot_isolation	=	database_type_recno_settings_controller->snapshot_isolation;

	return database_type_recno_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

void RPbdb_DatabaseTypeRecnoSettingsController_internal_setFlags(	RPbdb_DatabaseTypeRecnoSettingsController*		database_type_recno_settings_controller )	{
	
	RPbdb_Database*			database = database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	database->wrapped_bdb_database->set_flags(	database->wrapped_bdb_database,
												RPbdb_DatabaseTypeSettingsController_internal_setFlags( database_type_recno_settings_controller->parent_database_type_settings_controller )
												|	RPbdb_DatabaseTypeRecnoSettingsController_recordRenumbering( database_type_recno_settings_controller )
												|	RPbdb_DatabaseTypeRecnoSettingsController_snapshotIsolation( database_type_recno_settings_controller ) );
}

