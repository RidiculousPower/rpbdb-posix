/*
 *		RPbdb::RuntimeStorageController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RuntimeStorageController.h"
#include "RuntimeStorageController_internal.h"

#include "Environment.h"
#include "Environment_internal.h"

#include "Database.h"
#include "Database_internal.h"
#include "DatabaseController.h"
#include "DatabaseController_internal.h"
#include "DatabaseCursorController_internal.h"
#include "DatabaseCursor.h"

#include "ErrorController.h"

#include "Record.h"

#include "SettingsController.h"
#include "DatabaseSettingsController.h"
#include "DatabaseSettingsController_internal.h"
#include "DatabaseRecordReadWriteSettingsController.h"
#include "DatabaseTypeSettingsController.h"
#include "DatabaseTypeBtreeSettingsController.h"
#include "DatabaseCursorReadWriteSettingsController.h"
#include "DatabaseCursorSettingsController.h"
#include "DatabaseCursorSettingsController_internal.h"
#include "DebugSettingsController.h"
#include "FileSettingsController.h"
#include "LockSettingsController.h"
#include "LogSettingsController.h"
#include "MemoryPoolSettingsController.h"
#include "MemoryPoolFileSettingsController.h"
#include "ThreadSettingsController.h"
#include "TransactionSettingsController.h"
#include "EnvironmentCacheSettingsController.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/

//	A given process (whether single- or multi- threaded) has one RuntimeStorageController
//	It is actually the singleton RuntimeStorageController that defines our "process environment",
//	and multiple RPbdb_Environments can co-exist under the umbrella of this singleton
RPbdb_RuntimeStorageController* RPbdb_RuntimeStorageController_sharedInstance()	{

	//	We only ever want one runtime_storage_controller
	static RPbdb_RuntimeStorageController	runtime_storage_controller;
	
	//	Initialize our runtime environment if it hasn't been done already	
	if ( runtime_storage_controller.runtime_environment == NULL )	{
		
		runtime_storage_controller.default_environment	=	NULL;
		
		//	Initialize runtime environment
		RPbdb_RuntimeStorageController_internal_initRuntimeEnvironment( & runtime_storage_controller );
	}
	
	return & runtime_storage_controller;	
}

/*********
*  free  *
*********/
void RPbdb_RuntimeStorageController_free( RPbdb_RuntimeStorageController** runtime_storage_controller )	{

	//	free runtime storage environments reference database
	if ( ( *runtime_storage_controller )->environment_reference_database != NULL )	{
		RPbdb_Database_free( & ( ( *runtime_storage_controller )->environment_reference_database ) );
	}
	//	free runtime storage database reference database
	if ( ( *runtime_storage_controller )->database_reference_database != NULL )	{
		RPbdb_Database_free( & ( ( *runtime_storage_controller )->database_reference_database ) );
	}
	//	free runtime storages primary database (stores other runtime storages)
	if ( ( *runtime_storage_controller )->runtime_storages_database != NULL )	{
		RPbdb_Database_free( & ( ( *runtime_storage_controller )->runtime_storages_database ) );
	}
	//	free runtime storage database cursor
	if ( ( *runtime_storage_controller )->database_cursor != NULL )	{
		RPbdb_DatabaseCursor_free( & ( ( *runtime_storage_controller )->database_cursor ) );
	}
	//	free runtime storage environment
	if ( ( *runtime_storage_controller )->runtime_environment != NULL )	{
		RPbdb_Environment_free( & ( ( *runtime_storage_controller )->runtime_environment ) );
	}
		
	free( *runtime_storage_controller );
	*runtime_storage_controller	=	NULL;
}

/***********************
*  settingsController  *
***********************/
RPbdb_RuntimeStorageSettingsController* RPbdb_RuntimeStorageController_settingsController(	RPbdb_RuntimeStorageController* runtime_storage_controller )	{
	return runtime_storage_controller->settings_controller;
}

/***********************
*  currentWorkingEnvironment  *
***********************/

RPbdb_Environment* RPbdb_RuntimeStorageController_currentWorkingEnvironment(	RPbdb_RuntimeStorageController*		runtime_storage_controller )	{
	
	return runtime_storage_controller->default_environment;
}

/******************************
*  requireDefaultEnvironment  *
******************************/

