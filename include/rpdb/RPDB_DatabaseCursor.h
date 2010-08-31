/*
 *		RPDB::DatabaseController::Database::DatabaseCursorController::DatabaseCursor
 *
 *
 */

#ifndef RPDB_DATABASE_CURSOR
	#define RPDB_DATABASE_CURSOR

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseCursor* RPDB_DatabaseCursor_new( RPDB_DatabaseCursorController* parent_database_cursor_controller );
	void RPDB_DatabaseCursor_free(	RPDB_DatabaseCursor** database_cursor );
	RPDB_DatabaseCursorSettingsController* RPDB_DatabaseCursor_settingsController(	RPDB_DatabaseCursor* database_cursor );
	RPDB_Environment* RPDB_DatabaseCursor_parentEnvironment(	RPDB_DatabaseCursor* database_cursor );
	RPDB_Database* RPDB_DatabaseCursor_parentDatabase(	RPDB_DatabaseCursor* database_cursor );
	RPDB_DatabaseCursorController* RPDB_DatabaseCursor_parentDatabaseCursorController(	RPDB_DatabaseCursor* database_cursor );
	RPDB_DatabaseCursor* RPDB_DatabaseCursor_open( RPDB_DatabaseCursor* database_cursor );
BOOL RPDB_DatabaseCursor_isOpen( RPDB_DatabaseCursor* database_cursor );
	RPDB_DatabaseCursor* RPDB_DatabaseCursor_close( RPDB_DatabaseCursor* database_cursor );
	RPDB_DatabaseCursor* RPDB_DatabaseCursor_duplicateCursor( RPDB_DatabaseCursor* database_cursor );
	void RPDB_DatabaseCursor_writeRecordAsCurrentData(	RPDB_DatabaseCursor*	database_cursor, 
														RPDB_Record*			record );
	void RPDB_DatabaseCursor_writeDataAsCurrent(	RPDB_DatabaseCursor*	database_cursor, 
													RPDB_Data*				data );
	void RPDB_DatabaseCursor_writeRawDataAsCurrent(	RPDB_DatabaseCursor*	database_cursor, 
														void*					data_raw,
														uint32_t				data_size );
	void RPDB_DatabaseCursor_writeRecordAsDuplicateDataAfterCurrent(	RPDB_DatabaseCursor*	database_cursor, 
																		RPDB_Record*							record );
	void RPDB_DatabaseCursor_writeDataAsDuplicateAfterCurrent(	RPDB_DatabaseCursor*	database_cursor, 
																RPDB_Data*				data );
	void RPDB_DatabaseCursor_writeRawDataAsDuplicateAfterCurrent(	RPDB_DatabaseCursor*	database_cursor, 
																	void*					data_raw,
																	uint32_t				data_size );
	void RPDB_DatabaseCursor_writeRecordAsDuplicateBeforeCurrent(	RPDB_DatabaseCursor*	database_cursor, 
																	RPDB_Record*							record );
	void RPDB_DatabaseCursor_writeDataAsDuplicateBeforeCurrent(	RPDB_DatabaseCursor*	database_cursor, 
																	RPDB_Data*				data );
	void RPDB_DatabaseCursor_writeRawDataAsDuplicateBeforeCurrent(	RPDB_DatabaseCursor*	database_cursor, 
																	void*					data_raw,
																	uint32_t				data_size );
	void RPDB_DatabaseCursor_writeRecord(	RPDB_DatabaseCursor*	database_cursor, 
										  RPDB_Record*							record );
	void RPDB_DatabaseCursor_writeKeyDataPair(		RPDB_DatabaseCursor*	database_cursor, 
											   RPDB_Key*				key,
											   RPDB_Data*				data );
	void RPDB_DatabaseCursor_writeRawKeyDataPair(	RPDB_DatabaseCursor*	database_cursor, 
												  void*					key_raw,
												  uint32_t				key_size,
												  void*					data_raw,
												  uint32_t				data_size );
	void RPDB_DatabaseCursor_writeRecordBeforeAnyDuplicates(	RPDB_DatabaseCursor*	database_cursor, 
																		RPDB_Record*							record );
	void RPDB_DatabaseCursor_writeKeyDataPairBeforeAnyDuplicates(		RPDB_DatabaseCursor*	database_cursor, 
																		RPDB_Key*				key,
																		RPDB_Data*				data );
	void RPDB_DatabaseCursor_writeRawKeyDataPairBeforeAnyDuplicates(	RPDB_DatabaseCursor*	database_cursor, 
																		void*					key_raw,
																		uint32_t				key_size,
																		void*					data_raw,
																		uint32_t				data_size );
	void RPDB_DatabaseCursor_writeRecordAfterAnyDuplicates(	RPDB_DatabaseCursor*	database_cursor, 
																RPDB_Record*							record );
	void RPDB_DatabaseCursor_writeKeyDataPairAfterAnyDuplicates(	RPDB_DatabaseCursor*	database_cursor, 
																	RPDB_Key*				key,
																	RPDB_Data*				data );
	void RPDB_DatabaseCursor_writeRawKeyDataPairAfterAnyDuplicates(	RPDB_DatabaseCursor*	database_cursor, 
																		void*					key_raw,
																		uint32_t				key_size,
																		void*					data_raw,
																		uint32_t				data_size );
	void RPDB_DatabaseCursor_writeRecordOnlyIfNotInDatabase(	RPDB_DatabaseCursor*	database_cursor, 
																RPDB_Record*							record );
	void RPDB_DatabaseCursor_writeKeyDataPairOnlyIfNotInDatabase(	RPDB_DatabaseCursor*	database_cursor, 
																	RPDB_Key*				key,
																	RPDB_Data*				data );
	void RPDB_DatabaseCursor_writeRawKeyDataPairOnlyIfNotInDatabase(	RPDB_DatabaseCursor*	database_cursor, 
																		void*					key_raw,
																		uint32_t				key_size,
																		void*					data_raw,
																		uint32_t				data_size );
	BOOL RPDB_DatabaseCursor_keyExists(	RPDB_DatabaseCursor*		database_cursor, 
											RPDB_Key*					key );
	BOOL RPDB_DatabaseCursor_rawKeyExists(	RPDB_DatabaseCursor*		database_cursor, 
											void*						raw_key,
											uint32_t					key_size );
	RPDB_Record* RPDB_DatabaseCursor_retrieveRecord(	RPDB_DatabaseCursor*		database_cursor, 
														RPDB_Record*				record );
	RPDB_Record* RPDB_DatabaseCursor_retrieveKey(	RPDB_DatabaseCursor*		database_cursor, 
													RPDB_Key*					key_data );
	RPDB_Record* RPDB_DatabaseCursor_retrieveRawKey(	RPDB_DatabaseCursor*		database_cursor, 
														void*						raw_key,
														uint32_t					key_size );
	RPDB_Record* RPDB_DatabaseCursor_retrieveMatchingKeyDataPair(	RPDB_DatabaseCursor*		database_cursor, 
																	RPDB_Key*					key_data,
																	RPDB_Data*					data );
	RPDB_Record* RPDB_DatabaseCursor_retrieveMatchingRawKeyDataPair(	RPDB_DatabaseCursor*		database_cursor,
																		void*						raw_key,
																		uint32_t					key_size,
																		void*						raw_data,
																		uint32_t					data_size );
	RPDB_Record* RPDB_DatabaseCursor_retrieveRecordWithNumber(	RPDB_DatabaseCursor* 	database_cursor,
	 																db_recno_t*									record_id );
	RPDB_Record* RPDB_DatabaseCursor_retrieveRecordWithNumberAsKey(	RPDB_DatabaseCursor* 	database_cursor,
	 																	RPDB_Key*				key_with_record_number );
	RPDB_Record* RPDB_DatabaseCursor_retrievePartialRawKey(	RPDB_DatabaseCursor*		database_cursor,
																void*										raw_key,
																uint32_t									key_size );
	RPDB_Record* RPDB_DatabaseCursor_retrievePartialData(	RPDB_DatabaseCursor*		database_cursor,
	 														RPDB_Data*					data );
	RPDB_Record* RPDB_DatabaseCursor_retrievePartialKeyDataPair(	RPDB_DatabaseCursor*		database_cursor,
																	RPDB_Key*					partial_key,
																	RPDB_Data*					partial_data );
	RPDB_Record* RPDB_DatabaseCursor_retrieveRawKeyPartialDataPair(	RPDB_DatabaseCursor*		database_cursor,
																		void*										raw_key,
																		uint32_t									key_size,
																		void*										raw_data,
																		uint32_t									data_size );
	RPDB_Record* RPDB_DatabaseCursor_retrieveCurrent( RPDB_DatabaseCursor* database_cursor );
	RPDB_Record* RPDB_DatabaseCursor_retrieveFirst( RPDB_DatabaseCursor* database_cursor );
	RPDB_Record* RPDB_DatabaseCursor_retrieveLast( RPDB_DatabaseCursor* database_cursor );
	RPDB_Record* RPDB_DatabaseCursor_retrieveNext( RPDB_DatabaseCursor* database_cursor );
	RPDB_Record* RPDB_DatabaseCursor_retrieveNextDuplicate( RPDB_DatabaseCursor* database_cursor );
	RPDB_Record* RPDB_DatabaseCursor_retrieveNextNonDuplicate( RPDB_DatabaseCursor* database_cursor );
	RPDB_Record* RPDB_DatabaseCursor_retrievePrevious( RPDB_DatabaseCursor* database_cursor );
	RPDB_Record* RPDB_DatabaseCursor_retrievePreviousDuplicate( RPDB_DatabaseCursor* database_cursor );
	RPDB_Record* RPDB_DatabaseCursor_retrievePreviousNonDuplicate( RPDB_DatabaseCursor* database_cursor );
	RPDB_Record* RPDB_DatabaseCursor_retrieveCurrentRecordNumber( RPDB_DatabaseCursor* database_cursor );
	db_recno_t RPDB_DatabaseCursor_countDuplicatesForCurrentKey( RPDB_DatabaseCursor* database_cursor );
	void RPDB_DatabaseCursor_resetIteration( RPDB_DatabaseCursor* database_cursor );
