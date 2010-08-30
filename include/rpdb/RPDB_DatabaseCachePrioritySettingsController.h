/*
 *		RPDB::Database::Cursor::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *
 *
 */

#ifndef RPDB_DATABASE_CACHE_PRIORITY_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_CACHE_PRIORITY_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
					
	RPDB_DatabaseCachePrioritySettingsController*	RPDB_DatabaseCachePrioritySettingsController_new(											RPDB_DatabaseCacheSettingsController*			database_cache_setting_controller );

	void											RPDB_DatabaseCachePrioritySettingsController_free(								RPDB_DatabaseCachePrioritySettingsController** database_cache_priority_settings_controller );
	RPDB_Environment*						RPDB_DatabaseCachePrioritySettingsController_parentEnvironment(	RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller );
	RPDB_Database* RPDB_DatabaseCachePrioritySettingsController_parentDatabase(	RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller );
											
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_priority(										RPDB_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller );
																																																											
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_veryLow(										RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											RPDB_DatabaseCachePrioritySettingsController_setVeryLow(									RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_isAtLeastVeryLow(								RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_isAtMostVeryLow(								RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
																																															
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_low(											RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											RPDB_DatabaseCachePrioritySettingsController_setLow(										RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_isAtLeastLow(									RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_isAtMostLow(									RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
																																															
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_default(		   								RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											RPDB_DatabaseCachePrioritySettingsController_setDefault(	   								RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_isAtLeastDefault(								RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_isAtMostDefault(								RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
																																															
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_high(											RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											RPDB_DatabaseCachePrioritySettingsController_setHigh(										RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_isAtLeastHigh(								RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_isAtMostHigh(									RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
																																															
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_veryHigh(										RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											RPDB_DatabaseCachePrioritySettingsController_setVeryHigh(									RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_isAtLeastVeryHigh(							RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_isAtMostVeryHigh( 							RPDB_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
											
#endif

