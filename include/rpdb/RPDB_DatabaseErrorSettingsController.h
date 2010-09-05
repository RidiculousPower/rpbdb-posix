/*
 *		RPDB::DatabaseController::Database::DatabaseSettingsController::DatabaseErrorSettingsController
 *
 *
 */

#ifndef RPDB_DATABASE_ERROR_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_ERROR_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseErrorSettingsController*													RPDB_DatabaseErrorSettingsController_new(												RPDB_DatabaseSettingsController*				database_settings_controller );

	void															RPDB_DatabaseErrorSettingsController_free(	RPDB_DatabaseErrorSettingsController** database_error_settings_controller );
	RPDB_Environment*										RPDB_DatabaseErrorSettingsController_parentEnvironment(	RPDB_DatabaseErrorSettingsController* database_error_settings_controller );
	RPDB_Database* RPDB_DatabaseErrorSettingsController_parentDatabase(	RPDB_DatabaseErrorSettingsController* database_error_settings_controller );

	FILE*																					RPDB_DatabaseErrorSettingsController_file(												RPDB_DatabaseErrorSettingsController*			database_error_settings_controller );
	void 																					RPDB_DatabaseErrorSettingsController_setFile(											RPDB_DatabaseErrorSettingsController*			database_error_settings_controller, 
																																													FILE*											error_file );
	FILE*																					RPDB_DatabaseErrorSettingsController_setFileFromPath(									RPDB_DatabaseErrorSettingsController*			database_error_settings_controller,
																																													char*											error_file_path );
	char*																					RPDB_DatabaseErrorSettingsController_prefix(											RPDB_DatabaseErrorSettingsController*			database_error_settings_controller );
	void																					RPDB_DatabaseErrorSettingsController_setPrefix(										RPDB_DatabaseErrorSettingsController*			database_error_settings_controller, 
																																													const char*										error_prefix );
/*
	void																					RPDB_DatabaseErrorSettingsController_setErrorCallbackMethod(							RPDB_DatabaseErrorSettingsController*			database_error_settings_controller,
																																																			void (*error_callback_method)(	RPDB_Environment*			environment,
																																																											const char*		error_prefix_string,
																																																											const char*		error_message	)	);

	void (*error_callback_method)(	RPDB_Environment*			environment,                                                                                                                                             
									const char*		error_prefix_string,                                                                                                                                                            
									const char*		error_message	)						RPDB_DatabaseErrorSettingsController_errorCallbackMethod(								RPDB_DatabaseErrorSettingsController*			database_error_settings_controller );
*/
#endif

