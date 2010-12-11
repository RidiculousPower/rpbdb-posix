/*
 *		Rbdb::DatabaseController::Database
 *
 *
 */

#ifndef RBDB_DATABASE
	#define RBDB_DATABASE

	#include "Rbdb_BaseStandardInclude.h"

	#include <time.h>

	/****************
	*  Prototypes  *
	****************/

Rbdb_Database* Rbdb_Database_new(	Rbdb_DatabaseController*	parent_database_controller,
																	char*											database_name );

	void																								Rbdb_Database_free(	Rbdb_Database** database );
	Rbdb_DatabaseSettingsController*																	Rbdb_Database_settingsController(	Rbdb_Database* database );
	Rbdb_Environment*																					Rbdb_Database_parentEnvironment(	Rbdb_Database* database );
	Rbdb_DatabaseController* Rbdb_Database_parentDatabaseController(	Rbdb_Database* database );

	char* Rbdb_Database_filename( Rbdb_Database* database );
	char*																								Rbdb_Database_name( 									Rbdb_Database* 			database );
	void																								Rbdb_Database_rename(		Rbdb_Database* 			database,
																																							char*						name);

	BOOL																								Rbdb_Database_isOpen( Rbdb_Database* database );
	Rbdb_Database*																						Rbdb_Database_open(									Rbdb_Database*			database );
	void																								Rbdb_Database_close(									Rbdb_Database*			database );
	void																								Rbdb_Database_erase( 									Rbdb_Database*			database );
	uint32_t Rbdb_Database_empty( Rbdb_Database* database );
	void Rbdb_Database_sync( Rbdb_Database* database );
	
	void Rbdb_Database_closeAllSecondaryDatabases( Rbdb_Database* database );
	void Rbdb_Database_freeAllSecondaryDatabases( Rbdb_Database* database );
	BOOL																								Rbdb_Database_associateSecondaryDatabase(				Rbdb_Database*			database, 
																																								Rbdb_Database*			secondary_database );
	Rbdb_Record* 																						Rbdb_Database_compact(									Rbdb_Database*			database, 
																																								Rbdb_Record*			start_record, 
																																								Rbdb_Record*			stop_record );

	Rbdb_Record*																						Rbdb_Database_compactAllRecords( 						Rbdb_Database*			database );
	Rbdb_Database*																						Rbdb_Database_upgrade(									Rbdb_Database*			database );
	void																								Rbdb_Database_resetDatabaseIDs(						Rbdb_Database*			database );
	Rbdb_Database*																						Rbdb_Database_prepareDatabaseForFileTransfer(			Rbdb_Database*			database );
                                            														                                                		
	//	Controllers                         															                                                		                    	
	Rbdb_DatabaseCursorController*																		Rbdb_Database_cursorController(						Rbdb_Database*			database );
	Rbdb_DatabaseJoinController* Rbdb_Database_joinController( Rbdb_Database* database );
Rbdb_DatabaseSequenceController* Rbdb_Database_sequenceController( Rbdb_Database* database );
	Rbdb_DatabaseSettingsController*																	Rbdb_Database_settingsController(						Rbdb_Database*			database );
                                          														                                                		
	BOOL Rbdb_Database_isPrimary(	Rbdb_Database*	database );
	BOOL																								Rbdb_Database_isSecondary(								Rbdb_Database*			database );
	Rbdb_Database* Rbdb_Database_primaryDatabase( Rbdb_Database*	secondary_database );
	
	void Rbdb_Database_setSecondaryKeyCreationCallbackMethod(	Rbdb_Database*						secondary_database,
																Rbdb_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method);
	Rbdb_SecondaryKeyCallbackMethod Rbdb_Database_secondaryKeyCreationCallbackMethod(	Rbdb_Database*		secondary_database );
	Rbdb_Database* Rbdb_Database_createSecondaryIndex(	Rbdb_Database*						primary_database,
																										 char*								index_name,
																										 Rbdb_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method);
	Rbdb_Database* Rbdb_Database_databaseForSecondaryIndex(	Rbdb_Database*		primary_database,
															 char*				index_name );
	Rbdb_Database* Rbdb_Database_createSecondaryIndexWithDuplicates(	Rbdb_Database*						primary_database,
																		char*								index_name,
																		Rbdb_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method);
Rbdb_Database* Rbdb_Database_createSecondaryIndexWithSortedDuplicates(	Rbdb_Database*										primary_database,
																																				char*															index_name,
																																				Rbdb_SecondaryKeyCallbackMethod		secondary_key_creation_callback_method);
