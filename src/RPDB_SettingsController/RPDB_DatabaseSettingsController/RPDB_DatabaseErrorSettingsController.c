/*
 *		RPDB::DatabaseController::Database::DatabaseSettingsController::DatabaseErrorSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseErrorSettingsController.h"

#include "RPDB_ErrorController.h"
#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_Environment.h"
#include "RPDB_DatabaseRecordReadWriteSettingsController.h"

#include "RPDB_DatabaseErrorSettingsController_internal.h"
#include "RPDB_RuntimeStorageController_internal.h"

#include "RPDB_Directory_internal.h"

#include "RPDB_SettingsController.h"
#include "RPDB_FileSettingsController.h"

#include <errno.h>
#include <string.h>
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseErrorSettingsController* RPDB_DatabaseErrorSettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseErrorSettingsController*		database_error_settings_controller = calloc( 1, sizeof( RPDB_DatabaseErrorSettingsController ) );

	database_error_settings_controller->parent_database_settings_controller = database_settings_controller;
	
	return database_error_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseErrorSettingsController_free(	RPDB_DatabaseErrorSettingsController** database_error_settings_controller )	{

	//	Make sure file is open so we don't close a closed file.
	if ( ( *database_error_settings_controller )->error_file_is_open )	{

		fclose( ( *database_error_settings_controller )->error_file );
		( *database_error_settings_controller )->error_file_is_open	=	FALSE;
		( *database_error_settings_controller )->error_file			=	NULL;
	}

	free( *database_error_settings_controller );
	*database_error_settings_controller	=	NULL;
}


/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseErrorSettingsController_parentEnvironment(	RPDB_DatabaseErrorSettingsController* database_error_settings_controller )	{
	return database_error_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseErrorSettingsController_parentDatabase(	RPDB_DatabaseErrorSettingsController* database_error_settings_controller )	{
	return database_error_settings_controller->parent_database_settings_controller->parent_database;
}

/*************
*  file  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_errfile.html
FILE* RPDB_DatabaseErrorSettingsController_file( RPDB_DatabaseErrorSettingsController* database_error_settings_controller )	{
	
	RPDB_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

	if ( database_error_settings_controller->error_file == NULL )	{
		database->wrapped_bdb_database->get_errfile(	database->wrapped_bdb_database, 
														&( database_error_settings_controller->error_file ) );
	}
	
	return database_error_settings_controller->error_file;
}

/****************
*  setFile  *
****************/

void RPDB_DatabaseErrorSettingsController_setFile(	RPDB_DatabaseErrorSettingsController*		database_error_settings_controller, 
																										FILE*										error_file )	{

	RPDB_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

	database_error_settings_controller->error_file = error_file;

	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_errfile( database->wrapped_bdb_database, error_file );
	}
}

/************************
*  setFileFromPath  *
************************/

