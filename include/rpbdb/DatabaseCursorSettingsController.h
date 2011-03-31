/*
 *		RPbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController
 *
 *
 */

#ifndef RPBDB_DATABASE_CURSOR_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_CURSOR_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseCursorSettingsController*				RPbdb_DatabaseCursorSettingsController_new(									RPbdb_DatabaseSettingsController*				database_settings_controller );

	void												RPbdb_DatabaseCursorSettingsController_free(								RPbdb_DatabaseCursorSettingsController** database_cursor_settings_controller );
	RPbdb_Environment*							RPbdb_DatabaseCursorSettingsController_parentEnvironment(		RPbdb_DatabaseCursorSettingsController* database_cursor_settings_controller );
	RPbdb_Database* RPbdb_DatabaseCursorSettingsController_parentDatabase(	RPbdb_DatabaseCursorSettingsController* database_cursor_settings_controller );
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursorSettingsController_parentDatabaseCursor(	RPbdb_DatabaseCursorSettingsController* database_cursor_settings_controller );
																																		
	BOOL												RPbdb_DatabaseCursorSettingsController_duplicateRetainsLocation(			RPbdb_DatabaseCursorSettingsController*			cursor_settings_controller );
	void												RPbdb_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOn(		RPbdb_DatabaseCursorSettingsController*			cursor_settings_controller );
	void												RPbdb_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOff(		RPbdb_DatabaseCursorSettingsController*			cursor_settings_controller );
																																	
	RPbdb_DatabaseCursorCacheSettingsController*		RPbdb_DatabaseCursorSettingsController_cacheSettingsController(				RPbdb_DatabaseCursorSettingsController*			cursor_settings_controller );
	RPbdb_DatabaseCursorReadWriteSettingsController*			RPbdb_DatabaseCursorSettingsController_readWriteSettingsController(			RPbdb_DatabaseCursorSettingsController*			cursor_settings_controller );

#endif

