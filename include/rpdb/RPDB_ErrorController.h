/*
 *		RPDB::ErrorController
 *
 *
 */

#ifndef RPDB_ERROR_CONTROLLER
	#define RPDB_ERROR_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_ErrorController*	RPDB_ErrorController_new(			RPDB_Environment*						environment );

	void					RPDB_ErrorController_free(	RPDB_ErrorController** error_controller );
	RPDB_ErrorSettingsController*	RPDB_ErrorController_settingsController(	RPDB_ErrorController* error_controller );
	RPDB_Environment*		RPDB_ErrorController_parentEnvironment(	RPDB_ErrorController* error_controller );

	RPDB_Error*			RPDB_ErrorController_raiseError(	RPDB_ErrorController*		error_controller, 
																int							error_number, 
																char*						error_function, 
																char*						additional_explanation_message );
	void					RPDB_ErrorController_throwError(	RPDB_ErrorController*		error_controller,
																int							error_number, 
																char*						error_function, 
																char*						additional_explanation_message );
	void					RPDB_ErrorController_pushError(	RPDB_ErrorController*		error_controller, 
																RPDB_Error*				error );
	RPDB_Error*				RPDB_ErrorController_shiftError(	RPDB_ErrorController*		error_controller );
	BOOL					RPDB_ErrorController_hasError(		RPDB_ErrorController*		error_controller );


#endif

