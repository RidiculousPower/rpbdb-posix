#ifndef RPBDB_MEMORY_POOL_FILE_CONTROLLER_INTERNAL
	#define RPBDB_MEMORY_POOL_FILE_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int RPbdb_MemoryPoolFileController_internal_pageInMethod(	DB_ENV*		bdb_environment,
															db_pgno_t	page_number,
															void*		page_address,
															DBT*		bdb_page_cookie );
															
int RPbdb_MemoryPoolFileController_internal_pageInMethod(	DB_ENV*		environment,
															db_pgno_t	page_number,
															void*		page_address,
															DBT*		page_cookie );


#endif