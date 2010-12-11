#ifndef RBDB_RECORD_INTERNAL
	#define RBDB_RECORD_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

Rbdb_Record* Rbdb_Record_internal_newWithoutDBT(	Rbdb_Database* parent_database	);

Rbdb_Record* Rbdb_Record_internal_newFromKeyDBTDataDBT(	Rbdb_Database* parent_database,
													  DBT*	dbt_key,
													  DBT*	dbt_data	);

Rbdb_Record* Rbdb_Record_internal_newFromKeyData(	Rbdb_Database* parent_database,
												   Rbdb_Key*	dbt_key,
												   Rbdb_Data*	dbt_data	);
	
void	Rbdb_Record_internal_freeFromRuntimeStorage( Rbdb_Record** record );

#endif