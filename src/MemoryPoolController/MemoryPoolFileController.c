/*
 *		RPbdb::MemoryPoolFileController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "MemoryPoolFileController.h"
#include "MemoryPoolFileController_internal.h"

#include "MemoryPoolFile.h"
#include "MemoryPoolController.h"

#include "Environment.h"

#include "Data.h"
#include "DBT_internal.h"

#include "SettingsController.h"
#include "MemoryPoolSettingsController.h"
#include "MemoryPoolFileSettingsController_internal.h"

#include "RuntimeStorageController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																												Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_MemoryPoolFileController* RPbdb_MemoryPoolFileController_new( RPbdb_MemoryPoolController* parent_memory_pool_controller )	{
	
	RPbdb_MemoryPoolFileController*		memory_pool_file_controller = calloc( 1, sizeof( RPbdb_MemoryPoolFileController ) );

	memory_pool_file_controller->parent_memory_pool_controller = parent_memory_pool_controller;

	return memory_pool_file_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_MemoryPoolFileController_free(	RPbdb_MemoryPoolFileController** memory_pool_file_controller )	{

	free( memory_pool_file_controller );
}

/***************************
*  settingsController  *
***************************/
RPbdb_MemoryPoolFileSettingsController* RPbdb_MemoryPoolFileController_settingsController(	RPbdb_MemoryPoolFileController* memory_pool_file_controller )	{
	return memory_pool_file_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MemoryPoolFileController_parentEnvironment(	RPbdb_MemoryPoolFileController* memory_pool_file_controller )	{
	return memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*****************
*  createFile  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fcreate.html
RPbdb_MemoryPoolFile* RPbdb_MemoryPoolFileController_createFile( RPbdb_MemoryPoolFileController* memory_pool_file_controller )	{
	
	RPbdb_Environment*		environment = memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
	
	RPbdb_MemoryPoolFile*	memory_pool_file = RPbdb_MemoryPoolFile_new( memory_pool_file_controller );
	
	environment->wrapped_bdb_environment->memp_fcreate(	environment->wrapped_bdb_environment,
								&( memory_pool_file->wrapped_bdb_memory_pool_file ),
								RPbdb_MemoryPoolFileSettingsController_internal_openFlags( RPbdb_MemoryPoolSettingsController_fileSettingsController( RPbdb_SettingsController_memoryPoolSettingsController( RPbdb_Environment_settingsController( environment ) ) ) ) );
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
RPbdb_MemoryPoolFile* RPbdb_MemoryPoolFileController_openFile(	RPbdb_MemoryPoolFileController*		memory_pool_file_controller,
 																char*								file_path,
																//	This should be broken down into functions that specify the type of mode, probably
																int									chmod_mode,
																//	How do we determine how large pagesize should be?
																size_t								pagesize_in_bytes )	{
	
	RPbdb_MemoryPoolFile*	memory_pool_file = RPbdb_MemoryPoolFile_new( memory_pool_file_controller );
	
	memory_pool_file->wrapped_bdb_memory_pool_file->open(	memory_pool_file->wrapped_bdb_memory_pool_file,
															file_path,
															RPbdb_MemoryPoolFileSettingsController_internal_openFlags( RPbdb_MemoryPoolSettingsController_fileSettingsController( RPbdb_SettingsController_memoryPoolSettingsController( RPbdb_Environment_settingsController( memory_pool_file_controller->parent_memory_pool_controller->parent_environment ) ) ) ),
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
void RPbdb_MemoryPoolFileController_setPageInMethod(		RPbdb_MemoryPoolFileController*		memory_pool_file_controller,
															int									file_type,
															int									(*page_in_method)(	RPbdb_Environment*			environment,
															   														void*			page_data,
															   														RPbdb_Data*		page_cookie	))	{
	
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
									& RPbdb_MemoryPoolFileController_internal_pageInMethod ),
								( memory_pool_file_controller->page_out_method == NULL ?
									NULL :
									& RPbdb_MemoryPoolFileController_internal_pageOutMethod ) );
}
*/
/**********************
*  pageInMethod  *
**********************/
/*
int (*page_in_method)(	RPbdb_Environment*			environment,
						void*			page_data,
						RPbdb_Data*		page_cookie	) RPbdb_MemoryPoolFileController_pageInMethod(		RPbdb_MemoryPoolFileController*		memory_pool_file_controller )	{
	
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
void RPbdb_MemoryPoolFileController_setPageOutMethod(		RPbdb_MemoryPoolFileController*		memory_pool_file_controller,
															int									file_type,
															int									(*page_out_method)(	RPbdb_Environment*			environment,
															   									 					void*			page_data,
															   									 					RPbdb_Data*		page_cookie	) )	{
	
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
									& RPbdb_MemoryPoolFileController_internal_pageInMethod ),
								( memory_pool_file_controller->page_out_method == NULL ?
									NULL :
									& RPbdb_MemoryPoolFileController_internal_pageOutMethod ) );
}
*/
/**********************
*  pageOutMethod  *
**********************/
/*
int (*page_out_method)(	RPbdb_Environment*			environment,
						void*			page_data,
						RPbdb_Data*		page_cookie	) RPbdb_MemoryPoolFileController_pageOutMethod(		RPbdb_MemoryPoolFileController*		memory_pool_file_controller )	{
	
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
int RPbdb_MemoryPoolFileController_internal_pageInMethod(	DB_ENV*		bdb_environment,
															db_pgno_t	page_number,
															void*		page_data,
															DBT*		bdb_page_cookie )	{

	//	Retrieve RPbdb environment
	RPbdb_Environment*								environment						=	RPbdb_RuntimeStorageController_internal_environmentForBDBEnvironment( bdb_environment );
	
	//	Retrieve Memory Pool File Controller
	RPbdb_MemoryPoolFileController*		memory_pool_file_controller		=	RPbdb_MemoryPoolController_fileController( RPbdb_Environment_memoryPoolController() );
	
	//	Wrap DBT in RPbdb_Data
	RPbdb_Data*							page_cookie						=	(RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT( NULL, bdb_page_cookie );
	
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
int RPbdb_MemoryPoolFileController_internal_pageInMethod(	DB_ENV*		environment,
															db_pgno_t	page_number,
															void*		page_address,
															DBT*		page_cookie )	{

	//	Retrieve RPbdb environment
	RPbdb_Environment*								environment						=	RPbdb_RuntimeStorageController_internal_environmentForBDBEnvironment( bdb_environment );
	
	//	Retrieve Memory Pool File Controller
	RPbdb_MemoryPoolFileController*		memory_pool_file_controller		=	RPbdb_MemoryPoolController_fileController( RPbdb_Environment_memoryPoolController() );
	
	//	Wrap DBT in RPbdb_Data
	RPbdb_Data*							page_cookie						=	(RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT( NULL, bdb_page_cookie );
	
	//	Call user-specified method
	return	*( memory_pool_file_controller->page_out_method )(	memory_pool_file_controller,
																page_data,
																page_cookie		);
}*/

