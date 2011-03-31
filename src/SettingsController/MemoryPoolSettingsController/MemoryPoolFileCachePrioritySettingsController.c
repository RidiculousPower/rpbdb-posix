/*
 *		RPbdb::SettingsController::MemoryPoolSettingsController::MemoryPoolFileSettingsController::MemoryPoolFilePageSettingsController::MemoryPoolFilePagePrioritySettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "MemoryPoolFileCachePrioritySettingsController.h"

#include "MemoryPoolFileCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_MemoryPoolFileCachePrioritySettingsController* RPbdb_MemoryPoolFileCachePrioritySettingsController_new( RPbdb_MemoryPoolFileCacheSettingsController*	memory_pool_file_cache_settings_controller )	{

	RPbdb_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller = calloc( 1, sizeof( RPbdb_MemoryPoolFileCachePrioritySettingsController ) );

	memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller = memory_pool_file_cache_settings_controller;

	return memory_pool_file_cache_priority_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_MemoryPoolFileCachePrioritySettingsController_free(	RPbdb_MemoryPoolFileCachePrioritySettingsController** memory_pool_file_cache_priority_settings_controller )	{

	free( *memory_pool_file_cache_priority_settings_controller );
	*memory_pool_file_cache_priority_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MemoryPoolFileCachePrioritySettingsController_parentEnvironment(	RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{
	return memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*************************
*  currentPriority  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_priority.html
DB_CACHE_PRIORITY RPbdb_MemoryPoolFileCachePrioritySettingsController_currentPriority( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	RPbdb_MemoryPoolFile*			db_mpool_file	= memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file;
	
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
BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_veryLow( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

	/*****************
	*  setVeryLow  *
	*****************/

	void RPbdb_MemoryPoolFileCachePrioritySettingsController_setVeryLow( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

	/*********************
	*  atLeastVeryLow  *
	*********************/

	BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastVeryLow( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

	/*********************
	*  atMostVeryLow  *
	*********************/

	BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostVeryLow( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

/************
*  low  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_low( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

	/*************
	*  setLow  *
	*************/

	void RPbdb_MemoryPoolFileCachePrioritySettingsController_setLow( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

	/*****************
	*  atLeastLow  *
	*****************/

	BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastLow( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

	/*****************
	*  atMostLow  *
	******************/

	BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostLow( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

/*****************
*  default  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_default( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

	/*****************
	*  setDefault  *
	*****************/

	void RPbdb_MemoryPoolFileCachePrioritySettingsController_setDefault( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

	/*********************
	*  atLeastDefault  *
	*********************/

	BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastDefault( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

	/*********************
	*  atMostDefault  *
	*********************/

	BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostDefault( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

/*************
*  high  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_high( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

	/*****************
	*  setHigh  *
	*****************/

	void RPbdb_MemoryPoolFileCachePrioritySettingsController_setHigh( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

	/*********************
	*  atLeastHigh  *
	*********************/

	BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastHigh( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

	/*****************
	*  atMostHigh  *
	*****************/

	BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostHigh( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

/*****************
*  veryHigh  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_veryHigh( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

	/*********************
	*  setVeryHigh  *
	*********************/

	void RPbdb_MemoryPoolFileCachePrioritySettingsController_setVeryHigh( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

	/*************************
	*  atLeastVeryHigh  *
	*************************/

	BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastVeryHigh( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

	/*********************
	*  atMostVeryHigh  *
	*********************/

	BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostVeryHigh( RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
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
BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast(	RPbdb_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY											cache_priority )	{

	DB_CACHE_PRIORITY	current_priority	=	RPbdb_MemoryPoolFileCachePrioritySettingsController_currentPriority( memory_pool_file_cache_priority_settings_controller );

	return ( current_priority >= cache_priority ? TRUE : FALSE );
}

/*****************
*  isAtMost  *
*****************/

BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost(	RPbdb_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY											cache_priority )	{

	DB_CACHE_PRIORITY	current_priority	=	RPbdb_MemoryPoolFileCachePrioritySettingsController_currentPriority( memory_pool_file_cache_priority_settings_controller );

	return ( current_priority <= cache_priority ? TRUE : FALSE );
}

/**************************
*  checkIfPriorityIs  *
**************************/

BOOL RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority(	RPbdb_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller, 
																																							DB_CACHE_PRIORITY											cache_priority )	{


	DB_CACHE_PRIORITY	current_priority	=	RPbdb_MemoryPoolFileCachePrioritySettingsController_currentPriority( memory_pool_file_cache_priority_settings_controller );

	return ( current_priority == cache_priority ? TRUE : FALSE );
}

/**********************
*  setPriorityTo  *
**********************/

void RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo(	RPbdb_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY											cache_priority )	{

	RPbdb_MemoryPoolFile*			db_mpool_file	= memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file;

	if ( db_mpool_file != NULL )	{
		db_mpool_file->wrapped_bdb_memory_pool_file->set_priority(	db_mpool_file->wrapped_bdb_memory_pool_file, 
																																cache_priority );
	}
	
	memory_pool_file_cache_priority_settings_controller->priority	=	cache_priority;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_MemoryPoolFileCachePrioritySettingsController* RPbdb_MemoryPoolFileCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller_copy	=	RPbdb_MemoryPoolFileCachePrioritySettingsController_new( memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller );

	//	Instances and Pointers
	memory_pool_file_cache_priority_settings_controller_copy->priority	=	memory_pool_file_cache_priority_settings_controller->priority;

	return memory_pool_file_cache_priority_settings_controller_copy;
}

