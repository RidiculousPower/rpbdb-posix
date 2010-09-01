/*
 *		RPDB::DatabaseController::Database::DatabaseCursorController::DatabaseCursor
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseCursor.h"
#include "RPDB_DatabaseCursor_internal.h"

#include "RPDB_Environment.h"

#include "RPDB_ErrorController.h"

#include "RPDB_Database.h"
#include "RPDB_Database_internal.h"

#include "RPDB_Record.h"
#include "RPDB_Record_internal.h"
#include "RPDB_Key.h"

#include "RPDB_TransactionController.h"
#include "RPDB_TransactionController_internal.h"

#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_DatabaseCursorSettingsController.h"
#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_DatabaseTypeSettingsController.h"
#include "RPDB_DatabaseTypeBtreeSettingsController.h"
#include "RPDB_DatabaseReadWriteSettingsController.h"

#include "RPDB_DatabaseCursorSettingsController_internal.h"
#include "RPDB_DatabaseCursorReadWriteSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
RPDB_DatabaseCursor* RPDB_DatabaseCursor_new( RPDB_DatabaseCursorController* parent_database_cursor_controller )	{

	RPDB_DatabaseCursor*		database_cursor = calloc( 1, sizeof( RPDB_DatabaseCursor ) );
	
	if ( parent_database_cursor_controller->runtime_storage_database != NULL )	{
		database_cursor->runtime_identifier =	RPDB_Database_internal_storeRuntimeAddress(	parent_database_cursor_controller->runtime_storage_database,
																																											(void*) database_cursor );
	}
	
	database_cursor->parent_database_cursor_controller = parent_database_cursor_controller;

	//	Make call to instantiate local settings controller
	database_cursor->settings_controller	=	RPDB_DatabaseCursorSettingsController_internal_copyOfSettingsControllerForInstance( RPDB_DatabaseSettingsController_cursorSettingsController( RPDB_Database_settingsController( parent_database_cursor_controller->parent_database ) ) );

	database_cursor->iteration_started	=	0;
	database_cursor->is_open			=	FALSE;
	database_cursor->name				=	NULL;

	return database_cursor;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseCursor_free(	RPDB_DatabaseCursor** database_cursor )	{

	if ( ( *database_cursor )->parent_database_cursor_controller->runtime_storage_database != NULL )	{
		RPDB_Database_internal_freeStoredRuntimeAddress(	( *database_cursor )->parent_database_cursor_controller->runtime_storage_database,
																											( *database_cursor )->runtime_identifier );
	}

	//	close self
	if ( RPDB_DatabaseCursor_isOpen( *database_cursor ) )	{
		RPDB_DatabaseCursor_close( *database_cursor );
	}

	//	free local settings controller
	if ( ( *database_cursor )->settings_controller != NULL )	{
		RPDB_DatabaseCursorSettingsController_free( & ( ( *database_cursor )->settings_controller ) );
	}
	
	//	If we have a name we have to free it
	if ( ( *database_cursor )->name != NULL )	{
		free( ( *database_cursor )->name );
		( *database_cursor )->name	=	NULL;
	}
	
	//	free self
	free( *database_cursor );
	*database_cursor	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_DatabaseCursorSettingsController* RPDB_DatabaseCursor_settingsController(	RPDB_DatabaseCursor* database_cursor )	{
	return database_cursor->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseCursor_parentEnvironment(	RPDB_DatabaseCursor* database_cursor )	{
	return database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseCursor_parentDatabase(	RPDB_DatabaseCursor* database_cursor )	{
	return database_cursor->parent_database_cursor_controller->parent_database;
}

/***************************************
*  parentCursorController  *
***************************************/
RPDB_DatabaseCursorController* RPDB_DatabaseCursor_parentDatabaseCursorController(	RPDB_DatabaseCursor* database_cursor )	{
	return database_cursor->parent_database_cursor_controller;
}

/************
*  open  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
RPDB_DatabaseCursor* RPDB_DatabaseCursor_open( RPDB_DatabaseCursor* database_cursor )	{
	
	int					connection_error	= 0;

	RPDB_Environment*	environment	=	database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;

	DB_TXN*	transaction_id	=	NULL;
	if ( database_cursor->parent_database_cursor_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	RPDB_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	RPDB_DatabaseSettingsController*				database_settings_controller				=	RPDB_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	RPDB_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	RPDB_DatabaseSettingsController_cursorSettingsController( database_settings_controller );
	
	uint32_t	open_flags	=	RPDB_DatabaseCursorSettingsController_internal_openFlags( database_cursor_settings_controller );
	
	RPDB_Database*	parent_database	=	database_cursor->parent_database_cursor_controller->parent_database;
	
	//	Open our BDB database_cursor
	if ( ( connection_error = parent_database->wrapped_bdb_database->cursor(	parent_database->wrapped_bdb_database,
																																						transaction_id,
																																						&( database_cursor->wrapped_bdb_cursor ), 
																																						open_flags ) ) ) {

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ), 
																									connection_error, 
																									"RPDB_DatabaseCursor_open" );
		return NULL;
	}
	
	database_cursor->is_open	=	TRUE;

	return database_cursor;
}

/************
*  isOpen  *
************/

BOOL RPDB_DatabaseCursor_isOpen( RPDB_DatabaseCursor* database_cursor )	{
	return database_cursor->is_open;
}
	
