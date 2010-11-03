/*
 *		RPDB::RPDB_SettingsController::RPDB_DatabaseCacheSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseCacheSettingsController.h"

#include "RPDB_ErrorController.h"
#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_DatabaseCacheSettingsController.h"
#include "RPDB_DatabaseCachePrioritySettingsController.h"

#include "RPDB_DatabaseCacheSettingsController_internal.h"
#include "RPDB_DatabaseCachePrioritySettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_DatabaseCacheSettingsController* RPDB_DatabaseCacheSettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller = calloc( 1, sizeof( RPDB_DatabaseCacheSettingsController ) );

	database_cache_settings_controller->parent_database_settings_controller = database_settings_controller;

	RPDB_DatabaseCacheSettingsController_internal_initDefaultSettings( database_cache_settings_controller );

	return database_cache_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseCacheSettingsController_free(	RPDB_DatabaseCacheSettingsController** database_cache_settings_controller )	{

	if ( ( *database_cache_settings_controller )->priority_settings_controller != NULL )	{
		RPDB_DatabaseCachePrioritySettingsController_free( & ( ( *database_cache_settings_controller )->priority_settings_controller ) );
	}

	free( *database_cache_settings_controller );
	*database_cache_settings_controller		=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseCacheSettingsController_parentEnvironment(	RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{
	return database_cache_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseCacheSettingsController_parentDatabase(	RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{
	return database_cache_settings_controller->parent_database_settings_controller->parent_database;
}

/********************
*  maxSizeInBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_cachesize.html
//	Because databases opened within Berkeley DB environments use the cache specified to the environment, 
//	it is an error to attempt to set a cache in a database created within an environment.
uint64_t RPDB_DatabaseCacheSettingsController_maxSizeInBytes( RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{

	RPDB_Database*				database;
	uint32_t				gigabytes_size;
	uint32_t				additional_bytes_size;
	
	if ( RPDB_DatabaseCacheSettingsController_internal_isInEnvironment( database_cache_settings_controller ) )	{
		RPDB_ErrorController_throwError(	RPDB_ErrorController_new( NULL ), 
											RP_ERROR_NO_SETTING_DB_CACHE_WHILE_IN_ENVIRONMENT, 
											"RPDB_DatabaseCacheSettingsController_maxSizeInBytes", 
											"This setting is only for when using a database outside an environment." );
		return 0;
	}
	
	//	Once we've grabbed cache size once, any time it's changed we've updated the change already
	if ( database_cache_settings_controller->max_size_in_bytes == 0 )	{
	
			//	No environment, so we know we're dealing with an instance settings controller
			database =	database_cache_settings_controller->parent_database_settings_controller->parent_database;

			database->wrapped_bdb_database->get_cachesize(	database->wrapped_bdb_database, 
										& gigabytes_size, 
										& additional_bytes_size, 
										&( database_cache_settings_controller->number_cache_regions ) );
	}

	database_cache_settings_controller->max_size_in_bytes =		gigabytes_size
															*	1024 /*  megs  */ 
															*	1024 /*  kbytes  */ 
															*	1024 /*  bytes  */ 
															+	additional_bytes_size; 
	
	//	Return in bytes
	return database_cache_settings_controller->max_size_in_bytes;
}

	/********************
	*  maxSizeInKBytes  *
	********************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_cachesize.html
	long RPDB_DatabaseCacheSettingsController_maxSizeInKBytes( RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{

		float	max_size_kbytes = (float)RPDB_DatabaseCacheSettingsController_maxSizeInBytes( database_cache_settings_controller );
		
		return max_size_kbytes / (float)1024;
	}

	/********************
	*  maxSizeInMBytes  *
	********************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_cachesize.html
	long RPDB_DatabaseCacheSettingsController_maxSizeInMBytes( RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{

		float	max_size_mbytes = (float)RPDB_DatabaseCacheSettingsController_maxSizeInKBytes( database_cache_settings_controller );
		
		return max_size_mbytes / (float)1024;
	}

	/********************
	*  maxSizeInGBytes  *
	********************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_cachesize.html
	long RPDB_DatabaseCacheSettingsController_maxSizeInGBytes( RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{

		float	max_size_gbytes = (float)RPDB_DatabaseCacheSettingsController_maxSizeInMBytes( database_cache_settings_controller );
		
		return max_size_gbytes / (float)1024;
	}

/************************
*  setMaxSizeInBytes  *
************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_cachesize.html
//	Because databases opened within Berkeley DB environments use the cache specified to the environment, 
//	it is an error to attempt to set a cache in a database created within an environment.
void RPDB_DatabaseCacheSettingsController_setMaxSizeInBytes(	RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																uint32_t									max_size_in_bytes )	{

	uint32_t	additional_bytes_size					= max_size_in_bytes % (1024 * 1024 * 1024);
	uint32_t	gigabytes_size							= max_size_in_bytes - additional_bytes_size;
	
	if ( RPDB_DatabaseCacheSettingsController_internal_isInEnvironment( database_cache_settings_controller ) )	{
		RPDB_ErrorController_throwError(	RPDB_ErrorController_new( NULL ), 
											RP_ERROR_NO_SETTING_DB_CACHE_WHILE_IN_ENVIRONMENT, 
										 "RPDB_DatabaseCacheSettingsController_setMaxSizeInBytes", 
										 "This setting is only for when using a database outside an environment." );
		return;
	}

	//	No environment, so we know we're dealing with an instance settings controller
	RPDB_Database*		database =	database_cache_settings_controller->parent_database_settings_controller->parent_database;

	if ( database->wrapped_bdb_database != NULL )	{
		database->wrapped_bdb_database->set_cachesize(	database->wrapped_bdb_database, 
									gigabytes_size, 
									additional_bytes_size, 
									database_cache_settings_controller->number_cache_regions );
	}
	
	//	Store the setting for reference later
	database_cache_settings_controller->max_size_in_bytes = max_size_in_bytes;
}

	/************************
	*  setMaxSizeInKBytes  *
	************************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
	void RPDB_DatabaseCacheSettingsController_setMaxSizeInKBytes(	RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																	uint32_t									max_size_kbytes )	{
		RPDB_DatabaseCacheSettingsController_setMaxSizeInBytes(	database_cache_settings_controller, 
																	max_size_kbytes * 1024 );
	}

	/************************
	*  setMaxSizeInMBytes  *
	************************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
	void RPDB_DatabaseCacheSettingsController_setMaxSizeInMBytes(	RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																	uint32_t									max_size_mbytes )	{
		RPDB_DatabaseCacheSettingsController_setMaxSizeInKBytes(	database_cache_settings_controller, 
																	max_size_mbytes * 1024 );
	}

	/************************
	*  setMaxSizeInGBytes  *
	************************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
	void RPDB_DatabaseCacheSettingsController_setMaxSizeInGBytes(	RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																	uint32_t									max_size_gbytes )	{
		RPDB_DatabaseCacheSettingsController_setMaxSizeInMBytes(	database_cache_settings_controller, 
																	max_size_gbytes * 1024 );
	}

	/****************************************
	*  setMaxSizeInGBytesMBytesKBytesBytes  *
	****************************************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
	void RPDB_DatabaseCacheSettingsController_setMaxSizeInGBytesMBytesKBytesBytes(	RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																					uint32_t									max_size_gbytes, 
																					uint32_t									additional_max_size_mbytes, 
																					uint32_t									additional_max_size_kbytes, 
																					uint32_t									additional_max_size_in_bytes )	{
		RPDB_DatabaseCacheSettingsController_setMaxSizeInBytes( database_cache_settings_controller,	max_size_gbytes * 1024 * 1024 * 1024
		 																								+	additional_max_size_mbytes * 1024 * 1024
																										+	additional_max_size_kbytes * 1024
																										+	additional_max_size_in_bytes );
	}

	/************************************
	*  setMaxSizeInMBytesKBytesBytes  *
	************************************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
	void RPDB_DatabaseCacheSettingsController_setMaxSizeInMBytesKBytesBytes(	RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																				uint32_t									max_size_mbytes, 
																				uint32_t									additional_max_size_kbytes, 
																				uint32_t									additional_max_size_in_bytes )	{
		RPDB_DatabaseCacheSettingsController_setMaxSizeInBytes( database_cache_settings_controller,	max_size_mbytes * 1024 * 1024
																										+	additional_max_size_kbytes * 1024
																										+	additional_max_size_in_bytes );
	}

	/****************************
	*  setMaxSizeInKBytesBytes  *
	****************************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
	void RPDB_DatabaseCacheSettingsController_setMaxSizeInKBytesBytes(	RPDB_DatabaseCacheSettingsController* database_cache_settings_controller, 
																		uint32_t								max_size_kbytes, 
																		uint32_t								additional_max_size_in_bytes )	{
		RPDB_DatabaseCacheSettingsController_setMaxSizeInBytes(	database_cache_settings_controller,	
																	max_size_kbytes * 1024
																	+	additional_max_size_in_bytes );
	}

/**************************
*  numberCacheRegions  *
**************************/