void RPDB_DatabaseCursor_resetDuplicateIteration( RPDB_DatabaseCursor* database_cursor );
	RPDB_Record* RPDB_DatabaseCursor_iterate( RPDB_DatabaseCursor* database_cursor,
																						RPDB_Record*					record );
	RPDB_Record* RPDB_DatabaseCursor_iterateDuplicates( RPDB_DatabaseCursor* database_cursor,
																											RPDB_Record*					record );
	RPDB_Record* RPDB_DatabaseCursor_iterateKeys( RPDB_DatabaseCursor* database_cursor,
																								RPDB_Record*					record );
	RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteCurrentRecord( RPDB_DatabaseCursor*	database_cursor );
	RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteKey(	RPDB_DatabaseCursor*	database_cursor,
	 														RPDB_Key*								key	);
	RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteRawKey(	RPDB_DatabaseCursor*	database_cursor,
	 															void*					key,
																uint32_t				key_size );
	RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteKeyDataPair(	RPDB_DatabaseCursor*	database_cursor,
	 																	RPDB_Key*				key,
	 																	RPDB_Data*				data	);
	RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteRawKeyDataPair(	RPDB_DatabaseCursor*	database_cursor,
	 																	void*					raw_key,
																		uint32_t				key_size,
																		void*					raw_data,
																		uint32_t				data_size	);
	RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteRecordNumber(	RPDB_DatabaseCursor*	database_cursor,
	 																	db_recno_t*				record_number	);
	RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteRecord(	RPDB_DatabaseCursor*	database_cursor,
	 															RPDB_Record*			record	);

#endif

