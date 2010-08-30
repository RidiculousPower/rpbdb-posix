/*
 *		RPDB:RPDB_SettingsController:RPDB_MemoryPoolSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MemoryPoolSettingsController.h"

#include "RPDB_MemoryPoolFile.h"

#include "RPDB_MemoryPoolFileSettingsController.h"
#include "RPDB_MemoryPoolReadWriteSettingsController.h"
#include "RPDB_MemoryPoolSettingsController_internal.h"

#include "RPDB_SettingsController.h"
#include "RPDB_LogSettingsController.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_MemoryPoolSettingsController* RPDB_MemoryPoolSettingsController_new( RPDB_SettingsController* settings_controller )	{

	RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller = calloc( 1, sizeof( RPDB_MemoryPoolSettingsController ) );

	memory_pool_settings_controller->parent_settings_controller = settings_controller;

	RPDB_MemoryPoolSettingsController_internal_initDefaultSettings( memory_pool_settings_controller );

	return memory_pool_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_MemoryPoolSettingsController_free(	RPDB_MemoryPoolSettingsController** memory_pool_settings_controller )	{

	if ( ( *memory_pool_settings_controller )->file_settings_controller != NULL )	{
		RPDB_MemoryPoolFileSettingsController_free( & ( ( *memory_pool_settings_controller )->file_settings_controller ) );
	}
	
	free( *memory_pool_settings_controller );
	*memory_pool_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MemoryPoolSettingsController_parentEnvironment(	RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	return memory_pool_settings_controller->parent_settings_controller->parent_environment;
}


/*********
*  on  *
*********/

//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPDB_MemoryPoolSettingsController_on( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->on == TRUE )	{
		return DB_INIT_MPOOL;	
	}
	return FALSE;
}

/*************
*  off  *
*************/

//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
BOOL RPDB_MemoryPoolSettingsController_off( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->on == FALSE )	{
		return DB_INIT_MPOOL;	
	}
	return FALSE;
}

	/*************
	*  turnOn  *
	*************/

	//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_MemoryPoolSettingsController_turnOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->on = TRUE;
	}

	/*************
	*  turnOff  *
	*************/

	//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_MemoryPoolSettingsController_turnOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->on = FALSE;
	}

/**************************
*  isInMemoryEnvironment  *
**************************/

BOOL RPDB_MemoryPoolSettingsController_isInMemoryEnvironment( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	
	RPDB_LogSettingsController*	log_settings_controller	=	RPDB_SettingsController_logSettingsController( memory_pool_settings_controller->parent_settings_controller );
	
	//	does application have private environment access?
	//	is a temporary backing file disabled?
	//	check if logging is on; if it is, are we writing to files?
	if (			RPDB_MemoryPoolSettingsController_applicationHasExclusiveAccess( memory_pool_settings_controller )
			&&	RPDB_MemoryPoolSettingsController_doNotWriteToTemporaryBackingFile( memory_pool_settings_controller )
			&&	(	!		RPDB_LogSettingsController_logInMemory( log_settings_controller )
						||	RPDB_LogSettingsController_off( log_settings_controller ) ) )	{
		
		return TRUE;
	}
	return FALSE;
}

/*********************
*  memoryMapping  *
*********************/

//	DB_NOMMAP 				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
//	Note: function default inverts default from flag
int RPDB_MemoryPoolSettingsController_memoryMapping( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->memory_mapping == TRUE )	{
		return DB_NOMMAP;
	}
	return FALSE;
}

	/*****************************
	*  turnMemoryMappingOn  *
	*****************************/

	//	DB_NOMMAP 				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	//	Note: function default inverts default from flag
	void RPDB_MemoryPoolSettingsController_turnMemoryMappingOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->memory_mapping = TRUE;
	}

	/*****************************
	*  turnMemoryMappingOff  *
	*****************************/

	//	DB_NOMMAP 				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	//	Note: function default inverts default from flag
	void RPDB_MemoryPoolSettingsController_turnMemoryMappingOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->memory_mapping = FALSE;
	}

/*****************************************
*  doNotWriteToTemporaryBackingFile  *
*****************************************/

