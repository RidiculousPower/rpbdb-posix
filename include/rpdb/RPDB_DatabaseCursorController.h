/*
 *		RPDB::DatabaseController::Database::DatabaseCursorController
 *
 *
 */

#ifndef RPDB_DATABASE_CURSOR_CONTROLLER
	#define RPDB_DATABASE_CURSOR_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseCursorController* RPDB_DatabaseCursorController_new( RPDB_Database* parent_database );

	void										RPDB_DatabaseCursorController_free(	RPDB_DatabaseCursorController** database_cursor_controller );
	RPDB_DatabaseCursorSettingsController*		RPDB_DatabaseCursorController_settingsController(	RPDB_DatabaseCursorController* database_cursor_controller );
	RPDB_Environment*					RPDB_DatabaseCursorController_parentEnvironment(	RPDB_DatabaseCursorController* database_cursor_controller );
	RPDB_Database* RPDB_DatabaseCursorController_parentDatabase(	RPDB_DatabaseCursorController* database_cursor_controller );

	void											RPDB_DatabaseCursorController_closeAllCursors(			RPDB_DatabaseCursorController*			cursor_controller );
	void											RPDB_DatabaseCursorController_freeAllCursors(			RPDB_DatabaseCursorController*			cursor_controller );
	RPDB_DatabaseCursor* RPDB_DatabaseCursorController_cursor( RPDB_DatabaseCursorController*		cursor_controller );

#endif

