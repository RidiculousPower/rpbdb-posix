/*
 *		RPDB::RPDB_DatabaseController::RPDB_Database::(RPDB_DatabaseCursorController::RPDB_DatabaseCursor::)RPDB_Record::RPDB_DBT => RPDB_Key
 *
 *
 */

#ifndef RPDB_KEY
	#define RPDB_KEY

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
	
	RPDB_Key*						RPDB_Key_new(			RPDB_Record*	parent_record );

	void							RPDB_Key_free(	RPDB_Key** key );
	RPDB_DatabaseRecordSettingsController*	RPDB_Key_settingsController(	RPDB_Key* key );
	RPDB_Environment*		RPDB_Key_parentEnvironment(	RPDB_Key* key );
	RPDB_Database* RPDB_Key_parentDatabase(	RPDB_Key* dbt );
	RPDB_Record* RPDB_Key_parentRecord(	RPDB_DatabaseRecordSettingsController* key );

	void*							RPDB_Key_keyData(		RPDB_Key*		key );
	void RPDB_Key_setKeyData(	RPDB_Key*	key,
								void*		key_raw,
								uint32_t	key_size );

#endif

