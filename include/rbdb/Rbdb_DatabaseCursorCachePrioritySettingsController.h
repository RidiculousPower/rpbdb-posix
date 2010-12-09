/*
 *		Rbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *		Rbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorCacheSettingsController::CursorSettingsCachePriorityController
 *
 */

#ifndef Rbdb_DATABASE_CURSOR_CACHE_PRIORITY_SETTINGS_CONTROLLER
	#define Rbdb_DATABASE_CURSOR_CACHE_PRIORITY_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
					
	Rbdb_DatabaseCursorCachePrioritySettingsController*	Rbdb_DatabaseCursorCachePrioritySettingsController_new(		Rbdb_DatabaseCursorCacheSettingsController*				database_cursor_cache_settings_controller );

	void													Rbdb_DatabaseCursorCachePrioritySettingsController_free(	Rbdb_DatabaseCursorCachePrioritySettingsController** database_cursor_cache_priority_settings_controller );
	Rbdb_Environment*								Rbdb_DatabaseCursorCachePrioritySettingsController_parentEnvironment(	Rbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller );
	Rbdb_Database* Rbdb_DatabaseCursorCachePrioritySettingsController_parentDatabase(	Rbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller );
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursorCachePrioritySettingsController_parentDatabaseCursor(	Rbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller );

	DB_CACHE_PRIORITY			Rbdb_DatabaseCursorCachePrioritySettingsController_priority(											Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );

	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_veryLow(											Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		Rbdb_DatabaseCursorCachePrioritySettingsController_setVeryLow(											Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastVeryLow(									Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_isAtMostVeryLow(									Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
																																										
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_low(												Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		Rbdb_DatabaseCursorCachePrioritySettingsController_setLow(												Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastLow(										Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_isAtMostLow(										Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
																																										
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_default(											Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		Rbdb_DatabaseCursorCachePrioritySettingsController_setDefault(											Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastDefault(									Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_isAtMostDefault(									Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
																																										
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_high(												Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		Rbdb_DatabaseCursorCachePrioritySettingsController_setHigh(											Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastHigh(										Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_isAtMostHigh(										Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
																																										
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_veryHigh(											Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	void		Rbdb_DatabaseCursorCachePrioritySettingsController_setVeryHigh(										Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_isAtLeastVeryHigh(									Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );
	BOOL		Rbdb_DatabaseCursorCachePrioritySettingsController_isAtMostVeryHigh(									Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller );

#endif

