/*
 *		Rbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseErrorSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseErrorSettingsController.h"

#include "Rbdb_ErrorController.h"
#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_Environment.h"
#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"

#include "Rbdb_DatabaseErrorSettingsController_internal.h"
#include "Rbdb_RuntimeStorageController_internal.h"

#include "Rbdb_Directory_internal.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_FileSettingsController.h"

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

Rbdb_DatabaseErrorSettingsController* Rbdb_DatabaseErrorSettingsController_new( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_DatabaseErrorSettingsController*		database_error_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseErrorSettingsController ) );

	database_error_settings_controller->parent_database_settings_controller = database_settings_controller;
	
	return database_error_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseErrorSettingsController_free(	Rbdb_DatabaseErrorSettingsController** database_error_settings_controller )	{

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
Rbdb_Environment* Rbdb_DatabaseErrorSettingsController_parentEnvironment(	Rbdb_DatabaseErrorSettingsController* database_error_settings_controller )	{
	return database_error_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseErrorSettingsController_parentDatabase(	Rbdb_DatabaseErrorSettingsController* database_error_settings_controller )	{
	return database_error_settings_controller->parent_database_settings_controller->parent_database;
}

/*************
*  file  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_errfile.html
FILE* Rbdb_DatabaseErrorSettingsController_file( Rbdb_DatabaseErrorSettingsController* database_error_settings_controller )	{
	
	Rbdb_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

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

void Rbdb_DatabaseErrorSettingsController_setFile(	Rbdb_DatabaseErrorSettingsController*		database_error_settings_controller, 
																										FILE*										error_file )	{

	Rbdb_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

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
FILE* Rbdb_DatabaseErrorSettingsController_setFileFromPath(		Rbdb_DatabaseErrorSettingsController*		database_error_settings_controller, 
																															char*																		error_file_path )	{
	
	Rbdb_Environment*	environment	=	database_error_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
	Rbdb_SettingsController*			settings_controller				=	Rbdb_Environment_settingsController( environment );
	Rbdb_FileSettingsController*	file_settings_controller	=	Rbdb_SettingsController_fileSettingsController( settings_controller );
	
	//	Create if necessary only creates the db; we have to create the directory if it doesn't yet exist
	if ( Rbdb_FileSettingsController_createIfNecessary( file_settings_controller ) ){
		Rbdb_Directory_internal_ensureDirectoryPathExistsForFile( error_file_path );
	}
	
	errno = FALSE;
	FILE*		error_file	= fopen( error_file_path, "a");
	if ( errno )	{
		Rbdb_ErrorController_throwError(	Rbdb_ErrorController_new( database_error_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																																RP_ERROR_NO_FILE_AT_PATH,
																																"Rbdb_DatabaseErrorSettingsController_setFileFromPath",
																																strerror( errno ) );
		return NULL;
	}

	database_error_settings_controller->error_file_path = error_file_path;

	Rbdb_DatabaseErrorSettingsController_setFile( database_error_settings_controller, error_file );

	return error_file;
}

/**************
*  prefix  *
**************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_errpfx.html
char* Rbdb_DatabaseErrorSettingsController_prefix( Rbdb_DatabaseErrorSettingsController* database_error_settings_controller )	{

	Rbdb_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

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

void Rbdb_DatabaseErrorSettingsController_setPrefix(	Rbdb_DatabaseErrorSettingsController*		database_error_settings_controller, 
														const char*									error_prefix )	{

	Rbdb_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

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
void Rbdb_DatabaseErrorSettingsController_setErrorCallbackMethod(	Rbdb_DatabaseErrorSettingsController*	database_error_settings_controller,
 																	void									(*error_callback_method)(	Rbdb_Environment*			environment,
																											   							const char*		error_prefix_string,
																											   							const char*		error_message	)	)	{

	Rbdb_Database*	database	= database_error_settings_controller->parent_database_settings_controller->parent_database;

	database_error_settings_controller->error_callback_method = error_callback_method;

	if ( database->wrapped_bdb_database )	{
		database->set_errcall(	database, 
								( database_error_settings_controller->error_callback_method == NULL ?
									NULL :
									& Rbdb_DatabaseErrorSettingsController_internal_errorCallback ) );
	}
}
*/
/****************************
*  errorCallbackMethod  *
****************************/
/*
void (*error_callback_method)(	Rbdb*			environment,
								const char*		error_prefix_string,
								const char*		error_message	) Rbdb_DatabaseErrorSettingsController_errorCallbackMethod( Rbdb_DatabaseErrorSettingsController* database_error_settings_controller )	{
	
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
void Rbdb_DatabaseErrorSettingsController_internal_errorCallbackMethod(	const DB_ENV*		bdb_environment,
																			const char*			error_prefix_string,
																			const char*			error_message )	{
	
	//	Retrieve Rbdb environment
	Rbdb_Environment*										environment								=	Rbdb_RuntimeStorageController_internal_environmentForBDBEnvironment( bdb_environment );
	
	Rbdb_DatabaseErrorSettingsController*		database_error_settings_controller		=	Rbdb_DatabaseSettingsController_errorSettingsController(
																								Rbdb_SettingsController_databaseSettingsController( 
																									Rbdb_Environment_settingsController( environment ) ) );
	
	//	Call user-specified callback
	* ( database_error_settings_controller->error_callback_method )( 	database_error_settings_controller,
																		error_prefix_string,
																		error_message );
}
*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_DatabaseErrorSettingsController* Rbdb_DatabaseErrorSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseErrorSettingsController* database_error_settings_controller )	{

	Rbdb_DatabaseErrorSettingsController* database_error_settings_controller_copy	=	Rbdb_DatabaseErrorSettingsController_new( database_error_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_error_settings_controller_copy->error_prefix	=	database_error_settings_controller->error_prefix;
	database_error_settings_controller_copy->error_file_path	=	database_error_settings_controller->error_file_path;
	database_error_settings_controller_copy->error_file_is_open	=	database_error_settings_controller->error_file_is_open;
	database_error_settings_controller_copy->error_file	=	database_error_settings_controller->error_file;

	return database_error_settings_controller_copy;
}

