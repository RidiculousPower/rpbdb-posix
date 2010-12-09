/*
 *		Rbdb::LogController::LogCursorController
 *
 *	
 */

#ifndef Rbdb_LOG_CURSOR_CONTROLLER
	#define Rbdb_LOG_CURSOR_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_LogCursorController*		Rbdb_LogCursorController_new(						Rbdb_LogController*			log_controller );

	void								Rbdb_LogCursorController_free(	Rbdb_LogCursorController** log_cursor_controller );
	Rbdb_LogSettingsController*	Rbdb_LogCursorController_settingsController(	Rbdb_LogCursorController* log_cursor_controller );
	Rbdb_Environment*			Rbdb_LogCursorController_parentEnvironment(	Rbdb_LogCursorController* log_cursor_controller );

	void							Rbdb_LogCursorController_closeAllCursors(			Rbdb_LogCursorController*		cursor_controller );
	void							Rbdb_LogCursorController_freeAllCursors(			Rbdb_LogCursorController*		cursor_controller );

#endif

