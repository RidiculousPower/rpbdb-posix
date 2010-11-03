/*
 *		RPDB::MemoryPoolController::MemoryPoolFile::MemoryPoolFilePageController::MemoryPoolFilePage
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MemoryPoolFilePage.h"
#include "RPDB_MemoryPoolFilePage_internal.h"

#include "RPDB_Database_internal.h"

#include "RPDB_MemoryPoolFile.h"
#include "RPDB_MemoryPoolFilePageController.h"

#include "RPDB_Environment.h"

#include "RPDB_SettingsController.h"
#include "RPDB_MemoryPoolSettingsController.h"
#include "RPDB_MemoryPoolFileSettingsController.h"
#include "RPDB_MemoryPoolFileCacheSettingsController.h"
#include "RPDB_MemoryPoolFileCachePrioritySettingsController.h"
#include "RPDB_MemoryPoolFilePageSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_MemoryPoolFilePage* RPDB_MemoryPoolFilePage_new( RPDB_MemoryPoolFilePageController* parent_memory_pool_file_page_controller )	{
	
	RPDB_MemoryPoolFilePage*		memory_pool_file_page = calloc( 1, sizeof( RPDB_MemoryPoolFilePage ) );

	if ( parent_memory_pool_file_page_controller->runtime_storage_database != NULL )	{
		memory_pool_file_page->runtime_identifier =	RPDB_Database_internal_storeRuntimeAddress(	parent_memory_pool_file_page_controller->runtime_storage_database,
																																														(void*) memory_pool_file_page );
	}

	memory_pool_file_page->parent_memory_pool_file_page_controller = parent_memory_pool_file_page_controller;

	return memory_pool_file_page;
}

/***************************
*  free  *
***************************/
void RPDB_MemoryPoolFilePage_free(	RPDB_MemoryPoolFilePage** memory_pool_file_page )	{

	if ( ( *memory_pool_file_page )->parent_memory_pool_file_page_controller->runtime_storage_database != NULL )	{
		RPDB_Database_internal_freeStoredRuntimeAddress(	( *memory_pool_file_page )->parent_memory_pool_file_page_controller->runtime_storage_database,
																											( *memory_pool_file_page )->runtime_identifier );
	}
	RPDB_MemoryPoolFilePage_internal_freeFromRuntimeStorage( memory_pool_file_page );
}

/***************************
*  free  *
***************************/

void RPDB_MemoryPoolFilePage_internal_freeFromRuntimeStorage(	RPDB_MemoryPoolFilePage** memory_pool_file_page )	{

	free( *memory_pool_file_page );
}

/***************************
*  settingsController  *
***************************/
RPDB_MemoryPoolFilePageSettingsController* RPDB_MemoryPoolFilePage_settingsController(	RPDB_MemoryPoolFilePage* memory_pool_file_page )	{
	return memory_pool_file_page->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MemoryPoolFilePage_parentEnvironment(	RPDB_MemoryPoolFilePage* memory_pool_file_page )	{
	return memory_pool_file_page->parent_memory_pool_file_page_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*************************
*  writePageToCache  *
*************************/

//	The DB_MPOOLFILE->put method returns a reference to a page in the cache, setting the priority of the page as specified by the priority parameter.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fput.html
RPDB_MemoryPoolFilePage* RPDB_MemoryPoolFilePageController_writePageToCache( RPDB_MemoryPoolFilePage* memory_pool_file_page )	{
	
	RPDB_MemoryPoolFileSettingsController*							memory_pool_file_settings_controller								=	RPDB_MemoryPoolFile_settingsController( memory_pool_file_page->parent_memory_pool_file_page_controller->parent_memory_pool_file );
	RPDB_MemoryPoolFileCacheSettingsController*					memory_pool_file_cache_settings_controller					=	RPDB_MemoryPoolFileSettingsController_cacheSettingsController( memory_pool_file_settings_controller );
	RPDB_MemoryPoolFileCachePrioritySettingsController*	memory_pool_file_cache_priority_settings_controller	=	RPDB_MemoryPoolFileCacheSettingsController_prioritySettingsController( memory_pool_file_cache_settings_controller );
	RPDB_MemoryPoolFilePageSettingsController*					memory_pool_file_page_settings_controller						=	RPDB_MemoryPoolFileSettingsController_pageSettingsController( memory_pool_file_settings_controller );
	
	memory_pool_file_page->wrapped_bdb_memory_pool_file->put(	memory_pool_file_page->wrapped_bdb_memory_pool_file,
																														memory_pool_file_page->page_address,
																														RPDB_MemoryPoolFileCachePrioritySettingsController_currentPriority( memory_pool_file_cache_priority_settings_controller ),
																														RPDB_MemoryPoolFilePageSettingsController_internal_writePageToCacheFlags( memory_pool_file_page_settings_controller ) );
	return memory_pool_file_page;
}





