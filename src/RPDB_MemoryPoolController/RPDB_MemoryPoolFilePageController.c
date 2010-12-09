/*
 *		Rbdb::MemoryPoolController::MemoryPoolFile::MemoryPoolFilePageController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_MemoryPoolFilePageController.h"

#include "Rbdb_MemoryPoolFile.h"
#include "Rbdb_MemoryPoolFilePage.h"

#include "Rbdb_Environment.h"

#include "Rbdb_TransactionController.h"
#include "Rbdb_TransactionController_internal.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_MemoryPoolSettingsController.h"
#include "Rbdb_MemoryPoolFileSettingsController.h"
#include "Rbdb_MemoryPoolFilePageSettingsController.h"
#include "Rbdb_MemoryPoolFilePageSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_MemoryPoolFilePageController* Rbdb_MemoryPoolFilePageController_new( Rbdb_MemoryPoolFile* parent_memory_pool_file )	{
	
	Rbdb_MemoryPoolFilePageController*		memory_pool_file_page_controller = calloc( 1, sizeof( Rbdb_MemoryPoolFilePageController ) );

	memory_pool_file_page_controller->parent_memory_pool_file = parent_memory_pool_file;

	return memory_pool_file_page_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_MemoryPoolFilePageController_free(	Rbdb_MemoryPoolFilePageController** memory_pool_file_page_controller )	{

	free( memory_pool_file_page_controller );
}

/***************************
*  settingsController  *
***************************/
Rbdb_MemoryPoolFilePageSettingsController* Rbdb_MemoryPoolFilePageController_settingsController(	Rbdb_MemoryPoolFilePageController* memory_pool_file_page_controller )	{
	return memory_pool_file_page_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_MemoryPoolFilePageController_parentEnvironment(	Rbdb_MemoryPoolFilePageController* memory_pool_file_page_controller )	{
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
Rbdb_MemoryPoolFilePage* Rbdb_MemoryPoolFilePageController_retrievePageFromCache(	Rbdb_MemoryPoolFilePageController*	memory_pool_file_page_controller,
 																					db_pgno_t							page_number_address	)	{

	Rbdb_MemoryPoolFile*		memory_pool_file		= memory_pool_file_page_controller->parent_memory_pool_file;
	
	Rbdb_MemoryPoolFilePage*	memory_pool_file_page	= Rbdb_MemoryPoolFilePage_new( memory_pool_file_page_controller );
	
	Rbdb_Environment*	environment	=	memory_pool_file_page_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
	
	DB_TXN*	transaction_id	=	NULL;
	if ( environment->transaction_controller != NULL )	{
		transaction_id	=	Rbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	memory_pool_file->wrapped_bdb_memory_pool_file->get(	memory_pool_file->wrapped_bdb_memory_pool_file,
															& page_number_address,
															transaction_id,
															Rbdb_MemoryPoolFilePageSettingsController_internal_retrievePageFromCacheFlags( Rbdb_MemoryPoolFileSettingsController_pageSettingsController( Rbdb_MemoryPoolSettingsController_fileSettingsController( Rbdb_SettingsController_memoryPoolSettingsController( Rbdb_Environment_settingsController( memory_pool_file_page_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment )))) ),
															&( memory_pool_file_page->page_data ) );							
	return memory_pool_file_page;
}






