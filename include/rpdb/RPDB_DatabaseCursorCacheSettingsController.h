/*
 *		Rbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorCacheSettingsController
 *		Rbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorCacheSettingsController
 *
 */

#ifndef Rbdb_DATABASE_CURSOR_CACHE_SETTINGS_CONTROLLER
	#define Rbdb_DATABASE_CURSOR_CACHE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
		
	Rbdb_DatabaseCursorCacheSettingsController*				Rbdb_DatabaseCursorCacheSettingsController_new(										Rbdb_DatabaseCursorSettingsController*			cursor_settings_controller );

	void														Rbdb_DatabaseCursorCacheSettingsController_free(									Rbdb_DatabaseCursorCacheSettingsController** database_cursor_cache_settings_controller );
	Rbdb_Environment*									Rbdb_DatabaseCursorCacheSettingsController_parentEnvironment(			Rbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller );
	Rbdb_Database* Rbdb_DatabaseCursorCacheSettingsController_parentDatabase(	Rbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller );
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursorCacheSettingsController_parentDatabaseCursor(	Rbdb_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller );
																																			
	void														Rbdb_DatabaseCursorCacheSettingsController_initDefaultSettings(						Rbdb_DatabaseCursorSettingsController*			cursor_settings_controller );
	Rbdb_DatabaseCursorCachePrioritySettingsController*		Rbdb_DatabaseCursorCacheSettingsController_priorityController(							Rbdb_DatabaseCursorCacheSettingsController*	cursor_cache_settings_controller );


#endif

