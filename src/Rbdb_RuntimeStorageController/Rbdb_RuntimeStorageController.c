/*
 *		Rbdb::RuntimeStorageController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_RuntimeStorageController.h"
#include "Rbdb_RuntimeStorageController_internal.h"

#include "Rbdb_Environment.h"
#include "Rbdb_Environment_internal.h"

#include "Rbdb_Database.h"
#include "Rbdb_Database_internal.h"
#include "Rbdb_DatabaseController.h"
#include "Rbdb_DatabaseController_internal.h"
#include "Rbdb_DatabaseCursorController_internal.h"
#include "Rbdb_DatabaseCursor.h"

#include "Rbdb_ErrorController.h"

#include "Rbdb_Record.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseSettingsController_internal.h"
#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"
#include "Rbdb_DatabaseTypeSettingsController.h"
#include "Rbdb_DatabaseTypeBtreeSettingsController.h"
#include "Rbdb_DatabaseCursorReadWriteSettingsController.h"
#include "Rbdb_DatabaseCursorSettingsController.h"
#include "Rbdb_DatabaseCursorSettingsController_internal.h"
#include "Rbdb_DebugSettingsController.h"
#include "Rbdb_FileSettingsController.h"
#include "Rbdb_LockSettingsController.h"
#include "Rbdb_LogSettingsController.h"
#include "Rbdb_MemoryPoolSettingsController.h"
#include "Rbdb_MemoryPoolFileSettingsController.h"
#include "Rbdb_ThreadSettingsController.h"
#include "Rbdb_TransactionSettingsController.h"
#include "Rbdb_EnvironmentCacheSettingsController.h"

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
//	and multiple Rbdb_Environments can co-exist under the umbrella of this singleton
Rbdb_RuntimeStorageController* Rbdb_RuntimeStorageController_sharedInstance()	{

	//	We only ever want one runtime_storage_controller
	static Rbdb_RuntimeStorageController	runtime_storage_controller;
	
	//	Initialize our runtime environment if it hasn't been done already	
	if ( runtime_storage_controller.runtime_environment == NULL )	{
		
		runtime_storage_controller.default_environment	=	NULL;
		
		//	Initialize runtime environment
		Rbdb_RuntimeStorageController_internal_initRuntimeEnvironment( & runtime_storage_controller );
	}
	
	return & runtime_storage_controller;	
}

/*********
*  free  *
*********/
void Rbdb_RuntimeStorageController_free( Rbdb_RuntimeStorageController** runtime_storage_controller )	{

	//	free runtime storage environments reference database
	if ( ( *runtime_storage_controller )->environment_reference_database != NULL )	{
		Rbdb_Database_free( & ( ( *runtime_storage_controller )->environment_reference_database ) );
	}
	//	free runtime storage database reference database
	if ( ( *runtime_storage_controller )->database_reference_database != NULL )	{
		Rbdb_Database_free( & ( ( *runtime_storage_controller )->database_reference_database ) );
	}
	//	free runtime storages primary database (stores other runtime storages)
	if ( ( *runtime_storage_controller )->runtime_storages_database != NULL )	{
		Rbdb_Database_free( & ( ( *runtime_storage_controller )->runtime_storages_database ) );
	}
	//	free runtime storage database cursor
	if ( ( *runtime_storage_controller )->database_cursor != NULL )	{
		Rbdb_DatabaseCursor_free( & ( ( *runtime_storage_controller )->database_cursor ) );
	}
	//	free runtime storage environment
	if ( ( *runtime_storage_controller )->runtime_environment != NULL )	{
		Rbdb_Environment_free( & ( ( *runtime_storage_controller )->runtime_environment ) );
	}
		
	free( *runtime_storage_controller );
	*runtime_storage_controller	=	NULL;
}

/***********************
*  settingsController  *
***********************/
Rbdb_RuntimeStorageSettingsController* Rbdb_RuntimeStorageController_settingsController(	Rbdb_RuntimeStorageController* runtime_storage_controller )	{
	return runtime_storage_controller->settings_controller;
}

/***********************
*  currentWorkingEnvironment  *
***********************/

