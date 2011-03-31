/*
 *		RPbdb::MemoryPoolController::MemoryPoolFile::MemoryPoolFilePageController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "MemoryPoolFilePageController.h"

#include "MemoryPoolFile.h"
#include "MemoryPoolFilePage.h"

#include "Environment.h"

#include "TransactionController.h"
#include "TransactionController_internal.h"

#include "SettingsController.h"
#include "MemoryPoolSettingsController.h"
#include "MemoryPoolFileSettingsController.h"
#include "MemoryPoolFilePageSettingsController.h"
#include "MemoryPoolFilePageSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_MemoryPoolFilePageController* RPbdb_MemoryPoolFilePageController_new( RPbdb_MemoryPoolFile* parent_memory_pool_file )	{
	
	RPbdb_MemoryPoolFilePageController*		memory_pool_file_page_controller = calloc( 1, sizeof( RPbdb_MemoryPoolFilePageController ) );

	memory_pool_file_page_controller->parent_memory_pool_file = parent_memory_pool_file;

	return memory_pool_file_page_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_MemoryPoolFilePageController_free(	RPbdb_MemoryPoolFilePageController** memory_pool_file_page_controller )	{

	free( memory_pool_file_page_controller );
}

/***************************
*  settingsController  *
***************************/
RPbdb_MemoryPoolFilePageSettingsController* RPbdb_MemoryPoolFilePageController_settingsController(	RPbdb_MemoryPoolFilePageController* memory_pool_file_page_controller )	{
	return memory_pool_file_page_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MemoryPoolFilePageController_parentEnvironment(	RPbdb_MemoryPoolFilePageController* memory_pool_file_page_controller )	{
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
RPbdb_MemoryPoolFilePage* RPbdb_MemoryPoolFilePageController_retrievePageFromCache(	RPbdb_MemoryPoolFilePageController*	memory_pool_file_page_controller,
 																					db_pgno_t							page_number_address	)	{

	RPbdb_MemoryPoolFile*		memory_pool_file		= memory_pool_file_page_controller->parent_memory_pool_file;
	
	RPbdb_MemoryPoolFilePage*	memory_pool_file_page	= RPbdb_MemoryPoolFilePage_new( memory_pool_file_page_controller );
	
	RPbdb_Environment*	environment	=	memory_pool_file_page_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
	
	DB_TXN*	transaction_id	=	NULL;
	if ( environment->transaction_controller != NULL )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	memory_pool_file->wrapped_bdb_memory_pool_file->get(	memory_pool_file->wrapped_bdb_memory_pool_file,
															& page_number_address,
															transaction_id,
															RPbdb_MemoryPoolFilePageSettingsController_internal_retrievePageFromCacheFlags( RPbdb_MemoryPoolFileSettingsController_pageSettingsController( RPbdb_MemoryPoolSettingsController_fileSettingsController( RPbdb_SettingsController_memoryPoolSettingsController( RPbdb_Environment_settingsController( memory_pool_file_page_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment )))) ),
															&( memory_pool_file_page->page_data ) );							
	return memory_pool_file_page;
}






