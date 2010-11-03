/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MemoryPoolFileSettingsController.h"

#include "RPDB_Environment.h"
#include "RPDB_Record.h"

#include "RPDB_FileSettingsController.h"
#include "RPDB_EnvironmentCacheSettingsController.h"
#include "RPDB_TransactionSettingsController.h"
#include "RPDB_MemoryPoolSettingsController.h"
#include "RPDB_MemoryPoolFileSettingsController.h"
#include "RPDB_MemoryPoolFileCacheSettingsController.h"
#include "RPDB_MemoryPoolFilePageSettingsController.h"
#include "RPDB_MemoryPoolFileCacheSettingsController.h"
#include "RPDB_MemoryPoolFileCachePrioritySettingsController.h"
#include "RPDB_SettingsController.h"

#include "RPDB_MemoryPoolFileSettingsController_internal.h"
#include "RPDB_MemoryPoolFileCachePrioritySettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_MemoryPoolFileSettingsController* RPDB_MemoryPoolFileSettingsController_new( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	
	RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller = calloc( 1, sizeof( RPDB_MemoryPoolFileSettingsController ) );

	memory_pool_file_settings_controller->parent_memory_pool_settings_controller = memory_pool_settings_controller;

	return memory_pool_file_settings_controller;
}

//	We have a general settings controller and a particular settings controller
//	No setting is applied until the particular settings controller is created
//	At that point, any non-NULL values will be applied to the particular instance. 

/***************************
*  free  *
***************************/
void RPDB_MemoryPoolFileSettingsController_free(	RPDB_MemoryPoolFileSettingsController** memory_pool_file_settings_controller )	{

	if ( ( *memory_pool_file_settings_controller )->page_settings_controller != NULL )	{
		RPDB_MemoryPoolFilePageSettingsController_free( & ( ( *memory_pool_file_settings_controller )->page_settings_controller ) );
	}
	if ( ( *memory_pool_file_settings_controller )->cookie != NULL )	{
		RPDB_Record_free( & ( ( *memory_pool_file_settings_controller )->cookie ) );
	}
	if ( ( *memory_pool_file_settings_controller )->cache_settings_controller != NULL )	{
		RPDB_MemoryPoolFileCacheSettingsController_free( & ( ( *memory_pool_file_settings_controller )->cache_settings_controller ) );
	}

	free( *memory_pool_file_settings_controller );
	*memory_pool_file_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MemoryPoolFileSettingsController_parentEnvironment(	RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	return memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*********************************************
*  createWithNumberInitialNullBytes  *
*********************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_clear_len.html
int RPDB_MemoryPoolFileSettingsController_createWithNumberInitialNullBytes( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if (	memory_pool_file_settings_controller->create_with_number_initial_bytes == FALSE
		&&	memory_pool_file_settings_controller->parent_memory_pool_file != FALSE )	{
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->get_clear_len(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																						&( memory_pool_file_settings_controller->create_with_number_initial_bytes ) );
	}
	return memory_pool_file_settings_controller->create_with_number_initial_bytes;
}

/*************************************************
*  setReturnsCreateWithNumberInitialNullBytes  *
*************************************************/

void RPDB_MemoryPoolFileSettingsController_setReturnsCreateWithNumberInitialNullBytes( RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																						int											initial_null_bytes )	{

	memory_pool_file_settings_controller->create_with_number_initial_bytes = initial_null_bytes;
	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->set_clear_len(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																													memory_pool_file_settings_controller->create_with_number_initial_bytes );
	}
}

/*************
*  fileID  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_fileid.html
uint8_t* RPDB_MemoryPoolFileSettingsController_fileID( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if (	memory_pool_file_settings_controller->file_id == 0
		&&	memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->get_fileid(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																													memory_pool_file_settings_controller->file_id );
	}
	return memory_pool_file_settings_controller->file_id;
}

/*****************
*  setFileID  *
*****************/

void RPDB_MemoryPoolFileSettingsController_setFileID(	RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
														uint8_t*									file_id )	{

	memory_pool_file_settings_controller->file_id = file_id;
	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->set_fileid(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																													memory_pool_file_settings_controller->file_id );
	}
}

