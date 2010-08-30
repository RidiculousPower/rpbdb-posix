/*
 *		RPDB::LogController::LogCursorController::LogCursor
 *
 *	
 */

#ifndef RPDB_LOG_CURSOR
	#define RPDB_LOG_CURSOR

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_LogCursor*		RPDB_LogCursor_new(									RPDB_LogCursorController*	parent_log_cursor_controller );

	void					RPDB_LogCursor_free(	RPDB_LogCursor** log_cursor );
	RPDB_LogSettingsController*	RPDB_LogCursor_settingsController(	RPDB_LogCursor* log_cursor );
	RPDB_Environment*			RPDB_LogCursor_parentEnvironment(	RPDB_LogCursor* log_cursor );

	RPDB_LogCursor*		RPDB_LogCursor_open(									RPDB_LogCursor* 			log_cursor );
	void					RPDB_LogCursor_close(						RPDB_LogCursor* 			log_cursor );
	RPDB_Log*				RPDB_LogCursor_retrieveCurrentLogRecord(		RPDB_LogCursor* 			log_cursor );
	RPDB_Log*				RPDB_LogCursor_retrieveFirstLogRecord(		RPDB_LogCursor* 			log_cursor );
	RPDB_Log*				RPDB_LogCursor_retrieveLastLogRecord(		RPDB_LogCursor* 			log_cursor );
	RPDB_Log*				RPDB_LogCursor_retrieveNextLogRecord(		RPDB_LogCursor* 			log_cursor );
	RPDB_Log*				RPDB_LogCursor_retrievePreviousLogRecord(	RPDB_LogCursor* 			log_cursor );
	RPDB_Log*				RPDB_LogCursor_retrieveLogRecord(			RPDB_LogCursor*			log_cursor,
	 																				RPDB_LogSequenceNumber*	log_sequence_number );
#endif

