/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "MemoryPoolFileSettingsController.h"

#include "Environment.h"
#include "Record.h"
#include "Data.h"

#include "FileSettingsController.h"
#include "EnvironmentCacheSettingsController.h"
#include "TransactionSettingsController.h"
#include "MemoryPoolSettingsController.h"
#include "MemoryPoolFileSettingsController.h"
#include "MemoryPoolFileCacheSettingsController.h"
#include "MemoryPoolFilePageSettingsController.h"
#include "MemoryPoolFileCacheSettingsController.h"
#include "MemoryPoolFileCachePrioritySettingsController.h"
#include "SettingsController.h"

#include "MemoryPoolFileSettingsController_internal.h"
#include "MemoryPoolFileCachePrioritySettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPbdb_MemoryPoolFileSettingsController* RPbdb_MemoryPoolFileSettingsController_new( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	
	RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller = calloc( 1, sizeof( RPbdb_MemoryPoolFileSettingsController ) );

	memory_pool_file_settings_controller->parent_memory_pool_settings_controller = memory_pool_settings_controller;

	return memory_pool_file_settings_controller;
}

//	We have a general settings controller and a particular settings controller
//	No setting is applied until the particular settings controller is created
//	At that point, any non-NULL values will be applied to the particular instance. 

/***************************
*  free  *
***************************/
void RPbdb_MemoryPoolFileSettingsController_free(	RPbdb_MemoryPoolFileSettingsController** memory_pool_file_settings_controller )	{

	if ( ( *memory_pool_file_settings_controller )->page_settings_controller != NULL )	{
		RPbdb_MemoryPoolFilePageSettingsController_free( & ( ( *memory_pool_file_settings_controller )->page_settings_controller ) );
	}
	if ( ( *memory_pool_file_settings_controller )->cookie != NULL )	{
		RPbdb_Data_free( & ( ( *memory_pool_file_settings_controller )->cookie ) );
	}
	if ( ( *memory_pool_file_settings_controller )->cache_settings_controller != NULL )	{
		RPbdb_MemoryPoolFileCacheSettingsController_free( & ( ( *memory_pool_file_settings_controller )->cache_settings_controller ) );
	}

	free( *memory_pool_file_settings_controller );
	*memory_pool_file_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MemoryPoolFileSettingsController_parentEnvironment(	RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	return memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*********************************************
*  createWithNumberInitialNullBytes  *
*********************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_clear_len.html
int RPbdb_MemoryPoolFileSettingsController_createWithInitialNullBytesNumbering( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
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

void RPbdb_MemoryPoolFileSettingsController_setCreateWithInitialNullBytesNumbering( RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
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
uint8_t* RPbdb_MemoryPoolFileSettingsController_fileID( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
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

void RPbdb_MemoryPoolFileSettingsController_setFileID(	RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																											uint8_t																		file_id[ DB_FILE_ID_LEN ] )	{

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
int RPbdb_MemoryPoolFileSettingsController_fileType( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	if (	memory_pool_file_settings_controller->file_type == RPBDB_UNITIALIZED
		&&	memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->get_ftype(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																					&( memory_pool_file_settings_controller->file_type ) );
	}
	return memory_pool_file_settings_controller->file_type;
}

/*********************
*  setFileType  *
*********************/

void RPbdb_MemoryPoolFileSettingsController_setFileType(	RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
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
int RPbdb_MemoryPoolFileSettingsController_logSequenceNumberOffset( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if (	memory_pool_file_settings_controller->log_sequence_number_offset == RPBDB_UNITIALIZED
		&&	memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->get_lsn_offset(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																						&( memory_pool_file_settings_controller->log_sequence_number_offset ) );
	}
	return memory_pool_file_settings_controller->log_sequence_number_offset;
}

/*********************************
*  setLogSequenceNumberOffset  *
*********************************/

void RPbdb_MemoryPoolFileSettingsController_setLogSequenceNumberOffset(	RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
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
uint64_t RPbdb_MemoryPoolFileSettingsController_maxFileSizeInBytes( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	uint32_t		gigabytes;
	uint32_t		additional_bytes;

	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		
		RPbdb_MemoryPoolFile*	memory_pool_file	=	memory_pool_file_settings_controller->parent_memory_pool_file;
		
		memory_pool_file->wrapped_bdb_memory_pool_file->get_maxsize(	memory_pool_file->wrapped_bdb_memory_pool_file, 
																																	& gigabytes, 
																																	& additional_bytes );

		memory_pool_file_settings_controller->max_file_size_in_bytes =		gigabytes * ( 1024 * 1024 * 1024 )
																																		+ additional_bytes;
	
	}
	
	return memory_pool_file_settings_controller->max_file_size_in_bytes;
}

/************************
*  maxFileSizeInKBytes  *
************************/

long RPbdb_MemoryPoolFileSettingsController_maxFileSizeInKBytes( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	uint64_t	max_file_size_in_bytes	=	RPbdb_MemoryPoolFileSettingsController_maxFileSizeInBytes( memory_pool_file_settings_controller );
	uint32_t	max_file_size_in_kbytes	=	max_file_size_in_bytes / 1024;

	return max_file_size_in_kbytes;
}

/************************
*  maxFileSizeInMBytes  *
************************/

long RPbdb_MemoryPoolFileSettingsController_maxFileSizeInMBytes( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	uint64_t	max_file_size_in_kbytes	=	RPbdb_MemoryPoolFileSettingsController_maxFileSizeInKBytes( memory_pool_file_settings_controller );
	uint32_t	max_file_size_in_mbytes	=	max_file_size_in_kbytes / 1024;

	return max_file_size_in_mbytes;
}

/************************
*  maxFileSizeInGBytes  *
************************/

long RPbdb_MemoryPoolFileSettingsController_maxFileSizeInGBytes( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	uint64_t	max_file_size_in_mbytes	=	RPbdb_MemoryPoolFileSettingsController_maxFileSizeInMBytes( memory_pool_file_settings_controller );
	uint32_t	max_file_size_in_gbytes	=	max_file_size_in_mbytes / 1024;

	return max_file_size_in_gbytes;
}

/**************************
*  setMaxFileSizeInBytes  *
**************************/

void RPbdb_MemoryPoolFileSettingsController_setMaxFileSizeInBytes(	RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint64_t																	max_file_size_in_bytes )	{

	uint32_t		gigabytes;
	uint32_t		additional_bytes;
	
	uint32_t		bytes_in_gigabyte	=	( 1024 * 1024 * 1024 );
	
	additional_bytes	= max_file_size_in_bytes % bytes_in_gigabyte;
	gigabytes					= ( max_file_size_in_bytes - additional_bytes ) / bytes_in_gigabyte;
	
	memory_pool_file_settings_controller->max_file_size_in_bytes = max_file_size_in_bytes;
	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{

		RPbdb_MemoryPoolFile*	memory_pool_file	=	memory_pool_file_settings_controller->parent_memory_pool_file;

		memory_pool_file->wrapped_bdb_memory_pool_file->set_maxsize(	memory_pool_file->wrapped_bdb_memory_pool_file, 
																																	gigabytes,
																																	additional_bytes );
	}
}

/***************************
*  setMaxFileSizeInKBytes  *
***************************/

void RPbdb_MemoryPoolFileSettingsController_setMaxFileSizeInKBytes(	RPbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																		uint32_t 																size_in_kbytes )	{
	
//	uint64_t	size_in_kbytes_64 = size_in_kbytes;
	uint64_t	size_in_bytes	=	(uint64_t) size_in_kbytes * 1024;

	RPbdb_MemoryPoolFileSettingsController_setMaxFileSizeInBytes(	memory_pool_file_settings_controller, 
																																size_in_bytes );
}

/***************************
*  setMaxFileSizeInMBytes  *
***************************/

void RPbdb_MemoryPoolFileSettingsController_setMaxFileSizeInMBytes(	RPbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																		uint32_t																size_in_mbytes )	{

	uint32_t	size_in_kbytes	=	size_in_mbytes * 1024;

	RPbdb_MemoryPoolFileSettingsController_setMaxFileSizeInKBytes(	memory_pool_file_settings_controller, 
																																size_in_kbytes );
}

/***************************
*  setMaxFileSizeInGBytes  *
***************************/

void RPbdb_MemoryPoolFileSettingsController_setMaxFileSizeInGBytes(	RPbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																		uint32_t																size_in_gbytes )	{

	uint32_t	size_in_mbytes	=	size_in_gbytes * 1024;

	RPbdb_MemoryPoolFileSettingsController_setMaxFileSizeInMBytes(	memory_pool_file_settings_controller, 
																																size_in_mbytes );
}

/********************
*  pageSizeInBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_maxsize.html
uint64_t RPbdb_MemoryPoolFileSettingsController_pageSizeInBytes( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	uint32_t		size_in_bytes	=	0;

	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		
		RPbdb_Environment*	parent_environment	=	memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
		parent_environment->wrapped_bdb_environment->get_mp_pagesize(	parent_environment->wrapped_bdb_environment, 
																																	& size_in_bytes );
	}
	
	memory_pool_file_settings_controller->page_size_in_bytes	=		size_in_bytes;
	
	return memory_pool_file_settings_controller->page_size_in_bytes;
}

/*********************
*  pageSizeInKBytes  *
*********************/

long RPbdb_MemoryPoolFileSettingsController_pageSizeInKBytes( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	return RPbdb_MemoryPoolFileSettingsController_pageSizeInBytes( memory_pool_file_settings_controller ) / 1024;
}

/***********************
*  setPageSizeInBytes  *
***********************/

void RPbdb_MemoryPoolFileSettingsController_setPageSizeInBytes(	RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																uint64_t																	page_size_in_bytes )	{

	memory_pool_file_settings_controller->page_size_in_bytes = page_size_in_bytes;
	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{

		RPbdb_Environment*	parent_environment	=	memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
		parent_environment->wrapped_bdb_environment->set_mp_pagesize(	parent_environment->wrapped_bdb_environment, 
																																	page_size_in_bytes );
	}
}

/************************
*  setPageSizeInKBytes  *
************************/

void RPbdb_MemoryPoolFileSettingsController_setPageSizeInKBytes(	RPbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																uint32_t 																size_in_kbytes )	{

	RPbdb_MemoryPoolFileSettingsController_setPageSizeInBytes(	memory_pool_file_settings_controller, 
																														size_in_kbytes * 1024 );
}

/*************
*  cookie  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_pgcookie.html
RPbdb_Data* RPbdb_MemoryPoolFileSettingsController_cookie( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if (	memory_pool_file_settings_controller->cookie == NULL
		&&	memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{

		memory_pool_file_settings_controller->cookie = RPbdb_Data_new( NULL );
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->get_pgcookie(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																																																								memory_pool_file_settings_controller->cookie->wrapped_bdb_dbt );
	}
	return memory_pool_file_settings_controller->cookie;
}

/*****************
*  setCookie  *
*****************/

void RPbdb_MemoryPoolFileSettingsController_setCookie(	RPbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																											RPbdb_Data*																cookie )	{

	memory_pool_file_settings_controller->cookie = cookie;
	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{

		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->set_pgcookie(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																																																								cookie->wrapped_bdb_dbt );
	}
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/**************************
*  cacheController  *
**************************/

RPbdb_MemoryPoolFileCacheSettingsController* RPbdb_MemoryPoolFileSettingsController_cacheSettingsController( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if ( memory_pool_file_settings_controller->cache_settings_controller == NULL )	{
		
		memory_pool_file_settings_controller->cache_settings_controller = RPbdb_MemoryPoolFileCacheSettingsController_new( memory_pool_file_settings_controller );
	}
	return memory_pool_file_settings_controller->cache_settings_controller;
}

/**************************
*  pageController  *
**************************/

RPbdb_MemoryPoolFilePageSettingsController* RPbdb_MemoryPoolFileSettingsController_pageSettingsController( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if ( memory_pool_file_settings_controller->page_settings_controller == NULL )	{
		
		memory_pool_file_settings_controller->page_settings_controller = RPbdb_MemoryPoolFilePageSettingsController_new( memory_pool_file_settings_controller );
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

int RPbdb_MemoryPoolFileSettingsController_internal_createFlags( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller __attribute__((unused)) )	{

	//	Not currently used - returns 0
	return RPBDB_NO_FLAGS;
}

/********************
*  openFlags  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fcreate.html
int RPbdb_MemoryPoolFileSettingsController_internal_openFlags( RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	//	These need to be set up properly
	return	RPbdb_FileSettingsController_createIfNecessary( RPbdb_SettingsController_fileSettingsController( memory_pool_file_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller ) )
			|	RPbdb_EnvironmentCacheSettingsController_buffering( RPbdb_SettingsController_cacheSettingsController( memory_pool_file_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller ) )
			|	RPbdb_TransactionSettingsController_environmentalSnapshotIsolation( RPbdb_SettingsController_transactionSettingsController( memory_pool_file_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller ) )
			|	RPbdb_MemoryPoolSettingsController_memoryMapping( memory_pool_file_settings_controller->parent_memory_pool_settings_controller )
			|	RPbdb_MemoryPoolSettingsController_pagesizeFactorMismatchShouldFail( memory_pool_file_settings_controller->parent_memory_pool_settings_controller )
			|	RPbdb_FileSettingsController_openReadOnly( RPbdb_SettingsController_fileSettingsController( memory_pool_file_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller ) );

}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_MemoryPoolFileSettingsController* RPbdb_MemoryPoolFileSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller_copy	=	RPbdb_MemoryPoolFileSettingsController_new( memory_pool_file_settings_controller->parent_memory_pool_settings_controller );

	//	Instances and Pointers
	memory_pool_file_settings_controller_copy->create_with_number_initial_bytes	=	memory_pool_file_settings_controller->create_with_number_initial_bytes;
	memory_pool_file_settings_controller_copy->max_file_size_in_bytes	=	memory_pool_file_settings_controller->max_file_size_in_bytes;
	memory_pool_file_settings_controller_copy->file_type	=	memory_pool_file_settings_controller->file_type;
	memory_pool_file_settings_controller_copy->log_sequence_number_offset	=	memory_pool_file_settings_controller->log_sequence_number_offset;
	memory_pool_file_settings_controller_copy->file_id	=	memory_pool_file_settings_controller->file_id;

	return memory_pool_file_settings_controller_copy;
}

