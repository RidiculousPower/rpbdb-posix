/*
 *		Rbdb::ErrorController
 *
 *
 */

#ifndef RBDB_ERROR_CONTROLLER
	#define RBDB_ERROR_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_ErrorController*	Rbdb_ErrorController_new(			Rbdb_Environment*						environment );

	void					Rbdb_ErrorController_free(	Rbdb_ErrorController** error_controller );
	Rbdb_ErrorSettingsController*	Rbdb_ErrorController_settingsController(	Rbdb_ErrorController* error_controller );
	Rbdb_Environment*		Rbdb_ErrorController_parentEnvironment(	Rbdb_ErrorController* error_controller );

	Rbdb_Error*			Rbdb_ErrorController_raiseError(	Rbdb_ErrorController*		error_controller, 
																int							error_number, 
																char*						error_function, 
																char*						additional_explanation_message );
	void					Rbdb_ErrorController_throwError(	Rbdb_ErrorController*		error_controller,
																int							error_number, 
																char*						error_function, 
																char*						additional_explanation_message );
	void					Rbdb_ErrorController_pushError(	Rbdb_ErrorController*		error_controller, 
																Rbdb_Error*				error );
	Rbdb_Error*				Rbdb_ErrorController_shiftError(	Rbdb_ErrorController*		error_controller );
	BOOL					Rbdb_ErrorController_hasError(		Rbdb_ErrorController*		error_controller );


#endif

