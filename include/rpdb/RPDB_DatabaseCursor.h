/*
 *		Rbdb::DatabaseController::Database::DatabaseCursorController::DatabaseCursor
 *
 *
 */

#ifndef Rbdb_DATABASE_CURSOR
	#define Rbdb_DATABASE_CURSOR

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_new( Rbdb_DatabaseCursorController* parent_database_cursor_controller );
	void Rbdb_DatabaseCursor_free(	Rbdb_DatabaseCursor** database_cursor );
	Rbdb_DatabaseCursorSettingsController* Rbdb_DatabaseCursor_settingsController(	Rbdb_DatabaseCursor* database_cursor );
	Rbdb_Environment* Rbdb_DatabaseCursor_parentEnvironment(	Rbdb_DatabaseCursor* database_cursor );
	Rbdb_Database* Rbdb_DatabaseCursor_parentDatabase(	Rbdb_DatabaseCursor* database_cursor );
	Rbdb_DatabaseCursorController* Rbdb_DatabaseCursor_parentDatabaseCursorController(	Rbdb_DatabaseCursor* database_cursor );
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_open( Rbdb_DatabaseCursor* database_cursor );
BOOL Rbdb_DatabaseCursor_isOpen( Rbdb_DatabaseCursor* database_cursor );
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_close( Rbdb_DatabaseCursor* database_cursor );
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_duplicateCursor( Rbdb_DatabaseCursor* database_cursor );
	void Rbdb_DatabaseCursor_overwriteCurrentDataWithRecord(	Rbdb_DatabaseCursor*	database_cursor, 
														Rbdb_Record*			record );
	void Rbdb_DatabaseCursor_overwriteCurrentData(	Rbdb_DatabaseCursor*	database_cursor, 
													Rbdb_Data*				data );
	void Rbdb_DatabaseCursor_overwriteCurrentDataWithRawData(	Rbdb_DatabaseCursor*	database_cursor, 
														void*					data_raw,
														uint32_t				data_size );
	void Rbdb_DatabaseCursor_writeRecordAsDuplicateDataAfterCurrent(	Rbdb_DatabaseCursor*	database_cursor, 
																		Rbdb_Record*							record );
	void Rbdb_DatabaseCursor_writeDataAsDuplicateAfterCurrent(	Rbdb_DatabaseCursor*	database_cursor, 
																Rbdb_Data*				data );
	void Rbdb_DatabaseCursor_writeRawDataAsDuplicateAfterCurrent(	Rbdb_DatabaseCursor*	database_cursor, 
																	void*					data_raw,
																	uint32_t				data_size );
	void Rbdb_DatabaseCursor_writeRecordAsDuplicateBeforeCurrent(	Rbdb_DatabaseCursor*	database_cursor, 
																	Rbdb_Record*							record );
	void Rbdb_DatabaseCursor_writeDataAsDuplicateBeforeCurrent(	Rbdb_DatabaseCursor*	database_cursor, 
																	Rbdb_Data*				data );
	void Rbdb_DatabaseCursor_writeRawDataAsDuplicateBeforeCurrent(	Rbdb_DatabaseCursor*	database_cursor, 
																	void*					data_raw,
																	uint32_t				data_size );
	void Rbdb_DatabaseCursor_writeRecord(	Rbdb_DatabaseCursor*	database_cursor, 
										  Rbdb_Record*							record );
	void Rbdb_DatabaseCursor_writeKeyDataPair(		Rbdb_DatabaseCursor*	database_cursor, 
											   Rbdb_Key*				key,
											   Rbdb_Data*				data );
	void Rbdb_DatabaseCursor_writeRawKeyDataPair(	Rbdb_DatabaseCursor*	database_cursor, 
												  void*					key_raw,
												  uint32_t				key_size,
												  void*					data_raw,
												  uint32_t				data_size );
	void Rbdb_DatabaseCursor_writeRecordBeforeAnyDuplicates(	Rbdb_DatabaseCursor*	database_cursor, 
																		Rbdb_Record*							record );
	void Rbdb_DatabaseCursor_writeKeyDataPairBeforeAnyDuplicates(		Rbdb_DatabaseCursor*	database_cursor, 
																		Rbdb_Key*				key,
																		Rbdb_Data*				data );
	void Rbdb_DatabaseCursor_writeRawKeyDataPairBeforeAnyDuplicates(	Rbdb_DatabaseCursor*	database_cursor, 
																		void*					key_raw,
																		uint32_t				key_size,
																		void*					data_raw,
																		uint32_t				data_size );
	void Rbdb_DatabaseCursor_writeRecordAfterAnyDuplicates(	Rbdb_DatabaseCursor*	database_cursor, 
																Rbdb_Record*							record );
	void Rbdb_DatabaseCursor_writeKeyDataPairAfterAnyDuplicates(	Rbdb_DatabaseCursor*	database_cursor, 
																	Rbdb_Key*				key,
																	Rbdb_Data*				data );
	void Rbdb_DatabaseCursor_writeRawKeyDataPairAfterAnyDuplicates(	Rbdb_DatabaseCursor*	database_cursor, 
																		void*					key_raw,
																		uint32_t				key_size,
																		void*					data_raw,
																		uint32_t				data_size );
	BOOL Rbdb_DatabaseCursor_writeRecordOnlyIfNotInDatabase(	Rbdb_DatabaseCursor*	database_cursor, 
																Rbdb_Record*							record );
	BOOL Rbdb_DatabaseCursor_writeKeyDataPairOnlyIfNotInDatabase(	Rbdb_DatabaseCursor*	database_cursor, 
																	Rbdb_Key*				key,
																	Rbdb_Data*				data );
	BOOL Rbdb_DatabaseCursor_writeRawKeyDataPairOnlyIfNotInDatabase(	Rbdb_DatabaseCursor*	database_cursor, 
																		void*					key_raw,
																		uint32_t				key_size,
																		void*					data_raw,
																		uint32_t				data_size );
	BOOL Rbdb_DatabaseCursor_keyExists(	Rbdb_DatabaseCursor*		database_cursor, 
											Rbdb_Key*					key );
	BOOL Rbdb_DatabaseCursor_rawKeyExists(	Rbdb_DatabaseCursor*		database_cursor, 
											void*						raw_key,
											uint32_t					key_size );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveRecord(	Rbdb_DatabaseCursor*		database_cursor, 
														Rbdb_Record*				record );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveKey(	Rbdb_DatabaseCursor*		database_cursor, 
													Rbdb_Key*					key_data );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveRawKey(	Rbdb_DatabaseCursor*		database_cursor, 
														void*						raw_key,
														uint32_t					key_size );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveMatchingKeyDataPair(	Rbdb_DatabaseCursor*		database_cursor, 
																	Rbdb_Key*					key_data,
																	Rbdb_Data*					data );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveMatchingRawKeyDataPair(	Rbdb_DatabaseCursor*		database_cursor,
																		void*						raw_key,
																		uint32_t					key_size,
																		void*						raw_data,
																		uint32_t					data_size );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveRecordWithNumber(	Rbdb_DatabaseCursor* 	database_cursor,
	 																db_recno_t*									record_id );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveRecordWithNumberAsKey(	Rbdb_DatabaseCursor* 	database_cursor,
	 																	Rbdb_Key*				key_with_record_number );

	Rbdb_Record* Rbdb_DatabaseCursor_retrievePartialRawKey(	Rbdb_DatabaseCursor*		database_cursor,
																													void*										key_raw,
																													uint32_t								key_size );
	Rbdb_Record* Rbdb_DatabaseCursor_retrievePartialKey(	Rbdb_DatabaseCursor*		database_cursor,
																												Rbdb_Key*								partial_key );
	Rbdb_Record* Rbdb_DatabaseCursor_retrievePartialKeyInRecord(	Rbdb_DatabaseCursor*		database_cursor,
																																Rbdb_Record*						record  );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveDuplicateMatchingRawData(	Rbdb_DatabaseCursor*		database_cursor,
																																			void*										key_raw,
																																			uint32_t								key_size,
																																			void*										data_raw,
																																			uint32_t								data_size );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveDuplicateMatchingPartialData(	Rbdb_DatabaseCursor*		database_cursor,
																																					Rbdb_Key*								partial_key,
																																					Rbdb_Data*							partial_data );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveDuplicateMatchingPartialDataInRecord(	Rbdb_DatabaseCursor*		database_cursor,
																																									Rbdb_Record*						record  );

	Rbdb_Record* Rbdb_DatabaseCursor_retrieveCurrent( Rbdb_DatabaseCursor* database_cursor );
	BOOL Rbdb_DatabaseCursor_setToFirst( Rbdb_DatabaseCursor* database_cursor );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveFirst( Rbdb_DatabaseCursor* database_cursor );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveLast( Rbdb_DatabaseCursor* database_cursor );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveNext( Rbdb_DatabaseCursor* database_cursor );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveNextDuplicate( Rbdb_DatabaseCursor* database_cursor );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveNextNonDuplicate( Rbdb_DatabaseCursor* database_cursor );
	Rbdb_Record* Rbdb_DatabaseCursor_retrievePrevious( Rbdb_DatabaseCursor* database_cursor );
	Rbdb_Record* Rbdb_DatabaseCursor_retrievePreviousDuplicate( Rbdb_DatabaseCursor* database_cursor );
	Rbdb_Record* Rbdb_DatabaseCursor_retrievePreviousNonDuplicate( Rbdb_DatabaseCursor* database_cursor );
	Rbdb_Record* Rbdb_DatabaseCursor_retrieveCurrentRecordNumber( Rbdb_DatabaseCursor* database_cursor );
	db_recno_t Rbdb_DatabaseCursor_countDuplicatesForCurrentKey( Rbdb_DatabaseCursor* database_cursor );
	void Rbdb_DatabaseCursor_resetIteration( Rbdb_DatabaseCursor* database_cursor );
