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
int RPDB_MemoryPoolReadWriteSettingsController_maxMappedDBSize( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller )	{

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

void RPDB_MemoryPoolReadWriteSettingsController_setMaxMappedDBSize( RPDB_MemoryPoolReadWriteSettingsController* memory_pool_read_write_settings_controller, size_t max_mapped_db_size )	{

	RPDB_Environment*		environment;
	
	environment = memory_pool_read_write_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_mp_mmapsize(	environment->wrapped_bdb_environment, 
										memory_pool_read_write_settings_controller->max_mapped_db_size );
	}
	
	memory_pool_read_write_settings_controller->max_mapped_db_size = max_mapped_db_size;
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
	memory_pool_read_write_settings_controller_copy->memory_pool_read_write_settings_controller	=	memory_pool_read_write_settings_controller->memory_pool_read_write_settings_controller;
	memory_pool_read_write_settings_controller_copy->max_sequential_writes	=	memory_pool_read_write_settings_controller->max_sequential_writes;
	memory_pool_read_write_settings_controller_copy->max_mapped_db_size	=	memory_pool_read_write_settings_controller->max_mapped_db_size;
	memory_pool_read_write_settings_controller_copy->page_fault_shared_regions	=	memory_pool_read_write_settings_controller->page_fault_shared_regions;
	memory_pool_read_write_settings_controller_copy->max_open_files	=	memory_pool_read_write_settings_controller->max_open_files;

	return memory_pool_read_write_settings_controller_copy;
}

