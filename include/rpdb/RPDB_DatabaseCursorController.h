/*
 *		Rbdb::DatabaseController::Database::DatabaseCursorController
 *
 *
 */

#ifndef Rbdb_DATABASE_CURSOR_CONTROLLER
	#define Rbdb_DATABASE_CURSOR_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseCursorController* Rbdb_DatabaseCursorController_new( Rbdb_Database* parent_database );

	void										Rbdb_DatabaseCursorController_free(	Rbdb_DatabaseCursorController** database_cursor_controller );
	Rbdb_DatabaseCursorSettingsController*		Rbdb_DatabaseCursorController_settingsController(	Rbdb_DatabaseCursorController* database_cursor_controller );
	Rbdb_Environment*					Rbdb_DatabaseCursorController_parentEnvironment(	Rbdb_DatabaseCursorController* database_cursor_controller );
	Rbdb_Database* Rbdb_DatabaseCursorController_parentDatabase(	Rbdb_DatabaseCursorController* database_cursor_controller );

	void											Rbdb_DatabaseCursorController_closeAllCursors(			Rbdb_DatabaseCursorController*			cursor_controller );
	void											Rbdb_DatabaseCursorController_freeAllCursors(			Rbdb_DatabaseCursorController*			cursor_controller );
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursorController_cursor( Rbdb_DatabaseCursorController*		cursor_controller );

#endif