void Rbdb_Database_createSecondaryIndexWithDatabase(	Rbdb_Database*						primary_database,
													Rbdb_Database*						secondary_database,
													char*								index_name,
													Rbdb_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method);
	Rbdb_DatabaseCursor* Rbdb_Database_cursor( Rbdb_Database* database );
	BOOL										Rbdb_Database_keyExists(										Rbdb_Database*	database,
																						Rbdb_Key*						key_data );
	BOOL Rbdb_Database_rawKeyExists(	Rbdb_Database*	database,
													   void*				raw_key,
													   uint32_t					key_size );
	Rbdb_Record* Rbdb_Database_retrieveRecord(	Rbdb_Database*	database, 
																  Rbdb_Record*						record );
		Rbdb_Record*								Rbdb_Database_retrieveKey(							Rbdb_Database*	database, 
																																	Rbdb_Key*						key_data );
	Rbdb_Record* Rbdb_Database_retrieveRawKey(	Rbdb_Database*		database, 
																		   void*									raw_key,
																		   uint32_t								key_size );
		Rbdb_Record*								Rbdb_Database_retrieveMatchingKeyDataPair(		Rbdb_Database*	database, 
																																	Rbdb_Key*						key_data,
																																	Rbdb_Data*							data );
	Rbdb_Record* Rbdb_Database_retrieveMatchingRecord(	Rbdb_Database*		database, 
																											Rbdb_Record*			record );
	Rbdb_Record* Rbdb_Database_retrieveMatchingRawKeyDataPair(	Rbdb_Database*		database,
																						   void*									raw_key,
																						   uint32_t								key_size,
																						   void*									raw_data,
																						   uint32_t								data_size );
		Rbdb_Record*								Rbdb_Database_retrieveRawRecordID(					Rbdb_Database*	database,
																																	db_recno_t*							record_id );
		Rbdb_Record*								Rbdb_Database_retrieveRecordID(						Rbdb_Database*	database,
																																	Rbdb_Key*						key_data_record_id );
		Rbdb_Record*								Rbdb_Database_retrievePartialRawKey(				Rbdb_Database*	database,
																																	void*								raw_key );
		Rbdb_Record*								Rbdb_Database_retrievePartialKey(					Rbdb_Database*	database,
																																	Rbdb_Key*							partial_key );
		Rbdb_Record*								Rbdb_Database_retrievePartialData(				Rbdb_Database*	database,
																																	Rbdb_Data*							data );
		Rbdb_Record*								Rbdb_Database_retrieveRawKeyPartialObjectPair(		Rbdb_Database*	database,
																																	void*								raw_key,
																																	void*								raw_data );
/*
		Rbdb_KeyRange*								Rbdb_Database_relativePositionOfKey(							Rbdb_Database*	database,
																																	Rbdb_Key*							key_data );
		Rbdb_KeyRange*								Rbdb_Database_relativePositionOfRawKey(						Rbdb_Database*	database,
																																	void*								raw_key );
*/
		Rbdb_Record*								Rbdb_Database_shiftQueue(									Rbdb_Database*	database, Rbdb_Record* record );
		Rbdb_Record*								Rbdb_Database_shiftQueueOrWait(								Rbdb_Database*	database, Rbdb_Record* record );
	//	Rbdb_DatabaseRecordReadWriteSettingsController*	Rbdb_Database_settingsController(							Rbdb_Database* 	database );
	
	void									Rbdb_Database_write(			Rbdb_Database*		database, 
																								Rbdb_Record*						write_record );
	void									Rbdb_Database_writeKeyDataPair(		Rbdb_Database*		database, 
																								Rbdb_Key*							write_key, 
																								Rbdb_Data*							write_data );
	Rbdb_Record* Rbdb_Database_writeRawKeyDataPair(	Rbdb_Database*	database, 
													   void*							write_key, 
													   uint32_t						key_size,
													   void*							write_data,
													   uint32_t						data_size	 );

void Rbdb_Database_appendRawKeyDataPair(	Rbdb_Database*			database, 
																					void*								primary_key,
																					uint32_t						key_size,
																					void*								write_data,
																					uint32_t						data_size );
db_recno_t Rbdb_Database_appendRawData(	Rbdb_Database*			database, 
																				void*								write_data,
																				uint32_t						data_size );
db_recno_t Rbdb_Database_appendData(	Rbdb_Database*			database, 
																			Rbdb_Data*					write_data );
void Rbdb_Database_appendKeyDataPair(	Rbdb_Database*			database, 
																			Rbdb_Key*						primary_key,
																			Rbdb_Data*					write_data );
void Rbdb_Database_appendRecord(	Rbdb_Database*			database, 
																	Rbdb_Record*				record );

	//	Rbdb_DatabaseRecordReadWriteSettingsController*	Rbdb_Database_settingsController(	Rbdb_Database* 		database );

	void										Rbdb_Database_free(	Rbdb_Database** database );
	Rbdb_DatabaseSettingsController*		Rbdb_Database_settingsController(	Rbdb_Database* database );
	Rbdb_Environment*					Rbdb_Database_parentEnvironment(	Rbdb_Database* database );

	Rbdb_Database* Rbdb_Database_deleteRecord(	Rbdb_Database* 	database,
											Rbdb_Record*		record );
	Rbdb_Database*								Rbdb_Database_deleteDataForKey(	Rbdb_Database* 	database,
																									Rbdb_Key*							deletion_key );
	Rbdb_Database* Rbdb_Database_deleteDataForRawKey(	Rbdb_Database* 	database,
																				   void*								raw_deletion_key,
																				   uint32_t							key_size );
	//	Rbdb_DatabaseRecordReadWriteSettingsController*		Rbdb_Database_settingsController(	Rbdb_Database* 	database );
	Rbdb_Database* Rbdb_Database_verify( Rbdb_Database* database );

#endif

