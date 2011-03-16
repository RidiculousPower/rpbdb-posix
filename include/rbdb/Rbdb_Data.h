/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record::RBDB_DBT => Rbdb_Data
 *
 *
 */

#ifndef RBDB_DATA
	#define RBDB_DATA

	#include <cerialize.h>

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

void* Rbdb_Data_rawData( Rbdb_Data* data );
void Rbdb_Data_setRawData(	Rbdb_Data*	data,
														void*		data_raw,
														uint32_t	data_size );
uint32_t Rbdb_Data_size( Rbdb_Data* data );
CerializeType Rbdb_Data_type( Rbdb_Data* data );
void Rbdb_Data_setType(	Rbdb_Data*											data,
												CerializeType	type );

struct timeval* Rbdb_Data_creationStamp( Rbdb_Data* data );
struct timeval* Rbdb_Data_modificationStamp( Rbdb_Data* data );

#endif

