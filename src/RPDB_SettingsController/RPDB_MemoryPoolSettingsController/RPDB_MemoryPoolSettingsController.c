/*
 *		RPDB:RPDB_SettingsController:RPDB_MemoryPoolSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MemoryPoolSettingsController.h"

#include "RPDB_MemoryPoolFile.h"

#include "RPDB_MemoryPoolFileSettingsController.h"
#include "RPDB_MemoryPoolReadWriteSettingsController.h"
#include "RPDB_MemoryPoolSettingsController_internal.h"

#include "RPDB_SettingsController.h"
#include "RPDB_LogSettingsController.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_MemoryPoolSettingsController* RPDB_MemoryPoolSettingsController_new( RPDB_SettingsController* settings_controller )	{

	RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller = calloc( 1, sizeof( RPDB_MemoryPoolSettingsController ) );

	memory_pool_settings_controller->parent_settings_controller = settings_controller;

	RPDB_MemoryPoolSettingsController_internal_initDefaultSettings( memory_pool_settings_controller );

	return memory_pool_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_MemoryPoolSettingsController_free(	RPDB_MemoryPoolSettingsController** memory_pool_settings_controller )	{

	if ( ( *memory_pool_settings_controller )->file_settings_controller != NULL )	{
		RPDB_MemoryPoolFileSettingsController_free( & ( ( *memory_pool_settings_controller )->file_settings_controller ) );
	}
	
	free( *memory_pool_settings_controller );
	*memory_pool_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MemoryPoolSettingsController_parentEnvironment(	RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	return memory_pool_settings_controller->parent_settings_controller->parent_environment;
}


/*********
*  on  *
*********/

//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPDB_MemoryPoolSettingsController_on( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->on == TRUE )	{
		return DB_INIT_MPOOL;	
	}
	return FALSE;
}

/*************
*  off  *
*************/

//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
BOOL RPDB_MemoryPoolSettingsController_off( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->on == FALSE )	{
		return DB_INIT_MPOOL;	
	}
	return FALSE;
}

	/*************
	*  turnOn  *
	*************/

	//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_MemoryPoolSettingsController_turnOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->on = TRUE;
	}

	/*************
	*  turnOff  *
	*************/

	//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_MemoryPoolSettingsController_turnOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->on = FALSE;
	}

/*********************
*  memoryMapping  *
*********************/

//	DB_NOMMAP 				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
//	Note: function default inverts default from flag
int RPDB_MemoryPoolSettingsController_memoryMapping( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
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
	void RPDB_MemoryPoolSettingsController_turnMemoryMappingOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->memory_mapping = TRUE;
	}

	/*****************************
	*  turnMemoryMappingOff  *
	*****************************/

	//	DB_NOMMAP 				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	//	Note: function default inverts default from flag
	void RPDB_MemoryPoolSettingsController_turnMemoryMappingOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->memory_mapping = FALSE;
	}

/*************************************
*  removeFileWithLastReference  *
*************************************/

//	DB_MPOOL_UNLINK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
int RPDB_MemoryPoolSettingsController_removeFileWithLastReference( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->remove_file_with_last_reference == TRUE )	{
		return DB_MPOOL_UNLINK;
	}
	return FALSE;
}

	/*****************************************
	*  turnRemoveFileWithLastReferenceOn  *
	*****************************************/

	//	DB_MPOOL_UNLINK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	void RPDB_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->remove_file_with_last_reference = TRUE;
	}

	/*****************************************
	*  turnRemoveFileWithLastReferenceOff  *
	*****************************************/

	//	DB_MPOOL_UNLINK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	void RPDB_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->remove_file_with_last_reference = FALSE;
	}

/******************************************
*  pagesizeFactorMismatchShouldFail  *
******************************************/

//	Attempts to open files which are not a multiple of the page size in length will fail, by default. 
//	If the DB_ODDFILESIZE flag is set, any partial page at the end of the file will be ignored and the open will proceed.
//	DB_ODDFILESIZE	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fopen.html
int RPDB_MemoryPoolSettingsController_pagesizeFactorMismatchShouldFail( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	if ( memory_pool_settings_controller->pagesize_factor_mismatch_should_fail == TRUE )	{
		return DB_ODDFILESIZE;
	}
	return FALSE;
}

	/**************************************************
	*  turnPageSizeFactorMismatchShouldFailOn  *
	**************************************************/

	void RPDB_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOn( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

		memory_pool_settings_controller->pagesize_factor_mismatch_should_fail = TRUE;
	}

	/**************************************************
	*  turnPageSizeFactorMismatchShouldFailOff  *
	**************************************************/

	void RPDB_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOff( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

		memory_pool_settings_controller->pagesize_factor_mismatch_should_fail = FALSE;
	}


/**************************************************
*  fileSettingsController  *
**************************************************/

RPDB_MemoryPoolFileSettingsController* RPDB_MemoryPoolSettingsController_fileSettingsController( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	if ( memory_pool_settings_controller->file_settings_controller == NULL )	{
		memory_pool_settings_controller->file_settings_controller = RPDB_MemoryPoolFileSettingsController_new( memory_pool_settings_controller );
	}
	return memory_pool_settings_controller->file_settings_controller;
}

/**************************************************
*  readWriteSettingsController  *
**************************************************/

RPDB_MemoryPoolReadWriteSettingsController* RPDB_MemoryPoolSettingsController_readWriteSettingsController( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	
	if ( memory_pool_settings_controller->record_read_write_settings_controller == NULL )	{
		memory_pool_settings_controller->record_read_write_settings_controller = RPDB_MemoryPoolReadWriteSettingsController_new( memory_pool_settings_controller );
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

void RPDB_MemoryPoolSettingsController_internal_initDefaultSettings( RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	memory_pool_settings_controller->on											= FALSE;
	memory_pool_settings_controller->memory_mapping								= FALSE;
	memory_pool_settings_controller->remove_file_with_last_reference 			= FALSE;
	memory_pool_settings_controller->threaded									= FALSE;

}

/*****************
*  closeFlags  *
*****************/

int RPDB_MemoryPoolSettingsController_internal_closeFlags( RPDB_MemoryPoolFile* memory_pool_file __attribute__((unused)) )	{

	//	Not currently used - returns 0
	return RPDB_NO_FLAGS;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_MemoryPoolSettingsController* RPDB_MemoryPoolSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	RPDB_MemoryPoolSettingsController* memory_pool_settings_controller_copy	=	RPDB_MemoryPoolSettingsController_new( memory_pool_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	memory_pool_settings_controller_copy->memory_mapping	=	memory_pool_settings_controller->memory_mapping;
	memory_pool_settings_controller_copy->threaded	=	memory_pool_settings_controller->threaded;
	memory_pool_settings_controller_copy->pagesize_factor_mismatch_should_fail	=	memory_pool_settings_controller->pagesize_factor_mismatch_should_fail;
	memory_pool_settings_controller_copy->on	=	memory_pool_settings_controller->on;
	memory_pool_settings_controller_copy->remove_file_with_last_reference	=	memory_pool_settings_controller->remove_file_with_last_reference;

	return memory_pool_settings_controller_copy;
}

