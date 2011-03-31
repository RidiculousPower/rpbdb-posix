/*
 *		RPbdb::RPbdb_DatabaseController::RPbdb_Database::(RPbdb_DatabaseCursorController::RPbdb_DatabaseCursor::)RPbdb_Record
 *
 *
 */

#ifndef RPBDB_RECORD
	#define RPBDB_RECORD

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_Record*						RPbdb_Record_new(					RPbdb_Database*		parent_database );

	void								RPbdb_Record_free(							RPbdb_Record** record );
	RPbdb_DatabaseRecordSettingsController*		RPbdb_Record_settingsController(	RPbdb_Record* record );
	RPbdb_Environment*			RPbdb_Record_parentEnvironment(	RPbdb_Record* record );
	RPbdb_Database* RPbdb_Record_parentDatabase(	RPbdb_Record* record );

	RPbdb_DBT*						RPbdb_Record_key(					RPbdb_Record*		record );
	void								RPbdb_Record_setKey(				RPbdb_Record*		record,
																								RPbdb_Key*			key );
	void								RPbdb_Record_setData(				RPbdb_Record*			record,
										   					   				RPbdb_Data*				object );
	RPbdb_Data*							RPbdb_Record_data(				RPbdb_Record*		record );		
void* RPbdb_Record_rawData( RPbdb_Record* record );	
void RPbdb_Record_setRawData(	RPbdb_Record*	record,
							 void*			raw_data,
							 u_int32_t		raw_data_size );
void* RPbdb_Record_rawKey( RPbdb_Record* record );
void RPbdb_Record_setRawKey(	RPbdb_Record*	record,
							void*			raw_key,
							u_int32_t		raw_key_size );
	uint32_t RPbdb_Record_keySize( RPbdb_Record* record );
	uint32_t RPbdb_Record_dataSize( RPbdb_Record* record );
	void* RPbdb_Record_rawPrimaryKey( RPbdb_Record* record );
	uint32_t RPbdb_Record_primaryKeySize( RPbdb_Record* record );
	RPbdb_Key*							RPbdb_Record_primaryKey(			RPbdb_Record*		record );
	RPbdb_Key*					RPbdb_Record_retrievalKey(			RPbdb_Record*		record );

	void RPbdb_Record_setExistsInDatabase(	RPbdb_Record*	record,
											BOOL			data_status	);
	int RPbdb_Record_existsInDatabase( RPbdb_Record* record );
	void RPbdb_Record_setRequiresUpdateToDatabase(	RPbdb_Record*	record,
													BOOL			data_status	);
	int RPbdb_Record_requiresUpdateToDatabase( RPbdb_Record* record );
	RPbdb_DatabaseRecordSettingsController*		RPbdb_Record_settingsController(	RPbdb_Record*		record );
		
		
#endif

