#ifndef RBDB_DATABASE_INTERNAL
	#define RBDB_DATABASE_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void Rbdb_Database_internal_ensureOpen( Rbdb_Database* database );
void Rbdb_Database_internal_initWrappedDatabase(	Rbdb_Database* database );
int		Rbdb_Database_internal_secondaryKeyCreationCallbackMethod(	DB*					bdb_secondary_database, 
																   const DBT*			bdb_key, 
																   const DBT*			bdb_data, 
																   DBT*				bdb_return_data );
void Rbdb_Database_internal_openWithoutRuntimeStorage( Rbdb_Database* database );

Rbdb_Record* Rbdb_Database_internal_writeRawKeyDataPair(	Rbdb_Database*	database, 
																		 uint32_t						flags,
																		 void*							primary_key,
																		 uint32_t						key_size,
																		 void*							data,
																		 uint32_t						data_size );
	Rbdb_Record*	Rbdb_Database_internal_writeRecord(			Rbdb_Database*	database, 
																			uint32_t						flags,
																			Rbdb_Record*					record );
Rbdb_Record*	Rbdb_Database_internal_writeKeyDataPair(	Rbdb_Database*	database, 
																			uint32_t						flags,
																			Rbdb_Key*						primary_key,
																			Rbdb_Data*					write_data );	

void Rbdb_Database_internal_prepareRecordForWriteRetrieveDelete(	Rbdb_Database*		database, 
																																	Rbdb_Record*			record,
																																	BOOL							prepare_data_in_record );
																			
Rbdb_Record* Rbdb_Database_internal_retrieveRawKeyDataPair(	Rbdb_Database*			database, 
																			   uint32_t								flag, 
																			   void*									key,
																			   uint32_t								key_size,
																			   void*									data,
																			   uint32_t								data_size );
	Rbdb_Record*	Rbdb_Database_internal_retrieveRecord(	Rbdb_Database*	database, 
																		 uint32_t							flag, 
																		 Rbdb_Record*							record );																			
char* Rbdb_Database_internal_secondaryDatabaseNameForIndex( char* index_name,
																														char*	primary_database_name );
Rbdb_Database* Rbdb_Database_internal_configureDatabaseInstanceForSecondaryIndexOnPrimaryDatabase(	Rbdb_Database*		primary_database,
																																																		Rbdb_Database*		secondary_database,
																																																		char*							index_name,
																																																		BOOL							enable_duplicates,
																																																		BOOL							enable_sorted_duplicates);
char* Rbdb_Database_internal_filenameForName( char* database_name );
Rbdb_Database* Rbdb_Database_internal_initForRuntimeStorage(	Rbdb_Database*		runtime_storage_database );
db_recno_t Rbdb_Database_internal_storeRuntimeAddress(	Rbdb_Database*	runtime_database,
																												void*			runtime_pointer );
void Rbdb_Database_internal_freeStoredRuntimeAddress(	Rbdb_Database*	runtime_database,
																											db_recno_t			runtime_record_number	);
void Rbdb_Database_internal_closeAllStoredRuntimeAddresses(	Rbdb_Database*	runtime_database,
																														void *close_function( void* )	);
void Rbdb_Database_internal_freeAllStoredRuntimeAddresses(	Rbdb_Database*	runtime_database,
																														void *free_function( void** ) );

char* Rbdb_Database_internal_errorfilePathForDatabase( Rbdb_Database* database );
void Rbdb_Database_internal_freeAllStoredRuntimeAddresses(	Rbdb_Database*	runtime_database,
																														void *free_function( void** ) );
void Rbdb_Database_internal_freeFromRuntimeStorage( Rbdb_Database** database );

#endif

