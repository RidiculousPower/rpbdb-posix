/*
 *		RPbdb::DatabaseController::Database::DatabaseCursorController::DatabaseCursor
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseCursor.h"
#include "DatabaseCursor_internal.h"

#include "Environment.h"

#include "ErrorController.h"

#include "Database.h"
#include "Database_internal.h"

#include "Record.h"
#include "Record_internal.h"
#include "Key.h"
#include "Data.h"

#include "TransactionController.h"
#include "TransactionController_internal.h"

#include "DatabaseSettingsController.h"
#include "DatabaseCursorSettingsController.h"
#include "DatabaseSettingsController.h"
#include "DatabaseTypeSettingsController.h"
#include "DatabaseTypeBtreeSettingsController.h"
#include "DatabaseRecordSettingsController.h"
#include "DatabaseRecordReadWriteSettingsController.h"

#include "DatabaseCursorSettingsController_internal.h"
#include "DatabaseCursorReadWriteSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_new( RPbdb_DatabaseCursorController* parent_database_cursor_controller )	{

	RPbdb_DatabaseCursor*		database_cursor = calloc( 1, sizeof( RPbdb_DatabaseCursor ) );
	
	if ( parent_database_cursor_controller->runtime_storage_database != NULL )	{
		database_cursor->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_database_cursor_controller->runtime_storage_database,
																																											(void*) database_cursor );
	}
	
	database_cursor->parent_database_cursor_controller = parent_database_cursor_controller;

	RPbdb_Database*													parent_database												=	parent_database_cursor_controller->parent_database;
	RPbdb_DatabaseSettingsController*				database_settings_controller					=	RPbdb_Database_settingsController( parent_database );
	RPbdb_DatabaseCursorSettingsController*	database_cursor_settings_controller		=	RPbdb_DatabaseSettingsController_cursorSettingsController( database_settings_controller );

	//	Make call to instantiate local settings controller
	database_cursor->settings_controller	=	RPbdb_DatabaseCursorSettingsController_internal_copyOfSettingsControllerForInstance( database_cursor_settings_controller );

	database_cursor->iteration_started	=	0;
	database_cursor->is_open						=	FALSE;
	database_cursor->name								=	NULL;
	database_cursor->retrieved_record   =	FALSE;

	return database_cursor;
}

/***************************
*  free  *
***************************/

void RPbdb_DatabaseCursor_free(	RPbdb_DatabaseCursor** database_cursor )	{

	if ( ( *database_cursor )->parent_database_cursor_controller->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *database_cursor )->parent_database_cursor_controller->runtime_storage_database,
																											( *database_cursor )->runtime_identifier );
	}

	RPbdb_DatabaseCursor_internal_freeFromRuntimeStorage( database_cursor );
}

/***************************
*  freeFromRuntimeStorage  *
***************************/

void RPbdb_DatabaseCursor_internal_freeFromRuntimeStorage(	RPbdb_DatabaseCursor** database_cursor )	{

	//	close self
	if ( RPbdb_DatabaseCursor_isOpen( *database_cursor ) )	{
		RPbdb_DatabaseCursor_close( *database_cursor );
	}

	//	free local settings controller
	if ( ( *database_cursor )->settings_controller != NULL )	{
		RPbdb_DatabaseCursorSettingsController_free( & ( ( *database_cursor )->settings_controller ) );
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
RPbdb_DatabaseCursorSettingsController* RPbdb_DatabaseCursor_settingsController(	RPbdb_DatabaseCursor* database_cursor )	{
	return database_cursor->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseCursor_parentEnvironment(	RPbdb_DatabaseCursor* database_cursor )	{
	return database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseCursor_parentDatabase(	RPbdb_DatabaseCursor* database_cursor )	{
	return database_cursor->parent_database_cursor_controller->parent_database;
}

/***************************************
*  parentCursorController  *
***************************************/
RPbdb_DatabaseCursorController* RPbdb_DatabaseCursor_parentDatabaseCursorController(	RPbdb_DatabaseCursor* database_cursor )	{
	return database_cursor->parent_database_cursor_controller;
}

/************
*  open  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_open( RPbdb_DatabaseCursor* database_cursor )	{
	
	int					connection_error	= 0;

	RPbdb_Database*		parent_database	=	database_cursor->parent_database_cursor_controller->parent_database;
	RPbdb_Database_internal_ensureOpen( parent_database );

	RPbdb_Environment*	environment	=	database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;

	DB_TXN*	transaction_id	=	NULL;
	if ( database_cursor->parent_database_cursor_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	RPbdb_DatabaseSettingsController*				database_settings_controller				=	RPbdb_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	RPbdb_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	RPbdb_DatabaseSettingsController_cursorSettingsController( database_settings_controller );
	
	uint32_t	open_flags	=	RPbdb_DatabaseCursorSettingsController_internal_openFlags( database_cursor_settings_controller );
	
	//	Open our BDB database_cursor
	if ( ( connection_error = parent_database->wrapped_bdb_database->cursor(	parent_database->wrapped_bdb_database,
																																						transaction_id,
																																						&( database_cursor->wrapped_bdb_cursor ), 
																																						open_flags ) ) ) {

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ), 
																									connection_error, 
																									"DatabaseCursor_open" );
		return NULL;
	}
	
	database_cursor->is_open	=	TRUE;

	return database_cursor;
}

/************
*  isOpen  *
************/

BOOL RPbdb_DatabaseCursor_isOpen( RPbdb_DatabaseCursor* database_cursor )	{
	return database_cursor->is_open;
}
	
/*************
*  close  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_close.html
RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_close( RPbdb_DatabaseCursor* database_cursor )	{

	int					connection_error	= 0;
	
	if (	RPbdb_DatabaseCursor_isOpen( database_cursor )
    &&  database_cursor->wrapped_bdb_cursor
		&&	( connection_error = database_cursor->wrapped_bdb_cursor->close( database_cursor->wrapped_bdb_cursor ) ) ) {

    RPbdb_Environment* environment = database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ), 
																									connection_error, 
																									"DatabaseCursor_close" );
		return NULL;
	}
	
	database_cursor->is_open	=	FALSE;
	
	return database_cursor;
}

/*************************
*  duplicateCursor  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_dup.html
RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_duplicateCursor( RPbdb_DatabaseCursor* database_cursor )	{

	RPbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	RPbdb_DatabaseCursor*		cursor_copy	= RPbdb_DatabaseCursor_new( database_cursor->parent_database_cursor_controller );

	RPbdb_DatabaseSettingsController*				database_settings_controller				=	RPbdb_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	RPbdb_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	RPbdb_DatabaseSettingsController_cursorSettingsController( database_settings_controller );
	
	uint32_t	duplicate_flags	=	RPbdb_DatabaseCursorSettingsController_internal_duplicateFlags( database_cursor_settings_controller );

	int							connection_error	= 0;
	if ( ( connection_error = database_cursor->wrapped_bdb_cursor->dup(	database_cursor->wrapped_bdb_cursor, 
																																			& cursor_copy->wrapped_bdb_cursor,
																																			duplicate_flags ) ) ) {

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ), 
																									connection_error, 
																									"DatabaseCursor_copy" );
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
void RPbdb_DatabaseCursor_overwriteCurrentDataWithRecord(	RPbdb_DatabaseCursor*	database_cursor, 
																													RPbdb_Record*			record )	{

	RPbdb_DatabaseCursor_internal_writeRecord(	database_cursor, 
																						DB_CURRENT, 
																						record );
}

/****************************************
*  writeKeyDataPairAsCurrentRecord  *
****************************************/

//	DB_CURRENT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPbdb_DatabaseCursor_overwriteCurrentData(	RPbdb_DatabaseCursor*	database_cursor, 
																							RPbdb_Data*				data )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																																					DB_CURRENT,
																																					NULL,
																																					data );
	RPbdb_Record_free( & record );
}

/********************************************
*  writeRawKeyDataPairAsCurrentRecord  *
********************************************/

//	DB_CURRENT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPbdb_DatabaseCursor_overwriteCurrentDataWithRawData(	RPbdb_DatabaseCursor*	database_cursor, 
																								void*									data_raw,
																								uint32_t							data_size )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																																						DB_CURRENT,
																																						NULL,
																																						0,
																																						data_raw,
																																						data_size );
	RPbdb_Record_free( & record );
}

