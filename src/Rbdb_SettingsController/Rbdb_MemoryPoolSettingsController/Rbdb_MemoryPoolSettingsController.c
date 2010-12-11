/*
 *		Rbdb:Rbdb_SettingsController:Rbdb_MemoryPoolSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_MemoryPoolSettingsController.h"

#include "Rbdb_MemoryPoolFile.h"

#include "Rbdb_MemoryPoolFileSettingsController.h"
#include "Rbdb_MemoryPoolReadWriteSettingsController.h"
#include "Rbdb_MemoryPoolSettingsController_internal.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_LogSettingsController.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_MemoryPoolSettingsController* Rbdb_MemoryPoolSettingsController_new( Rbdb_SettingsController* settings_controller )	{

	Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller = calloc( 1, sizeof( Rbdb_MemoryPoolSettingsController ) );

	memory_pool_settings_controller->parent_settings_controller = settings_controller;

	Rbdb_MemoryPoolSettingsController_internal_initDefaultSettings( memory_pool_settings_controller );

	return memory_pool_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_MemoryPoolSettingsController_free(	Rbdb_MemoryPoolSettingsController** memory_pool_settings_controller )	{

	if ( ( *memory_pool_settings_controller )->file_settings_controller != NULL )	{
		Rbdb_MemoryPoolFileSettingsController_free( & ( ( *memory_pool_settings_controller )->file_settings_controller ) );
	}
	
	free( *memory_pool_settings_controller );
	*memory_pool_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_MemoryPoolSettingsController_parentEnvironment(	Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	return memory_pool_settings_controller->parent_settings_controller->parent_environment;
}


/*********
*  on  *
*********/

//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int Rbdb_MemoryPoolSettingsController_on( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->on == TRUE )	{
		return DB_INIT_MPOOL;	
	}
	return FALSE;
}

/*************
*  off  *
*************/

//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
BOOL Rbdb_MemoryPoolSettingsController_off( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->on == FALSE )	{
		return DB_INIT_MPOOL;	
	}
	return FALSE;
}

	/*************
	*  turnOn  *
	*************/

	//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void Rbdb_MemoryPoolSettingsController_turnOn( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->on = TRUE;
	}

	/*************
	*  turnOff  *
	*************/

	//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void Rbdb_MemoryPoolSettingsController_turnOff( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->on = FALSE;
	}

/*********************
*  memoryMapping  *
*********************/

//	DB_NOMMAP 				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
//	Note: function default inverts default from flag
int Rbdb_MemoryPoolSettingsController_memoryMapping( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->memory_mapping == TRUE )	{
		return DB_NOMMAP;
	}
	return FALSE;
}

	/*****************************
	*  turnMemoryMappingOn  *
	*****************************/

	//	DB_NOMMAP 				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	//	Note: function default inverts default from flag
	void Rbdb_MemoryPoolSettingsController_turnMemoryMappingOn( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->memory_mapping = TRUE;
	}

	/*****************************
	*  turnMemoryMappingOff  *
	*****************************/

	//	DB_NOMMAP 				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	//	Note: function default inverts default from flag
	void Rbdb_MemoryPoolSettingsController_turnMemoryMappingOff( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->memory_mapping = FALSE;
	}

/*************************************
*  removeFileWithLastReference  *
*************************************/

//	DB_MPOOL_UNLINK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
int Rbdb_MemoryPoolSettingsController_removeFileWithLastReference( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->remove_file_with_last_reference == TRUE )	{
		return DB_MPOOL_UNLINK;
	}
	return FALSE;
}

	/*****************************************
	*  turnRemoveFileWithLastReferenceOn  *
	*****************************************/

	//	DB_MPOOL_UNLINK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	void Rbdb_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOn( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->remove_file_with_last_reference = TRUE;
	}

	/*****************************************
	*  turnRemoveFileWithLastReferenceOff  *
	*****************************************/

	//	DB_MPOOL_UNLINK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	void Rbdb_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOff( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->remove_file_with_last_reference = FALSE;
	}

/******************************************
*  pagesizeFactorMismatchShouldFail  *
******************************************/

//	Attempts to open files which are not a multiple of the page size in length will fail, by default. 
//	If the DB_ODDFILESIZE flag is set, any partial page at the end of the file will be ignored and the open will proceed.
//	DB_ODDFILESIZE	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fopen.html
int Rbdb_MemoryPoolSettingsController_pagesizeFactorMismatchShouldFail( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	if ( memory_pool_settings_controller->pagesize_factor_mismatch_should_fail == TRUE )	{
		return DB_ODDFILESIZE;
	}
	return FALSE;
}

	/**************************************************
	*  turnPageSizeFactorMismatchShouldFailOn  *
	**************************************************/

	void Rbdb_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOn( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{

		memory_pool_settings_controller->pagesize_factor_mismatch_should_fail = TRUE;
	}

	/**************************************************
	*  turnPageSizeFactorMismatchShouldFailOff  *
	**************************************************/

	void Rbdb_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOff( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{

		memory_pool_settings_controller->pagesize_factor_mismatch_should_fail = FALSE;
	}


/**************************************************
*  fileSettingsController  *
**************************************************/

Rbdb_MemoryPoolFileSettingsController* Rbdb_MemoryPoolSettingsController_fileSettingsController( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	if ( memory_pool_settings_controller->file_settings_controller == NULL )	{
		memory_pool_settings_controller->file_settings_controller = Rbdb_MemoryPoolFileSettingsController_new( memory_pool_settings_controller );
	}
	return memory_pool_settings_controller->file_settings_controller;
}

/**************************************************
*  readWriteSettingsController  *
**************************************************/

Rbdb_MemoryPoolReadWriteSettingsController* Rbdb_MemoryPoolSettingsController_readWriteSettingsController( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	
	if ( memory_pool_settings_controller->record_read_write_settings_controller == NULL )	{
		memory_pool_settings_controller->record_read_write_settings_controller = Rbdb_MemoryPoolReadWriteSettingsController_new( memory_pool_settings_controller );
	}
	return memory_pool_settings_controller->record_read_write_settings_controller;
}



/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/****************************
*  initDefaultSettings  *
****************************/

void Rbdb_MemoryPoolSettingsController_internal_initDefaultSettings( Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	memory_pool_settings_controller->on											= FALSE;
	memory_pool_settings_controller->memory_mapping								= FALSE;
	memory_pool_settings_controller->remove_file_with_last_reference 			= FALSE;
	memory_pool_settings_controller->threaded									= FALSE;

}

/*****************
*  closeFlags  *
*****************/

int Rbdb_MemoryPoolSettingsController_internal_closeFlags( Rbdb_MemoryPoolFile* memory_pool_file __attribute__((unused)) )	{

	//	Not currently used - returns 0
	return RBDB_NO_FLAGS;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_MemoryPoolSettingsController* Rbdb_MemoryPoolSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller_copy	=	Rbdb_MemoryPoolSettingsController_new( memory_pool_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	memory_pool_settings_controller_copy->memory_mapping	=	memory_pool_settings_controller->memory_mapping;
	memory_pool_settings_controller_copy->threaded	=	memory_pool_settings_controller->threaded;
	memory_pool_settings_controller_copy->pagesize_factor_mismatch_should_fail	=	memory_pool_settings_controller->pagesize_factor_mismatch_should_fail;
	memory_pool_settings_controller_copy->on	=	memory_pool_settings_controller->on;
	memory_pool_settings_controller_copy->remove_file_with_last_reference	=	memory_pool_settings_controller->remove_file_with_last_reference;

	return memory_pool_settings_controller_copy;
}