int RPDB_DatabaseCacheSettingsController_numberCacheRegions( RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{

	if ( RPDB_DatabaseCacheSettingsController_internal_isInEnvironment( database_cache_settings_controller ) )	{
		RPDB_ErrorController_throwError(	RPDB_ErrorController_new( NULL ), 
											RP_ERROR_NO_SETTING_DB_CACHE_WHILE_IN_ENVIRONMENT, 
										 "RPDB_DatabaseCacheSettingsController_numberContiguousRegions", 
										 "This setting is only for when using a database outside an environment." );
		return 0;
	}

	return database_cache_settings_controller->number_cache_regions;
}

/****************************
*  setNumberCacheRegions  *
*****************************/

void RPDB_DatabaseCacheSettingsController_setNumberCacheRegions(	RPDB_DatabaseCacheSettingsController* database_cache_settings_controller, 
																	int number_cache_regions )	{		
	if ( RPDB_DatabaseCacheSettingsController_internal_isInEnvironment( database_cache_settings_controller ) )	{
		RPDB_ErrorController_throwError(	RPDB_ErrorController_new( NULL ), 
											RP_ERROR_NO_SETTING_DB_CACHE_WHILE_IN_ENVIRONMENT, 
										 "RPDB_DatabaseCacheSettingsController_setNumberCacheRegions", 
										 "This setting is only for when using a database outside an environment." );
	}

	database_cache_settings_controller->number_cache_regions = number_cache_regions;
}

/*********************
*  cacheUpdate  *
*********************/

	//	To be included in a later version:

/*
	//	Check cache statistics and attempt to estimate best size database. 
	//	http://www.oracle.com/technology/documentation/berkeley-db/db/ref/am_conf/cachesize.html
	RPDB_CacheUpdate* RPDB_DatabaseCacheSettingsController_cacheUpdate( RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{

		//	When using the Btree access method, you must have a cache big enough for the minimum working set for a single access.
		//		This will include a root page, one or more internal pages (depending on the depth of your tree), and a leaf page. 
		//	If your keys are of moderate size (a few tens of bytes) and your pages are on the order of 4KB to 8KB, most Btree applications will be only three levels.
		//	The rule-of-thumb is that cache is good, and more cache is better. 
		//	 Generally, applications benefit from increasing the cache size up to a point, at which the performance will stop improving as the cache size increases. 
		//		When this point is reached, one of two things have happened: 
		//			either the cache is large enough that the application is almost never having to retrieve information from disk, 
		//				or, 
		//			your application is doing truly random accesses, 
		//			and therefore increasing size of the cache doesn't significantly increase the odds of finding the next requested information in the cache.
		//	That said, it is important not to increase your cache size beyond the capabilities of your system, as that will result in reduced performance.
		//	Under many operating systems, tying down enough virtual memory will cause your memory and potentially your program to be swapped. 
		//		This is especially likely on systems without unified OS buffer caches and virtual memory spaces, 
		//		as the buffer cache was allocated at boot time and so cannot be adjusted based on application requests for large amounts of virtual memory.
		//	For example, even if accesses are truly random within a Btree, your access pattern will favor internal pages to leaf pages, 
		//		so your cache should be large enough to hold all internal pages. In the steady state, this requires at most one I/O per operation to retrieve the appropriate leaf page.
		//	You can use the db_stat utility to monitor the effectiveness of your cache.
	}
*/

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/**************************
*  priorityController  *
**************************/

RPDB_DatabaseCachePrioritySettingsController* RPDB_DatabaseCacheSettingsController_priorityController( RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{
	
	if ( database_cache_settings_controller->priority_settings_controller == NULL )	{
		
		database_cache_settings_controller->priority_settings_controller = RPDB_DatabaseCachePrioritySettingsController_new( database_cache_settings_controller );
	}
	return database_cache_settings_controller->priority_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************************
*  isInEnvironment  *
*************************/

BOOL RPDB_DatabaseCacheSettingsController_internal_isInEnvironment( RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{

	if (	//	Make sure if we have a parent database settings controller that we don't have a parent settings controller and that we don't have
			//	an environment as parent to the db or database_cursor
			//	If we did, then we would have an environmental settings controller as the parent and not a db or database_cursor as the parent
		(	database_cache_settings_controller->parent_database_settings_controller->parent_database == NULL
		&&	database_cache_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment != NULL ) )	{
		
		return RP_IN_ENVIRONMENT;
	}
	
	return FALSE;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseCacheSettingsController* RPDB_DatabaseCacheSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{

	RPDB_DatabaseCacheSettingsController* database_cache_settings_controller_copy	=	RPDB_DatabaseCacheSettingsController_new( database_cache_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_cache_settings_controller_copy->max_size_in_bytes	=	database_cache_settings_controller->max_size_in_bytes;
	database_cache_settings_controller_copy->number_cache_regions	=	database_cache_settings_controller->number_cache_regions;

	return database_cache_settings_controller_copy;
}


/****************************
*  initDefaultSettings  *
****************************/

void RPDB_DatabaseCacheSettingsController_internal_initDefaultSettings( RPDB_DatabaseCacheSettingsController* database_cache_settings_controller )	{
	//	By default we'll assume 1 memory region
	database_cache_settings_controller->number_cache_regions = 1;
}	