RPbdb_Environment* RPbdb_RuntimeStorageController_requireDefaultEnvironment(	RPbdb_RuntimeStorageController*		runtime_storage_controller )	{
	
	if ( runtime_storage_controller->default_environment )	{
		return runtime_storage_controller->default_environment;
	}
	else {
		
		RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( NULL ),
																			RPBDB_ERROR_DEFAULT_ENVIRONMENT_NOT_FOUND, 
																			"RuntimeStorageController_requireDefaultEnvironment",
																			RPBDB_ERROR_MESSAGE_TRANSACTION_OPEN );
		
	}
	return NULL;
}

/**************************
*  setCurrentWorkingEnvironment  *
**************************/

void RPbdb_RuntimeStorageController_setCurrentWorkingEnvironment(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																													RPbdb_Environment*					environment )	{
	
	runtime_storage_controller->default_environment	=	environment;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************************************************************************************************************************************************************
																		Initialization
*******************************************************************************************************************************************************************************************/

/***************************
*  initRuntimeEnvironment  *
***************************/

RPbdb_RuntimeStorageController* RPbdb_RuntimeStorageController_internal_initRuntimeEnvironment( RPbdb_RuntimeStorageController* runtime_storage_controller )	{
	
	/*----------------------*
	*  Runtime Environment  *
	*----------------------*/
	
	//	Initialize our runtime environment (RPBDB_IN_MEMORY == NULL for in-memory)
	runtime_storage_controller->runtime_environment		=	RPbdb_Environment_new(	RPBDB_IN_MEMORY );
	
	//	Init settings for our runtime environment (create the DB_ENV instance)
	RPbdb_Environment_internal_initWrappedEnvironment(	runtime_storage_controller->runtime_environment,
																										TRUE );

	/*----------------------*
	*  Settings Controller  *
	*----------------------*/
	
	RPbdb_SettingsController*	settings_controller		=	RPbdb_Environment_settingsController( runtime_storage_controller->runtime_environment );
	
	/*----------------------*
	*  Create if Necessary  *
	*----------------------*/
	
	RPbdb_FileSettingsController*	file_settings_controller	=	RPbdb_SettingsController_fileSettingsController( settings_controller );
	
	//	Set to create environment if necessary
	RPbdb_FileSettingsController_turnCreateIfNecessaryOn( file_settings_controller );
															
	/*---------------*
	*  Transactions  *
	*---------------*/
	
	//	Turn off transaction related systems for runtime storage
	RPbdb_TransactionSettingsController_turnOff( RPbdb_SettingsController_transactionSettingsController( settings_controller ) );
	RPbdb_LogSettingsController_turnOff( RPbdb_SettingsController_logSettingsController( settings_controller ) );
	RPbdb_LockSettingsController_turnOff( RPbdb_SettingsController_lockSettingsController( settings_controller ) );	
	RPbdb_DebugSettingsController*	debug_settings_controller	=	RPbdb_SettingsController_debugSettingsController( settings_controller );
	RPbdb_DebugSettingsController_turnRegisterForRecoveryOff( debug_settings_controller );
	RPbdb_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOff( debug_settings_controller );
	RPbdb_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOff( debug_settings_controller );

	/*------------------*
	*  Store in Memory  *
	*------------------*/
	
	//	Initialize runtime environment for memory-only (prohibit writing to disk)
	RPbdb_Environment_initForStorageInMemory( runtime_storage_controller->runtime_environment );
	//	And make sure we actually have a memory pool
	RPbdb_MemoryPoolSettingsController_turnOn( RPbdb_SettingsController_memoryPoolSettingsController( settings_controller ) );

	/*-------------*
	*  Cache Size  *
	*-------------*/

	RPbdb_EnvironmentCacheSettingsController*	environment_cache_settings_controller	=	RPbdb_SettingsController_cacheSettingsController( settings_controller );

	RPbdb_EnvironmentCacheSettingsController_setSizeInMBytes(	environment_cache_settings_controller,
																														RPBDB_RUNTIME_STORAGE_CACHE_SIZE_IN_MB	);
	
	/*------------*
	*  Page Size  *
	*------------*/

	RPbdb_MemoryPoolSettingsController*			memory_pool_settings_controller	=	RPbdb_SettingsController_memoryPoolSettingsController( settings_controller );
	RPbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller	=	RPbdb_MemoryPoolSettingsController_fileSettingsController( memory_pool_settings_controller );

	RPbdb_MemoryPoolFileSettingsController_setPageSizeInKBytes(	memory_pool_file_settings_controller,
																															RPBDB_RUNTIME_STORAGE_PAGE_SIZE_IN_K );
	
	/*-------------------*
	*  Open Environment  *
	*-------------------*/
	
	//	Open environment
	RPbdb_Environment_internal_openWithoutRuntimeStorage( runtime_storage_controller->runtime_environment );

	/*------------------------*
	*  Runtime Database Type  *
	*------------------------*/
	
	RPbdb_DatabaseSettingsController*			database_settings_controller			=	RPbdb_SettingsController_databaseSettingsController( settings_controller );
	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController(	database_settings_controller );
	//	Unless otherwise specified, all of our runtime storage will be btree - set the environmental default
	RPbdb_DatabaseTypeSettingsController_setTypeToBTree(	database_type_settings_controller );
	
	/*----------------------*
	*  Database Controller  *
	*----------------------*/
	
	//	Initialize database controller so that we don't create another set of runtime databases inside our runtime environment
	runtime_storage_controller->runtime_environment->database_controller	=	RPbdb_DatabaseController_internal_newWithoutRuntimeStorage( runtime_storage_controller->runtime_environment );
	
	/*--------------------*
	*  Runtime Databases  *
	*--------------------*/
	
	//	Databases for referencing runtime information
	RPbdb_RuntimeStorageController_internal_initRuntimeStoragesDatabases( runtime_storage_controller );
	
	RPbdb_RuntimeStorageController_internal_initEnvironmentAndDatabaseReferenceDatabases( runtime_storage_controller );
	
	/*---------------------*
	*  Runtime Controller  *
	*---------------------*/
	
	return runtime_storage_controller;
}

/************************
*  initPrimaryDatabase  *
************************/

void RPbdb_RuntimeStorageController_internal_initRuntimeStoragesDatabases(	RPbdb_RuntimeStorageController*		runtime_storage_controller )	{

	/*----------------------------*
	*  Primary Storages Database  *
	*----------------------------*/
	
	//	Initialize our runtime storages database
	RPbdb_DatabaseController*	database_controller	=	RPbdb_Environment_databaseController( runtime_storage_controller->runtime_environment );
	runtime_storage_controller->runtime_storages_database			=	RPbdb_Database_new(	database_controller,
																																									"runtime_storages" );
	
}

/************************
*  initPrimaryDatabase  *
************************/

void RPbdb_RuntimeStorageController_internal_initEnvironmentAndDatabaseReferenceDatabases(	RPbdb_RuntimeStorageController*		runtime_storage_controller )	{
	
	RPbdb_DatabaseController*	database_controller	=	RPbdb_Environment_databaseController(	runtime_storage_controller->runtime_environment );
	
	//	database store references to RPbdb_Environment* by DB_ENV*
	runtime_storage_controller->environment_reference_database			=	RPbdb_Database_new(	database_controller,
																																												"runtime_storage__environments" );
	
	//	database store references to RPbdb_Database* by DB*
	runtime_storage_controller->database_reference_database				=	RPbdb_Database_new(	database_controller,
																																											"runtime_storage_database_reference_database" );
	
	RPbdb_Database_internal_openWithoutRuntimeStorage( runtime_storage_controller->environment_reference_database );	
	RPbdb_Database_internal_openWithoutRuntimeStorage( runtime_storage_controller->database_reference_database );	
}

/*******************************************************************************************************************************************************************************************
																Environment and Database Callback Hooks
*******************************************************************************************************************************************************************************************/

/**************************************
*  storeEnvironmentForBDBEnvironment  *
**************************************/

//	We are storing primarily by BDB key because every callback has to look up the BDB key -
//	so it should be more efficient to only look up once. Asking for environment should be
//	less frequent, so less expensive to ask through a secondary (and less likely to multiply).
void RPbdb_RuntimeStorageController_internal_storeEnvironmentForBDBEnvironment(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																																								RPbdb_Environment*									environment	)	{

	//	declare and zero keys
	DBT	bdb_key;
	DBT	bdb_data;
	memset( & bdb_key, 0, sizeof( DBT ) );
	memset( & bdb_data, 0, sizeof( DBT ) );

	//	get wrapped bdb environment address and store as key
	uintptr_t	bdb_environment_address	=	(uintptr_t) environment->wrapped_bdb_environment;
	bdb_key.data		=	& bdb_environment_address;
	bdb_key.size		=	sizeof( uintptr_t );
	bdb_key.flags		=	RPBDB_NO_FLAGS;
	
	//	get rpbdb environment address and store as data
	uintptr_t environment_address	=	(uintptr_t) environment;
	bdb_data.data		=	& environment_address;
	bdb_data.size		=	sizeof( uintptr_t );
	bdb_data.flags	=	RPBDB_NO_FLAGS;

	//	store in runtime storage environments reference database
	RPbdb_Database*	environment_reference_database	=	runtime_storage_controller->environment_reference_database;
	int	connection_error = RP_NO_ERROR;
	if ( ( connection_error = environment_reference_database->wrapped_bdb_database->put(	environment_reference_database->wrapped_bdb_database,
																																												NULL,
																																												& bdb_key,
																																												& bdb_data,
																																												RPBDB_NO_FLAGS ) ) )	{
		
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"RuntimeStorageController_internal_storeEnvironmentForBDBEnvironment" );
	}

	RPbdb_RuntimeStorageController_setCurrentWorkingEnvironment(	runtime_storage_controller,
																															environment	);
}

