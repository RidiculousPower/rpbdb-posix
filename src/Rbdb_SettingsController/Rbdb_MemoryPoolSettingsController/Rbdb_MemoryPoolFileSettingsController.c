/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_MemoryPoolFileSettingsController.h"

#include "Rbdb_Environment.h"
#include "Rbdb_Record.h"
#include "Rbdb_Data.h"

#include "Rbdb_FileSettingsController.h"
#include "Rbdb_EnvironmentCacheSettingsController.h"
#include "Rbdb_TransactionSettingsController.h"
#include "Rbdb_MemoryPoolSettingsController.h"
#include "Rbdb_MemoryPoolFileSettingsController.h"
#include "Rbdb_MemoryPoolFileCacheSettingsController.h"
#include "Rbdb_MemoryPoolFilePageSettingsController.h"
#include "Rbdb_MemoryPoolFileCacheSettingsController.h"
#include "Rbdb_MemoryPoolFileCachePrioritySettingsController.h"
#include "Rbdb_SettingsController.h"

#include "Rbdb_MemoryPoolFileSettingsController_internal.h"
#include "Rbdb_MemoryPoolFileCachePrioritySettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
Rbdb_MemoryPoolFileSettingsController* Rbdb_MemoryPoolFileSettingsController_new( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	
	Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller = calloc( 1, sizeof( Rbdb_MemoryPoolFileSettingsController ) );

	memory_pool_file_settings_controller->parent_memory_pool_settings_controller = memory_pool_settings_controller;

	return memory_pool_file_settings_controller;
}

//	We have a general settings controller and a particular settings controller
//	No setting is applied until the particular settings controller is created
//	At that point, any non-NULL values will be applied to the particular instance. 

