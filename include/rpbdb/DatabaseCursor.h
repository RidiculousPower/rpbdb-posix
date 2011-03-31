/*
 *		RPbdb::DatabaseController::Database::DatabaseCursorController::DatabaseCursor
 *
 *
 */

#ifndef RPBDB_DATABASE_CURSOR
	#define RPBDB_DATABASE_CURSOR

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_new( RPbdb_DatabaseCursorController* parent_database_cursor_controller );
	void RPbdb_DatabaseCursor_free(	RPbdb_DatabaseCursor** database_cursor );
	RPbdb_DatabaseCursorSettingsController* RPbdb_DatabaseCursor_settingsController(	RPbdb_DatabaseCursor* database_cursor );
	RPbdb_Environment* RPbdb_DatabaseCursor_parentEnvironment(	RPbdb_DatabaseCursor* database_cursor );
	RPbdb_Database* RPbdb_DatabaseCursor_parentDatabase(	RPbdb_DatabaseCursor* database_cursor );
	RPbdb_DatabaseCursorController* RPbdb_DatabaseCursor_parentDatabaseCursorController(	RPbdb_DatabaseCursor* database_cursor );
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_open( RPbdb_DatabaseCursor* database_cursor );
BOOL RPbdb_DatabaseCursor_isOpen( RPbdb_DatabaseCursor* database_cursor );
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_close( RPbdb_DatabaseCursor* database_cursor );
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_duplicateCursor( RPbdb_DatabaseCursor* database_cursor );
	void RPbdb_DatabaseCursor_overwriteCurrentDataWithRecord(	RPbdb_DatabaseCursor*	database_cursor, 
														RPbdb_Record*			record );
	void RPbdb_DatabaseCursor_overwriteCurrentData(	RPbdb_DatabaseCursor*	database_cursor, 
													RPbdb_Data*				data );
	void RPbdb_DatabaseCursor_overwriteCurrentDataWithRawData(	RPbdb_DatabaseCursor*	database_cursor, 
														void*					data_raw,
														uint32_t				data_size );
	void RPbdb_DatabaseCursor_writeRecordAsDuplicateDataAfterCurrent(	RPbdb_DatabaseCursor*	database_cursor, 
																		RPbdb_Record*							record );
	void RPbdb_DatabaseCursor_writeDataAsDuplicateAfterCurrent(	RPbdb_DatabaseCursor*	database_cursor, 
																RPbdb_Data*				data );
	void RPbdb_DatabaseCursor_writeRawDataAsDuplicateAfterCurrent(	RPbdb_DatabaseCursor*	database_cursor, 
																	void*					data_raw,
																	uint32_t				data_size );
	void RPbdb_DatabaseCursor_writeRecordAsDuplicateBeforeCurrent(	RPbdb_DatabaseCursor*	database_cursor, 
																	RPbdb_Record*							record );
	void RPbdb_DatabaseCursor_writeDataAsDuplicateBeforeCurrent(	RPbdb_DatabaseCursor*	database_cursor, 
																	RPbdb_Data*				data );
	void RPbdb_DatabaseCursor_writeRawDataAsDuplicateBeforeCurrent(	RPbdb_DatabaseCursor*	database_cursor, 
																	void*					data_raw,
																	uint32_t				data_size );
	void RPbdb_DatabaseCursor_writeRecord(	RPbdb_DatabaseCursor*	database_cursor, 
										  RPbdb_Record*							record );
	void RPbdb_DatabaseCursor_writeKeyDataPair(		RPbdb_DatabaseCursor*	database_cursor, 
											   RPbdb_Key*				key,
											   RPbdb_Data*				data );
	void RPbdb_DatabaseCursor_writeRawKeyDataPair(	RPbdb_DatabaseCursor*	database_cursor, 
												  void*					key_raw,
												  uint32_t				key_size,
												  void*					data_raw,
												  uint32_t				data_size );
	void RPbdb_DatabaseCursor_writeRecordBeforeAnyDuplicates(	RPbdb_DatabaseCursor*	database_cursor, 
																		RPbdb_Record*							record );
	void RPbdb_DatabaseCursor_writeKeyDataPairBeforeAnyDuplicates(		RPbdb_DatabaseCursor*	database_cursor, 
																		RPbdb_Key*				key,
																		RPbdb_Data*				data );
	void RPbdb_DatabaseCursor_writeRawKeyDataPairBeforeAnyDuplicates(	RPbdb_DatabaseCursor*	database_cursor, 
																		void*					key_raw,
																		uint32_t				key_size,
																		void*					data_raw,
																		uint32_t				data_size );
	void RPbdb_DatabaseCursor_writeRecordAfterAnyDuplicates(	RPbdb_DatabaseCursor*	database_cursor, 
																RPbdb_Record*							record );
	void RPbdb_DatabaseCursor_writeKeyDataPairAfterAnyDuplicates(	RPbdb_DatabaseCursor*	database_cursor, 
																	RPbdb_Key*				key,
																	RPbdb_Data*				data );
	void RPbdb_DatabaseCursor_writeRawKeyDataPairAfterAnyDuplicates(	RPbdb_DatabaseCursor*	database_cursor, 
																		void*					key_raw,
																		uint32_t				key_size,
																		void*					data_raw,
																		uint32_t				data_size );
	BOOL RPbdb_DatabaseCursor_writeRecordOnlyIfNotInDatabase(	RPbdb_DatabaseCursor*	database_cursor, 
																RPbdb_Record*							record );
	BOOL RPbdb_DatabaseCursor_writeKeyDataPairOnlyIfNotInDatabase(	RPbdb_DatabaseCursor*	database_cursor, 
																	RPbdb_Key*				key,
																	RPbdb_Data*				data );
	BOOL RPbdb_DatabaseCursor_writeRawKeyDataPairOnlyIfNotInDatabase(	RPbdb_DatabaseCursor*	database_cursor, 
																		void*					key_raw,
																		uint32_t				key_size,
																		void*					data_raw,
																		uint32_t				data_size );
	BOOL RPbdb_DatabaseCursor_keyExists(	RPbdb_DatabaseCursor*		database_cursor, 
											RPbdb_Key*					key );
	BOOL RPbdb_DatabaseCursor_rawKeyExists(	RPbdb_DatabaseCursor*		database_cursor, 
											void*						raw_key,
											uint32_t					key_size );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveRecord(	RPbdb_DatabaseCursor*		database_cursor, 
														RPbdb_Record*				record );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveKey(	RPbdb_DatabaseCursor*		database_cursor, 
													RPbdb_Key*					key_data );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveRawKey(	RPbdb_DatabaseCursor*		database_cursor, 
														void*						raw_key,
														uint32_t					key_size );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveMatchingKeyDataPair(	RPbdb_DatabaseCursor*		database_cursor, 
																	RPbdb_Key*					key_data,
																	RPbdb_Data*					data );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveMatchingRawKeyDataPair(	RPbdb_DatabaseCursor*		database_cursor,
																		void*						raw_key,
																		uint32_t					key_size,
																		void*						raw_data,
																		uint32_t					data_size );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveRecordWithNumber(	RPbdb_DatabaseCursor* 	database_cursor,
	 																db_recno_t*									record_id );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveRecordWithNumberAsKey(	RPbdb_DatabaseCursor* 	database_cursor,
	 																	RPbdb_Key*				key_with_record_number );

	RPbdb_Record* RPbdb_DatabaseCursor_retrievePartialRawKey(	RPbdb_DatabaseCursor*		database_cursor,
																													void*										key_raw,
																													uint32_t								key_size );
	RPbdb_Record* RPbdb_DatabaseCursor_retrievePartialKey(	RPbdb_DatabaseCursor*		database_cursor,
																												RPbdb_Key*								partial_key );
	RPbdb_Record* RPbdb_DatabaseCursor_retrievePartialKeyInRecord(	RPbdb_DatabaseCursor*		database_cursor,
																																RPbdb_Record*						record  );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveDuplicateMatchingRawData(	RPbdb_DatabaseCursor*		database_cursor,
																																			void*										key_raw,
																																			uint32_t								key_size,
																																			void*										data_raw,
																																			uint32_t								data_size );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveDuplicateMatchingPartialData(	RPbdb_DatabaseCursor*		database_cursor,
																																					RPbdb_Key*								partial_key,
																																					RPbdb_Data*							partial_data );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveDuplicateMatchingPartialDataInRecord(	RPbdb_DatabaseCursor*		database_cursor,
																																									RPbdb_Record*						record  );

	RPbdb_Record* RPbdb_DatabaseCursor_retrieveCurrent( RPbdb_DatabaseCursor* database_cursor );
	BOOL RPbdb_DatabaseCursor_setToFirst( RPbdb_DatabaseCursor* database_cursor );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveFirst( RPbdb_DatabaseCursor* database_cursor );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveLast( RPbdb_DatabaseCursor* database_cursor );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveNext( RPbdb_DatabaseCursor* database_cursor );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveNextDuplicate( RPbdb_DatabaseCursor* database_cursor );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveNextNonDuplicate( RPbdb_DatabaseCursor* database_cursor );
	RPbdb_Record* RPbdb_DatabaseCursor_retrievePrevious( RPbdb_DatabaseCursor* database_cursor );
	RPbdb_Record* RPbdb_DatabaseCursor_retrievePreviousDuplicate( RPbdb_DatabaseCursor* database_cursor );
	RPbdb_Record* RPbdb_DatabaseCursor_retrievePreviousNonDuplicate( RPbdb_DatabaseCursor* database_cursor );
	RPbdb_Record* RPbdb_DatabaseCursor_retrieveCurrentRecordNumber( RPbdb_DatabaseCursor* database_cursor );
	db_recno_t RPbdb_DatabaseCursor_countDuplicatesForCurrentKey( RPbdb_DatabaseCursor* database_cursor );
	void RPbdb_DatabaseCursor_resetIteration( RPbdb_DatabaseCursor* database_cursor );