Rbdb_Environment* Rbdb_RuntimeStorageController_currentWorkingEnvironment(	Rbdb_RuntimeStorageController*		runtime_storage_controller )	{
	
	return runtime_storage_controller->default_environment;
}

/******************************
*  requireDefaultEnvironment  *
******************************/

Rbdb_Environment* Rbdb_RuntimeStorageController_requireDefaultEnvironment(	Rbdb_RuntimeStorageController*		runtime_storage_controller )	{
	
	if ( runtime_storage_controller->default_environment )	{
		return runtime_storage_controller->default_environment;
	}
	else {
		
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( NULL ),
																			RBDB_ERROR_DEFAULT_ENVIRONMENT_NOT_FOUND, 
																			"Rbdb_RuntimeStorageController_requireDefaultEnvironment",
																			RBDB_ERROR_MESSAGE_TRANSACTION_OPEN );
		
	}
	return NULL;
}

/**************************
*  setCurrentWorkingEnvironment  *
**************************/

void Rbdb_RuntimeStorageController_setCurrentWorkingEnvironment(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																													Rbdb_Environment*					environment )	{
	
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

Rbdb_RuntimeStorageController* Rbdb_RuntimeStorageController_internal_initRuntimeEnvironment( Rbdb_RuntimeStorageController* runtime_storage_controller )	{
	
	/*----------------------*
	*  Runtime Environment  *
	*----------------------*/
	
	//	Initialize our runtime environment (RBDB_IN_MEMORY == NULL for in-memory)
	runtime_storage_controller->runtime_environment		=	Rbdb_Environment_new(	RBDB_IN_MEMORY );
	
	//	Init settings for our runtime environment (create the DB_ENV instance)
	Rbdb_Environment_internal_initWrappedEnvironment(	runtime_storage_controller->runtime_environment,
																										TRUE );

	/*----------------------*
	*  Settings Controller  *
	*----------------------*/
	
	Rbdb_SettingsController*	settings_controller		=	Rbdb_Environment_settingsController( runtime_storage_controller->runtime_environment );
	
	/*----------------------*
	*  Create if Necessary  *
	*----------------------*/
	
	Rbdb_FileSettingsController*	file_settings_controller	=	Rbdb_SettingsController_fileSettingsController( settings_controller );
	
	//	Set to create environment if necessary
	Rbdb_FileSettingsController_turnCreateIfNecessaryOn( file_settings_controller );
															
	/*---------------*
	*  Transactions  *
	*---------------*/
	
	//	Turn off transaction related systems for runtime storage
	Rbdb_TransactionSettingsController_turnOff( Rbdb_SettingsController_transactionSettingsController( settings_controller ) );
	Rbdb_LogSettingsController_turnOff( Rbdb_SettingsController_logSettingsController( settings_controller ) );
	Rbdb_LockSettingsController_turnOff( Rbdb_SettingsController_lockSettingsController( settings_controller ) );	
	Rbdb_DebugSettingsController*	debug_settings_controller	=	Rbdb_SettingsController_debugSettingsController( settings_controller );
	Rbdb_DebugSettingsController_turnRegisterForRecoveryOff( debug_settings_controller );
	Rbdb_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOff( debug_settings_controller );
	Rbdb_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOff( debug_settings_controller );

	/*------------------*
	*  Store in Memory  *
	*------------------*/
	
	//	Initialize runtime environment for memory-only (prohibit writing to disk)
	Rbdb_Environment_initForStorageInMemory( runtime_storage_controller->runtime_environment );
	//	And make sure we actually have a memory pool
	Rbdb_MemoryPoolSettingsController_turnOn( Rbdb_SettingsController_memoryPoolSettingsController( settings_controller ) );

	/*-------------*
	*  Cache Size  *
	*-------------*/

	Rbdb_EnvironmentCacheSettingsController*	environment_cache_settings_controller	=	Rbdb_SettingsController_cacheSettingsController( settings_controller );

	Rbdb_EnvironmentCacheSettingsController_setSizeInMBytes(	environment_cache_settings_controller,
																														RBDB_RUNTIME_STORAGE_CACHE_SIZE_IN_MB	);
	
	/*------------*
	*  Page Size  *
	*------------*/

	Rbdb_MemoryPoolSettingsController*			memory_pool_settings_controller	=	Rbdb_SettingsController_memoryPoolSettingsController( settings_controller );
	Rbdb_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller	=	Rbdb_MemoryPoolSettingsController_fileSettingsController( memory_pool_settings_controller );

	Rbdb_MemoryPoolFileSettingsController_setPageSizeInKBytes(	memory_pool_file_settings_controller,
																															RBDB_RUNTIME_STORAGE_PAGE_SIZE_IN_K );
	
	/*-------------------*
	*  Open Environment  *
	*-------------------*/
	
	//	Open environment
	Rbdb_Environment_internal_openWithoutRuntimeStorage( runtime_storage_controller->runtime_environment );

	/*------------------------*
	*  Runtime Database Type  *
	*------------------------*/
	
	Rbdb_DatabaseSettingsController*			database_settings_controller			=	Rbdb_SettingsController_databaseSettingsController( settings_controller );
	Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	Rbdb_DatabaseSettingsController_typeSettingsController(	database_settings_controller );
	//	Unless otherwise specified, all of our runtime storage will be btree - set the environmental default
	Rbdb_DatabaseTypeSettingsController_setTypeToBTree(	database_type_settings_controller );
	
	/*----------------------*
	*  Database Controller  *
	*----------------------*/
	
	//	Initialize database controller so that we don't create another set of runtime databases inside our runtime environment
	runtime_storage_controller->runtime_environment->database_controller	=	Rbdb_DatabaseController_internal_newWithoutRuntimeStorage( runtime_storage_controller->runtime_environment );
	
	/*--------------------*
	*  Runtime Databases  *
	*--------------------*/
	
	//	Databases for referencing runtime information
	Rbdb_RuntimeStorageController_internal_initRuntimeStoragesDatabases( runtime_storage_controller );
	
	Rbdb_RuntimeStorageController_internal_initEnvironmentAndDatabaseReferenceDatabases( runtime_storage_controller );
	
	/*---------------------*
	*  Runtime Controller  *
	*---------------------*/
	
	return runtime_storage_controller;
}

/************************
*  initPrimaryDatabase  *
************************/

void Rbdb_RuntimeStorageController_internal_initRuntimeStoragesDatabases(	Rbdb_RuntimeStorageController*		runtime_storage_controller )	{

	/*----------------------------*
	*  Primary Storages Database  *
	*----------------------------*/
	
	//	Initialize our runtime storages database
	Rbdb_DatabaseController*	database_controller	=	Rbdb_Environment_databaseController( runtime_storage_controller->runtime_environment );
	runtime_storage_controller->runtime_storages_database			=	Rbdb_Database_new(	database_controller,
																																									"runtime_storages" );
	
}

/************************
*  initPrimaryDatabase  *
************************/

void Rbdb_RuntimeStorageController_internal_initEnvironmentAndDatabaseReferenceDatabases(	Rbdb_RuntimeStorageController*		runtime_storage_controller )	{
	
	Rbdb_DatabaseController*	database_controller	=	Rbdb_Environment_databaseController(	runtime_storage_controller->runtime_environment );
	
	//	database store references to Rbdb_Environment* by DB_ENV*
	runtime_storage_controller->environment_reference_database			=	Rbdb_Database_new(	database_controller,
																																												"runtime_storage__environments" );
	
	//	database store references to Rbdb_Database* by DB*
	runtime_storage_controller->database_reference_database				=	Rbdb_Database_new(	database_controller,
																																											"runtime_storage_database_reference_database" );
	
	Rbdb_Database_internal_openWithoutRuntimeStorage( runtime_storage_controller->environment_reference_database );	
	Rbdb_Database_internal_openWithoutRuntimeStorage( runtime_storage_controller->database_reference_database );	
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
void Rbdb_RuntimeStorageController_internal_storeEnvironmentForBDBEnvironment(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																																								Rbdb_Environment*									environment	)	{

	//	declare and zero keys
	DBT	bdb_key;
	DBT	bdb_data;
	memset( & bdb_key, 0, sizeof( DBT ) );
	memset( & bdb_data, 0, sizeof( DBT ) );

	//	get wrapped bdb environment address and store as key
	uintptr_t	bdb_environment_address	=	(uintptr_t) environment->wrapped_bdb_environment;
	bdb_key.data		=	& bdb_environment_address;
	bdb_key.size		=	sizeof( uintptr_t );
	bdb_key.flags		=	RBDB_NO_FLAGS;
	
	//	get rbdb environment address and store as data
	uintptr_t environment_address	=	(uintptr_t) environment;
	bdb_data.data		=	& environment_address;
	bdb_data.size		=	sizeof( uintptr_t );
	bdb_data.flags	=	RBDB_NO_FLAGS;

	//	store in runtime storage environments reference database
	Rbdb_Database*	environment_reference_database	=	runtime_storage_controller->environment_reference_database;
	int	connection_error = RP_NO_ERROR;
	if ( ( connection_error = environment_reference_database->wrapped_bdb_database->put(	environment_reference_database->wrapped_bdb_database,
																																												NULL,
																																												& bdb_key,
																																												& bdb_data,
																																												RBDB_NO_FLAGS ) ) )	{
		
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"Rbdb_RuntimeStorageController_internal_storeEnvironmentForBDBEnvironment" );
	}

	Rbdb_RuntimeStorageController_setCurrentWorkingEnvironment(	runtime_storage_controller,
																															environment	);
}

/****************************
*  removeStoredEnvironment  *
****************************/

void Rbdb_RuntimeStorageController_internal_removeStoredEnvironment(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																																			Rbdb_Environment*									environment	)	{

	//	create and zero key
	DBT	bdb_key;
	memset( & bdb_key, 0, sizeof( DBT ) );
	
	uintptr_t	bdb_environment_address	=	(uintptr_t) environment->wrapped_bdb_environment;
	bdb_key.data	=	(void*) & bdb_environment_address;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RBDB_NO_FLAGS;
	
	Rbdb_Database*	environments_database	=	runtime_storage_controller->environment_reference_database;
	int	connection_error = RP_NO_ERROR;	
	if ( ( connection_error = environments_database->wrapped_bdb_database->del(	environments_database->wrapped_bdb_database,
																																							NULL,
																																							& bdb_key,
																																							RBDB_NO_FLAGS ) ) )	{
		
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"Rbdb_RuntimeStorageController_internal_removeStoredEnvironment" );
	}
}

