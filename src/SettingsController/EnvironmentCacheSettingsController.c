/*
 *		RPbdb::RPbdb_SettingsController::RPbdb_EnvironmentCacheSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "EnvironmentCacheSettingsController.h"

#include "Environment.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/

RPbdb_EnvironmentCacheSettingsController* RPbdb_EnvironmentCacheSettingsController_new( RPbdb_SettingsController* settings_controller )	{

	RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller = calloc( 1, sizeof( RPbdb_EnvironmentCacheSettingsController ) );

	cache_settings_controller->parent_settings_controller = settings_controller;

	//	Not much that we have to do here - controllers will be lazy-loaded
	return cache_settings_controller;
}

/*********
*  free  *
*********/
void RPbdb_EnvironmentCacheSettingsController_free(	RPbdb_EnvironmentCacheSettingsController** environment_cache_settings_controller )	{

	free( *environment_cache_settings_controller );
	*environment_cache_settings_controller	=	NULL;
}

/**********************
*  parentEnvironment  *
**********************/
RPbdb_Environment* RPbdb_EnvironmentCacheSettingsController_parentEnvironment(	RPbdb_EnvironmentCacheSettingsController* environment_cache_settings_controller )	{
	return environment_cache_settings_controller->parent_settings_controller->parent_environment;
}

/**************
*  buffering  *
**************/

//	DB_DIRECT_DB            http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
BOOL RPbdb_EnvironmentCacheSettingsController_buffering( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller )	{
	if ( cache_settings_controller->buffering == TRUE )	{
		return DB_DIRECT_DB;
	}
	return FALSE;
}

	/********************
	*  turnBufferingOn  *
	********************/

	void RPbdb_EnvironmentCacheSettingsController_turnBufferingOn( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller )	{
		cache_settings_controller->buffering = TRUE;
	}

	/*********************
	*  turnBufferingOff  *
	*********************/

	void RPbdb_EnvironmentCacheSettingsController_turnBufferingOff( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller )	{
		cache_settings_controller->buffering = FALSE;
	}

/****************
*  sizeInBytes  *
****************/

//http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
uint64_t RPbdb_EnvironmentCacheSettingsController_sizeInBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller )	{

	RPbdb_Environment*			environment = cache_settings_controller->parent_settings_controller->parent_environment;
					
	uint32_t		gigabytes_size					=	0;
	uint32_t		additional_bytes_size		=	0;
	
	//	FIX - need additional function to retrieve number of regions
	int					number_of_regions				=	0;

	if (	! cache_settings_controller->size_in_bytes
		&&	environment->wrapped_bdb_environment != NULL )	{
		
		int	connection_error	=	RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->get_cachesize(	environment->wrapped_bdb_environment, 
																																										& gigabytes_size, 
																																										& additional_bytes_size,
																																										&	number_of_regions ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
																										connection_error, 
																										"EnvironmentCacheSettingsController_sizeInBytes" );
		}
	}
	
	//	Return in bytes
	cache_settings_controller->size_in_bytes	=		gigabytes_size 
																							* 1024 /*  megs  */ 
																							* 1024 /*  kbytes  */ 
																							* 1024 /*  bytes  */ 
																							+ additional_bytes_size;

	return cache_settings_controller->size_in_bytes;
}

