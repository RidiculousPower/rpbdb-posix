/*
 *		Rbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController
 *
 *
 */

#ifndef Rbdb_DATABASE_CURSOR_SETTINGS_CONTROLLER
	#define Rbdb_DATABASE_CURSOR_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseCursorSettingsController*				Rbdb_DatabaseCursorSettingsController_new(									Rbdb_DatabaseSettingsController*				database_settings_controller );

	void												Rbdb_DatabaseCursorSettingsController_free(								Rbdb_DatabaseCursorSettingsController** database_cursor_settings_controller );
	Rbdb_Environment*							Rbdb_DatabaseCursorSettingsController_parentEnvironment(		Rbdb_DatabaseCursorSettingsController* database_cursor_settings_controller );
	Rbdb_Database* Rbdb_DatabaseCursorSettingsController_parentDatabase(	Rbdb_DatabaseCursorSettingsController* database_cursor_settings_controller );
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursorSettingsController_parentDatabaseCursor(	Rbdb_DatabaseCursorSettingsController* database_cursor_settings_controller );
																																		
	BOOL												Rbdb_DatabaseCursorSettingsController_duplicateRetainsLocation(			Rbdb_DatabaseCursorSettingsController*			cursor_settings_controller );
	void												Rbdb_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOn(		Rbdb_DatabaseCursorSettingsController*			cursor_settings_controller );
	void												Rbdb_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOff(		Rbdb_DatabaseCursorSettingsController*			cursor_settings_controller );
																																	
	Rbdb_DatabaseCursorCacheSettingsController*		Rbdb_DatabaseCursorSettingsController_cacheSettingsController(				Rbdb_DatabaseCursorSettingsController*			cursor_settings_controller );
	Rbdb_DatabaseCursorReadWriteSettingsController*			Rbdb_DatabaseCursorSettingsController_readWriteSettingsController(			Rbdb_DatabaseCursorSettingsController*			cursor_settings_controller );

#endif

