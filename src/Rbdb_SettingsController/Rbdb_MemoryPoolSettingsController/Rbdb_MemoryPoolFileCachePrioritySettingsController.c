/*
 *		Rbdb::SettingsController::MemoryPoolSettingsController::MemoryPoolFileSettingsController::MemoryPoolFilePageSettingsController::MemoryPoolFilePagePrioritySettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_MemoryPoolFileCachePrioritySettingsController.h"

#include "Rbdb_MemoryPoolFileCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

Rbdb_MemoryPoolFileCachePrioritySettingsController* Rbdb_MemoryPoolFileCachePrioritySettingsController_new( Rbdb_MemoryPoolFileCacheSettingsController*	memory_pool_file_cache_settings_controller )	{

	Rbdb_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller = calloc( 1, sizeof( Rbdb_MemoryPoolFileCachePrioritySettingsController ) );

	memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller = memory_pool_file_cache_settings_controller;

	return memory_pool_file_cache_priority_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_MemoryPoolFileCachePrioritySettingsController_free(	Rbdb_MemoryPoolFileCachePrioritySettingsController** memory_pool_file_cache_priority_settings_controller )	{

	free( *memory_pool_file_cache_priority_settings_controller );
	*memory_pool_file_cache_priority_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_MemoryPoolFileCachePrioritySettingsController_parentEnvironment(	Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{
	return memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file->parent_memory_pool_file_controller->parent_memory_pool_controller->parent_environment;
}

/*************************
*  currentPriority  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/memp_set_priority.html
DB_CACHE_PRIORITY Rbdb_MemoryPoolFileCachePrioritySettingsController_currentPriority( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	Rbdb_MemoryPoolFile*			db_mpool_file	= memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file;
	
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
BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_veryLow( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
}

	/*****************
	*  setVeryLow  *
	*****************/

	void Rbdb_MemoryPoolFileCachePrioritySettingsController_setVeryLow( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

	/*********************
	*  atLeastVeryLow  *
	*********************/

	BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastVeryLow( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

	/*********************
	*  atMostVeryLow  *
	*********************/

	BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostVeryLow( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_LOW );
	}

/************
*  low  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_low( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_LOW );
}

	/*************
	*  setLow  *
	*************/

	void Rbdb_MemoryPoolFileCachePrioritySettingsController_setLow( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

	/*****************
	*  atLeastLow  *
	*****************/

	BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastLow( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

	/*****************
	*  atMostLow  *
	******************/

	BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostLow( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_LOW );
	}

/*****************
*  default  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_default( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
}

	/*****************
	*  setDefault  *
	*****************/

	void Rbdb_MemoryPoolFileCachePrioritySettingsController_setDefault( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

	/*********************
	*  atLeastDefault  *
	*********************/

	BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastDefault( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

	/*********************
	*  atMostDefault  *
	*********************/

	BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostDefault( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_DEFAULT );
	}

/*************
*  high  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_high( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_HIGH );
}

	/*****************
	*  setHigh  *
	*****************/

	void Rbdb_MemoryPoolFileCachePrioritySettingsController_setHigh( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

	/*********************
	*  atLeastHigh  *
	*********************/

	BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastHigh( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

	/*****************
	*  atMostHigh  *
	*****************/

	BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostHigh( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_HIGH );
	}

/*****************
*  veryHigh  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_set_priority.html
BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_veryHigh( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
}

	/*********************
	*  setVeryHigh  *
	*********************/

	void Rbdb_MemoryPoolFileCachePrioritySettingsController_setVeryHigh( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

	/*************************
	*  atLeastVeryHigh  *
	*************************/

	BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastVeryHigh( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
	}

	/*********************
	*  atMostVeryHigh  *
	*********************/

	BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostVeryHigh( Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

		return Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost( memory_pool_file_cache_priority_settings_controller, DB_PRIORITY_VERY_HIGH );
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
BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtLeast(	Rbdb_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY											cache_priority )	{

	DB_CACHE_PRIORITY	current_priority	=	Rbdb_MemoryPoolFileCachePrioritySettingsController_currentPriority( memory_pool_file_cache_priority_settings_controller );

	return ( current_priority >= cache_priority ? TRUE : FALSE );
}

/*****************
*  isAtMost  *
*****************/

BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isAtMost(	Rbdb_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY											cache_priority )	{

	DB_CACHE_PRIORITY	current_priority	=	Rbdb_MemoryPoolFileCachePrioritySettingsController_currentPriority( memory_pool_file_cache_priority_settings_controller );

	return ( current_priority <= cache_priority ? TRUE : FALSE );
}

/**************************
*  checkIfPriorityIs  *
**************************/

BOOL Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_isPriority(	Rbdb_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller, 
																																							DB_CACHE_PRIORITY											cache_priority )	{


	DB_CACHE_PRIORITY	current_priority	=	Rbdb_MemoryPoolFileCachePrioritySettingsController_currentPriority( memory_pool_file_cache_priority_settings_controller );

	return ( current_priority == cache_priority ? TRUE : FALSE );
}

/**********************
*  setPriorityTo  *
**********************/

void Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_setPriorityTo(	Rbdb_MemoryPoolFileCachePrioritySettingsController*		memory_pool_file_cache_priority_settings_controller, 
																																								DB_CACHE_PRIORITY											cache_priority )	{

	Rbdb_MemoryPoolFile*			db_mpool_file	= memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller->parent_memory_pool_file_settings_controller->parent_memory_pool_file;

	if ( db_mpool_file != NULL )	{
		db_mpool_file->wrapped_bdb_memory_pool_file->set_priority(	db_mpool_file->wrapped_bdb_memory_pool_file, 
																																cache_priority );
	}
	
	memory_pool_file_cache_priority_settings_controller->priority	=	cache_priority;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_MemoryPoolFileCachePrioritySettingsController* Rbdb_MemoryPoolFileCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller )	{

	Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller_copy	=	Rbdb_MemoryPoolFileCachePrioritySettingsController_new( memory_pool_file_cache_priority_settings_controller->parent_memory_pool_file_cache_settings_controller );

	//	Instances and Pointers
	memory_pool_file_cache_priority_settings_controller_copy->priority	=	memory_pool_file_cache_priority_settings_controller->priority;

	return memory_pool_file_cache_priority_settings_controller_copy;
}

