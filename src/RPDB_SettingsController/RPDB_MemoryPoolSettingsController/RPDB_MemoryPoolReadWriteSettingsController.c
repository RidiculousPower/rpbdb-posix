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

#include "RPDB_MemoryPoolReadWriteSettingsController.h"

#include "RPDB_SettingsController.h"
#include "RPDB_LogSettingsController.h"

#include "RPDB_Environment.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_MemoryPoolReadWriteSettingsController* RPDB_MemoryPoolReadWriteSettingsController_new( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	
	RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller = calloc( 1, sizeof( RPDB_MemoryPoolReadWriteSettingsController ) );

	memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller = memory_pool_settings_controller;

	memory_pool_read_write_settings_controller->database_allocates_memory_using_malloc 	= FALSE;
	memory_pool_read_write_settings_controller->database_allocates_memory_using_realloc	= FALSE;
	memory_pool_read_write_settings_controller->application_allocates_memory				= FALSE;
	memory_pool_read_write_settings_controller->database_free_memory						= FALSE;	
	memory_pool_read_write_settings_controller->do_not_write_to_temporary_backing_file						= FALSE;

	return memory_pool_read_write_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_MemoryPoolReadWriteSettingsController_free(	RPDB_MemoryPoolReadWriteSettingsController** memory_pool_read_write_settings_controller )	{

	free( memory_pool_read_write_settings_controller );
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MemoryPoolReadWriteSettingsController_parentEnvironment(	RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	return memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
}

/*********************
*  maxOpenFiles  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_openfd.html
int RPDB_MemoryPoolReadWriteSettingsController_maxOpenFiles( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	RPDB_Environment*	environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
	
	if (	memory_pool_read_write_settings_controller->max_open_files == RPDB_UNITIALIZED
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_mp_max_openfd(	environment->wrapped_bdb_environment, 
										&( memory_pool_read_write_settings_controller->max_open_files ) );
	}
	
	return memory_pool_read_write_settings_controller->max_open_files;
}

/*************************
*  setMaxOpenFiles  *
*************************/

void RPDB_MemoryPoolReadWriteSettingsController_setMaxOpenFiles( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller, int max_open_files )	{

	RPDB_Environment*		environment;
	
	environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->set_mp_max_openfd( environment->wrapped_bdb_environment, max_open_files );
	}
	
	memory_pool_read_write_settings_controller->max_open_files = max_open_files;
}

/*****************************
*  maxSequentialWrites  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_maxwrite.html
int RPDB_MemoryPoolReadWriteSettingsController_maxSequentialWrites( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	
	RPDB_Environment*		environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
		
	if (	memory_pool_read_write_settings_controller->max_sequential_writes == RPDB_UNITIALIZED
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_mp_max_write(	environment->wrapped_bdb_environment, 
										&( memory_pool_read_write_settings_controller->max_sequential_writes ), 
										&( memory_pool_read_write_settings_controller->time_to_sleep_before_next_write ) );
	}
	
	return memory_pool_read_write_settings_controller->max_sequential_writes;
}

/*****************************
*  setMaxSequentialWrites  *
*****************************/

void RPDB_MemoryPoolReadWriteSettingsController_setMaxSequentialWrites( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller, int max_sequential_writes )	{

	RPDB_Environment*		environment;
	
	environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_mp_max_write(	environment->wrapped_bdb_environment, 
																max_sequential_writes, 
																memory_pool_read_write_settings_controller->time_to_sleep_before_next_write );
	}
	
	memory_pool_read_write_settings_controller->max_sequential_writes = max_sequential_writes;
}

/************************************
*  timeToSleepBeforeNextWrite  *
************************************/

int RPDB_MemoryPoolReadWriteSettingsController_timeToSleepBeforeNextWrite( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	RPDB_Environment*		environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
	
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_mp_max_write(	environment->wrapped_bdb_environment, 
										&( memory_pool_read_write_settings_controller->max_sequential_writes ), 
										&( memory_pool_read_write_settings_controller->time_to_sleep_before_next_write ) );
	}
	
	return memory_pool_read_write_settings_controller->time_to_sleep_before_next_write;
}

/****************************************
*  setTimeToSleepBeforeNextWrite  *
****************************************/

void RPDB_MemoryPoolReadWriteSettingsController_setTimeToSleepBeforeNextWrite( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller, db_timeout_t time_to_sleep_before_next_write )	{

	RPDB_Environment*		environment;
	
	environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_mp_max_write(	environment->wrapped_bdb_environment, 
																memory_pool_read_write_settings_controller->max_sequential_writes, 
																time_to_sleep_before_next_write );
	}
	
	memory_pool_read_write_settings_controller->time_to_sleep_before_next_write = time_to_sleep_before_next_write;
}

/************************
*  maxMappedDBSize  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_mp_mmapsize.html
size_t RPDB_MemoryPoolReadWriteSettingsController_maxMappedDatabaseSize( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	RPDB_Environment*		environment;
	
	environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_mp_mmapsize(	environment->wrapped_bdb_environment,
																														&( memory_pool_read_write_settings_controller->max_mapped_db_size ) );
	}
	
	return memory_pool_read_write_settings_controller->max_mapped_db_size;
}

/****************************
*  setMaxMappedDBSize  *
****************************/

