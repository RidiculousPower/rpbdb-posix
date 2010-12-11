/*
 *		Rbdb::MemoryPoolFileController
 *
 *	
 */

#ifndef RBDB_MEMORY_POOL_FILE_CONTROLLER
	#define RBDB_MEMORY_POOL_FILE_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_MemoryPoolFileController*											Rbdb_MemoryPoolFileController_new(					Rbdb_MemoryPoolController*				memory_pool_controller );

	void																	Rbdb_MemoryPoolFileController_free(	Rbdb_MemoryPoolFileController** memory_pool_file_controller );
	Rbdb_MemoryPoolFileSettingsController*									Rbdb_MemoryPoolFileController_settingsController(	Rbdb_MemoryPoolFileController* memory_pool_file_controller );
	Rbdb_Environment*												Rbdb_MemoryPoolFileController_parentEnvironment(	Rbdb_MemoryPoolFileController* memory_pool_file_controller );

	Rbdb_MemoryPoolFile*		   											Rbdb_MemoryPoolFileController_createFile(			Rbdb_MemoryPoolFileController*			memory_pool_file_controller );
	Rbdb_MemoryPoolFile*		   											Rbdb_MemoryPoolFileController_openFile(			Rbdb_MemoryPoolFileController*			memory_pool_file_controller,
	 					 		   											  													char*									file_path,
						 		   											  													//	This should be broken down into functions that specify the type of mode, probably
						 		   											  													int										chmod_mode,
						 		   											  													//	How do we determine how large pagesize should be?
						 		   											  													size_t									pagesize_in_bytes );
	/*
	void																	Rbdb_MemoryPoolFileController_setPageInMethod(		Rbdb_MemoryPoolFileController*			memory_pool_file_controller,
																									   							int										file_type	);
	int	(*page_in_method)(	Rbdb_Environment*			environment,
							void*			page_data,
							Rbdb_Data*		page_cookie	)					Rbdb_MemoryPoolFileController_pageInMethod(		Rbdb_MemoryPoolFileController*		memory_pool_file_controller );

	void																	Rbdb_MemoryPoolFileController_setPageOutMethod(	Rbdb_MemoryPoolFileController*			memory_pool_file_controller,
																			   													int										file_type	);
	int	(*page_out_method)(	Rbdb_Environment*			environment,
							void*			page_data,
							Rbdb_Data*		page_cookie	)					Rbdb_MemoryPoolFileController_pageOutMethod(		Rbdb_MemoryPoolFileController*		memory_pool_file_controller );
*/
#endif

