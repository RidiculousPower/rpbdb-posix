/*
 *		RPbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorCacheSettingsController
 *		RPbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorCacheSettingsController
 *
 */

#ifndef RPBDB_DATABASE_CURSOR_CACHE_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_CURSOR_CACHE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
		
	RPbdb_DatabaseCursorCacheSettingsController*				RPbdb_DatabaseCursorCacheSettingsController_new(										RPbdb_DatabaseCursorSettingsController*			cursor_settings_controller );

	void														RPbdb_DatabaseCursorCacheSettingsController_free(									RPbdb_DatabaseCursorCacheSettingsController** database_cursor_cache_settings_controller );
	RPbdb_Environment*									RPbdb_DatabaseCursorCacheSettingsController_parentEnvironment(			RPbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller );
	RPbdb_Database* RPbdb_DatabaseCursorCacheSettingsController_parentDatabase(	RPbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller );
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursorCacheSettingsController_parentDatabaseCursor(	RPbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller );
																																			
	void														RPbdb_DatabaseCursorCacheSettingsController_initDefaultSettings(						RPbdb_DatabaseCursorSettingsController*			cursor_settings_controller );
	RPbdb_DatabaseCursorCachePrioritySettingsController*		RPbdb_DatabaseCursorCacheSettingsController_priorityController(							RPbdb_DatabaseCursorCacheSettingsController*	cursor_cache_settings_controller );


#endif