/*************
*  close  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_close.html
RPDB_DatabaseCursor* RPDB_DatabaseCursor_close( RPDB_DatabaseCursor* database_cursor )	{

	int					connection_error	= 0;
	
	if (	RPDB_DatabaseCursor_isOpen( database_cursor )
		&&	( connection_error = database_cursor->wrapped_bdb_cursor->close( database_cursor->wrapped_bdb_cursor ) ) ) {

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ), 
																									connection_error, 
																									"RPDB_DatabaseCursor_close" );
		return NULL;
	}
	
	database_cursor->is_open	=	FALSE;
	
	return database_cursor;
}

/*************************
*  duplicateCursor  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_dup.html
RPDB_DatabaseCursor* RPDB_DatabaseCursor_duplicateCursor( RPDB_DatabaseCursor* database_cursor )	{

	RPDB_DatabaseCursor_internal_ensureOpen( database_cursor );

	int							connection_error	= 0;

	RPDB_DatabaseCursor*		cursor_copy;

	cursor_copy = RPDB_DatabaseCursor_new( database_cursor->parent_database_cursor_controller );

	RPDB_DatabaseSettingsController*				database_settings_controller				=	RPDB_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	RPDB_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	RPDB_DatabaseSettingsController_cursorSettingsController( database_settings_controller );
	
	uint32_t	duplicate_flags	=	RPDB_DatabaseCursorSettingsController_internal_duplicateFlags( database_cursor_settings_controller );

	if ( ( connection_error = database_cursor->wrapped_bdb_cursor->dup(	database_cursor->wrapped_bdb_cursor, 
																																			& cursor_copy->wrapped_bdb_cursor,
																																			duplicate_flags ) ) ) {

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ), 
																									connection_error, 
																									"RPDB_DatabaseCursor_copy" );
		return NULL;
	}

	return cursor_copy;
}

/*******************************************************************************************************************************************************************************************
																	Writing Data
*******************************************************************************************************************************************************************************************/

/************************************
*  writeAsCurrentRecord  *
************************************/

//	DB_CURRENT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeRecordAsCurrentData(	RPDB_DatabaseCursor*	database_cursor, 
																										RPDB_Record*			record )	{

	RPDB_DatabaseCursor_internal_writeRecord(	database_cursor, 
																						DB_CURRENT, 
																						record );
}

/****************************************
*  writeKeyDataPairAsCurrentRecord  *
****************************************/

//	DB_CURRENT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeDataAsCurrent(	RPDB_DatabaseCursor*	database_cursor, 
																							RPDB_Data*				data )	{

	RPDB_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																									DB_CURRENT,
																									NULL,
																									data );
}

/********************************************
*  writeRawKeyDataPairAsCurrentRecord  *
********************************************/

//	DB_CURRENT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeRawDataAsCurrent(	RPDB_DatabaseCursor*	database_cursor, 
																								void*									data_raw,
																								uint32_t							data_size )	{

	RPDB_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																										DB_CURRENT,
																										NULL,
																										0,
																										data_raw,
																										data_size );
}

/****************************************
*  writeAfterCurrentRecord  *
****************************************/

//	DB_AFTER				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeRecordAsDuplicateDataAfterCurrent(	RPDB_DatabaseCursor*		database_cursor, 
																																	RPDB_Record*						record )	{

	RPDB_DatabaseCursor_internal_writeRecord(		database_cursor, 
																							DB_AFTER, 
																							record );
}

/********************************************
*  writeKeyDataPairAfterCurrentRecord  *
********************************************/

//	DB_AFTER				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeDataAsDuplicateAfterCurrent(	RPDB_DatabaseCursor*	database_cursor, 
																														RPDB_Data*				data )	{

	RPDB_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																									DB_AFTER,
																									NULL,
																									data );
}

/************************************************
*  writeRawKeyDataPairAfterCurrentRecord  *
************************************************/

//	DB_AFTER				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeRawDataAsDuplicateAfterCurrent(	RPDB_DatabaseCursor*	database_cursor, 
																															void*									data_raw,
																															uint32_t							data_size )	{

	RPDB_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																										DB_AFTER,
																										NULL,
																										0,
																										data_raw,
																										data_size );
}

/******************************************
*  writeBeforeCurrentRecord  *
******************************************/

//	DB_BEFORE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeRecordAsDuplicateBeforeCurrent(	RPDB_DatabaseCursor*		database_cursor, 
																															RPDB_Record*						record )	{

	RPDB_DatabaseCursor_internal_writeRecord(		database_cursor, 
																							DB_BEFORE, 
																							record );
}

/********************************************
*  writeKeyDataPairBeforeCurrentRecord  *
********************************************/

//	DB_BEFORE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeDataAsDuplicateBeforeCurrent(	RPDB_DatabaseCursor*	database_cursor, 
																														RPDB_Data*						data )	{

	RPDB_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																									DB_BEFORE,
																									NULL,
																									data );
}

/************************************************
*  writeRawKeyDataPairBeforeCurrentRecord  *
************************************************/

//	DB_BEFORE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeRawDataAsDuplicateBeforeCurrent(	RPDB_DatabaseCursor*	database_cursor, 
																																void*									data_raw,
																																uint32_t							data_size )	{

	RPDB_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																										DB_BEFORE,
																										NULL,
																										0,
																										data_raw,
																										data_size );
}


/*********************************
*  writeRecordBeforeAnyDuplicates  *
*********************************/

void RPDB_DatabaseCursor_writeRecord(	RPDB_DatabaseCursor*	database_cursor, 
																			RPDB_Record*							record )	{

	RPDB_DatabaseCursor_writeRecordAfterAnyDuplicates(	database_cursor,
														record );
}

/*****************************************
*  writeKeyDataPair  *
*****************************************/

void RPDB_DatabaseCursor_writeKeyDataPair(		RPDB_DatabaseCursor*	database_cursor, 
																							RPDB_Key*				key,
																							RPDB_Data*				data )	{

	RPDB_DatabaseCursor_writeKeyDataPairAfterAnyDuplicates(	database_cursor,
																													key,
																													data	);
}
	
/*****************************************
*  writeRawKeyDataPair  *
*****************************************/

void RPDB_DatabaseCursor_writeRawKeyDataPair(	RPDB_DatabaseCursor*	database_cursor, 
																							void*									key_raw,
																							uint32_t							key_size,
																							void*									data_raw,
																							uint32_t							data_size )	{
	
	RPDB_DatabaseCursor_writeRawKeyDataPairAfterAnyDuplicates(	database_cursor,
																															key_raw,
																															key_size,
																															data_raw,
																															data_size	);
}

