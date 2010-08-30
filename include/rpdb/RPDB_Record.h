/*
 *		RPDB::RPDB_DatabaseController::RPDB_Database::(RPDB_DatabaseCursorController::RPDB_DatabaseCursor::)RPDB_Record
 *
 *
 */

#ifndef RPDB_RECORD
	#define RPDB_RECORD

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_Record*						RPDB_Record_new(					RPDB_Database*		parent_database );

	void								RPDB_Record_free(							RPDB_Record** record );
	RPDB_DatabaseRecordSettingsController*		RPDB_Record_settingsController(	RPDB_Record* record );
	RPDB_Environment*			RPDB_Record_parentEnvironment(	RPDB_Record* record );
	RPDB_Database* RPDB_Record_parentDatabase(	RPDB_Record* record );

	RPDB_DBT*							RPDB_Record_key(					RPDB_Record*		record );
	void								RPDB_Record_setKey(				RPDB_Record*		record,
																			RPDB_Key*			key );
	void RPDB_Record_setKeyFromRawKey(	RPDB_Record*		record,
											void*				key_raw,
											uint32_t			key_size );
	void								RPDB_Record_setData(				RPDB_Record*			record,
										   					   				RPDB_Data*				object );
	void RPDB_Record_setDataFromRawData(	RPDB_Record*		record,
											void*				data_raw,
											uint32_t			data_size );
	RPDB_Data*							RPDB_Record_data(				RPDB_Record*		record );		
void* RPDB_Record_rawData( RPDB_Record* record );	
void RPDB_Record_setRawData(	RPDB_Record*	record,
							 void*			raw_data,
							 u_int32_t		raw_data_size );
void* RPDB_Record_rawKey( RPDB_Record* record );
void RPDB_Record_setRawKey(	RPDB_Record*	record,
							void*			raw_key,
							u_int32_t		raw_key_size );
	uint32_t RPDB_Record_keySize( RPDB_Record* record );
	uint32_t RPDB_Record_dataSize( RPDB_Record* record );
	RPDB_Key*							RPDB_Record_primaryKey(			RPDB_Record*		record );
	RPDB_Key*					RPDB_Record_retrievalKey(			RPDB_Record*		record );
	void RPDB_Record_setExistsInDatabase(	RPDB_Record*	record,
											BOOL			data_status	);
	int RPDB_Record_existsInDatabase( RPDB_Record* record );
	void RPDB_Record_setRequiresUpdateToDatabase(	RPDB_Record*	record,
													BOOL			data_status	);
	int RPDB_Record_requiresUpdateToDatabase( RPDB_Record* record );
	RPDB_DatabaseRecordSettingsController*		RPDB_Record_settingsController(	RPDB_Record*		record );
		
		
#endif