/****************************************
*  writeAfterCurrentRecord  *
****************************************/

//	DB_AFTER				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPbdb_DatabaseCursor_writeRecordAsDuplicateDataAfterCurrent(	RPbdb_DatabaseCursor*		database_cursor, 
																																	RPbdb_Record*						record )	{

	RPbdb_DatabaseCursor_internal_writeRecord(		database_cursor, 
																							DB_AFTER, 
																							record );
}

/********************************************
*  writeKeyDataPairAfterCurrentRecord  *
********************************************/

//	DB_AFTER				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPbdb_DatabaseCursor_writeDataAsDuplicateAfterCurrent(	RPbdb_DatabaseCursor*	database_cursor, 
																														RPbdb_Data*				data )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																																					DB_AFTER,
																																					NULL,
																																					data );
	RPbdb_Record_free( & record );
}

/************************************************
*  writeRawKeyDataPairAfterCurrentRecord  *
************************************************/

//	DB_AFTER				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPbdb_DatabaseCursor_writeRawDataAsDuplicateAfterCurrent(	RPbdb_DatabaseCursor*	database_cursor, 
																															void*									data_raw,
																															uint32_t							data_size )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																																						DB_AFTER,
																																						NULL,
																																						0,
																																						data_raw,
																																						data_size );
	RPbdb_Record_free( & record );
}

/******************************************
*  writeBeforeCurrentRecord  *
******************************************/

//	DB_BEFORE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPbdb_DatabaseCursor_writeRecordAsDuplicateBeforeCurrent(	RPbdb_DatabaseCursor*		database_cursor, 
																															RPbdb_Record*						record )	{

	RPbdb_DatabaseCursor_internal_writeRecord(		database_cursor, 
																							DB_BEFORE, 
																							record );
}

/********************************************
*  writeKeyDataPairBeforeCurrentRecord  *
********************************************/

//	DB_BEFORE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPbdb_DatabaseCursor_writeDataAsDuplicateBeforeCurrent(	RPbdb_DatabaseCursor*	database_cursor, 
																														RPbdb_Data*						data )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																																					DB_BEFORE,
																																					NULL,
																																					data );
	RPbdb_Record_free( & record );
}

/************************************************
*  writeRawKeyDataPairBeforeCurrentRecord  *
************************************************/

//	DB_BEFORE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPbdb_DatabaseCursor_writeRawDataAsDuplicateBeforeCurrent(	RPbdb_DatabaseCursor*	database_cursor, 
																																void*									data_raw,
																																uint32_t							data_size )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																																						DB_BEFORE,
																																						NULL,
																																						0,
																																						data_raw,
																																						data_size );
	RPbdb_Record_free( & record );
}


/*********************************
*  writeRecordBeforeAnyDuplicates  *
*********************************/

void RPbdb_DatabaseCursor_writeRecord(	RPbdb_DatabaseCursor*	database_cursor, 
																			RPbdb_Record*							record )	{

	RPbdb_DatabaseCursor_writeRecordAfterAnyDuplicates(	database_cursor,
																											record );
}

/*****************************************
*  writeKeyDataPair  *
*****************************************/

void RPbdb_DatabaseCursor_writeKeyDataPair(		RPbdb_DatabaseCursor*	database_cursor, 
																							RPbdb_Key*				key,
																							RPbdb_Data*				data )	{

	RPbdb_DatabaseCursor_writeKeyDataPairAfterAnyDuplicates(	database_cursor,
																													key,
																													data	);
}
	
/*****************************************
*  writeRawKeyDataPair  *
*****************************************/

