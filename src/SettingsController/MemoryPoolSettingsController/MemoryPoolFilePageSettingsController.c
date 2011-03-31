/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "MemoryPoolFilePageSettingsController.h"

#include "MemoryPoolFileSettingsController.h"

#include "MemoryPoolFilePageSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPbdb_MemoryPoolFilePageSettingsController* RPbdb_MemoryPoolFilePageSettingsController_new( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	RPbdb_MemoryPoolFilePageSettingsController*		memory_pool_file_page_settings_controller = calloc( 1, sizeof( RPbdb_MemoryPoolFileSettingsController ) );

	memory_pool_file_page_settings_controller->parent_memory_pool_file_settings_controller = memory_pool_file_settings_controller;

	return memory_pool_file_page_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_MemoryPoolFilePageSettingsController_free(	RPbdb_MemoryPoolFilePageSettingsController** memory_pool_file_page_settings_controller )	{

	free( *memory_pool_file_page_settings_controller );
	*memory_pool_file_page_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MemoryPoolFilePageSettingsController_parentEnvironment(	RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	return memory_pool_file_page_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*****************************************
*  getPageCreatesPageIfDoesNotExist  *
*****************************************/

//	The DB_MPOOL_CREATE, DB_MPOOL_LAST, and DB_MPOOL_NEW flags are mutually exclusive.
//	DB_MPOOL_CREATE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL RPbdb_MemoryPoolFilePageSettingsController_getPageCreatesPageIfDoesNotExist( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	
	if (	memory_pool_file_page_settings_controller->get_page_creates_page_if_does_not_exist == TRUE )	{
		return DB_MPOOL_CREATE;
	}

	return FALSE;
}

	/*********************************************
	*  turnGetPageCreatesPageIfDoesNotExistOn  *
	*********************************************/

	void RPbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOn( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	
		memory_pool_file_page_settings_controller->get_page_creates_page_if_does_not_exist = TRUE;
		RPbdb_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOff( memory_pool_file_page_settings_controller );
		RPbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOff( memory_pool_file_page_settings_controller );
	}

	/*************************************************
	*  turnGetPageCreatesPageIfDoesNotExistOff  *
	*************************************************/

	void RPbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOff( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	
		memory_pool_file_page_settings_controller->get_page_creates_page_if_does_not_exist = FALSE;
	}

/*****************************************
*  getPageWritesCopyBeforeEviction  *
*****************************************/

//	The page will be modified and must be written to the source file before being evicted from the pool. 
//	For files open with the DB_MULTIVERSION flag set, a new copy of the page will be made if this is the first time the specified transaction is modifying it.
//	DB_MPOOL_DIRTY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL RPbdb_MemoryPoolFilePageSettingsController_getPageWritesCopyBeforeEviction( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	if (	memory_pool_file_page_settings_controller->get_page_writes_copy_before_eviction == TRUE )	{
		return DB_MPOOL_DIRTY;
	}

	return FALSE;
}

	/*********************************************
	*  turnGetPageWritesCopyBeforeEvictionOn  *
	*********************************************/

	void RPbdb_MemoryPoolFilePageSettingsController_turnGetPageWritesCopyBeforeEvictionOn( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_writes_copy_before_eviction = TRUE;
	}

	/*********************************************
	*  turnGetPageWritesCopyBeforeEvictionOff  *
	*********************************************/

	void RPbdb_MemoryPoolFilePageSettingsController_turnGetPageWritesCopyBeforeEvictionOff( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_writes_copy_before_eviction = FALSE;
	}

/*********************************************
*  getPageWritesBeforeEvictionWithoutCopy  *
*********************************************/

//	The page will be modified and must be written to the source file before being evicted from the pool. 
//	No copy of the page will be made, regardless of the DB_MULTIVERSION setting. 
//	This flag is only intended for use in situations where a transaction name is not available, such as during aborts or recovery.
//	DB_MPOOL_EDIT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL RPbdb_MemoryPoolFilePageSettingsController_getPageWritesBeforeEvictionWithoutCopy( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	if (	memory_pool_file_page_settings_controller->get_page_writes_before_eviction_without_copy == TRUE )	{
		return DB_MPOOL_EDIT;
	}

	return FALSE;
}

	/*************************************************************
	*  turnWriteBeforeEvictionButProhibitMultiversionCopyOn  *
	*************************************************************/

	void RPbdb_MemoryPoolFilePageSettingsController_turnWriteBeforeEvictionButProhibitMultiversionCopyOn( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_writes_before_eviction_without_copy = TRUE;
	}

	/*************************************************************
	*  turnWriteBeforeEvictionButProhibitMultiversionCopyOff  *
	*************************************************************/

	void RPbdb_MemoryPoolFilePageSettingsController_turnWriteBeforeEvictionButProhibitMultiversionCopyOff( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_writes_before_eviction_without_copy = FALSE;
	}
	