void RPDB_MemoryPoolReadWriteSettingsController_setMaxMappedDatabaseSize(	RPDB_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller, 
																																					size_t																				max_mapped_db_size )	{

	RPDB_Environment*		environment;
	
	environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;

	memory_pool_read_write_settings_controller->max_mapped_db_size = max_mapped_db_size;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_mp_mmapsize(	environment->wrapped_bdb_environment, 
																														memory_pool_read_write_settings_controller->max_mapped_db_size );
	}
	
}

/*****************************
*  pagefaultSharedRegions  *
*****************************/

//	DB_REGION_INIT          http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
BOOL RPDB_MemoryPoolReadWriteSettingsController_pagefaultSharedRegions( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->page_fault_shared_regions == TRUE )	{
		return DB_REGION_INIT;	
	}
	return FALSE;
}

	/*************************************
	*  turnPagefaultSharedRegionsOn  *
	*************************************/

	//	DB_REGION_INIT          http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->page_fault_shared_regions = TRUE;
	}

	/*************************************
	*  turnPagefaultSharedRegionsOff  *
	*************************************/

	//	DB_REGION_INIT          http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->page_fault_shared_regions = FALSE;
	}

/*********************************
*  useSystemMemoryForStorage  *
*********************************/

//	DB_SYSTEM_MEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPDB_MemoryPoolReadWriteSettingsController_useSystemMemoryForStorage( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->use_system_memory_for_storage == TRUE )	{
		return DB_SYSTEM_MEM;
	}
	return FALSE;
}

	/*****************************************
	*  turnUseSystemMemoryForStorageOn  *
	*****************************************/

	//	DB_SYSTEM_MEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnUseSystemMemoryForStorageOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->use_system_memory_for_storage = TRUE;
	}

	/*****************************************
	*  turnUseSystemMemoryForStorageOff  *
	*****************************************/

	//	DB_SYSTEM_MEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnUseSystemMemoryForStorageOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->use_system_memory_for_storage = FALSE;
	}

/*************************************
*  applicationHasExclusiveAccess  *
*************************************/

//	DB_PRIVATE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPDB_MemoryPoolReadWriteSettingsController_applicationHasExclusiveAccess( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->use_application_memory_for_storage == TRUE )	{
		return DB_PRIVATE;
	}
	return FALSE;
}

	/*********************************************
	*  turnApplicationHasExclusiveAccessOn  *
	*********************************************/

	//	DB_PRIVATE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->use_application_memory_for_storage = TRUE;
	}

	/*********************************************
	*  turnApplicationHasExclusiveAccessOff  *
	*********************************************/

	//	DB_PRIVATE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->use_application_memory_for_storage = FALSE;
	}
	
/*****************************************
*  databaseAllocatesMemoryUsingMalloc  *
*****************************************/

//	DB_DBT_MALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int RPDB_MemoryPoolReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->database_allocates_memory_using_malloc == TRUE )	{
		return DB_DBT_MALLOC;
	}
	return FALSE;
}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOn  *
	*************************************************/

	//	DB_DBT_MALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( memory_pool_read_write_settings_controller );
		RPDB_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_read_write_settings_controller );
		RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( memory_pool_read_write_settings_controller );
		memory_pool_read_write_settings_controller->database_allocates_memory_using_malloc = TRUE;
	}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOff  *
	*************************************************/

	//	DB_DBT_MALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->database_allocates_memory_using_malloc = FALSE;
	}

/********************************************
*  databaseAllocatesMemoryUsingRealloc  *
********************************************/

//	DB_DBT_REALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int RPDB_MemoryPoolReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	if ( memory_pool_read_write_settings_controller->database_allocates_memory_using_realloc == TRUE )	{
		return DB_DBT_REALLOC;
	}
	return FALSE;
}

	/****************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOn  *
	****************************************************/

	//	DB_DBT_REALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( memory_pool_read_write_settings_controller );
		RPDB_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_read_write_settings_controller );
		RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( memory_pool_read_write_settings_controller );
		memory_pool_read_write_settings_controller->database_allocates_memory_using_realloc = TRUE;
	}

	/****************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOff  *
	****************************************************/

	//	DB_DBT_REALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->database_allocates_memory_using_realloc = FALSE;
	}

/************************************
*  applicationAllocatesMemory  *
************************************/

//	DB_DBT_USERMEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int RPDB_MemoryPoolReadWriteSettingsController_applicationAllocatesMemory( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	if ( memory_pool_read_write_settings_controller->application_allocates_memory == TRUE )	{
		return DB_DBT_USERMEM;
	}
	return FALSE;
}

	/****************************************
	*  turnApplicationAllocatesMemoryOn  *
	****************************************/

	//	DB_DBT_USERMEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( memory_pool_read_write_settings_controller );
		RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( memory_pool_read_write_settings_controller );
		RPDB_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_read_write_settings_controller );
		RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( memory_pool_read_write_settings_controller );
		memory_pool_read_write_settings_controller->application_allocates_memory = TRUE;
	}

	/****************************************
	*  turnApplicationAllocatesMemoryOff  *
	****************************************/

	//	DB_DBT_USERMEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->application_allocates_memory = FALSE;
	}

