/*
 *		RPbdb::Database::Cursor::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *
 *
 */

#ifndef RPBDB_DATABASE_CACHE_PRIORITY_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_CACHE_PRIORITY_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
					
	RPbdb_DatabaseCachePrioritySettingsController*	RPbdb_DatabaseCachePrioritySettingsController_new(											RPbdb_DatabaseCacheSettingsController*			database_cache_setting_controller );

	void											RPbdb_DatabaseCachePrioritySettingsController_free(								RPbdb_DatabaseCachePrioritySettingsController** database_cache_priority_settings_controller );
	RPbdb_Environment*						RPbdb_DatabaseCachePrioritySettingsController_parentEnvironment(	RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller );
	RPbdb_Database* RPbdb_DatabaseCachePrioritySettingsController_parentDatabase(	RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller );
											
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_priority(										RPbdb_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller );
																																																											
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_veryLow(										RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											RPbdb_DatabaseCachePrioritySettingsController_setVeryLow(									RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_isAtLeastVeryLow(								RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_isAtMostVeryLow(								RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
																																															
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_low(											RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											RPbdb_DatabaseCachePrioritySettingsController_setLow(										RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_isAtLeastLow(									RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_isAtMostLow(									RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
																																															
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_default(		   								RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											RPbdb_DatabaseCachePrioritySettingsController_setDefault(	   								RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_isAtLeastDefault(								RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_isAtMostDefault(								RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
																																															
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_high(											RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											RPbdb_DatabaseCachePrioritySettingsController_setHigh(										RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_isAtLeastHigh(								RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_isAtMostHigh(									RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
																																															
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_veryHigh(										RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											RPbdb_DatabaseCachePrioritySettingsController_setVeryHigh(									RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_isAtLeastVeryHigh(							RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_isAtMostVeryHigh( 							RPbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
											
#endif

