/*
 *		RPbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *		RPbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *
 */

#ifndef RPBDB_DATABASE_CURSOR_CACHE_PRIORITY_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_CURSOR_CACHE_PRIORITY_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
					
	RPbdb_DatabaseCursorCachePrioritySettingsController*	RPbdb_DatabaseCursorCachePrioritySettingsController_new(		RPbdb_DatabaseCursorCacheSettingsController*				database_cursor_cache_settings_controller );

	void													RPbdb_DatabaseCursorCachePrioritySettingsController_free(	RPbdb_DatabaseCursorCachePrioritySettingsController** database_cursor_cache_priority_settings_controller );
	RPbdb_Environment*								RPbdb_DatabaseCursorCachePrioritySettingsController_parentEnvironment(	RPbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller );
	RPbdb_Database* RPbdb_DatabaseCursorCachePrioritySettingsController_parentDatabase(	RPbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller );
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursorCachePrioritySettingsController_parentDatabaseCursor(	RPbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller );

	DB_CACHE_PRIORITY			RPbdb_DatabaseCursorCachePrioritySettingsController_priority(											RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );

	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_veryLow(											RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		RPbdb_DatabaseCursorCachePrioritySettingsController_setVeryLow(											RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastVeryLow(									RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_isAtMostVeryLow(									RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
																																										
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_low(												RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		RPbdb_DatabaseCursorCachePrioritySettingsController_setLow(												RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastLow(										RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_isAtMostLow(										RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
																																										
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_default(											RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		RPbdb_DatabaseCursorCachePrioritySettingsController_setDefault(											RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastDefault(									RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_isAtMostDefault(									RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
																																										
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_high(												RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		RPbdb_DatabaseCursorCachePrioritySettingsController_setHigh(											RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastHigh(										RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_isAtMostHigh(										RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
																																										
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_veryHigh(											RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		RPbdb_DatabaseCursorCachePrioritySettingsController_setVeryHigh(										RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastVeryHigh(									RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPbdb_DatabaseCursorCachePrioritySettingsController_isAtMostVeryHigh(									RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );

#endif