/********************************
*  storeDatabaseForBDBDatabase  *
********************************/

void Rbdb_RuntimeStorageController_internal_storeDatabaseForBDBDatabase(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																																					Rbdb_Database*										database	)	{
	
	//	create and zero key and data
	DBT	bdb_key;
	DBT	bdb_data;
	memset( & bdb_key, 0, sizeof( DBT ) );
	memset( & bdb_data, 0, sizeof( DBT ) );
	
	//	get wrapped bdb database address as key
	uintptr_t	bdb_database_address	=	(uintptr_t) database->wrapped_bdb_database;
	bdb_key.data	=	& bdb_database_address;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RBDB_NO_FLAGS;
	
	//	get rbdb database address for data
	uintptr_t database_address	=	(uintptr_t) database;	
	bdb_data.data	=	& database_address;
	bdb_data.size	=	sizeof( uintptr_t );
	bdb_data.flags	=	RBDB_NO_FLAGS;

	Rbdb_Database*	database_reference_database	=	runtime_storage_controller->database_reference_database;
	int connection_error = RP_NO_ERROR;
	if ( ( connection_error = database_reference_database->wrapped_bdb_database->put(	database_reference_database->wrapped_bdb_database,
																																										NULL,
																																										& bdb_key,
																																										& bdb_data,
																																										RBDB_NO_FLAGS ) ) )	{
		
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"Rbdb_RuntimeStorageController_internal_storeDatabaseForBDBDatabase" );
	}
}

