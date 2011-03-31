/*
 *		RPbdb::RPbdb_DatabaseController::RPbdb_Database::(RPbdb_DatabaseCursorController::RPbdb_DatabaseCursor::)RPbdb_Record::RPBDB_DBT => RPbdb_Data
 *
 *
 */

#ifndef RPBDB_DATA
	#define RPBDB_DATA

	#include <cerialize.h>

	#include "BaseStandardInclude.h"

/****************
*  Prototypes  *
****************/

RPbdb_Data*		RPbdb_Data_new(			RPbdb_Record*	parent_record );

void			RPbdb_Data_free(	RPbdb_Data** data );
RPbdb_DatabaseRecordSettingsController*	RPbdb_Data_settingsController(	RPbdb_Data* data );
RPbdb_Environment*		RPbdb_Data_parentEnvironment(	RPbdb_Data* data );
RPbdb_Database* RPbdb_Data_parentDatabase(	RPbdb_Data* data );
RPbdb_Record* RPbdb_Data_parentRecord(	RPbdb_DatabaseRecordSettingsController* data );

void* RPbdb_Data_rawData( RPbdb_Data* data );
void RPbdb_Data_setRawData(	RPbdb_Data*	data,
														void*		data_raw,
														uint32_t	data_size );
uint32_t RPbdb_Data_size( RPbdb_Data* data );
CerializeType RPbdb_Data_type( RPbdb_Data* data );
void RPbdb_Data_setType(	RPbdb_Data*											data,
												CerializeType	type );

struct timeval* RPbdb_Data_creationStamp( RPbdb_Data* data );
struct timeval* RPbdb_Data_modificationStamp( RPbdb_Data* data );

#endif

