/*
 *		RPDB::RuntimeStorageController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_RuntimeStorageController.h"
#include "RPDB_RuntimeStorageController_internal.h"

#include "RPDB_RuntimeStorage.h"

#include "RPDB_Environment.h"
#include "RPDB_Environment_internal.h"

#include "RPDB_Database.h"
#include "RPDB_Database_internal.h"
#include "RPDB_DatabaseController.h"
#include "RPDB_DatabaseController_internal.h"
#include "RPDB_DatabaseCursorController_internal.h"
#include "RPDB_DatabaseCursor.h"

#include "RPDB_ErrorController.h"

#include "RPDB_Record.h"

#include "RPDB_SettingsController.h"
#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_DatabaseSettingsController_internal.h"
#include "RPDB_DatabaseReadWriteSettingsController.h"
#include "RPDB_DatabaseTypeSettingsController.h"
#include "RPDB_DatabaseTypeBtreeSettingsController.h"
#include "RPDB_DatabaseCursorReadWriteSettingsController.h"
#include "RPDB_DatabaseCursorSettingsController.h"
#include "RPDB_DatabaseCursorSettingsController_internal.h"
#include "RPDB_DebugSettingsController.h"
#include "RPDB_FileSettingsController.h"
#include "RPDB_LockSettingsController.h"
#include "RPDB_LogSettingsController.h"
#include "RPDB_MemoryPoolSettingsController.h"
#include "RPDB_MemoryPoolFileSettingsController.h"
#include "RPDB_ThreadSettingsController.h"
#include "RPDB_TransactionSettingsController.h"
#include "RPDB_RuntimeStorageSettingsController.h"
#include "RPDB_EnvironmentCacheSettingsController.h"

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
//	and multiple RPDB_Environments can co-exist under the umbrella of this singleton
RPDB_RuntimeStorageController* RPDB_RuntimeStorageController_sharedInstance()	{

	//	We only ever want one runtime_storage_controller
	static RPDB_RuntimeStorageController	runtime_storage_controller;
	
	//	Initialize our runtime environment if it hasn't been done already	
	if ( runtime_storage_controller.runtime_environment == NULL )	{
		
		runtime_storage_controller.default_environment	=	NULL;
		
		//	Initialize runtime environment
		RPDB_RuntimeStorageController_internal_initRuntimeEnvironment( & runtime_storage_controller );
	}
	
	return & runtime_storage_controller;	
}

/*********
*  free  *
*********/
void RPDB_RuntimeStorageController_free( RPDB_RuntimeStorageController** runtime_storage_controller )	{

	//	free runtime storage environments reference database
	if ( ( *runtime_storage_controller )->environment_reference_database != NULL )	{
		RPDB_Database_free( & ( ( *runtime_storage_controller )->environment_reference_database ) );
	}
	//	free runtime storage database reference database
	if ( ( *runtime_storage_controller )->database_reference_database != NULL )	{
		RPDB_Database_free( & ( ( *runtime_storage_controller )->database_reference_database ) );
	}
	//	free runtime storages primary database (stores other runtime storages)
	if ( ( *runtime_storage_controller )->runtime_storages_database != NULL )	{
		RPDB_Database_free( & ( ( *runtime_storage_controller )->runtime_storages_database ) );
	}
	//	free runtime storage database cursor
	if ( ( *runtime_storage_controller )->database_cursor != NULL )	{
		RPDB_DatabaseCursor_free( & ( ( *runtime_storage_controller )->database_cursor ) );
	}
	//	free runtime settings controller
	if ( ( *runtime_storage_controller )->settings_controller != NULL )	{
		RPDB_RuntimeStorageSettingsController_free( & ( ( *runtime_storage_controller )->settings_controller ) );
	}
	//	free runtime storage environment
	if ( ( *runtime_storage_controller )->runtime_environment != NULL )	{
		RPDB_Environment_free( & ( ( *runtime_storage_controller )->runtime_environment ) );
	}
		
	free( *runtime_storage_controller );
	*runtime_storage_controller	=	NULL;
}

