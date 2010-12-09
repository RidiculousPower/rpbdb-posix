/*
 *		Rbdb::MemoryPoolController::MemoryPoolFile::MemoryPoolFilePageController::MemoryPoolFilePage
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_MemoryPoolFilePage.h"
#include "Rbdb_MemoryPoolFilePage_internal.h"

#include "Rbdb_Database_internal.h"

#include "Rbdb_MemoryPoolFile.h"
#include "Rbdb_MemoryPoolFilePageController.h"

#include "Rbdb_Environment.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_MemoryPoolSettingsController.h"
#include "Rbdb_MemoryPoolFileSettingsController.h"
#include "Rbdb_MemoryPoolFileCacheSettingsController.h"
#include "Rbdb_MemoryPoolFileCachePrioritySettingsController.h"
#include "Rbdb_MemoryPoolFilePageSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_MemoryPoolFilePage* Rbdb_MemoryPoolFilePage_new( Rbdb_MemoryPoolFilePageController* parent_memory_pool_file_page_controller )	{
	
	Rbdb_MemoryPoolFilePage*		memory_pool_file_page = calloc( 1, sizeof( Rbdb_MemoryPoolFilePage ) );

	if ( parent_memory_pool_file_page_controller->runtime_storage_database != NULL )	{
		memory_pool_file_page->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_memory_pool_file_page_controller->runtime_storage_database,
																																														(void*) memory_pool_file_page );
	}

	memory_pool_file_page->parent_memory_pool_file_page_controller = parent_memory_pool_file_page_controller;

	return memory_pool_file_page;
}

/***************************
*  free  *
***************************/
void Rbdb_MemoryPoolFilePage_free(	Rbdb_MemoryPoolFilePage** memory_pool_file_page )	{

	if ( ( *memory_pool_file_page )->parent_memory_pool_file_page_controller->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *memory_pool_file_page )->parent_memory_pool_file_page_controller->runtime_storage_database,
																											( *memory_pool_file_page )->runtime_identifier );
	}
	Rbdb_MemoryPoolFilePage_internal_freeFromRuntimeStorage( memory_pool_file_page );
}

/***************************
*  free  *
***************************/

void Rbdb_MemoryPoolFilePage_internal_freeFromRuntimeStorage(	Rbdb_MemoryPoolFilePage** memory_pool_file_page )	{

	free( *memory_pool_file_page );
}

/***************************
*  settingsController  *
***************************/
Rbdb_MemoryPoolFilePageSettingsController* Rbdb_MemoryPoolFilePage_settingsController(	Rbdb_MemoryPoolFilePage* memory_pool_file_page )	{
	return memory_pool_file_page->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_MemoryPoolFilePage_parentEnvironment(	Rbdb_MemoryPoolFilePage* memory_pool_file_page )	{
	return memory_pool_file_page->parent_memory_pool_file_page_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*************************
*  writePageToCache  *
*************************/

//	The DB_MPOOLFILE->put method returns a reference to a page in the cache, setting the priority of the page as specified by the priority parameter.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fput.html
Rbdb_MemoryPoolFilePage* Rbdb_MemoryPoolFilePageController_writePageToCache( Rbdb_MemoryPoolFilePage* memory_pool_file_page )	{
	
	Rbdb_MemoryPoolFileSettingsController*							memory_pool_file_settings_controller								=	Rbdb_MemoryPoolFile_settingsController( memory_pool_file_page->parent_memory_pool_file_page_controller->parent_memory_pool_file );
	Rbdb_MemoryPoolFileCacheSettingsController*					memory_pool_file_cache_settings_controller					=	Rbdb_MemoryPoolFileSettingsController_cacheSettingsController( memory_pool_file_settings_controller );
	Rbdb_MemoryPoolFileCachePrioritySettingsController*	memory_pool_file_cache_priority_settings_controller	=	Rbdb_MemoryPoolFileCacheSettingsController_prioritySettingsController( memory_pool_file_cache_settings_controller );
	Rbdb_MemoryPoolFilePageSettingsController*					memory_pool_file_page_settings_controller						=	Rbdb_MemoryPoolFileSettingsController_pageSettingsController( memory_pool_file_settings_controller );
	
	memory_pool_file_page->wrapped_bdb_memory_pool_file->put(	memory_pool_file_page->wrapped_bdb_memory_pool_file,
																														memory_pool_file_page->page_address,
																														Rbdb_MemoryPoolFileCachePrioritySettingsController_currentPriority( memory_pool_file_cache_priority_settings_controller ),
																														Rbdb_MemoryPoolFilePageSettingsController_internal_writePageToCacheFlags( memory_pool_file_page_settings_controller ) );
	return memory_pool_file_page;
}





