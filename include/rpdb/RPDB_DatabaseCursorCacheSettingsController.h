/*
 *		RPDB::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorCacheSettingsController
 *		RPDB::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorCacheSettingsController
 *
 */

#ifndef RPDB_DATABASE_CURSOR_CACHE_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_CURSOR_CACHE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
		
	RPDB_DatabaseCursorCacheSettingsController*				RPDB_DatabaseCursorCacheSettingsController_new(										RPDB_DatabaseCursorSettingsController*			cursor_settings_controller );

	void														RPDB_DatabaseCursorCacheSettingsController_free(									RPDB_DatabaseCursorCacheSettingsController** database_cursor_cache_settings_controller );
	RPDB_Environment*									RPDB_DatabaseCursorCacheSettingsController_parentEnvironment(			RPDB_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller );
	RPDB_Database* RPDB_DatabaseCursorCacheSettingsController_parentDatabase(	RPDB_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller );
	RPDB_DatabaseCursor* RPDB_DatabaseCursorCacheSettingsController_parentDatabaseCursor(	RPDB_DatabaseCursorCacheSettingsController* database_cursor_cache_settings_controller );
																																			
	void														RPDB_DatabaseCursorCacheSettingsController_initDefaultSettings(						RPDB_DatabaseCursorSettingsController*			cursor_settings_controller );
	RPDB_DatabaseCursorCachePrioritySettingsController*		RPDB_DatabaseCursorCacheSettingsController_priorityController(							RPDB_DatabaseCursorCacheSettingsController*	cursor_cache_settings_controller );


#endif