void RPbdb_DatabaseCursor_writeRawKeyDataPair(	RPbdb_DatabaseCursor*	database_cursor, 
																							void*									key_raw,
																							uint32_t							key_size,
																							void*									data_raw,
																							uint32_t							data_size )	{
	
	RPbdb_DatabaseCursor_writeRawKeyDataPairAfterAnyDuplicates(	database_cursor,
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
void RPbdb_DatabaseCursor_writeRecordBeforeAnyDuplicates(	RPbdb_DatabaseCursor*	database_cursor, 
																													RPbdb_Record*							record )	{

	RPbdb_DatabaseCursor_internal_writeRecord(		database_cursor, 
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
void RPbdb_DatabaseCursor_writeKeyDataPairBeforeAnyDuplicates(		RPbdb_DatabaseCursor*	database_cursor, 
																																RPbdb_Key*							key,
																																RPbdb_Data*						data )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																																					DB_KEYFIRST,
																																					key,
																																					data );
	RPbdb_Record_free( & record );
}

/*****************************************
*  writeRawKeyDataPairAsFirstRecord  *
*****************************************/

//	If the key already exists in the database and no duplicate sort function has been specified, 
//	the inserted data item is added as the first of the data items for that key.
//	If duplicate sort function has been specified, it will be used rather than inserting before duplicates. 
//	DB_KEYFIRST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPbdb_DatabaseCursor_writeRawKeyDataPairBeforeAnyDuplicates(	RPbdb_DatabaseCursor*	database_cursor, 
																																	void*									key_raw,
																																	uint32_t							key_size,
																																	void*									data_raw,
																																	uint32_t							data_size )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																																						DB_KEYFIRST,
																																						key_raw,
																																						key_size,
																																						data_raw,
																																						data_size );
	RPbdb_Record_free( & record );
}

/********************************
*  writeDataAsLastRecord  *
********************************/

//	If the key already exists in the database and no duplicate sort function has been specified, 
//	the inserted data item is added as the first of the data items for that key.
//	If duplicate sort function has been specified, it will be used rather than inserting after duplicates. 
//	DB_KEYLAST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPbdb_DatabaseCursor_writeRecordAfterAnyDuplicates(	RPbdb_DatabaseCursor*	database_cursor, 
																												RPbdb_Record*							record )	{

	RPbdb_DatabaseCursor_internal_writeRecord(	database_cursor, 
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
void RPbdb_DatabaseCursor_writeKeyDataPairAfterAnyDuplicates(	RPbdb_DatabaseCursor*	database_cursor, 
																															RPbdb_Key*							key,
																															RPbdb_Data*						data )	{
	
	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																																					DB_KEYLAST,
																																					key,
																																					data );
	RPbdb_Record_free( & record );
}

/********************************************
*  writeRawKeyDataPairAsLastRecord  *
********************************************/

//	If the key already exists in the database and no duplicate sort function has been specified, 
//	the inserted data item is added as the first of the data items for that key.
//	If duplicate sort function has been specified, it will be used rather than inserting after duplicates. 
//	DB_KEYLAST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void RPbdb_DatabaseCursor_writeRawKeyDataPairAfterAnyDuplicates(	RPbdb_DatabaseCursor*	database_cursor, 
																																void*									key_raw,
																																uint32_t							key_size,
																																void*									data_raw,
																																uint32_t							data_size )	{
	
	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																																						DB_KEYLAST,
																																						key_raw,
																																						key_size,
																																						data_raw,
																																						data_size );
	RPbdb_Record_free( & record );
}


/**************************************
*  writeOnlyIfNonExisting  *
**************************************/

//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
BOOL RPbdb_DatabaseCursor_writeRecordOnlyIfNotInDatabase(	RPbdb_DatabaseCursor*		database_cursor, 
																													RPbdb_Record*						record )	{

	record	=	RPbdb_DatabaseCursor_internal_writeRecord(	database_cursor, 
																											DB_NODUPDATA,
																											record );
	if ( record->data->wrapped_bdb_dbt->size == 0 )	{
		return FALSE;
	}
	return TRUE;

}

/******************************************
*  writeKeyDataPairOnlyIfNonExisting  *
******************************************/

//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
BOOL RPbdb_DatabaseCursor_writeKeyDataPairOnlyIfNotInDatabase(	RPbdb_DatabaseCursor*	database_cursor, 
																															RPbdb_Key*							key,
																															RPbdb_Data*						data )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																																					DB_NODUPDATA,
																																					key,
																																					data );
	if ( record->data->wrapped_bdb_dbt->size == 0 )	{
		return FALSE;
	}
	return TRUE;
}

/**********************************************
*  writeRawKeyDataPairOnlyIfNonExisting  *
**********************************************/

//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
BOOL RPbdb_DatabaseCursor_writeRawKeyDataPairOnlyIfNotInDatabase(	RPbdb_DatabaseCursor*	database_cursor, 
																																	void*									key_raw,
																																	uint32_t							key_size,
																																	void*									data_raw,
																																	uint32_t							data_size )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																																						DB_NODUPDATA,
																																						key_raw,
																																						key_size,
																																						data_raw,
																																						data_size );
	if ( record->data->wrapped_bdb_dbt->size == 0 )	{
		return FALSE;
	}
	return TRUE;
}

/*******************************************************************************************************************************************************************************************
																	Initial Retrieval
*******************************************************************************************************************************************************************************************/

/*****************************
*  recordExistsForKey  *
*****************************/

BOOL RPbdb_DatabaseCursor_keyExists(	RPbdb_DatabaseCursor*		database_cursor, 
																		RPbdb_Key*								key )	{

	RPbdb_Record*	record	=	RPbdb_Record_internal_newFromKeyData(	database_cursor->parent_database_cursor_controller->parent_database,
																																key,
																																NULL	);

	record = 	RPbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																													DB_SET, 
																													record );
	
	BOOL	exists_in_database	=	( record->result == TRUE );
	
	RPbdb_Record_free( & record );
	
	return exists_in_database;
}

/*****************************
*  recordExistsForRawKey  *
*****************************/

