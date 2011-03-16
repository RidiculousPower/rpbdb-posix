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

	Rbdb_DBT*	Rbdb_DBT_new(		Rbdb_Record*	parent_record );

	void							Rbdb_DBT_free(								Rbdb_DBT**						dbt );
	Rbdb_DatabaseRecordSettingsController*	Rbdb_DBT_settingsController(				Rbdb_DBT*						dbt );
	Rbdb_Environment*		Rbdb_DBT_parentEnvironment(	Rbdb_DBT*	dbt );
	Rbdb_Database* Rbdb_DBT_parentDatabase(	Rbdb_DBT* dbt );
	Rbdb_Record* Rbdb_DBT_parentRecord(	Rbdb_DBT* dbt );

	void*		Rbdb_DBT_data(		Rbdb_DBT*		dbt );
	void Rbdb_DBT_setData(	Rbdb_DBT*	dbt, 
							void*		data_raw,
							uint32_t	data_size );
	uint32_t	Rbdb_DBT_size(		Rbdb_DBT*		dbt );	

CerializeType Rbdb_DBT_type( Rbdb_DBT* dbt );
void Rbdb_DBT_setType(	Rbdb_DBT*												dbt,
												CerializeType	type);

#endif

