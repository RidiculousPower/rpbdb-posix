/*
 *		RPDB::MemoryPoolFileController
 *
 *	
 */

#ifndef RPDB_MEMORY_POOL_FILE_CONTROLLER
	#define RPDB_MEMORY_POOL_FILE_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_MemoryPoolFileController*											RPDB_MemoryPoolFileController_new(					RPDB_MemoryPoolController*				memory_pool_controller );

	void																	RPDB_MemoryPoolFileController_free(	RPDB_MemoryPoolFileController** memory_pool_file_controller );
	RPDB_MemoryPoolFileSettingsController*									RPDB_MemoryPoolFileController_settingsController(	RPDB_MemoryPoolFileController* memory_pool_file_controller );
	RPDB_Environment*												RPDB_MemoryPoolFileController_parentEnvironment(	RPDB_MemoryPoolFileController* memory_pool_file_controller );

	RPDB_MemoryPoolFile*		   											RPDB_MemoryPoolFileController_createFile(			RPDB_MemoryPoolFileController*			memory_pool_file_controller );
	RPDB_MemoryPoolFile*		   											RPDB_MemoryPoolFileController_openFile(			RPDB_MemoryPoolFileController*			memory_pool_file_controller,
	 					 		   											  													char*									file_path,
						 		   											  													//	This should be broken down into functions that specify the type of mode, probably
						 		   											  													int										chmod_mode,
						 		   											  													//	How do we determine how large pagesize should be?
						 		   											  													size_t									pagesize_in_bytes );
	/*
	void																	RPDB_MemoryPoolFileController_setPageInMethod(		RPDB_MemoryPoolFileController*			memory_pool_file_controller,
																									   							int										file_type	);
	int	(*page_in_method)(	RPDB_Environment*			environment,
							void*			page_data,
							RPDB_Data*		page_cookie	)					RPDB_MemoryPoolFileController_pageInMethod(		RPDB_MemoryPoolFileController*		memory_pool_file_controller );

	void																	RPDB_MemoryPoolFileController_setPageOutMethod(	RPDB_MemoryPoolFileController*			memory_pool_file_controller,
																			   													int										file_type	);
	int	(*page_out_method)(	RPDB_Environment*			environment,
							void*			page_data,
							RPDB_Data*		page_cookie	)					RPDB_MemoryPoolFileController_pageOutMethod(		RPDB_MemoryPoolFileController*		memory_pool_file_controller );
*/
#endif

