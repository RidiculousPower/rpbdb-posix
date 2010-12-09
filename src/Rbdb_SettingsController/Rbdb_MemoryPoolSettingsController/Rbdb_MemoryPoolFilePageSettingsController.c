/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_MemoryPoolFilePageSettingsController.h"

#include "Rbdb_MemoryPoolFileSettingsController.h"

#include "Rbdb_MemoryPoolFilePageSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
Rbdb_MemoryPoolFilePageSettingsController* Rbdb_MemoryPoolFilePageSettingsController_new( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	Rbdb_MemoryPoolFilePageSettingsController*		memory_pool_file_page_settings_controller = calloc( 1, sizeof( Rbdb_MemoryPoolFileSettingsController ) );

	memory_pool_file_page_settings_controller->parent_memory_pool_file_settings_controller = memory_pool_file_settings_controller;

	return memory_pool_file_page_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_MemoryPoolFilePageSettingsController_free(	Rbdb_MemoryPoolFilePageSettingsController** memory_pool_file_page_settings_controller )	{

	free( *memory_pool_file_page_settings_controller );
	*memory_pool_file_page_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_MemoryPoolFilePageSettingsController_parentEnvironment(	Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	return memory_pool_file_page_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*****************************************
*  getPageCreatesPageIfDoesNotExist  *
*****************************************/

//	The DB_MPOOL_CREATE, DB_MPOOL_LAST, and DB_MPOOL_NEW flags are mutually exclusive.
//	DB_MPOOL_CREATE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL Rbdb_MemoryPoolFilePageSettingsController_getPageCreatesPageIfDoesNotExist( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	
	if (	memory_pool_file_page_settings_controller->get_page_creates_page_if_does_not_exist == TRUE )	{
		return DB_MPOOL_CREATE;
	}

	return FALSE;
}

	/*********************************************
	*  turnGetPageCreatesPageIfDoesNotExistOn  *
	*********************************************/

	void Rbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOn( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	
		memory_pool_file_page_settings_controller->get_page_creates_page_if_does_not_exist = TRUE;
		Rbdb_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOff( memory_pool_file_page_settings_controller );
		Rbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOff( memory_pool_file_page_settings_controller );
	}

	/*************************************************
	*  turnGetPageCreatesPageIfDoesNotExistOff  *
	*************************************************/

	void Rbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOff( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	
		memory_pool_file_page_settings_controller->get_page_creates_page_if_does_not_exist = FALSE;
	}

/*****************************************
*  getPageWritesCopyBeforeEviction  *
*****************************************/

//	The page will be modified and must be written to the source file before being evicted from the pool. 
//	For files open with the DB_MULTIVERSION flag set, a new copy of the page will be made if this is the first time the specified transaction is modifying it.
//	DB_MPOOL_DIRTY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL Rbdb_MemoryPoolFilePageSettingsController_getPageWritesCopyBeforeEviction( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	if (	memory_pool_file_page_settings_controller->get_page_writes_copy_before_eviction == TRUE )	{
		return DB_MPOOL_DIRTY;
	}

	return FALSE;
}

	/*********************************************
	*  turnGetPageWritesCopyBeforeEvictionOn  *
	*********************************************/

	void Rbdb_MemoryPoolFilePageSettingsController_turnGetPageWritesCopyBeforeEvictionOn( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_writes_copy_before_eviction = TRUE;
	}

	/*********************************************
	*  turnGetPageWritesCopyBeforeEvictionOff  *
	*********************************************/

	void Rbdb_MemoryPoolFilePageSettingsController_turnGetPageWritesCopyBeforeEvictionOff( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_writes_copy_before_eviction = FALSE;
	}

/*********************************************
*  getPageWritesBeforeEvictionWithoutCopy  *
*********************************************/

//	The page will be modified and must be written to the source file before being evicted from the pool. 
//	No copy of the page will be made, regardless of the DB_MULTIVERSION setting. 
//	This flag is only intended for use in situations where a transaction name is not available, such as during aborts or recovery.
//	DB_MPOOL_EDIT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL Rbdb_MemoryPoolFilePageSettingsController_getPageWritesBeforeEvictionWithoutCopy( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	if (	memory_pool_file_page_settings_controller->get_page_writes_before_eviction_without_copy == TRUE )	{
		return DB_MPOOL_EDIT;
	}

	return FALSE;
}

	/*************************************************************
	*  turnWriteBeforeEvictionButProhibitMultiversionCopyOn  *
	*************************************************************/

	void Rbdb_MemoryPoolFilePageSettingsController_turnWriteBeforeEvictionButProhibitMultiversionCopyOn( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_writes_before_eviction_without_copy = TRUE;
	}

	/*************************************************************
	*  turnWriteBeforeEvictionButProhibitMultiversionCopyOff  *
	*************************************************************/

	void Rbdb_MemoryPoolFilePageSettingsController_turnWriteBeforeEvictionButProhibitMultiversionCopyOff( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_writes_before_eviction_without_copy = FALSE;
	}
	
