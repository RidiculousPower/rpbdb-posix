#ifndef RPBDB_RECORD_INTERNAL
	#define RPBDB_RECORD_INTERNAL
		
	/*******************************************************************************************************************************************************************************************
	********************************************************************************************************************************************************************************************
																	Internal Method Prototypes
	********************************************************************************************************************************************************************************************
	*******************************************************************************************************************************************************************************************/

	RPbdb_Record* RPbdb_Record_internal_newWithoutDBT(	RPbdb_Database* parent_database	);

	RPbdb_Record* RPbdb_Record_internal_newFromKeyDBTDataDBT(	RPbdb_Database* parent_database,
															DBT*	dbt_key,
															DBT*	dbt_data	);

	RPbdb_Record* RPbdb_Record_internal_newFromKeyData(	RPbdb_Database* parent_database,
														 RPbdb_Key*	dbt_key,
														 RPbdb_Data*	dbt_data	);
		
	void	RPbdb_Record_internal_freeFromRuntimeStorage( RPbdb_Record** record );

void RPbdb_Record_internal_createOrUpdateKeyTypeAndDataFooter( RPbdb_Record*	record,
																															BOOL					prepare_data_in_record );


#endif