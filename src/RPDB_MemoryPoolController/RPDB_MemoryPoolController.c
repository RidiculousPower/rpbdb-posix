/*
 *		RPDB::MemoryPoolController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MemoryPoolController.h"

#include "RPDB_MemoryPoolFileController.h"

#include "RPDB_LogSequenceNumber.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_MemoryPoolController* RPDB_MemoryPoolController_new( RPDB_Environment* parent_environment )	{
	
	RPDB_MemoryPoolController*		memory_pool_controller = calloc( 1, sizeof( RPDB_MemoryPoolController ) );

	memory_pool_controller->parent_environment = parent_environment;

	return memory_pool_controller;
}

/***************************
*  free  *
***************************/
void RPDB_MemoryPoolController_free(	RPDB_MemoryPoolController** memory_pool_controller )	{

	if ( ( *memory_pool_controller )->file_controller != NULL )	{
		RPDB_MemoryPoolFileController_free( & ( ( *memory_pool_controller )->file_controller ) );
	}

	free( *memory_pool_controller );
	*memory_pool_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_MemoryPoolSettingsController* RPDB_MemoryPoolController_settingsController(	RPDB_MemoryPoolController* memory_pool_controller )	{
	return memory_pool_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MemoryPoolController_parentEnvironment(	RPDB_MemoryPoolController* memory_pool_controller )	{
	return memory_pool_controller->parent_environment;
}

/*********************
*  trickleClean  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_trickle.html
void RPDB_MemoryPoolController_trickleClean(	RPDB_MemoryPoolController*		memory_pool_controller, 
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
void RPDB_MemoryPoolController_flush(	RPDB_MemoryPoolController*		memory_pool_controller, 
										RPDB_LogSequenceNumber*		write_all_records_before_lsn )	{
	
	DB_ENV*		environment = memory_pool_controller->parent_environment->wrapped_bdb_environment;
	
	environment->memp_sync(	environment, 
							write_all_records_before_lsn->wrapped_bdb_log_sequence_number );
}

/*************************
*  setMallocMethod  *
*************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_alloc.html
void RPDB_MemoryPoolController_setMallocMethod(	RPDB_MemoryPoolController*				memory_pool_controller,
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
void *(*malloc_method)( size_t ) RPDB_MemoryPoolController_mallocMethod( RPDB_MemoryPoolController* memory_pool_controller )	{
	
	return memory_pool_controller->malloc_method;
}
*/
/*************************
*  setReallocMethod  *
*************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_alloc.html
void RPDB_MemoryPoolController_setReallocMethod(	RPDB_MemoryPoolController*					memory_pool_controller,
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
void *(*realloc_method)( void*, size_t ) RPDB_MemoryPoolController_reallocMethod( RPDB_MemoryPoolController* memory_pool_controller )	{

	return memory_pool_controller->realloc_method;
}
*/
/*********************
*  setFreeMethod  *
*********************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_alloc.html
void RPDB_MemoryPoolController_setFreeMethod(	RPDB_MemoryPoolController*			memory_pool_controller,
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
void *(*free_method)( void* ) RPDB_MemoryPoolController_freeMethod( RPDB_MemoryPoolController* memory_pool_controller )	{

	return memory_pool_controller->free_method;
}
*/

/************************
*  fileController  *
************************/

RPDB_MemoryPoolFileController* RPDB_MemoryPoolController_fileController( RPDB_MemoryPoolController* memory_pool_controller )	{

	if ( memory_pool_controller->file_controller == NULL )	{
		memory_pool_controller->file_controller	=	RPDB_MemoryPoolFileController_new( memory_pool_controller );
	}
	
	return memory_pool_controller->file_controller;
}


