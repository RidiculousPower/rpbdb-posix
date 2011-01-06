/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record::RBDB_DBT => Rbdb_Key
 *
 *
 */

#ifndef RBDB_KEY
	#define RBDB_KEY

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
	
	Rbdb_Key*						Rbdb_Key_new(			Rbdb_Record*	parent_record );

	void							Rbdb_Key_free(	Rbdb_Key** key );
	Rbdb_DatabaseRecordSettingsController*	Rbdb_Key_settingsController(	Rbdb_Key* key );
	Rbdb_Environment*		Rbdb_Key_parentEnvironment(	Rbdb_Key* key );
	Rbdb_Database* Rbdb_Key_parentDatabase(	Rbdb_Key* dbt );
	Rbdb_Record* Rbdb_Key_parentRecord(	Rbdb_DatabaseRecordSettingsController* key );

	void*							Rbdb_Key_rawData(		Rbdb_Key*		key );
	void Rbdb_Key_setRawData(	Rbdb_Key*	key,
								void*		key_raw,
								uint32_t	key_size );
	uint32_t Rbdb_Key_size( Rbdb_Key* data );

Rbdb_DatabaseRecordStorageType Rbdb_Key_type( Rbdb_Key* key );
void Rbdb_Key_setType(	Rbdb_Key*												key,
												Rbdb_DatabaseRecordStorageType	type );

#endif

