/*
 *		RPbdb::MemoryPoolFileController
 *
 *	
 */

#ifndef RPBDB_MEMORY_POOL_FILE_CONTROLLER
	#define RPBDB_MEMORY_POOL_FILE_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_MemoryPoolFileController*											RPbdb_MemoryPoolFileController_new(					RPbdb_MemoryPoolController*				memory_pool_controller );

	void																	RPbdb_MemoryPoolFileController_free(	RPbdb_MemoryPoolFileController** memory_pool_file_controller );
	RPbdb_MemoryPoolFileSettingsController*									RPbdb_MemoryPoolFileController_settingsController(	RPbdb_MemoryPoolFileController* memory_pool_file_controller );
	RPbdb_Environment*												RPbdb_MemoryPoolFileController_parentEnvironment(	RPbdb_MemoryPoolFileController* memory_pool_file_controller );

	RPbdb_MemoryPoolFile*		   											RPbdb_MemoryPoolFileController_createFile(			RPbdb_MemoryPoolFileController*			memory_pool_file_controller );
	RPbdb_MemoryPoolFile*		   											RPbdb_MemoryPoolFileController_openFile(			RPbdb_MemoryPoolFileController*			memory_pool_file_controller,
	 					 		   											  													char*									file_path,
						 		   											  													//	This should be broken down into functions that specify the type of mode, probably
						 		   											  													int										chmod_mode,
						 		   											  													//	How do we determine how large pagesize should be?
						 		   											  													size_t									pagesize_in_bytes );
	/*
	void																	RPbdb_MemoryPoolFileController_setPageInMethod(		RPbdb_MemoryPoolFileController*			memory_pool_file_controller,
																									   							int										file_type	);
	int	(*page_in_method)(	RPbdb_Environment*			environment,
							void*			page_data,
							RPbdb_Data*		page_cookie	)					RPbdb_MemoryPoolFileController_pageInMethod(		RPbdb_MemoryPoolFileController*		memory_pool_file_controller );

	void																	RPbdb_MemoryPoolFileController_setPageOutMethod(	RPbdb_MemoryPoolFileController*			memory_pool_file_controller,
																			   													int										file_type	);
	int	(*page_out_method)(	RPbdb_Environment*			environment,
							void*			page_data,
							RPbdb_Data*		page_cookie	)					RPbdb_MemoryPoolFileController_pageOutMethod(		RPbdb_MemoryPoolFileController*		memory_pool_file_controller );
*/
#endif

