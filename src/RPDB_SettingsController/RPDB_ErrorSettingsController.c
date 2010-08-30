/*
 *		RPDB::ErrorSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_ErrorSettingsController.h"

#include "RPDB_ErrorController.h"
#include "RPDB_SettingsController.h"
#include "RPDB_Environment.h"

#include "RPDB_ErrorSettingsController_internal.h"
#include "RPDB_RuntimeStorageController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_ErrorSettingsController* RPDB_ErrorSettingsController_new( RPDB_SettingsController* settings_controller )	{
	
	RPDB_ErrorSettingsController*		error_settings_controller = calloc( 1, sizeof( RPDB_ErrorSettingsController ) );

	error_settings_controller->parent_settings_controller = settings_controller;
	
	return error_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_ErrorSettingsController_free(	RPDB_ErrorSettingsController** error_settings_controller )	{

	//	Make sure file is open so we don't close a closed file.
	if ( ( *error_settings_controller )->file_is_open )	{

		fclose( ( *error_settings_controller )->file );
		( *error_settings_controller )->file_is_open	=	FALSE;
		( *error_settings_controller )->file			=	NULL;
	}

	free( *error_settings_controller );
	*error_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_ErrorSettingsController_parentEnvironment(	RPDB_ErrorSettingsController* error_settings_controller )	{
	return error_settings_controller->parent_settings_controller->parent_environment;
}

/************
*  file  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errfile.html
FILE* RPDB_ErrorSettingsController_file( RPDB_ErrorSettingsController* error_settings_controller )	{
	
	RPDB_Environment*		environment	= error_settings_controller->parent_settings_controller->parent_environment;
		
	if (	error_settings_controller->file == NULL
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->get_errfile(	environment->wrapped_bdb_environment, 
															&( error_settings_controller->file ) );
	}
	
	return error_settings_controller->file;
}

/****************
*  setFile  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errfile.html
void RPDB_ErrorSettingsController_setFile(	RPDB_ErrorSettingsController*		error_settings_controller, 
											FILE*								file )	{

	RPDB_Environment*		environment;

	environment = error_settings_controller->parent_settings_controller->parent_environment;

	error_settings_controller->file = file;
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_errfile(	environment->wrapped_bdb_environment, 
															file );
	}
}

/************************
*  setFileFromPath  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errfile.html
FILE* RPDB_ErrorSettingsController_setFileFromPath( RPDB_ErrorSettingsController* error_settings_controller, char* file_path )	{

	RPDB_Environment*		environment;
	FILE*		file;

	environment = error_settings_controller->parent_settings_controller->parent_environment;

	file = fopen( file_path, "w");

	if ( file == NULL )	{
		RPDB_ErrorController_throwError(	RPDB_Environment_errorController( environment ), 
											RP_ERROR_NO_FILE_AT_PATH, 
											"RPDB_ErrorSettingsController_setFileFromPath",
											"File not found at path." );
		return NULL;
	}
	
	RPDB_ErrorSettingsController_setFile(	error_settings_controller, 
											file );
	
	return file;
}

/************
*  prefix  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errpfx.html
char* RPDB_ErrorSettingsController_prefix( RPDB_ErrorSettingsController* error_settings_controller )	{

	RPDB_Environment*		environment;

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
void RPDB_ErrorSettingsController_setPrefix( RPDB_ErrorSettingsController* error_settings_controller, char* error_prefix )	{

	RPDB_Environment*		environment;

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
void RPDB_ErrorSettingsController_setErrorCallbackMethod(	RPDB_ErrorSettingsController*					error_settings_controller,
 															void (*error_callback_method)(	RPDB_Environment*			environment,
																							const char*		error_prefix,
																							const char*		error_message ) )	{
	
	RPDB_Environment*		environment;

	environment = error_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_errcall(	environment->wrapped_bdb_environment,
															( error_callback_method == NULL ?
																NULL :
																& RPDB_ErrorSettingsController_internal_errorCallbackMethod ) );
	}
	
	error_settings_controller->error_callback_method = error_callback_method;
}
*/
/************************
*  errorCallbackMethod  *
************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_errcall.html
void (*error_callback_method)(	RPDB_Environment*			environment,
								const char*		error_prefix,
								const char*		error_message ) RPDB_ErrorSettingsController_errorCallbackMethod( RPDB_ErrorSettingsController* error_settings_controller )	{
	
	return error_settings_controller->error_callback_method;
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
void RPDB_ErrorSettingsController_internal_errorCallbackMethod(	const DB_ENV*		bdb_environment,
																	const char*			error_prefix,
																	const char*			error_message )	{
	
	RPDB_Environment*							environment					=	RPDB_RuntimeStorageController_internal_environmentForBDBEnvironment( bdb_environment );
	
	RPDB_ErrorSettingsController*	error_settings_controller	=	RPDB_SettingsController_errorSettingsController( RPDB_Environment_settingsController( environment ) );
	
	*( error_settings_controller->error_callback_method )(	environment,
															error_prefix,
															error_message );
}
*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_ErrorSettingsController* RPDB_ErrorSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_ErrorSettingsController* error_settings_controller )	{

	RPDB_ErrorSettingsController* error_settings_controller_copy	=	RPDB_ErrorSettingsController_new( error_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	error_settings_controller_copy->prefix	=	error_settings_controller->prefix;
	error_settings_controller_copy->file_is_open	=	error_settings_controller->file_is_open;
	error_settings_controller_copy->file	=	error_settings_controller->file;

	return error_settings_controller_copy;
}

