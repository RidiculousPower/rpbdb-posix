/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record::RBDB_DBT => Rbdb_Key
 *
 *
 */

#ifndef RBDB_KEY_INTERNAL
	#define RBDB_KEY_INTERNAL

	void Rbdb_Key_internal_appendType( Rbdb_Key* key );
	Rbdb_DatabaseRecordStorageType Rbdb_Key_internal_keyType( Rbdb_Key* record );
	void Rbdb_Key_internal_addKeyTypeToExistingRecord( Rbdb_Key* key __attribute__ ((unused)) );

#endif

