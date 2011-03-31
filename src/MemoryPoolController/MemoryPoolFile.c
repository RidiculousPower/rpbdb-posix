/*
 *		RPbdb::MemoryPoolController::MemoryPoolFile
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
 
#include "MemoryPoolFile.h"
#include "MemoryPoolFile_internal.h"

#include "Database_internal.h"

#include "MemoryPoolFileSettingsController.h"
#include "MemoryPoolSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPbdb_MemoryPoolFile* RPbdb_MemoryPoolFile_new( RPbdb_MemoryPoolFileController* parent_memory_pool_file_controller )	{
	
	RPbdb_MemoryPoolFile*		memory_pool_file = calloc( 1, sizeof( RPbdb_MemoryPoolFile ) );

	if ( parent_memory_pool_file_controller->runtime_storage_database != NULL )	{
		memory_pool_file->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_memory_pool_file_controller->runtime_storage_database,
																																												(void*) memory_pool_file );
	}

	memory_pool_file->parent_memory_pool_file_controller = parent_memory_pool_file_controller;

	return memory_pool_file;
}

/***************************
*  free  *
***************************/
void RPbdb_MemoryPoolFile_free(	RPbdb_MemoryPoolFile** memory_pool_file )	{

	if ( ( *memory_pool_file )->parent_memory_pool_file_controller->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *memory_pool_file )->parent_memory_pool_file_controller->runtime_storage_database,
																											( *memory_pool_file )->runtime_identifier );
	}
	RPbdb_MemoryPoolFile_freeFromRuntimeStorage( memory_pool_file );
}

/***************************
*  freeFromRuntimeStorage  *
***************************/
void RPbdb_MemoryPoolFile_freeFromRuntimeStorage(	RPbdb_MemoryPoolFile** memory_pool_file )	{

	if ( ( *memory_pool_file )->settings_controller != NULL )	{
		RPbdb_MemoryPoolFileSettingsController_free( & ( ( *memory_pool_file )->settings_controller ) );
	}

	free( *memory_pool_file );
	*memory_pool_file	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_MemoryPoolFileSettingsController* RPbdb_MemoryPoolFile_settingsController(	RPbdb_MemoryPoolFile* memory_pool_file )	{
	return memory_pool_file->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MemoryPoolFile_parentEnvironment(	RPbdb_MemoryPoolFile* memory_pool_file )	{
	return memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*************
*  sync  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fsync.html
void RPbdb_MemoryPoolFile_sync( RPbdb_MemoryPoolFile* memory_pool_file )	{
	
	memory_pool_file->wrapped_bdb_memory_pool_file->sync( memory_pool_file->wrapped_bdb_memory_pool_file );
}

/*************
*  close  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fclose.html
void RPbdb_MemoryPoolFile_close( RPbdb_MemoryPoolFile* memory_pool_file )	{
	
	memory_pool_file->wrapped_bdb_memory_pool_file->close(	memory_pool_file->wrapped_bdb_memory_pool_file,
	 														RPbdb_MemoryPoolSettingsController_internal_closeFlags( memory_pool_file )	);
}
