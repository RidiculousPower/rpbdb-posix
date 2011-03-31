#ifndef RPBDB_DATABASE_INTERNAL
	#define RPBDB_DATABASE_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void RPbdb_Database_internal_ensureOpen( RPbdb_Database* database );
void RPbdb_Database_internal_initWrappedDatabase(	RPbdb_Database* database );
int		RPbdb_Database_internal_secondaryKeyCreationCallbackMethod(	DB*					bdb_secondary_database, 
																   const DBT*			bdb_key, 
																   const DBT*			bdb_data, 
																   DBT*				bdb_return_data );
void RPbdb_Database_internal_openWithoutRuntimeStorage( RPbdb_Database* database );

RPbdb_Record* RPbdb_Database_internal_writeRawKeyDataPair(	RPbdb_Database*	database, 
																		 uint32_t						flags,
																		 void*							primary_key,
																		 uint32_t						key_size,
																		 void*							data,
																		 uint32_t						data_size );
	RPbdb_Record*	RPbdb_Database_internal_writeRecord(			RPbdb_Database*	database, 
																			uint32_t						flags,
																			RPbdb_Record*					record );
RPbdb_Record*	RPbdb_Database_internal_writeKeyDataPair(	RPbdb_Database*	database, 
																			uint32_t						flags,
																			RPbdb_Key*						primary_key,
																			RPbdb_Data*					write_data );	

void RPbdb_Database_internal_prepareRecordForWriteRetrieveDelete(	RPbdb_Database*		database, 
																																	RPbdb_Record*			record,
																																	BOOL							prepare_data_in_record );
																			
RPbdb_Record* RPbdb_Database_internal_retrieveRawKeyDataPair(	RPbdb_Database*			database, 
																			   uint32_t								flag, 
																			   void*									key,
																			   uint32_t								key_size,
																			   void*									data,
																			   uint32_t								data_size );
	RPbdb_Record*	RPbdb_Database_internal_retrieveRecord(	RPbdb_Database*	database, 
																		 uint32_t							flag, 
																		 RPbdb_Record*							record );																			
char* RPbdb_Database_internal_secondaryDatabaseNameForIndex( char* index_name,
																														char*	primary_database_name );
RPbdb_Database* RPbdb_Database_internal_configureDatabaseInstanceForSecondaryIndexOnPrimaryDatabase(	RPbdb_Database*		primary_database,
																																																		RPbdb_Database*		secondary_database,
																																																		char*							index_name,
																																																		BOOL							enable_duplicates,
																																																		BOOL							enable_sorted_duplicates);
char* RPbdb_Database_internal_filenameForName( char* database_name );
RPbdb_Database* RPbdb_Database_internal_initForRuntimeStorage(	RPbdb_Database*		runtime_storage_database );
db_recno_t RPbdb_Database_internal_storeRuntimeAddress(	RPbdb_Database*	runtime_database,
																												void*			runtime_pointer );
void RPbdb_Database_internal_freeStoredRuntimeAddress(	RPbdb_Database*	runtime_database,
																											db_recno_t			runtime_record_number	);
void RPbdb_Database_internal_closeAllStoredRuntimeAddresses(	RPbdb_Database*	runtime_database,
																														void *close_function( void* )	);
void RPbdb_Database_internal_freeAllStoredRuntimeAddresses(	RPbdb_Database*	runtime_database,
																														void *free_function( void** ) );

char* RPbdb_Database_internal_errorfilePathForDatabase( RPbdb_Database* database );
void RPbdb_Database_internal_freeAllStoredRuntimeAddresses(	RPbdb_Database*	runtime_database,
																														void *free_function( void** ) );
void RPbdb_Database_internal_freeFromRuntimeStorage( RPbdb_Database** database );

#endif

