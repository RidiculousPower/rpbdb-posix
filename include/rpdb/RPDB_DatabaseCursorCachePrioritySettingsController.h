/*
 *		RPDB::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *		RPDB::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *
 */

#ifndef RPDB_DATABASE_CURSOR_CACHE_PRIORITY_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_CURSOR_CACHE_PRIORITY_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
					
	RPDB_DatabaseCursorCachePrioritySettingsController*	RPDB_DatabaseCursorCachePrioritySettingsController_new(		RPDB_DatabaseCursorCacheSettingsController*				database_cursor_cache_settings_controller );

	void													RPDB_DatabaseCursorCachePrioritySettingsController_free(	RPDB_DatabaseCursorCachePrioritySettingsController** database_cursor_cache_priority_settings_controller );
	RPDB_Environment*								RPDB_DatabaseCursorCachePrioritySettingsController_parentEnvironment(	RPDB_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller );
	RPDB_Database* RPDB_DatabaseCursorCachePrioritySettingsController_parentDatabase(	RPDB_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller );
	RPDB_DatabaseCursor* RPDB_DatabaseCursorCachePrioritySettingsController_parentDatabaseCursor(	RPDB_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller );

	DB_CACHE_PRIORITY			RPDB_DatabaseCursorCachePrioritySettingsController_priority(											RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );

	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_veryLow(											RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		RPDB_DatabaseCursorCachePrioritySettingsController_setVeryLow(											RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_isAtLeastVeryLow(									RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_isAtMostVeryLow(									RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
																																										
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_low(												RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		RPDB_DatabaseCursorCachePrioritySettingsController_setLow(												RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_isAtLeastLow(										RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_isAtMostLow(										RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
																																										
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_default(											RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		RPDB_DatabaseCursorCachePrioritySettingsController_setDefault(											RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_isAtLeastDefault(									RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_isAtMostDefault(									RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
																																										
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_high(												RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		RPDB_DatabaseCursorCachePrioritySettingsController_setHigh(											RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_isAtLeastHigh(										RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_isAtMostHigh(										RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
																																										
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_veryHigh(											RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		RPDB_DatabaseCursorCachePrioritySettingsController_setVeryHigh(										RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_isAtLeastVeryHigh(									RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		RPDB_DatabaseCursorCachePrioritySettingsController_isAtMostVeryHigh(									RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );

#endif

