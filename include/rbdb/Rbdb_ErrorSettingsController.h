/*
 *		Rbdb::ErrorSettingsController
 *
 *
 */

#ifndef RBDB_ERROR_SETTINGS_CONTROLLER
	#define RBDB_ERROR_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_ErrorSettingsController*				Rbdb_ErrorSettingsController_new(						Rbdb_SettingsController*								settings_controller );

	void										Rbdb_ErrorSettingsController_free(	Rbdb_ErrorSettingsController** error_settings_controller );
	Rbdb_Environment*					Rbdb_ErrorSettingsController_parentEnvironment(	Rbdb_ErrorSettingsController* error_settings_controller );

	FILE*										Rbdb_ErrorSettingsController_file(						Rbdb_ErrorSettingsController*							error_settings_controller );
	void										Rbdb_ErrorSettingsController_setFile(					Rbdb_ErrorSettingsController*							error_settings_controller, 
																										FILE*													file );
	FILE*										Rbdb_ErrorSettingsController_setFileFromPath(			Rbdb_ErrorSettingsController*							error_settings_controller, 
																										char*													file_path );
	char*										Rbdb_ErrorSettingsController_prefix(					Rbdb_ErrorSettingsController*							error_settings_controller );
	void										Rbdb_ErrorSettingsController_setPrefix(				Rbdb_ErrorSettingsController*							error_settings_controller, 
																										char*													error_prefix );

/*
	void										Rbdb_ErrorSettingsController_setErrorCallbackMethod(	Rbdb_ErrorSettingsController*							error_settings_controller,
																										void (*error_callback_method)(	Rbdb_Environment*					environment,
																																		const char*				error_prefix,
																																		const char*				error_message ) );
	void (*error_callback_method)(	Rbdb_Environment*					environment,                                                                                                                  
									const char*				error_prefix,                                                                                                                               
									const char*				error_message )		Rbdb_ErrorSettingsController_errorCallbackMethod(		Rbdb_ErrorSettingsController*							error_settings_controller );
*/
#endif

