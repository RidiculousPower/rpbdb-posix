/*
 *		RPbdb::SettingsController::DatabaseSettingsController::DatabaseCompactSettingsController
 *		RPbdb::DatabaseController::Database::SettingsController::CompactSettingsController
 *
 */

#ifndef RPBDB_DATABASE_COMPACT_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_COMPACT_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseCompactSettingsController*	RPbdb_DatabaseCompactSettingsController_new(											RPbdb_DatabaseSettingsController*			database_settings_controller );

	void										RPbdb_DatabaseCompactSettingsController_free(	RPbdb_DatabaseCompactSettingsController** database_compact_settings_controller );
	RPbdb_Environment*					RPbdb_DatabaseCompactSettingsController_parentEnvironment(	RPbdb_DatabaseCompactSettingsController* database_compact_settings_controller );
	RPbdb_Database* RPbdb_DatabaseCompactSettingsController_parentDatabase(	RPbdb_DatabaseCompactSettingsController* database_compact_settings_controller );
																																		
	int											RPbdb_DatabaseCompactSettingsController_fillPercent(									RPbdb_DatabaseCompactSettingsController*	database_compact_settings_controller );
	void										RPbdb_DatabaseCompactSettingsController_setFillPercent(									RPbdb_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																																		int											fill_percent );
	int											RPbdb_DatabaseCompactSettingsController_maxPagesToCompact(								RPbdb_DatabaseCompactSettingsController*	database_compact_settings_controller );
	void										RPbdb_DatabaseCompactSettingsController_setMaxPagesToCompact(							RPbdb_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																																		int											max_pages_to_compact );
	db_timeout_t								RPbdb_DatabaseCompactSettingsController_timeout(										RPbdb_DatabaseCompactSettingsController*	database_compact_settings_controller );
	void										RPbdb_DatabaseCompactSettingsController_setTimeout(										RPbdb_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																																		int											timeout );

#endif

