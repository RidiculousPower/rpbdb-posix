/*
 *		RPbdb::MemoryPoolController
 *
 *	
 */

#ifndef RPBDB_MEMORY_POOL_CONTROLLER
	#define RPBDB_MEMORY_POOL_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_MemoryPoolController*					RPbdb_MemoryPoolController_new(					RPbdb_Environment*										environment );

	void										RPbdb_MemoryPoolController_free(	RPbdb_MemoryPoolController** memory_pool_controller );
	RPbdb_MemoryPoolSettingsController*			RPbdb_MemoryPoolController_settingsController(	RPbdb_MemoryPoolController* memory_pool_controller );
	RPbdb_Environment*					RPbdb_MemoryPoolController_parentEnvironment(	RPbdb_MemoryPoolController* memory_pool_controller );

	void										RPbdb_MemoryPoolController_trickleClean(		RPbdb_MemoryPoolController*					memory_pool_controller, 
																								int											percent_of_pages_to_clean );
	void											RPbdb_MemoryPoolController_flush(				RPbdb_MemoryPoolController*					memory_pool_controller, 
	   																							RPbdb_LogSequenceNumber*					write_all_records_before_lsn );
/*
	void										RPbdb_MemoryPoolController_setMallocMethod(		RPbdb_MemoryPoolController*					memory_pool_controller,
	 											   												void *(*malloc_method)( size_t )			malloc_method	);
	void*	(*malloc_method)( size_t )			RPbdb_MemoryPoolController_mallocMethod(		RPbdb_MemoryPoolController*					memory_pool_controller );
	void										RPbdb_MemoryPoolController_setReallocMethod(	RPbdb_MemoryPoolController*					memory_pool_controller,
	 									   														void *(*realloc_method)( void*, size_t )	realloc_method	);
	void*	(*realloc_method)( void*, size_t )	RPbdb_MemoryPoolController_reallocMethod(		RPbdb_MemoryPoolController*					memory_pool_controller );
	void										RPbdb_MemoryPoolController_setFreeMethod(		RPbdb_MemoryPoolController*					memory_pool_controller,
	 											   												void *(*free_method)( void* )				free_method	);
	void*	(*free_method)( void* )				RPbdb_MemoryPoolController_freeMethod(			RPbdb_MemoryPoolController*					memory_pool_controller );
*/
	RPbdb_MemoryPoolFileController*				RPbdb_MemoryPoolController_fileController(		RPbdb_MemoryPoolController*					memory_pool_controller );

#endif

