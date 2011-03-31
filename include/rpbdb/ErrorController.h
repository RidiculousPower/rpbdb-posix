/*
 *		RPbdb::ErrorController
 *
 *
 */

#ifndef RPBDB_ERROR_CONTROLLER
	#define RPBDB_ERROR_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_ErrorController*	RPbdb_ErrorController_new(			RPbdb_Environment*						environment );

	void					RPbdb_ErrorController_free(	RPbdb_ErrorController** error_controller );
	RPbdb_ErrorSettingsController*	RPbdb_ErrorController_settingsController(	RPbdb_ErrorController* error_controller );
	RPbdb_Environment*		RPbdb_ErrorController_parentEnvironment(	RPbdb_ErrorController* error_controller );

	RPbdb_Error*			RPbdb_ErrorController_raiseError(	RPbdb_ErrorController*		error_controller, 
																int							error_number, 
																char*						error_function, 
																char*						additional_explanation_message );
	void					RPbdb_ErrorController_throwError(	RPbdb_ErrorController*		error_controller,
																int							error_number, 
																char*						error_function, 
																char*						additional_explanation_message );
	void					RPbdb_ErrorController_pushError(	RPbdb_ErrorController*		error_controller, 
																RPbdb_Error*				error );
	RPbdb_Error*				RPbdb_ErrorController_shiftError(	RPbdb_ErrorController*		error_controller );
	BOOL					RPbdb_ErrorController_hasError(		RPbdb_ErrorController*		error_controller );


#endif

