/*
 *		Rbdb::Database::Cursor::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *
 *
 */

#ifndef Rbdb_DATABASE_CACHE_PRIORITY_SETTINGS_CONTROLLER
	#define Rbdb_DATABASE_CACHE_PRIORITY_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
					
	Rbdb_DatabaseCachePrioritySettingsController*	Rbdb_DatabaseCachePrioritySettingsController_new(											Rbdb_DatabaseCacheSettingsController*			database_cache_setting_controller );

	void											Rbdb_DatabaseCachePrioritySettingsController_free(								Rbdb_DatabaseCachePrioritySettingsController** database_cache_priority_settings_controller );
	Rbdb_Environment*						Rbdb_DatabaseCachePrioritySettingsController_parentEnvironment(	Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller );
	Rbdb_Database* Rbdb_DatabaseCachePrioritySettingsController_parentDatabase(	Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller );
											
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_priority(										Rbdb_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller );
																																																											
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_veryLow(										Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											Rbdb_DatabaseCachePrioritySettingsController_setVeryLow(									Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_isAtLeastVeryLow(								Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_isAtMostVeryLow(								Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
																																															
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_low(											Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											Rbdb_DatabaseCachePrioritySettingsController_setLow(										Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_isAtLeastLow(									Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_isAtMostLow(									Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
																																															
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_default(		   								Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											Rbdb_DatabaseCachePrioritySettingsController_setDefault(	   								Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_isAtLeastDefault(								Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_isAtMostDefault(								Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
																																															
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_high(											Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											Rbdb_DatabaseCachePrioritySettingsController_setHigh(										Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_isAtLeastHigh(								Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_isAtMostHigh(									Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
																																															
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_veryHigh(										Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	void											Rbdb_DatabaseCachePrioritySettingsController_setVeryHigh(									Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_isAtLeastVeryHigh(							Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
	DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_isAtMostVeryHigh( 							Rbdb_DatabaseCachePrioritySettingsController*	database_cache_priority_settings_controller );
											
#endif

