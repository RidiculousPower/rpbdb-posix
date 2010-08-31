/*
 *		RPDB::DatabaseController::Database
 *
 *
 */

#ifndef RPDB_DATABASE
	#define RPDB_DATABASE

	#include "RPDB_BaseStandardInclude.h"

	#include <time.h>

	/****************
	*  Prototypes  *
	****************/

RPDB_Database* RPDB_Database_new(	RPDB_DatabaseController*	parent_database_controller,
																	char*											database_name );

	void																								RPDB_Database_free(	RPDB_Database** database );
	RPDB_DatabaseSettingsController*																	RPDB_Database_settingsController(	RPDB_Database* database );
	RPDB_Environment*																					RPDB_Database_parentEnvironment(	RPDB_Database* database );
	RPDB_DatabaseController* RPDB_Database_parentDatabaseController(	RPDB_Database* database );

	char* RPDB_Database_filename( RPDB_Database* database );
	char*																								RPDB_Database_name( 									RPDB_Database* 			database );
	void																								RPDB_Database_rename(		RPDB_Database* 			database,
																																							char*						name);

	BOOL																								RPDB_Database_isOpen( RPDB_Database* database );
	RPDB_Database*																						RPDB_Database_open(									RPDB_Database*			database );
	void																								RPDB_Database_close(									RPDB_Database*			database );
	void																								RPDB_Database_erase( 									RPDB_Database*			database );
	void RPDB_Database_empty( RPDB_Database* database );
	void RPDB_Database_sync( RPDB_Database* database );
	
	void RPDB_Database_closeAllSecondaryDatabases( RPDB_Database* database );
void RPDB_Database_freeAllSecondaryDatabases( RPDB_Database* database );
	BOOL																								RPDB_Database_associateSecondaryDatabase(				RPDB_Database*			database, 
																																								RPDB_Database*			secondary_database );
	RPDB_Record* 																						RPDB_Database_compact(									RPDB_Database*			database, 
																																								RPDB_Record*			start_record, 
																																								RPDB_Record*			stop_record );

	RPDB_Record*																						RPDB_Database_compactAllRecords( 						RPDB_Database*			database );
	RPDB_Database*																						RPDB_Database_upgrade(									RPDB_Database*			database );
	void																								RPDB_Database_resetDatabaseIDs(						RPDB_Database*			database );
	RPDB_Database*																						RPDB_Database_prepareDatabaseForFileTransfer(			RPDB_Database*			database );
                                            														                                                		
	//	Controllers                         															                                                		                    	
	RPDB_DatabaseCursorController*																		RPDB_Database_cursorController(						RPDB_Database*			database );
RPDB_DatabaseJoinController* RPDB_Database_joinController( RPDB_Database* database );
	RPDB_DatabaseSettingsController*																	RPDB_Database_settingsController(						RPDB_Database*			database );
                                          														                                                		
BOOL RPDB_Database_isPrimary(	RPDB_Database*	database );
	BOOL																								RPDB_Database_isSecondary(								RPDB_Database*			database );
	
	void RPDB_Database_setSecondaryKeyCreationCallbackMethod(	RPDB_Database*						secondary_database,
																RPDB_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method);
	RPDB_SecondaryKeyCallbackMethod RPDB_Database_secondaryKeyCreationCallbackMethod(	RPDB_Database*		secondary_database );
RPDB_Database* RPDB_Database_createSecondaryIndex(	RPDB_Database*						primary_database,
										 char*								index_name,
										 RPDB_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method);
RPDB_Database* RPDB_Database_databaseForSecondaryIndex(	RPDB_Database*		primary_database,
														 char*				index_name );
RPDB_Database* RPDB_Database_createSecondaryIndexWithDuplicates(	RPDB_Database*						primary_database,
																	char*								index_name,
																	RPDB_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method);
