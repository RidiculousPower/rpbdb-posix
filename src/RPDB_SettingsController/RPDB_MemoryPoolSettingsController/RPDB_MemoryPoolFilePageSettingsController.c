/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MemoryPoolFilePageSettingsController.h"

#include "RPDB_MemoryPoolFileSettingsController.h"

#include "RPDB_MemoryPoolFilePageSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_MemoryPoolFilePageSettingsController* RPDB_MemoryPoolFilePageSettingsController_new( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	RPDB_MemoryPoolFilePageSettingsController*		memory_pool_file_page_settings_controller = calloc( 1, sizeof( RPDB_MemoryPoolFileSettingsController ) );

	memory_pool_file_page_settings_controller->parent_memory_pool_file_settings_controller = memory_pool_file_settings_controller;

	return memory_pool_file_page_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_MemoryPoolFilePageSettingsController_free(	RPDB_MemoryPoolFilePageSettingsController** memory_pool_file_page_settings_controller )	{

	free( *memory_pool_file_page_settings_controller );
	*memory_pool_file_page_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MemoryPoolFilePageSettingsController_parentEnvironment(	RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	return memory_pool_file_page_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*****************************************
*  getPageCreatesPageIfDoesNotExist  *
*****************************************/

//	The DB_MPOOL_CREATE, DB_MPOOL_LAST, and DB_MPOOL_NEW flags are mutually exclusive.
//	DB_MPOOL_CREATE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL RPDB_MemoryPoolFilePageSettingsController_getPageCreatesPageIfDoesNotExist( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	
	if (	memory_pool_file_page_settings_controller->get_page_creates_page_if_does_not_exist == TRUE )	{
		return DB_MPOOL_CREATE;
	}

	return FALSE;
}

	/*********************************************
	*  turnGetPageCreatesPageIfDoesNotExistOn  *
	*********************************************/

	void RPDB_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOn( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	
		memory_pool_file_page_settings_controller->get_page_creates_page_if_does_not_exist = TRUE;
		RPDB_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOff( memory_pool_file_page_settings_controller );
		RPDB_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOff( memory_pool_file_page_settings_controller );
	}

	/*************************************************
	*  turnGetPageCreatesPageIfDoesNotExistOff  *
	*************************************************/

	void RPDB_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOff( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	
		memory_pool_file_page_settings_controller->get_page_creates_page_if_does_not_exist = FALSE;
	}

/*****************************************
*  getPageWritesCopyBeforeEviction  *
*****************************************/

//	The page will be modified and must be written to the source file before being evicted from the pool. 
//	For files open with the DB_MULTIVERSION flag set, a new copy of the page will be made if this is the first time the specified transaction is modifying it.
//	DB_MPOOL_DIRTY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL RPDB_MemoryPoolFilePageSettingsController_getPageWritesCopyBeforeEviction( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	if (	memory_pool_file_page_settings_controller->get_page_writes_copy_before_eviction == TRUE )	{
		return DB_MPOOL_DIRTY;
	}

	return FALSE;
}

	/*********************************************
	*  turnGetPageWritesCopyBeforeEvictionOn  *
	*********************************************/

	void RPDB_MemoryPoolFilePageSettingsController_turnGetPageWritesCopyBeforeEvictionOn( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_writes_copy_before_eviction = TRUE;
	}

	/*********************************************
	*  turnGetPageWritesCopyBeforeEvictionOff  *
	*********************************************/

	void RPDB_MemoryPoolFilePageSettingsController_turnGetPageWritesCopyBeforeEvictionOff( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_writes_copy_before_eviction = FALSE;
	}

/*********************************************
*  getPageWritesBeforeEvictionWithoutCopy  *
*********************************************/

//	The page will be modified and must be written to the source file before being evicted from the pool. 
//	No copy of the page will be made, regardless of the DB_MULTIVERSION setting. 
//	This flag is only intended for use in situations where a transaction name is not available, such as during aborts or recovery.
//	DB_MPOOL_EDIT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL RPDB_MemoryPoolFilePageSettingsController_getPageWritesBeforeEvictionWithoutCopy( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	if (	memory_pool_file_page_settings_controller->get_page_writes_before_eviction_without_copy == TRUE )	{
		return DB_MPOOL_EDIT;
	}

	return FALSE;
}

	/*************************************************************
	*  turnWriteBeforeEvictionButProhibitMultiversionCopyOn  *
	*************************************************************/

	void RPDB_MemoryPoolFilePageSettingsController_turnWriteBeforeEvictionButProhibitMultiversionCopyOn( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_writes_before_eviction_without_copy = TRUE;
	}

	/*************************************************************
	*  turnWriteBeforeEvictionButProhibitMultiversionCopyOff  *
	*************************************************************/

	void RPDB_MemoryPoolFilePageSettingsController_turnWriteBeforeEvictionButProhibitMultiversionCopyOff( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_writes_before_eviction_without_copy = FALSE;
	}
	