/***************************************
*  removeDatabaseStoredForBDBDatabase  *
***************************************/

void Rbdb_RuntimeStorageController_internal_removeDatabaseStoredForBDBDatabase(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																																								Rbdb_Database*						database	)	{
	
	//	create and zero key
	DBT	bdb_key;
	memset( & bdb_key, 0, sizeof( DBT ) );
	
	//	get bdb environment address and set as deletion key
	uintptr_t	bdb_database_address	=	(uintptr_t) database->wrapped_bdb_database;
	bdb_key.data	=	& bdb_database_address;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RBDB_NO_FLAGS;
	
	Rbdb_Database*	database_reference_database	=	runtime_storage_controller->database_reference_database;
	int	connection_error = RP_NO_ERROR;	
	if ( Rbdb_Database_rawKeyExists(	database_reference_database,
										& bdb_database_address,
										sizeof( uintptr_t ) ) )	{
		if ( ( connection_error = database_reference_database->wrapped_bdb_database->del(	database_reference_database->wrapped_bdb_database,
																																											NULL,
																																											& bdb_key,
																																											RBDB_NO_FLAGS ) ) )	{
			
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( runtime_storage_controller->runtime_environment ),
																										connection_error, 
																										"Rbdb_RuntimeStorageController_internal_removeDatabaseStoredForBDBDatabase" );
		}
	}
}

