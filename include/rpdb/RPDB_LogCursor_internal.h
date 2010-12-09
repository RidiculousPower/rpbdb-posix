#ifndef Rbdb_LOG_CURSOR_INTERNAL
	#define Rbdb_LOG_CURSOR_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

Rbdb_Log*	Rbdb_LogCursor_internal_retrieveLogRecord(	Rbdb_LogCursor*	log_cursor,
																 uint32_t			which_record	);

void Rbdb_LogCursor_internal_freeFromRuntimeStorage(	Rbdb_LogCursor** log_cursor );

#endif