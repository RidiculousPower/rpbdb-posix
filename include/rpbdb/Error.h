/*
 *		RPbdb::ErrorController::Error
 *
 *
 */

#ifndef RPBDB_ERROR
	#define RPBDB_ERROR

	#include "BaseStandardInclude.h"

	#include <signal.h>

	/****************
	*  Prototypes  *
	****************/

	RPbdb_Error*	RPbdb_Error_new(									RPbdb_ErrorController*		error_controller );
	void			RPbdb_Error_free(	RPbdb_Error** error );
	RPbdb_ErrorSettingsController*	RPbdb_Error_settingsController(	RPbdb_Error* error );
	RPbdb_Environment*		RPbdb_Error_parentEnvironment(	RPbdb_Error* error );
	RPbdb_Error*	RPbdb_Error_newErrorWithNumberFunction(	RPbdb_ErrorController*		error_controller, 
																											int											error_number, 
																											char*										error_function );
	RPbdb_Error*	RPbdb_Error_newErrorWithNumberFunctionAndMessage(	RPbdb_ErrorController*		error_controller, 
																																int											error_number, 
																																char*										error_function, 
																																char*										additional_explanation_message );
	void			RPbdb_Error_terminate(								RPbdb_Error*				error );

#endif

