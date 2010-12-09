/*
 *		Rbdb::ErrorController::Error
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_Error.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

//	instantiate a new error struct and return it
Rbdb_Error* Rbdb_Error_new( Rbdb_ErrorController* error_controller )	{

	Rbdb_Error*		error = calloc( 1, sizeof( Rbdb_Error ) );

	error->parent_error_controller = error_controller;

	return error;
}

/****************************
*  newWithNumberFunction  *
****************************/

//	instantiate a new error struct, set error_number, error_function, and additional_explanation_message
Rbdb_Error* Rbdb_Error_newErrorWithNumberFunction(	Rbdb_ErrorController*	parent_error_controller, 
														int						error_number, 
														char*					error_function )	{

	Rbdb_Error*		error = Rbdb_Error_new( parent_error_controller );

	error->number = error_number;
	error->function = error_function;

	return error;
}

/****************************************
*  newWithNumberFunctionAndMessage  *
****************************************/

//	instantiate a new error struct, set error_number, error_function, and additional_explanation_message
Rbdb_Error* Rbdb_Error_newErrorWithNumberFunctionAndMessage(	Rbdb_ErrorController*	parent_error_controller, 
																int						error_number, 
																char*					error_function, 
																char*					additional_explanation_message )	{

	Rbdb_Error*		error = Rbdb_Error_newErrorWithNumberFunction( parent_error_controller, error_number, error_function );

	error->message = additional_explanation_message;

	return error;
}

/***************************
*  free  *
***************************/
void Rbdb_Error_free(	Rbdb_Error** error )	{

	free( error );
}

/***************************
*  settingsController  *
***************************/
Rbdb_ErrorSettingsController* Rbdb_Error_settingsController(	Rbdb_Error* error )	{
	return error->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_Error_parentEnvironment(	Rbdb_Error* error )	{
	return error->parent_error_controller->parent_environment;
}

/****************
*  terminate  *
****************/

//	Prints error that has been thrown and Terminates the application. 
void Rbdb_Error_terminate( Rbdb_Error* error )	{

	Rbdb_Error_internal_outputBDBError( error );
	
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
void Rbdb_Error_internal_outputBDBError( Rbdb_Error* error )	{
	
	fprintf( stderr, "Error (%s): %s",	error->function, 
								db_strerror( error->number )  );
	if ( error->message != NULL )	{
		fprintf( stderr, " - \"%s\"", error->message );
	}
	fprintf( stderr, "\n" );
}




