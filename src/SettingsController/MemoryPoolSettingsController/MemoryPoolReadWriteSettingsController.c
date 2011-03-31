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

#include "MemoryPoolReadWriteSettingsController.h"

#include "SettingsController.h"
#include "LogSettingsController.h"

#include "Environment.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPbdb_MemoryPoolReadWriteSettingsController* RPbdb_MemoryPoolReadWriteSettingsController_new( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	
	RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller = calloc( 1, sizeof( RPbdb_MemoryPoolReadWriteSettingsController ) );

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
void RPbdb_MemoryPoolReadWriteSettingsController_free(	RPbdb_MemoryPoolReadWriteSettingsController** memory_pool_read_write_settings_controller )	{

	free( memory_pool_read_write_settings_controller );
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MemoryPoolReadWriteSettingsController_parentEnvironment(	RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	return memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
}

/*********************
*  maxOpenFiles  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_openfd.html
int RPbdb_MemoryPoolReadWriteSettingsController_maxOpenFiles( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	RPbdb_Environment*	environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
	
	if (	memory_pool_read_write_settings_controller->max_open_files == RPBDB_UNITIALIZED
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_mp_max_openfd(	environment->wrapped_bdb_environment, 
										&( memory_pool_read_write_settings_controller->max_open_files ) );
	}
	
	return memory_pool_read_write_settings_controller->max_open_files;
}

/*************************
*  setMaxOpenFiles  *
*************************/

void RPbdb_MemoryPoolReadWriteSettingsController_setMaxOpenFiles( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller, int max_open_files )	{

	RPbdb_Environment*		environment;
	
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
int RPbdb_MemoryPoolReadWriteSettingsController_maxSequentialWrites( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	
	RPbdb_Environment*		environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
		
	if (	memory_pool_read_write_settings_controller->max_sequential_writes == RPBDB_UNITIALIZED
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

void RPbdb_MemoryPoolReadWriteSettingsController_setMaxSequentialWrites( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller, int max_sequential_writes )	{

	RPbdb_Environment*		environment;
	
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

int RPbdb_MemoryPoolReadWriteSettingsController_timeToSleepBeforeNextWrite( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	RPbdb_Environment*		environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
	
	
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

void RPbdb_MemoryPoolReadWriteSettingsController_setTimeToSleepBeforeNextWrite( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller, db_timeout_t time_to_sleep_before_next_write )	{

	RPbdb_Environment*		environment;
	
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
size_t RPbdb_MemoryPoolReadWriteSettingsController_maxMappedDatabaseSize( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	RPbdb_Environment*		environment;
	
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

void RPbdb_MemoryPoolReadWriteSettingsController_setMaxMappedDatabaseSize(	RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller, 
																																					size_t																				max_mapped_db_size )	{

	RPbdb_Environment*		environment;
	
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
BOOL RPbdb_MemoryPoolReadWriteSettingsController_pagefaultSharedRegions( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->page_fault_shared_regions == TRUE )	{
		return DB_REGION_INIT;	
	}
	return FALSE;
}

	/*************************************
	*  turnPagefaultSharedRegionsOn  *
	*************************************/

	//	DB_REGION_INIT          http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->page_fault_shared_regions = TRUE;
	}

	/*************************************
	*  turnPagefaultSharedRegionsOff  *
	*************************************/

	//	DB_REGION_INIT          http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->page_fault_shared_regions = FALSE;
	}

/*********************************
*  useSystemMemoryForStorage  *
*********************************/

//	DB_SYSTEM_MEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPbdb_MemoryPoolReadWriteSettingsController_useSystemMemoryForStorage( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->use_system_memory_for_storage == TRUE )	{
		return DB_SYSTEM_MEM;
	}
	return FALSE;
}

	/*****************************************
	*  turnUseSystemMemoryForStorageOn  *
	*****************************************/

	//	DB_SYSTEM_MEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnUseSystemMemoryForStorageOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->use_system_memory_for_storage = TRUE;
	}

	/*****************************************
	*  turnUseSystemMemoryForStorageOff  *
	*****************************************/

	//	DB_SYSTEM_MEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnUseSystemMemoryForStorageOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->use_system_memory_for_storage = FALSE;
	}

/*************************************
*  applicationHasExclusiveAccess  *
*************************************/

//	DB_PRIVATE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPbdb_MemoryPoolReadWriteSettingsController_applicationHasExclusiveAccess( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->use_application_memory_for_storage == TRUE )	{
		return DB_PRIVATE;
	}
	return FALSE;
}

	/*********************************************
	*  turnApplicationHasExclusiveAccessOn  *
	*********************************************/

	//	DB_PRIVATE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->use_application_memory_for_storage = TRUE;
	}

	/*********************************************
	*  turnApplicationHasExclusiveAccessOff  *
	*********************************************/

	//	DB_PRIVATE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->use_application_memory_for_storage = FALSE;
	}
	
/*****************************************
*  databaseAllocatesMemoryUsingMalloc  *
*****************************************/