/*****************************
*  getPageReturnsLastPage  *
*****************************/

//	The DB_MPOOL_CREATE, DB_MPOOL_LAST, and DB_MPOOL_NEW flags are mutually exclusive.
//	Return the last page of the source file, and copy its page number into the memory location to which pgnoaddr refers.
//	DB_MPOOL_LAST		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL RPbdb_MemoryPoolFilePageSettingsController_getPageReturnsLastPage( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	if (	memory_pool_file_page_settings_controller->get_page_returns_last_page == TRUE )	{
		return DB_MPOOL_LAST;
	}

	return FALSE;
}

	/*************************************
	*  turnGetPageReturnsLastPageOn  *
	*************************************/

	void RPbdb_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOn( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_returns_last_page = TRUE;
		RPbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOff( memory_pool_file_page_settings_controller );
		RPbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOff( memory_pool_file_page_settings_controller );		
	}

	/*************************************
	*  turnGetPageReturnsLastPageOff  *
	*************************************/

	void RPbdb_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOff( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_returns_last_page = FALSE;
	}	
	
/*****************************
*  getPageCreatesNewPage  *
*****************************/

//	The DB_MPOOL_CREATE, DB_MPOOL_LAST, and DB_MPOOL_NEW flags are mutually exclusive.
//	Create a new page in the file, and copy its page number into the memory location to which pgnoaddr refers. 
//	In this case, the pgin method, if specified, is not called.
//	DB_MPOOL_NEW		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL RPbdb_MemoryPoolFilePageSettingsController_getPageCreatesNewPage( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	if (	memory_pool_file_page_settings_controller->get_page_creates_new_page == TRUE )	{
		return DB_MPOOL_NEW;
	}

	return FALSE;
}

	/*************************************
	*  turnGetPageCreatesNewPageOn  *
	*************************************/

	void RPbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOn( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_creates_new_page = TRUE;
		RPbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOff( memory_pool_file_page_settings_controller );
		RPbdb_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOff( memory_pool_file_page_settings_controller );
	}

	/*************************************
	*  turnGetPageCreatesNewPageOff  *
	*************************************/

	void RPbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOff( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_creates_new_page = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
	
/*************************************
*  retrievePageFromCacheFlags  *
*************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html.html
BOOL RPbdb_MemoryPoolFilePageSettingsController_internal_retrievePageFromCacheFlags( RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	
	return	RPbdb_MemoryPoolFilePageSettingsController_getPageCreatesPageIfDoesNotExist( memory_pool_file_page_settings_controller )
			|	RPbdb_MemoryPoolFilePageSettingsController_getPageWritesCopyBeforeEviction( memory_pool_file_page_settings_controller )
			|	RPbdb_MemoryPoolFilePageSettingsController_getPageWritesBeforeEvictionWithoutCopy( memory_pool_file_page_settings_controller )
			|	RPbdb_MemoryPoolFilePageSettingsController_getPageReturnsLastPage( memory_pool_file_page_settings_controller )
			|	RPbdb_MemoryPoolFilePageSettingsController_getPageCreatesNewPage( memory_pool_file_page_settings_controller );
	
}	

/*****************************
*  writePageToCacheFlags  *
*****************************/

BOOL RPbdb_MemoryPoolFilePageSettingsController_internal_writePageToCacheFlags( RPbdb_MemoryPoolFilePageSettingsController*		memory_pool_file_page_settings_controller __attribute__((unused)) )	{

	//	Currently unused - returns 0
	return RPBDB_NO_FLAGS;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_MemoryPoolFilePageSettingsController* RPbdb_MemoryPoolFilePageSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	RPbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller_copy	=	RPbdb_MemoryPoolFilePageSettingsController_new( memory_pool_file_page_settings_controller->parent_memory_pool_file_settings_controller );

	//	Instances and Pointers
	memory_pool_file_page_settings_controller_copy->get_page_returns_last_page	=	memory_pool_file_page_settings_controller->get_page_returns_last_page;
	memory_pool_file_page_settings_controller_copy->get_page_writes_copy_before_eviction	=	memory_pool_file_page_settings_controller->get_page_writes_copy_before_eviction;
	memory_pool_file_page_settings_controller_copy->get_page_creates_page_if_does_not_exist	=	memory_pool_file_page_settings_controller->get_page_creates_page_if_does_not_exist;
	memory_pool_file_page_settings_controller_copy->get_page_creates_new_page	=	memory_pool_file_page_settings_controller->get_page_creates_new_page;
	memory_pool_file_page_settings_controller_copy->get_page_writes_before_eviction_without_copy	=	memory_pool_file_page_settings_controller->get_page_writes_before_eviction_without_copy;

	return memory_pool_file_page_settings_controller_copy;
}