/******************************
*  databaseFreesMemory  *
******************************/

//	DB_DBT_APPMALLOC	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int RPDB_MemoryPoolReadWriteSettingsController_databaseFreesMemory( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	if ( memory_pool_read_write_settings_controller->database_free_memory == TRUE )	{
		return DB_DBT_APPMALLOC;
	}
	return FALSE;
}

	/**********************************
	*  turnDatabaseFreesMemoryOn  *
	**********************************/

	//	DB_DBT_APPMALLOC	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( memory_pool_read_write_settings_controller );
		RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( memory_pool_read_write_settings_controller );
		RPDB_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_read_write_settings_controller );
		memory_pool_read_write_settings_controller->database_free_memory = TRUE;
	}

	/**************************************
	*  turnDatabaseFreesMemoryOff  *
	**************************************/

	//	DB_DBT_APPMALLOC	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->database_free_memory = FALSE;
	}


/*****************************************
*  doNotWriteToTemporaryBackingFile  *
*****************************************/

//	DB_MPOOL_NOFILE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
int RPDB_MemoryPoolReadWriteSettingsController_doNotWriteToTemporaryBackingFile( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->do_not_write_to_temporary_backing_file == TRUE )	{
		return DB_MPOOL_NOFILE;
	}
	return FALSE;
}

	/*********************************************
	*  turnDoNotWriteToTemporaryBackingFileOn  *
	*********************************************/

	//	DB_MPOOL_NOFILE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	//	Note: method default inverts flag default
	void RPDB_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOn( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->do_not_write_to_temporary_backing_file = TRUE;
	}

	/*************************************************
	*  turnDoNotWriteToTemporaryBackingFileOff  *
	*************************************************/

	//	DB_MPOOL_NOFILE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	//	Note: method default inverts flag default
	void RPDB_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOff( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->do_not_write_to_temporary_backing_file = FALSE;
	}

/**************************
*  isInMemoryEnvironment  *
**************************/

BOOL RPDB_MemoryPoolReadWriteSettingsController_isInMemoryEnvironment( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	
	RPDB_LogSettingsController*	log_settings_controller	=	RPDB_SettingsController_logSettingsController( memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller );
	
	//	does application have private environment access?
	//	is a temporary backing file disabled?
	//	check if logging is on; if it is, are we writing to files?
	if (			RPDB_MemoryPoolReadWriteSettingsController_applicationHasExclusiveAccess( memory_pool_read_write_settings_controller )
			&&	RPDB_MemoryPoolReadWriteSettingsController_doNotWriteToTemporaryBackingFile( memory_pool_read_write_settings_controller )
			&&	(	!		RPDB_LogSettingsController_logInMemory( log_settings_controller )
						||	RPDB_LogSettingsController_off( log_settings_controller ) ) )	{
		
		return TRUE;
	}
	return FALSE;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_MemoryPoolReadWriteSettingsController* RPDB_MemoryPoolReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller_copy	=	RPDB_MemoryPoolReadWriteSettingsController_new( memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller );

	//	Instances and Pointers
	memory_pool_read_write_settings_controller_copy->time_to_sleep_before_next_write	=	memory_pool_read_write_settings_controller->time_to_sleep_before_next_write;
	memory_pool_read_write_settings_controller_copy->max_sequential_writes	=	memory_pool_read_write_settings_controller->max_sequential_writes;
	memory_pool_read_write_settings_controller_copy->max_mapped_db_size	=	memory_pool_read_write_settings_controller->max_mapped_db_size;
	memory_pool_read_write_settings_controller_copy->page_fault_shared_regions	=	memory_pool_read_write_settings_controller->page_fault_shared_regions;
	memory_pool_read_write_settings_controller_copy->max_open_files	=	memory_pool_read_write_settings_controller->max_open_files;

	memory_pool_read_write_settings_controller_copy->database_allocates_memory_using_malloc	=	memory_pool_read_write_settings_controller->database_allocates_memory_using_malloc;
	memory_pool_read_write_settings_controller_copy->use_system_memory_for_storage	=	memory_pool_read_write_settings_controller->use_system_memory_for_storage;
	memory_pool_read_write_settings_controller_copy->database_allocates_memory_using_realloc	=	memory_pool_read_write_settings_controller->database_allocates_memory_using_realloc;
	memory_pool_read_write_settings_controller_copy->database_free_memory	=	memory_pool_read_write_settings_controller->database_free_memory;
	memory_pool_read_write_settings_controller_copy->application_allocates_memory	=	memory_pool_read_write_settings_controller->application_allocates_memory;
	memory_pool_read_write_settings_controller_copy->use_application_memory_for_storage	=	memory_pool_read_write_settings_controller->use_application_memory_for_storage;
	memory_pool_read_write_settings_controller_copy->do_not_write_to_temporary_backing_file	=	memory_pool_read_write_settings_controller->do_not_write_to_temporary_backing_file;

	return memory_pool_read_write_settings_controller_copy;
}