/***********************
*  settingsController  *
***********************/
RPDB_RuntimeStorageSettingsController* RPDB_RuntimeStorageController_settingsController(	RPDB_RuntimeStorageController* runtime_storage_controller )	{
	return runtime_storage_controller->settings_controller;
}

/***********************
*  defaultEnvironment  *
***********************/

RPDB_Environment* RPDB_RuntimeStorageController_defaultEnvironment(	RPDB_RuntimeStorageController*		runtime_storage_controller )	{
	
	return runtime_storage_controller->default_environment;
}

/******************************
*  requireDefaultEnvironment  *
******************************/

RPDB_Environment* RPDB_RuntimeStorageController_requireDefaultEnvironment(	RPDB_RuntimeStorageController*		runtime_storage_controller )	{
	
	if ( runtime_storage_controller->default_environment )	{
		return runtime_storage_controller->default_environment;
	}
	else {
		
		RPDB_ErrorController_throwError(	RPDB_Environment_errorController( NULL ),
																			RPDB_ERROR_DEFAULT_ENVIRONMENT_NOT_FOUND, 
																			"RPDB_RuntimeStorageController_requireDefaultEnvironment",
																			RPDB_ERROR_MESSAGE_TRANSACTION_OPEN );
		
	}
	return NULL;
}

/**************************
*  setDefaultEnvironment  *
**************************/

