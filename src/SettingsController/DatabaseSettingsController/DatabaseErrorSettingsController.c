/*
 *		RPbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseErrorSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseErrorSettingsController.h"

#include "ErrorController.h"
#include "DatabaseSettingsController.h"
#include "Environment.h"
#include "DatabaseRecordReadWriteSettingsController.h"

#include "DatabaseErrorSettingsController_internal.h"
#include "RuntimeStorageController_internal.h"

#include "Directory_internal.h"

#include "SettingsController.h"
#include "FileSettingsController.h"

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

RPbdb_DatabaseErrorSettingsController* RPbdb_DatabaseErrorSettingsController_new( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_DatabaseErrorSettingsController*		database_error_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseErrorSettingsController ) );

	database_error_settings_controller->parent_database_settings_controller = database_settings_controller;
	
	return database_error_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseErrorSettingsController_free(	RPbdb_DatabaseErrorSettingsController** database_error_settings_controller )	{

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
RPbdb_Environment* RPbdb_DatabaseErrorSettingsController_parentEnvironment(	RPbdb_DatabaseErrorSettingsController* database_error_settings_controller )	{
	return database_error_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseErrorSettingsController_parentDatabase(	RPbdb_DatabaseErrorSettingsController* database_error_settings_controller )	{
	return database_error_settings_controller->parent_database_settings_controller->parent_database;
}

/*************
*  file  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_errfile.html
FILE* RPbdb_DatabaseErrorSettingsController_file( RPbdb_DatabaseErrorSettingsController* database_error_settings_controller )	{
	
	RPbdb_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL
			&&	database_error_settings_controller->error_file == NULL )	{
		database->wrapped_bdb_database->get_errfile(	database->wrapped_bdb_database, 
																									&( database_error_settings_controller->error_file ) );
	}
	
	return database_error_settings_controller->error_file;
}

/****************
*  setFile  *
****************/

void RPbdb_DatabaseErrorSettingsController_setFile(	RPbdb_DatabaseErrorSettingsController*		database_error_settings_controller, 
																										FILE*										error_file )	{

	RPbdb_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

	database_error_settings_controller->error_file = error_file;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_errfile( database->wrapped_bdb_database, error_file );
	}
}

/************************
*  setFileFromPath  *
************************/

//	Presumably this FILE* needs to be closed
FILE* RPbdb_DatabaseErrorSettingsController_setFileFromPath(		RPbdb_DatabaseErrorSettingsController*		database_error_settings_controller, 
																															char*																		error_file_path )	{
	
	RPbdb_Environment*	environment	=	database_error_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
	RPbdb_SettingsController*			settings_controller				=	RPbdb_Environment_settingsController( environment );
	RPbdb_FileSettingsController*	file_settings_controller	=	RPbdb_SettingsController_fileSettingsController( settings_controller );
	
	//	Create if necessary only creates the db; we have to create the directory if it doesn't yet exist
	if ( RPbdb_FileSettingsController_createIfNecessary( file_settings_controller ) ){
		RPbdb_Directory_internal_ensureDirectoryPathExistsForFile( error_file_path );
	}
	
	errno = FALSE;
	FILE*		error_file	= fopen( error_file_path, "a");
	if ( errno )	{
		RPbdb_ErrorController_throwError(	RPbdb_ErrorController_new( database_error_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																																RP_ERROR_NO_FILE_AT_PATH,
																																"DatabaseErrorSettingsController_setFileFromPath",
																																strerror( errno ) );
		return NULL;
	}

	database_error_settings_controller->error_file_path = error_file_path;

	RPbdb_DatabaseErrorSettingsController_setFile( database_error_settings_controller, error_file );

	return error_file;
}

/**************
*  prefix  *
**************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_errpfx.html
char* RPbdb_DatabaseErrorSettingsController_prefix( RPbdb_DatabaseErrorSettingsController* database_error_settings_controller )	{

	RPbdb_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
			
		database->wrapped_bdb_database->get_errpfx(	database->wrapped_bdb_database, 
																								(const char**) &( database_error_settings_controller->error_prefix ) );
	}
	
	return database_error_settings_controller->error_prefix;
}

/******************
*  setPrefix  *
******************/

void RPbdb_DatabaseErrorSettingsController_setPrefix(	RPbdb_DatabaseErrorSettingsController*		database_error_settings_controller, 
														const char*									error_prefix )	{

	RPbdb_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
			
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
void RPbdb_DatabaseErrorSettingsController_setErrorCallbackMethod(	RPbdb_DatabaseErrorSettingsController*	database_error_settings_controller,
 																	void									(*error_callback_method)(	RPbdb_Environment*			environment,
																											   							const char*		error_prefix_string,
																											   							const char*		error_message	)	)	{

	RPbdb_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

	database_error_settings_controller->error_callback_method = error_callback_method;

	if ( database->wrapped_bdb_database )	{
		database->set_errcall(	database, 
								( database_error_settings_controller->error_callback_method == NULL ?
									NULL :
									& RPbdb_DatabaseErrorSettingsController_internal_errorCallback ) );
	}
}
*/
/****************************
*  errorCallbackMethod  *
****************************/
/*
void (*error_callback_method)(	RPbdb*			environment,
								const char*		error_prefix_string,
								const char*		error_message	) RPbdb_DatabaseErrorSettingsController_errorCallbackMethod( RPbdb_DatabaseErrorSettingsController* database_error_settings_controller )	{
	
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
void RPbdb_DatabaseErrorSettingsController_internal_errorCallbackMethod(	const DB_ENV*		bdb_environment,
																			const char*			error_prefix_string,
																			const char*			error_message )	{
	
	//	Retrieve RPbdb environment
	RPbdb_Environment*										environment								=	RPbdb_RuntimeStorageController_internal_environmentForBDBEnvironment( bdb_environment );
	
	RPbdb_DatabaseErrorSettingsController*		database_error_settings_controller		=	RPbdb_DatabaseSettingsController_errorSettingsController(
																								RPbdb_SettingsController_databaseSettingsController( 
																									RPbdb_Environment_settingsController( environment ) ) );
	
	//	Call user-specified callback
	* ( database_error_settings_controller->error_callback_method )( 	database_error_settings_controller,
																		error_prefix_string,
																		error_message );
}
*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseErrorSettingsController* RPbdb_DatabaseErrorSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseErrorSettingsController* database_error_settings_controller )	{

	RPbdb_DatabaseErrorSettingsController* database_error_settings_controller_copy	=	RPbdb_DatabaseErrorSettingsController_new( database_error_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_error_settings_controller_copy->error_prefix	=	database_error_settings_controller->error_prefix;
	database_error_settings_controller_copy->error_file_path	=	database_error_settings_controller->error_file_path;
	database_error_settings_controller_copy->error_file_is_open	=	database_error_settings_controller->error_file_is_open;
	database_error_settings_controller_copy->error_file	=	database_error_settings_controller->error_file;

	return database_error_settings_controller_copy;
}