/*****************
*  fileType  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_ftype.html
//	The ftype parameter sets the file's type for the purposes of input and output processing. 
//	The ftype must be the same as a ftype parameter previously specified to the DB_ENV->memp_register method.
int RPDB_MemoryPoolFileSettingsController_fileType( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	if (	memory_pool_file_settings_controller->file_type == RPDB_UNITIALIZED
		&&	memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->get_ftype(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																					&( memory_pool_file_settings_controller->file_type ) );
	}
	return memory_pool_file_settings_controller->file_type;
}

/*********************
*  setFileType  *
*********************/

void RPDB_MemoryPoolFileSettingsController_setFileType(	RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
															int											file_type )	{

	memory_pool_file_settings_controller->file_type = file_type;
	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->set_ftype(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																					memory_pool_file_settings_controller->file_type );
	}
}

/*********************************
*  logSequenceNumberOffset  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_lsn_offset.html
int RPDB_MemoryPoolFileSettingsController_logSequenceNumberOffset( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if (	memory_pool_file_settings_controller->log_sequence_number_offset == RPDB_UNITIALIZED
		&&	memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->get_lsn_offset(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																						&( memory_pool_file_settings_controller->log_sequence_number_offset ) );
	}
	return memory_pool_file_settings_controller->log_sequence_number_offset;
}

/*********************************
*  setLogSequenceNumberOffset  *
*********************************/

void RPDB_MemoryPoolFileSettingsController_setLogSequenceNumberOffset(	RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																		int32_t										log_sequence_number_offset )	{

	memory_pool_file_settings_controller->log_sequence_number_offset = log_sequence_number_offset;
	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->set_lsn_offset(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																						memory_pool_file_settings_controller->log_sequence_number_offset );
	}
}

/***********************
*  maxFileSizeInBytes  *
***********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_maxsize.html
uint64_t RPDB_MemoryPoolFileSettingsController_maxFileSizeInBytes( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	uint32_t		gigabytes;
	uint32_t		additional_bytes;

	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		
		RPDB_MemoryPoolFile*	memory_pool_file	=	memory_pool_file_settings_controller->parent_memory_pool_file;
		
		memory_pool_file->wrapped_bdb_memory_pool_file->get_maxsize(	memory_pool_file->wrapped_bdb_memory_pool_file, 
																																	& gigabytes, 
																																	& additional_bytes );
	}
	
	memory_pool_file_settings_controller->max_file_size_in_bytes =		gigabytes * ( 1024 * 1024 * 1024 )
																																	+ additional_bytes;
	
	return memory_pool_file_settings_controller->max_file_size_in_bytes;
}

/************************
*  maxFileSizeInKBytes  *
************************/

long RPDB_MemoryPoolFileSettingsController_maxFileSizeInKBytes( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	return RPDB_MemoryPoolFileSettingsController_maxFileSizeInBytes( memory_pool_file_settings_controller ) / 1024;
}

/************************
*  maxFileSizeInMBytes  *
************************/

long RPDB_MemoryPoolFileSettingsController_maxFileSizeInMBytes( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	return RPDB_MemoryPoolFileSettingsController_maxFileSizeInKBytes( memory_pool_file_settings_controller ) / 1024;
}

/************************
*  maxFileSizeInGBytes  *
************************/

long RPDB_MemoryPoolFileSettingsController_maxFileSizeInGBytes( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	return RPDB_MemoryPoolFileSettingsController_maxFileSizeInMBytes( memory_pool_file_settings_controller ) / 1024;
}

/**************************
*  setMaxFileSizeInBytes  *
**************************/