/****************************
*  removeStoredEnvironment  *
****************************/

void RPbdb_RuntimeStorageController_internal_removeStoredEnvironment(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																																			RPbdb_Environment*									environment	)	{

	//	create and zero key
	DBT	bdb_key;
	memset( & bdb_key, 0, sizeof( DBT ) );
	
	uintptr_t	bdb_environment_address	=	(uintptr_t) environment->wrapped_bdb_environment;
	bdb_key.data	=	(void*) & bdb_environment_address;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RPBDB_NO_FLAGS;
	
	RPbdb_Database*	environments_database	=	runtime_storage_controller->environment_reference_database;
	int	connection_error = RP_NO_ERROR;	
	if ( ( connection_error = environments_database->wrapped_bdb_database->del(	environments_database->wrapped_bdb_database,
																																							NULL,
																																							& bdb_key,
																																							RPBDB_NO_FLAGS ) ) )	{
		
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"RuntimeStorageController_internal_removeStoredEnvironment" );
	}
}

/********************************
*  storeDatabaseForBDBDatabase  *
********************************/

void RPbdb_RuntimeStorageController_internal_storeDatabaseForBDBDatabase(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																																					RPbdb_Database*										database	)	{
	
	//	create and zero key and data
	DBT	bdb_key;
	DBT	bdb_data;
	memset( & bdb_key, 0, sizeof( DBT ) );
	memset( & bdb_data, 0, sizeof( DBT ) );
	
	//	get wrapped bdb database address as key
	uintptr_t	bdb_database_address	=	(uintptr_t) database->wrapped_bdb_database;
	bdb_key.data	=	& bdb_database_address;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RPBDB_NO_FLAGS;
	
	//	get rpbdb database address for data
	uintptr_t database_address	=	(uintptr_t) database;	
	bdb_data.data	=	& database_address;
	bdb_data.size	=	sizeof( uintptr_t );
	bdb_data.flags	=	RPBDB_NO_FLAGS;

	RPbdb_Database*	database_reference_database	=	runtime_storage_controller->database_reference_database;
	int connection_error = RP_NO_ERROR;
	if ( ( connection_error = database_reference_database->wrapped_bdb_database->put(	database_reference_database->wrapped_bdb_database,
																																										NULL,
																																										& bdb_key,
																																										& bdb_data,
																																										RPBDB_NO_FLAGS ) ) )	{
		
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"RuntimeStorageController_internal_storeDatabaseForBDBDatabase" );
	}
}

