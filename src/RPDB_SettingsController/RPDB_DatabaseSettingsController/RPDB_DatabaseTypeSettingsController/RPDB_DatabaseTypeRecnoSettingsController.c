/*
 *		RPDB::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeRecnoSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseTypeRecnoSettingsController.h"

#include "RPDB_Environment.h"
#include "RPDB_ErrorController.h"
#include "RPDB_DatabaseTypeSettingsController.h"
#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_Database.h"
#include "RPDB_Record.h"

#include "RPDB_DatabaseTypeRecnoSettingsController_internal.h"
#include "RPDB_RuntimeStorageController_internal.h"
#include "RPDB_Record_internal.h"

#include "RPDB_DatabaseTypeSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseTypeRecnoSettingsController* RPDB_DatabaseTypeRecnoSettingsController_new( RPDB_DatabaseTypeSettingsController*						parent_database_type_settings_controller )	{

	RPDB_DatabaseTypeRecnoSettingsController*		database_type_recno_settings_controller = calloc( 1, sizeof( RPDB_DatabaseTypeRecnoSettingsController ) );

	database_type_recno_settings_controller->parent_database_type_settings_controller = parent_database_type_settings_controller;

	return database_type_recno_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseTypeRecnoSettingsController_free(	RPDB_DatabaseTypeRecnoSettingsController** database_type_recno_settings_controller )	{

	free( *database_type_recno_settings_controller );
	*database_type_recno_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseTypeRecnoSettingsController_parentEnvironment(	RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	return database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseTypeRecnoSettingsController_parentDatabase(	RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	return database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/*************************
*  recordRenumbering  *
*************************/

//	DB_RENUMBER				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPDB_DatabaseTypeRecnoSettingsController_recordRenumbering( RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{

	if ( database_type_recno_settings_controller->record_renumbering )	{

		return DB_RENUMBER;
	}

	return FALSE;
}

	/*********************************
	*  turnRecordRenumberingOn  *
	*********************************/

	void RPDB_DatabaseTypeRecnoSettingsController_turnRecordRenumberingOn( RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
		database_type_recno_settings_controller->record_renumbering = TRUE;
	}

	/*********************************
	*  turnRecordRenumberingOff  *
	*********************************/

	void RPDB_DatabaseTypeRecnoSettingsController_turnRecordRenumberingOff( RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
		database_type_recno_settings_controller->record_renumbering = FALSE;
	}

/*****************
*  snapshot  *
*****************/

//	DB_SNAPSHOT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPDB_DatabaseTypeRecnoSettingsController_snapshotIsolation( RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{

	if ( database_type_recno_settings_controller->snapshot_isolation )	{
	
		return DB_SNAPSHOT;
	}
	
	return FALSE;
}

	/*********************************
	*  turnSnapshotIsolationOn  *
	*********************************/

	void RPDB_DatabaseTypeRecnoSettingsController_turnSnapshotIsolationOn( RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
		database_type_recno_settings_controller->snapshot_isolation = TRUE;
	}

	/*********************************
	*  turnSnapshotIsolationOff  *
	*********************************/

	void RPDB_DatabaseTypeRecnoSettingsController_turnSnapshotIsolationOff( RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
		database_type_recno_settings_controller->snapshot_isolation = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/******************
*  sourceFile  *
******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_source.html
char* RPDB_DatabaseTypeRecnoSettingsController_sourceFile( RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
	int		connection_error	= 0;
	RPDB_Database*		database	=	database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	if (	database_type_recno_settings_controller->source_file_path == NULL
		&&	database->wrapped_bdb_database != NULL )	{
		
		//	Get the record number source
		if ( ( connection_error = database->wrapped_bdb_database->get_re_source(	database->wrapped_bdb_database, 
															(const char**) &( database_type_recno_settings_controller->source_file_path ) ) ) )	{
		
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"RPDB_DatabaseTypeRecnoSettingsController_sourceFile" );
		}
	}
	
	return database_type_recno_settings_controller->source_file_path;
}

/*********************
*  setSourceFile  *
*********************/

void RPDB_DatabaseTypeRecnoSettingsController_setSourceFile(	RPDB_DatabaseTypeRecnoSettingsController*	database_type_recno_settings_controller,
																char*										file_path )	{
	
	RPDB_Database*	database	= database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{

		int		connection_error	= RP_NO_ERROR;
		//	Set the record number source
		if ( ( connection_error = database->wrapped_bdb_database->set_re_source(	database->wrapped_bdb_database,
																					file_path )  ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"RPDB_DatabaseTypeRecnoSettingsController_setSourceFile" );
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
void RPDB_DatabaseTypeRecnoSettingsController_setAppendCallbackMethod(	RPDB_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller,
 																		int (*append_callback_method)(	RPDB_Database*		database,
																										RPDB_Record*		record ) )	{

 RPDB_Database*	database	= database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;

	int			connection_error	= 0;

	if ( ( connection_error = database->set_append_recno(	database, 
															( database_type_recno_settings_controller->append_callback_method == NULL ?
															 	NULL :
																& RPDB_DatabaseTypeHashSettingsController_internal_appendCallbackMethod ) ) )	{

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"RPDB_DatabaseTypeRecnoSettingsController_appendCallbackMethod" );
	}

	database_type_recno_settings_controller->append_callback_method = append_callback_method;
}
*/
/*****************************
*  appendCallbackMethod  *
*****************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_append_recno.html
void (*append_callback_method)(	RPDB_Database*		database,
								RPDB_Record*		record ) RPDB_DatabaseTypeRecnoSettingsController_appendCallback( RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{

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
int RPDB_DatabaseTypeRecnoSettingsController_internal_appendCallbackMethod(	DB*				bdb_database, 
																				DBT*			bdb_data, 
																				db_recno_t		record_number )	{
	
	RPDB_Database*	database	=	RPDB_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );
	
	RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller = RPDB_DatabaseTypeSettingsController_recnoSettingsController(
																							RPDB_DatabaseSettingsController_typeSettingsController( 
																								RPDB_Database_settingsController( database ) );
	RPDB_Record*	record		=	RPDB_Record_internal_newFromRawKeyDBTDataPair( & record_number,
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
RPDB_DatabaseTypeRecnoSettingsController* RPDB_DatabaseTypeRecnoSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{

	RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller_copy	=	RPDB_DatabaseTypeRecnoSettingsController_new( database_type_recno_settings_controller->parent_database_type_settings_controller );

	//	Instances and Pointers
	database_type_recno_settings_controller_copy->record_renumbering	=	database_type_recno_settings_controller->record_renumbering;
	database_type_recno_settings_controller_copy->source_file_path	=	database_type_recno_settings_controller->source_file_path;
	database_type_recno_settings_controller_copy->snapshot_isolation	=	database_type_recno_settings_controller->snapshot_isolation;

	return database_type_recno_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

void RPDB_DatabaseTypeRecnoSettingsController_internal_setFlags(	RPDB_DatabaseTypeRecnoSettingsController*		database_type_recno_settings_controller )	{
	
	RPDB_Database*			database = database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	database->wrapped_bdb_database->set_flags(	database->wrapped_bdb_database,
												RPDB_DatabaseTypeSettingsController_internal_setFlags( database_type_recno_settings_controller->parent_database_type_settings_controller )
												|	RPDB_DatabaseTypeRecnoSettingsController_recordRenumbering( database_type_recno_settings_controller )
												|	RPDB_DatabaseTypeRecnoSettingsController_snapshotIsolation( database_type_recno_settings_controller ) );
}