void RPDB_RuntimeStorageController_setDefaultEnvironment(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																													RPDB_Environment*					environment )	{
	
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

RPDB_RuntimeStorageController* RPDB_RuntimeStorageController_internal_initRuntimeEnvironment( RPDB_RuntimeStorageController* runtime_storage_controller )	{
	
	/*----------------------*
	*  Runtime Environment  *
	*----------------------*/
	
	//	Initialize our runtime environment (RPDB_IN_MEMORY == NULL for in-memory)
	runtime_storage_controller->runtime_environment		=	RPDB_Environment_new(	RPDB_IN_MEMORY );
	
	//	Init settings for our runtime environment (create the DB_ENV instance)
	RPDB_Environment_internal_initWrappedEnvironment(	runtime_storage_controller->runtime_environment,
																										TRUE );

	/*----------------------*
	*  Settings Controller  *
	*----------------------*/
	
	//	Initialize our runtime settings controller
	//	RPDB_RuntimeStorageSettingsController
	
	RPDB_RuntimeStorageSettingsController*	runtime_storage_settings_controller		=	RPDB_RuntimeStorageSettingsController_new( runtime_storage_controller );

	runtime_storage_controller->settings_controller																=	runtime_storage_settings_controller;
	
	RPDB_SettingsController*	settings_controller		=	RPDB_Environment_settingsController( runtime_storage_controller->runtime_environment );
	
	/*----------------------*
	*  Create if Necessary  *
	*----------------------*/
	
	RPDB_FileSettingsController*	file_settings_controller	=	RPDB_SettingsController_fileSettingsController( settings_controller );
	
	//	Set to create environment if necessary
	RPDB_FileSettingsController_turnCreateIfNecessaryOn( file_settings_controller );
															
	/*---------------*
	*  Transactions  *
	*---------------*/
	
	//	Turn off transaction related systems for runtime storage
	RPDB_TransactionSettingsController_turnOff( RPDB_SettingsController_transactionSettingsController( settings_controller ) );
	RPDB_LogSettingsController_turnOff( RPDB_SettingsController_logSettingsController( settings_controller ) );
	RPDB_LockSettingsController_turnOff( RPDB_SettingsController_lockSettingsController( settings_controller ) );	
	RPDB_DebugSettingsController*	debug_settings_controller	=	RPDB_SettingsController_debugSettingsController( settings_controller );
	RPDB_DebugSettingsController_turnRegisterForRecoveryOff( debug_settings_controller );
	RPDB_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOff( debug_settings_controller );
	RPDB_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOff( debug_settings_controller );

	/*------------------*
	*  Store in Memory  *
	*------------------*/
	
	//	Initialize runtime environment for memory-only (prohibit writing to disk)
	RPDB_Environment_initForStorageInMemory( runtime_storage_controller->runtime_environment );
	//	And make sure we actually have a memory pool
	RPDB_MemoryPoolSettingsController_turnOn( RPDB_SettingsController_memoryPoolSettingsController( settings_controller ) );

	/*-------------*
	*  Cache Size  *
	*-------------*/

	RPDB_EnvironmentCacheSettingsController*	environment_cache_settings_controller	=	RPDB_SettingsController_cacheSettingsController( settings_controller );

	RPDB_EnvironmentCacheSettingsController_setSizeInMBytes(	environment_cache_settings_controller,
																														RPDB_RUNTIME_STORAGE_CACHE_SIZE_IN_MB	);
	
	/*------------*
	*  Page Size  *
	*------------*/

	RPDB_MemoryPoolSettingsController*			memory_pool_settings_controller	=	RPDB_SettingsController_memoryPoolSettingsController( settings_controller );
	RPDB_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller	=	RPDB_MemoryPoolSettingsController_fileSettingsController( memory_pool_settings_controller );

	RPDB_MemoryPoolFileSettingsController_setPageSizeInKBytes(	memory_pool_file_settings_controller,
																															RPDB_RUNTIME_STORAGE_PAGE_SIZE_IN_K );
	
	/*-------------------*
	*  Open Environment  *
	*-------------------*/
	
	//	Open environment
	RPDB_Environment_internal_openWithoutRuntimeStorage( runtime_storage_controller->runtime_environment );

	/*------------------------*
	*  Runtime Database Type  *
	*------------------------*/
	
	RPDB_DatabaseSettingsController*			database_settings_controller			=	RPDB_SettingsController_databaseSettingsController( settings_controller );
	RPDB_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPDB_DatabaseSettingsController_typeSettingsController(	database_settings_controller );
	//	Unless otherwise specified, all of our runtime storage will be btree - set the environmental default
	RPDB_DatabaseTypeSettingsController_setTypeToBTree(	database_type_settings_controller );
	
	/*----------------------*
	*  Database Controller  *
	*----------------------*/
	
	//	Initialize database controller so that we don't create another set of runtime databases inside our runtime environment
	runtime_storage_controller->runtime_environment->database_controller	=	RPDB_DatabaseController_internal_newWithoutRuntimeStorage( runtime_storage_controller->runtime_environment );
	
	/*--------------------*
	*  Runtime Databases  *
	*--------------------*/
	
	//	Databases for referencing runtime information
	RPDB_RuntimeStorageController_internal_initRuntimeStoragesDatabases( runtime_storage_controller );
	
	RPDB_RuntimeStorageController_internal_initEnvironmentAndDatabaseReferenceDatabases( runtime_storage_controller );
	
	/*---------------------*
	*  Runtime Controller  *
	*---------------------*/
	
	return runtime_storage_controller;
}

/************************
*  initPrimaryDatabase  *
************************/

void RPDB_RuntimeStorageController_internal_initRuntimeStoragesDatabases(	RPDB_RuntimeStorageController*		runtime_storage_controller )	{

	/*----------------------------*
	*  Primary Storages Database  *
	*----------------------------*/
	
	//	Initialize our runtime storages database
	RPDB_DatabaseController*	database_controller	=	RPDB_Environment_databaseController( runtime_storage_controller->runtime_environment );
	runtime_storage_controller->runtime_storages_database			=	RPDB_Database_new(	database_controller,
																																									"runtime_storages" );
	
	/*------------------*
	*  Database Cursor  *
	*------------------*/
	
	//	Init database_cursor for runtime iteration
	RPDB_RuntimeStorageController_internal_initRuntimeStoragesCursors( runtime_storage_controller );
	
}

/************************
*  initPrimaryDatabase  *
************************/

void RPDB_RuntimeStorageController_internal_initEnvironmentAndDatabaseReferenceDatabases(	RPDB_RuntimeStorageController*		runtime_storage_controller )	{
	
	RPDB_DatabaseController*	database_controller	=	RPDB_Environment_databaseController(	runtime_storage_controller->runtime_environment );
	
	//	database store references to RPDB_Environment* by DB_ENV*
	runtime_storage_controller->environment_reference_database			=	RPDB_Database_new(	database_controller,
																																												"runtime_storage__environments" );
	
	//	database store references to RPDB_Database* by DB*
	runtime_storage_controller->database_reference_database				=	RPDB_Database_new(	database_controller,
																																											"runtime_storage_database_reference_database" );
	
	RPDB_Database_internal_openWithoutRuntimeStorage( runtime_storage_controller->environment_reference_database );	
	RPDB_Database_internal_openWithoutRuntimeStorage( runtime_storage_controller->database_reference_database );	
}

/*****************************
*  initRuntimeStorageCursor  *
*****************************/

void RPDB_RuntimeStorageController_internal_initRuntimeStoragesCursors(	RPDB_RuntimeStorageController*		runtime_storage_controller )	{
	
	//	We need to initialize the cursor controller here without runtime storage so we don't loop
	runtime_storage_controller->runtime_storages_database->cursor_controller	=	RPDB_DatabaseCursorController_internal_newWithoutRuntimeStorage( runtime_storage_controller->runtime_storages_database );
	
	//	Create a database_cursor to deal with runtime database activity
	runtime_storage_controller->database_cursor	=	RPDB_DatabaseCursor_new( RPDB_Database_cursorController( runtime_storage_controller->runtime_storages_database ) );
	
	RPDB_DatabaseCursorSettingsController*						database_cursor_settings_controller	=	RPDB_DatabaseCursor_settingsController( runtime_storage_controller->database_cursor );
	RPDB_DatabaseCursorReadWriteSettingsController*		database_cursor_read_write_settings_controller	=	RPDB_DatabaseCursorSettingsController_readWriteSettingsController( database_cursor_settings_controller );
	//	We want to be able to use the database_cursor for writing data
	RPDB_DatabaseCursorReadWriteSettingsController_turnPermitWriteOn(	database_cursor_read_write_settings_controller );
	
	//	Now open the database_cursor
	RPDB_DatabaseCursor_open( runtime_storage_controller->database_cursor );	
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
void RPDB_RuntimeStorageController_internal_storeEnvironmentForBDBEnvironment(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																																								RPDB_Environment*									environment	)	{

	//	declare and zero keys
	DBT	bdb_key;
	DBT	bdb_data;
	memset( & bdb_key, 0, sizeof( DBT ) );
	memset( & bdb_data, 0, sizeof( DBT ) );

	//	get wrapped bdb environment address and store as key
	uintptr_t	bdb_environment_address	=	(uintptr_t) environment->wrapped_bdb_environment;
	bdb_key.data	=	& bdb_environment_address;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RPDB_NO_FLAGS;
	
	//	get rpdb environment address and store as data
	uintptr_t environment_address	=	(uintptr_t) environment;
	bdb_data.data	=	& environment_address;
	bdb_data.size	=	sizeof( uintptr_t );
	bdb_data.flags	=	RPDB_NO_FLAGS;

	//	store in runtime storage environments reference database
	RPDB_Database*	environment_reference_database	=	runtime_storage_controller->environment_reference_database;
	int	connection_error = RP_NO_ERROR;
	if ( ( connection_error = environment_reference_database->wrapped_bdb_database->put(	environment_reference_database->wrapped_bdb_database,
																																												NULL,
																																												& bdb_key,
																																												& bdb_data,
																																												RPDB_NO_FLAGS ) ) )	{
		
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"RPDB_RuntimeStorageController_internal_storeEnvironmentForBDBEnvironment" );
	}

	//	If we automatically set default environment then we need to do so here
	if ( RPDB_RuntimeStorageSettingsController_automaticDefaultEnvironment( runtime_storage_controller->settings_controller ) )	{
		
		if ( RPDB_RuntimeStorageController_defaultEnvironment( runtime_storage_controller ) == NULL )	{
			
			RPDB_RuntimeStorageController_setDefaultEnvironment(	runtime_storage_controller,
																														environment	);
		}
	}	
}

/****************************
*  removeStoredEnvironment  *
****************************/

void RPDB_RuntimeStorageController_internal_removeStoredEnvironment(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																																			RPDB_Environment*									environment	)	{

	//	create and zero key
	DBT	bdb_key;
	memset( & bdb_key, 0, sizeof( DBT ) );
	
	uintptr_t	bdb_environment_address	=	(uintptr_t) environment->wrapped_bdb_environment;
	bdb_key.data	=	(void*) & bdb_environment_address;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RPDB_NO_FLAGS;
	
	RPDB_Database*	environments_database	=	runtime_storage_controller->environment_reference_database;
	int	connection_error = RP_NO_ERROR;	
	if ( ( connection_error = environments_database->wrapped_bdb_database->del(	environments_database->wrapped_bdb_database,
																																							NULL,
																																							& bdb_key,
																																							RPDB_NO_FLAGS ) ) )	{
		
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"RPDB_RuntimeStorageController_internal_removeStoredEnvironment" );
	}
}

