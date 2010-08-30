/*
 *		RPDB::MemoryPoolController::MemoryPoolFile::MemoryPoolFilePageController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MemoryPoolFilePageController.h"

#include "RPDB_MemoryPoolFile.h"
#include "RPDB_MemoryPoolFilePage.h"

#include "RPDB_Environment.h"

#include "RPDB_TransactionController.h"
#include "RPDB_TransactionController_internal.h"

#include "RPDB_SettingsController.h"
#include "RPDB_MemoryPoolSettingsController.h"
#include "RPDB_MemoryPoolFileSettingsController.h"
#include "RPDB_MemoryPoolFilePageSettingsController.h"
#include "RPDB_MemoryPoolFilePageSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_MemoryPoolFilePageController* RPDB_MemoryPoolFilePageController_new( RPDB_MemoryPoolFile* parent_memory_pool_file )	{
	
	RPDB_MemoryPoolFilePageController*		memory_pool_file_page_controller = calloc( 1, sizeof( RPDB_MemoryPoolFilePageController ) );

	memory_pool_file_page_controller->parent_memory_pool_file = parent_memory_pool_file;

	return memory_pool_file_page_controller;
}

/***************************
*  free  *
***************************/
void RPDB_MemoryPoolFilePageController_free(	RPDB_MemoryPoolFilePageController** memory_pool_file_page_controller )	{

	free( memory_pool_file_page_controller );
}

/***************************
*  settingsController  *
***************************/
RPDB_MemoryPoolFilePageSettingsController* RPDB_MemoryPoolFilePageController_settingsController(	RPDB_MemoryPoolFilePageController* memory_pool_file_page_controller )	{
	return memory_pool_file_page_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MemoryPoolFilePageController_parentEnvironment(	RPDB_MemoryPoolFilePageController* memory_pool_file_page_controller )	{
	return memory_pool_file_page_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*****************************
*  retrievePageFromCache  *
*****************************/

//	If the flags parameter is set to DB_MPOOL_LAST or DB_MPOOL_NEW, the page number of the created page 
//	is copied into the memory location to which the pgnoaddr parameter refers. 
//	Otherwise, the pgnoaddr parameter is the page to create or retrieve.
//	Page numbers begin at 0; that is, the first page in the file is page number 0, not page number 1.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
RPDB_MemoryPoolFilePage* RPDB_MemoryPoolFilePageController_retrievePageFromCache(	RPDB_MemoryPoolFilePageController*	memory_pool_file_page_controller,
 																					db_pgno_t							page_number_address	)	{

	RPDB_MemoryPoolFile*		memory_pool_file		= memory_pool_file_page_controller->parent_memory_pool_file;
	
	RPDB_MemoryPoolFilePage*	memory_pool_file_page	= RPDB_MemoryPoolFilePage_new( memory_pool_file_page_controller );
	
	RPDB_Environment*	environment	=	memory_pool_file_page_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
	
	DB_TXN*	transaction_id	=	NULL;
	if ( environment->transaction_controller != NULL )	{
		transaction_id	=	RPDB_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	memory_pool_file->wrapped_bdb_memory_pool_file->get(	memory_pool_file->wrapped_bdb_memory_pool_file,
															& page_number_address,
															transaction_id,
															RPDB_MemoryPoolFilePageSettingsController_internal_retrievePageFromCacheFlags( RPDB_MemoryPoolFileSettingsController_pageSettingsController( RPDB_MemoryPoolSettingsController_fileSettingsController( RPDB_SettingsController_memoryPoolSettingsController( RPDB_Environment_settingsController( memory_pool_file_page_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment )))) ),
															&( memory_pool_file_page->page_data ) );							
	return memory_pool_file_page;
}






