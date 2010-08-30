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

#include "RPDB_MemoryPoolFile.h"
#include "RPDB_MemoryPoolFilePageController.h"

#include "RPDB_Environment.h"

#include "RPDB_SettingsController.h"
#include "RPDB_MemoryPoolSettingsController.h"
#include "RPDB_MemoryPoolFileSettingsController.h"
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

RPDB_MemoryPoolFilePage* RPDB_MemoryPoolFilePage_new( RPDB_MemoryPoolFilePageController* memory_pool_file_page_controller )	{
	
	RPDB_MemoryPoolFilePage*		memory_pool_file_page = calloc( 1, sizeof( RPDB_MemoryPoolFilePage ) );

	memory_pool_file_page->parent_memory_pool_file_page_controller = memory_pool_file_page_controller;

	return memory_pool_file_page;
}

/***************************
*  free  *
***************************/
void RPDB_MemoryPoolFilePage_free(	RPDB_MemoryPoolFilePage** memory_pool_file_page )	{

	free( memory_pool_file_page );
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
	
	memory_pool_file_page->wrapped_bdb_memory_pool_file->put(	memory_pool_file_page->wrapped_bdb_memory_pool_file,
								memory_pool_file_page->page_address,
								RPDB_MemoryPoolFileCachePrioritySettingsController_currentPriority( RPDB_MemoryPoolFileSettingsController_cachePrioritySettingsController( RPDB_MemoryPoolFile_settingsController( memory_pool_file_page->parent_memory_pool_file_page_controller->parent_memory_pool_file ) ) ),
								RPDB_MemoryPoolFilePageSettingsController_internal_writePageToCacheFlags( RPDB_MemoryPoolFileSettingsController_pageSettingsController( RPDB_MemoryPoolSettingsController_fileSettingsController( RPDB_SettingsController_memoryPoolSettingsController( RPDB_Environment_settingsController( memory_pool_file_page->parent_memory_pool_file_page_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment) ) ) ) ) );
	return memory_pool_file_page;
}