/********************************
*  storeDatabaseForBDBDatabase  *
********************************/

void RPDB_RuntimeStorageController_internal_storeDatabaseForBDBDatabase(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																																					RPDB_Database*										database	)	{
	
	//	create and zero key and data
	DBT	bdb_key;
	DBT	bdb_data;
	memset( & bdb_key, 0, sizeof( DBT ) );
	memset( & bdb_data, 0, sizeof( DBT ) );
	
	//	get wrapped bdb database address as key
	uintptr_t	bdb_database_address	=	(uintptr_t) database->wrapped_bdb_database;
	bdb_key.data	=	& bdb_database_address;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RPDB_NO_FLAGS;
	
	//	get rpdb database address for data
	uintptr_t database_address	=	(uintptr_t) database;	
	bdb_data.data	=	& database_address;
	bdb_data.size	=	sizeof( uintptr_t );
	bdb_data.flags	=	RPDB_NO_FLAGS;

	RPDB_Database*	database_reference_database	=	runtime_storage_controller->database_reference_database;
	int connection_error = RP_NO_ERROR;
	if ( ( connection_error = database_reference_database->wrapped_bdb_database->put(	database_reference_database->wrapped_bdb_database,
																																										NULL,
																																										& bdb_key,
																																										& bdb_data,
																																										RPDB_NO_FLAGS ) ) )	{
		
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"RPDB_RuntimeStorageController_internal_storeDatabaseForBDBDatabase" );
	}
}

