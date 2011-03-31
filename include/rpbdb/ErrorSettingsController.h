/*
 *		RPbdb::ErrorSettingsController
 *
 *
 */

#ifndef RPBDB_ERROR_SETTINGS_CONTROLLER
	#define RPBDB_ERROR_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_ErrorSettingsController*				RPbdb_ErrorSettingsController_new(						RPbdb_SettingsController*								settings_controller );

	void										RPbdb_ErrorSettingsController_free(	RPbdb_ErrorSettingsController** error_settings_controller );
	RPbdb_Environment*					RPbdb_ErrorSettingsController_parentEnvironment(	RPbdb_ErrorSettingsController* error_settings_controller );

	FILE*										RPbdb_ErrorSettingsController_file(						RPbdb_ErrorSettingsController*							error_settings_controller );
	void										RPbdb_ErrorSettingsController_setFile(					RPbdb_ErrorSettingsController*							error_settings_controller, 
																										FILE*													file );
	FILE*										RPbdb_ErrorSettingsController_setFileFromPath(			RPbdb_ErrorSettingsController*							error_settings_controller, 
																										char*													file_path );
	char*										RPbdb_ErrorSettingsController_prefix(					RPbdb_ErrorSettingsController*							error_settings_controller );
	void										RPbdb_ErrorSettingsController_setPrefix(				RPbdb_ErrorSettingsController*							error_settings_controller, 
																										char*													error_prefix );

/*
	void										RPbdb_ErrorSettingsController_setErrorCallbackMethod(	RPbdb_ErrorSettingsController*							error_settings_controller,
																										void (*error_callback_method)(	RPbdb_Environment*					environment,
																																		const char*				error_prefix,
																																		const char*				error_message ) );
	void (*error_callback_method)(	RPbdb_Environment*					environment,                                                                                                                  
									const char*				error_prefix,                                                                                                                               
									const char*				error_message )		RPbdb_ErrorSettingsController_errorCallbackMethod(		RPbdb_ErrorSettingsController*							error_settings_controller );
*/
#endif

