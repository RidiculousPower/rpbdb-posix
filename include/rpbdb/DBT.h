/*
 *		RPbdb::RPbdb_DatabaseController::RPbdb_Database::(RPbdb_DatabaseCursorController::RPbdb_DatabaseCursor::)RPbdb_Record::RPBDB_DBT
 *
 *
 */

#ifndef RPBDB_DBT_HEADER
	#define RPBDB_DBT_HEADER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DBT*	RPbdb_DBT_new(		RPbdb_Record*	parent_record );

	void							RPbdb_DBT_free(								RPbdb_DBT**						dbt );
	RPbdb_DatabaseRecordSettingsController*	RPbdb_DBT_settingsController(				RPbdb_DBT*						dbt );
	RPbdb_Environment*		RPbdb_DBT_parentEnvironment(	RPbdb_DBT*	dbt );
	RPbdb_Database* RPbdb_DBT_parentDatabase(	RPbdb_DBT* dbt );
	RPbdb_Record* RPbdb_DBT_parentRecord(	RPbdb_DBT* dbt );

	void*		RPbdb_DBT_data(		RPbdb_DBT*		dbt );
	void RPbdb_DBT_setData(	RPbdb_DBT*	dbt, 
							void*		data_raw,
							uint32_t	data_size );
	uint32_t	RPbdb_DBT_size(		RPbdb_DBT*		dbt );	

CerializeType RPbdb_DBT_type( RPbdb_DBT* dbt );
void RPbdb_DBT_setType(	RPbdb_DBT*												dbt,
												CerializeType	type);

#endif

