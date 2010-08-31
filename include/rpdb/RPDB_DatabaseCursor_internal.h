#ifndef RPDB_DATABASE_CURSOR_INTERNAL
	#define RPDB_DATABASE_CURSOR_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void RPDB_DatabaseCursor_internal_ensureOpen( RPDB_DatabaseCursor* database_cursor );
RPDB_Record* RPDB_DatabaseCursor_internal_writeRecord(	RPDB_DatabaseCursor*	database_cursor, 
															uint32_t				flags,
															RPDB_Record*			record );
RPDB_Record* RPDB_DatabaseCursor_internal_writeKeyDataPair(	RPDB_DatabaseCursor*	database_cursor, 
																uint32_t				flags,
																RPDB_Key*				key,
																RPDB_Data*				data );
RPDB_Record* RPDB_DatabaseCursor_internal_writeRawKeyDataPair(	RPDB_DatabaseCursor*	database_cursor, 
																	uint32_t				flags,
																	void*					key,
																	uint32_t				key_size,
																	void*					data,
																	uint32_t				data_size );
RPDB_Record* RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	RPDB_DatabaseCursor*		database_cursor, 
																	uint32_t					flag, 
																	void*						key,
																	uint32_t					key_size,
																	void*						data,
																	uint32_t					data_size );
RPDB_Record* RPDB_DatabaseCursor_internal_retrieveKeyDataPair(	RPDB_DatabaseCursor*		database_cursor, 
																	uint32_t					flags, 
																	RPDB_Key*					key,
																	RPDB_Data*					data	);
RPDB_Record* RPDB_DatabaseCursor_internal_retrieveRecord(	RPDB_DatabaseCursor*		database_cursor, 
															uint32_t					flags, 
															RPDB_Record*				record);

RPDB_Record* RPDB_DatabaseCursor_internal_retrieveFirst(	RPDB_DatabaseCursor*	cursor,
																													RPDB_Record*					record );
RPDB_Record* RPDB_DatabaseCursor_internal_retrieveCurrent(	RPDB_DatabaseCursor*	cursor,
																														RPDB_Record*					record );
RPDB_Record* RPDB_DatabaseCursor_internal_retrieveNext(	RPDB_DatabaseCursor*	cursor,
																												RPDB_Record*					record );
RPDB_Record* RPDB_DatabaseCursor_internal_retrieveNextDuplicate(	RPDB_DatabaseCursor*	cursor,
																																	RPDB_Record*					record );
RPDB_Record* RPDB_DatabaseCursor_internal_retrieveNextNonDuplicate(	RPDB_DatabaseCursor*	cursor,
																																		RPDB_Record*					record );


#endif