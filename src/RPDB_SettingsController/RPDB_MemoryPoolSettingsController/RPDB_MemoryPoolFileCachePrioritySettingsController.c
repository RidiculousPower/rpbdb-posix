/*
 *		RPDB::SettingsController::MemoryPoolSettingsController::MemoryPoolFileSettingsController::MemoryPoolFilePageSettingsController::MemoryPoolFilePagePrioritySettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MemoryPoolFileCachePrioritySettingsController.h"

#include "RPDB_MemoryPoolFileCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_MemoryPoolFileCachePrioritySettingsController* RPDB_MemoryPoolFileCachePrioritySettingsController_new( RPDB_MemoryPoolFileCacheSettingsController*	memory_pool_file_cache_settings_controller )	{

	RPDB_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller = calloc( 1, sizeof( RPDB_MemoryPoolFileCachePrioritySettingsController ) );

	memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller = memory_pool_file_cache_settings_controller;

	return memory_pool_file_cache_priority_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_MemoryPoolFileCachePrioritySettingsController_free(	RPDB_MemoryPoolFileCachePrioritySettingsController** memory_pool_file_cache_priority_settings_controller )	{

	free( *memory_pool_file_cache_priority_settings_controller );
	*memory_pool_file_cache_priority_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MemoryPoolFileCachePrioritySettingsController_parentEnvironment(	RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{
	return memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*************************
*  currentPriority  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_priority.html
DB_CACHE_PRIORITY RPDB_MemoryPoolFileCachePrioritySettingsController_currentPriority( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	RPDB_MemoryPoolFile*			db_mpool_file	= memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file;
	
	if ( db_mpool_file != NULL )	{
		db_mpool_file->wrapped_bdb_memory_pool_file->get_priority(	db_mpool_file->wrapped_bdb_memory_pool_file, 
																																& memory_pool_file_cache_priority_settings_controller->priority );
	}
	return memory_pool_file_cache_priority_settings_controller->priority;
}

/*****************
*  veryLow  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_veryLow( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

	/*****************
	*  setVeryLow  *
	*****************/

	void RPDB_MemoryPoolFileCachePrioritySettingsController_setVeryLow( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		RPDB_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

	/*********************
	*  atLeastVeryLow  *
	*********************/

	BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_isAtLeastVeryLow( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

	/*********************
	*  atMostVeryLow  *
	*********************/

	BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_isAtMostVeryLow( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

/************
*  low  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_low( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

	/*************
	*  setLow  *
	*************/

	void RPDB_MemoryPoolFileCachePrioritySettingsController_setLow( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		RPDB_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

	/*****************
	*  atLeastLow  *
	*****************/

	BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_isAtLeastLow( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

	/*****************
	*  atMostLow  *
	******************/

	BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_isAtMostLow( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

/*****************
*  default  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_default( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

	/*****************
	*  setDefault  *
	*****************/

	void RPDB_MemoryPoolFileCachePrioritySettingsController_setDefault( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		RPDB_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

	/*********************
	*  atLeastDefault  *
	*********************/

	BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_isAtLeastDefault( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

	/*********************
	*  atMostDefault  *
	*********************/

	BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_isAtMostDefault( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

/*************
*  high  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_high( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

	/*****************
	*  setHigh  *
	*****************/

	void RPDB_MemoryPoolFileCachePrioritySettingsController_setHigh( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		RPDB_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

	/*********************
	*  atLeastHigh  *
	*********************/

	BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_isAtLeastHigh( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

	/*****************
	*  atMostHigh  *
	*****************/

	BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_isAtMostHigh( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

/*****************
*  veryHigh  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_veryHigh( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

	/*********************
	*  setVeryHigh  *
	*********************/

	void RPDB_MemoryPoolFileCachePrioritySettingsController_setVeryHigh( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		RPDB_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

	/*************************
	*  atLeastVeryHigh  *
	*************************/

	BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_isAtLeastVeryHigh( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

	/*********************
	*  atMostVeryHigh  *
	*********************/

	BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_isAtMostVeryHigh( RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************
*  isAtLeast  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_priority.html
BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast(	RPDB_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY											cache_priority )	{

	DB_CACHE_PRIORITY	current_priority	=	RPDB_MemoryPoolFileCachePrioritySettingsController_currentPriority( memory_pool_file_cache_priority_settings_controller );

	return ( current_priority >= cache_priority ? TRUE : FALSE );
}

/*****************
*  isAtMost  *
*****************/

BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost(	RPDB_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY											cache_priority )	{

	DB_CACHE_PRIORITY	current_priority	=	RPDB_MemoryPoolFileCachePrioritySettingsController_currentPriority( memory_pool_file_cache_priority_settings_controller );

	return ( current_priority <= cache_priority ? TRUE : FALSE );
}

/**************************
*  checkIfPriorityIs  *
**************************/

BOOL RPDB_MemoryPoolFileCachePrioritySettingsController_internal_isPriority(	RPDB_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller, 
																																							DB_CACHE_PRIORITY											cache_priority )	{


	DB_CACHE_PRIORITY	current_priority	=	RPDB_MemoryPoolFileCachePrioritySettingsController_currentPriority( memory_pool_file_cache_priority_settings_controller );

	return ( current_priority == cache_priority ? TRUE : FALSE );
}

/**********************
*  setPriorityTo  *
**********************/

void RPDB_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo(	RPDB_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY											cache_priority )	{

	RPDB_MemoryPoolFile*			db_mpool_file	= memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file;

	if ( db_mpool_file != NULL )	{
		db_mpool_file->wrapped_bdb_memory_pool_file->set_priority(	db_mpool_file->wrapped_bdb_memory_pool_file, 
																																cache_priority );
	}
	
	memory_pool_file_cache_priority_settings_controller->priority	=	cache_priority;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_MemoryPoolFileCachePrioritySettingsController* RPDB_MemoryPoolFileCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller_copy	=	RPDB_MemoryPoolFileCachePrioritySettingsController_new( memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller );

	//	Instances and Pointers
	memory_pool_file_cache_priority_settings_controller_copy->priority	=	memory_pool_file_cache_priority_settings_controller->priority;

	return memory_pool_file_cache_priority_settings_controller_copy;
}