BOOL RPbdb_DatabaseCursor_rawKeyExists(	RPbdb_DatabaseCursor*		database_cursor, 
																				void*										key_raw,
																				uint32_t								key_size )	{

	RPbdb_Key*	key	=	RPbdb_Key_new( NULL );
	
	RPbdb_Key_setRawData(	key,
										key_raw,
										key_size );

	return RPbdb_DatabaseCursor_keyExists(	database_cursor,
																				key );
}

/*************************
*  retrieveRecord  *
*************************/

RPbdb_Record* RPbdb_DatabaseCursor_retrieveRecord(	RPbdb_DatabaseCursor*		database_cursor, 
																									RPbdb_Record*						record )	{

	return RPbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																											DB_SET, 
																											record );
}

/*****************************
*  retrieveKey  *
*****************************/

RPbdb_Record* RPbdb_DatabaseCursor_retrieveKey(	RPbdb_DatabaseCursor*		database_cursor, 
																							RPbdb_Key*								key_data )	{

	RPbdb_Database*	parent_database	=	database_cursor->parent_database_cursor_controller->parent_database;
	RPbdb_Record*	record	=	RPbdb_Record_new( parent_database );
	
	RPbdb_Record_setKey(	record,
											key_data );
	
	if (		RPbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																												DB_SET, 
																												record )->result == FALSE
			||	record->result == DB_KEYEMPTY )	{
		RPbdb_Record_free( & record );
	}
	return record;
}

/********************************
*  retrieveRawKey  *
********************************/

//	DB_SET				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Move the database_cursor to specified location
RPbdb_Record* RPbdb_DatabaseCursor_retrieveRawKey(	RPbdb_DatabaseCursor*		database_cursor, 
																									void*										key_raw,
																									uint32_t								key_size )	{

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_SET, 
																															key_raw,
																															key_size, 
																															NULL,
																															0 );
}

/*********************************************
*  retrieveMatchingKeyDataPair  *
*********************************************/

RPbdb_Record* RPbdb_DatabaseCursor_retrieveMatchingKeyDataPair(	RPbdb_DatabaseCursor*		database_cursor, 
																															RPbdb_Key*								key_data,
																															RPbdb_Data*							data )	{

	RPbdb_Database*	parent_database	=	database_cursor->parent_database_cursor_controller->parent_database;
	RPbdb_Record*	record	=	RPbdb_Record_new( parent_database );
	
	RPbdb_Record_setKey(	record,
											key_data );
	RPbdb_Record_setData(	record,
												data );

	if (		RPbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																												DB_GET_BOTH, 
																												record )->result == FALSE
			||	record->result == DB_KEYEMPTY )	{
		RPbdb_Record_free( & record );
	}
	return record;
}

/************************************************
*  retrieveMatchingRawKeyDataPair  *
************************************************/

//	DB_GET_BOTH				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	We need to add key specification here
RPbdb_Record* RPbdb_DatabaseCursor_retrieveMatchingRawKeyDataPair(	RPbdb_DatabaseCursor*		database_cursor,
																																	void*										key_raw,
																																	uint32_t								key_size,
																																	void*										data_raw,
																																	uint32_t								data_size )	{

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
RPbdb_Record* RPbdb_DatabaseCursor_retrieveRecordWithNumber(	RPbdb_DatabaseCursor* 	database_cursor,
																														db_recno_t*									record_id )	{

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_SET_RECNO,
																															record_id, 
																															sizeof( uint32_t ),
																															NULL,
																															0 );
}

/****************************************
*  retrieveRecordWithNumberInKey  *
****************************************/

RPbdb_Record* RPbdb_DatabaseCursor_retrieveRecordWithNumberAsKey(	RPbdb_DatabaseCursor* 	database_cursor,
																																RPbdb_Key*				key_with_record_number )	{

	//	We should probably make sure here that record ID is an int

	RPbdb_Database*	parent_database	=	database_cursor->parent_database_cursor_controller->parent_database;
	RPbdb_Record*	record	=	RPbdb_Record_new( parent_database );
	
	RPbdb_Record_setKey(	record,
											key_with_record_number );

	if (		RPbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																												DB_SET_RECNO, 
																												record )->result == FALSE
			||	record->result == DB_KEYEMPTY )	{
		RPbdb_Record_free( & record );
	}
	return record;
}

/*****************************************
*  retrievePartialRawKey  *
*****************************************/

//	DB_SET_RANGE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Must be Btree and it must have been created with the DB_RECNUM flag.
//	Permits partial key matches and range searches by returning the smallest item matching or including the key
RPbdb_Record* RPbdb_DatabaseCursor_retrievePartialRawKey(	RPbdb_DatabaseCursor*		database_cursor,
																												void*										key_raw,
																												uint32_t								key_size )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																																								DB_SET_RANGE, 
																																								key_raw, 
																																								key_size,
																																								NULL,
																																								0 );

	if ( record->data->wrapped_bdb_dbt->size == 0 )	{
		RPbdb_Record_free( & record );
	}
	return record;
}

/**************************************
*  retrievePartialKeyDataPair  *
**************************************/

//	DB_GET_BOTH_RANGE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Permits partial data matches and range searches by returning the smallest item matching or including the data
RPbdb_Record* RPbdb_DatabaseCursor_retrievePartialKey(	RPbdb_DatabaseCursor*		database_cursor,
																											RPbdb_Key*								partial_key )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_retrieveKeyDataPair(	database_cursor, 
																																						DB_SET_RANGE, 
																																						partial_key, 
																																						NULL  );

	if ( record->data->wrapped_bdb_dbt->size == 0 )	{
		RPbdb_Record_free( & record );
	}
	return record;
}

/**************************************
*  retrievePartialKeyInRecord  *
**************************************/

RPbdb_Record* RPbdb_DatabaseCursor_retrievePartialKeyInRecord(	RPbdb_DatabaseCursor*		database_cursor,
																															RPbdb_Record*						record  )	{
	
	record	=	RPbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																													DB_SET_RANGE, 
																													record  );
	return record;
}

/**************************************************
*  retrieveRawKeyPartialDataPair  *
**************************************************/

