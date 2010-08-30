/*
 *		RPDB::ErrorController::Error
 *
 *
 */

#ifndef RPDB_ERROR
	#define RPDB_ERROR

	#include "RPDB_BaseStandardInclude.h"

	#include <signal.h>

	/****************
	*  Prototypes  *
	****************/

	RPDB_Error*	RPDB_Error_new(									RPDB_ErrorController*		error_controller );
	void			RPDB_Error_free(	RPDB_Error** error );
	RPDB_ErrorSettingsController*	RPDB_Error_settingsController(	RPDB_Error* error );
	RPDB_Environment*		RPDB_Error_parentEnvironment(	RPDB_Error* error );
	RPDB_Error*	RPDB_Error_newErrorWithNumberFunction(	RPDB_ErrorController*		error_controller, 
																											int											error_number, 
																											char*										error_function );
	RPDB_Error*	RPDB_Error_newErrorWithNumberFunctionAndMessage(	RPDB_ErrorController*		error_controller, 
																																int											error_number, 
																																char*										error_function, 
																																char*										additional_explanation_message );
	void			RPDB_Error_terminate(								RPDB_Error*				error );

#endif

