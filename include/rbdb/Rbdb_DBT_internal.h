#ifndef RBDB_DBT_INTERNAL
	#define RBDB_DBT_INTERNAL
	
	Rbdb_DBT* Rbdb_DBT_internal_newFromBDBDBT(	Rbdb_Record*	parent_record, 
																							DBT*			bdb_dbt );

	void Rbdb_DBT_internal_verifyKeyDataTyping(	Rbdb_DBT*												dbt,
																							Rbdb_DatabaseRecordStorageType	type	);

void Rbdb_DBT_internal_verifyKeyDataTyping(	Rbdb_DBT*												dbt,
																						Rbdb_DatabaseRecordStorageType	type	);

#endif