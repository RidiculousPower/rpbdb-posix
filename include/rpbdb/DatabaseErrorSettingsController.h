/*
 *		RPbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseErrorSettingsController
 *
 *
 */

#ifndef RPBDB_DATABASE_ERROR_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_ERROR_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseErrorSettingsController*													RPbdb_DatabaseErrorSettingsController_new(												RPbdb_DatabaseSettingsController*				database_settings_controller );

	void															RPbdb_DatabaseErrorSettingsController_free(	RPbdb_DatabaseErrorSettingsController** database_error_settings_controller );
	RPbdb_Environment*										RPbdb_DatabaseErrorSettingsController_parentEnvironment(	RPbdb_DatabaseErrorSettingsController* database_error_settings_controller );
	RPbdb_Database* RPbdb_DatabaseErrorSettingsController_parentDatabase(	RPbdb_DatabaseErrorSettingsController* database_error_settings_controller );

	FILE*																					RPbdb_DatabaseErrorSettingsController_file(												RPbdb_DatabaseErrorSettingsController*			database_error_settings_controller );
	void 																					RPbdb_DatabaseErrorSettingsController_setFile(											RPbdb_DatabaseErrorSettingsController*			database_error_settings_controller, 
																																													FILE*											error_file );
	FILE*																					RPbdb_DatabaseErrorSettingsController_setFileFromPath(									RPbdb_DatabaseErrorSettingsController*			database_error_settings_controller,
																																													char*											error_file_path );
	char*																					RPbdb_DatabaseErrorSettingsController_prefix(											RPbdb_DatabaseErrorSettingsController*			database_error_settings_controller );
	void																					RPbdb_DatabaseErrorSettingsController_setPrefix(										RPbdb_DatabaseErrorSettingsController*			database_error_settings_controller, 
																																													const char*										error_prefix );
/*
	void																					RPbdb_DatabaseErrorSettingsController_setErrorCallbackMethod(							RPbdb_DatabaseErrorSettingsController*			database_error_settings_controller,
																																																			void (*error_callback_method)(	RPbdb_Environment*			environment,
																																																											const char*		error_prefix_string,
																																																											const char*		error_message	)	);

	void (*error_callback_method)(	RPbdb_Environment*			environment,                                                                                                                                             
									const char*		error_prefix_string,                                                                                                                                                            
									const char*		error_message	)						RPbdb_DatabaseErrorSettingsController_errorCallbackMethod(								RPbdb_DatabaseErrorSettingsController*			database_error_settings_controller );
*/
#endif