/***************************************
*  removeDatabaseStoredForBDBDatabase  *
***************************************/

void RPDB_RuntimeStorageController_internal_removeDatabaseStoredForBDBDatabase(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																																								RPDB_Database*						database	)	{
	
	//	create and zero key
	DBT	bdb_key;
	memset( & bdb_key, 0, sizeof( DBT ) );
	
	//	get bdb environment address and set as deletion key
	uintptr_t	bdb_database_address	=	(uintptr_t) database->wrapped_bdb_database;
	bdb_key.data	=	& bdb_database_address;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RPDB_NO_FLAGS;
	
	RPDB_Database*	database_reference_database	=	runtime_storage_controller->database_reference_database;
	int	connection_error = RP_NO_ERROR;	
	if ( RPDB_Database_rawKeyExists(	database_reference_database,
										& bdb_database_address,
										sizeof( uintptr_t ) ) )	{
		if ( ( connection_error = database_reference_database->wrapped_bdb_database->del(	database_reference_database->wrapped_bdb_database,
																																											NULL,
																																											& bdb_key,
																																											RPDB_NO_FLAGS ) ) )	{
			
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( runtime_storage_controller->runtime_environment ),
																										connection_error, 
																										"RPDB_RuntimeStorageController_internal_removeDatabaseStoredForBDBDatabase" );
		}
	}
}