RPbdb_Record* RPbdb_DatabaseCursor_retrieveDuplicateMatchingRawData(	RPbdb_DatabaseCursor*		database_cursor,
																																		void*										key_raw,
																																		uint32_t								key_size,
																																		void*										data_raw,
																																		uint32_t								data_size )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																																								DB_GET_BOTH_RANGE, 
																																								key_raw, 
																																								key_size,
																																								data_raw,
																																								data_size );

	if ( record->data->wrapped_bdb_dbt->size == 0 )	{
		RPbdb_Record_free( & record );
	}
	return record;
}

/**************************************
*  retrievePartialKeyDataPair  *
**************************************/

//	DB_GET_BOTH_RANGE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Permits partial data matches and range searches by returning the smallest item matching or including the data
RPbdb_Record* RPbdb_DatabaseCursor_retrieveDuplicateMatchingPartialData(	RPbdb_DatabaseCursor*		database_cursor,
																																				RPbdb_Key*								partial_key,
																																				RPbdb_Data*							partial_data )	{

	RPbdb_Record*	record	=	RPbdb_DatabaseCursor_internal_retrieveKeyDataPair(	database_cursor, 
																																						DB_GET_BOTH_RANGE, 
																																						partial_key, 
																																						partial_data  );

	if ( record->data->wrapped_bdb_dbt->size == 0 )	{
		RPbdb_Record_free( & record );
	}
	return record;
}

/**************************************
*  retrievePartialKeyDataPairInRecord  *
**************************************/

RPbdb_Record* RPbdb_DatabaseCursor_retrieveDuplicateMatchingPartialDataInRecord(	RPbdb_DatabaseCursor*		database_cursor,
																																								RPbdb_Record*						record  )	{
	
	uint32_t	partial_data_size	=	RPbdb_Record_dataSize( record );
	record	=	RPbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																													DB_GET_BOTH_RANGE, 
																													record  );
	
	if ( RPbdb_Record_dataSize( record ) == partial_data_size )	{
		RPbdb_Record_setRawData( record,
														NULL,
														0 );
	}
	
	return record;
}


/*******************************************************************************************************************************************************************************************
																Relative to Current Key
*******************************************************************************************************************************************************************************************/

/****************
*  current  *
****************/

//	DB_CURRENT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPbdb_Record* RPbdb_DatabaseCursor_retrieveCurrent( RPbdb_DatabaseCursor* database_cursor )	{

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
BOOL RPbdb_DatabaseCursor_setToFirst( RPbdb_DatabaseCursor* database_cursor )	{
	RPbdb_Record*	first_record	=	RPbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	
	RPbdb_DatabaseCursor_internal_retrieveFirst(	database_cursor,
																							first_record );
	
	BOOL has_record	=	FALSE;
	if ( first_record->result )	{
		has_record	=	TRUE;
	}

	RPbdb_Record_free( & first_record );

	return has_record;
}

/****************
*  first  *
****************/

