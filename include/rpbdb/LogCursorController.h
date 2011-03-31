/*
 *		RPbdb::LogController::LogCursorController
 *
 *	
 */

#ifndef RPBDB_LOG_CURSOR_CONTROLLER
	#define RPBDB_LOG_CURSOR_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_LogCursorController*		RPbdb_LogCursorController_new(						RPbdb_LogController*			log_controller );

	void								RPbdb_LogCursorController_free(	RPbdb_LogCursorController** log_cursor_controller );
	RPbdb_LogSettingsController*	RPbdb_LogCursorController_settingsController(	RPbdb_LogCursorController* log_cursor_controller );
	RPbdb_Environment*			RPbdb_LogCursorController_parentEnvironment(	RPbdb_LogCursorController* log_cursor_controller );

	void							RPbdb_LogCursorController_closeAllCursors(			RPbdb_LogCursorController*		cursor_controller );
	void							RPbdb_LogCursorController_freeAllCursors(			RPbdb_LogCursorController*		cursor_controller );

#endif

