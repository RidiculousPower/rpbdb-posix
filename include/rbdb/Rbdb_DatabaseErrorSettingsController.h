/*
 *		Rbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseErrorSettingsController
 *
 *
 */

#ifndef RBDB_DATABASE_ERROR_SETTINGS_CONTROLLER
	#define RBDB_DATABASE_ERROR_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseErrorSettingsController*													Rbdb_DatabaseErrorSettingsController_new(												Rbdb_DatabaseSettingsController*				database_settings_controller );

	void															Rbdb_DatabaseErrorSettingsController_free(	Rbdb_DatabaseErrorSettingsController** database_error_settings_controller );
	Rbdb_Environment*										Rbdb_DatabaseErrorSettingsController_parentEnvironment(	Rbdb_DatabaseErrorSettingsController* database_error_settings_controller );
	Rbdb_Database* Rbdb_DatabaseErrorSettingsController_parentDatabase(	Rbdb_DatabaseErrorSettingsController* database_error_settings_controller );

	FILE*																					Rbdb_DatabaseErrorSettingsController_file(												Rbdb_DatabaseErrorSettingsController*			database_error_settings_controller );
	void 																					Rbdb_DatabaseErrorSettingsController_setFile(											Rbdb_DatabaseErrorSettingsController*			database_error_settings_controller, 
																																													FILE*											error_file );
	FILE*																					Rbdb_DatabaseErrorSettingsController_setFileFromPath(									Rbdb_DatabaseErrorSettingsController*			database_error_settings_controller,
																																													char*											error_file_path );
	char*																					Rbdb_DatabaseErrorSettingsController_prefix(											Rbdb_DatabaseErrorSettingsController*			database_error_settings_controller );
	void																					Rbdb_DatabaseErrorSettingsController_setPrefix(										Rbdb_DatabaseErrorSettingsController*			database_error_settings_controller, 
																																													const char*										error_prefix );
/*
	void																					Rbdb_DatabaseErrorSettingsController_setErrorCallbackMethod(							Rbdb_DatabaseErrorSettingsController*			database_error_settings_controller,
																																																			void (*error_callback_method)(	Rbdb_Environment*			environment,
																																																											const char*		error_prefix_string,
																																																											const char*		error_message	)	);

	void (*error_callback_method)(	Rbdb_Environment*			environment,                                                                                                                                             
									const char*		error_prefix_string,                                                                                                                                                            
									const char*		error_message	)						Rbdb_DatabaseErrorSettingsController_errorCallbackMethod(								Rbdb_DatabaseErrorSettingsController*			database_error_settings_controller );
*/
#endif

