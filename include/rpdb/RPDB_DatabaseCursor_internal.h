#ifndef Rbdb_DATABASE_CURSOR_INTERNAL
	#define Rbdb_DATABASE_CURSOR_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void Rbdb_DatabaseCursor_internal_ensureOpen( Rbdb_DatabaseCursor* database_cursor );
Rbdb_Record* Rbdb_DatabaseCursor_internal_writeRecord(	Rbdb_DatabaseCursor*	database_cursor, 
															uint32_t				flags,
															Rbdb_Record*			record );
Rbdb_Record* Rbdb_DatabaseCursor_internal_writeKeyDataPair(	Rbdb_DatabaseCursor*	database_cursor, 
																uint32_t				flags,
																Rbdb_Key*				key,
																Rbdb_Data*				data );
Rbdb_Record* Rbdb_DatabaseCursor_internal_writeRawKeyDataPair(	Rbdb_DatabaseCursor*	database_cursor, 
																	uint32_t				flags,
																	void*					key,
																	uint32_t				key_size,
																	void*					data,
																	uint32_t				data_size );
Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	Rbdb_DatabaseCursor*		database_cursor, 
																	uint32_t					flag, 
																	void*						key,
																	uint32_t					key_size,
																	void*						data,
																	uint32_t					data_size );
Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveKeyDataPair(	Rbdb_DatabaseCursor*		database_cursor, 
																	uint32_t					flags, 
																	Rbdb_Key*					key,
																	Rbdb_Data*					data	);
Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveRecord(	Rbdb_DatabaseCursor*		database_cursor, 
															uint32_t					flags, 
															Rbdb_Record*				record);

Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveFirst(	Rbdb_DatabaseCursor*	cursor,
																													Rbdb_Record*					record );
Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveCurrent(	Rbdb_DatabaseCursor*	cursor,
																														Rbdb_Record*					record );
Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveNext(	Rbdb_DatabaseCursor*	cursor,
																												Rbdb_Record*					record );
Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveNextDuplicate(	Rbdb_DatabaseCursor*	cursor,
																																	Rbdb_Record*					record );
Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveNextNonDuplicate(	Rbdb_DatabaseCursor*	cursor,
																																		Rbdb_Record*					record );

void Rbdb_DatabaseCursor_internal_freeFromRuntimeStorage(	Rbdb_DatabaseCursor** database_cursor );

#endif