//	DB_DBT_MALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int RPbdb_MemoryPoolReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->database_allocates_memory_using_malloc == TRUE )	{
		return DB_DBT_MALLOC;
	}
	return FALSE;
}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOn  *
	*************************************************/

	//	DB_DBT_MALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( memory_pool_read_write_settings_controller );
		RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_read_write_settings_controller );
		RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( memory_pool_read_write_settings_controller );
		memory_pool_read_write_settings_controller->database_allocates_memory_using_malloc = TRUE;
	}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOff  *
	*************************************************/

	//	DB_DBT_MALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->database_allocates_memory_using_malloc = FALSE;
	}

/********************************************
*  databaseAllocatesMemoryUsingRealloc  *
********************************************/

//	DB_DBT_REALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int RPbdb_MemoryPoolReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	if ( memory_pool_read_write_settings_controller->database_allocates_memory_using_realloc == TRUE )	{
		return DB_DBT_REALLOC;
	}
	return FALSE;
}

	/****************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOn  *
	****************************************************/

	//	DB_DBT_REALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( memory_pool_read_write_settings_controller );
		RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_read_write_settings_controller );
		RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( memory_pool_read_write_settings_controller );
		memory_pool_read_write_settings_controller->database_allocates_memory_using_realloc = TRUE;
	}

	/****************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOff  *
	****************************************************/

	//	DB_DBT_REALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->database_allocates_memory_using_realloc = FALSE;
	}

/************************************
*  applicationAllocatesMemory  *
************************************/

//	DB_DBT_USERMEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int RPbdb_MemoryPoolReadWriteSettingsController_applicationAllocatesMemory( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	if ( memory_pool_read_write_settings_controller->application_allocates_memory == TRUE )	{
		return DB_DBT_USERMEM;
	}
	return FALSE;
}

	/****************************************
	*  turnApplicationAllocatesMemoryOn  *
	****************************************/

	//	DB_DBT_USERMEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( memory_pool_read_write_settings_controller );
		RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( memory_pool_read_write_settings_controller );
		RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_read_write_settings_controller );
		RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( memory_pool_read_write_settings_controller );
		memory_pool_read_write_settings_controller->application_allocates_memory = TRUE;
	}

	/****************************************
	*  turnApplicationAllocatesMemoryOff  *
	****************************************/

	//	DB_DBT_USERMEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->application_allocates_memory = FALSE;
	}

/******************************
*  databaseFreesMemory  *
******************************/

//	DB_DBT_APPMALLOC	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int RPbdb_MemoryPoolReadWriteSettingsController_databaseFreesMemory( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	if ( memory_pool_read_write_settings_controller->database_free_memory == TRUE )	{
		return DB_DBT_APPMALLOC;
	}
	return FALSE;
}

	/**********************************
	*  turnDatabaseFreesMemoryOn  *
	**********************************/

	//	DB_DBT_APPMALLOC	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( memory_pool_read_write_settings_controller );
		RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( memory_pool_read_write_settings_controller );
		RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_read_write_settings_controller );
		memory_pool_read_write_settings_controller->database_free_memory = TRUE;
	}

	/**************************************
	*  turnDatabaseFreesMemoryOff  *
	**************************************/

	//	DB_DBT_APPMALLOC	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->database_free_memory = FALSE;
	}


/*****************************************
*  doNotWriteToTemporaryBackingFile  *
*****************************************/

//	DB_MPOOL_NOFILE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
int RPbdb_MemoryPoolReadWriteSettingsController_doNotWriteToTemporaryBackingFile( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
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
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOn( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->do_not_write_to_temporary_backing_file = TRUE;
	}

	/*************************************************
	*  turnDoNotWriteToTemporaryBackingFileOff  *
	*************************************************/

	//	DB_MPOOL_NOFILE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	//	Note: method default inverts flag default
	void RPbdb_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOff( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->do_not_write_to_temporary_backing_file = FALSE;
	}

/**************************
*  isInMemoryEnvironment  *
**************************/

BOOL RPbdb_MemoryPoolReadWriteSettingsController_isInMemoryEnvironment( RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	
	RPbdb_LogSettingsController*	log_settings_controller	=	RPbdb_SettingsController_logSettingsController( memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller );
	
	//	does application have private environment access?
	//	is a temporary backing file disabled?
	//	check if logging is on; if it is, are we writing to files?
	if (			RPbdb_MemoryPoolReadWriteSettingsController_applicationHasExclusiveAccess( memory_pool_read_write_settings_controller )
			&&	RPbdb_MemoryPoolReadWriteSettingsController_doNotWriteToTemporaryBackingFile( memory_pool_read_write_settings_controller )
			&&	(	!		RPbdb_LogSettingsController_logInMemory( log_settings_controller )
						||	RPbdb_LogSettingsController_off( log_settings_controller ) ) )	{
		
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
RPbdb_MemoryPoolReadWriteSettingsController* RPbdb_MemoryPoolReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	RPbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller_copy	=	RPbdb_MemoryPoolReadWriteSettingsController_new( memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller );

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

