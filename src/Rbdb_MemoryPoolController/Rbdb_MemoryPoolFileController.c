/*
 *		Rbdb::MemoryPoolFileController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_MemoryPoolFileController.h"
#include "Rbdb_MemoryPoolFileController_internal.h"

#include "Rbdb_MemoryPoolFile.h"
#include "Rbdb_MemoryPoolController.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Data.h"
#include "Rbdb_Data_internal.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_MemoryPoolSettingsController.h"
#include "Rbdb_MemoryPoolFileSettingsController_internal.h"

#include "Rbdb_RuntimeStorageController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																												Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_MemoryPoolFileController* Rbdb_MemoryPoolFileController_new( Rbdb_MemoryPoolController* parent_memory_pool_controller )	{
	
	Rbdb_MemoryPoolFileController*		memory_pool_file_controller = calloc( 1, sizeof( Rbdb_MemoryPoolFileController ) );

	memory_pool_file_controller->parent_memory_pool_controller = parent_memory_pool_controller;

	return memory_pool_file_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_MemoryPoolFileController_free(	Rbdb_MemoryPoolFileController** memory_pool_file_controller )	{

	free( memory_pool_file_controller );
}

/***************************
*  settingsController  *
***************************/
Rbdb_MemoryPoolFileSettingsController* Rbdb_MemoryPoolFileController_settingsController(	Rbdb_MemoryPoolFileController* memory_pool_file_controller )	{
	return memory_pool_file_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_MemoryPoolFileController_parentEnvironment(	Rbdb_MemoryPoolFileController* memory_pool_file_controller )	{
	return memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*****************
*  createFile  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fcreate.html
Rbdb_MemoryPoolFile* Rbdb_MemoryPoolFileController_createFile( Rbdb_MemoryPoolFileController* memory_pool_file_controller )	{
	
	Rbdb_Environment*		environment = memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
	
	Rbdb_MemoryPoolFile*	memory_pool_file = Rbdb_MemoryPoolFile_new( memory_pool_file_controller );
	
	environment->wrapped_bdb_environment->memp_fcreate(	environment->wrapped_bdb_environment,
								&( memory_pool_file->wrapped_bdb_memory_pool_file ),
								Rbdb_MemoryPoolFileSettingsController_internal_openFlags( Rbdb_MemoryPoolSettingsController_fileSettingsController( Rbdb_SettingsController_memoryPoolSettingsController( Rbdb_Environment_settingsController( environment ) ) ) ) );
	return memory_pool_file;
}

/*****************
*  openFile  *
*****************/

//	The file parameter is the name of the file to be opened. 
//	If file is NULL, a private temporary file is created that cannot be shared with any other process 
//	(although it may be shared with other threads of control in the same process).
//	The pagesize parameter is the size, in bytes, of the unit of transfer between the application and the cache, 
//	although it is not necessarily the unit of transfer between the cache and the underlying filesystem.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fopen.html
Rbdb_MemoryPoolFile* Rbdb_MemoryPoolFileController_openFile(	Rbdb_MemoryPoolFileController*		memory_pool_file_controller,
 																char*								file_path,
																//	This should be broken down into functions that specify the type of mode, probably
																int									chmod_mode,
																//	How do we determine how large pagesize should be?
																size_t								pagesize_in_bytes )	{
	
	Rbdb_MemoryPoolFile*	memory_pool_file = Rbdb_MemoryPoolFile_new( memory_pool_file_controller );
	
	memory_pool_file->wrapped_bdb_memory_pool_file->open(	memory_pool_file->wrapped_bdb_memory_pool_file,
															file_path,
															Rbdb_MemoryPoolFileSettingsController_internal_openFlags( Rbdb_MemoryPoolSettingsController_fileSettingsController( Rbdb_SettingsController_memoryPoolSettingsController( Rbdb_Environment_settingsController( memory_pool_file_controller->parent_memory_pool_controller->parent_environment ) ) ) ),
															chmod_mode,
															pagesize_in_bytes );
							
	return memory_pool_file;
}

/*******************************************************************************************************************************************************************************************
																		Callback Public Methods
*******************************************************************************************************************************************************************************************/

/**************************
*  setPageInMethod  *
**************************/
/*
//	The ftype parameter specifies the type of file for which the page-in and page-out functions will be called.
//	The ftype value for a file must be a non-zero positive number less than 128 
//	(0 and negative numbers are reserved for internal use by the Berkeley DB library).
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_register.html
void Rbdb_MemoryPoolFileController_setPageInMethod(		Rbdb_MemoryPoolFileController*		memory_pool_file_controller,
															int									file_type,
															int									(*page_in_method)(	Rbdb_Environment*			environment,
															   														void*			page_data,
															   														Rbdb_Data*		page_cookie	))	{
	
	if (	file_type < 1
		||	file_type > 128 )	{

		//	Throw error - negative values reserved for BDB, max value 128
		//	FIX
	}
	
	DB_ENV*	environment	=	memory_pool_file_controller->parent_memory_pool_controller->parent_environment->wrapped_bdb_environment;
	
	environment->memp_register(	environment,
								file_type,
								( memory_pool_file_controller->page_in_method == NULL ?
									NULL :
									& Rbdb_MemoryPoolFileController_internal_pageInMethod ),
								( memory_pool_file_controller->page_out_method == NULL ?
									NULL :
									& Rbdb_MemoryPoolFileController_internal_pageOutMethod ) );
}
*/
/**********************
*  pageInMethod  *
**********************/
/*
int (*page_in_method)(	Rbdb_Environment*			environment,
						void*			page_data,
						Rbdb_Data*		page_cookie	) Rbdb_MemoryPoolFileController_pageInMethod(		Rbdb_MemoryPoolFileController*		memory_pool_file_controller )	{
	
	return memory_pool_file_controller->page_in_method;
}
*/
/**************************
*  setPageOutMethod  *
**************************/
/*
//	The ftype parameter specifies the type of file for which the page-in and page-out functions will be called.
//	The ftype value for a file must be a non-zero positive number less than 128 
//	(0 and negative numbers are reserved for internal use by the Berkeley DB library).
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_register.html
void Rbdb_MemoryPoolFileController_setPageOutMethod(		Rbdb_MemoryPoolFileController*		memory_pool_file_controller,
															int									file_type,
															int									(*page_out_method)(	Rbdb_Environment*			environment,
															   									 					void*			page_data,
															   									 					Rbdb_Data*		page_cookie	) )	{
	
	if (	file_type < 1
		||	file_type > 128 )	{

		//	Throw error - negative values reserved for BDB, max value 128
		//	FIX
	}
	
	DB_ENV*	environment	=	memory_pool_file_controller->parent_memory_pool_controller->parent_environment->wrapped_bdb_environment;
	
	environment->memp_register(	environment,
								file_type,
								( memory_pool_file_controller->page_in_method == NULL ?
									NULL :
									& Rbdb_MemoryPoolFileController_internal_pageInMethod ),
								( memory_pool_file_controller->page_out_method == NULL ?
									NULL :
									& Rbdb_MemoryPoolFileController_internal_pageOutMethod ) );
}
*/
/**********************
*  pageOutMethod  *
**********************/
/*
int (*page_out_method)(	Rbdb_Environment*			environment,
						void*			page_data,
						Rbdb_Data*		page_cookie	) Rbdb_MemoryPoolFileController_pageOutMethod(		Rbdb_MemoryPoolFileController*		memory_pool_file_controller )	{
	
	return memory_pool_file_controller->page_out_method;
}
*/

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/**********************
*  pageInMethod  *
**********************/
/*
int Rbdb_MemoryPoolFileController_internal_pageInMethod(	DB_ENV*		bdb_environment,
															db_pgno_t	page_number,
															void*		page_data,
															DBT*		bdb_page_cookie )	{

	//	Retrieve Rbdb environment
	Rbdb_Environment*								environment						=	Rbdb_RuntimeStorageController_internal_environmentForBDBEnvironment( bdb_environment );
	
	//	Retrieve Memory Pool File Controller
	Rbdb_MemoryPoolFileController*		memory_pool_file_controller		=	Rbdb_MemoryPoolController_fileController( Rbdb_Environment_memoryPoolController() );
	
	//	Wrap DBT in Rbdb_Data
	Rbdb_Data*							page_cookie						=	Rbdb_Data_internal_newrb_Rbdb_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT( NULL, bdb_page_cookie );
	
	//	Call user-specified method
	return	*( memory_pool_file_controller->page_in_method )(	memory_pool_file_controller,
																page_data,
																page_cookie		);
}           	
*/
/**********************
*  pageOutMethod  *
**********************/
/*
int Rbdb_MemoryPoolFileController_internal_pageInMethod(	DB_ENV*		environment,
															db_pgno_t	page_number,
															void*		page_address,
															DBT*		page_cookie )	{

	//	Retrieve Rbdb environment
	Rbdb_Environment*								environment						=	Rbdb_RuntimeStorageController_internal_environmentForBDBEnvironment( bdb_environment );
	
	//	Retrieve Memory Pool File Controller
	Rbdb_MemoryPoolFileController*		memory_pool_file_controller		=	Rbdb_MemoryPoolController_fileController( Rbdb_Environment_memoryPoolController() );
	
	//	Wrap DBT in Rbdb_Data
	Rbdb_Data*							page_cookie						=	Rbdb_Data_internal_newrb_Rbdb_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT( NULL, bdb_page_cookie );
	
	//	Call user-specified method
	return	*( memory_pool_file_controller->page_out_method )(	memory_pool_file_controller,
																page_data,
																page_cookie		);
}*/

