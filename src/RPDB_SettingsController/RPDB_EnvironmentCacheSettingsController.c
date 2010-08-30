/*
 *		RPDB::RPDB_SettingsController::RPDB_EnvironmentCacheSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_EnvironmentCacheSettingsController.h"

#include "RPDB_Environment.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/

RPDB_EnvironmentCacheSettingsController* RPDB_EnvironmentCacheSettingsController_new( RPDB_SettingsController* settings_controller )	{

	RPDB_EnvironmentCacheSettingsController*		cache_settings_controller = calloc( 1, sizeof( RPDB_EnvironmentCacheSettingsController ) );

	cache_settings_controller->parent_settings_controller = settings_controller;

	//	Not much that we have to do here - controllers will be lazy-loaded
	return cache_settings_controller;
}

/*********
*  free  *
*********/
void RPDB_EnvironmentCacheSettingsController_free(	RPDB_EnvironmentCacheSettingsController** environment_cache_settings_controller )	{

	free( *environment_cache_settings_controller );
	*environment_cache_settings_controller	=	NULL;
}

/**********************
*  parentEnvironment  *
**********************/
RPDB_Environment* RPDB_EnvironmentCacheSettingsController_parentEnvironment(	RPDB_EnvironmentCacheSettingsController* environment_cache_settings_controller )	{
	return environment_cache_settings_controller->parent_settings_controller->parent_environment;
}

/**************
*  buffering  *
**************/

//	DB_DIRECT_DB            http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
BOOL RPDB_EnvironmentCacheSettingsController_buffering( RPDB_EnvironmentCacheSettingsController* cache_settings_controller )	{
	if ( cache_settings_controller->buffering == TRUE )	{
		return DB_DIRECT_DB;
	}
	return FALSE;
}

	/********************
	*  turnBufferingOn  *
	********************/

	void RPDB_EnvironmentCacheSettingsController_turnBufferingOn( RPDB_EnvironmentCacheSettingsController* cache_settings_controller )	{
		cache_settings_controller->buffering = TRUE;
	}

	/*********************
	*  turnBufferingOff  *
	*********************/

	void RPDB_EnvironmentCacheSettingsController_turnBufferingOff( RPDB_EnvironmentCacheSettingsController* cache_settings_controller )	{
		cache_settings_controller->buffering = FALSE;
	}

/****************
*  sizeInBytes  *
****************/

//http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
uint64_t RPDB_EnvironmentCacheSettingsController_sizeInBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller )	{

	RPDB_Environment*			environment = cache_settings_controller->parent_settings_controller->parent_environment;
					
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

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
																										connection_error, 
																										"RPDB_EnvironmentCacheSettingsController_sizeInBytes" );
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
double RPDB_EnvironmentCacheSettingsController_sizeInKBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller )	{

	double	size_kbytes = (double)RPDB_EnvironmentCacheSettingsController_sizeInBytes( cache_settings_controller );
	
	return size_kbytes / (double)1024;
}

