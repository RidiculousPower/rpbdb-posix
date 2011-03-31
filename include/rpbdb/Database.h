/*
 *		RPbdb::DatabaseController::Database
 *
 *
 */

#ifndef RPBDB_DATABASE
	#define RPBDB_DATABASE

	#include "BaseStandardInclude.h"

	#include <time.h>

	/****************
	*  Prototypes  *
	****************/

RPbdb_Database* RPbdb_Database_new(	RPbdb_DatabaseController*	parent_database_controller,
																	char*											database_name );

	void																								RPbdb_Database_free(	RPbdb_Database** database );
	RPbdb_DatabaseSettingsController*																	RPbdb_Database_settingsController(	RPbdb_Database* database );
	RPbdb_Environment*																					RPbdb_Database_parentEnvironment(	RPbdb_Database* database );
	RPbdb_DatabaseController* RPbdb_Database_parentDatabaseController(	RPbdb_Database* database );

	char* RPbdb_Database_filename( RPbdb_Database* database );
	char*																								RPbdb_Database_name( 									RPbdb_Database* 			database );
	void																								RPbdb_Database_rename(		RPbdb_Database* 			database,
																																							char*						name);

	BOOL																								RPbdb_Database_isOpen( RPbdb_Database* database );
	RPbdb_Database*																						RPbdb_Database_open(									RPbdb_Database*			database );
	void																								RPbdb_Database_close(									RPbdb_Database*			database );
	void																								RPbdb_Database_erase( 									RPbdb_Database*			database );
	uint32_t RPbdb_Database_empty( RPbdb_Database* database );
	void RPbdb_Database_sync( RPbdb_Database* database );
	
	void RPbdb_Database_closeAllSecondaryDatabases( RPbdb_Database* database );
	void RPbdb_Database_freeAllSecondaryDatabases( RPbdb_Database* database );
	BOOL																								RPbdb_Database_associateSecondaryDatabase(				RPbdb_Database*			database, 
																																								RPbdb_Database*			secondary_database );
	RPbdb_Record* 																						RPbdb_Database_compact(									RPbdb_Database*			database, 
																																								RPbdb_Record*			start_record, 
																																								RPbdb_Record*			stop_record );

	RPbdb_Record*																						RPbdb_Database_compactAllRecords( 						RPbdb_Database*			database );
	RPbdb_Database*																						RPbdb_Database_upgrade(									RPbdb_Database*			database );
	void																								RPbdb_Database_resetDatabaseIDs(						RPbdb_Database*			database );
	RPbdb_Database*																						RPbdb_Database_prepareDatabaseForFileTransfer(			RPbdb_Database*			database );
                                            														                                                		
	//	Controllers                         															                                                		                    	
	RPbdb_DatabaseCursorController*																		RPbdb_Database_cursorController(						RPbdb_Database*			database );
	RPbdb_DatabaseJoinController* RPbdb_Database_joinController( RPbdb_Database* database );
RPbdb_DatabaseSequenceController* RPbdb_Database_sequenceController( RPbdb_Database* database );
	RPbdb_DatabaseSettingsController*																	RPbdb_Database_settingsController(						RPbdb_Database*			database );
                                          														                                                		
	BOOL RPbdb_Database_isPrimary(	RPbdb_Database*	database );
	BOOL																								RPbdb_Database_isSecondary(								RPbdb_Database*			database );
	RPbdb_Database* RPbdb_Database_primaryDatabase( RPbdb_Database*	secondary_database );
	char* RPbdb_Database_secondaryIndexName( RPbdb_Database*	database );
	
	void RPbdb_Database_setSecondaryKeyCreationCallbackMethod(	RPbdb_Database*						secondary_database,
																RPbdb_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method);
	RPbdb_SecondaryKeyCallbackMethod RPbdb_Database_secondaryKeyCreationCallbackMethod(	RPbdb_Database*		secondary_database );
	RPbdb_Database* RPbdb_Database_createSecondaryIndex(	RPbdb_Database*						primary_database,
																										 char*								index_name,
																										 RPbdb_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method);
	RPbdb_Database* RPbdb_Database_databaseForSecondaryIndex(	RPbdb_Database*		primary_database,
															 char*				index_name );
	RPbdb_Database* RPbdb_Database_createSecondaryIndexWithDuplicates(	RPbdb_Database*						primary_database,
																		char*								index_name,
																		RPbdb_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method);
RPbdb_Database* RPbdb_Database_createSecondaryIndexWithSortedDuplicates(	RPbdb_Database*										primary_database,
																																				char*															index_name,
																																				RPbdb_SecondaryKeyCallbackMethod		secondary_key_creation_callback_method);
