/*
 *		Rbdb::MemoryPoolController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_MemoryPoolController.h"

#include "Rbdb_MemoryPoolFileController.h"

#include "Rbdb_LogSequenceNumber.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_MemoryPoolController* Rbdb_MemoryPoolController_new( Rbdb_Environment* parent_environment )	{
	
	Rbdb_MemoryPoolController*		memory_pool_controller = calloc( 1, sizeof( Rbdb_MemoryPoolController ) );

	memory_pool_controller->parent_environment = parent_environment;

	return memory_pool_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_MemoryPoolController_free(	Rbdb_MemoryPoolController** memory_pool_controller )	{

	if ( ( *memory_pool_controller )->file_controller != NULL )	{
		Rbdb_MemoryPoolFileController_free( & ( ( *memory_pool_controller )->file_controller ) );
	}

	free( *memory_pool_controller );
	*memory_pool_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_MemoryPoolSettingsController* Rbdb_MemoryPoolController_settingsController(	Rbdb_MemoryPoolController* memory_pool_controller )	{
	return memory_pool_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_MemoryPoolController_parentEnvironment(	Rbdb_MemoryPoolController* memory_pool_controller )	{
	return memory_pool_controller->parent_environment;
}

/*********************
*  trickleClean  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_trickle.html
void Rbdb_MemoryPoolController_trickleClean(	Rbdb_MemoryPoolController*		memory_pool_controller, 
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
void Rbdb_MemoryPoolController_flush(	Rbdb_MemoryPoolController*		memory_pool_controller, 
										Rbdb_LogSequenceNumber*		write_all_records_before_lsn )	{
	
	DB_ENV*		environment = memory_pool_controller->parent_environment->wrapped_bdb_environment;
	
	environment->memp_sync(	environment, 
							write_all_records_before_lsn->wrapped_bdb_log_sequence_number );
}

/*************************
*  setMallocMethod  *
*************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_alloc.html
void Rbdb_MemoryPoolController_setMallocMethod(	Rbdb_MemoryPoolController*				memory_pool_controller,
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
void *(*malloc_method)( size_t ) Rbdb_MemoryPoolController_mallocMethod( Rbdb_MemoryPoolController* memory_pool_controller )	{
	
	return memory_pool_controller->malloc_method;
}
*/
/*************************
*  setReallocMethod  *
*************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_alloc.html
void Rbdb_MemoryPoolController_setReallocMethod(	Rbdb_MemoryPoolController*					memory_pool_controller,
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
void *(*realloc_method)( void*, size_t ) Rbdb_MemoryPoolController_reallocMethod( Rbdb_MemoryPoolController* memory_pool_controller )	{

	return memory_pool_controller->realloc_method;
}
*/
/*********************
*  setFreeMethod  *
*********************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_alloc.html
void Rbdb_MemoryPoolController_setFreeMethod(	Rbdb_MemoryPoolController*			memory_pool_controller,
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
void *(*free_method)( void* ) Rbdb_MemoryPoolController_freeMethod( Rbdb_MemoryPoolController* memory_pool_controller )	{

	return memory_pool_controller->free_method;
}
*/

/************************
*  fileController  *
************************/

Rbdb_MemoryPoolFileController* Rbdb_MemoryPoolController_fileController( Rbdb_MemoryPoolController* memory_pool_controller )	{

	if ( memory_pool_controller->file_controller == NULL )	{
		memory_pool_controller->file_controller	=	Rbdb_MemoryPoolFileController_new( memory_pool_controller );
	}
	
	return memory_pool_controller->file_controller;
}


