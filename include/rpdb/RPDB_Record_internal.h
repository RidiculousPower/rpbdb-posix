#ifndef RPDB_RECORD_INTERNAL
	#define RPDB_RECORD_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPDB_Record* RPDB_Record_internal_newWithoutDBT(	RPDB_Database* parent_database	);

RPDB_Record* RPDB_Record_internal_newFromKeyDBTDataDBT(	RPDB_Database* parent_database,
													  DBT*	dbt_key,
													  DBT*	dbt_data	);

RPDB_Record* RPDB_Record_internal_newFromKeyData(	RPDB_Database* parent_database,
												   RPDB_Key*	dbt_key,
												   RPDB_Data*	dbt_data	);
	
void	RPDB_Record_internal_freeFromRuntimeStorage( RPDB_Record** record );

#endif