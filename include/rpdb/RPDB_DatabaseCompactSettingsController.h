/*
 *		RPDB::SettingsController::DatabaseSettingsController::DatabaseCompactSettingsController
 *		RPDB::DatabaseController::Database::SettingsController::CompactSettingsController
 *
 */

#ifndef RPDB_DATABASE_COMPACT_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_COMPACT_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseCompactSettingsController*	RPDB_DatabaseCompactSettingsController_new(											RPDB_DatabaseSettingsController*			database_settings_controller );

	void										RPDB_DatabaseCompactSettingsController_free(	RPDB_DatabaseCompactSettingsController** database_compact_settings_controller );
	RPDB_Environment*					RPDB_DatabaseCompactSettingsController_parentEnvironment(	RPDB_DatabaseCompactSettingsController* database_compact_settings_controller );
	RPDB_Database* RPDB_DatabaseCompactSettingsController_parentDatabase(	RPDB_DatabaseCompactSettingsController* database_compact_settings_controller );
																																		
	int											RPDB_DatabaseCompactSettingsController_fillPercent(									RPDB_DatabaseCompactSettingsController*	database_compact_settings_controller );
	void										RPDB_DatabaseCompactSettingsController_setFillPercent(									RPDB_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																																		int											fill_percent );
	int											RPDB_DatabaseCompactSettingsController_maxPagesToCompact(								RPDB_DatabaseCompactSettingsController*	database_compact_settings_controller );
	void										RPDB_DatabaseCompactSettingsController_setMaxPagesToCompact(							RPDB_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																																		int											max_pages_to_compact );
	db_timeout_t								RPDB_DatabaseCompactSettingsController_timeout(										RPDB_DatabaseCompactSettingsController*	database_compact_settings_controller );
	void										RPDB_DatabaseCompactSettingsController_setTimeout(										RPDB_DatabaseCompactSettingsController*	database_compact_settings_controller, 
																																		int											timeout );

#endif