/*********************************
*  writeAsFirstRecord  *
*********************************/

//	If the key already exists in the database and no duplicate sort function has been specified, 
//	the inserted data item is added as the first of the data items for that key.
//	If duplicate sort function has been specified, it will be used rather than inserting before duplicates. 
//	DB_KEYFIRST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeRecordBeforeAnyDuplicates(	RPDB_DatabaseCursor*	database_cursor, 
																													RPDB_Record*							record )	{

	RPDB_DatabaseCursor_internal_writeRecord(		database_cursor, 
																							DB_KEYFIRST, 
																							record );
}

/*****************************************
*  writeKeyDataPairAsFirstRecord  *
*****************************************/

//	If the key already exists in the database and no duplicate sort function has been specified, 
//	the inserted data item is added as the first of the data items for that key.
//	If duplicate sort function has been specified, it will be used rather than inserting before duplicates. 
//	DB_KEYFIRST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeKeyDataPairBeforeAnyDuplicates(		RPDB_DatabaseCursor*	database_cursor, 
																																RPDB_Key*							key,
																																RPDB_Data*						data )	{

	RPDB_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																									DB_KEYFIRST,
																									key,
																									data );
}

/*****************************************
*  writeRawKeyDataPairAsFirstRecord  *
*****************************************/

//	If the key already exists in the database and no duplicate sort function has been specified, 
//	the inserted data item is added as the first of the data items for that key.
//	If duplicate sort function has been specified, it will be used rather than inserting before duplicates. 
//	DB_KEYFIRST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeRawKeyDataPairBeforeAnyDuplicates(	RPDB_DatabaseCursor*	database_cursor, 
																																	void*									key_raw,
																																	uint32_t							key_size,
																																	void*									data_raw,
																																	uint32_t							data_size )	{

	RPDB_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																										DB_KEYFIRST,
																										key_raw,
																										key_size,
																										data_raw,
																										data_size );
}

/********************************
*  writeDataAsLastRecord  *
********************************/

//	If the key already exists in the database and no duplicate sort function has been specified, 
//	the inserted data item is added as the first of the data items for that key.
//	If duplicate sort function has been specified, it will be used rather than inserting after duplicates. 
//	DB_KEYLAST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeRecordAfterAnyDuplicates(	RPDB_DatabaseCursor*	database_cursor, 
																												RPDB_Record*							record )	{

	RPDB_DatabaseCursor_internal_writeRecord(	database_cursor, 
																						DB_KEYLAST, 
																						record );
}

/****************************************
*  writeKeyDataPairAsLastRecord  *
****************************************/

//	If the key already exists in the database and no duplicate sort function has been specified, 
//	the inserted data item is added as the first of the data items for that key.
//	If duplicate sort function has been specified, it will be used rather than inserting after duplicates. 
//	DB_KEYLAST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeKeyDataPairAfterAnyDuplicates(	RPDB_DatabaseCursor*	database_cursor, 
																															RPDB_Key*							key,
																															RPDB_Data*						data )	{
	
	RPDB_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																									DB_KEYLAST,
																									key,
																									data );
}

/********************************************
*  writeRawKeyDataPairAsLastRecord  *
********************************************/

//	If the key already exists in the database and no duplicate sort function has been specified, 
//	the inserted data item is added as the first of the data items for that key.
//	If duplicate sort function has been specified, it will be used rather than inserting after duplicates. 
//	DB_KEYLAST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeRawKeyDataPairAfterAnyDuplicates(	RPDB_DatabaseCursor*	database_cursor, 
																																void*									key_raw,
																																uint32_t							key_size,
																																void*									data_raw,
																																uint32_t							data_size )	{
	
	RPDB_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																										DB_KEYLAST,
																										key_raw,
																										key_size,
																										data_raw,
																										data_size );
}


/**************************************
*  writeOnlyIfNonExisting  *
**************************************/

//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeRecordOnlyIfNotInDatabase(	RPDB_DatabaseCursor*		database_cursor, 
																													RPDB_Record*						record )	{

	RPDB_DatabaseCursor_internal_writeRecord(	database_cursor, 
																						DB_NODUPDATA,
																						record );
}

/******************************************
*  writeKeyDataPairOnlyIfNonExisting  *
******************************************/

//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeKeyDataPairOnlyIfNotInDatabase(	RPDB_DatabaseCursor*	database_cursor, 
																															RPDB_Key*							key,
																															RPDB_Data*						data )	{

	RPDB_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																									DB_NODUPDATA,
																									key,
																									data );
}

/**********************************************
*  writeRawKeyDataPairOnlyIfNonExisting  *
**********************************************/

//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPDB_DatabaseCursor_writeRawKeyDataPairOnlyIfNotInDatabase(	RPDB_DatabaseCursor*	database_cursor, 
																																	void*									key_raw,
																																	uint32_t							key_size,
																																	void*									data_raw,
																																	uint32_t							data_size )	{

	RPDB_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																										DB_NODUPDATA,
																										key_raw,
																										key_size,
																										data_raw,
																										data_size );
}

/*******************************************************************************************************************************************************************************************
																	Initial Retrieval
*******************************************************************************************************************************************************************************************/

/*****************************
*  recordExistsForKey  *
*****************************/

BOOL RPDB_DatabaseCursor_keyExists(	RPDB_DatabaseCursor*		database_cursor, 
																		RPDB_Key*								key )	{

	RPDB_Record*	record	=	RPDB_Record_internal_newFromKeyData(	database_cursor->parent_database_cursor_controller->parent_database,
																																key,
																																NULL	);

	record = 	RPDB_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																													DB_SET, 
																													record );
	
	int	exists_in_database	=	RPDB_Record_existsInDatabase( record );

	if ( exists_in_database == DB_NOTFOUND )	{
		return FALSE;
	}
	else if ( exists_in_database == DB_KEYEMPTY )	{
		return RPDB_EMPTY_KEY_EXISTS;
	}
	return TRUE;
}

