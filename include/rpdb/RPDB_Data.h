/*
 *		RPDB::RPDB_DatabaseController::RPDB_Database::(RPDB_DatabaseCursorController::RPDB_DatabaseCursor::)RPDB_Record::RPDB_DBT => RPDB_Data
 *
 *
 */

#ifndef RPDB_DATA
	#define RPDB_DATA

	#include "RPDB_BaseStandardInclude.h"

/****************
*  Prototypes  *
****************/

RPDB_Data*		RPDB_Data_new(			RPDB_Record*	parent_record );

void			RPDB_Data_free(	RPDB_Data** data );
RPDB_DatabaseRecordSettingsController*	RPDB_Data_settingsController(	RPDB_Data* data );
RPDB_Environment*		RPDB_Data_parentEnvironment(	RPDB_Data* data );
RPDB_Database* RPDB_Data_parentDatabase(	RPDB_Data* data );
RPDB_Record* RPDB_Data_parentRecord(	RPDB_DatabaseRecordSettingsController* data );

void*			RPDB_Data_rawData(		RPDB_Data*		data );
void RPDB_Data_setRawData(	RPDB_Data*	data,
							void*		data_raw,
							uint32_t	data_size );
uint32_t RPDB_Data_size( RPDB_Data* data );

#endif

