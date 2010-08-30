/*
 *		RPDB::MemoryPoolController
 *
 *	
 */

#ifndef RPDB_MEMORY_POOL_CONTROLLER
	#define RPDB_MEMORY_POOL_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_MemoryPoolController*					RPDB_MemoryPoolController_new(					RPDB_Environment*										environment );

	void										RPDB_MemoryPoolController_free(	RPDB_MemoryPoolController** memory_pool_controller );
	RPDB_MemoryPoolSettingsController*			RPDB_MemoryPoolController_settingsController(	RPDB_MemoryPoolController* memory_pool_controller );
	RPDB_Environment*					RPDB_MemoryPoolController_parentEnvironment(	RPDB_MemoryPoolController* memory_pool_controller );

	void										RPDB_MemoryPoolController_trickleClean(		RPDB_MemoryPoolController*					memory_pool_controller, 
																								int											percent_of_pages_to_clean );
	void											RPDB_MemoryPoolController_flush(				RPDB_MemoryPoolController*					memory_pool_controller, 
	   																							RPDB_LogSequenceNumber*					write_all_records_before_lsn );
/*
	void										RPDB_MemoryPoolController_setMallocMethod(		RPDB_MemoryPoolController*					memory_pool_controller,
	 											   												void *(*malloc_method)( size_t )			malloc_method	);
	void*	(*malloc_method)( size_t )			RPDB_MemoryPoolController_mallocMethod(		RPDB_MemoryPoolController*					memory_pool_controller );
	void										RPDB_MemoryPoolController_setReallocMethod(	RPDB_MemoryPoolController*					memory_pool_controller,
	 									   														void *(*realloc_method)( void*, size_t )	realloc_method	);
	void*	(*realloc_method)( void*, size_t )	RPDB_MemoryPoolController_reallocMethod(		RPDB_MemoryPoolController*					memory_pool_controller );
	void										RPDB_MemoryPoolController_setFreeMethod(		RPDB_MemoryPoolController*					memory_pool_controller,
	 											   												void *(*free_method)( void* )				free_method	);
	void*	(*free_method)( void* )				RPDB_MemoryPoolController_freeMethod(			RPDB_MemoryPoolController*					memory_pool_controller );
*/
	RPDB_MemoryPoolFileController*				RPDB_MemoryPoolController_fileController(		RPDB_MemoryPoolController*					memory_pool_controller );

#endif