//	Presumably this FILE* needs to be closed
FILE* RPDB_DatabaseErrorSettingsController_setFileFromPath(		RPDB_DatabaseErrorSettingsController*		database_error_settings_controller, 
																															char*																		error_file_path )	{
	
	RPDB_Environment*	environment	=	database_error_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
	RPDB_SettingsController*			settings_controller				=	RPDB_Environment_settingsController( environment );
	RPDB_FileSettingsController*	file_settings_controller	=	RPDB_SettingsController_fileSettingsController( settings_controller );
	
	//	Create if necessary only creates the db; we have to create the directory if it doesn't yet exist
	if ( RPDB_FileSettingsController_createIfNecessary( file_settings_controller ) ){
		RPDB_Directory_internal_ensureDirectoryPathExistsForFile( error_file_path );
	}
	
	errno = FALSE;
	FILE*		error_file	= fopen( error_file_path, "a");
	if ( errno )	{
		RPDB_ErrorController_throwError(	RPDB_ErrorController_new( database_error_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																																RP_ERROR_NO_FILE_AT_PATH,
																																"RPDB_DatabaseErrorSettingsController_setFileFromPath",
																																strerror( errno ) );
		return NULL;
	}

	database_error_settings_controller->error_file_path = error_file_path;

	RPDB_DatabaseErrorSettingsController_setFile( database_error_settings_controller, error_file );

	return error_file;
}

/**************
*  prefix  *
**************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_errpfx.html
char* RPDB_DatabaseErrorSettingsController_prefix( RPDB_DatabaseErrorSettingsController* database_error_settings_controller )	{

	RPDB_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->get_errpfx(	database->wrapped_bdb_database, 
													(const char**) &( database_error_settings_controller->error_prefix ) );
	}
	
	return database_error_settings_controller->error_prefix;
}

/******************
*  setPrefix  *
******************/

void RPDB_DatabaseErrorSettingsController_setPrefix(	RPDB_DatabaseErrorSettingsController*		database_error_settings_controller, 
														const char*									error_prefix )	{

	RPDB_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_errpfx(	database->wrapped_bdb_database,
													error_prefix );
	}
	
	database_error_settings_controller->error_prefix = (char*) error_prefix;
}

/****************************
*  setErrorCallbackMethod  *
****************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_errcall.html
void RPDB_DatabaseErrorSettingsController_setErrorCallbackMethod(	RPDB_DatabaseErrorSettingsController*	database_error_settings_controller,
 																	void									(*error_callback_method)(	RPDB_Environment*			environment,
																											   							const char*		error_prefix_string,
																											   							const char*		error_message	)	)	{

	RPDB_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

	database_error_settings_controller->error_callback_method = error_callback_method;

	if ( database->wrapped_bdb_database )	{
		database->set_errcall(	database, 
								( database_error_settings_controller->error_callback_method == NULL ?
									NULL :
									& RPDB_DatabaseErrorSettingsController_internal_errorCallback ) );
	}
}
*/
/****************************
*  errorCallbackMethod  *
****************************/
/*
void (*error_callback_method)(	RPDB*			environment,
								const char*		error_prefix_string,
								const char*		error_message	) RPDB_DatabaseErrorSettingsController_errorCallbackMethod( RPDB_DatabaseErrorSettingsController* database_error_settings_controller )	{
	
	return database_error_settings_controller->error_callback_method;
}
*/
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*********************
*  errorCallback  *
*********************/
/*
void RPDB_DatabaseErrorSettingsController_internal_errorCallbackMethod(	const DB_ENV*		bdb_environment,
																			const char*			error_prefix_string,
																			const char*			error_message )	{
	
	//	Retrieve RPDB environment
	RPDB_Environment*										environment								=	RPDB_RuntimeStorageController_internal_environmentForBDBEnvironment( bdb_environment );
	
	RPDB_DatabaseErrorSettingsController*		database_error_settings_controller		=	RPDB_DatabaseSettingsController_errorSettingsController(
																								RPDB_SettingsController_databaseSettingsController( 
																									RPDB_Environment_settingsController( environment ) ) );
	
	//	Call user-specified callback
	* ( database_error_settings_controller->error_callback_method )( 	database_error_settings_controller,
																		error_prefix_string,
																		error_message );
}
*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseErrorSettingsController* RPDB_DatabaseErrorSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseErrorSettingsController* database_error_settings_controller )	{

	RPDB_DatabaseErrorSettingsController* database_error_settings_controller_copy	=	RPDB_DatabaseErrorSettingsController_new( database_error_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_error_settings_controller_copy->error_prefix	=	database_error_settings_controller->error_prefix;
	database_error_settings_controller_copy->error_file_path	=	database_error_settings_controller->error_file_path;
	database_error_settings_controller_copy->error_file_is_open	=	database_error_settings_controller->error_file_is_open;
	database_error_settings_controller_copy->error_file	=	database_error_settings_controller->error_file;

	return database_error_settings_controller_copy;
}

