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

#include "Rbdb_MemoryPoolReadWriteSettingsController.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_LogSettingsController.h"

#include "Rbdb_Environment.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
Rbdb_MemoryPoolReadWriteSettingsController* Rbdb_MemoryPoolReadWriteSettingsController_new( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	
	Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller = calloc( 1, sizeof( Rbdb_MemoryPoolReadWriteSettingsController ) );

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
void Rbdb_MemoryPoolReadWriteSettingsController_free(	Rbdb_MemoryPoolReadWriteSettingsController** memory_pool_read_write_settings_controller )	{

	free( memory_pool_read_write_settings_controller );
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_MemoryPoolReadWriteSettingsController_parentEnvironment(	Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	return memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
}

/*********************
*  maxOpenFiles  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_openfd.html
int Rbdb_MemoryPoolReadWriteSettingsController_maxOpenFiles( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	Rbdb_Environment*	environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
	
	if (	memory_pool_read_write_settings_controller->max_open_files == Rbdb_UNITIALIZED
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_mp_max_openfd(	environment->wrapped_bdb_environment, 
										&( memory_pool_read_write_settings_controller->max_open_files ) );
	}
	
	return memory_pool_read_write_settings_controller->max_open_files;
}

/*************************
*  setMaxOpenFiles  *
*************************/

void Rbdb_MemoryPoolReadWriteSettingsController_setMaxOpenFiles( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller, int max_open_files )	{

	Rbdb_Environment*		environment;
	
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
int Rbdb_MemoryPoolReadWriteSettingsController_maxSequentialWrites( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	
	Rbdb_Environment*		environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
		
	if (	memory_pool_read_write_settings_controller->max_sequential_writes == Rbdb_UNITIALIZED
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

void Rbdb_MemoryPoolReadWriteSettingsController_setMaxSequentialWrites( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller, int max_sequential_writes )	{

	Rbdb_Environment*		environment;
	
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

int Rbdb_MemoryPoolReadWriteSettingsController_timeToSleepBeforeNextWrite( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	Rbdb_Environment*		environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
	
	
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

void Rbdb_MemoryPoolReadWriteSettingsController_setTimeToSleepBeforeNextWrite( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller, db_timeout_t time_to_sleep_before_next_write )	{

	Rbdb_Environment*		environment;
	
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
size_t Rbdb_MemoryPoolReadWriteSettingsController_maxMappedDatabaseSize( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	Rbdb_Environment*		environment;
	
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

void Rbdb_MemoryPoolReadWriteSettingsController_setMaxMappedDatabaseSize(	Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller, 
																																					size_t																				max_mapped_db_size )	{

	Rbdb_Environment*		environment;
	
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
BOOL Rbdb_MemoryPoolReadWriteSettingsController_pagefaultSharedRegions( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->page_fault_shared_regions == TRUE )	{
		return DB_REGION_INIT;	
	}
	return FALSE;
}

	/*************************************
	*  turnPagefaultSharedRegionsOn  *
	*************************************/

	//	DB_REGION_INIT          http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->page_fault_shared_regions = TRUE;
	}

	/*************************************
	*  turnPagefaultSharedRegionsOff  *
	*************************************/

	//	DB_REGION_INIT          http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnPagefaultSharedRegionsOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->page_fault_shared_regions = FALSE;
	}

/*********************************
*  useSystemMemoryForStorage  *
*********************************/

//	DB_SYSTEM_MEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int Rbdb_MemoryPoolReadWriteSettingsController_useSystemMemoryForStorage( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->use_system_memory_for_storage == TRUE )	{
		return DB_SYSTEM_MEM;
	}
	return FALSE;
}

	/*****************************************
	*  turnUseSystemMemoryForStorageOn  *
	*****************************************/

	//	DB_SYSTEM_MEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnUseSystemMemoryForStorageOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->use_system_memory_for_storage = TRUE;
	}

	/*****************************************
	*  turnUseSystemMemoryForStorageOff  *
	*****************************************/

	//	DB_SYSTEM_MEM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnUseSystemMemoryForStorageOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->use_system_memory_for_storage = FALSE;
	}

/*************************************
*  applicationHasExclusiveAccess  *
*************************************/

//	DB_PRIVATE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int Rbdb_MemoryPoolReadWriteSettingsController_applicationHasExclusiveAccess( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->use_application_memory_for_storage == TRUE )	{
		return DB_PRIVATE;
	}
	return FALSE;
}

	/*********************************************
	*  turnApplicationHasExclusiveAccessOn  *
	*********************************************/

	//	DB_PRIVATE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->use_application_memory_for_storage = TRUE;
	}

	/*********************************************
	*  turnApplicationHasExclusiveAccessOff  *
	*********************************************/

	//	DB_PRIVATE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->use_application_memory_for_storage = FALSE;
	}
	
/*****************************************
*  databaseAllocatesMemoryUsingMalloc  *
*****************************************/