void RPDB_MemoryPoolFileSettingsController_setMaxFileSizeInBytes(	RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint64_t																	max_file_size_in_bytes )	{

	uint32_t		gigabytes;
	uint32_t		additional_bytes;
	
	additional_bytes = max_file_size_in_bytes % ( 1024 * 1024 * 1024 );
	gigabytes = ( max_file_size_in_bytes - additional_bytes ) / ( 1024 * 1024 * 1024 );
	
	memory_pool_file_settings_controller->max_file_size_in_bytes = max_file_size_in_bytes;
	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{

		RPDB_MemoryPoolFile*	memory_pool_file	=	memory_pool_file_settings_controller->parent_memory_pool_file;

		memory_pool_file->wrapped_bdb_memory_pool_file->set_maxsize(	memory_pool_file->wrapped_bdb_memory_pool_file, 
																																	gigabytes,
																																	additional_bytes );
	}
}

/***************************
*  setMaxFileSizeInKBytes  *
***************************/

void RPDB_MemoryPoolFileSettingsController_setMaxFileSizeInKBytes(	RPDB_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																		uint32_t 																size_in_kbytes )	{

	RPDB_MemoryPoolFileSettingsController_setMaxFileSizeInBytes(	memory_pool_file_settings_controller, 
																																size_in_kbytes * 1024 );
}

/***************************
*  setMaxFileSizeInMBytes  *
***************************/

void RPDB_MemoryPoolFileSettingsController_setMaxFileSizeInMBytes(	RPDB_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																		uint32_t																size_in_mbytes )	{

	RPDB_MemoryPoolFileSettingsController_setMaxFileSizeInKBytes(	memory_pool_file_settings_controller, 
																																size_in_mbytes * 1024 * 1024 );
}

/***************************
*  setMaxFileSizeInGBytes  *
***************************/

void RPDB_MemoryPoolFileSettingsController_setMaxFileSizeInGBytes(	RPDB_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																		uint32_t																size_in_gbytes )	{

	RPDB_MemoryPoolFileSettingsController_setMaxFileSizeInMBytes(	memory_pool_file_settings_controller, 
																																size_in_gbytes * 1024 * 1024 * 1024 );
}

/********************
*  pageSizeInBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_maxsize.html
uint64_t RPDB_MemoryPoolFileSettingsController_pageSizeInBytes( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	uint32_t		size_in_bytes	=	0;

	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		
		RPDB_Environment*	parent_environment	=	memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
		parent_environment->wrapped_bdb_environment->get_mp_pagesize(	parent_environment->wrapped_bdb_environment, 
																																	& size_in_bytes );
	}
	
	memory_pool_file_settings_controller->page_size_in_bytes	=		size_in_bytes;
	
	return memory_pool_file_settings_controller->page_size_in_bytes;
}

/*********************
*  pageSizeInKBytes  *
*********************/

long RPDB_MemoryPoolFileSettingsController_pageSizeInKBytes( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	return RPDB_MemoryPoolFileSettingsController_pageSizeInBytes( memory_pool_file_settings_controller ) / 1024;
}

/***********************
*  setPageSizeInBytes  *
***********************/

void RPDB_MemoryPoolFileSettingsController_setPageSizeInBytes(	RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																uint64_t																	page_size_in_bytes )	{

	memory_pool_file_settings_controller->page_size_in_bytes = page_size_in_bytes;
	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{

		RPDB_Environment*	parent_environment	=	memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
		parent_environment->wrapped_bdb_environment->set_mp_pagesize(	parent_environment->wrapped_bdb_environment, 
																																	page_size_in_bytes );
	}
}

/************************
*  setPageSizeInKBytes  *
************************/

void RPDB_MemoryPoolFileSettingsController_setPageSizeInKBytes(	RPDB_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																uint32_t 																size_in_kbytes )	{

	RPDB_MemoryPoolFileSettingsController_setPageSizeInBytes(	memory_pool_file_settings_controller, 
																														size_in_kbytes * 1024 );
}

