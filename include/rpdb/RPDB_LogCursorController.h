/*
 *		RPDB::LogController::LogCursorController
 *
 *	
 */

#ifndef RPDB_LOG_CURSOR_CONTROLLER
	#define RPDB_LOG_CURSOR_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_LogCursorController*		RPDB_LogCursorController_new(						RPDB_LogController*			log_controller );

	void								RPDB_LogCursorController_free(	RPDB_LogCursorController** log_cursor_controller );
	RPDB_LogSettingsController*	RPDB_LogCursorController_settingsController(	RPDB_LogCursorController* log_cursor_controller );
	RPDB_Environment*			RPDB_LogCursorController_parentEnvironment(	RPDB_LogCursorController* log_cursor_controller );

	void							RPDB_LogCursorController_closeAllCursors(			RPDB_LogCursorController*		cursor_controller );
	void							RPDB_LogCursorController_freeAllCursors(			RPDB_LogCursorController*		cursor_controller );

	char* RPDB_LogCursorController_internal_uniqueIdentifier( RPDB_LogCursorController* log_cursor_controller );

#endif

