/*
 *		RPbdb::ErrorController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "ErrorController.h"
#include "ErrorController_internal.h"

#include "Error.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/
	
//	Return the error controller
RPbdb_ErrorController* RPbdb_ErrorController_new( RPbdb_Environment* environment )	{

	//	Allocate ErrorController
	RPbdb_ErrorController*			error_controller = calloc( 1, sizeof( RPbdb_ErrorController ) );

	error_controller->parent_environment = environment;

	return error_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_ErrorController_free(	RPbdb_ErrorController** error_controller )	{

	free( *error_controller );
	*error_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_ErrorSettingsController* RPbdb_ErrorController_settingsController(	RPbdb_ErrorController* error_controller )	{
	return error_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_ErrorController_parentEnvironment(	RPbdb_ErrorController* error_controller )	{
	return error_controller->parent_environment;
}

/************
*  raise  *
************/

//	instantiate an error and throw an exception but do not process it
RPbdb_Error* RPbdb_ErrorController_raiseError(	RPbdb_ErrorController*	error_controller, 
												int						error_number, 
												char*					error_function, 
												char*					additional_explanation_message )	{

//	FIX
	RPbdb_Error* error = RPbdb_Error_newErrorWithNumberFunctionAndMessage(	error_controller, 
																			error_number, 
																			error_function, 
																			additional_explanation_message );

//	RPbdb_ErrorController_push( error_controller, error );

	return error;
}



/************
*  throw  *
************/

//	instantiate an error and throw an exception and process it as fatal
void	RPbdb_ErrorController_throwError(		RPbdb_ErrorController*	error_controller,
												int						error_number, 
												char*					error_function, 
												char*					additional_explanation_message )	{

	RPbdb_Error_terminate( RPbdb_ErrorController_raiseError(	error_controller, 
																error_number, 
																error_function, 
																additional_explanation_message ) );
}

/************
*  push  *
************/

//	we'll keep a stack of errors as they're thrown (assuming the program isn't terminated)
//	push error onto the end of this stack
void RPbdb_ErrorController_pushError(	RPbdb_ErrorController*	error_controller, 
										RPbdb_Error*			error )	{
	
	RPbdb_Error*		error_iterator;
	
	//	if we haven't initiated the stack yet, make this the first error on the stack
	if ( error_controller->error_stack == NULL )	{
		error_controller->error_stack = error;
	}
	else	{
		error_iterator = error_controller->error_stack;
		/*
		while ( error_iterator->next != NULL )	{
			error_iterator = error_iterator->next;
		}
		error_iterator->next = error;
		*/
	}
}

/************
*  shift  *
************/

//	shift error from the start of stack
RPbdb_Error* RPbdb_ErrorController_shiftError( RPbdb_ErrorController* error_controller )	{
	
	//	get the first error - the head of our linked list of errors
	RPbdb_Error*		shifted_error = error_controller->error_stack;
	
	//	so long as the stack has an error, reset the stack to the next error (which may be NULL)
	if ( shifted_error != NULL )	{
	/*
		error_controller->error_stack = shifted_error->next;
		*/
	}
	
	//	return the shifted error (may return NULL)
	return shifted_error;
}

/******************
*  hasError  *
******************/

BOOL RPbdb_ErrorController_hasError( RPbdb_ErrorController* error_controller )	{

	if ( error_controller->error_stack )	{
		return TRUE;
	}
	else	{
		return FALSE;
	}
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  throwBDBError  *
************/

//	instantiate an error and throw an exception and process it as fatal
void RPbdb_ErrorController_internal_throwBDBError(	RPbdb_ErrorController*	error_controller,
													int						error_number, 
													char*					error_function )	{

	RPbdb_Error* error = RPbdb_Error_newErrorWithNumberFunctionAndMessage(	error_controller, 
																		  error_number, 
																		  error_function, 
																		  NULL );
	
	RPbdb_Error_internal_outputBDBError(	error );
	
	RPbdb_Error_terminate( error );

}