/*****************************
*  getPageReturnsLastPage  *
*****************************/

//	The DB_MPOOL_CREATE, DB_MPOOL_LAST, and DB_MPOOL_NEW flags are mutually exclusive.
//	Return the last page of the source file, and copy its page number into the memory location to which pgnoaddr refers.
//	DB_MPOOL_LAST		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL Rbdb_MemoryPoolFilePageSettingsController_getPageReturnsLastPage( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	if (	memory_pool_file_page_settings_controller->get_page_returns_last_page == TRUE )	{
		return DB_MPOOL_LAST;
	}

	return FALSE;
}

	/*************************************
	*  turnGetPageReturnsLastPageOn  *
	*************************************/

	void Rbdb_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOn( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_returns_last_page = TRUE;
		Rbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOff( memory_pool_file_page_settings_controller );
		Rbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOff( memory_pool_file_page_settings_controller );		
	}

	/*************************************
	*  turnGetPageReturnsLastPageOff  *
	*************************************/

	void Rbdb_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOff( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_returns_last_page = FALSE;
	}	
	
/*****************************
*  getPageCreatesNewPage  *
*****************************/

//	The DB_MPOOL_CREATE, DB_MPOOL_LAST, and DB_MPOOL_NEW flags are mutually exclusive.
//	Create a new page in the file, and copy its page number into the memory location to which pgnoaddr refers. 
//	In this case, the pgin method, if specified, is not called.
//	DB_MPOOL_NEW		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fget.html
BOOL Rbdb_MemoryPoolFilePageSettingsController_getPageCreatesNewPage( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	if (	memory_pool_file_page_settings_controller->get_page_creates_new_page == TRUE )	{
		return DB_MPOOL_NEW;
	}

	return FALSE;
}

	/*************************************
	*  turnGetPageCreatesNewPageOn  *
	*************************************/

	void Rbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOn( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

		memory_pool_file_page_settings_controller->get_page_creates_new_page = TRUE;
		Rbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesPageIfDoesNotExistOff( memory_pool_file_page_settings_controller );
		Rbdb_MemoryPoolFilePageSettingsController_turnGetPageReturnsLastPageOff( memory_pool_file_page_settings_controller );
	}

	/*************************************
	*  turnGetPageCreatesNewPageOff  *
	*************************************/

	void Rbdb_MemoryPoolFilePageSettingsController_turnGetPageCreatesNewPageOff( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

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
BOOL Rbdb_MemoryPoolFilePageSettingsController_internal_retrievePageFromCacheFlags( Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{
	
	return	Rbdb_MemoryPoolFilePageSettingsController_getPageCreatesPageIfDoesNotExist( memory_pool_file_page_settings_controller )
			|	Rbdb_MemoryPoolFilePageSettingsController_getPageWritesCopyBeforeEviction( memory_pool_file_page_settings_controller )
			|	Rbdb_MemoryPoolFilePageSettingsController_getPageWritesBeforeEvictionWithoutCopy( memory_pool_file_page_settings_controller )
			|	Rbdb_MemoryPoolFilePageSettingsController_getPageReturnsLastPage( memory_pool_file_page_settings_controller )
			|	Rbdb_MemoryPoolFilePageSettingsController_getPageCreatesNewPage( memory_pool_file_page_settings_controller );
	
}	

/*****************************
*  writePageToCacheFlags  *
*****************************/

BOOL Rbdb_MemoryPoolFilePageSettingsController_internal_writePageToCacheFlags( Rbdb_MemoryPoolFilePageSettingsController*		memory_pool_file_page_settings_controller __attribute__((unused)) )	{

	//	Currently unused - returns 0
	return Rbdb_NO_FLAGS;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_MemoryPoolFilePageSettingsController* Rbdb_MemoryPoolFilePageSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller )	{

	Rbdb_MemoryPoolFilePageSettingsController* memory_pool_file_page_settings_controller_copy	=	Rbdb_MemoryPoolFilePageSettingsController_new( memory_pool_file_page_settings_controller->parent_memory_pool_file_settings_controller );

	//	Instances and Pointers
	memory_pool_file_page_settings_controller_copy->get_page_returns_last_page	=	memory_pool_file_page_settings_controller->get_page_returns_last_page;
	memory_pool_file_page_settings_controller_copy->get_page_writes_copy_before_eviction	=	memory_pool_file_page_settings_controller->get_page_writes_copy_before_eviction;
	memory_pool_file_page_settings_controller_copy->get_page_creates_page_if_does_not_exist	=	memory_pool_file_page_settings_controller->get_page_creates_page_if_does_not_exist;
	memory_pool_file_page_settings_controller_copy->get_page_creates_new_page	=	memory_pool_file_page_settings_controller->get_page_creates_new_page;
	memory_pool_file_page_settings_controller_copy->get_page_writes_before_eviction_without_copy	=	memory_pool_file_page_settings_controller->get_page_writes_before_eviction_without_copy;

	return memory_pool_file_page_settings_controller_copy;
}

