/*
 *		RPDB::ErrorSettingsController
 *
 *
 */

#ifndef RPDB_ERROR_SETTINGS_CONTROLLER
	#define RPDB_ERROR_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_ErrorSettingsController*				RPDB_ErrorSettingsController_new(						RPDB_SettingsController*								settings_controller );

	void										RPDB_ErrorSettingsController_free(	RPDB_ErrorSettingsController** error_settings_controller );
	RPDB_Environment*					RPDB_ErrorSettingsController_parentEnvironment(	RPDB_ErrorSettingsController* error_settings_controller );

	FILE*										RPDB_ErrorSettingsController_file(						RPDB_ErrorSettingsController*							error_settings_controller );
	void										RPDB_ErrorSettingsController_setFile(					RPDB_ErrorSettingsController*							error_settings_controller, 
																										FILE*													file );
	FILE*										RPDB_ErrorSettingsController_setFileFromPath(			RPDB_ErrorSettingsController*							error_settings_controller, 
																										char*													file_path );
	char*										RPDB_ErrorSettingsController_prefix(					RPDB_ErrorSettingsController*							error_settings_controller );
	void										RPDB_ErrorSettingsController_setPrefix(				RPDB_ErrorSettingsController*							error_settings_controller, 
																										char*													error_prefix );

/*
	void										RPDB_ErrorSettingsController_setErrorCallbackMethod(	RPDB_ErrorSettingsController*							error_settings_controller,
																										void (*error_callback_method)(	RPDB_Environment*					environment,
																																		const char*				error_prefix,
																																		const char*				error_message ) );
	void (*error_callback_method)(	RPDB_Environment*					environment,                                                                                                                  
									const char*				error_prefix,                                                                                                                               
									const char*				error_message )		RPDB_ErrorSettingsController_errorCallbackMethod(		RPDB_ErrorSettingsController*							error_settings_controller );
*/
#endif