/*****************************
*  recordExistsForRawKey  *
*****************************/

BOOL RPDB_DatabaseCursor_rawKeyExists(	RPDB_DatabaseCursor*		database_cursor, 
																				void*										key_raw,
																				uint32_t								key_size )	{

	RPDB_Key*	key	=	RPDB_Key_new( NULL );
	
	key->wrapped_bdb_dbt->data	= key_raw;
	key->wrapped_bdb_dbt->size	= key_size;

	return RPDB_DatabaseCursor_keyExists(	database_cursor,
																				key );
}

/*************************
*  retrieveRecord  *
*************************/

RPDB_Record* RPDB_DatabaseCursor_retrieveRecord(	RPDB_DatabaseCursor*		database_cursor, 
																									RPDB_Record*						record )	{

	return RPDB_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																											DB_SET, 
																											record );
}

/*****************************
*  retrieveKey  *
*****************************/

RPDB_Record* RPDB_DatabaseCursor_retrieveKey(	RPDB_DatabaseCursor*		database_cursor, 
																							RPDB_Key*								key_data )	{

	RPDB_Record*	record	=	RPDB_Record_new( NULL );
	
	RPDB_Record_setKey(	record,
											key_data );
	
	if (		RPDB_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																												DB_SET, 
																												record )->result == FALSE
			||	record->result == DB_KEYEMPTY )	{
		RPDB_Record_free( & record );
	}
	return record;
}

/********************************
*  retrieveRawKey  *
********************************/

//	DB_SET				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Move the database_cursor to specified location
RPDB_Record* RPDB_DatabaseCursor_retrieveRawKey(	RPDB_DatabaseCursor*		database_cursor, 
																									void*										key_raw,
																									uint32_t								key_size )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_SET, 
																															key_raw,
																															key_size, 
																															NULL,
																															0 );
}

/*********************************************
*  retrieveMatchingKeyDataPair  *
*********************************************/

RPDB_Record* RPDB_DatabaseCursor_retrieveMatchingKeyDataPair(	RPDB_DatabaseCursor*		database_cursor, 
																															RPDB_Key*								key_data,
																															RPDB_Data*							data )	{

	RPDB_Record*	record	=	RPDB_Record_new( NULL );
	
	RPDB_Record_setKey(	record,
											key_data );
	RPDB_Record_setData(	record,
												data );

	if (		RPDB_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																												DB_GET_BOTH, 
																												record )->result == FALSE
			||	record->result == DB_KEYEMPTY )	{
		RPDB_Record_free( & record );
	}
	return record;
}

/************************************************
*  retrieveMatchingRawKeyDataPair  *
************************************************/

//	DB_GET_BOTH				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	We need to add key specification here
RPDB_Record* RPDB_DatabaseCursor_retrieveMatchingRawKeyDataPair(	RPDB_DatabaseCursor*		database_cursor,
																																	void*										key_raw,
																																	uint32_t								key_size,
																																	void*										data_raw,
																																	uint32_t								data_size )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_GET_BOTH, 
																															key_raw,
																															key_size, 
																															data_raw,
																															data_size );
}

/**********************************
*  retrieveRecordWithNumber  *
**********************************/

//	DB_SET_RECNO			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Must be Btree created with Recnum
RPDB_Record* RPDB_DatabaseCursor_retrieveRecordWithNumber(	RPDB_DatabaseCursor* 	database_cursor,
																														db_recno_t*									record_id )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_SET_RECNO,
																															record_id, 
																															sizeof( uint32_t ),
																															NULL,
																															0 );
}

/****************************************
*  retrieveRecordWithNumberInKey  *
****************************************/

RPDB_Record* RPDB_DatabaseCursor_retrieveRecordWithNumberAsKey(	RPDB_DatabaseCursor* 	database_cursor,
																																RPDB_Key*				key_with_record_number )	{

	//	We should probably make sure here that record ID is an int

	RPDB_Record*	record	=	RPDB_Record_new( NULL );
	
	RPDB_Record_setKey(	record,
											key_with_record_number );

	if (		RPDB_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																												DB_SET_RECNO, 
																												record )->result == FALSE
			||	record->result == DB_KEYEMPTY )	{
		RPDB_Record_free( & record );
	}
	return record;
}

/*****************************************
*  retrievePartialRawKey  *
*****************************************/

RPDB_Record* RPDB_DatabaseCursor_retrievePartialRawKey(	RPDB_DatabaseCursor*		database_cursor,
																												void*										key_raw,
																												uint32_t								key_size )	{

	//	Make sure type is Btree
	
	//	Make sure was created with DB_RECNUM

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_SET_RANGE, 
																															key_raw, 
																															key_size,
																															NULL,
																															0 );
}

/****************************************
*  retrievePartialObject  *
****************************************/

//	DB_SET_RANGE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Must be Btree and it must have been created with the DB_RECNUM flag.
//	Permits partial key matches and range searches by returning the smallest item matching or including the key
RPDB_Record* RPDB_DatabaseCursor_retrievePartialData(	RPDB_DatabaseCursor*		database_cursor,
																											RPDB_Data*							data )	{
	
	RPDB_Record*	record	=	RPDB_Record_new( NULL );
	
	RPDB_Record_setData(	record,
												data );
	
	if (		RPDB_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																												DB_SET_RANGE, 
																												record )->result == FALSE 
			||	record->result == DB_KEYEMPTY )	{
		RPDB_Record_free( & record );
	}
	return record;
}

/**************************************
*  retrievePartialData  *
**************************************/