//	DB_MPOOL_NOFILE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
int RPDB_MemoryPoolSettingsController_doNotWriteToTemporaryBackingFile( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->do_not_write_to_temporary_backing_file == TRUE )	{
		return DB_MPOOL_NOFILE;
	}
	return FALSE;
}

	/*********************************************
	*  turnDoNotWriteToTemporaryBackingFileOn  *
	*********************************************/

	//	DB_MPOOL_NOFILE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	//	Note: method default inverts flag default
	void RPDB_MemoryPoolSettingsController_turnDoNotWriteToTemporaryBackingFileOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->do_not_write_to_temporary_backing_file = TRUE;
	}

	/*************************************************
	*  turnDoNotWriteToTemporaryBackingFileOff  *
	*************************************************/

	//	DB_MPOOL_NOFILE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	//	Note: method default inverts flag default
	void RPDB_MemoryPoolSettingsController_turnDoNotWriteToTemporaryBackingFileOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->do_not_write_to_temporary_backing_file = FALSE;
	}

/*************************************
*  removeFileWithLastReference  *
*************************************/

//	DB_MPOOL_UNLINK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
int RPDB_MemoryPoolSettingsController_removeFileWithLastReference( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->remove_file_with_last_reference == TRUE )	{
		return DB_MPOOL_UNLINK;
	}
	return FALSE;
}

	/*****************************************
	*  turnRemoveFileWithLastReferenceOn  *
	*****************************************/

	//	DB_MPOOL_UNLINK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	void RPDB_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->remove_file_with_last_reference = TRUE;
	}

	/*****************************************
	*  turnRemoveFileWithLastReferenceOff  *
	*****************************************/

	//	DB_MPOOL_UNLINK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	void RPDB_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->remove_file_with_last_reference = FALSE;
	}

/*********************************
*  useSystemMemoryForStorage  *
*********************************/

//	DB_SYSTEM_MEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPDB_MemoryPoolSettingsController_useSystemMemoryForStorage( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->use_system_memory_for_storage == TRUE )	{
		return DB_SYSTEM_MEM;
	}
	return FALSE;
}

	/*****************************************
	*  turnUseSystemMemoryForStorageOn  *
	*****************************************/

	//	DB_SYSTEM_MEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_MemoryPoolSettingsController_turnUseSystemMemoryForStorageOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->use_system_memory_for_storage = TRUE;
	}

	/*****************************************
	*  turnUseSystemMemoryForStorageOff  *
	*****************************************/

	//	DB_SYSTEM_MEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_MemoryPoolSettingsController_turnUseSystemMemoryForStorageOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->use_system_memory_for_storage = FALSE;
	}

/*************************************
*  applicationHasExclusiveAccess  *
*************************************/

//	DB_PRIVATE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPDB_MemoryPoolSettingsController_applicationHasExclusiveAccess( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->use_application_memory_for_storage == TRUE )	{
		return DB_PRIVATE;
	}
	return FALSE;
}

	/*********************************************
	*  turnApplicationHasExclusiveAccessOn  *
	*********************************************/

	//	DB_PRIVATE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_MemoryPoolSettingsController_turnApplicationHasExclusiveAccessOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->use_application_memory_for_storage = TRUE;
	}

	/*********************************************
	*  turnApplicationHasExclusiveAccessOff  *
	*********************************************/

	//	DB_PRIVATE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_MemoryPoolSettingsController_turnApplicationHasExclusiveAccessOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->use_application_memory_for_storage = FALSE;
	}
	
/*****************************************
*  databaseAllocatesMemoryUsingMalloc  *
*****************************************/

//	DB_DBT_MALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int RPDB_MemoryPoolSettingsController_databaseAllocatesMemoryUsingMalloc( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->database_allocates_memory_using_malloc == TRUE )	{
		return DB_DBT_MALLOC;
	}
	return FALSE;
}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOn  *
	*************************************************/

	//	DB_DBT_MALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( memory_pool_settings_controller );
		RPDB_MemoryPoolSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_settings_controller );
		RPDB_MemoryPoolSettingsController_turnDatabaseFreesMemoryOff( memory_pool_settings_controller );
		memory_pool_settings_controller->database_allocates_memory_using_malloc = TRUE;
	}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOff  *
	*************************************************/

	//	DB_DBT_MALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->database_allocates_memory_using_malloc = FALSE;
	}