/*****************
*  sizeInMBytes  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
double RPDB_EnvironmentCacheSettingsController_sizeInMBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller )	{

	double	size_mbytes = (double)RPDB_EnvironmentCacheSettingsController_sizeInKBytes( cache_settings_controller );
	
	return size_mbytes / (double)1024;
}

/*****************
*  sizeInGBytes  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
double RPDB_EnvironmentCacheSettingsController_sizeInGBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller )	{

	double	size_gbytes = (double)RPDB_EnvironmentCacheSettingsController_sizeInMBytes( cache_settings_controller );
	return size_gbytes / (double)1024;
}


/*******************
*  setSizeInBytes  *
*******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInBytes(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																															uint32_t																	size_in_bytes )	{

	RPDB_Environment*		environment = cache_settings_controller->parent_settings_controller->parent_environment;

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
																																										1 ) ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
																										connection_error, 
																										"RPDB_EnvironmentCacheSettingsController_setSizeInBytes" );		
		}
	}
}

/********************
*  setSizeInKBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInKBytes( RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																															uint32_t																	size_kbytes  )	{
	RPDB_EnvironmentCacheSettingsController_setSizeInBytes(	cache_settings_controller, 
																													size_kbytes * 1024 );
}

/********************
*  setSizeInMBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInMBytes( RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																															uint32_t																	size_mbytes  )	{

	RPDB_EnvironmentCacheSettingsController_setSizeInKBytes(	cache_settings_controller, 
																														size_mbytes * 1024 );
}

/********************
*  setSizeInGBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInGBytes( RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																															uint32_t																	size_gbytes  )	{

	RPDB_EnvironmentCacheSettingsController_setSizeInMBytes(	cache_settings_controller, 
																														size_gbytes * 1024 );
}

/*************************************
*  setSizeInGBytesMBytesKBytesBytes  *
*************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInGBytesMBytesKBytesBytes(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																								uint32_t																	size_gbytes, 
																																								uint32_t																	additional_size_mbytes, 
																																								uint32_t																	additional_size_kbytes, 
																																								uint32_t																	additional_size_in_bytes  )	{

	RPDB_EnvironmentCacheSettingsController_setSizeInBytes( cache_settings_controller,	
																													size_gbytes * 1024 * 1024 * 1024
																													+	additional_size_mbytes * 1024 * 1024
																													+	additional_size_kbytes * 1024
																													+	additional_size_in_bytes );
}

/*******************************
*  setSizeInMBytesKBytesBytes  *
*******************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInMBytesKBytesBytes(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																					uint32_t																	size_mbytes, 
																																					uint32_t																	additional_size_kbytes, 
																																					uint32_t																	additional_size_in_bytes  )	{

	RPDB_EnvironmentCacheSettingsController_setSizeInBytes( cache_settings_controller,	
																													size_mbytes * 1024 * 1024
																													+	additional_size_kbytes * 1024
																													+	additional_size_in_bytes );
}

/*************************
*  setSizeInKBytesBytes  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInKBytesBytes( RPDB_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																	uint32_t																		size_kbytes, 
																																	uint32_t																		additional_size_in_bytes  )	{

	RPDB_EnvironmentCacheSettingsController_setSizeInBytes( cache_settings_controller,	
																													size_kbytes * 1024
																													+	additional_size_in_bytes );
}


/******************************
*  setSizeInBytesWithRegions  *
******************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																				uint32_t																	size_in_bytes,
																																				int																				number_of_regions )	{

	RPDB_Environment*		environment = cache_settings_controller->parent_settings_controller->parent_environment;

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

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
																										connection_error, 
																										"RPDB_EnvironmentCacheSettingsController_setSizeInBytesWithRegions" );		
		}
	}
}

/*******************************
*  setSizeInKBytesWithRegions  *
*******************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInKBytesWithRegions(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																					uint32_t																	size_kbytes,
																																					int																				number_of_regions  )	{
	RPDB_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	cache_settings_controller, 
																																			size_kbytes * 1024,
																																			number_of_regions );
}

/*******************************
*  setSizeInMBytesWithRegions  *
*******************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInMBytesWithRegions( RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																					uint32_t																	size_mbytes,
																																					int																				number_of_regions  )	{

	RPDB_EnvironmentCacheSettingsController_setSizeInKBytesWithRegions(	cache_settings_controller, 
																																			size_mbytes * 1024,
																																			number_of_regions );
}

/*******************************
*  setSizeInGBytesWithRegions  *
*******************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInGBytesWithRegions(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																					uint32_t																	size_gbytes,
																																					int																				number_of_regions  )	{

	RPDB_EnvironmentCacheSettingsController_setSizeInMBytesWithRegions(	cache_settings_controller, 
																																			size_gbytes * 1024,
																																			number_of_regions );
}

/************************************************
*  setSizeInGBytesMBytesKBytesBytesWithRegions  *
************************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInGBytesMBytesKBytesBytesWithRegions(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																													uint32_t																	size_gbytes, 
																																													uint32_t																	additional_size_mbytes, 
																																													uint32_t																	additional_size_kbytes, 
																																													uint32_t																	additional_size_in_bytes,
																																													int																				number_of_regions  )	{

	RPDB_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	cache_settings_controller,	
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
void RPDB_EnvironmentCacheSettingsController_setSizeInMBytesKBytesBytesWithRegions(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																										uint32_t																	size_mbytes, 
																																										uint32_t																	additional_size_kbytes, 
																																										uint32_t																	additional_size_in_bytes,
																																										int																				number_of_regions  )	{

	RPDB_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	cache_settings_controller,	
																																			size_mbytes * 1024 * 1024
																																			+	additional_size_kbytes * 1024
																																			+	additional_size_in_bytes,
																																			number_of_regions );
}

/************************************
*  setSizeInKBytesBytesWithRegions  *
************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cachesize.html
void RPDB_EnvironmentCacheSettingsController_setSizeInKBytesBytesWithRegions( RPDB_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																							uint32_t																		size_kbytes, 
																																							uint32_t																		additional_size_in_bytes,
																																							int																					number_of_regions  )	{

	RPDB_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	cache_settings_controller,	
																																			size_kbytes * 1024
																																			+	additional_size_in_bytes,
																																			number_of_regions );
}

/*******************
*  maxSizeInBytes  *
*******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
uint64_t RPDB_EnvironmentCacheSettingsController_maxSizeInBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller )	{

	RPDB_Environment*			environment = cache_settings_controller->parent_settings_controller->parent_environment;
					
	uint32_t		gigabytes_size					=	0;
	uint32_t		additional_bytes_size		=	0;		


	if (	! cache_settings_controller->max_size_in_bytes
		&&	environment->wrapped_bdb_environment != NULL )	{
		
		int	connection_error	=	RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->get_cache_max(	environment->wrapped_bdb_environment, 
																																										& gigabytes_size, 
																																										& additional_bytes_size ) ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
																										connection_error, 
																										"RPDB_EnvironmentCacheSettingsController_maxSizeInBytes" );
		}
	}
	
	//	Return in bytes
	cache_settings_controller->max_size_in_bytes	=		gigabytes_size 
																									* 1024 /*  megs  */ 
																									* 1024 /*  kbytes  */ 
																									* 1024 /*  bytes  */ 
																									+ additional_bytes_size;

	return cache_settings_controller->max_size_in_bytes;
}