/***************************************
*  removeDatabaseStoredForBDBDatabase  *
***************************************/

void RPbdb_RuntimeStorageController_internal_removeDatabaseStoredForBDBDatabase(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																																								RPbdb_Database*						database	)	{
	
	//	create and zero key
	DBT	bdb_key;
	memset( & bdb_key, 0, sizeof( DBT ) );
	
	//	get bdb environment address and set as deletion key
	uintptr_t	bdb_database_address	=	(uintptr_t) database->wrapped_bdb_database;
	bdb_key.data	=	& bdb_database_address;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RPBDB_NO_FLAGS;
	
	RPbdb_Database*	database_reference_database	=	runtime_storage_controller->database_reference_database;
	int	connection_error = RP_NO_ERROR;	
	if ( RPbdb_Database_rawKeyExists(	database_reference_database,
										& bdb_database_address,
										sizeof( uintptr_t ) ) )	{
		if ( ( connection_error = database_reference_database->wrapped_bdb_database->del(	database_reference_database->wrapped_bdb_database,
																																											NULL,
																																											& bdb_key,
																																											RPBDB_NO_FLAGS ) ) )	{
			
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( runtime_storage_controller->runtime_environment ),
																										connection_error, 
																										"RuntimeStorageController_internal_removeDatabaseStoredForBDBDatabase" );
		}
	}
}