//	DB_DBT_MALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int Rbdb_MemoryPoolReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	if ( memory_pool_read_write_settings_controller->database_allocates_memory_using_malloc == TRUE )	{
		return DB_DBT_MALLOC;
	}
	return FALSE;
}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOn  *
	*************************************************/

	//	DB_DBT_MALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( memory_pool_read_write_settings_controller );
		Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_read_write_settings_controller );
		Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( memory_pool_read_write_settings_controller );
		memory_pool_read_write_settings_controller->database_allocates_memory_using_malloc = TRUE;
	}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOff  *
	*************************************************/

	//	DB_DBT_MALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->database_allocates_memory_using_malloc = FALSE;
	}

/********************************************
*  databaseAllocatesMemoryUsingRealloc  *
********************************************/

//	DB_DBT_REALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int Rbdb_MemoryPoolReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	if ( memory_pool_read_write_settings_controller->database_allocates_memory_using_realloc == TRUE )	{
		return DB_DBT_REALLOC;
	}
	return FALSE;
}

	/****************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOn  *
	****************************************************/

	//	DB_DBT_REALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( memory_pool_read_write_settings_controller );
		Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_read_write_settings_controller );
		Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( memory_pool_read_write_settings_controller );
		memory_pool_read_write_settings_controller->database_allocates_memory_using_realloc = TRUE;
	}

	/****************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOff  *
	****************************************************/

	//	DB_DBT_REALLOC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->database_allocates_memory_using_realloc = FALSE;
	}

/************************************
*  applicationAllocatesMemory  *
************************************/

//	DB_DBT_USERMEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int Rbdb_MemoryPoolReadWriteSettingsController_applicationAllocatesMemory( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	if ( memory_pool_read_write_settings_controller->application_allocates_memory == TRUE )	{
		return DB_DBT_USERMEM;
	}
	return FALSE;
}

	/****************************************
	*  turnApplicationAllocatesMemoryOn  *
	****************************************/

	//	DB_DBT_USERMEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( memory_pool_read_write_settings_controller );
		Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( memory_pool_read_write_settings_controller );
		Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_read_write_settings_controller );
		Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( memory_pool_read_write_settings_controller );
		memory_pool_read_write_settings_controller->application_allocates_memory = TRUE;
	}

	/****************************************
	*  turnApplicationAllocatesMemoryOff  *
	****************************************/

	//	DB_DBT_USERMEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->application_allocates_memory = FALSE;
	}

/******************************
*  databaseFreesMemory  *
******************************/

//	DB_DBT_APPMALLOC	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
int Rbdb_MemoryPoolReadWriteSettingsController_databaseFreesMemory( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	if ( memory_pool_read_write_settings_controller->database_free_memory == TRUE )	{
		return DB_DBT_APPMALLOC;
	}
	return FALSE;
}

	/**********************************
	*  turnDatabaseFreesMemoryOn  *
	**********************************/

	//	DB_DBT_APPMALLOC	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( memory_pool_read_write_settings_controller );
		Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( memory_pool_read_write_settings_controller );
		Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationAllocatesMemoryOff( memory_pool_read_write_settings_controller );
		memory_pool_read_write_settings_controller->database_free_memory = TRUE;
	}

	/**************************************
	*  turnDatabaseFreesMemoryOff  *
	**************************************/

	//	DB_DBT_APPMALLOC	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDatabaseFreesMemoryOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->database_free_memory = FALSE;
	}


/*****************************************
*  doNotWriteToTemporaryBackingFile  *
*****************************************/

//	DB_MPOOL_NOFILE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
int Rbdb_MemoryPoolReadWriteSettingsController_doNotWriteToTemporaryBackingFile( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
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
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOn( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->do_not_write_to_temporary_backing_file = TRUE;
	}

	/*************************************************
	*  turnDoNotWriteToTemporaryBackingFileOff  *
	*************************************************/

	//	DB_MPOOL_NOFILE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	//	Note: method default inverts flag default
	void Rbdb_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOff( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
		memory_pool_read_write_settings_controller->do_not_write_to_temporary_backing_file = FALSE;
	}

/**************************
*  isInMemoryEnvironment  *
**************************/

BOOL Rbdb_MemoryPoolReadWriteSettingsController_isInMemoryEnvironment( Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{
	
	Rbdb_LogSettingsController*	log_settings_controller	=	Rbdb_SettingsController_logSettingsController( memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller );
	
	//	does application have private environment access?
	//	is a temporary backing file disabled?
	//	check if logging is on; if it is, are we writing to files?
	if (			Rbdb_MemoryPoolReadWriteSettingsController_applicationHasExclusiveAccess( memory_pool_read_write_settings_controller )
			&&	Rbdb_MemoryPoolReadWriteSettingsController_doNotWriteToTemporaryBackingFile( memory_pool_read_write_settings_controller )
			&&	(	!		Rbdb_LogSettingsController_logInMemory( log_settings_controller )
						||	Rbdb_LogSettingsController_off( log_settings_controller ) ) )	{
		
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
Rbdb_MemoryPoolReadWriteSettingsController* Rbdb_MemoryPoolReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

	Rbdb_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller_copy	=	Rbdb_MemoryPoolReadWriteSettingsController_new( memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller );

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

