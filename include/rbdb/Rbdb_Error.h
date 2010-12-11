/*
 *		Rbdb::ErrorController::Error
 *
 *
 */

#ifndef RBDB_ERROR
	#define RBDB_ERROR

	#include "Rbdb_BaseStandardInclude.h"

	#include <signal.h>

	/****************
	*  Prototypes  *
	****************/

	Rbdb_Error*	Rbdb_Error_new(									Rbdb_ErrorController*		error_controller );
	void			Rbdb_Error_free(	Rbdb_Error** error );
	Rbdb_ErrorSettingsController*	Rbdb_Error_settingsController(	Rbdb_Error* error );
	Rbdb_Environment*		Rbdb_Error_parentEnvironment(	Rbdb_Error* error );
	Rbdb_Error*	Rbdb_Error_newErrorWithNumberFunction(	Rbdb_ErrorController*		error_controller, 
																											int											error_number, 
																											char*										error_function );
	Rbdb_Error*	Rbdb_Error_newErrorWithNumberFunctionAndMessage(	Rbdb_ErrorController*		error_controller, 
																																int											error_number, 
																																char*										error_function, 
																																char*										additional_explanation_message );
	void			Rbdb_Error_terminate(								Rbdb_Error*				error );

#endif

