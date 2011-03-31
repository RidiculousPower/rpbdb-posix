/*
 *		RPbdb:RPbdb_SettingsController:RPbdb_MemoryPoolSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "MemoryPoolSettingsController.h"

#include "MemoryPoolFile.h"

#include "MemoryPoolFileSettingsController.h"
#include "MemoryPoolReadWriteSettingsController.h"
#include "MemoryPoolSettingsController_internal.h"

#include "SettingsController.h"
#include "LogSettingsController.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_MemoryPoolSettingsController* RPbdb_MemoryPoolSettingsController_new( RPbdb_SettingsController* settings_controller )	{

	RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller = calloc( 1, sizeof( RPbdb_MemoryPoolSettingsController ) );

	memory_pool_settings_controller->parent_settings_controller = settings_controller;

	RPbdb_MemoryPoolSettingsController_internal_initDefaultSettings( memory_pool_settings_controller );

	return memory_pool_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_MemoryPoolSettingsController_free(	RPbdb_MemoryPoolSettingsController** memory_pool_settings_controller )	{

	if ( ( *memory_pool_settings_controller )->file_settings_controller != NULL )	{
		RPbdb_MemoryPoolFileSettingsController_free( & ( ( *memory_pool_settings_controller )->file_settings_controller ) );
	}
	
	free( *memory_pool_settings_controller );
	*memory_pool_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MemoryPoolSettingsController_parentEnvironment(	RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	return memory_pool_settings_controller->parent_settings_controller->parent_environment;
}


/*********
*  on  *
*********/

//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPbdb_MemoryPoolSettingsController_on( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->on == TRUE )	{
		return DB_INIT_MPOOL;	
	}
	return FALSE;
}

/*************
*  off  *
*************/

//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
BOOL RPbdb_MemoryPoolSettingsController_off( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->on == FALSE )	{
		return DB_INIT_MPOOL;	
	}
	return FALSE;
}

	/*************
	*  turnOn  *
	*************/

	//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPbdb_MemoryPoolSettingsController_turnOn( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->on = TRUE;
	}

	/*************
	*  turnOff  *
	*************/

	//	DB_INIT_MPOOL			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPbdb_MemoryPoolSettingsController_turnOff( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->on = FALSE;
	}

/*********************
*  memoryMapping  *
*********************/

//	DB_NOMMAP 				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
//	Note: function default inverts default from flag
int RPbdb_MemoryPoolSettingsController_memoryMapping( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
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
	void RPbdb_MemoryPoolSettingsController_turnMemoryMappingOn( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->memory_mapping = TRUE;
	}

	/*****************************
	*  turnMemoryMappingOff  *
	*****************************/

	//	DB_NOMMAP 				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	//	Note: function default inverts default from flag
	void RPbdb_MemoryPoolSettingsController_turnMemoryMappingOff( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->memory_mapping = FALSE;
	}

/*************************************
*  removeFileWithLastReference  *
*************************************/

//	DB_MPOOL_UNLINK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
int RPbdb_MemoryPoolSettingsController_removeFileWithLastReference( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	if ( memory_pool_settings_controller->remove_file_with_last_reference == TRUE )	{
		return DB_MPOOL_UNLINK;
	}
	return FALSE;
}

	/*****************************************
	*  turnRemoveFileWithLastReferenceOn  *
	*****************************************/

	//	DB_MPOOL_UNLINK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	void RPbdb_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOn( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->remove_file_with_last_reference = TRUE;
	}

	/*****************************************
	*  turnRemoveFileWithLastReferenceOff  *
	*****************************************/

	//	DB_MPOOL_UNLINK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_flags.html
	void RPbdb_MemoryPoolSettingsController_turnRemoveFileWithLastReferenceOff( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
		memory_pool_settings_controller->remove_file_with_last_reference = FALSE;
	}

/******************************************
*  pagesizeFactorMismatchShouldFail  *
******************************************/

//	Attempts to open files which are not a multiple of the page size in length will fail, by default. 
//	If the DB_ODDFILESIZE flag is set, any partial page at the end of the file will be ignored and the open will proceed.
//	DB_ODDFILESIZE	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_fopen.html
int RPbdb_MemoryPoolSettingsController_pagesizeFactorMismatchShouldFail( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	if ( memory_pool_settings_controller->pagesize_factor_mismatch_should_fail == TRUE )	{
		return DB_ODDFILESIZE;
	}
	return FALSE;
}

	/**************************************************
	*  turnPageSizeFactorMismatchShouldFailOn  *
	**************************************************/

	void RPbdb_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOn( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{

		memory_pool_settings_controller->pagesize_factor_mismatch_should_fail = TRUE;
	}

	/**************************************************
	*  turnPageSizeFactorMismatchShouldFailOff  *
	**************************************************/

	void RPbdb_MemoryPoolSettingsController_turnPageSizeFactorMismatchShouldFailOff( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{

		memory_pool_settings_controller->pagesize_factor_mismatch_should_fail = FALSE;
	}


/**************************************************
*  fileSettingsController  *
**************************************************/

RPbdb_MemoryPoolFileSettingsController* RPbdb_MemoryPoolSettingsController_fileSettingsController( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	if ( memory_pool_settings_controller->file_settings_controller == NULL )	{
		memory_pool_settings_controller->file_settings_controller = RPbdb_MemoryPoolFileSettingsController_new( memory_pool_settings_controller );
	}
	return memory_pool_settings_controller->file_settings_controller;
}

/**************************************************
*  readWriteSettingsController  *
**************************************************/

RPbdb_MemoryPoolReadWriteSettingsController* RPbdb_MemoryPoolSettingsController_readWriteSettingsController( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{
	
	if ( memory_pool_settings_controller->record_read_write_settings_controller == NULL )	{
		memory_pool_settings_controller->record_read_write_settings_controller = RPbdb_MemoryPoolReadWriteSettingsController_new( memory_pool_settings_controller );
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

void RPbdb_MemoryPoolSettingsController_internal_initDefaultSettings( RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	memory_pool_settings_controller->on											= FALSE;
	memory_pool_settings_controller->memory_mapping								= FALSE;
	memory_pool_settings_controller->remove_file_with_last_reference 			= FALSE;
	memory_pool_settings_controller->threaded									= FALSE;

}

/*****************
*  closeFlags  *
*****************/

int RPbdb_MemoryPoolSettingsController_internal_closeFlags( RPbdb_MemoryPoolFile* memory_pool_file __attribute__((unused)) )	{

	//	Not currently used - returns 0
	return RPBDB_NO_FLAGS;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_MemoryPoolSettingsController* RPbdb_MemoryPoolSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller )	{

	RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller_copy	=	RPbdb_MemoryPoolSettingsController_new( memory_pool_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	memory_pool_settings_controller_copy->memory_mapping	=	memory_pool_settings_controller->memory_mapping;
	memory_pool_settings_controller_copy->threaded	=	memory_pool_settings_controller->threaded;
	memory_pool_settings_controller_copy->pagesize_factor_mismatch_should_fail	=	memory_pool_settings_controller->pagesize_factor_mismatch_should_fail;
	memory_pool_settings_controller_copy->on	=	memory_pool_settings_controller->on;
	memory_pool_settings_controller_copy->remove_file_with_last_reference	=	memory_pool_settings_controller->remove_file_with_last_reference;

	return memory_pool_settings_controller_copy;
}