//	DB_GET_BOTH_RANGE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Permits partial data matches and range searches by returning the smallest item matching or including the data
RPDB_Record* RPDB_DatabaseCursor_retrievePartialKeyDataPair(	RPDB_DatabaseCursor*		database_cursor,
																															RPDB_Key*								partial_key,
																															RPDB_Data*							partial_data )	{

	RPDB_Record*	record	=	RPDB_Record_new( NULL );
	
	RPDB_Record_setKey(	record,
											partial_key);
	RPDB_Record_setData(	record,
												partial_data);
	
	if (		RPDB_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																												DB_GET_BOTH_RANGE, 
																												record )->result == FALSE
			||	record->result == DB_KEYEMPTY )	{
		RPDB_Record_free( & record );
	}
	return record;
}

/**************************************************
*  retrieveRawKeyPartialDataPair  *
**************************************************/

RPDB_Record* RPDB_DatabaseCursor_retrieveRawKeyPartialDataPair(	RPDB_DatabaseCursor*		database_cursor,
																																void*										key_raw,
																																uint32_t								key_size,
																																void*										data_raw,
																																uint32_t								data_size )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_GET_BOTH_RANGE, 
																															key_raw, 
																															key_size,
																															data_raw,
																															data_size );
}

/*******************************************************************************************************************************************************************************************
																Relative to Current Key
*******************************************************************************************************************************************************************************************/

/****************
*  current  *
****************/

//	DB_CURRENT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPDB_Record* RPDB_DatabaseCursor_retrieveCurrent( RPDB_DatabaseCursor* database_cursor )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_CURRENT, 
																															NULL,
																															0,
																															NULL,
																															0 );
}

/****************
*  setToFirst  *
****************/

//	DB_FIRST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL RPDB_DatabaseCursor_setToFirst( RPDB_DatabaseCursor* database_cursor )	{
	RPDB_Record*	first_record	=	RPDB_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	
	RPDB_DatabaseCursor_internal_retrieveFirst(	database_cursor,
																							first_record );
	
	BOOL has_record	=	FALSE;
	if ( first_record->result )	{
		has_record	=	TRUE;
	}

	RPDB_Record_free( & first_record );

	return has_record;
}

/****************
*  first  *
****************/

//	DB_FIRST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPDB_Record* RPDB_DatabaseCursor_retrieveFirst( RPDB_DatabaseCursor* database_cursor )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_FIRST, 
																															NULL,
																															0, 
																															NULL,
																															0 );
}

/**************
*  last  *
**************/

//	DB_LAST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPDB_Record* RPDB_DatabaseCursor_retrieveLast( RPDB_DatabaseCursor* database_cursor )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor,
																															DB_LAST,
																															NULL, 
																															0,
																															NULL,
																															0 );
}

/*****************
*  retrieveNext  *
*****************/

//	DB_NEXT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPDB_Record* RPDB_DatabaseCursor_retrieveNext( RPDB_DatabaseCursor* database_cursor )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_NEXT, 
																															NULL, 
																															0,
																															NULL,
																															0 );
}		

/************************
*  nextDuplicate  *
************************/

//	DB_NEXT_DUP			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPDB_Record* RPDB_DatabaseCursor_retrieveNextDuplicate( RPDB_DatabaseCursor* database_cursor )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_NEXT_DUP, 
																															NULL, 
																															0,
																															NULL,
																															0 );
}

/*************************
*  nextNonDuplicate  *
*************************/

//	DB_NEXT_NODUP		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPDB_Record* RPDB_DatabaseCursor_retrieveNextNonDuplicate( RPDB_DatabaseCursor* database_cursor )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_NEXT_NODUP, 
																															NULL, 
																															0,
																															NULL,
																															0 );
}

/******************
*  previous  *
******************/

//	DB_PREV				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPDB_Record* RPDB_DatabaseCursor_retrievePrevious( RPDB_DatabaseCursor* database_cursor )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_PREV, 
																															NULL, 
																															0,
																															NULL,
																															0 );
}

/****************************
*  previousDuplicate  *
****************************/

//	DB_PREV_DUP				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPDB_Record* RPDB_DatabaseCursor_retrievePreviousDuplicate( RPDB_DatabaseCursor* database_cursor )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_PREV_DUP, 
																															NULL, 
																															0,
																															NULL,
																															0 );
}

/******************************
*  previousNonDuplicate  *
******************************/

//	DB_PREV_NODUP				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPDB_Record* RPDB_DatabaseCursor_retrievePreviousNonDuplicate( RPDB_DatabaseCursor* database_cursor )	{

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_PREV_NODUP, 
																															NULL, 
																															0,
																															NULL,
																															0 );
}

/**************************************
*  retrieveCurrentRecordNumber  *
**************************************/

//	DB_GET_RECNO			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Must be Btree created with Recnum
RPDB_Record* RPDB_DatabaseCursor_retrieveCurrentRecordNumber( RPDB_DatabaseCursor* database_cursor )	{

	RPDB_DatabaseCursor_internal_ensureOpen( database_cursor );

	RPDB_DatabaseSettingsController*			database_settings_controller			=	RPDB_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	RPDB_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPDB_DatabaseSettingsController_typeSettingsController( database_settings_controller );
	DBTYPE																database_type											=	RPDB_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

	//	Make sure we have DB_RECNO
	if ( database_type != DB_RECNO )	{

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ),
																									RP_ERROR_NOT_DB_QUEUE_OR_DB_RECNO, 
																									"RPDB_Database_append" );
	}

	return RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_GET_RECNO, 
																															NULL, 
																															0,
																															NULL,
																															0 );
}

/*********************************
*  recordCountForCurrentKey  *
*********************************/

