/*
 *		Rbdb::LogController::LogCursorController::LogCursor
 *
 *	
 */

#ifndef RBDB_LOG_CURSOR
	#define RBDB_LOG_CURSOR

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_LogCursor*		Rbdb_LogCursor_new(									Rbdb_LogCursorController*	parent_log_cursor_controller );

	void					Rbdb_LogCursor_free(	Rbdb_LogCursor** log_cursor );
	Rbdb_LogSettingsController*	Rbdb_LogCursor_settingsController(	Rbdb_LogCursor* log_cursor );
	Rbdb_Environment*			Rbdb_LogCursor_parentEnvironment(	Rbdb_LogCursor* log_cursor );

	Rbdb_LogCursor*		Rbdb_LogCursor_open(									Rbdb_LogCursor* 			log_cursor );
	void					Rbdb_LogCursor_close(						Rbdb_LogCursor* 			log_cursor );
	Rbdb_Log*				Rbdb_LogCursor_retrieveCurrentLogRecord(		Rbdb_LogCursor* 			log_cursor );
	Rbdb_Log*				Rbdb_LogCursor_retrieveFirstLogRecord(		Rbdb_LogCursor* 			log_cursor );
	Rbdb_Log*				Rbdb_LogCursor_retrieveLastLogRecord(		Rbdb_LogCursor* 			log_cursor );
	Rbdb_Log*				Rbdb_LogCursor_retrieveNextLogRecord(		Rbdb_LogCursor* 			log_cursor );
	Rbdb_Log*				Rbdb_LogCursor_retrievePreviousLogRecord(	Rbdb_LogCursor* 			log_cursor );
	Rbdb_Log*				Rbdb_LogCursor_retrieveLogRecord(			Rbdb_LogCursor*			log_cursor,
	 																				Rbdb_LogSequenceNumber*	log_sequence_number );
#endif

