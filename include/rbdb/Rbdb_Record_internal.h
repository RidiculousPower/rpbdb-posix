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

void Rbdb_Record_internal_createOrUpdateKeyTypeAndDataFooter( Rbdb_Record*	record,
																															BOOL					prepare_footer_for_data );

	void Rbdb_Record_internal_appendKeyType( Rbdb_Record* record );
	Rbdb_DatabaseRecordStorageType Rbdb_Record_internal_keyType( Rbdb_Record* record );
	void Rbdb_Record_internal_addKeyTypeToExistingRecord( Rbdb_Record* record );

	void Rbdb_Record_internal_createDataFooter( Rbdb_Record* record );
	void Rbdb_Record_internal_updateDataFooter( Rbdb_Record* record );
	Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )* Rbdb_Record_internal_dataFooter( Rbdb_Record* record );
	Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )* Rbdb_Record_internal_upgradeFooter( Rbdb_Record*		record );
	void Rbdb_Record_internal_addDataFooterToExistingRecord( Rbdb_Record* record );

#endif