//	Count data items for current key
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_count.html
db_recno_t RPDB_DatabaseCursor_countDuplicatesForCurrentKey( RPDB_DatabaseCursor* database_cursor )	{

	RPDB_DatabaseCursor_internal_ensureOpen( database_cursor );

	db_recno_t			number_data_items_for_cursor;		

	RPDB_Environment*						environment	= database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;

	RPDB_DatabaseSettingsController*				database_settings_controller				=	RPDB_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	RPDB_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	RPDB_DatabaseSettingsController_cursorSettingsController( database_settings_controller );
	
	int	count_data_items_flags	=	RPDB_DatabaseCursorSettingsController_internal_countDataItemsFlags( database_cursor_settings_controller );

	int	connection_error	= 0;
	if ( ( connection_error = database_cursor->wrapped_bdb_cursor->count(	database_cursor->wrapped_bdb_cursor, 
																																				& number_data_items_for_cursor, 
																																				count_data_items_flags ) ) ) {

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ), 
																									connection_error, 
																									"RPDB_DatabaseCursor_itemCountForCurrentKey" );
	}

	return number_data_items_for_cursor;
}

/************************
*  resetIteration  *
************************/

void RPDB_DatabaseCursor_resetIteration( RPDB_DatabaseCursor* database_cursor )	{
	database_cursor->iteration_started	=	FALSE;
}

/************************
*  resetIteration  *
************************/

void RPDB_DatabaseCursor_resetDuplicateIteration( RPDB_DatabaseCursor* database_cursor )	{
	database_cursor->duplicate_iteration_started	=	FALSE;
}
	
/****************************
*  iterate  *
****************************/

// if we have duplicates for db, each iterates duplicates
// if we have no duplicates for db, each iterates records
RPDB_Record* RPDB_DatabaseCursor_iterate(	RPDB_DatabaseCursor*	database_cursor,
																					RPDB_Record*					record )	{

	RPDB_DatabaseCursor_internal_ensureOpen( database_cursor );
	
	//	if we have a null record, instantiate it
	//	caller responsible for freeing
	if ( record == NULL )	{
		record = RPDB_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}
	
	//	Args:
	//	0 args: intelligent iteration
	//	1 arg: if true - force iterate all 

	if ( database_cursor->iteration_started == FALSE )	{
		RPDB_DatabaseCursor_internal_retrieveCurrent(	database_cursor,
																									record );
		database_cursor->iteration_started = TRUE;
	}
	else {
	
		RPDB_DatabaseCursor_internal_retrieveNext(	database_cursor,
																								record );
	}
	
	if ( record->result == FALSE )	{
		RPDB_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return RPDB_DatabaseCursor_iterate(	database_cursor,
																				record );
	}

	return record;
}

/****************************
*  iterateDuplicates  *
****************************/

//	iterates all records with one or more duplicates
RPDB_Record* RPDB_DatabaseCursor_iterateDuplicates( RPDB_DatabaseCursor*	database_cursor,
																										RPDB_Record*					record  )	{
	
	RPDB_DatabaseCursor_internal_ensureOpen( database_cursor );

	//	if we have a null record, instantiate it
	//	caller responsible for freeing
	if ( record == NULL )	{
		record = RPDB_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}

	if ( database_cursor->duplicate_iteration_started == FALSE )	{
		RPDB_DatabaseCursor_internal_retrieveCurrent( database_cursor,
																									record );
		database_cursor->duplicate_iteration_started = TRUE;
	}
	else {
		RPDB_DatabaseCursor_internal_retrieveNextDuplicate( database_cursor,
																												record );		
	}
	
	if ( record->result == FALSE )	{
		RPDB_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return RPDB_DatabaseCursor_iterateDuplicates(	database_cursor,
																									record );
	}
	
	return record;
}

/****************************
*  iterateNonDuplicates  *
****************************/

//	iterates all records without duplicates
RPDB_Record* RPDB_DatabaseCursor_iterateKeys( RPDB_DatabaseCursor* database_cursor,
																							RPDB_Record*					record  )	{
	
	RPDB_DatabaseCursor_internal_ensureOpen( database_cursor );

	//	if we have a null record, instantiate it
	//	caller responsible for freeing
	if ( record == NULL )	{
		record = RPDB_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}

	if ( database_cursor->iteration_started == FALSE )	{
		RPDB_DatabaseCursor_internal_retrieveCurrent( database_cursor,
																									record );
		database_cursor->iteration_started	=	TRUE;
	}
	else {
		RPDB_DatabaseCursor_internal_retrieveNextNonDuplicate(	database_cursor,
																														record );		
	}
	
	if ( record->result == FALSE )	{
		RPDB_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return RPDB_DatabaseCursor_iterateKeys(	database_cursor,
																						record );
	}
	
	return record;
}

/*******************************************************************************************************************************************************************************************
																	Deleting Data
*******************************************************************************************************************************************************************************************/

/*****************************
*  deleteCurrentRecord  *
*****************************/

//	Deletes key/pair to which database_cursor refers
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_del.html
RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteCurrentRecord( RPDB_DatabaseCursor*	database_cursor )	{

	int					connection_error	= 0;

	RPDB_DatabaseSettingsController*									database_settings_controller										=	RPDB_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	RPDB_DatabaseCursorSettingsController*						database_cursor_settings_controller							=	RPDB_DatabaseSettingsController_cursorSettingsController( database_settings_controller );
	RPDB_DatabaseCursorReadWriteSettingsController*		database_cursor_read_write_settings_controller	=	RPDB_DatabaseCursorSettingsController_readWriteSettingsController( database_cursor_settings_controller );
	
	uint32_t		flags	=	RPDB_DatabaseCursorReadWriteSettingsController_internal_deleteFlags( database_cursor_read_write_settings_controller );
	
	if ( ( connection_error = database_cursor->wrapped_bdb_cursor->del(	database_cursor->wrapped_bdb_cursor, 
																																			flags ) ) ) {

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ), 
																									connection_error, 
																									"RPDB_DatabaseCursor_delete" );
		return NULL;
	}
	
	return database_cursor;
}

/*****************************
*  deleteRecordWithKey  *
*****************************/

RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteKey(	RPDB_DatabaseCursor*		database_cursor,
																										RPDB_Key*								key	)	{
	
	//	Set current record to key/data pair
	RPDB_DatabaseCursor_retrieveKey(	database_cursor,
																		key );
	
	//	Delete current record
	RPDB_DatabaseCursor_deleteCurrentRecord( database_cursor );
	
	return database_cursor;
}

/*****************************
*  deleteRecordWithRawKey  *
*****************************/

RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteRawKey(	RPDB_DatabaseCursor*	database_cursor,
																												void*									key_raw,
																												uint32_t							key_size )	{
	RPDB_Key*	key	=	RPDB_Key_new( NULL );
	RPDB_Key_setKeyData(	key,
												key_raw,
												key_size );
							
	RPDB_DatabaseCursor_deleteKey(	database_cursor,
																	key );
	return database_cursor;
}

/************************************
*  deleteRecordWithKeyDataPair  *
************************************/

RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteKeyDataPair(	RPDB_DatabaseCursor*	database_cursor,
																														RPDB_Key*							key,
																														RPDB_Data*						data	)	{
	
	//	Set current record to key/data pair
	RPDB_DatabaseCursor_retrieveMatchingKeyDataPair(	database_cursor,
																										key,
																										data );
	
	//	Delete current record
	RPDB_DatabaseCursor_deleteCurrentRecord( database_cursor );
	
	return database_cursor;
}

/*************************************
*  deleteRecordWithRawKeyDataPair  *
*************************************/

RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteRawKeyDataPair(	RPDB_DatabaseCursor*	database_cursor,
																																void*									key_raw,
																																uint32_t							key_size,
																																void*									data_raw,
																																uint32_t							data_size	)	{

	RPDB_Record*	record	=	RPDB_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	RPDB_Record_setKeyFromRawKey(	record,
																key_raw,
																key_size );
	RPDB_Record_setDataFromRawData(	record,
																	data_raw,
																	data_size );
	RPDB_DatabaseCursor_deleteKeyDataPair(	database_cursor,
																					record->key,
																					record->data );
	return database_cursor;
}

/******************************
*  deleteRecordWithNumber  *
******************************/

RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteRecordNumber(	RPDB_DatabaseCursor*	database_cursor,
																															db_recno_t*				record_number	)	{
	
	//	Set current record to record number
	RPDB_DatabaseCursor_retrieveRawKey( database_cursor ,
																			record_number,
																			sizeof( uint32_t ) );
	
	//	Delete current record
	return RPDB_DatabaseCursor_deleteCurrentRecord( database_cursor );
}

/********************
*  deleteRecord  *
********************/

RPDB_DatabaseCursor* RPDB_DatabaseCursor_deleteRecord(	RPDB_DatabaseCursor*	database_cursor,
 															RPDB_Record*			record	)	{
	
	//	Set current record to data
	RPDB_DatabaseCursor_retrieveRecord( database_cursor ,
																			record );
	
	//	Delete current record
	return RPDB_DatabaseCursor_deleteCurrentRecord( database_cursor );
}


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Write Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************************
*  ensureInitialized  *
***********************/

void RPDB_DatabaseCursor_internal_ensureOpen( RPDB_DatabaseCursor* database_cursor )	{
	
	if ( ! RPDB_DatabaseCursor_isOpen( database_cursor ) )	{
		RPDB_DatabaseCursor_open( database_cursor );
	}
}

/*******************
*  writeData  *
*******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
RPDB_Record* RPDB_DatabaseCursor_internal_writeRecord(	RPDB_DatabaseCursor*	database_cursor, 
															uint32_t				flags,
															RPDB_Record*			record )	{

	RPDB_DatabaseCursor_internal_ensureOpen( database_cursor );

	int	connection_error	= 0;

	if ( ( connection_error = database_cursor->wrapped_bdb_cursor->put(	database_cursor->wrapped_bdb_cursor, 
																																			record->key->wrapped_bdb_dbt, 
																																			record->data->wrapped_bdb_dbt, 
																																			flags ) ) ) {

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ), 
																									connection_error, 
																									"RPDB_DatabaseCursor_internal_write" );
	}
	return record;
}

/**************************
*  writeKeyDataPair  *
**************************/

RPDB_Record* RPDB_DatabaseCursor_internal_writeKeyDataPair(	RPDB_DatabaseCursor*	database_cursor, 
																														uint32_t							flags,
																														RPDB_Key*							key,
																														RPDB_Data*						data )	{

	RPDB_Record*				record			= RPDB_Record_internal_newFromKeyData(	database_cursor->parent_database_cursor_controller->parent_database,
																																					key,
																																					data	);

	return RPDB_DatabaseCursor_internal_writeRecord(	database_cursor,
																										flags,
																										record );
}

/******************************
*  writeRawKeyDataPair  *
******************************/

RPDB_Record* RPDB_DatabaseCursor_internal_writeRawKeyDataPair(	RPDB_DatabaseCursor*	database_cursor, 
																																uint32_t							flags,
																																void*									key,
																																uint32_t							key_size,
																																void*									data,
																																uint32_t							data_size )	{

	RPDB_Record*				record			= RPDB_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	
	record->key->wrapped_bdb_dbt->data	= key;
	record->key->wrapped_bdb_dbt->size	= key_size;
	record->data->wrapped_bdb_dbt->data			= data;
	record->data->wrapped_bdb_dbt->size			= data_size;
	
	return 	RPDB_DatabaseCursor_internal_writeRecord(	database_cursor,
																										flags,
																										record );
}


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Retrieve Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/**********************************
*  retrieveRawKeyDataPair  *
**********************************/

