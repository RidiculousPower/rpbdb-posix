/*
 *		RPDB::RPDB_DatabaseController::RPDB_Database::(RPDB_DatabaseCursorController::RPDB_DatabaseCursor::)RPDB_Record::RPDB_DBT
 *
 *
 */

#ifndef RPDB_DBT_HEADER
	#define RPDB_DBT_HEADER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DBT*	RPDB_DBT_new(		RPDB_Record*	parent_record );

	void							RPDB_DBT_free(								RPDB_DBT**						dbt );
	RPDB_DatabaseRecordSettingsController*	RPDB_DBT_settingsController(				RPDB_DBT*						dbt );
	RPDB_Environment*		RPDB_DBT_parentEnvironment(	RPDB_DBT*	dbt );
	RPDB_Database* RPDB_DBT_parentDatabase(	RPDB_DBT* dbt );
	RPDB_Record* RPDB_DBT_parentRecord(	RPDB_DBT* dbt );

	void*		RPDB_DBT_data(		RPDB_DBT*		dbt );
	void RPDB_DBT_setData(	RPDB_DBT*	dbt, 
							void*		data_raw,
							uint32_t	data_size );
	uint32_t	RPDB_DBT_size(		RPDB_DBT*		dbt );	

#endif