/*****************************
*  getPageReturnsLastPage  *
*****************************/

//	The DB_MPOOL_CREATE, DB_MPOOL_LAST, and DB_MPOOL_NEW flags are mutually exclusive.
//	Return the last page of the source file, and copy its page number into the memory location to which pgnoaddr refers.
//	DB_MPOOL_LAST		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL RPDB_MemoryPoolFilePageSettingsController_getPageReturnsLastPage( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	if (	memory_pool_file_page_settings_controller->get_page_returns_last_page == TRUE )	{
		return DB_MPOOL_LAST;
	}

	return FALSE;
}

	/*************************************
	*  turnGetPageReturnsLastPageOn  *
	*************************************/

	void RPDB_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOn( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_returns_last_page = TRUE;
		RPDB_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOff( memory_pool_file_page_settings_controller );
		RPDB_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOff( memory_pool_file_page_settings_controller );		
	}

	/*************************************
	*  turnGetPageReturnsLastPageOff  *
	*************************************/

	void RPDB_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOff( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_returns_last_page = FALSE;
	}	
	
/*****************************
*  getPageCreatesNewPage  *
*****************************/

//	The DB_MPOOL_CREATE, DB_MPOOL_LAST, and DB_MPOOL_NEW flags are mutually exclusive.
//	Create a new page in the file, and copy its page number into the memory location to which pgnoaddr refers. 
//	In this case, the pgin method, if specified, is not called.
//	DB_MPOOL_NEW		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL RPDB_MemoryPoolFilePageSettingsController_getPageCreatesNewPage( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	if (	memory_pool_file_page_settings_controller->get_page_creates_new_page == TRUE )	{
		return DB_MPOOL_NEW;
	}

	return FALSE;
}

	/*************************************
	*  turnGetPageCreatesNewPageOn  *
	*************************************/

	void RPDB_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOn( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_creates_new_page = TRUE;
		RPDB_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOff( memory_pool_file_page_settings_controller );
		RPDB_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOff( memory_pool_file_page_settings_controller );
	}

	/*************************************
	*  turnGetPageCreatesNewPageOff  *
	*************************************/

	void RPDB_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOff( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

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
BOOL RPDB_MemoryPoolFilePageSettingsController_internal_retrievePageFromCacheFlags( RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	
	return	RPDB_MemoryPoolFilePageSettingsController_getPageCreatesPageIfDoesNotExist( memory_pool_file_page_settings_controller )
			|	RPDB_MemoryPoolFilePageSettingsController_getPageWritesCopyBeforeEviction( memory_pool_file_page_settings_controller )
			|	RPDB_MemoryPoolFilePageSettingsController_getPageWritesBeforeEvictionWithoutCopy( memory_pool_file_page_settings_controller )
			|	RPDB_MemoryPoolFilePageSettingsController_getPageReturnsLastPage( memory_pool_file_page_settings_controller )
			|	RPDB_MemoryPoolFilePageSettingsController_getPageCreatesNewPage( memory_pool_file_page_settings_controller );
	
}	

/*****************************
*  writePageToCacheFlags  *
*****************************/

BOOL RPDB_MemoryPoolFilePageSettingsController_internal_writePageToCacheFlags( RPDB_MemoryPoolFilePageSettingsController*		memory_pool_file_page_settings_controller __attribute__((unused)) )	{

	//	Currently unused - returns 0
	return RPDB_NO_FLAGS;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_MemoryPoolFilePageSettingsController* RPDB_MemoryPoolFilePageSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	RPDB_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller_copy	=	RPDB_MemoryPoolFilePageSettingsController_new( memory_pool_file_page_settings_controller->parent_memory_pool_file_settings_controller );

	//	Instances and Pointers
	memory_pool_file_page_settings_controller_copy->get_page_returns_last_page	=	memory_pool_file_page_settings_controller->get_page_returns_last_page;
	memory_pool_file_page_settings_controller_copy->get_page_writes_copy_before_eviction	=	memory_pool_file_page_settings_controller->get_page_writes_copy_before_eviction;
	memory_pool_file_page_settings_controller_copy->get_page_creates_page_if_does_not_exist	=	memory_pool_file_page_settings_controller->get_page_creates_page_if_does_not_exist;
	memory_pool_file_page_settings_controller_copy->get_page_creates_new_page	=	memory_pool_file_page_settings_controller->get_page_creates_new_page;
	memory_pool_file_page_settings_controller_copy->get_page_writes_before_eviction_without_copy	=	memory_pool_file_page_settings_controller->get_page_writes_before_eviction_without_copy;

	return memory_pool_file_page_settings_controller_copy;
}