void RPDB_Database_createSecondaryIndexWithDatabase(	RPDB_Database*						primary_database,
													RPDB_Database*						secondary_database,
													char*								index_name,
													RPDB_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method);
	RPDB_DatabaseCursor* RPDB_Database_cursor( RPDB_Database* database );
	BOOL										RPDB_Database_keyExists(										RPDB_Database*	database,
																						RPDB_Key*						key_data );
	BOOL RPDB_Database_rawKeyExists(	RPDB_Database*	database,
													   void*				raw_key,
													   uint32_t					key_size );
	RPDB_Record* RPDB_Database_retrieveRecord(	RPDB_Database*	database, 
																  RPDB_Record*						record );
		RPDB_Record*								RPDB_Database_retrieveKey(							RPDB_Database*	database, 
																																	RPDB_Key*						key_data );
	RPDB_Record* RPDB_Database_retrieveRawKey(	RPDB_Database*		database, 
																		   void*									raw_key,
																		   uint32_t								key_size );
		RPDB_Record*								RPDB_Database_retrieveMatchingKeyDataPair(		RPDB_Database*	database, 
																																	RPDB_Key*						key_data,
																																	RPDB_Data*							data );
	RPDB_Record* RPDB_Database_retrieveMatchingRawKeyDataPair(	RPDB_Database*		database,
																						   void*									raw_key,
																						   uint32_t								key_size,
																						   void*									raw_data,
																						   uint32_t								data_size );
		RPDB_Record*								RPDB_Database_retrieveRawRecordID(					RPDB_Database*	database,
																																	db_recno_t*							record_id );
		RPDB_Record*								RPDB_Database_retrieveRecordID(						RPDB_Database*	database,
																																	RPDB_Key*						key_data_record_id );
		RPDB_Record*								RPDB_Database_retrievePartialRawKey(				RPDB_Database*	database,
																																	void*								raw_key );
		RPDB_Record*								RPDB_Database_retrievePartialKey(					RPDB_Database*	database,
																																	RPDB_Key*							partial_key );
		RPDB_Record*								RPDB_Database_retrievePartialData(				RPDB_Database*	database,
																																	RPDB_Data*							data );
		RPDB_Record*								RPDB_Database_retrieveRawKeyPartialObjectPair(		RPDB_Database*	database,
																																	void*								raw_key,
																																	void*								raw_data );
/*
		RPDB_KeyRange*								RPDB_Database_relativePositionOfKey(							RPDB_Database*	database,
																																	RPDB_Key*							key_data );
		RPDB_KeyRange*								RPDB_Database_relativePositionOfRawKey(						RPDB_Database*	database,
																																	void*								raw_key );
*/
		RPDB_Record*								RPDB_Database_shiftQueue(									RPDB_Database*	database );
		RPDB_Record*								RPDB_Database_shiftQueueOrWait(								RPDB_Database*	database );
	//	RPDB_DatabaseReadWriteSettingsController*	RPDB_Database_settingsController(							RPDB_Database* 	database );
	
	void									RPDB_Database_write(			RPDB_Database*		database, 
																								RPDB_Record*						write_record );
	void									RPDB_Database_writeKeyDataPair(		RPDB_Database*		database, 
																								RPDB_Key*							write_key, 
																								RPDB_Data*							write_data );
	RPDB_Record* RPDB_Database_writeRawKeyDataPair(	RPDB_Database*	database, 
													   void*							write_key, 
													   uint32_t						key_size,
													   void*							write_data,
													   uint32_t						data_size	 );

void RPDB_Database_appendRawKeyDataPair(	RPDB_Database*			database, 
																					void*								primary_key,
																					uint32_t						key_size,
																					void*								write_data,
																					uint32_t						data_size );
void RPDB_Database_appendRawData(	RPDB_Database*			database, 
																	void*								write_data,
																	uint32_t						data_size );
void RPDB_Database_appendData(	RPDB_Database*			database, 
																RPDB_Data*					write_data );
void RPDB_Database_appendKeyDataPair(	RPDB_Database*			database, 
																			RPDB_Key*						primary_key,
																			RPDB_Data*					write_data );
void RPDB_Database_appendRecord(	RPDB_Database*			database, 
																	RPDB_Record*				record );

	//	RPDB_DatabaseReadWriteSettingsController*	RPDB_Database_settingsController(	RPDB_Database* 		database );

	void										RPDB_Database_free(	RPDB_Database** database );
	RPDB_DatabaseSettingsController*		RPDB_Database_settingsController(	RPDB_Database* database );
	RPDB_Environment*					RPDB_Database_parentEnvironment(	RPDB_Database* database );

	RPDB_Database* RPDB_Database_deleteRecord(	RPDB_Database* 	database,
											RPDB_Record*		record );
	RPDB_Database*								RPDB_Database_deleteDataForKey(	RPDB_Database* 	database,
																									RPDB_Key*							deletion_key );
	RPDB_Database* RPDB_Database_deleteDataForRawKey(	RPDB_Database* 	database,
																				   void*								raw_deletion_key,
																				   uint32_t							key_size );
	//	RPDB_DatabaseReadWriteSettingsController*		RPDB_Database_settingsController(	RPDB_Database* 	database );
	
#endif

