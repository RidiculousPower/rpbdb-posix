#ifndef RPDB_DATABASE_INTERNAL
	#define RPDB_DATABASE_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void RPDB_Database_internal_ensureOpen( RPDB_Database* database );
void RPDB_Database_internal_initWrappedDatabase(	RPDB_Database* database );
int		RPDB_Database_internal_secondaryKeyCreationCallbackMethod(	DB*					bdb_secondary_database, 
																   const DBT*			bdb_key, 
																   const DBT*			bdb_data, 
																   DBT*				bdb_return_data );
void RPDB_Database_internal_openWithoutRuntimeStorage( RPDB_Database* database );

RPDB_Record* RPDB_Database_internal_writeRawKeyDataPair(	RPDB_Database*	database, 
																		 uint32_t						flags,
																		 void*							primary_key,
																		 uint32_t						key_size,
																		 void*							data,
																		 uint32_t						data_size );
	RPDB_Record*	RPDB_Database_internal_writeRecord(			RPDB_Database*	database, 
																			uint32_t						flags,
																			RPDB_Record*					record );
RPDB_Record*	RPDB_Database_internal_writeKeyDataPair(	RPDB_Database*	database, 
																			uint32_t						flags,
																			RPDB_Key*						primary_key,
																			RPDB_Data*					write_data );	
																			
RPDB_Record* RPDB_Database_internal_retrieveRawKeyDataPair(	RPDB_Database*			database, 
																			   uint32_t								flag, 
																			   void*									key,
																			   uint32_t								key_size,
																			   void*									data,
																			   uint32_t								data_size );
	RPDB_Record*	RPDB_Database_internal_retrieveRecord(	RPDB_Database*	database, 
																		 uint32_t							flag, 
																		 RPDB_Record*							record );																			
RPDB_Database* RPDB_Database_internal_configureDatabaseInstanceForSecondaryIndexOnPrimaryDatabase(	RPDB_Database*		primary_database,
																																																		RPDB_Database*		secondary_database,
																																																		char*							index_name,
																																																		BOOL							enable_sorted_duplicates );
char* RPDB_Database_internal_filenameForName( char* database_name );
RPDB_Database* RPDB_Database_internal_initForRuntimeStorage(	RPDB_Database*		runtime_storage_database );
db_recno_t RPDB_Database_internal_storeRuntimeAddress(	RPDB_Database*	runtime_database,
																												void*			runtime_pointer );
void RPDB_Database_internal_freeStoredRuntimeAddress(	RPDB_Database*	runtime_database,
																											db_recno_t			runtime_record_number	);
void RPDB_Database_internal_closeAllStoredRuntimeAddresses(	RPDB_Database*	runtime_database,
																														void *close_function( void* )	);
void RPDB_Database_internal_freeAllStoredRuntimeAddresses(	RPDB_Database*	runtime_database,
																														void *free_function( void** ) );

char* RPDB_Database_internal_errorfilePathForDatabase( RPDB_Database* database );

#endif