/********************************************
*  databaseAllocatesMemoryUsingRealloc  *
********************************************/

//	DB_DBT_REALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int RPDB_MemoryPoolSettingsController_databaseAllocatesMemoryUsingRealloc( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	if ( memory_pool_settings_controller->database_allocates_memory_using_realloc == TRUE )	{
		return DB_DBT_REALLOC;
	}
	return FALSE;
}

	/****************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOn  *
	****************************************************/

	//	DB_DBT_REALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( memory_pool_settings_controller );
		RPDB_MemoryPoolSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_settings_controller );
		RPDB_MemoryPoolSettingsController_turnDatabaseFreesMemoryOff( memory_pool_settings_controller );
		memory_pool_settings_controller->database_allocates_memory_using_realloc = TRUE;
	}

	/****************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOff  *
	****************************************************/

	//	DB_DBT_REALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->database_allocates_memory_using_realloc = FALSE;
	}

/************************************
*  applicationAllocatesMemory  *
************************************/

//	DB_DBT_USERMEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int RPDB_MemoryPoolSettingsController_applicationAllocatesMemory( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	if ( memory_pool_settings_controller->application_allocates_memory == TRUE )	{
		return DB_DBT_USERMEM;
	}
	return FALSE;
}

	/****************************************
	*  turnApplicationAllocatesMemoryOn  *
	****************************************/

	//	DB_DBT_USERMEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolSettingsController_turnApplicationAllocatesMemoryOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( memory_pool_settings_controller );
		RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( memory_pool_settings_controller );
		RPDB_MemoryPoolSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_settings_controller );
		RPDB_MemoryPoolSettingsController_turnDatabaseFreesMemoryOff( memory_pool_settings_controller );
		memory_pool_settings_controller->application_allocates_memory = TRUE;
	}

	/****************************************
	*  turnApplicationAllocatesMemoryOff  *
	****************************************/

	//	DB_DBT_USERMEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolSettingsController_turnApplicationAllocatesMemoryOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->application_allocates_memory = FALSE;
	}

/******************************
*  databaseFreesMemory  *
******************************/

//	DB_DBT_APPMALLOC	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int RPDB_MemoryPoolSettingsController_databaseFreesMemory( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	if ( memory_pool_settings_controller->database_free_memory == TRUE )	{
		return DB_DBT_APPMALLOC;
	}
	return FALSE;
}

	/**********************************
	*  turnDatabaseFreesMemoryOn  *
	**********************************/

	//	DB_DBT_APPMALLOC	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolSettingsController_turnDatabaseFreesMemoryOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( memory_pool_settings_controller );
		RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( memory_pool_settings_controller );
		RPDB_MemoryPoolSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_settings_controller );
		memory_pool_settings_controller->database_free_memory = TRUE;
	}

	/**************************************
	*  turnDatabaseFreesMemoryOff  *
	**************************************/

	//	DB_DBT_APPMALLOC	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolSettingsController_turnDatabaseFreesMemoryOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->database_free_memory = FALSE;
	}

/******************************************
*  pagesizeFactorMismatchShouldFail  *
******************************************/

//	Attempts to open files which are not a multiple of the page size in length will fail, by default. 
//	If the DB_ODDFILESIZE flag is set, any partial page at the end of the file will be ignored and the open will proceed.
//	DB_ODDFILESIZE	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fopen.html
int RPDB_MemoryPoolSettingsController_pagesizeFactorMismatchShouldFail( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	if ( memory_pool_settings_controller->pagesize_factor_mismatch_should_fail == TRUE )	{
		return DB_ODDFILESIZE;
	}
	return FALSE;
}

	/**************************************************
	*  turnPageSizeFactorMismatchShouldFailOn  *
	**************************************************/

	void RPDB_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

		memory_pool_settings_controller->pagesize_factor_mismatch_should_fail = TRUE;
	}

	/**************************************************
	*  turnPageSizeFactorMismatchShouldFailOff  *
	**************************************************/

	void RPDB_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

		memory_pool_settings_controller->pagesize_factor_mismatch_should_fail = FALSE;
	}