/*********************************
*  environmentForBDBEnvironment  *
*********************************/

RPbdb_Environment* RPbdb_RuntimeStorageController_internal_environmentForBDBEnvironment(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																																												DB_ENV*								bdb_environment	)	{
	
	//	runtime_storage_controller->environment_reference_database contains bdb_environment_address => environment_address
	//	since any given runtime storage is within the same memory space, every environment will have a unique memory address
	
	
	//	when runtime storage is created, this database needs to be initialized
	//	when an environment is created, this database needs an entry for the environment
	//	when this function is called, it returns the rpbdb environment for bdb address
	
	RPbdb_Database*	database	=	runtime_storage_controller->environment_reference_database;
	
	DBT	bdb_key;
	DBT	bdb_data;
	
	bdb_key.data	=	(void*) bdb_environment;
	bdb_key.size	=	sizeof( uintptr_t );
	
	int	connection_error	=	0;
	
	if ( ( connection_error = database->wrapped_bdb_database->get(	database->wrapped_bdb_database,
																																	NULL,
																																	& bdb_key,
																																	& bdb_data,
																																	RPBDB_NO_FLAGS ) ) )	{
	
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"RuntimeStorageController_internal_environmentForBDBEnvironment" );
		return NULL;		
	}
	
	RPbdb_Environment*	return_environment	=	(RPbdb_Environment*) ( *(uintptr_t*) bdb_data.data );
	
	return return_environment;
}	

/***************************
*  databaseForBDBDatabase  *
***************************/

RPbdb_Database* RPbdb_RuntimeStorageController_internal_databaseForBDBDatabase(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																																							DB*									bdb_database	)	{
	
	//	runtime_storage_controller->database_reference_database contains bdb_database_address => database_address
	//	since any given runtime storage is within the same memory space, every database will have a unique memory address
	
	//	when runtime storage is created, this database needs to be initialized
	//	when a database is created, this database needs an entry for the database
	//	when this function is called, it returns the rpbdb database for bdb address
	
	//	create and zero key and data
	DBT					bdb_key;
	DBT					bdb_data;
	memset( & bdb_key, 0, sizeof( DBT ) );
	memset( & bdb_data, 0, sizeof( DBT ) );
	
	//	get address of passed bdb database - matches key and wrapped bdb database
	uintptr_t		address_of_bdb_database	=	(uintptr_t) bdb_database;
	bdb_key.data	=	& address_of_bdb_database;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RPBDB_NO_FLAGS;
	
	RPbdb_Database*		database_reference_database	=	runtime_storage_controller->database_reference_database;
	int	connection_error	=	RP_NO_ERROR;				
	if ( ( connection_error = database_reference_database->wrapped_bdb_database->get(	database_reference_database->wrapped_bdb_database,
																					NULL,
																					& bdb_key,
																					& bdb_data,
																					RPBDB_NO_FLAGS ) ) )	{
		
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"RuntimeStorageController_internal_databaseForBDBDatabase" );
		return NULL;
	}
	
	return (RPbdb_Database*) ( *(uintptr_t*) bdb_data.data );
}	
