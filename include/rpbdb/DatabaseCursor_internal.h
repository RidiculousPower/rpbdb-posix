#ifndef RPBDB_DATABASE_CURSOR_INTERNAL
	#define RPBDB_DATABASE_CURSOR_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void RPbdb_DatabaseCursor_internal_ensureOpen( RPbdb_DatabaseCursor* database_cursor );
RPbdb_Record* RPbdb_DatabaseCursor_internal_writeRecord(	RPbdb_DatabaseCursor*	database_cursor, 
															uint32_t				flags,
															RPbdb_Record*			record );
RPbdb_Record* RPbdb_DatabaseCursor_internal_writeKeyDataPair(	RPbdb_DatabaseCursor*	database_cursor, 
																uint32_t				flags,
																RPbdb_Key*				key,
																RPbdb_Data*				data );
RPbdb_Record* RPbdb_DatabaseCursor_internal_writeRawKeyDataPair(	RPbdb_DatabaseCursor*	database_cursor, 
																	uint32_t				flags,
																	void*					key,
																	uint32_t				key_size,
																	void*					data,
																	uint32_t				data_size );
RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	RPbdb_DatabaseCursor*		database_cursor, 
																	uint32_t					flag, 
																	void*						key,
																	uint32_t					key_size,
																	void*						data,
																	uint32_t					data_size );
RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveKeyDataPair(	RPbdb_DatabaseCursor*		database_cursor, 
																	uint32_t					flags, 
																	RPbdb_Key*					key,
																	RPbdb_Data*					data	);
RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveRecord(	RPbdb_DatabaseCursor*		database_cursor, 
															uint32_t					flags, 
															RPbdb_Record*				record);

RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveFirst(	RPbdb_DatabaseCursor*	cursor,
																													RPbdb_Record*					record );
RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveCurrent(	RPbdb_DatabaseCursor*	cursor,
																														RPbdb_Record*					record );
RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveNext(	RPbdb_DatabaseCursor*	cursor,
																												RPbdb_Record*					record );
RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveNextDuplicate(	RPbdb_DatabaseCursor*	cursor,
																																	RPbdb_Record*					record );
RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveNextNonDuplicate(	RPbdb_DatabaseCursor*	cursor,
																																		RPbdb_Record*					record );

void RPbdb_DatabaseCursor_internal_freeFromRuntimeStorage(	RPbdb_DatabaseCursor** database_cursor );

#endif