/**************************************************
*  fileSettingsController  *
**************************************************/

RPDB_MemoryPoolFileSettingsController* RPDB_MemoryPoolSettingsController_fileSettingsController( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	if ( memory_pool_settings_controller->file_settings_controller == NULL )	{
		memory_pool_settings_controller->file_settings_controller = RPDB_MemoryPoolFileSettingsController_new( memory_pool_settings_controller );
	}
	return memory_pool_settings_controller->file_settings_controller;
}

/**************************************************
*  readWriteSettingsController  *
**************************************************/

RPDB_MemoryPoolReadWriteSettingsController* RPDB_MemoryPoolSettingsController_readWriteSettingsController( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	
	if ( memory_pool_settings_controller->read_write_settings_controller == NULL )	{
		memory_pool_settings_controller->read_write_settings_controller = RPDB_MemoryPoolReadWriteSettingsController_new( memory_pool_settings_controller );
	}
	return memory_pool_settings_controller->read_write_settings_controller;
}



/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/****************************
*  initDefaultSettings  *
****************************/

void RPDB_MemoryPoolSettingsController_internal_initDefaultSettings( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	memory_pool_settings_controller->on											= FALSE;
	memory_pool_settings_controller->memory_mapping								= FALSE;
	memory_pool_settings_controller->remove_file_with_last_reference 			= FALSE;
	memory_pool_settings_controller->threaded									= FALSE;
	memory_pool_settings_controller->database_allocates_memory_using_malloc 	= FALSE;
	memory_pool_settings_controller->database_allocates_memory_using_realloc	= FALSE;
	memory_pool_settings_controller->application_allocates_memory				= FALSE;
	memory_pool_settings_controller->database_free_memory						= FALSE;
	
	memory_pool_settings_controller->do_not_write_to_temporary_backing_file						= FALSE;

}

/*****************
*  closeFlags  *
*****************/

int RPDB_MemoryPoolSettingsController_internal_closeFlags( RPDB_MemoryPoolFile* memory_pool_file __attribute__((unused)) )	{

	//	Not currently used - returns 0
	return RPDB_NO_FLAGS;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_MemoryPoolSettingsController* RPDB_MemoryPoolSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	RPDB_MemoryPoolSettingsController* memory_pool_settings_controller_copy	=	RPDB_MemoryPoolSettingsController_new( memory_pool_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	memory_pool_settings_controller_copy->database_allocates_memory_using_malloc	=	memory_pool_settings_controller->database_allocates_memory_using_malloc;
	memory_pool_settings_controller_copy->threaded	=	memory_pool_settings_controller->threaded;
	memory_pool_settings_controller_copy->use_system_memory_for_storage	=	memory_pool_settings_controller->use_system_memory_for_storage;
	memory_pool_settings_controller_copy->database_allocates_memory_using_realloc	=	memory_pool_settings_controller->database_allocates_memory_using_realloc;
	memory_pool_settings_controller_copy->pagesize_factor_mismatch_should_fail	=	memory_pool_settings_controller->pagesize_factor_mismatch_should_fail;
	memory_pool_settings_controller_copy->database_free_memory	=	memory_pool_settings_controller->database_free_memory;
	memory_pool_settings_controller_copy->application_allocates_memory	=	memory_pool_settings_controller->application_allocates_memory;
	memory_pool_settings_controller_copy->use_application_memory_for_storage	=	memory_pool_settings_controller->use_application_memory_for_storage;
	memory_pool_settings_controller_copy->memory_mapping	=	memory_pool_settings_controller->memory_mapping;
	memory_pool_settings_controller_copy->do_not_write_to_temporary_backing_file	=	memory_pool_settings_controller->do_not_write_to_temporary_backing_file;
	memory_pool_settings_controller_copy->on	=	memory_pool_settings_controller->on;
	memory_pool_settings_controller_copy->remove_file_with_last_reference	=	memory_pool_settings_controller->remove_file_with_last_reference;

	return memory_pool_settings_controller_copy;
}

