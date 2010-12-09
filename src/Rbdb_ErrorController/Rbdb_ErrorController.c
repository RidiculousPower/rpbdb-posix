/*
 *		Rbdb::ErrorController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_ErrorController.h"
#include "Rbdb_ErrorController_internal.h"

#include "Rbdb_Error.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/
	
//	Return the error controller
Rbdb_ErrorController* Rbdb_ErrorController_new( Rbdb_Environment* environment )	{

	//	Allocate ErrorController
	Rbdb_ErrorController*			error_controller = calloc( 1, sizeof( Rbdb_ErrorController ) );

	error_controller->parent_environment = environment;

	return error_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_ErrorController_free(	Rbdb_ErrorController** error_controller )	{

	free( *error_controller );
	*error_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_ErrorSettingsController* Rbdb_ErrorController_settingsController(	Rbdb_ErrorController* error_controller )	{
	return error_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_ErrorController_parentEnvironment(	Rbdb_ErrorController* error_controller )	{
	return error_controller->parent_environment;
}

/************
*  raise  *
************/

//	instantiate an error and throw an exception but do not process it
Rbdb_Error* Rbdb_ErrorController_raiseError(	Rbdb_ErrorController*	error_controller, 
												int						error_number, 
												char*					error_function, 
												char*					additional_explanation_message )	{

//	FIX
	Rbdb_Error* error = Rbdb_Error_newErrorWithNumberFunctionAndMessage(	error_controller, 
																			error_number, 
																			error_function, 
																			additional_explanation_message );

//	Rbdb_ErrorController_push( error_controller, error );

	return error;
}



/************
*  throw  *
************/

//	instantiate an error and throw an exception and process it as fatal
void	Rbdb_ErrorController_throwError(		Rbdb_ErrorController*	error_controller,
												int						error_number, 
												char*					error_function, 
												char*					additional_explanation_message )	{

	Rbdb_Error_terminate( Rbdb_ErrorController_raiseError(	error_controller, 
																error_number, 
																error_function, 
																additional_explanation_message ) );
}

/************
*  push  *
************/

//	we'll keep a stack of errors as they're thrown (assuming the program isn't terminated)
//	push error onto the end of this stack
void Rbdb_ErrorController_pushError(	Rbdb_ErrorController*	error_controller, 
										Rbdb_Error*			error )	{
	
	Rbdb_Error*		error_iterator;
	
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
Rbdb_Error* Rbdb_ErrorController_shiftError( Rbdb_ErrorController* error_controller )	{
	
	//	get the first error - the head of our linked list of errors
	Rbdb_Error*		shifted_error = error_controller->error_stack;
	
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

BOOL Rbdb_ErrorController_hasError( Rbdb_ErrorController* error_controller )	{

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
void Rbdb_ErrorController_internal_throwBDBError(	Rbdb_ErrorController*	error_controller,
													int						error_number, 
													char*					error_function )	{

	Rbdb_Error* error = Rbdb_Error_newErrorWithNumberFunctionAndMessage(	error_controller, 
																		  error_number, 
																		  error_function, 
																		  NULL );
	
	Rbdb_Error_internal_outputBDBError(	error );
	
	Rbdb_Error_terminate( error );

}