void RPbdb_Database_createSecondaryIndexWithDatabase(	RPbdb_Database*						primary_database,
													RPbdb_Database*						secondary_database,
													char*								index_name,
													RPbdb_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method);
	RPbdb_DatabaseCursor* RPbdb_Database_cursor( RPbdb_Database* database );
	BOOL										RPbdb_Database_keyExists(										RPbdb_Database*	database,
																						RPbdb_Key*						key_data );
	BOOL RPbdb_Database_rawKeyExists(	RPbdb_Database*	database,
													   void*				raw_key,
													   uint32_t					key_size );
	RPbdb_Record* RPbdb_Database_retrieveRecord(	RPbdb_Database*	database, 
																  RPbdb_Record*						record );
		RPbdb_Record*								RPbdb_Database_retrieveKey(							RPbdb_Database*	database, 
																																	RPbdb_Key*						key_data );
	RPbdb_Record* RPbdb_Database_retrieveRawKey(	RPbdb_Database*		database, 
																		   void*									raw_key,
																		   uint32_t								key_size );
		RPbdb_Record*								RPbdb_Database_retrieveMatchingKeyDataPair(		RPbdb_Database*	database, 
																																	RPbdb_Key*						key_data,
																																	RPbdb_Data*							data );
	RPbdb_Record* RPbdb_Database_retrieveMatchingRecord(	RPbdb_Database*		database, 
																											RPbdb_Record*			record );
	RPbdb_Record* RPbdb_Database_retrieveMatchingRawKeyDataPair(	RPbdb_Database*		database,
																						   void*									raw_key,
																						   uint32_t								key_size,
																						   void*									raw_data,
																						   uint32_t								data_size );
		RPbdb_Record*								RPbdb_Database_retrieveRawRecordID(					RPbdb_Database*	database,
																																	db_recno_t*							record_id );
		RPbdb_Record*								RPbdb_Database_retrieveRecordID(						RPbdb_Database*	database,
																																	RPbdb_Key*						key_data_record_id );
		RPbdb_Record*								RPbdb_Database_retrievePartialRawKey(				RPbdb_Database*	database,
																																	void*								raw_key );
		RPbdb_Record*								RPbdb_Database_retrievePartialKey(					RPbdb_Database*	database,
																																	RPbdb_Key*							partial_key );
		RPbdb_Record*								RPbdb_Database_retrievePartialData(				RPbdb_Database*	database,
																																	RPbdb_Data*							data );
		RPbdb_Record*								RPbdb_Database_retrieveRawKeyPartialObjectPair(		RPbdb_Database*	database,
																																	void*								raw_key,
																																	void*								raw_data );
/*
		RPbdb_KeyRange*								RPbdb_Database_relativePositionOfKey(							RPbdb_Database*	database,
																																	RPbdb_Key*							key_data );
		RPbdb_KeyRange*								RPbdb_Database_relativePositionOfRawKey(						RPbdb_Database*	database,
																																	void*								raw_key );
*/
		RPbdb_Record*								RPbdb_Database_shiftQueue(									RPbdb_Database*	database, RPbdb_Record* record );
		RPbdb_Record*								RPbdb_Database_shiftQueueOrWait(								RPbdb_Database*	database, RPbdb_Record* record );
	//	RPbdb_DatabaseRecordReadWriteSettingsController*	RPbdb_Database_settingsController(							RPbdb_Database* 	database );
	
	void									RPbdb_Database_write(			RPbdb_Database*		database, 
																								RPbdb_Record*						write_record );
	void									RPbdb_Database_writeKeyDataPair(		RPbdb_Database*		database, 
																								RPbdb_Key*							write_key, 
																								RPbdb_Data*							write_data );
	RPbdb_Record* RPbdb_Database_writeRawKeyDataPair(	RPbdb_Database*	database, 
													   void*							write_key, 
													   uint32_t						key_size,
													   void*							write_data,
													   uint32_t						data_size	 );

void RPbdb_Database_appendRawKeyDataPair(	RPbdb_Database*			database, 
																					void*								primary_key,
																					uint32_t						key_size,
																					void*								write_data,
																					uint32_t						data_size );
db_recno_t RPbdb_Database_appendRawData(	RPbdb_Database*			database, 
																				void*								write_data,
																				uint32_t						data_size );
db_recno_t RPbdb_Database_appendData(	RPbdb_Database*			database, 
																			RPbdb_Data*					write_data );
db_recno_t RPbdb_Database_appendKeyDataPair(	RPbdb_Database*			database, 
																			RPbdb_Key*						primary_key,
																			RPbdb_Data*					write_data );
db_recno_t RPbdb_Database_appendRecord(	RPbdb_Database*			database, 
																	RPbdb_Record*				record );

	//	RPbdb_DatabaseRecordReadWriteSettingsController*	RPbdb_Database_settingsController(	RPbdb_Database* 		database );

	void										RPbdb_Database_free(	RPbdb_Database** database );
	RPbdb_DatabaseSettingsController*		RPbdb_Database_settingsController(	RPbdb_Database* database );
	RPbdb_Environment*					RPbdb_Database_parentEnvironment(	RPbdb_Database* database );

	RPbdb_Database* RPbdb_Database_deleteRecord(	RPbdb_Database* 	database,
											RPbdb_Record*		record );
	RPbdb_Database*								RPbdb_Database_deleteDataForKey(	RPbdb_Database* 	database,
																									RPbdb_Key*							deletion_key );
	RPbdb_Database* RPbdb_Database_deleteDataForRawKey(	RPbdb_Database* 	database,
																				   void*								raw_deletion_key,
																				   uint32_t							key_size );
	//	RPbdb_DatabaseRecordReadWriteSettingsController*		RPbdb_Database_settingsController(	RPbdb_Database* 	database );
	RPbdb_Database* RPbdb_Database_verify( RPbdb_Database* database );

#endif

