/*
 *		RPDB::MemoryPoolFileController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MemoryPoolFileController.h"
#include "RPDB_MemoryPoolFileController_internal.h"

#include "RPDB_MemoryPoolFile.h"
#include "RPDB_MemoryPoolController.h"

#include "RPDB_Environment.h"

#include "RPDB_Data.h"
#include "RPDB_Data_internal.h"

#include "RPDB_SettingsController.h"
#include "RPDB_MemoryPoolSettingsController.h"
#include "RPDB_MemoryPoolFileSettingsController_internal.h"

#include "RPDB_RuntimeStorageController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																												Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_MemoryPoolFileController* RPDB_MemoryPoolFileController_new( RPDB_MemoryPoolController* parent_memory_pool_controller )	{
	
	RPDB_MemoryPoolFileController*		memory_pool_file_controller = calloc( 1, sizeof( RPDB_MemoryPoolFileController ) );

	memory_pool_file_controller->parent_memory_pool_controller = parent_memory_pool_controller;

	return memory_pool_file_controller;
}

/***************************
*  free  *
***************************/
void RPDB_MemoryPoolFileController_free(	RPDB_MemoryPoolFileController** memory_pool_file_controller )	{

	free( memory_pool_file_controller );
}

/***************************
*  settingsController  *
***************************/
RPDB_MemoryPoolFileSettingsController* RPDB_MemoryPoolFileController_settingsController(	RPDB_MemoryPoolFileController* memory_pool_file_controller )	{
	return memory_pool_file_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MemoryPoolFileController_parentEnvironment(	RPDB_MemoryPoolFileController* memory_pool_file_controller )	{
	return memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*****************
*  createFile  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fcreate.html
RPDB_MemoryPoolFile* RPDB_MemoryPoolFileController_createFile( RPDB_MemoryPoolFileController* memory_pool_file_controller )	{
	
	RPDB_Environment*		environment = memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
	
	RPDB_MemoryPoolFile*	memory_pool_file = RPDB_MemoryPoolFile_new( memory_pool_file_controller );
	
	environment->wrapped_bdb_environment->memp_fcreate(	environment->wrapped_bdb_environment,
								&( memory_pool_file->wrapped_bdb_memory_pool_file ),
								RPDB_MemoryPoolFileSettingsController_internal_openFlags( RPDB_MemoryPoolSettingsController_fileSettingsController( RPDB_SettingsController_memoryPoolSettingsController( RPDB_Environment_settingsController( environment ) ) ) ) );
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
RPDB_MemoryPoolFile* RPDB_MemoryPoolFileController_openFile(	RPDB_MemoryPoolFileController*		memory_pool_file_controller,
 																char*								file_path,
																//	This should be broken down into functions that specify the type of mode, probably
																int									chmod_mode,
																//	How do we determine how large pagesize should be?
																size_t								pagesize_in_bytes )	{
	
	RPDB_MemoryPoolFile*	memory_pool_file = RPDB_MemoryPoolFile_new( memory_pool_file_controller );
	
	memory_pool_file->wrapped_bdb_memory_pool_file->open(	memory_pool_file->wrapped_bdb_memory_pool_file,
															file_path,
															RPDB_MemoryPoolFileSettingsController_internal_openFlags( RPDB_MemoryPoolSettingsController_fileSettingsController( RPDB_SettingsController_memoryPoolSettingsController( RPDB_Environment_settingsController( memory_pool_file_controller->parent_memory_pool_controller->parent_environment ) ) ) ),
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
void RPDB_MemoryPoolFileController_setPageInMethod(		RPDB_MemoryPoolFileController*		memory_pool_file_controller,
															int									file_type,
															int									(*page_in_method)(	RPDB_Environment*			environment,
															   														void*			page_data,
															   														RPDB_Data*		page_cookie	))	{
	
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
									& RPDB_MemoryPoolFileController_internal_pageInMethod ),
								( memory_pool_file_controller->page_out_method == NULL ?
									NULL :
									& RPDB_MemoryPoolFileController_internal_pageOutMethod ) );
}
*/
/**********************
*  pageInMethod  *
**********************/
/*
int (*page_in_method)(	RPDB_Environment*			environment,
						void*			page_data,
						RPDB_Data*		page_cookie	) RPDB_MemoryPoolFileController_pageInMethod(		RPDB_MemoryPoolFileController*		memory_pool_file_controller )	{
	
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
void RPDB_MemoryPoolFileController_setPageOutMethod(		RPDB_MemoryPoolFileController*		memory_pool_file_controller,
															int									file_type,
															int									(*page_out_method)(	RPDB_Environment*			environment,
															   									 					void*			page_data,
															   									 					RPDB_Data*		page_cookie	) )	{
	
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
									& RPDB_MemoryPoolFileController_internal_pageInMethod ),
								( memory_pool_file_controller->page_out_method == NULL ?
									NULL :
									& RPDB_MemoryPoolFileController_internal_pageOutMethod ) );
}
*/
/**********************
*  pageOutMethod  *
**********************/
/*
int (*page_out_method)(	RPDB_Environment*			environment,
						void*			page_data,
						RPDB_Data*		page_cookie	) RPDB_MemoryPoolFileController_pageOutMethod(		RPDB_MemoryPoolFileController*		memory_pool_file_controller )	{
	
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
int RPDB_MemoryPoolFileController_internal_pageInMethod(	DB_ENV*		bdb_environment,
															db_pgno_t	page_number,
															void*		page_data,
															DBT*		bdb_page_cookie )	{

	//	Retrieve RPDB environment
	RPDB_Environment*								environment						=	RPDB_RuntimeStorageController_internal_environmentForBDBEnvironment( bdb_environment );
	
	//	Retrieve Memory Pool File Controller
	RPDB_MemoryPoolFileController*		memory_pool_file_controller		=	RPDB_MemoryPoolController_fileController( RPDB_Environment_memoryPoolController() );
	
	//	Wrap DBT in RPDB_Data
	RPDB_Data*							page_cookie						=	RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT( NULL, bdb_page_cookie );
	
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
int RPDB_MemoryPoolFileController_internal_pageInMethod(	DB_ENV*		environment,
															db_pgno_t	page_number,
															void*		page_address,
															DBT*		page_cookie )	{

	//	Retrieve RPDB environment
	RPDB_Environment*								environment						=	RPDB_RuntimeStorageController_internal_environmentForBDBEnvironment( bdb_environment );
	
	//	Retrieve Memory Pool File Controller
	RPDB_MemoryPoolFileController*		memory_pool_file_controller		=	RPDB_MemoryPoolController_fileController( RPDB_Environment_memoryPoolController() );
	
	//	Wrap DBT in RPDB_Data
	RPDB_Data*							page_cookie						=	RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT( NULL, bdb_page_cookie );
	
	//	Call user-specified method
	return	*( memory_pool_file_controller->page_out_method )(	memory_pool_file_controller,
																page_data,
																page_cookie		);
}*/

