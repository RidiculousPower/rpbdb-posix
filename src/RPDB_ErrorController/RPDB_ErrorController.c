/*
 *		RPDB::ErrorController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_ErrorController.h"
#include "RPDB_ErrorController_internal.h"

#include "RPDB_Error.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/
	
//	Return the error controller
RPDB_ErrorController* RPDB_ErrorController_new( RPDB_Environment* environment )	{

	//	Allocate ErrorController
	RPDB_ErrorController*			error_controller = calloc( 1, sizeof( RPDB_ErrorController ) );

	error_controller->parent_environment = environment;

	return error_controller;
}

/***************************
*  free  *
***************************/
void RPDB_ErrorController_free(	RPDB_ErrorController** error_controller )	{

	free( *error_controller );
	*error_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_ErrorSettingsController* RPDB_ErrorController_settingsController(	RPDB_ErrorController* error_controller )	{
	return error_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_ErrorController_parentEnvironment(	RPDB_ErrorController* error_controller )	{
	return error_controller->parent_environment;
}

/************
*  raise  *
************/

//	instantiate an error and throw an exception but do not process it
RPDB_Error* RPDB_ErrorController_raiseError(	RPDB_ErrorController*	error_controller, 
												int						error_number, 
												char*					error_function, 
												char*					additional_explanation_message )	{

//	FIX
	RPDB_Error* error = RPDB_Error_newErrorWithNumberFunctionAndMessage(	error_controller, 
																			error_number, 
																			error_function, 
																			additional_explanation_message );

//	RPDB_ErrorController_push( error_controller, error );

	return error;
}



/************
*  throw  *
************/

//	instantiate an error and throw an exception and process it as fatal
void	RPDB_ErrorController_throwError(		RPDB_ErrorController*	error_controller,
												int						error_number, 
												char*					error_function, 
												char*					additional_explanation_message )	{

	RPDB_Error_terminate( RPDB_ErrorController_raiseError(	error_controller, 
																error_number, 
																error_function, 
																additional_explanation_message ) );
}

/************
*  push  *
************/

//	we'll keep a stack of errors as they're thrown (assuming the program isn't terminated)
//	push error onto the end of this stack
void RPDB_ErrorController_pushError(	RPDB_ErrorController*	error_controller, 
										RPDB_Error*			error )	{
	
	RPDB_Error*		error_iterator;
	
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
RPDB_Error* RPDB_ErrorController_shiftError( RPDB_ErrorController* error_controller )	{
	
	//	get the first error - the head of our linked list of errors
	RPDB_Error*		shifted_error = error_controller->error_stack;
	
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

BOOL RPDB_ErrorController_hasError( RPDB_ErrorController* error_controller )	{

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
void RPDB_ErrorController_internal_throwBDBError(	RPDB_ErrorController*	error_controller,
													int						error_number, 
													char*					error_function )	{

	RPDB_Error* error = RPDB_Error_newErrorWithNumberFunctionAndMessage(	error_controller, 
																		  error_number, 
																		  error_function, 
																		  NULL );
	
	RPDB_Error_internal_outputBDBError(	error );
	
	RPDB_Error_terminate( error );

}

