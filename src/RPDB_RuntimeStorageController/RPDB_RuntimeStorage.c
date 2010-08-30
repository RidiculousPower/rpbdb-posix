/*
 *		RPDB::RuntimeStorageController::RuntimeStorage
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

	#include "RPDB_RuntimeStorage.h"
	#include "RPDB_RuntimeStorage_internal.h"

	#include "RPDB_RuntimeStorageController.h"
	#include "RPDB_RuntimeStorageController_internal.h"

	#include "RPDB_Database.h"
	#include "RPDB_Database_internal.h"

	#include "RPDB_DatabaseCursorController_internal.h"
	#include "RPDB_DatabaseCursor.h"
	#include "RPDB_DatabaseCursor_internal.h"

	#include "RPDB_Record.h"
	#include "RPDB_Key.h"
	#include "RPDB_Data.h"

	#include "RPDB_RuntimeStorageController.h"
	#include "RPDB_RuntimeStorageSettingsController.h"
	#include "RPDB_RuntimeStorageSettingsController_internal.h"

	#include "RPDB_DatabaseTypeSettingsController.h"
	#include "RPDB_DatabaseSettingsController.h"
	#include "RPDB_DatabaseCursorReadWriteSettingsController.h"
	#include "RPDB_DatabaseCursorSettingsController.h"
	
	#include <string.h>
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_RuntimeStorage* RPDB_RuntimeStorage_new(	RPDB_RuntimeStorageController*		parent_runtime_storage_controller,
												char*								runtime_storage_name )	{
	
	RPDB_RuntimeStorage*	runtime_storage = calloc( 1, sizeof( RPDB_RuntimeStorage ) );
	
	runtime_storage->parent_runtime_storage_controller = parent_runtime_storage_controller;
	
	//	Make call to instantiate local settings controller
	runtime_storage->settings_controller	=	RPDB_RuntimeStorageSettingsController_internal_copyOfSettingsControllerForInstance( RPDB_RuntimeStorageController_settingsController( parent_runtime_storage_controller ) );
	
	RPDB_RuntimeStorage_internal_initStorageHashForName(	runtime_storage,
															runtime_storage_name );
	
	return runtime_storage;	
}

/***************************
*  free  *
***************************/
void RPDB_RuntimeStorage_free(	RPDB_RuntimeStorage** runtime_storage )	{

	//	free this runtime storage's database cursor
	if ( ( *runtime_storage )->database_cursor != NULL )	{
		RPDB_DatabaseCursor_free( & ( ( *runtime_storage )->database_cursor ) );
	}
	
	//	free runtime storage settings controller
	//	this is the one settings controller not stored in the environment
	if ( ( *runtime_storage )->settings_controller != NULL )	{
		RPDB_RuntimeStorageSettingsController_free( & ( ( *runtime_storage )->settings_controller ) );
	}
	
	//	free this runtime storage's database
	if ( ( *runtime_storage )->database != NULL )	{
		RPDB_Database_free( & ( ( *runtime_storage )->database ) );
	}

	//	if we have a string for our name we allocated it via calloc so we need to free
	if ( ( *runtime_storage )->name != NULL )	{
		free( ( *runtime_storage )->name );
	}
	
	free( *runtime_storage );
	*runtime_storage	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_RuntimeStorageSettingsController* RPDB_RuntimeStorage_settingsController(	RPDB_RuntimeStorage* runtime_storage )	{
	return runtime_storage->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_RuntimeStorage_parentEnvironment(	RPDB_RuntimeStorage* runtime_storage )	{
	return runtime_storage->parent_environment;
}

/********************
*  countRecords  *
********************/

uint32_t RPDB_RuntimeStorage_countRecords(	RPDB_RuntimeStorage*	runtime_storage )	{

	
	//	Puts count in
	//	cursor_controller->runtime_storage->record_count
	
	return runtime_storage->record_count;
}

/****************
*  keyExists  *
****************/

BOOL RPDB_RuntimeStorage_keyExists(	RPDB_RuntimeStorage*		runtime_storage, 
										RPDB_Key*					key )	{

	return RPDB_Database_keyExists( runtime_storage->database,
														key	);
}

/********************
*  rawKeyExists  *
********************/

BOOL RPDB_RuntimeStorage_rawKeyExists(	RPDB_RuntimeStorage*		runtime_storage, 
																				void*										raw_key,
																				uint32_t								key_size )	{
	
	return RPDB_Database_rawKeyExists( runtime_storage->database,
															raw_key,
															key_size	);
}

/****************************
*  retrieveKey  *
****************************/

RPDB_Record* RPDB_RuntimeStorage_retrieveKey(	RPDB_RuntimeStorage*		runtime_storage, 
																							RPDB_Key*								key )	{
	
	//	Look in database for key - if it exists, return it
	return RPDB_DatabaseCursor_retrieveKey( runtime_storage->database_cursor,
																					key ); 
	
}

/********************************
*  retrieveRawKey  *
********************************/

RPDB_Record* RPDB_RuntimeStorage_retrieveRawKey(	RPDB_RuntimeStorage*		runtime_storage, 
																									void*										key,
																									uint32_t								key_size )	{
	
	//	Look in database for key - if it exists, return it
	return RPDB_DatabaseCursor_retrieveRawKey(	runtime_storage->database_cursor,
																							key,
																							key_size ); 
	
}

/********************
*  insertRecord  *
********************/

void RPDB_RuntimeStorage_insertRecord(	RPDB_RuntimeStorage*		runtime_storage, 
																				RPDB_Record*						record )	{
									
	RPDB_DatabaseCursor_writeRecord(	runtime_storage->database_cursor,
																		record );	
}

/************************
*  insertKeyDataPair  *
************************/

void RPDB_RuntimeStorage_insertKeyDataPair(	RPDB_RuntimeStorage*		runtime_storage, 
																						RPDB_Key*	 				key,
																						RPDB_Data*					data )	{
									
	RPDB_DatabaseCursor_internal_writeKeyDataPair(	runtime_storage->database_cursor, 
													DB_CURRENT,
													key,
													data );
}

/****************************
*  insertRawKeyDataPair  *
****************************/

//	Datas are generally going to be pointers (addresses stored during runtime), but they have to be stored as strings
void RPDB_RuntimeStorage_insertRawKeyDataPair(	RPDB_RuntimeStorage*		runtime_storage, 
												void* 						key,
												uint32_t					key_size,
												void* 						data,
												uint32_t					data_size )	{
	
	
	//	Set data in database for key to data
	RPDB_Database_writeRawKeyDataPair( runtime_storage->database,
										key,
										key_size,
										data,
										data_size );	
}

/********************
*  deleteRecord  *
********************/

void RPDB_RuntimeStorage_deleteRecord(	RPDB_RuntimeStorage*	runtime_storage,
										RPDB_Record*			record )	{

	RPDB_DatabaseCursor_deleteRecord(	runtime_storage->database_cursor,
										record	);
}

/************************
*  deleteRecordForKey  *
************************/

void RPDB_RuntimeStorage_deleteRecordForKey(	RPDB_RuntimeStorage*	runtime_storage,
												RPDB_Key*				key )	{

	//	Delete data in database for key
	RPDB_DatabaseCursor_deleteKey( runtime_storage->database_cursor,
									key	);
}

/****************************
*  deleteRecordForRawKey  *
****************************/

void RPDB_RuntimeStorage_deleteRecordForRawKey(	RPDB_RuntimeStorage*	runtime_storage,
													void*					key,
													uint32_t				key_size	)	{
	
	//	Delete data in database for key
	RPDB_DatabaseCursor_deleteRawKey(	runtime_storage->database_cursor,
										key,
										key_size	);
}


/****************
*  iterate  *
****************/

//	Sets the database_cursor to the first item in the database and returns it
void RPDB_RuntimeStorage_iterate( RPDB_RuntimeStorage*	runtime_storage )	{
	
	runtime_storage->started_iteration = FALSE;
	RPDB_DatabaseCursor_retrieveFirst( runtime_storage->database_cursor );
}

/********************
*  currentRecord  *
********************/

//	Returns whatever the database_cursor is currently pointing to
RPDB_Record* RPDB_RuntimeStorage_currentRecord( RPDB_RuntimeStorage*	runtime_storage )	{
	
	return RPDB_DatabaseCursor_retrieveCurrent( runtime_storage->database_cursor );
}

/******************
*  nextRecord  *
******************/

RPDB_Record* RPDB_RuntimeStorage_nextRecord( RPDB_RuntimeStorage*	runtime_storage )	{
	
	if ( runtime_storage->started_iteration == FALSE )	{
		runtime_storage->started_iteration = TRUE;
		return RPDB_RuntimeStorage_currentRecord( runtime_storage );
	}
	else	{
		return RPDB_DatabaseCursor_retrieveNext( runtime_storage->database_cursor );	
	}
	return NULL;
}

/********************
*  popCurrentData  *
********************/

//	Returns whatever the database_cursor is currently pointing to and removes it from the database. 
//	This is useful primarily for iterating all items for closing
RPDB_Record* RPDB_RuntimeStorage_popCurrentData( RPDB_RuntimeStorage*	runtime_storage )	{

	RPDB_Record*	current_record = RPDB_DatabaseCursor_retrieveCurrent( runtime_storage->database_cursor );
	if ( current_record != NULL )	{
		RPDB_DatabaseCursor_deleteCurrentRecord( runtime_storage->database_cursor );
		RPDB_DatabaseCursor_retrieveNext( runtime_storage->database_cursor );
	}
	
	return current_record;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********************************
*  initStorageHashForName  *
********************************/

RPDB_RuntimeStorage* RPDB_RuntimeStorage_internal_initStorageHashForName(	RPDB_RuntimeStorage*		runtime_storage,
																																						char*						name )	{
	
	runtime_storage->database	=	RPDB_Database_new(	runtime_storage->parent_runtime_storage_controller->runtime_environment->database_controller,
																									name );
	
	//	Set the database type - BTree
	RPDB_DatabaseTypeSettingsController_setTypeToBTree( 
		//	Type settings controller
		RPDB_DatabaseSettingsController_typeSettingsController(
			//	Get the local settings controller
			RPDB_Database_settingsController( runtime_storage->database ) ) );	
	
	//	Open the database with our settings
	RPDB_Database_internal_openWithoutRuntimeStorage( runtime_storage->database );
	
	//	We need to initialize the cursor controller here without runtime storage so we don't loop
	runtime_storage->database->cursor_controller	=	RPDB_DatabaseCursorController_internal_newWithoutRuntimeStorage( runtime_storage->database );
	
	//	Create a database_cursor to deal with runtime database activity
	runtime_storage->database_cursor			=	RPDB_DatabaseCursor_new( RPDB_Database_cursorController( runtime_storage->database ) );
	runtime_storage->database_cursor->name	=	strdup( "runtime_storage_cursor" );
	
	//	We want to be able to use the database_cursor for writing data
	RPDB_DatabaseCursorReadWriteSettingsController_turnPermitWriteOn( 
		RPDB_DatabaseCursorSettingsController_readWriteSettingsController( 
			RPDB_DatabaseCursor_settingsController( runtime_storage->database_cursor ) ) );
	
	//	Now open the database_cursor
	RPDB_DatabaseCursor_open( runtime_storage->database_cursor );
	
	return runtime_storage;
}