/***************************
*  free  *
***************************/
void Rbdb_MemoryPoolFileSettingsController_free(	Rbdb_MemoryPoolFileSettingsController** memory_pool_file_settings_controller )	{

	if ( ( *memory_pool_file_settings_controller )->page_settings_controller != NULL )	{
		Rbdb_MemoryPoolFilePageSettingsController_free( & ( ( *memory_pool_file_settings_controller )->page_settings_controller ) );
	}
	if ( ( *memory_pool_file_settings_controller )->cookie != NULL )	{
		Rbdb_Data_free( & ( ( *memory_pool_file_settings_controller )->cookie ) );
	}
	if ( ( *memory_pool_file_settings_controller )->cache_settings_controller != NULL )	{
		Rbdb_MemoryPoolFileCacheSettingsController_free( & ( ( *memory_pool_file_settings_controller )->cache_settings_controller ) );
	}

	free( *memory_pool_file_settings_controller );
	*memory_pool_file_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_MemoryPoolFileSettingsController_parentEnvironment(	Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	return memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*********************************************
*  createWithNumberInitialNullBytes  *
*********************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_clear_len.html
int Rbdb_MemoryPoolFileSettingsController_createWithInitialNullBytesNumbering( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
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

void Rbdb_MemoryPoolFileSettingsController_setCreateWithInitialNullBytesNumbering( Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
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
uint8_t* Rbdb_MemoryPoolFileSettingsController_fileID( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
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

void Rbdb_MemoryPoolFileSettingsController_setFileID(	Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
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
int Rbdb_MemoryPoolFileSettingsController_fileType( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	if (	memory_pool_file_settings_controller->file_type == Rbdb_UNITIALIZED
		&&	memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->get_ftype(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																					&( memory_pool_file_settings_controller->file_type ) );
	}
	return memory_pool_file_settings_controller->file_type;
}

/*********************
*  setFileType  *
*********************/

void Rbdb_MemoryPoolFileSettingsController_setFileType(	Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
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
int Rbdb_MemoryPoolFileSettingsController_logSequenceNumberOffset( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if (	memory_pool_file_settings_controller->log_sequence_number_offset == Rbdb_UNITIALIZED
		&&	memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->get_lsn_offset(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																						&( memory_pool_file_settings_controller->log_sequence_number_offset ) );
	}
	return memory_pool_file_settings_controller->log_sequence_number_offset;
}

/*********************************
*  setLogSequenceNumberOffset  *
*********************************/

void Rbdb_MemoryPoolFileSettingsController_setLogSequenceNumberOffset(	Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
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
uint64_t Rbdb_MemoryPoolFileSettingsController_maxFileSizeInBytes( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	uint32_t		gigabytes;
	uint32_t		additional_bytes;

	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		
		Rbdb_MemoryPoolFile*	memory_pool_file	=	memory_pool_file_settings_controller->parent_memory_pool_file;
		
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

long Rbdb_MemoryPoolFileSettingsController_maxFileSizeInKBytes( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	uint64_t	max_file_size_in_bytes	=	Rbdb_MemoryPoolFileSettingsController_maxFileSizeInBytes( memory_pool_file_settings_controller );
	uint32_t	max_file_size_in_kbytes	=	max_file_size_in_bytes / 1024;

	return max_file_size_in_kbytes;
}

/************************
*  maxFileSizeInMBytes  *
************************/

long Rbdb_MemoryPoolFileSettingsController_maxFileSizeInMBytes( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	uint64_t	max_file_size_in_kbytes	=	Rbdb_MemoryPoolFileSettingsController_maxFileSizeInKBytes( memory_pool_file_settings_controller );
	uint32_t	max_file_size_in_mbytes	=	max_file_size_in_kbytes / 1024;

	return max_file_size_in_mbytes;
}

/************************
*  maxFileSizeInGBytes  *
************************/

long Rbdb_MemoryPoolFileSettingsController_maxFileSizeInGBytes( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	uint64_t	max_file_size_in_mbytes	=	Rbdb_MemoryPoolFileSettingsController_maxFileSizeInMBytes( memory_pool_file_settings_controller );
	uint32_t	max_file_size_in_gbytes	=	max_file_size_in_mbytes / 1024;

	return max_file_size_in_gbytes;
}

/**************************
*  setMaxFileSizeInBytes  *
**************************/

void Rbdb_MemoryPoolFileSettingsController_setMaxFileSizeInBytes(	Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																	uint64_t																	max_file_size_in_bytes )	{

	uint32_t		gigabytes;
	uint32_t		additional_bytes;
	
	uint32_t		bytes_in_gigabyte	=	( 1024 * 1024 * 1024 );
	
	additional_bytes	= max_file_size_in_bytes % bytes_in_gigabyte;
	gigabytes					= ( max_file_size_in_bytes - additional_bytes ) / bytes_in_gigabyte;
	
	memory_pool_file_settings_controller->max_file_size_in_bytes = max_file_size_in_bytes;
	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{

		Rbdb_MemoryPoolFile*	memory_pool_file	=	memory_pool_file_settings_controller->parent_memory_pool_file;

		memory_pool_file->wrapped_bdb_memory_pool_file->set_maxsize(	memory_pool_file->wrapped_bdb_memory_pool_file, 
																																	gigabytes,
																																	additional_bytes );
	}
}

/***************************
*  setMaxFileSizeInKBytes  *
***************************/

void Rbdb_MemoryPoolFileSettingsController_setMaxFileSizeInKBytes(	Rbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																		uint32_t 																size_in_kbytes )	{
	
//	uint64_t	size_in_kbytes_64 = size_in_kbytes;
	uint64_t	size_in_bytes	=	(uint64_t) size_in_kbytes * 1024;

	Rbdb_MemoryPoolFileSettingsController_setMaxFileSizeInBytes(	memory_pool_file_settings_controller, 
																																size_in_bytes );
}

/***************************
*  setMaxFileSizeInMBytes  *
***************************/

void Rbdb_MemoryPoolFileSettingsController_setMaxFileSizeInMBytes(	Rbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																		uint32_t																size_in_mbytes )	{

	uint32_t	size_in_kbytes	=	size_in_mbytes * 1024;

	Rbdb_MemoryPoolFileSettingsController_setMaxFileSizeInKBytes(	memory_pool_file_settings_controller, 
																																size_in_kbytes );
}

/***************************
*  setMaxFileSizeInGBytes  *
***************************/

void Rbdb_MemoryPoolFileSettingsController_setMaxFileSizeInGBytes(	Rbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																		uint32_t																size_in_gbytes )	{

	uint32_t	size_in_mbytes	=	size_in_gbytes * 1024;

	Rbdb_MemoryPoolFileSettingsController_setMaxFileSizeInMBytes(	memory_pool_file_settings_controller, 
																																size_in_mbytes );
}

/********************
*  pageSizeInBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_maxsize.html
uint64_t Rbdb_MemoryPoolFileSettingsController_pageSizeInBytes( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	uint32_t		size_in_bytes	=	0;

	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{
		
		Rbdb_Environment*	parent_environment	=	memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
		parent_environment->wrapped_bdb_environment->get_mp_pagesize(	parent_environment->wrapped_bdb_environment, 
																																	& size_in_bytes );
	}
	
	memory_pool_file_settings_controller->page_size_in_bytes	=		size_in_bytes;
	
	return memory_pool_file_settings_controller->page_size_in_bytes;
}

/*********************
*  pageSizeInKBytes  *
*********************/

long Rbdb_MemoryPoolFileSettingsController_pageSizeInKBytes( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	return Rbdb_MemoryPoolFileSettingsController_pageSizeInBytes( memory_pool_file_settings_controller ) / 1024;
}

/***********************
*  setPageSizeInBytes  *
***********************/

void Rbdb_MemoryPoolFileSettingsController_setPageSizeInBytes(	Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																																uint64_t																	page_size_in_bytes )	{

	memory_pool_file_settings_controller->page_size_in_bytes = page_size_in_bytes;
	if ( memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{

		Rbdb_Environment*	parent_environment	=	memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
		parent_environment->wrapped_bdb_environment->set_mp_pagesize(	parent_environment->wrapped_bdb_environment, 
																																	page_size_in_bytes );
	}
}

/************************
*  setPageSizeInKBytes  *
************************/

void Rbdb_MemoryPoolFileSettingsController_setPageSizeInKBytes(	Rbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller, 
																																uint32_t 																size_in_kbytes )	{

	Rbdb_MemoryPoolFileSettingsController_setPageSizeInBytes(	memory_pool_file_settings_controller, 
																														size_in_kbytes * 1024 );
}

/*************
*  cookie  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_pgcookie.html
Rbdb_Data* Rbdb_MemoryPoolFileSettingsController_cookie( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if (	memory_pool_file_settings_controller->cookie == NULL
		&&	memory_pool_file_settings_controller->parent_memory_pool_file != NULL )	{

		memory_pool_file_settings_controller->cookie = Rbdb_Data_new( NULL );
		memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file->get_pgcookie(	memory_pool_file_settings_controller->parent_memory_pool_file->wrapped_bdb_memory_pool_file, 
																																																								memory_pool_file_settings_controller->cookie->wrapped_bdb_dbt );
	}
	return memory_pool_file_settings_controller->cookie;
}

/*****************
*  setCookie  *
*****************/

void Rbdb_MemoryPoolFileSettingsController_setCookie(	Rbdb_MemoryPoolFileSettingsController*		memory_pool_file_settings_controller, 
																											Rbdb_Data*																cookie )	{

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

Rbdb_MemoryPoolFileCacheSettingsController* Rbdb_MemoryPoolFileSettingsController_cacheSettingsController( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if ( memory_pool_file_settings_controller->cache_settings_controller == NULL )	{
		
		memory_pool_file_settings_controller->cache_settings_controller = Rbdb_MemoryPoolFileCacheSettingsController_new( memory_pool_file_settings_controller );
	}
	return memory_pool_file_settings_controller->cache_settings_controller;
}

/**************************
*  pageController  *
**************************/

Rbdb_MemoryPoolFilePageSettingsController* Rbdb_MemoryPoolFileSettingsController_pageSettingsController( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{
	
	if ( memory_pool_file_settings_controller->page_settings_controller == NULL )	{
		
		memory_pool_file_settings_controller->page_settings_controller = Rbdb_MemoryPoolFilePageSettingsController_new( memory_pool_file_settings_controller );
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

int Rbdb_MemoryPoolFileSettingsController_internal_createFlags( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller __attribute__((unused)) )	{

	//	Not currently used - returns 0
	return Rbdb_NO_FLAGS;
}

/********************
*  openFlags  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fcreate.html
int Rbdb_MemoryPoolFileSettingsController_internal_openFlags( Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	//	These need to be set up properly
	return	Rbdb_FileSettingsController_createIfNecessary( Rbdb_SettingsController_fileSettingsController( memory_pool_file_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller ) )
			|	Rbdb_EnvironmentCacheSettingsController_buffering( Rbdb_SettingsController_cacheSettingsController( memory_pool_file_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller ) )
			|	Rbdb_TransactionSettingsController_environmentalSnapshotIsolation( Rbdb_SettingsController_transactionSettingsController( memory_pool_file_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller ) )
			|	Rbdb_MemoryPoolSettingsController_memoryMapping( memory_pool_file_settings_controller->parent_memory_pool_settings_controller )
			|	Rbdb_MemoryPoolSettingsController_pagesizeFactorMismatchShouldFail( memory_pool_file_settings_controller->parent_memory_pool_settings_controller )
			|	Rbdb_FileSettingsController_openReadOnly( Rbdb_SettingsController_fileSettingsController( memory_pool_file_settings_controller->parent_memory_pool_settings_controller->parent_settings_controller ) );

}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_MemoryPoolFileSettingsController* Rbdb_MemoryPoolFileSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller )	{

	Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller_copy	=	Rbdb_MemoryPoolFileSettingsController_new( memory_pool_file_settings_controller->parent_memory_pool_settings_controller );

	//	Instances and Pointers
	memory_pool_file_settings_controller_copy->create_with_number_initial_bytes	=	memory_pool_file_settings_controller->create_with_number_initial_bytes;
	memory_pool_file_settings_controller_copy->max_file_size_in_bytes	=	memory_pool_file_settings_controller->max_file_size_in_bytes;
	memory_pool_file_settings_controller_copy->file_type	=	memory_pool_file_settings_controller->file_type;
	memory_pool_file_settings_controller_copy->log_sequence_number_offset	=	memory_pool_file_settings_controller->log_sequence_number_offset;
	memory_pool_file_settings_controller_copy->file_id	=	memory_pool_file_settings_controller->file_id;

	return memory_pool_file_settings_controller_copy;
}