//	Retrieves data using data->keyData->data as the key and copying data into data->data->data
//	The only difference between get and pget, so far as I can tell, is that pget also returns the primary key from the primary database
//	pget should never be used on a primary database
RPDB_Record* RPDB_DatabaseCursor_internal_retrieveRawKeyDataPair(	RPDB_DatabaseCursor*		database_cursor, 
																																	uint32_t								flag, 
																																	void*										key,
																																	uint32_t								key_size,
																																	void*										data,
																																	uint32_t								data_size )	{

	RPDB_Record*				record				= RPDB_Record_new( database_cursor->parent_database_cursor_controller->parent_database );

	if ( key != NULL )	{
		record->key->wrapped_bdb_dbt->data = key;
		record->key->wrapped_bdb_dbt->size = key_size;
	}
		
	//	If we have data we're using to retrieve, load it into the DBT
	if ( data != NULL )	{
		
		record->data->wrapped_bdb_dbt->data = data;
		record->data->wrapped_bdb_dbt->size = data_size;
		
	}

	return RPDB_DatabaseCursor_internal_retrieveRecord(	database_cursor,
																											flag,
																											record );
}

/**************************
*  retrieveRecord  *
**************************/

RPDB_Record* RPDB_DatabaseCursor_internal_retrieveKeyDataPair(	RPDB_DatabaseCursor*		database_cursor, 
																																uint32_t								flags, 
																																RPDB_Key*								key,
																																RPDB_Data*							data	)	{

	RPDB_Record*	record	=	RPDB_Record_internal_newFromKeyData(	database_cursor->parent_database_cursor_controller->parent_database,
																																key,
																																data );
	
	return RPDB_DatabaseCursor_internal_retrieveRecord(	database_cursor,
																											flags,
																											record );
}

/**************************
*  retrieveRecord  *
**************************/

RPDB_Record* RPDB_DatabaseCursor_internal_retrieveRecord(	RPDB_DatabaseCursor*		database_cursor, 
																													uint32_t								flags, 
																													RPDB_Record*						record)	{

	RPDB_DatabaseCursor_internal_ensureOpen( database_cursor );

	RPDB_Environment*	environment	= database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
	
	//	We have a flag describing what type of cursor operation we are executing; we need to add in flags
	//	that might apply to all situations.
	flags	|=	RPDB_DatabaseCursorReadWriteSettingsController_internal_retrieveFlags(	RPDB_DatabaseCursorSettingsController_readWriteSettingsController( RPDB_DatabaseSettingsController_cursorSettingsController( RPDB_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database ) ) ) );

	int		connection_error	= 0;

	//	If we have a secondary database we are using a secondary key and retrieving a primary key/data pair
	if ( RPDB_Database_isSecondary( database_cursor->parent_database_cursor_controller->parent_database ) )	{

		//	Get data via secondary key or throw error
		if ( ( connection_error = database_cursor->wrapped_bdb_cursor->pget(	database_cursor->wrapped_bdb_cursor, 
																																					record->key->wrapped_bdb_dbt, 
																																					record->primary_key->wrapped_bdb_dbt, 
																																					record->data->wrapped_bdb_dbt, 
																																					flags ) ) ) {

			//	If we don't have a record
			//	Or if our record used to exist but doesn't now
			if (	connection_error == DB_NOTFOUND )	{				
				record->result = FALSE;
			}
			else if ( connection_error == DB_KEYEMPTY )	{
				record->result = DB_KEYEMPTY;
			}
			//	Otherwise it really is an error
			else	{

				RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ), 
																											connection_error, 
																											"RPDB_DatabaseCursor_internal_retrieveRecord" );
			
				return NULL;
			}
		}
		else {
			record->result = TRUE;
		}

	}
	//	Otherwise we are retrieving a primary key/data pair
	else	{

		if ( ( connection_error = database_cursor->wrapped_bdb_cursor->get(	database_cursor->wrapped_bdb_cursor, 
																																				record->key->wrapped_bdb_dbt, 
																																				record->data->wrapped_bdb_dbt, 
																																				flags ) ) ) {

			//	If we don't have a record
			//	Or if our record used to exist but doesn't now
			if (	connection_error == DB_NOTFOUND )	{				
				record->result = FALSE;
			}
			else if ( connection_error == DB_KEYEMPTY )	{
				record->result = DB_KEYEMPTY;
			}
			//	Otherwise it really is an error
			else	{

				RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ), 
																											connection_error, 
																											"RPDB_DatabaseCursor_internal_retrieveRecord" );
				return NULL;
			}
		}
		else {
			record->result = TRUE;
		}
	}
	
	return record;
}

/********************
*  retrieveFirst  *
********************/

RPDB_Record* RPDB_DatabaseCursor_internal_retrieveFirst(	RPDB_DatabaseCursor*	cursor,
																													RPDB_Record*					record )	{
	
	return RPDB_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_FIRST,
																											record );
}

/********************
*  retrieveCurrent  *
********************/

RPDB_Record* RPDB_DatabaseCursor_internal_retrieveCurrent(	RPDB_DatabaseCursor*	cursor,
																														RPDB_Record*					record )	{
	
	return RPDB_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_CURRENT,
																											record );
}

/*****************
*  retrieveNext  *
*****************/

RPDB_Record* RPDB_DatabaseCursor_internal_retrieveNext(	RPDB_DatabaseCursor*	cursor,
																												RPDB_Record*					record )	{

	return RPDB_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_NEXT,
																											record );
}

/**************************
*  retrieveNextDuplicate  *
**************************/

RPDB_Record* RPDB_DatabaseCursor_internal_retrieveNextDuplicate(	RPDB_DatabaseCursor*	cursor,
																																	RPDB_Record*					record )	{

	return RPDB_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_NEXT_DUP,
																											record );
}

/*****************************
*  retrieveNextNonDuplicate  *
*****************************/

RPDB_Record* RPDB_DatabaseCursor_internal_retrieveNextNonDuplicate(	RPDB_DatabaseCursor*	cursor,
																																		RPDB_Record*					record )	{

	return RPDB_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_NEXT_NODUP,
																											record );
}

