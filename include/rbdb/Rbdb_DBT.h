/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record::RBDB_DBT
 *
 *
 */

#ifndef RBDB_DBT_HEADER
	#define RBDB_DBT_HEADER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RBDB_DBT*	RBDB_DBT_new(		Rbdb_Record*	parent_record );

	void							RBDB_DBT_free(								RBDB_DBT**						dbt );
	Rbdb_DatabaseRecordSettingsController*	RBDB_DBT_settingsController(				RBDB_DBT*						dbt );
	Rbdb_Environment*		RBDB_DBT_parentEnvironment(	RBDB_DBT*	dbt );
	Rbdb_Database* RBDB_DBT_parentDatabase(	RBDB_DBT* dbt );
	Rbdb_Record* RBDB_DBT_parentRecord(	RBDB_DBT* dbt );

	void*		RBDB_DBT_data(		RBDB_DBT*		dbt );
	void RBDB_DBT_setData(	RBDB_DBT*	dbt, 
							void*		data_raw,
							uint32_t	data_size );
	uint32_t	RBDB_DBT_size(		RBDB_DBT*		dbt );	

#endif

