/*
 *		RPDB::DatabaseController::Database::CursorController::Cursor::CursorSettingsController
 *
 *
 */

#ifndef RPDB_DATABASE_CURSOR_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_CURSOR_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseCursorSettingsController*				RPDB_DatabaseCursorSettingsController_new(									RPDB_DatabaseSettingsController*				database_settings_controller );

	void												RPDB_DatabaseCursorSettingsController_free(								RPDB_DatabaseCursorSettingsController** database_cursor_settings_controller );
	RPDB_Environment*							RPDB_DatabaseCursorSettingsController_parentEnvironment(		RPDB_DatabaseCursorSettingsController* database_cursor_settings_controller );
	RPDB_Database* RPDB_DatabaseCursorSettingsController_parentDatabase(	RPDB_DatabaseCursorSettingsController* database_cursor_settings_controller );
	RPDB_DatabaseCursor* RPDB_DatabaseCursorSettingsController_parentDatabaseCursor(	RPDB_DatabaseCursorSettingsController* database_cursor_settings_controller );
																																		
	BOOL												RPDB_DatabaseCursorSettingsController_duplicateRetainsLocation(			RPDB_DatabaseCursorSettingsController*			cursor_settings_controller );
	void												RPDB_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOn(		RPDB_DatabaseCursorSettingsController*			cursor_settings_controller );
	void												RPDB_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOff(		RPDB_DatabaseCursorSettingsController*			cursor_settings_controller );
																																	
	RPDB_DatabaseCursorCacheSettingsController*		RPDB_DatabaseCursorSettingsController_cacheSettingsController(				RPDB_DatabaseCursorSettingsController*			cursor_settings_controller );
	RPDB_DatabaseCursorReadWriteSettingsController*			RPDB_DatabaseCursorSettingsController_readWriteSettingsController(			RPDB_DatabaseCursorSettingsController*			cursor_settings_controller );

#endif

