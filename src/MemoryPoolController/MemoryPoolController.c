/*
 *		RPbdb::MemoryPoolController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "MemoryPoolController.h"

#include "MemoryPoolFileController.h"

#include "LogSequenceNumber.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_MemoryPoolController* RPbdb_MemoryPoolController_new( RPbdb_Environment* parent_environment )	{
	
	RPbdb_MemoryPoolController*		memory_pool_controller = calloc( 1, sizeof( RPbdb_MemoryPoolController ) );

	memory_pool_controller->parent_environment = parent_environment;

	return memory_pool_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_MemoryPoolController_free(	RPbdb_MemoryPoolController** memory_pool_controller )	{

	if ( ( *memory_pool_controller )->file_controller != NULL )	{
		RPbdb_MemoryPoolFileController_free( & ( ( *memory_pool_controller )->file_controller ) );
	}

	free( *memory_pool_controller );
	*memory_pool_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_MemoryPoolSettingsController* RPbdb_MemoryPoolController_settingsController(	RPbdb_MemoryPoolController* memory_pool_controller )	{
	return memory_pool_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MemoryPoolController_parentEnvironment(	RPbdb_MemoryPoolController* memory_pool_controller )	{
	return memory_pool_controller->parent_environment;
}

/*********************
*  trickleClean  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_trickle.html
void RPbdb_MemoryPoolController_trickleClean(	RPbdb_MemoryPoolController*		memory_pool_controller, 
												int								percent_of_pages_to_clean )	{
	
	DB_ENV*		environment = memory_pool_controller->parent_environment->wrapped_bdb_environment;
	
	environment->memp_trickle(	environment, 
								percent_of_pages_to_clean,
								&( memory_pool_controller->memory_space_for_pages ) );
}

/*************
*  flush  *
*************/

//	The purpose of the lsn parameter is to enable a transaction manager to ensure, as part of a checkpoint, that all pages modified by a certain time have been written to disk.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_sync.html
void RPbdb_MemoryPoolController_flush(	RPbdb_MemoryPoolController*		memory_pool_controller, 
										RPbdb_LogSequenceNumber*		write_all_records_before_lsn )	{
	
	DB_ENV*		environment = memory_pool_controller->parent_environment->wrapped_bdb_environment;
	
	environment->memp_sync(	environment, 
							write_all_records_before_lsn->wrapped_bdb_log_sequence_number );
}

/*************************
*  setMallocMethod  *
*************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_alloc.html
void RPbdb_MemoryPoolController_setMallocMethod(	RPbdb_MemoryPoolController*				memory_pool_controller,
 													void*									(*malloc_method)( size_t )	)	{

	DB_ENV*		environment		= memory_pool_controller->parent_environment->wrapped_bdb_environment;

	memory_pool_controller->malloc_method = malloc_method;

	environment->set_alloc(	environment,
							memory_pool_controller->malloc_method,
							memory_pool_controller->realloc_method,
							memory_pool_controller->free_method );
}
*/
/*********************
*  mallocMethod  *
*********************/
/*
void *(*malloc_method)( size_t ) RPbdb_MemoryPoolController_mallocMethod( RPbdb_MemoryPoolController* memory_pool_controller )	{
	
	return memory_pool_controller->malloc_method;
}
*/
/*************************
*  setReallocMethod  *
*************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_alloc.html
void RPbdb_MemoryPoolController_setReallocMethod(	RPbdb_MemoryPoolController*					memory_pool_controller,
 													void*										(*realloc_method)( void*, size_t ) )	{

	DB_ENV*		environment		= memory_pool_controller->parent_environment->wrapped_bdb_environment;

	memory_pool_controller->realloc_method = realloc_method;

	environment->set_alloc(	environment,
							memory_pool_controller->malloc_method,
							memory_pool_controller->realloc_method,
							memory_pool_controller->free_method );
}
*/
/*********************
*  reallocMethod  *
*********************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_alloc.html
void *(*realloc_method)( void*, size_t ) RPbdb_MemoryPoolController_reallocMethod( RPbdb_MemoryPoolController* memory_pool_controller )	{

	return memory_pool_controller->realloc_method;
}
*/
/*********************
*  setFreeMethod  *
*********************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_alloc.html
void RPbdb_MemoryPoolController_setFreeMethod(	RPbdb_MemoryPoolController*			memory_pool_controller,
 												void*								(*free_method)( void* )	)	{
		
	DB_ENV*		environment		= memory_pool_controller->parent_environment->wrapped_bdb_environment;

	memory_pool_controller->free_method = free_method;

	environment->set_alloc(	environment,
							memory_pool_controller->malloc_method,
							memory_pool_controller->realloc_method,
							memory_pool_controller->free_method );
}
*/
/*****************
*  freeMethod  *
*****************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_alloc.html
void *(*free_method)( void* ) RPbdb_MemoryPoolController_freeMethod( RPbdb_MemoryPoolController* memory_pool_controller )	{

	return memory_pool_controller->free_method;
}
*/

/************************
*  fileController  *
************************/

RPbdb_MemoryPoolFileController* RPbdb_MemoryPoolController_fileController( RPbdb_MemoryPoolController* memory_pool_controller )	{

	if ( memory_pool_controller->file_controller == NULL )	{
		memory_pool_controller->file_controller	=	RPbdb_MemoryPoolFileController_new( memory_pool_controller );
	}
	
	return memory_pool_controller->file_controller;
}