void RPbdb_DatabaseCursor_resetDuplicateIteration( RPbdb_DatabaseCursor* database_cursor );
	RPbdb_Record* RPbdb_DatabaseCursor_iterate( RPbdb_DatabaseCursor* database_cursor,
																						RPbdb_Record*					record );
	RPbdb_Record* RPbdb_DatabaseCursor_iterateDuplicates( RPbdb_DatabaseCursor* database_cursor,
																											RPbdb_Record*					record );
	RPbdb_Record* RPbdb_DatabaseCursor_iterateKeys( RPbdb_DatabaseCursor* database_cursor,
																								RPbdb_Record*					record );
																								
																								
	RPbdb_Record* RPbdb_DatabaseCursor_slice( RPbdb_DatabaseCursor*	database_cursor,
																					uint32_t							length,
																					RPbdb_Record*					record );
	RPbdb_Record* RPbdb_DatabaseCursor_sliceKeys( RPbdb_DatabaseCursor*	database_cursor,
																							uint32_t							length,
																							RPbdb_Record*					record );
	RPbdb_Record* RPbdb_DatabaseCursor_sliceDuplicates( RPbdb_DatabaseCursor*	database_cursor,
																										uint32_t							length,
																										RPbdb_Record*					record );
																								
																								
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteCurrentRecord( RPbdb_DatabaseCursor*	database_cursor );
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteKey(	RPbdb_DatabaseCursor*	database_cursor,
	 														RPbdb_Key*								key	);
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteRawKey(	RPbdb_DatabaseCursor*	database_cursor,
	 															void*					key,
																uint32_t				key_size );
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteKeyDataPair(	RPbdb_DatabaseCursor*	database_cursor,
	 																	RPbdb_Key*				key,
	 																	RPbdb_Data*				data	);
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteRawKeyDataPair(	RPbdb_DatabaseCursor*	database_cursor,
	 																	void*					raw_key,
																		uint32_t				key_size,
																		void*					raw_data,
																		uint32_t				data_size	);
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteRecordNumber(	RPbdb_DatabaseCursor*	database_cursor,
	 																	db_recno_t*				record_number	);
	RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteRecord(	RPbdb_DatabaseCursor*	database_cursor,
	 															RPbdb_Record*			record	);

#endif