/*****************
*  sizeInKBytes  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
double RPbdb_EnvironmentCacheSettingsController_sizeInKBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller )	{

	double	size_kbytes = (double)RPbdb_EnvironmentCacheSettingsController_sizeInBytes( cache_settings_controller );
	
	return size_kbytes / (double)1024;
}

/*****************
*  sizeInMBytes  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
double RPbdb_EnvironmentCacheSettingsController_sizeInMBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller )	{

	double	size_mbytes = (double)RPbdb_EnvironmentCacheSettingsController_sizeInKBytes( cache_settings_controller );
	
	return size_mbytes / (double)1024;
}

/*****************
*  sizeInGBytes  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
double RPbdb_EnvironmentCacheSettingsController_sizeInGBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller )	{

	double	size_gbytes = (double)RPbdb_EnvironmentCacheSettingsController_sizeInMBytes( cache_settings_controller );
	return size_gbytes / (double)1024;
}


/*******************
*  setSizeInBytes  *
*******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInBytes(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																															uint64_t																	size_in_bytes )	{

	RPbdb_Environment*		environment = cache_settings_controller->parent_settings_controller->parent_environment;

	uint32_t	bytes_in_gigabyte	=	1024 * 1024 * 1024;

	uint32_t	additional_bytes_size	=		size_in_bytes %	bytes_in_gigabyte;
	uint32_t	gigabytes_size				=		( size_in_bytes -	additional_bytes_size ) % bytes_in_gigabyte;

	cache_settings_controller->size_in_bytes	=	size_in_bytes;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		int	connection_error	=	RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->set_cachesize(	environment->wrapped_bdb_environment, 
																																										gigabytes_size, 
																																										additional_bytes_size,
																																										1 ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
																										connection_error, 
																										"EnvironmentCacheSettingsController_setSizeInBytes" );		
		}
	}
}

/********************
*  setSizeInKBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInKBytes( RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																															uint32_t																	size_kbytes  )	{
	
	uint64_t	size_bytes	=	(uint64_t) size_kbytes * 1024;
	RPbdb_EnvironmentCacheSettingsController_setSizeInBytes(	cache_settings_controller, 
																													size_bytes );
}

/********************
*  setSizeInMBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInMBytes( RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																															uint32_t																	size_mbytes  )	{

	RPbdb_EnvironmentCacheSettingsController_setSizeInKBytes(	cache_settings_controller, 
																														size_mbytes * 1024 );
}

/********************
*  setSizeInGBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInGBytes( RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																															uint32_t																	size_gbytes  )	{

	RPbdb_EnvironmentCacheSettingsController_setSizeInMBytes(	cache_settings_controller, 
																														size_gbytes * 1024 );
}

/*************************************
*  setSizeInGBytesMBytesKBytesBytes  *
*************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInGBytesMBytesKBytesBytes(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																								uint32_t																	size_gbytes, 
																																								uint32_t																	additional_size_mbytes, 
																																								uint32_t																	additional_size_kbytes, 
																																								uint32_t																	additional_size_in_bytes  )	{

	RPbdb_EnvironmentCacheSettingsController_setSizeInBytes( cache_settings_controller,	
																													size_gbytes * 1024 * 1024 * 1024
																													+	additional_size_mbytes * 1024 * 1024
																													+	additional_size_kbytes * 1024
																													+	additional_size_in_bytes );
}

/*******************************
*  setSizeInMBytesKBytesBytes  *
*******************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInMBytesKBytesBytes(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																					uint32_t																	size_mbytes, 
																																					uint32_t																	additional_size_kbytes, 
																																					uint32_t																	additional_size_in_bytes  )	{

	RPbdb_EnvironmentCacheSettingsController_setSizeInBytes( cache_settings_controller,	
																													size_mbytes * 1024 * 1024
																													+	additional_size_kbytes * 1024
																													+	additional_size_in_bytes );
}

/*************************
*  setSizeInKBytesBytes  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInKBytesBytes( RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																	uint32_t																		size_kbytes, 
																																	uint32_t																		additional_size_in_bytes  )	{

	RPbdb_EnvironmentCacheSettingsController_setSizeInBytes( cache_settings_controller,	
																													size_kbytes * 1024
																													+	additional_size_in_bytes );
}


/******************************
*  setSizeInBytesWithRegions  *
******************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																				uint64_t																	size_in_bytes,
																																				int																				number_of_regions )	{

	RPbdb_Environment*		environment = cache_settings_controller->parent_settings_controller->parent_environment;

	uint32_t	additional_bytes_size	=		size_in_bytes 
																		%	( /* 1 gbyte in bytes */ 1024 * 1024 * 1024);
	uint32_t	gigabytes_size				=		size_in_bytes 
																		-	additional_bytes_size;

	cache_settings_controller->size_in_bytes	=	size_in_bytes;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		int	connection_error	=	RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->set_cachesize(	environment->wrapped_bdb_environment, 
																																										gigabytes_size, 
																																										additional_bytes_size,
																																										number_of_regions ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
																										connection_error, 
																										"EnvironmentCacheSettingsController_setSizeInBytesWithRegions" );		
		}
	}
}

