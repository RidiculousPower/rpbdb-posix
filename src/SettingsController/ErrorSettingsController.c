/*
 *		RPbdb::ErrorSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "ErrorSettingsController.h"

#include "ErrorController.h"
#include "SettingsController.h"
#include "Environment.h"

#include "FileSettingsController.h"
#include "ErrorSettingsController_internal.h"
#include "RuntimeStorageController_internal.h"
	
#include "Directory_internal.h"

#include <errno.h>
#include <string.h>
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_ErrorSettingsController* RPbdb_ErrorSettingsController_new( RPbdb_SettingsController* settings_controller )	{
	
	RPbdb_ErrorSettingsController*		error_settings_controller = calloc( 1, sizeof( RPbdb_ErrorSettingsController ) );

	error_settings_controller->parent_settings_controller = settings_controller;
	
	return error_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_ErrorSettingsController_free(	RPbdb_ErrorSettingsController** error_settings_controller )	{

	//	Make sure file is open so we don't close a closed file.
	if ( ( *error_settings_controller )->error_file_is_open )	{

		fclose( ( *error_settings_controller )->error_file );
		( *error_settings_controller )->error_file_is_open	=	FALSE;
		( *error_settings_controller )->error_file			=	NULL;
	}

	free( *error_settings_controller );
	*error_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_ErrorSettingsController_parentEnvironment(	RPbdb_ErrorSettingsController* error_settings_controller )	{
	return error_settings_controller->parent_settings_controller->parent_environment;
}

/************
*  file  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errfile.html
FILE* RPbdb_ErrorSettingsController_file( RPbdb_ErrorSettingsController* error_settings_controller )	{
	
	RPbdb_Environment*		environment	= error_settings_controller->parent_settings_controller->parent_environment;
		
	if (	error_settings_controller->error_file == NULL
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->get_errfile(	environment->wrapped_bdb_environment, 
															&( error_settings_controller->error_file ) );
	}
	
	return error_settings_controller->error_file;
}

/****************
*  setFile  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errfile.html
void RPbdb_ErrorSettingsController_setFile(	RPbdb_ErrorSettingsController*		error_settings_controller, 
																						FILE*								file )	{

	RPbdb_Environment*		environment;

	environment = error_settings_controller->parent_settings_controller->parent_environment;

	error_settings_controller->error_file = file;
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_errfile(	environment->wrapped_bdb_environment, 
																												file );
	}
}

/************************
*  setFileFromPath  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errfile.html
FILE* RPbdb_ErrorSettingsController_setFileFromPath( RPbdb_ErrorSettingsController* error_settings_controller, char* file_path )	{

	RPbdb_Environment*		environment	= error_settings_controller->parent_settings_controller->parent_environment;

	RPbdb_SettingsController*			settings_controller				=	RPbdb_Environment_settingsController( environment );
	RPbdb_FileSettingsController*	file_settings_controller	=	RPbdb_SettingsController_fileSettingsController( settings_controller );
	
	//	Create if necessary only creates the db; we have to create the directory if it doesn't yet exist
	if ( RPbdb_FileSettingsController_createIfNecessary( file_settings_controller ) ){
		RPbdb_Directory_internal_ensureDirectoryPathExistsForFile( file_path );
	}	

	errno = FALSE;
	FILE*		file	= fopen( file_path, "a" );	

	if ( errno )	{
		RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( environment ), 
																			RP_ERROR_NO_FILE_AT_PATH, 
																			"ErrorSettingsController_setFileFromPath",
																			strerror( errno ) );
		return NULL;
	}
	
	error_settings_controller->error_file_path	=	file_path;
	
	RPbdb_ErrorSettingsController_setFile(	error_settings_controller, 
																				file );
	
	return file;
}

/************
*  prefix  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errpfx.html
char* RPbdb_ErrorSettingsController_prefix( RPbdb_ErrorSettingsController* error_settings_controller )	{

	RPbdb_Environment*		environment;

	environment = error_settings_controller->parent_settings_controller->parent_environment;

	if ( error_settings_controller->prefix == NULL )	{
		environment->wrapped_bdb_environment->get_errpfx(	environment->wrapped_bdb_environment, 
																											(const char**) &( error_settings_controller->prefix ) );	
	}
	
	return error_settings_controller->prefix;
}

/****************
*  setPrefix  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errpfx.html
void RPbdb_ErrorSettingsController_setPrefix( RPbdb_ErrorSettingsController* error_settings_controller, char* error_prefix )	{

	RPbdb_Environment*		environment;

	environment = error_settings_controller->parent_settings_controller->parent_environment;

	error_settings_controller->prefix = error_prefix;
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_errpfx(	environment->wrapped_bdb_environment, 
															error_prefix );
	}
}

/****************************
*  setErrorCallbackMethod  *
****************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errcall.html
void RPbdb_ErrorSettingsController_setErrorCallbackMethod(	RPbdb_ErrorSettingsController*					error_settings_controller,
 															void (*error_callback_method)(	RPbdb_Environment*			environment,
																							const char*		error_prefix,
																							const char*		error_message ) )	{
	
	RPbdb_Environment*		environment;

	environment = error_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_errcall(	environment->wrapped_bdb_environment,
															( error_callback_method == NULL ?
																NULL :
																& RPbdb_ErrorSettingsController_internal_errorCallbackMethod ) );
	}
	
	error_settings_controller->error_callback_method = error_callback_method;
}
*/
/************************
*  errorCallbackMethod  *
************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errcall.html
void (*error_callback_method)(	RPbdb_Environment*			environment,
								const char*		error_prefix,
								const char*		error_message ) RPbdb_ErrorSettingsController_errorCallbackMethod( RPbdb_ErrorSettingsController* error_settings_controller )	{
	
	return error_settings_controller->error_callback_method;
}
*/

/*****************************
*  panicCallbackMethod  *
*****************************/
/*
void *(panic_callback_method)( RPbdb_Environment*	environment ) RPbdb_MessageSettingsController_panicCallbackMethod(	RPbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->panic_callback_method;
}
*/

/*****************************
*  setPanicCallbackMethod  *
*****************************/
/*
void RPbdb_MessageSettingsController_setPanicCallbackMethod(	RPbdb_MessageSettingsController*		message_settings_controller,
 																void *(panic_callback_method)( RPbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;

	message_settings_controller->panic_callback_method = panic_callback_method;
	//	Make sure we have our internal callback enabled
	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& RPbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************************
*  errorCallbackMethod  *
************************/
/*
void RPbdb_ErrorSettingsController_internal_errorCallbackMethod(	const DB_ENV*		bdb_environment,
																	const char*			error_prefix,
																	const char*			error_message )	{
	
	RPbdb_Environment*							environment					=	RPbdb_RuntimeStorageController_internal_environmentForBDBEnvironment( bdb_environment );
	
	RPbdb_ErrorSettingsController*	error_settings_controller	=	RPbdb_SettingsController_errorSettingsController( RPbdb_Environment_settingsController( environment ) );
	
	*( error_settings_controller->error_callback_method )(	environment,
															error_prefix,
															error_message );
}
*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_ErrorSettingsController* RPbdb_ErrorSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_ErrorSettingsController* error_settings_controller )	{

	RPbdb_ErrorSettingsController* error_settings_controller_copy	=	RPbdb_ErrorSettingsController_new( error_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	error_settings_controller_copy->prefix	=	error_settings_controller->prefix;
	error_settings_controller_copy->error_file_is_open	=	error_settings_controller->error_file_is_open;
	error_settings_controller_copy->error_file	=	error_settings_controller->error_file;

	return error_settings_controller_copy;
}