/*********************************
*  environmentForBDBEnvironment  *
*********************************/

RPDB_Environment* RPDB_RuntimeStorageController_internal_environmentForBDBEnvironment(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																																												DB_ENV*								bdb_environment	)	{
	
	//	runtime_storage_controller->environment_reference_database contains bdb_environment_address => environment_address
	//	since any given runtime storage is within the same memory space, every environment will have a unique memory address
	
	
	//	when runtime storage is created, this database needs to be initialized
	//	when an environment is created, this database needs an entry for the environment
	//	when this function is called, it returns the rpdb environment for bdb address
	
	RPDB_Database*	database	=	runtime_storage_controller->environment_reference_database;
	
	DBT	bdb_key;
	DBT	bdb_data;
	
	bdb_key.data	=	(void*) bdb_environment;
	bdb_key.size	=	sizeof( uintptr_t );
	
	int	connection_error	=	0;
	
	if ( ( connection_error = database->wrapped_bdb_database->get(	database->wrapped_bdb_database,
																																	NULL,
																																	& bdb_key,
																																	& bdb_data,
																																	RPDB_NO_FLAGS ) ) )	{
	
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"RPDB_RuntimeStorageController_internal_environmentForBDBEnvironment" );
		return NULL;		
	}
	
	RPDB_Environment*	return_environment	=	(RPDB_Environment*) ( *(uintptr_t*) bdb_data.data );
	
	return return_environment;
}	

/***************************
*  databaseForBDBDatabase  *
***************************/

RPDB_Database* RPDB_RuntimeStorageController_internal_databaseForBDBDatabase(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																																							DB*									bdb_database	)	{
	
	//	runtime_storage_controller->database_reference_database contains bdb_database_address => database_address
	//	since any given runtime storage is within the same memory space, every database will have a unique memory address
	
	//	when runtime storage is created, this database needs to be initialized
	//	when a database is created, this database needs an entry for the database
	//	when this function is called, it returns the rpdb database for bdb address
	
	//	create and zero key and data
	DBT					bdb_key;
	DBT					bdb_data;
	memset( & bdb_key, 0, sizeof( DBT ) );
	memset( & bdb_data, 0, sizeof( DBT ) );
	
	//	get address of passed bdb database - matches key and wrapped bdb database
	uintptr_t		address_of_bdb_database	=	(uintptr_t) bdb_database;
	bdb_key.data	=	& address_of_bdb_database;
	bdb_key.size	=	sizeof( uintptr_t );
	bdb_key.flags	=	RPDB_NO_FLAGS;
	
	RPDB_Database*		database_reference_database	=	runtime_storage_controller->database_reference_database;
	int	connection_error	=	RP_NO_ERROR;				
	if ( ( connection_error = database_reference_database->wrapped_bdb_database->get(	database_reference_database->wrapped_bdb_database,
																					NULL,
																					& bdb_key,
																					& bdb_data,
																					RPDB_NO_FLAGS ) ) )	{
		
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( runtime_storage_controller->runtime_environment ),
																									connection_error, 
																									"RPDB_RuntimeStorageController_internal_databaseForBDBDatabase" );
		return NULL;
	}
	
	return (RPDB_Database*) ( *(uintptr_t*) bdb_data.data );
}	
