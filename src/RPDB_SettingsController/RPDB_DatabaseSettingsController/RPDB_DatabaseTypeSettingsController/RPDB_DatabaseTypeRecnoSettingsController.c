/*
 *		Rbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeRecnoSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseTypeRecnoSettingsController.h"

#include "Rbdb_Environment.h"
#include "Rbdb_ErrorController.h"
#include "Rbdb_DatabaseTypeSettingsController.h"
#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_Database.h"
#include "Rbdb_Record.h"

#include "Rbdb_DatabaseTypeRecnoSettingsController_internal.h"
#include "Rbdb_RuntimeStorageController_internal.h"
#include "Rbdb_Record_internal.h"

#include "Rbdb_DatabaseTypeSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_DatabaseTypeRecnoSettingsController* Rbdb_DatabaseTypeRecnoSettingsController_new( Rbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller )	{

	Rbdb_DatabaseTypeRecnoSettingsController*		database_type_recno_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseTypeRecnoSettingsController ) );

	database_type_recno_settings_controller->parent_database_type_settings_controller = parent_database_type_settings_controller;

	return database_type_recno_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseTypeRecnoSettingsController_free(	Rbdb_DatabaseTypeRecnoSettingsController** database_type_recno_settings_controller )	{

	free( *database_type_recno_settings_controller );
	*database_type_recno_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseTypeRecnoSettingsController_parentEnvironment(	Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	return database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseTypeRecnoSettingsController_parentDatabase(	Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	return database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/*************************
*  recordRenumbering  *
*************************/

//	DB_RENUMBER				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL Rbdb_DatabaseTypeRecnoSettingsController_recordRenumbering( Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{

	if ( database_type_recno_settings_controller->record_renumbering )	{

		return DB_RENUMBER;
	}

	return FALSE;
}

	/*********************************
	*  turnRecordRenumberingOn  *
	*********************************/

	void Rbdb_DatabaseTypeRecnoSettingsController_turnRecordRenumberingOn( Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
		database_type_recno_settings_controller->record_renumbering = TRUE;
	}

	/*********************************
	*  turnRecordRenumberingOff  *
	*********************************/

	void Rbdb_DatabaseTypeRecnoSettingsController_turnRecordRenumberingOff( Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
		database_type_recno_settings_controller->record_renumbering = FALSE;
	}

/*****************
*  snapshot  *
*****************/

//	DB_SNAPSHOT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL Rbdb_DatabaseTypeRecnoSettingsController_snapshotIsolation( Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{

	if ( database_type_recno_settings_controller->snapshot_isolation )	{
	
		return DB_SNAPSHOT;
	}
	
	return FALSE;
}

	/*********************************
	*  turnSnapshotIsolationOn  *
	*********************************/

	void Rbdb_DatabaseTypeRecnoSettingsController_turnSnapshotIsolationOn( Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
		database_type_recno_settings_controller->snapshot_isolation = TRUE;
	}

	/*********************************
	*  turnSnapshotIsolationOff  *
	*********************************/

	void Rbdb_DatabaseTypeRecnoSettingsController_turnSnapshotIsolationOff( Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
		database_type_recno_settings_controller->snapshot_isolation = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/******************
*  sourceFile  *
******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_re_source.html
char* Rbdb_DatabaseTypeRecnoSettingsController_sourceFile( Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{
	
	int		connection_error	= 0;
	Rbdb_Database*		database	=	database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	if (	database_type_recno_settings_controller->source_file_path == NULL
		&&	database->wrapped_bdb_database != NULL )	{
		
		//	Get the record number source
		if ( ( connection_error = database->wrapped_bdb_database->get_re_source(	database->wrapped_bdb_database, 
															(const char**) &( database_type_recno_settings_controller->source_file_path ) ) ) )	{
		
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"Rbdb_DatabaseTypeRecnoSettingsController_sourceFile" );
		}
	}
	
	return database_type_recno_settings_controller->source_file_path;
}

/*********************
*  setSourceFile  *
*********************/

void Rbdb_DatabaseTypeRecnoSettingsController_setSourceFile(	Rbdb_DatabaseTypeRecnoSettingsController*	database_type_recno_settings_controller,
																char*										file_path )	{
	
	Rbdb_Database*	database	= database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{

		int		connection_error	= RP_NO_ERROR;
		//	Set the record number source
		if ( ( connection_error = database->wrapped_bdb_database->set_re_source(	database->wrapped_bdb_database,
																					file_path )  ) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"Rbdb_DatabaseTypeRecnoSettingsController_setSourceFile" );
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
void Rbdb_DatabaseTypeRecnoSettingsController_setAppendCallbackMethod(	Rbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller,
 																		int (*append_callback_method)(	Rbdb_Database*		database,
																										Rbdb_Record*		record ) )	{

 Rbdb_Database*	database	= database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;

	int			connection_error	= 0;

	if ( ( connection_error = database->set_append_recno(	database, 
															( database_type_recno_settings_controller->append_callback_method == NULL ?
															 	NULL :
																& Rbdb_DatabaseTypeHashSettingsController_internal_appendCallbackMethod ) ) )	{

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"Rbdb_DatabaseTypeRecnoSettingsController_appendCallbackMethod" );
	}

	database_type_recno_settings_controller->append_callback_method = append_callback_method;
}
*/
/*****************************
*  appendCallbackMethod  *
*****************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_append_recno.html
void (*append_callback_method)(	Rbdb_Database*		database,
								Rbdb_Record*		record ) Rbdb_DatabaseTypeRecnoSettingsController_appendCallback( Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{

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
int Rbdb_DatabaseTypeRecnoSettingsController_internal_appendCallbackMethod(	DB*				bdb_database, 
																				DBT*			bdb_data, 
																				db_recno_t		record_number )	{
	
	Rbdb_Database*	database	=	Rbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );
	
	Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller = Rbdb_DatabaseTypeSettingsController_recnoSettingsController(
																							Rbdb_DatabaseSettingsController_typeSettingsController( 
																								Rbdb_Database_settingsController( database ) );
	Rbdb_Record*	record		=	Rbdb_Record_internal_newFromRawKeyDBTDataPair( & record_number,
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
Rbdb_DatabaseTypeRecnoSettingsController* Rbdb_DatabaseTypeRecnoSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller )	{

	Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller_copy	=	Rbdb_DatabaseTypeRecnoSettingsController_new( database_type_recno_settings_controller->parent_database_type_settings_controller );

	//	Instances and Pointers
	database_type_recno_settings_controller_copy->record_renumbering	=	database_type_recno_settings_controller->record_renumbering;
	database_type_recno_settings_controller_copy->source_file_path	=	database_type_recno_settings_controller->source_file_path;
	database_type_recno_settings_controller_copy->snapshot_isolation	=	database_type_recno_settings_controller->snapshot_isolation;

	return database_type_recno_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

void Rbdb_DatabaseTypeRecnoSettingsController_internal_setFlags(	Rbdb_DatabaseTypeRecnoSettingsController*		database_type_recno_settings_controller )	{
	
	Rbdb_Database*			database = database_type_recno_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	database->wrapped_bdb_database->set_flags(	database->wrapped_bdb_database,
												Rbdb_DatabaseTypeSettingsController_internal_setFlags( database_type_recno_settings_controller->parent_database_type_settings_controller )
												|	Rbdb_DatabaseTypeRecnoSettingsController_recordRenumbering( database_type_recno_settings_controller )
												|	Rbdb_DatabaseTypeRecnoSettingsController_snapshotIsolation( database_type_recno_settings_controller ) );
}

