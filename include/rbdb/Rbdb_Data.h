/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record::Rbdb_DBT => Rbdb_Data
 *
 *
 */

#ifndef Rbdb_DATA
	#define Rbdb_DATA

	#include "Rbdb_BaseStandardInclude.h"

/****************
*  Prototypes  *
****************/

Rbdb_Data*		Rbdb_Data_new(			Rbdb_Record*	parent_record );

void			Rbdb_Data_free(	Rbdb_Data** data );
Rbdb_DatabaseRecordSettingsController*	Rbdb_Data_settingsController(	Rbdb_Data* data );
Rbdb_Environment*		Rbdb_Data_parentEnvironment(	Rbdb_Data* data );
Rbdb_Database* Rbdb_Data_parentDatabase(	Rbdb_Data* data );
Rbdb_Record* Rbdb_Data_parentRecord(	Rbdb_DatabaseRecordSettingsController* data );

void*			Rbdb_Data_rawData(		Rbdb_Data*		data );
void Rbdb_Data_setRawData(	Rbdb_Data*	data,
							void*		data_raw,
							uint32_t	data_size );
uint32_t Rbdb_Data_size( Rbdb_Data* data );

#endif

