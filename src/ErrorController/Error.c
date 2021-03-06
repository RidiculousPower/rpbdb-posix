/*
 *		RPbdb::ErrorController::Error
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Error.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

//	instantiate a new error struct and return it
RPbdb_Error* RPbdb_Error_new( RPbdb_ErrorController* error_controller )	{

	RPbdb_Error*		error = calloc( 1, sizeof( RPbdb_Error ) );

	error->parent_error_controller = error_controller;

	return error;
}

/****************************
*  newWithNumberFunction  *
****************************/

//	instantiate a new error struct, set error_number, error_function, and additional_explanation_message
RPbdb_Error* RPbdb_Error_newErrorWithNumberFunction(	RPbdb_ErrorController*	parent_error_controller, 
														int						error_number, 
														char*					error_function )	{

	RPbdb_Error*		error = RPbdb_Error_new( parent_error_controller );

	error->number = error_number;
	error->function = error_function;

	return error;
}

/****************************************
*  newWithNumberFunctionAndMessage  *
****************************************/

//	instantiate a new error struct, set error_number, error_function, and additional_explanation_message
RPbdb_Error* RPbdb_Error_newErrorWithNumberFunctionAndMessage(	RPbdb_ErrorController*	parent_error_controller, 
																int						error_number, 
																char*					error_function, 
																char*					additional_explanation_message )	{

	RPbdb_Error*		error = RPbdb_Error_newErrorWithNumberFunction( parent_error_controller, error_number, error_function );

	error->message = additional_explanation_message;

	return error;
}

/***************************
*  free  *
***************************/
void RPbdb_Error_free(	RPbdb_Error** error )	{

	free( error );
}

/***************************
*  settingsController  *
***************************/
RPbdb_ErrorSettingsController* RPbdb_Error_settingsController(	RPbdb_Error* error )	{
	return error->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_Error_parentEnvironment(	RPbdb_Error* error )	{
	return error->parent_error_controller->parent_environment;
}

/****************
*  terminate  *
****************/

//	Prints error that has been thrown and Terminates the application. 
void RPbdb_Error_terminate( RPbdb_Error* error )	{

	RPbdb_Error_internal_outputBDBError( error );
	
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
void RPbdb_Error_internal_outputBDBError( RPbdb_Error* error )	{
	
	fprintf( stderr, "Error (%s): %s",	error->function, 
								db_strerror( error->number )  );
	if ( error->message != NULL )	{
		fprintf( stderr, " - \"%s\"", error->message );
	}
	fprintf( stderr, "\n" );
}




