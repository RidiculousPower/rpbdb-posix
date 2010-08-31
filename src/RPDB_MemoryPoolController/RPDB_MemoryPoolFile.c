/*
 *		RPDB::MemoryPoolController::MemoryPoolFile
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
 
#include "RPDB_MemoryPoolFile.h"

#include "RPDB_Database_internal.h"

#include "RPDB_MemoryPoolFileSettingsController.h"
#include "RPDB_MemoryPoolSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_MemoryPoolFile* RPDB_MemoryPoolFile_new( RPDB_MemoryPoolFileController* parent_memory_pool_file_controller )	{
	
	RPDB_MemoryPoolFile*		memory_pool_file = calloc( 1, sizeof( RPDB_MemoryPoolFile ) );

	if ( parent_memory_pool_file_controller->runtime_storage_database != NULL )	{
		memory_pool_file->runtime_identifier =	RPDB_Database_internal_storeRuntimeAddress(	parent_memory_pool_file_controller->runtime_storage_database,
																																												(void*) memory_pool_file );
	}

	memory_pool_file->parent_memory_pool_file_controller = parent_memory_pool_file_controller;

	return memory_pool_file;
}

/***************************
*  free  *
***************************/
void RPDB_MemoryPoolFile_free(	RPDB_MemoryPoolFile** memory_pool_file )	{

	if ( ( *memory_pool_file )->parent_memory_pool_file_controller->runtime_storage_database != NULL )	{
		RPDB_Database_internal_freeStoredRuntimeAddress(	( *memory_pool_file )->parent_memory_pool_file_controller->runtime_storage_database,
																											( *memory_pool_file )->runtime_identifier );
	}

	if ( ( *memory_pool_file )->settings_controller != NULL )	{
		RPDB_MemoryPoolFileSettingsController_free( & ( ( *memory_pool_file )->settings_controller ) );
	}

	free( *memory_pool_file );
	*memory_pool_file	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_MemoryPoolFileSettingsController* RPDB_MemoryPoolFile_settingsController(	RPDB_MemoryPoolFile* memory_pool_file )	{
	return memory_pool_file->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MemoryPoolFile_parentEnvironment(	RPDB_MemoryPoolFile* memory_pool_file )	{
	return memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*************
*  sync  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fsync.html
void RPDB_MemoryPoolFile_sync( RPDB_MemoryPoolFile* memory_pool_file )	{
	
	memory_pool_file->wrapped_bdb_memory_pool_file->sync( memory_pool_file->wrapped_bdb_memory_pool_file );
}

/*************
*  close  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fclose.html
void RPDB_MemoryPoolFile_close( RPDB_MemoryPoolFile* memory_pool_file )	{
	
	memory_pool_file->wrapped_bdb_memory_pool_file->close(	memory_pool_file->wrapped_bdb_memory_pool_file,
	 														RPDB_MemoryPoolSettingsController_internal_closeFlags( memory_pool_file )	);
}
