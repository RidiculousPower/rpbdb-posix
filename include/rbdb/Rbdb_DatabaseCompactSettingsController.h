/*
 *		Rbdb::SettingsController::DatabaseSettingsController::DatabaseCompactSettingsController
 *		Rbdb::DatabaseController::Database::SettingsController::CompactSettingsController
 *
 */

#ifndef RBDB_DATABASE_COMPACT_SETTINGS_CONTROLLER
	#define RBDB_DATABASE_COMPACT_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseCompactSettingsController*	Rbdb_DatabaseCompactSettingsController_new(											Rbdb_DatabaseSettingsController*			database_settings_controller );

	void										Rbdb_DatabaseCompactSettingsController_free(	Rbdb_DatabaseCompactSettingsController** database_compact_settings_controller );
	Rbdb_Environment*					Rbdb_DatabaseCompactSettingsController_parentEnvironment(	Rbdb_DatabaseCompactSettingsController* database_compact_settings_controller );
	Rbdb_Database* Rbdb_DatabaseCompactSettingsController_parentDatabase(	Rbdb_DatabaseCompactSettingsController* database_compact_settings_controller );
																																		
	int											Rbdb_DatabaseCompactSettingsController_fillPercent(									Rbdb_DatabaseCompactSettingsController*	database_compact_settings_controller );
	void										Rbdb_DatabaseCompactSettingsController_setFillPercent(									Rbdb_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																																		int											fill_percent );
	int											Rbdb_DatabaseCompactSettingsController_maxPagesToCompact(								Rbdb_DatabaseCompactSettingsController*	database_compact_settings_controller );
	void										Rbdb_DatabaseCompactSettingsController_setMaxPagesToCompact(							Rbdb_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																																		int											max_pages_to_compact );
	db_timeout_t								Rbdb_DatabaseCompactSettingsController_timeout(										Rbdb_DatabaseCompactSettingsController*	database_compact_settings_controller );
	void										Rbdb_DatabaseCompactSettingsController_setTimeout(										Rbdb_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																																		int											timeout );

#endif

