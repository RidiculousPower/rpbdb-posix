/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record
 *
 *
 */

#ifndef RBDB_RECORD
	#define RBDB_RECORD

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_Record*						Rbdb_Record_new(					Rbdb_Database*		parent_database );

	void								Rbdb_Record_free(							Rbdb_Record** record );
	Rbdb_DatabaseRecordSettingsController*		Rbdb_Record_settingsController(	Rbdb_Record* record );
	Rbdb_Environment*			Rbdb_Record_parentEnvironment(	Rbdb_Record* record );
	Rbdb_Database* Rbdb_Record_parentDatabase(	Rbdb_Record* record );

	Rbdb_DBT*						Rbdb_Record_key(					Rbdb_Record*		record );
	void								Rbdb_Record_setKey(				Rbdb_Record*		record,
																								Rbdb_Key*			key );
	void								Rbdb_Record_setData(				Rbdb_Record*			record,
										   					   				Rbdb_Data*				object );
	Rbdb_Data*							Rbdb_Record_data(				Rbdb_Record*		record );		
void* Rbdb_Record_rawData( Rbdb_Record* record );	
void Rbdb_Record_setRawData(	Rbdb_Record*	record,
							 void*			raw_data,
							 u_int32_t		raw_data_size );
void* Rbdb_Record_rawKey( Rbdb_Record* record );
void Rbdb_Record_setRawKey(	Rbdb_Record*	record,
							void*			raw_key,
							u_int32_t		raw_key_size );
	uint32_t Rbdb_Record_keySize( Rbdb_Record* record );
	uint32_t Rbdb_Record_dataSize( Rbdb_Record* record );
	void* Rbdb_Record_rawPrimaryKey( Rbdb_Record* record );
	uint32_t Rbdb_Record_primaryKeySize( Rbdb_Record* record );
	Rbdb_Key*							Rbdb_Record_primaryKey(			Rbdb_Record*		record );
	Rbdb_Key*					Rbdb_Record_retrievalKey(			Rbdb_Record*		record );

	void Rbdb_Record_setExistsInDatabase(	Rbdb_Record*	record,
											BOOL			data_status	);
	int Rbdb_Record_existsInDatabase( Rbdb_Record* record );
	void Rbdb_Record_setRequiresUpdateToDatabase(	Rbdb_Record*	record,
													BOOL			data_status	);
	int Rbdb_Record_requiresUpdateToDatabase( Rbdb_Record* record );
	Rbdb_DatabaseRecordSettingsController*		Rbdb_Record_settingsController(	Rbdb_Record*		record );
		
		
#endif