/********************
*  maxSizeInKBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
double RPDB_EnvironmentCacheSettingsController_maxSizeInKBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller )	{

	double	max_size_kbytes = (double)RPDB_EnvironmentCacheSettingsController_maxSizeInBytes( cache_settings_controller );
	
	return max_size_kbytes / (double)1024;
}

/********************
*  maxSizeInMBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
double RPDB_EnvironmentCacheSettingsController_maxSizeInMBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller )	{

	double	max_size_mbytes = (double)RPDB_EnvironmentCacheSettingsController_maxSizeInKBytes( cache_settings_controller );
	
	return max_size_mbytes / (double)1024;
}

/********************
*  maxSizeInGBytes  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
double RPDB_EnvironmentCacheSettingsController_maxSizeInGBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller )	{

	double	max_size_gbytes = (double)RPDB_EnvironmentCacheSettingsController_maxSizeInMBytes( cache_settings_controller );
	return max_size_gbytes / (double)1024;
}

/**********************
*  setMaxSizeInBytes  *
**********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPDB_EnvironmentCacheSettingsController_setMaxSizeInBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller, uint32_t max_size_in_bytes )	{

	RPDB_Environment*		environment = cache_settings_controller->parent_settings_controller->parent_environment;

	uint32_t	additional_bytes_size	=		max_size_in_bytes 
																		%	( /* 1 gbyte in bytes */ 1024 * 1024 * 1024);
	uint32_t	gigabytes_size				=		max_size_in_bytes 
																		-	additional_bytes_size;

	cache_settings_controller->max_size_in_bytes	=	max_size_in_bytes;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		int	connection_error	=	RP_NO_ERROR;
		if ( ( connection_error = environment->wrapped_bdb_environment->set_cache_max(	environment->wrapped_bdb_environment, 
																																										gigabytes_size, 
																																										additional_bytes_size ) ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
																										connection_error, 
																										"RPDB_EnvironmentCacheSettingsController_setMaxSizeInBytes" );		
		}
	}
}