//	DB_FIRST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
RPbdb_Record* RPbdb_DatabaseCursor_retrieveFirst( RPbdb_DatabaseCursor* database_cursor )	{

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
RPbdb_Record* RPbdb_DatabaseCursor_retrieveLast( RPbdb_DatabaseCursor* database_cursor )	{

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor,
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
RPbdb_Record* RPbdb_DatabaseCursor_retrieveNext( RPbdb_DatabaseCursor* database_cursor )	{

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
RPbdb_Record* RPbdb_DatabaseCursor_retrieveNextDuplicate( RPbdb_DatabaseCursor* database_cursor )	{

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
RPbdb_Record* RPbdb_DatabaseCursor_retrieveNextNonDuplicate( RPbdb_DatabaseCursor* database_cursor )	{

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
RPbdb_Record* RPbdb_DatabaseCursor_retrievePrevious( RPbdb_DatabaseCursor* database_cursor )	{

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
RPbdb_Record* RPbdb_DatabaseCursor_retrievePreviousDuplicate( RPbdb_DatabaseCursor* database_cursor )	{

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
RPbdb_Record* RPbdb_DatabaseCursor_retrievePreviousNonDuplicate( RPbdb_DatabaseCursor* database_cursor )	{

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
RPbdb_Record* RPbdb_DatabaseCursor_retrieveCurrentRecordNumber( RPbdb_DatabaseCursor* database_cursor )	{

	RPbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	RPbdb_DatabaseSettingsController*			database_settings_controller			=	RPbdb_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
	DBTYPE																database_type											=	RPbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

	//	Make sure we have DB_RECNO
	if ( database_type != DB_RECNO )	{

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ),
																									RP_ERROR_NOT_DB_QUEUE_OR_DB_RECNO, 
																									"Database_append" );
	}

	return RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
db_recno_t RPbdb_DatabaseCursor_countDuplicatesForCurrentKey( RPbdb_DatabaseCursor* database_cursor )	{

	RPbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	db_recno_t			number_data_items_for_cursor;		

	RPbdb_Environment*						environment	= database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;

	RPbdb_DatabaseSettingsController*				database_settings_controller				=	RPbdb_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	RPbdb_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	RPbdb_DatabaseSettingsController_cursorSettingsController( database_settings_controller );
	
	int	count_data_items_flags	=	RPbdb_DatabaseCursorSettingsController_internal_countDataItemsFlags( database_cursor_settings_controller );

	int	connection_error	= 0;
	if ( ( connection_error = database_cursor->wrapped_bdb_cursor->count(	database_cursor->wrapped_bdb_cursor, 
																																				& number_data_items_for_cursor, 
																																				count_data_items_flags ) ) ) {

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ), 
																									connection_error, 
																									"DatabaseCursor_itemCountForCurrentKey" );
	}

	return number_data_items_for_cursor;
}

/************************
*  resetIteration  *
************************/

void RPbdb_DatabaseCursor_resetIteration( RPbdb_DatabaseCursor* database_cursor )	{
	database_cursor->iteration_started	=	FALSE;
}

/************************
*  resetIteration  *
************************/

void RPbdb_DatabaseCursor_resetDuplicateIteration( RPbdb_DatabaseCursor* database_cursor )	{
	database_cursor->duplicate_iteration_started	=	FALSE;
}
	
/****************************
*  iterate  *
****************************/

// if we have duplicates for db, each iterates duplicates
// if we have no duplicates for db, each iterates records
RPbdb_Record* RPbdb_DatabaseCursor_iterate(	RPbdb_DatabaseCursor*	database_cursor,
																					RPbdb_Record*					record )	{

	RPbdb_DatabaseCursor_internal_ensureOpen( database_cursor );
	
	//	if we have a null record, instantiate it
	//	caller responsible for freeing
	if ( record == NULL )	{
		record = RPbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}
	
	//	Args:
	//	0 args: intelligent iteration
	//	1 arg: if true - force iterate all 

	if ( database_cursor->iteration_started == FALSE )	{
    if ( database_cursor->retrieved_record == FALSE ) {
      RPbdb_DatabaseCursor_internal_retrieveFirst(	database_cursor,
                                                  record );
    }
    else  {
      RPbdb_DatabaseCursor_internal_retrieveCurrent(	database_cursor,
                                                    record );
    }
		database_cursor->iteration_started = TRUE;
	}
	else {
	
		RPbdb_DatabaseCursor_internal_retrieveNext(	database_cursor,
																								record );
	}
	
	if ( record->result == FALSE )	{
		RPbdb_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return RPbdb_DatabaseCursor_iterate(	database_cursor,
																				record );
	}

	return record;
}

/****************************
*  iterateDuplicates  *
****************************/

//	iterates all records with one or more duplicates
RPbdb_Record* RPbdb_DatabaseCursor_iterateDuplicates( RPbdb_DatabaseCursor*	database_cursor,
																										RPbdb_Record*					record  )	{
	
	RPbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	//	if we have a null record, instantiate it
	//	caller responsible for freeing
	if ( record == NULL )	{
		record = RPbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}

	if ( database_cursor->duplicate_iteration_started == FALSE )	{
		RPbdb_DatabaseCursor_internal_retrieveCurrent( database_cursor,
																									record );
		database_cursor->duplicate_iteration_started = TRUE;
	}
	else {
		RPbdb_DatabaseCursor_internal_retrieveNextDuplicate( database_cursor,
																												record );		
	}
	
	if ( record->result == FALSE )	{
		RPbdb_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return RPbdb_DatabaseCursor_iterateDuplicates(	database_cursor,
																									record );
	}
	
	return record;
}

/****************************
*  iterateKeys  *
****************************/

//	iterates all records without duplicates
RPbdb_Record* RPbdb_DatabaseCursor_iterateKeys( RPbdb_DatabaseCursor* database_cursor,
																							RPbdb_Record*					record  )	{
	
	RPbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	//	if we have a null record, instantiate it
	//	caller responsible for freeing
	if ( record == NULL )	{
		record = RPbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}

	if ( database_cursor->iteration_started == FALSE )	{
		RPbdb_DatabaseCursor_internal_retrieveCurrent( database_cursor,
																									record );
		database_cursor->iteration_started	=	TRUE;
	}
	else {
		RPbdb_DatabaseCursor_internal_retrieveNextNonDuplicate(	database_cursor,
																														record );		
	}
	
	if ( record->result == FALSE )	{
		RPbdb_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return RPbdb_DatabaseCursor_iterateKeys(	database_cursor,
																						record );
	}
	
	return record;
}

/****************************
*  slice  *
****************************/

//	iterates a slice of records
RPbdb_Record* RPbdb_DatabaseCursor_slice( RPbdb_DatabaseCursor*	database_cursor,
																				uint32_t							length,
																				RPbdb_Record*					record )	{

	if ( record == NULL )	{
		database_cursor->slice_length	=	length - 1;
		record = RPbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}
	else {
		database_cursor->slice_length--;
	}

	
	if ( database_cursor->iteration_started == FALSE )	{
		RPbdb_DatabaseCursor_internal_retrieveCurrent(	database_cursor,
																									record );
		database_cursor->iteration_started = TRUE;
	}
	else {
	
		RPbdb_DatabaseCursor_internal_retrieveNext(	database_cursor,
																								record );
	}
	
	if (		record->result == FALSE
			||	database_cursor->slice_length == 0 )	{

		RPbdb_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return RPbdb_DatabaseCursor_iterateKeys(	database_cursor,
																						record );
	}

	return record;
}

/****************************
*  sliceKeys  *
****************************/

//	iterates a slice of records
RPbdb_Record* RPbdb_DatabaseCursor_sliceKeys( RPbdb_DatabaseCursor*	database_cursor,
																						uint32_t							length,
																						RPbdb_Record*					record )	{

	if ( record == NULL )	{
		database_cursor->slice_length	=	length - 1;
		record = RPbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}
	else {
		database_cursor->slice_length--;
	}
	
	if ( database_cursor->iteration_started == FALSE )	{
		RPbdb_DatabaseCursor_internal_retrieveCurrent( database_cursor,
																									record );
		database_cursor->iteration_started	=	TRUE;
	}
	else {
		RPbdb_DatabaseCursor_internal_retrieveNextNonDuplicate(	database_cursor,
																														record );		
	}
	
	if (		record->result == FALSE
			||	database_cursor->slice_length == 0 )	{

		RPbdb_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return RPbdb_DatabaseCursor_iterateKeys(	database_cursor,
																						record );
	}

	return record;
}

/****************************
*  sliceDuplicates  *
****************************/

//	iterates a slice of records
RPbdb_Record* RPbdb_DatabaseCursor_sliceDuplicates( RPbdb_DatabaseCursor*	database_cursor,
																									uint32_t							length,
																									RPbdb_Record*					record )	{

	if ( record == NULL )	{
		database_cursor->slice_length	=	length - 1;
		record = RPbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}
	else {
		database_cursor->slice_length--;
	}

	if ( database_cursor->duplicate_iteration_started == FALSE )	{
		RPbdb_DatabaseCursor_internal_retrieveCurrent( database_cursor,
																									record );
		database_cursor->duplicate_iteration_started = TRUE;
	}
	else {
		RPbdb_DatabaseCursor_internal_retrieveNextDuplicate( database_cursor,
																												record );		
	}
	
	if (		record->result == FALSE
			||	database_cursor->slice_length == 0 )	{

		RPbdb_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return RPbdb_DatabaseCursor_iterateKeys(	database_cursor,
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
RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteCurrentRecord( RPbdb_DatabaseCursor*	database_cursor )	{

	int					connection_error	= 0;

	RPbdb_DatabaseSettingsController*									database_settings_controller										=	RPbdb_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	RPbdb_DatabaseCursorSettingsController*						database_cursor_settings_controller							=	RPbdb_DatabaseSettingsController_cursorSettingsController( database_settings_controller );
	RPbdb_DatabaseCursorReadWriteSettingsController*		database_cursor_record_read_write_settings_controller	=	RPbdb_DatabaseCursorSettingsController_readWriteSettingsController( database_cursor_settings_controller );
	
	uint32_t		flags	=	RPbdb_DatabaseCursorReadWriteSettingsController_internal_deleteFlags( database_cursor_record_read_write_settings_controller );
	
	if ( ( connection_error = database_cursor->wrapped_bdb_cursor->del(	database_cursor->wrapped_bdb_cursor, 
																																			flags ) ) ) {

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ), 
																									connection_error, 
																									"DatabaseCursor_deleteCurrentRecord" );
		return NULL;
	}
	
	return database_cursor;
}

/*****************************
*  deleteRecordWithKey  *
*****************************/

RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteKey(	RPbdb_DatabaseCursor*		database_cursor,
																										RPbdb_Key*								key	)	{
	
	//	Set current record to key/data pair
	RPbdb_DatabaseCursor_retrieveKey(	database_cursor,
																		key );
	
	//	Delete current record
	RPbdb_DatabaseCursor_deleteCurrentRecord( database_cursor );
	
	return database_cursor;
}

/*****************************
*  deleteRecordWithRawKey  *
*****************************/

RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteRawKey(	RPbdb_DatabaseCursor*	database_cursor,
																												void*									key_raw,
																												uint32_t							key_size )	{
	RPbdb_Key*	key	=	RPbdb_Key_new( NULL );
	RPbdb_Key_setRawData(	key,
												key_raw,
												key_size );
							
	RPbdb_DatabaseCursor_deleteKey(	database_cursor,
																	key );
	return database_cursor;
}

/************************************
*  deleteRecordWithKeyDataPair  *
************************************/

RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteKeyDataPair(	RPbdb_DatabaseCursor*	database_cursor,
																														RPbdb_Key*							key,
																														RPbdb_Data*						data	)	{
	
	//	Set current record to key/data pair
	RPbdb_DatabaseCursor_retrieveMatchingKeyDataPair(	database_cursor,
																										key,
																										data );
	
	//	Delete current record
	RPbdb_DatabaseCursor_deleteCurrentRecord( database_cursor );
	
	return database_cursor;
}

/*************************************
*  deleteRecordWithRawKeyDataPair  *
*************************************/

RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteRawKeyDataPair(	RPbdb_DatabaseCursor*	database_cursor,
																																void*									key_raw,
																																uint32_t							key_size,
																																void*									data_raw,
																																uint32_t							data_size	)	{

	RPbdb_Record*	record	=	RPbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	RPbdb_Record_setRawKey(	record,
													key_raw,
													key_size );
	RPbdb_Record_setRawData(	record,
													data_raw,
													data_size );
	RPbdb_DatabaseCursor_deleteKeyDataPair(	database_cursor,
																					record->key,
																					record->data );
	return database_cursor;
}

/******************************
*  deleteRecordWithNumber  *
******************************/

RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteRecordNumber(	RPbdb_DatabaseCursor*	database_cursor,
																															db_recno_t*						record_number	)	{
	
	//	Set current record to record number
	RPbdb_DatabaseCursor_retrieveRawKey( database_cursor ,
																			record_number,
																			sizeof( uint32_t ) );
	
	//	Delete current record
	return RPbdb_DatabaseCursor_deleteCurrentRecord( database_cursor );
}

/********************
*  deleteRecord  *
********************/

RPbdb_DatabaseCursor* RPbdb_DatabaseCursor_deleteRecord(	RPbdb_DatabaseCursor*	database_cursor,
																												RPbdb_Record*					record	)	{
	
	RPbdb_Database_internal_prepareRecordForWriteRetrieveDelete(	database_cursor->parent_database_cursor_controller->parent_database,
																															record,
																															FALSE );

	//	Set current record to data
	RPbdb_DatabaseCursor_retrieveRecord( database_cursor ,
																			record );
	
	//	Delete current record
	return RPbdb_DatabaseCursor_deleteCurrentRecord( database_cursor );
}


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Write Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************************
*  ensureInitialized  *
***********************/

void RPbdb_DatabaseCursor_internal_ensureOpen( RPbdb_DatabaseCursor* database_cursor )	{
	
	if ( ! RPbdb_DatabaseCursor_isOpen( database_cursor ) )	{
		RPbdb_DatabaseCursor_open( database_cursor );
	}
}

/*******************
*  writeData  *
*******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
RPbdb_Record* RPbdb_DatabaseCursor_internal_writeRecord(	RPbdb_DatabaseCursor*	database_cursor, 
																												uint32_t				flags,
																												RPbdb_Record*			record )	{

	RPbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	RPbdb_Database_internal_prepareRecordForWriteRetrieveDelete(	database_cursor->parent_database_cursor_controller->parent_database,
																															record,
																															TRUE );

	int	connection_error	= 0;

	if ( ( connection_error = database_cursor->wrapped_bdb_cursor->put(	database_cursor->wrapped_bdb_cursor, 
																																			record->key->wrapped_bdb_dbt, 
																																			record->data->wrapped_bdb_dbt, 
																																			flags ) ) ) {

		switch ( connection_error ) {
			//	if we asked for NODUPDATA we want to know if we inserted
			case DB_KEYEXIST:
				if ( flags == DB_NODUPDATA )	{
					record->data->wrapped_bdb_dbt->size = 0;
					return record;
				}
				break;
		}
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ), 
																									connection_error, 
																									"DatabaseCursor_internal_write" );
	}
	return record;
}

/**************************
*  writeKeyDataPair  *
**************************/

RPbdb_Record* RPbdb_DatabaseCursor_internal_writeKeyDataPair(	RPbdb_DatabaseCursor*	database_cursor, 
																														uint32_t							flags,
																														RPbdb_Key*							key,
																														RPbdb_Data*						data )	{

	RPbdb_Record*				record			= RPbdb_Record_internal_newFromKeyData(	database_cursor->parent_database_cursor_controller->parent_database,
																																					key,
																																					data	);

	return RPbdb_DatabaseCursor_internal_writeRecord(	database_cursor,
																										flags,
																										record );
}

/******************************
*  writeRawKeyDataPair  *
******************************/

RPbdb_Record* RPbdb_DatabaseCursor_internal_writeRawKeyDataPair(	RPbdb_DatabaseCursor*	database_cursor, 
																																uint32_t							flags,
																																void*									key,
																																uint32_t							key_size,
																																void*									data,
																																uint32_t							data_size )	{

	RPbdb_Record*				record			= RPbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	
	RPbdb_Key_setRawData(	record->key,
												key,
												key_size );
	RPbdb_Data_setRawData(	record->data,
												data,
												data_size );
	
	return 	RPbdb_DatabaseCursor_internal_writeRecord(	database_cursor,
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
RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	RPbdb_DatabaseCursor*		database_cursor, 
																																	uint32_t								flag, 
																																	void*										key,
																																	uint32_t								key_size,
																																	void*										data,
																																	uint32_t								data_size )	{

	RPbdb_Record*				record				= RPbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );

	if ( key != NULL )	{
		RPbdb_Key_setRawData(	record->key,
											key,
											key_size );
	}
		
	//	If we have data we're using to retrieve, load it into the DBT
	if ( data != NULL )	{
		
		RPbdb_Data_setRawData(	record->data,
												data,
												data_size );
		
	}

	return RPbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor,
																											flag,
																											record );
}

/**************************
*  retrieveRecord  *
**************************/

RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveKeyDataPair(	RPbdb_DatabaseCursor*		database_cursor, 
																																uint32_t								flags, 
																																RPbdb_Key*								key,
																																RPbdb_Data*							data	)	{

	RPbdb_Record*	record	=	RPbdb_Record_internal_newFromKeyData(	database_cursor->parent_database_cursor_controller->parent_database,
																																key,
																																data );
	
	return RPbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor,
																											flags,
																											record );
}

/**************************
*  retrieveRecord  *
**************************/

RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveRecord(	RPbdb_DatabaseCursor*		database_cursor, 
																													uint32_t								flags, 
																													RPbdb_Record*						record)	{

	RPbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	RPbdb_Database_internal_prepareRecordForWriteRetrieveDelete(	database_cursor->parent_database_cursor_controller->parent_database,
																															record,
																															( flags == DB_GET_BOTH ? TRUE : FALSE ) );

	RPbdb_Environment*	environment	= database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
	
	//	We have a flag describing what type of cursor operation we are executing; we need to add in flags
	//	that might apply to all situations.
	flags	|=	RPbdb_DatabaseCursorReadWriteSettingsController_internal_retrieveFlags(	RPbdb_DatabaseCursorSettingsController_readWriteSettingsController( RPbdb_DatabaseSettingsController_cursorSettingsController( RPbdb_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database ) ) ) );

	int		connection_error	= 0;

	//	If we have a secondary database we are using a secondary key and retrieving a primary key/data pair
	if ( RPbdb_Database_isSecondary( database_cursor->parent_database_cursor_controller->parent_database ) )	{

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

				RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ), 
																											connection_error, 
																											"DatabaseCursor_internal_retrieveRecord" );
			
				return NULL;
			}
		}
		else {
			record->result = TRUE;
      //  also note that this cursor now has a record set
      database_cursor->retrieved_record = TRUE;
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

				RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ), 
																											connection_error, 
																											"DatabaseCursor_internal_retrieveRecord" );
				return NULL;
			}
		}
		else {
			record->result                    = TRUE;
      //  also note that this cursor now has a record set
      database_cursor->retrieved_record = TRUE;
		}
	}
	
	return record;
}