/*************
*  cookie  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_pgcookie.html
RPDB_Record* RPDB_MemoryPoolFileSettingsController_cookie( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if (	memory_pool_file_settings_controller->cookie == NULL
		&&	memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{

		memory_pool_file_settings_controller->cookie = RPDB_Record_new( NULL );
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->get_pgcookie(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																																														memory_pool_file_settings_controller->cookie->data->wrapped_bdb_dbt );
	}
	return memory_pool_file_settings_controller->cookie;
}

/*****************
*  setCookie  *
*****************/

void RPDB_MemoryPoolFileSettingsController_setCookie(	RPDB_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
														RPDB_Record*								cookie )	{

	memory_pool_file_settings_controller->cookie = cookie;
	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{

		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->set_pgcookie(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																						cookie->data->wrapped_bdb_dbt );
	}
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/**************************
*  cacheController  *
**************************/

RPDB_MemoryPoolFileCacheSettingsController* RPDB_MemoryPoolFileSettingsController_cacheSettingsController( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if ( memory_pool_file_settings_controller->cache_settings_controller == NULL )	{
		
		memory_pool_file_settings_controller->cache_settings_controller = RPDB_MemoryPoolFileCacheSettingsController_new( memory_pool_file_settings_controller );
	}
	return memory_pool_file_settings_controller->cache_settings_controller;
}

/**************************
*  pageController  *
**************************/

RPDB_MemoryPoolFilePageSettingsController* RPDB_MemoryPoolFileSettingsController_pageSettingsController( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if ( memory_pool_file_settings_controller->page_settings_controller == NULL )	{
		
		memory_pool_file_settings_controller->page_settings_controller = RPDB_MemoryPoolFilePageSettingsController_new( memory_pool_file_settings_controller );
	}
	return memory_pool_file_settings_controller->page_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************************
*  createFlags  *
************************/

int RPDB_MemoryPoolFileSettingsController_internal_createFlags( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller __attribute__((unused)) )	{

	//	Not currently used - returns 0
	return RPDB_NO_FLAGS;
}

/********************
*  openFlags  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fcreate.html
int RPDB_MemoryPoolFileSettingsController_internal_openFlags( RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	//	These need to be set up properly
	return	RPDB_FileSettingsController_createIfNecessary( RPDB_SettingsController_fileSettingsController( memory_pool_file_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller ) )
			|	RPDB_EnvironmentCacheSettingsController_buffering( RPDB_SettingsController_cacheSettingsController( memory_pool_file_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller ) )
			|	RPDB_TransactionSettingsController_environmentalSnapshotIsolation( RPDB_SettingsController_transactionSettingsController( memory_pool_file_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller ) )
			|	RPDB_MemoryPoolSettingsController_memoryMapping( memory_pool_file_settings_controller->parent_memory_pool_settings_controller )
			|	RPDB_MemoryPoolSettingsController_pagesizeFactorMismatchShouldFail( memory_pool_file_settings_controller->parent_memory_pool_settings_controller )
			|	RPDB_FileSettingsController_openReadOnly( RPDB_SettingsController_fileSettingsController( memory_pool_file_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller ) );

}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_MemoryPoolFileSettingsController* RPDB_MemoryPoolFileSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller_copy	=	RPDB_MemoryPoolFileSettingsController_new( memory_pool_file_settings_controller->parent_memory_pool_settings_controller );

	//	Instances and Pointers
	memory_pool_file_settings_controller_copy->create_with_number_initial_bytes	=	memory_pool_file_settings_controller->create_with_number_initial_bytes;
	memory_pool_file_settings_controller_copy->max_file_size_in_bytes	=	memory_pool_file_settings_controller->max_file_size_in_bytes;
	memory_pool_file_settings_controller_copy->file_type	=	memory_pool_file_settings_controller->file_type;
	memory_pool_file_settings_controller_copy->log_sequence_number_offset	=	memory_pool_file_settings_controller->log_sequence_number_offset;
	memory_pool_file_settings_controller_copy->file_id	=	memory_pool_file_settings_controller->file_id;

	return memory_pool_file_settings_controller_copy;
}

