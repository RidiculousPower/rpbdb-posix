#ifndef RPDB_MEMORY_POOL_FILE_CONTROLLER_INTERNAL
	#define RPDB_MEMORY_POOL_FILE_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int RPDB_MemoryPoolFileController_internal_pageInMethod(	DB_ENV*		bdb_environment,
															db_pgno_t	page_number,
															void*		page_address,
															DBT*		bdb_page_cookie );
															
int RPDB_MemoryPoolFileController_internal_pageInMethod(	DB_ENV*		environment,
															db_pgno_t	page_number,
															void*		page_address,
															DBT*		page_cookie );


#endif