/***********************
*  setMaxSizeInKBytes  *
***********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPDB_EnvironmentCacheSettingsController_setMaxSizeInKBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller, uint32_t max_size_kbytes )	{

	RPDB_EnvironmentCacheSettingsController_setMaxSizeInBytes( cache_settings_controller, max_size_kbytes * 1024 );
}

/***********************
*  setMaxSizeInMBytes  *
***********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPDB_EnvironmentCacheSettingsController_setMaxSizeInMBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller, uint32_t max_size_mbytes )	{

	RPDB_EnvironmentCacheSettingsController_setMaxSizeInKBytes( cache_settings_controller, max_size_mbytes * 1024 );
}

/***********************
*  setMaxSizeInGBytes  *
***********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPDB_EnvironmentCacheSettingsController_setMaxSizeInGBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller, uint32_t max_size_gbytes )	{

	RPDB_EnvironmentCacheSettingsController_setMaxSizeInMBytes( cache_settings_controller, max_size_gbytes * 1024 );
}

/****************************************
*  setMaxSizeInGBytesMBytesKBytesBytes  *
****************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPDB_EnvironmentCacheSettingsController_setMaxSizeInGBytesMBytesKBytesBytes(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller,
																																									uint32_t																	max_size_gbytes,
																																									uint32_t																	additional_max_size_mbytes,
																																									uint32_t																	additional_max_size_kbytes,
																																									uint32_t																	additional_max_size_in_bytes )	{

	RPDB_EnvironmentCacheSettingsController_setMaxSizeInBytes( cache_settings_controller,	max_size_gbytes * 1024 * 1024 * 1024
																																											+	additional_max_size_mbytes * 1024 * 1024
																																											+	additional_max_size_kbytes * 1024
																																											+	additional_max_size_in_bytes );
}

/**********************************
*  setMaxSizeInMBytesKBytesBytes  *
**********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPDB_EnvironmentCacheSettingsController_setMaxSizeInMBytesKBytesBytes(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	max_size_mbytes, 
																																						uint32_t																	additional_max_size_kbytes, 
																																						uint32_t																	additional_max_size_in_bytes )	{

	RPDB_EnvironmentCacheSettingsController_setMaxSizeInBytes( cache_settings_controller,	max_size_mbytes * 1024 * 1024
																																											+	additional_max_size_kbytes * 1024
																																											+	additional_max_size_in_bytes );
}

/****************************
*  setMaxSizeInKBytesBytes  *
****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_cache_max.html
void RPDB_EnvironmentCacheSettingsController_setMaxSizeInKBytesBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller, 
																	  uint32_t		max_size_kbytes, 
																	  uint32_t		additional_max_size_in_bytes )	{

	RPDB_EnvironmentCacheSettingsController_setMaxSizeInBytes( cache_settings_controller,	max_size_kbytes * 1024
																																											+	additional_max_size_in_bytes );
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/****************************************
*  copyOfSettingsControllerForInstance  *
****************************************/

RPDB_EnvironmentCacheSettingsController* RPDB_EnvironmentCacheSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_EnvironmentCacheSettingsController* environment_cache_settings_controller )	{

	RPDB_EnvironmentCacheSettingsController* environment_cache_settings_controller_copy	=	RPDB_EnvironmentCacheSettingsController_new( environment_cache_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	environment_cache_settings_controller_copy->max_size_in_bytes	=	environment_cache_settings_controller->max_size_in_bytes;
	environment_cache_settings_controller_copy->buffering	=	environment_cache_settings_controller->buffering;

	return environment_cache_settings_controller_copy;
}