/********************
*  retrieveFirst  *
********************/

RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveFirst(	RPbdb_DatabaseCursor*	cursor,
																													RPbdb_Record*					record )	{
	
	return RPbdb_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_FIRST,
																											record );
}

/********************
*  retrieveCurrent  *
********************/

RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveCurrent(	RPbdb_DatabaseCursor*	cursor,
																														RPbdb_Record*					record )	{
	
  if ( cursor->retrieved_record == FALSE )  {
  
    RPbdb_Environment*	environment	= cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
    RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( environment ), 
                                      -1, 
                                      "DatabaseCursor_internal_retrieveCurrent",
                                      "Cannot retrieve 'current' record until 'current' has been set." );
  }
  
	return RPbdb_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_CURRENT,
																											record );
}

/*****************
*  retrieveNext  *
*****************/

RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveNext(	RPbdb_DatabaseCursor*	cursor,
																												RPbdb_Record*					record )	{

	return RPbdb_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_NEXT,
																											record );
}

/**************************
*  retrieveNextDuplicate  *
**************************/

RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveNextDuplicate(	RPbdb_DatabaseCursor*	cursor,
																																	RPbdb_Record*					record )	{

	return RPbdb_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_NEXT_DUP,
																											record );
}

/*****************************
*  retrieveNextNonDuplicate  *
*****************************/

RPbdb_Record* RPbdb_DatabaseCursor_internal_retrieveNextNonDuplicate(	RPbdb_DatabaseCursor*	cursor,
																																		RPbdb_Record*					record )	{

	return RPbdb_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_NEXT_NODUP,
																											record );
}

