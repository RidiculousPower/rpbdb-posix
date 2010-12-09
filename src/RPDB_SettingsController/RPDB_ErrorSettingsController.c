/*
 *		Rbdb::ErrorSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_ErrorSettingsController.h"

#include "Rbdb_ErrorController.h"
#include "Rbdb_SettingsController.h"
#include "Rbdb_Environment.h"

#include "Rbdb_FileSettingsController.h"
#include "Rbdb_ErrorSettingsController_internal.h"
#include "Rbdb_RuntimeStorageController_internal.h"
	
#include "Rbdb_Directory_internal.h"

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

Rbdb_ErrorSettingsController* Rbdb_ErrorSettingsController_new( Rbdb_SettingsController* settings_controller )	{
	
	Rbdb_ErrorSettingsController*		error_settings_controller = calloc( 1, sizeof( Rbdb_ErrorSettingsController ) );

	error_settings_controller->parent_settings_controller = settings_controller;
	
	return error_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_ErrorSettingsController_free(	Rbdb_ErrorSettingsController** error_settings_controller )	{

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
Rbdb_Environment* Rbdb_ErrorSettingsController_parentEnvironment(	Rbdb_ErrorSettingsController* error_settings_controller )	{
	return error_settings_controller->parent_settings_controller->parent_environment;
}

/************
*  file  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errfile.html
FILE* Rbdb_ErrorSettingsController_file( Rbdb_ErrorSettingsController* error_settings_controller )	{
	
	Rbdb_Environment*		environment	= error_settings_controller->parent_settings_controller->parent_environment;
		
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
void Rbdb_ErrorSettingsController_setFile(	Rbdb_ErrorSettingsController*		error_settings_controller, 
																						FILE*								file )	{

	Rbdb_Environment*		environment;

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
FILE* Rbdb_ErrorSettingsController_setFileFromPath( Rbdb_ErrorSettingsController* error_settings_controller, char* file_path )	{

	Rbdb_Environment*		environment	= error_settings_controller->parent_settings_controller->parent_environment;

	Rbdb_SettingsController*			settings_controller				=	Rbdb_Environment_settingsController( environment );
	Rbdb_FileSettingsController*	file_settings_controller	=	Rbdb_SettingsController_fileSettingsController( settings_controller );
	
	//	Create if necessary only creates the db; we have to create the directory if it doesn't yet exist
	if ( Rbdb_FileSettingsController_createIfNecessary( file_settings_controller ) ){
		Rbdb_Directory_internal_ensureDirectoryPathExistsForFile( file_path );
	}	

	errno = FALSE;
	FILE*		file	= fopen( file_path, "a" );	

	if ( errno )	{
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( environment ), 
																			RP_ERROR_NO_FILE_AT_PATH, 
																			"Rbdb_ErrorSettingsController_setFileFromPath",
																			strerror( errno ) );
		return NULL;
	}
	
	error_settings_controller->error_file_path	=	file_path;
	
	Rbdb_ErrorSettingsController_setFile(	error_settings_controller, 
																				file );
	
	return file;
}

/************
*  prefix  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errpfx.html
char* Rbdb_ErrorSettingsController_prefix( Rbdb_ErrorSettingsController* error_settings_controller )	{

	Rbdb_Environment*		environment;

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
void Rbdb_ErrorSettingsController_setPrefix( Rbdb_ErrorSettingsController* error_settings_controller, char* error_prefix )	{

	Rbdb_Environment*		environment;

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
void Rbdb_ErrorSettingsController_setErrorCallbackMethod(	Rbdb_ErrorSettingsController*					error_settings_controller,
 															void (*error_callback_method)(	Rbdb_Environment*			environment,
																							const char*		error_prefix,
																							const char*		error_message ) )	{
	
	Rbdb_Environment*		environment;

	environment = error_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_errcall(	environment->wrapped_bdb_environment,
															( error_callback_method == NULL ?
																NULL :
																& Rbdb_ErrorSettingsController_internal_errorCallbackMethod ) );
	}
	
	error_settings_controller->error_callback_method = error_callback_method;
}
*/
/************************
*  errorCallbackMethod  *
************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errcall.html
void (*error_callback_method)(	Rbdb_Environment*			environment,
								const char*		error_prefix,
								const char*		error_message ) Rbdb_ErrorSettingsController_errorCallbackMethod( Rbdb_ErrorSettingsController* error_settings_controller )	{
	
	return error_settings_controller->error_callback_method;
}
*/

/*****************************
*  panicCallbackMethod  *
*****************************/
/*
void *(panic_callback_method)( Rbdb_Environment*	environment ) Rbdb_MessageSettingsController_panicCallbackMethod(	Rbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->panic_callback_method;
}
*/

/*****************************
*  setPanicCallbackMethod  *
*****************************/
/*
void Rbdb_MessageSettingsController_setPanicCallbackMethod(	Rbdb_MessageSettingsController*		message_settings_controller,
 																void *(panic_callback_method)( Rbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;

	message_settings_controller->panic_callback_method = panic_callback_method;
	//	Make sure we have our internal callback enabled
	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& Rbdb_MessageSettingsController_internal_eventCallbackMethod );
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
void Rbdb_ErrorSettingsController_internal_errorCallbackMethod(	const DB_ENV*		bdb_environment,
																	const char*			error_prefix,
																	const char*			error_message )	{
	
	Rbdb_Environment*							environment					=	Rbdb_RuntimeStorageController_internal_environmentForBDBEnvironment( bdb_environment );
	
	Rbdb_ErrorSettingsController*	error_settings_controller	=	Rbdb_SettingsController_errorSettingsController( Rbdb_Environment_settingsController( environment ) );
	
	*( error_settings_controller->error_callback_method )(	environment,
															error_prefix,
															error_message );
}
*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_ErrorSettingsController* Rbdb_ErrorSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_ErrorSettingsController* error_settings_controller )	{

	Rbdb_ErrorSettingsController* error_settings_controller_copy	=	Rbdb_ErrorSettingsController_new( error_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	error_settings_controller_copy->prefix	=	error_settings_controller->prefix;
	error_settings_controller_copy->error_file_is_open	=	error_settings_controller->error_file_is_open;
	error_settings_controller_copy->error_file	=	error_settings_controller->error_file;

	return error_settings_controller_copy;
}

