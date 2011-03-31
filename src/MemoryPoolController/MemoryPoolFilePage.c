/*
 *		RPbdb::MemoryPoolController::MemoryPoolFile::MemoryPoolFilePageController::MemoryPoolFilePage
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "MemoryPoolFilePage.h"
#include "MemoryPoolFilePage_internal.h"

#include "Database_internal.h"

#include "MemoryPoolFile.h"
#include "MemoryPoolFilePageController.h"

#include "Environment.h"

#include "SettingsController.h"
#include "MemoryPoolSettingsController.h"
#include "MemoryPoolFileSettingsController.h"
#include "MemoryPoolFileCacheSettingsController.h"
#include "MemoryPoolFileCachePrioritySettingsController.h"
#include "MemoryPoolFilePageSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_MemoryPoolFilePage* RPbdb_MemoryPoolFilePage_new( RPbdb_MemoryPoolFilePageController* parent_memory_pool_file_page_controller )	{
	
	RPbdb_MemoryPoolFilePage*		memory_pool_file_page = calloc( 1, sizeof( RPbdb_MemoryPoolFilePage ) );

	if ( parent_memory_pool_file_page_controller->runtime_storage_database != NULL )	{
		memory_pool_file_page->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_memory_pool_file_page_controller->runtime_storage_database,
																																														(void*) memory_pool_file_page );
	}

	memory_pool_file_page->parent_memory_pool_file_page_controller = parent_memory_pool_file_page_controller;

	return memory_pool_file_page;
}

/***************************
*  free  *
***************************/
void RPbdb_MemoryPoolFilePage_free(	RPbdb_MemoryPoolFilePage** memory_pool_file_page )	{

	if ( ( *memory_pool_file_page )->parent_memory_pool_file_page_controller->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *memory_pool_file_page )->parent_memory_pool_file_page_controller->runtime_storage_database,
																											( *memory_pool_file_page )->runtime_identifier );
	}
	RPbdb_MemoryPoolFilePage_internal_freeFromRuntimeStorage( memory_pool_file_page );
}

/***************************
*  free  *
***************************/

void RPbdb_MemoryPoolFilePage_internal_freeFromRuntimeStorage(	RPbdb_MemoryPoolFilePage** memory_pool_file_page )	{

	free( *memory_pool_file_page );
}

/***************************
*  settingsController  *
***************************/
RPbdb_MemoryPoolFilePageSettingsController* RPbdb_MemoryPoolFilePage_settingsController(	RPbdb_MemoryPoolFilePage* memory_pool_file_page )	{
	return memory_pool_file_page->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MemoryPoolFilePage_parentEnvironment(	RPbdb_MemoryPoolFilePage* memory_pool_file_page )	{
	return memory_pool_file_page->parent_memory_pool_file_page_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*************************
*  writePageToCache  *
*************************/

//	The DB_MPOOLFILE->put method returns a reference to a page in the cache, setting the priority of the page as specified by the priority parameter.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fput.html
RPbdb_MemoryPoolFilePage* RPbdb_MemoryPoolFilePageController_writePageToCache( RPbdb_MemoryPoolFilePage* memory_pool_file_page )	{
	
	RPbdb_MemoryPoolFileSettingsController*							memory_pool_file_settings_controller								=	RPbdb_MemoryPoolFile_settingsController( memory_pool_file_page->parent_memory_pool_file_page_controller->parent_memory_pool_file );
	RPbdb_MemoryPoolFileCacheSettingsController*					memory_pool_file_cache_settings_controller					=	RPbdb_MemoryPoolFileSettingsController_cacheSettingsController( memory_pool_file_settings_controller );
	RPbdb_MemoryPoolFileCachePrioritySettingsController*	memory_pool_file_cache_priority_settings_controller	=	RPbdb_MemoryPoolFileCacheSettingsController_prioritySettingsController( memory_pool_file_cache_settings_controller );
	RPbdb_MemoryPoolFilePageSettingsController*					memory_pool_file_page_settings_controller						=	RPbdb_MemoryPoolFileSettingsController_pageSettingsController( memory_pool_file_settings_controller );
	
	memory_pool_file_page->wrapped_bdb_memory_pool_file->put(	memory_pool_file_page->wrapped_bdb_memory_pool_file,
																														memory_pool_file_page->page_address,
																														RPbdb_MemoryPoolFileCachePrioritySettingsController_currentPriority( memory_pool_file_cache_priority_settings_controller ),
																														RPbdb_MemoryPoolFilePageSettingsController_internal_writePageToCacheFlags( memory_pool_file_page_settings_controller ) );
	return memory_pool_file_page;
}





