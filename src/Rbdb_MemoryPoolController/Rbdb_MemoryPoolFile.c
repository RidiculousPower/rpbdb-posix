/*
 *		Rbdb::MemoryPoolController::MemoryPoolFile
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
 
#include "Rbdb_MemoryPoolFile.h"
#include "Rbdb_MemoryPoolFile_internal.h"

#include "Rbdb_Database_internal.h"

#include "Rbdb_MemoryPoolFileSettingsController.h"
#include "Rbdb_MemoryPoolSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
Rbdb_MemoryPoolFile* Rbdb_MemoryPoolFile_new( Rbdb_MemoryPoolFileController* parent_memory_pool_file_controller )	{
	
	Rbdb_MemoryPoolFile*		memory_pool_file = calloc( 1, sizeof( Rbdb_MemoryPoolFile ) );

	if ( parent_memory_pool_file_controller->runtime_storage_database != NULL )	{
		memory_pool_file->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_memory_pool_file_controller->runtime_storage_database,
																																												(void*) memory_pool_file );
	}

	memory_pool_file->parent_memory_pool_file_controller = parent_memory_pool_file_controller;

	return memory_pool_file;
}

/***************************
*  free  *
***************************/
void Rbdb_MemoryPoolFile_free(	Rbdb_MemoryPoolFile** memory_pool_file )	{

	if ( ( *memory_pool_file )->parent_memory_pool_file_controller->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *memory_pool_file )->parent_memory_pool_file_controller->runtime_storage_database,
																											( *memory_pool_file )->runtime_identifier );
	}
	Rbdb_MemoryPoolFile_freeFromRuntimeStorage( memory_pool_file );
}

/***************************
*  freeFromRuntimeStorage  *
***************************/
void Rbdb_MemoryPoolFile_freeFromRuntimeStorage(	Rbdb_MemoryPoolFile** memory_pool_file )	{

	if ( ( *memory_pool_file )->settings_controller != NULL )	{
		Rbdb_MemoryPoolFileSettingsController_free( & ( ( *memory_pool_file )->settings_controller ) );
	}

	free( *memory_pool_file );
	*memory_pool_file	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_MemoryPoolFileSettingsController* Rbdb_MemoryPoolFile_settingsController(	Rbdb_MemoryPoolFile* memory_pool_file )	{
	return memory_pool_file->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_MemoryPoolFile_parentEnvironment(	Rbdb_MemoryPoolFile* memory_pool_file )	{
	return memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*************
*  sync  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fsync.html
void Rbdb_MemoryPoolFile_sync( Rbdb_MemoryPoolFile* memory_pool_file )	{
	
	memory_pool_file->wrapped_bdb_memory_pool_file->sync( memory_pool_file->wrapped_bdb_memory_pool_file );
}

/*************
*  close  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fclose.html
void Rbdb_MemoryPoolFile_close( Rbdb_MemoryPoolFile* memory_pool_file )	{
	
	memory_pool_file->wrapped_bdb_memory_pool_file->close(	memory_pool_file->wrapped_bdb_memory_pool_file,
	 														Rbdb_MemoryPoolSettingsController_internal_closeFlags( memory_pool_file )	);
}
