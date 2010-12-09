/*
 *		Rbdb::MemoryPoolController
 *
 *	
 */

#ifndef Rbdb_MEMORY_POOL_CONTROLLER
	#define Rbdb_MEMORY_POOL_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_MemoryPoolController*					Rbdb_MemoryPoolController_new(					Rbdb_Environment*										environment );

	void										Rbdb_MemoryPoolController_free(	Rbdb_MemoryPoolController** memory_pool_controller );
	Rbdb_MemoryPoolSettingsController*			Rbdb_MemoryPoolController_settingsController(	Rbdb_MemoryPoolController* memory_pool_controller );
	Rbdb_Environment*					Rbdb_MemoryPoolController_parentEnvironment(	Rbdb_MemoryPoolController* memory_pool_controller );

	void										Rbdb_MemoryPoolController_trickleClean(		Rbdb_MemoryPoolController*					memory_pool_controller, 
																								int											percent_of_pages_to_clean );
	void											Rbdb_MemoryPoolController_flush(				Rbdb_MemoryPoolController*					memory_pool_controller, 
	   																							Rbdb_LogSequenceNumber*					write_all_records_before_lsn );
/*
	void										Rbdb_MemoryPoolController_setMallocMethod(		Rbdb_MemoryPoolController*					memory_pool_controller,
	 											   												void *(*malloc_method)( size_t )			malloc_method	);
	void*	(*malloc_method)( size_t )			Rbdb_MemoryPoolController_mallocMethod(		Rbdb_MemoryPoolController*					memory_pool_controller );
	void										Rbdb_MemoryPoolController_setReallocMethod(	Rbdb_MemoryPoolController*					memory_pool_controller,
	 									   														void *(*realloc_method)( void*, size_t )	realloc_method	);
	void*	(*realloc_method)( void*, size_t )	Rbdb_MemoryPoolController_reallocMethod(		Rbdb_MemoryPoolController*					memory_pool_controller );
	void										Rbdb_MemoryPoolController_setFreeMethod(		Rbdb_MemoryPoolController*					memory_pool_controller,
	 											   												void *(*free_method)( void* )				free_method	);
	void*	(*free_method)( void* )				Rbdb_MemoryPoolController_freeMethod(			Rbdb_MemoryPoolController*					memory_pool_controller );
*/
	Rbdb_MemoryPoolFileController*				Rbdb_MemoryPoolController_fileController(		Rbdb_MemoryPoolController*					memory_pool_controller );

#endif

