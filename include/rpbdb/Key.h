/*
 *		RPbdb::RPbdb_DatabaseController::RPbdb_Database::(RPbdb_DatabaseCursorController::RPbdb_DatabaseCursor::)RPbdb_Record::RPBDB_DBT => RPbdb_Key
 *
 *
 */

#ifndef RPBDB_KEY
	#define RPBDB_KEY

	#include <cerialize.h>

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
	
	RPbdb_Key*						RPbdb_Key_new(			RPbdb_Record*	parent_record );

	void							RPbdb_Key_free(	RPbdb_Key** key );
	RPbdb_DatabaseRecordSettingsController*	RPbdb_Key_settingsController(	RPbdb_Key* key );
	RPbdb_Environment*		RPbdb_Key_parentEnvironment(	RPbdb_Key* key );
	RPbdb_Database* RPbdb_Key_parentDatabase(	RPbdb_Key* dbt );
	RPbdb_Record* RPbdb_Key_parentRecord(	RPbdb_DatabaseRecordSettingsController* key );

	void*							RPbdb_Key_rawData(		RPbdb_Key*		key );
	void RPbdb_Key_setRawData(	RPbdb_Key*	key,
								void*		key_raw,
								uint32_t	key_size );
	uint32_t RPbdb_Key_size( RPbdb_Key* data );

CerializeType RPbdb_Key_type( RPbdb_Key* key );
void RPbdb_Key_setType(	RPbdb_Key*												key,
												CerializeType	type );

#endif

