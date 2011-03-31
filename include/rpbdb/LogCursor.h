/*
 *		RPbdb::LogController::LogCursorController::LogCursor
 *
 *	
 */

#ifndef RPBDB_LOG_CURSOR
	#define RPBDB_LOG_CURSOR

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_LogCursor*		RPbdb_LogCursor_new(									RPbdb_LogCursorController*	parent_log_cursor_controller );

	void					RPbdb_LogCursor_free(	RPbdb_LogCursor** log_cursor );
	RPbdb_LogSettingsController*	RPbdb_LogCursor_settingsController(	RPbdb_LogCursor* log_cursor );
	RPbdb_Environment*			RPbdb_LogCursor_parentEnvironment(	RPbdb_LogCursor* log_cursor );

	RPbdb_LogCursor*		RPbdb_LogCursor_open(									RPbdb_LogCursor* 			log_cursor );
	void					RPbdb_LogCursor_close(						RPbdb_LogCursor* 			log_cursor );
	RPbdb_Log*				RPbdb_LogCursor_retrieveCurrentLogRecord(		RPbdb_LogCursor* 			log_cursor );
	RPbdb_Log*				RPbdb_LogCursor_retrieveFirstLogRecord(		RPbdb_LogCursor* 			log_cursor );
	RPbdb_Log*				RPbdb_LogCursor_retrieveLastLogRecord(		RPbdb_LogCursor* 			log_cursor );
	RPbdb_Log*				RPbdb_LogCursor_retrieveNextLogRecord(		RPbdb_LogCursor* 			log_cursor );
	RPbdb_Log*				RPbdb_LogCursor_retrievePreviousLogRecord(	RPbdb_LogCursor* 			log_cursor );
	RPbdb_Log*				RPbdb_LogCursor_retrieveLogRecord(			RPbdb_LogCursor*			log_cursor,
	 																				RPbdb_LogSequenceNumber*	log_sequence_number );
#endif

