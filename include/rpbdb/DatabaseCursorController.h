/*
 *		RPbdb::DatabaseController::Database::DatabaseCursorController
 *
 *
 */

#ifndef RPBDB_DATABASE_CURSOR_CONTROLLER
	#define RPBDB_DATABASE_CURSOR_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseCursorController* RPbdb_DatabaseCursorController_new( RPbdb_Database* parent_database );

	void										RPbdb_DatabaseCursorController_free(	RPbdb_DatabaseCursorController** database_cursor_controller );
	RPbdb_DatabaseCursorSettingsController*		RPbdb_DatabaseCursorController_settingsController(	RPbdb_DatabaseCursorController* database_cursor_controller );
	RPbdb_Environment*					RPbdb_DatabaseCursorController_parentEnvironment(	RPbdb_DatabaseCursorController* database_cursor_controller );
	RPbdb_Database* RPbdb_DatabaseCursorController_parentDatabase(	RPbdb_DatabaseCursorController* database_cursor_controller );

	void											RPbdb_DatabaseCursorController_closeAllCursors(			RPbdb_DatabaseCursorController*			cursor_controller );
	void											RPbdb_DatabaseCursorController_freeAllCursors(			RPbdb_DatabaseCursorController*			cursor_controller );
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursorController_cursor( RPbdb_DatabaseCursorController*		cursor_controller );

#endif