void Rbdb_DatabaseCursor_resetDuplicateIteration( Rbdb_DatabaseCursor* database_cursor );
	Rbdb_Record* Rbdb_DatabaseCursor_iterate( Rbdb_DatabaseCursor* database_cursor,
																						Rbdb_Record*					record );
	Rbdb_Record* Rbdb_DatabaseCursor_iterateDuplicates( Rbdb_DatabaseCursor* database_cursor,
																											Rbdb_Record*					record );
	Rbdb_Record* Rbdb_DatabaseCursor_iterateKeys( Rbdb_DatabaseCursor* database_cursor,
																								Rbdb_Record*					record );
																								
																								
	Rbdb_Record* Rbdb_DatabaseCursor_slice( Rbdb_DatabaseCursor*	database_cursor,
																					uint32_t							length,
																					Rbdb_Record*					record );
	Rbdb_Record* Rbdb_DatabaseCursor_sliceKeys( Rbdb_DatabaseCursor*	database_cursor,
																							uint32_t							length,
																							Rbdb_Record*					record );
	Rbdb_Record* Rbdb_DatabaseCursor_sliceDuplicates( Rbdb_DatabaseCursor*	database_cursor,
																										uint32_t							length,
																										Rbdb_Record*					record );
																								
																								
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteCurrentRecord( Rbdb_DatabaseCursor*	database_cursor );
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteKey(	Rbdb_DatabaseCursor*	database_cursor,
	 														Rbdb_Key*								key	);
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteRawKey(	Rbdb_DatabaseCursor*	database_cursor,
	 															void*					key,
																uint32_t				key_size );
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteKeyDataPair(	Rbdb_DatabaseCursor*	database_cursor,
	 																	Rbdb_Key*				key,
	 																	Rbdb_Data*				data	);
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteRawKeyDataPair(	Rbdb_DatabaseCursor*	database_cursor,
	 																	void*					raw_key,
																		uint32_t				key_size,
																		void*					raw_data,
																		uint32_t				data_size	);
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteRecordNumber(	Rbdb_DatabaseCursor*	database_cursor,
	 																	db_recno_t*				record_number	);
	Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteRecord(	Rbdb_DatabaseCursor*	database_cursor,
	 															Rbdb_Record*			record	);

#endif