/*********************************
*  environmentForBDBEnvironment  *
*********************************/

Rbdb_Environment* Rbdb_RuntimeStorageController_internal_environmentForBDBEnvironment(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																																												DB_ENV*								bdb_environment	)	{
	
	//	runtime_storage_controller->environment_reference_database contains bdb_environment_address => environment_address
	//	since any given runtime storage is within the same memory space, every environment will have a unique memory address
	
	
	//	when runtime storage is created, this database needs to be initialized
	//	when an environment is created, this database needs an entry for the environment
	//	when this function is called, it returns the rbdb environment for bdb address
	
	Rbdb_Database*	database	=	runtime_storage_controller->environment_reference_database;
	
	DBT	bdb_key;
	DBT	bdb_data;
	
	bdb_key.data	=	(void*) bdb_environment;
	bdb_key.size	=	sizeof( uintptr_t );
	
	int	connection_error	=	0;
	
	if ( ( connection_error = database->wrapped_bdb_database->get(	database->wrapped_bdb_database,
																																	NULL,
																																	& bdb_key,
																																	& bdb_data,
																																	RBDB_NO_FLAGS ) ) )	{
	
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"Rbdb_RuntimeStorageController_internal_environmentForBDBEnvironment" );
		return NULL;		
	}
	
	Rbdb_Environment*	return_environment	=	(Rbdb_Environment*) ( *(uintptr_t*) bdb_data.data );
	
	return return_environment;
}	

/***************************
*  databaseForBDBDatabase  *
***************************/

Rbdb_Database* Rbdb_RuntimeStorageController_internal_databaseForBDBDatabase(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																																							DB*									bdb_database	)	{
	
	//	runtime_storage_controller->database_reference_database contains bdb_database_address => database_address
	//	since any given runtime storage is within the same memory space, every database will have a unique memory address
	
	//	when runtime storage is created, this database needs to be initialized
	//	when a database is created, this database needs an entry for the database
	//	when this function is called, it returns the rbdb database for bdb address
	
	//	create and zero key and data
	DBT					bdb_key;
	DBT					bdb_data;
	memset( & bdb_key, 0, sizeof( DBT ) );
	memset( & bdb_data, 0, sizeof( DBT ) );
	
	//	get address of passed bdb database - matches key and wrapped bdb database
	uintptr_t		address_of_bdb_database	=	(uintptr_t) bdb_database;
	bdb_key.data	=	& address_of_bdb_database;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RBDB_NO_FLAGS;
	
	Rbdb_Database*		database_reference_database	=	runtime_storage_controller->database_reference_database;
	int	connection_error	=	RP_NO_ERROR;				
	if ( ( connection_error = database_reference_database->wrapped_bdb_database->get(	database_reference_database->wrapped_bdb_database,
																					NULL,
																					& bdb_key,
																					& bdb_data,
																					RBDB_NO_FLAGS ) ) )	{
		
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"Rbdb_RuntimeStorageController_internal_databaseForBDBDatabase" );
		return NULL;
	}
	
	return (Rbdb_Database*) ( *(uintptr_t*) bdb_data.data );
}	