/*******************************
*  setSizeInKBytesWithRegions  *
*******************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInKBytesWithRegions(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																					uint32_t																	size_kbytes,
																																					int																				number_of_regions  )	{
	RPbdb_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	cache_settings_controller, 
																																			size_kbytes * 1024,
																																			number_of_regions );
}

/*******************************
*  setSizeInMBytesWithRegions  *
*******************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInMBytesWithRegions( RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																					uint32_t																	size_mbytes,
																																					int																				number_of_regions  )	{

	RPbdb_EnvironmentCacheSettingsController_setSizeInKBytesWithRegions(	cache_settings_controller, 
																																			size_mbytes * 1024,
																																			number_of_regions );
}

/*******************************
*  setSizeInGBytesWithRegions  *
*******************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInGBytesWithRegions(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																					uint32_t																	size_gbytes,
																																					int																				number_of_regions  )	{

	RPbdb_EnvironmentCacheSettingsController_setSizeInMBytesWithRegions(	cache_settings_controller, 
																																			size_gbytes * 1024,
																																			number_of_regions );
}

/************************************************
*  setSizeInGBytesMBytesKBytesBytesWithRegions  *
************************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInGBytesMBytesKBytesBytesWithRegions(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																													uint32_t																	size_gbytes, 
																																													uint32_t																	additional_size_mbytes, 
																																													uint32_t																	additional_size_kbytes, 
																																													uint32_t																	additional_size_in_bytes,
																																													int																				number_of_regions  )	{

	RPbdb_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	cache_settings_controller,	
																																			size_gbytes * 1024 * 1024 * 1024
																																			+	additional_size_mbytes * 1024 * 1024
																																			+	additional_size_kbytes * 1024
																																			+	additional_size_in_bytes,
																																			number_of_regions );
}

/******************************************
*  setSizeInMBytesKBytesBytesWithRegions  *
******************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInMBytesKBytesBytesWithRegions(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																										uint32_t																	size_mbytes, 
																																										uint32_t																	additional_size_kbytes, 
																																										uint32_t																	additional_size_in_bytes,
																																										int																				number_of_regions  )	{

	RPbdb_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	cache_settings_controller,	
																																			size_mbytes * 1024 * 1024
																																			+	additional_size_kbytes * 1024
																																			+	additional_size_in_bytes,
																																			number_of_regions );
}

/************************************
*  setSizeInKBytesBytesWithRegions  *
************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPbdb_EnvironmentCacheSettingsController_setSizeInKBytesBytesWithRegions( RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																							uint32_t																		size_kbytes, 
																																							uint32_t																		additional_size_in_bytes,
																																							int																					number_of_regions  )	{

	RPbdb_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	cache_settings_controller,	
																																			size_kbytes * 1024
																																			+	additional_size_in_bytes,
																																			number_of_regions );
}

/*******************
*  maxSizeInBytes  *
*******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
uint64_t RPbdb_EnvironmentCacheSettingsController_maxSizeInBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller )	{

	RPbdb_Environment*			environment = cache_settings_controller->parent_settings_controller->parent_environment;
					
	uint32_t		gigabytes_size					=	0;
	uint32_t		additional_bytes_size		=	0;		


	if (	! cache_settings_controller->max_size_in_bytes
		&&	environment->wrapped_bdb_environment != NULL )	{
		
		int	connection_error	=	RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->get_cache_max(	environment->wrapped_bdb_environment, 
																																										& gigabytes_size, 
																																										& additional_bytes_size ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
																										connection_error, 
																										"EnvironmentCacheSettingsController_maxSizeInBytes" );
		}

		//	Return in bytes
		cache_settings_controller->max_size_in_bytes	=		gigabytes_size 
																										* 1024 /*  megs  */ 
																										* 1024 /*  kbytes  */ 
																										* 1024 /*  bytes  */ 
																										+ additional_bytes_size;

	}
	
	return cache_settings_controller->max_size_in_bytes;
}

