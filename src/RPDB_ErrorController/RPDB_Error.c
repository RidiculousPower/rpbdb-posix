/*
 *		RPDB::ErrorController::Error
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_Error.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

//	instantiate a new error struct and return it
RPDB_Error* RPDB_Error_new( RPDB_ErrorController* error_controller )	{

	RPDB_Error*		error = calloc( 1, sizeof( RPDB_Error ) );

	error->parent_error_controller = error_controller;

	return error;
}

/****************************
*  newWithNumberFunction  *
****************************/

//	instantiate a new error struct, set error_number, error_function, and additional_explanation_message
RPDB_Error* RPDB_Error_newErrorWithNumberFunction(	RPDB_ErrorController*	parent_error_controller, 
														int						error_number, 
														char*					error_function )	{

	RPDB_Error*		error = RPDB_Error_new( parent_error_controller );

	error->number = error_number;
	error->function = error_function;

	return error;
}

/****************************************
*  newWithNumberFunctionAndMessage  *
****************************************/

//	instantiate a new error struct, set error_number, error_function, and additional_explanation_message
RPDB_Error* RPDB_Error_newErrorWithNumberFunctionAndMessage(	RPDB_ErrorController*	parent_error_controller, 
																int						error_number, 
																char*					error_function, 
																char*					additional_explanation_message )	{

	RPDB_Error*		error = RPDB_Error_newErrorWithNumberFunction( parent_error_controller, error_number, error_function );

	error->message = additional_explanation_message;

	return error;
}

/***************************
*  free  *
***************************/
void RPDB_Error_free(	RPDB_Error** error )	{

	free( error );
}

/***************************
*  settingsController  *
***************************/
RPDB_ErrorSettingsController* RPDB_Error_settingsController(	RPDB_Error* error )	{
	return error->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_Error_parentEnvironment(	RPDB_Error* error )	{
	return error->parent_error_controller->parent_environment;
}

/****************
*  terminate  *
****************/

//	Prints error that has been thrown and Terminates the application. 
void RPDB_Error_terminate( RPDB_Error* error )	{

	RPDB_Error_internal_outputBDBError( error );
	
	fprintf(	stdout,
				"Terminating from error.\n\n" );
	raise( SIGTERM );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********************
*  outputBDBError  *
*******************/

//	Prints to stderr an error that has been thrown
void RPDB_Error_internal_outputBDBError( RPDB_Error* error )	{
	
	fprintf( stderr, "Error (%s): %s",	error->function, 
								db_strerror( error->number )  );
	if ( error->message != NULL )	{
		fprintf( stderr, " - \"%s\"", error->message );
	}
	fprintf( stderr, "\n" );
}