/********************
*  maxSizeInKBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
double RPbdb_EnvironmentCacheSettingsController_maxSizeInKBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller )	{

	double	max_size_kbytes = (double)RPbdb_EnvironmentCacheSettingsController_maxSizeInBytes( cache_settings_controller );
	
	return max_size_kbytes / (double)1024;
}

/********************
*  maxSizeInMBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
double RPbdb_EnvironmentCacheSettingsController_maxSizeInMBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller )	{

	double	max_size_mbytes = (double)RPbdb_EnvironmentCacheSettingsController_maxSizeInKBytes( cache_settings_controller );
	
	return max_size_mbytes / (double)1024;
}

/********************
*  maxSizeInGBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
double RPbdb_EnvironmentCacheSettingsController_maxSizeInGBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller )	{

	double	max_size_gbytes = (double)RPbdb_EnvironmentCacheSettingsController_maxSizeInMBytes( cache_settings_controller );
	return max_size_gbytes / (double)1024;
}

/**********************
*  setMaxSizeInBytes  *
**********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPbdb_EnvironmentCacheSettingsController_setMaxSizeInBytes(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint64_t																	max_size_in_bytes )	{

	RPbdb_Environment*		environment = cache_settings_controller->parent_settings_controller->parent_environment;

	uint32_t	bytes_in_gigabyte	=	1024 * 1024 * 1024;

	uint64_t	additional_bytes_size	=		max_size_in_bytes % (uint64_t) bytes_in_gigabyte;
	uint64_t	gigabytes_in_bytes		=		max_size_in_bytes -	additional_bytes_size;
	uint64_t	gigabytes_size				=		gigabytes_in_bytes / (uint64_t) bytes_in_gigabyte;

	cache_settings_controller->max_size_in_bytes	=	max_size_in_bytes;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		int	connection_error	=	RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->set_cache_max(	environment->wrapped_bdb_environment, 
																																										(uint32_t) gigabytes_size, 
																																										(uint32_t) additional_bytes_size ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
																										connection_error, 
																										"EnvironmentCacheSettingsController_setMaxSizeInBytes" );		
		}
	}
}

/***********************
*  setMaxSizeInKBytes  *
***********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPbdb_EnvironmentCacheSettingsController_setMaxSizeInKBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller, uint32_t max_size_kbytes )	{

	uint64_t	max_size_bytes	=	(uint64_t) max_size_kbytes * 1024;

	RPbdb_EnvironmentCacheSettingsController_setMaxSizeInBytes(	cache_settings_controller,
																															max_size_bytes );
}

/***********************
*  setMaxSizeInMBytes  *
***********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPbdb_EnvironmentCacheSettingsController_setMaxSizeInMBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller, uint32_t max_size_mbytes )	{

	RPbdb_EnvironmentCacheSettingsController_setMaxSizeInKBytes( cache_settings_controller, max_size_mbytes * 1024 );
}

/***********************
*  setMaxSizeInGBytes  *
***********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPbdb_EnvironmentCacheSettingsController_setMaxSizeInGBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller, uint32_t max_size_gbytes )	{

	RPbdb_EnvironmentCacheSettingsController_setMaxSizeInMBytes( cache_settings_controller, max_size_gbytes * 1024 );
}

/****************************************
*  setMaxSizeInGBytesMBytesKBytesBytes  *
****************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPbdb_EnvironmentCacheSettingsController_setMaxSizeInGBytesMBytesKBytesBytes(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller,
																																									uint32_t																	max_size_gbytes,
																																									uint32_t																	additional_max_size_mbytes,
																																									uint32_t																	additional_max_size_kbytes,
																																									uint32_t																	additional_max_size_in_bytes )	{

	uint64_t	max_size_in_bytes	=	(uint64_t) max_size_gbytes * 1024 * 1024 * 1024
															+	(uint64_t) additional_max_size_mbytes * 1024 * 1024
															+	(uint64_t) additional_max_size_kbytes * 1024
															+	(uint64_t) additional_max_size_in_bytes;

	RPbdb_EnvironmentCacheSettingsController_setMaxSizeInBytes(	cache_settings_controller,	
																															max_size_in_bytes );
}

/**********************************
*  setMaxSizeInMBytesKBytesBytes  *
**********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPbdb_EnvironmentCacheSettingsController_setMaxSizeInMBytesKBytesBytes(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	max_size_mbytes, 
																																						uint32_t																	additional_max_size_kbytes, 
																																						uint32_t																	additional_max_size_in_bytes )	{

	uint64_t	max_size_in_bytes	=	(uint64_t) max_size_mbytes * 1024 * 1024
															+	(uint64_t) additional_max_size_kbytes * 1024
															+	(uint64_t) additional_max_size_in_bytes;

	RPbdb_EnvironmentCacheSettingsController_setMaxSizeInBytes(	cache_settings_controller,
																															max_size_in_bytes );
}

/****************************
*  setMaxSizeInKBytesBytes  *
****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPbdb_EnvironmentCacheSettingsController_setMaxSizeInKBytesBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller, 
																																			uint32_t		max_size_kbytes, 
																																			uint32_t		additional_max_size_in_bytes )	{

	uint64_t	max_size_in_bytes	=	(uint64_t) max_size_kbytes * 1024
															+	(uint64_t) additional_max_size_in_bytes;

	RPbdb_EnvironmentCacheSettingsController_setMaxSizeInBytes(	cache_settings_controller,	
																															max_size_in_bytes );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/****************************************
*  copyOfSettingsControllerForInstance  *
****************************************/

RPbdb_EnvironmentCacheSettingsController* RPbdb_EnvironmentCacheSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_EnvironmentCacheSettingsController* environment_cache_settings_controller )	{

	RPbdb_EnvironmentCacheSettingsController* environment_cache_settings_controller_copy	=	RPbdb_EnvironmentCacheSettingsController_new( environment_cache_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	environment_cache_settings_controller_copy->max_size_in_bytes	=	environment_cache_settings_controller->max_size_in_bytes;
	environment_cache_settings_controller_copy->buffering	=	environment_cache_settings_controller->buffering;

	return environment_cache_settings_controller_copy;
}

