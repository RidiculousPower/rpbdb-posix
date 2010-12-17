/*
 *		Rbdb::DatabaseController::Database::DatabaseCursorController::DatabaseCursor
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseCursor.h"
#include "Rbdb_DatabaseCursor_internal.h"

#include "Rbdb_Environment.h"

#include "Rbdb_ErrorController.h"

#include "Rbdb_Database.h"
#include "Rbdb_Database_internal.h"

#include "Rbdb_Record.h"
#include "Rbdb_Record_internal.h"
#include "Rbdb_Key.h"

#include "Rbdb_TransactionController.h"
#include "Rbdb_TransactionController_internal.h"

#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseCursorSettingsController.h"
#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseTypeSettingsController.h"
#include "Rbdb_DatabaseTypeBtreeSettingsController.h"
#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"

#include "Rbdb_DatabaseCursorSettingsController_internal.h"
#include "Rbdb_DatabaseCursorReadWriteSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_new( Rbdb_DatabaseCursorController* parent_database_cursor_controller )	{

	Rbdb_DatabaseCursor*		database_cursor = calloc( 1, sizeof( Rbdb_DatabaseCursor ) );
	
	if ( parent_database_cursor_controller->runtime_storage_database != NULL )	{
		database_cursor->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_database_cursor_controller->runtime_storage_database,
																																											(void*) database_cursor );
	}
	
	database_cursor->parent_database_cursor_controller = parent_database_cursor_controller;

	Rbdb_Database*													parent_database												=	parent_database_cursor_controller->parent_database;
	Rbdb_DatabaseSettingsController*				database_settings_controller					=	Rbdb_Database_settingsController( parent_database );
	Rbdb_DatabaseCursorSettingsController*	database_cursor_settings_controller		=	Rbdb_DatabaseSettingsController_cursorSettingsController( database_settings_controller );

	//	Make call to instantiate local settings controller
	database_cursor->settings_controller	=	Rbdb_DatabaseCursorSettingsController_internal_copyOfSettingsControllerForInstance( database_cursor_settings_controller );

	database_cursor->iteration_started	=	0;
	database_cursor->is_open						=	FALSE;
	database_cursor->name								=	NULL;

	return database_cursor;
}

/***************************
*  free  *
***************************/

void Rbdb_DatabaseCursor_free(	Rbdb_DatabaseCursor** database_cursor )	{

	if ( ( *database_cursor )->parent_database_cursor_controller->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *database_cursor )->parent_database_cursor_controller->runtime_storage_database,
																											( *database_cursor )->runtime_identifier );
	}

	Rbdb_DatabaseCursor_internal_freeFromRuntimeStorage( database_cursor );
}

/***************************
*  free  *
***************************/

void Rbdb_DatabaseCursor_internal_freeFromRuntimeStorage(	Rbdb_DatabaseCursor** database_cursor )	{

	//	close self
	if ( Rbdb_DatabaseCursor_isOpen( *database_cursor ) )	{
		Rbdb_DatabaseCursor_close( *database_cursor );
	}

	//	free local settings controller
	if ( ( *database_cursor )->settings_controller != NULL )	{
		Rbdb_DatabaseCursorSettingsController_free( & ( ( *database_cursor )->settings_controller ) );
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
Rbdb_DatabaseCursorSettingsController* Rbdb_DatabaseCursor_settingsController(	Rbdb_DatabaseCursor* database_cursor )	{
	return database_cursor->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseCursor_parentEnvironment(	Rbdb_DatabaseCursor* database_cursor )	{
	return database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseCursor_parentDatabase(	Rbdb_DatabaseCursor* database_cursor )	{
	return database_cursor->parent_database_cursor_controller->parent_database;
}

/***************************************
*  parentCursorController  *
***************************************/
Rbdb_DatabaseCursorController* Rbdb_DatabaseCursor_parentDatabaseCursorController(	Rbdb_DatabaseCursor* database_cursor )	{
	return database_cursor->parent_database_cursor_controller;
}

/************
*  open  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_open( Rbdb_DatabaseCursor* database_cursor )	{
	
	int					connection_error	= 0;

	Rbdb_Database*		parent_database	=	database_cursor->parent_database_cursor_controller->parent_database;
	Rbdb_Database_internal_ensureOpen( parent_database );

	Rbdb_Environment*	environment	=	database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;

	DB_TXN*	transaction_id	=	NULL;
	if ( database_cursor->parent_database_cursor_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	Rbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	Rbdb_DatabaseSettingsController*				database_settings_controller				=	Rbdb_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	Rbdb_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	Rbdb_DatabaseSettingsController_cursorSettingsController( database_settings_controller );
	
	uint32_t	open_flags	=	Rbdb_DatabaseCursorSettingsController_internal_openFlags( database_cursor_settings_controller );
	
	//	Open our BDB database_cursor
	if ( ( connection_error = parent_database->wrapped_bdb_database->cursor(	parent_database->wrapped_bdb_database,
																																						transaction_id,
																																						&( database_cursor->wrapped_bdb_cursor ), 
																																						open_flags ) ) ) {

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ), 
																									connection_error, 
																									"Rbdb_DatabaseCursor_open" );
		return NULL;
	}
	
	database_cursor->is_open	=	TRUE;

	return database_cursor;
}

/************
*  isOpen  *
************/

BOOL Rbdb_DatabaseCursor_isOpen( Rbdb_DatabaseCursor* database_cursor )	{
	return database_cursor->is_open;
}
	
/*************
*  close  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_close.html
Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_close( Rbdb_DatabaseCursor* database_cursor )	{

	int					connection_error	= 0;
	
	if (	Rbdb_DatabaseCursor_isOpen( database_cursor )
		&&	( connection_error = database_cursor->wrapped_bdb_cursor->close( database_cursor->wrapped_bdb_cursor ) ) ) {

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ), 
																									connection_error, 
																									"Rbdb_DatabaseCursor_close" );
		return NULL;
	}
	
	database_cursor->is_open	=	FALSE;
	
	return database_cursor;
}

/*************************
*  duplicateCursor  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_dup.html
Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_duplicateCursor( Rbdb_DatabaseCursor* database_cursor )	{

	Rbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	Rbdb_DatabaseCursor*		cursor_copy	= Rbdb_DatabaseCursor_new( database_cursor->parent_database_cursor_controller );

	Rbdb_DatabaseSettingsController*				database_settings_controller				=	Rbdb_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	Rbdb_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	Rbdb_DatabaseSettingsController_cursorSettingsController( database_settings_controller );
	
	uint32_t	duplicate_flags	=	Rbdb_DatabaseCursorSettingsController_internal_duplicateFlags( database_cursor_settings_controller );

	int							connection_error	= 0;
	if ( ( connection_error = database_cursor->wrapped_bdb_cursor->dup(	database_cursor->wrapped_bdb_cursor, 
																																			& cursor_copy->wrapped_bdb_cursor,
																																			duplicate_flags ) ) ) {

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ), 
																									connection_error, 
																									"Rbdb_DatabaseCursor_copy" );
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
void Rbdb_DatabaseCursor_overwriteCurrentDataWithRecord(	Rbdb_DatabaseCursor*	database_cursor, 
																													Rbdb_Record*			record )	{

	Rbdb_DatabaseCursor_internal_writeRecord(	database_cursor, 
																						DB_CURRENT, 
																						record );
}

/****************************************
*  writeKeyDataPairAsCurrentRecord  *
****************************************/

//	DB_CURRENT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void Rbdb_DatabaseCursor_overwriteCurrentData(	Rbdb_DatabaseCursor*	database_cursor, 
																							Rbdb_Data*				data )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																																					DB_CURRENT,
																																					NULL,
																																					data );
	Rbdb_Record_free( & record );
}

/********************************************
*  writeRawKeyDataPairAsCurrentRecord  *
********************************************/

//	DB_CURRENT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void Rbdb_DatabaseCursor_overwriteCurrentDataWithRawData(	Rbdb_DatabaseCursor*	database_cursor, 
																								void*									data_raw,
																								uint32_t							data_size )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																																						DB_CURRENT,
																																						NULL,
																																						0,
																																						data_raw,
																																						data_size );
	Rbdb_Record_free( & record );
}

/****************************************
*  writeAfterCurrentRecord  *
****************************************/

//	DB_AFTER				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void Rbdb_DatabaseCursor_writeRecordAsDuplicateDataAfterCurrent(	Rbdb_DatabaseCursor*		database_cursor, 
																																	Rbdb_Record*						record )	{

	Rbdb_DatabaseCursor_internal_writeRecord(		database_cursor, 
																							DB_AFTER, 
																							record );
}

/********************************************
*  writeKeyDataPairAfterCurrentRecord  *
********************************************/

//	DB_AFTER				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void Rbdb_DatabaseCursor_writeDataAsDuplicateAfterCurrent(	Rbdb_DatabaseCursor*	database_cursor, 
																														Rbdb_Data*				data )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																																					DB_AFTER,
																																					NULL,
																																					data );
	Rbdb_Record_free( & record );
}

/************************************************
*  writeRawKeyDataPairAfterCurrentRecord  *
************************************************/

//	DB_AFTER				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void Rbdb_DatabaseCursor_writeRawDataAsDuplicateAfterCurrent(	Rbdb_DatabaseCursor*	database_cursor, 
																															void*									data_raw,
																															uint32_t							data_size )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																																						DB_AFTER,
																																						NULL,
																																						0,
																																						data_raw,
																																						data_size );
	Rbdb_Record_free( & record );
}

/******************************************
*  writeBeforeCurrentRecord  *
******************************************/

//	DB_BEFORE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void Rbdb_DatabaseCursor_writeRecordAsDuplicateBeforeCurrent(	Rbdb_DatabaseCursor*		database_cursor, 
																															Rbdb_Record*						record )	{

	Rbdb_DatabaseCursor_internal_writeRecord(		database_cursor, 
																							DB_BEFORE, 
																							record );
}

/********************************************
*  writeKeyDataPairBeforeCurrentRecord  *
********************************************/

//	DB_BEFORE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void Rbdb_DatabaseCursor_writeDataAsDuplicateBeforeCurrent(	Rbdb_DatabaseCursor*	database_cursor, 
																														Rbdb_Data*						data )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																																					DB_BEFORE,
																																					NULL,
																																					data );
	Rbdb_Record_free( & record );
}

/************************************************
*  writeRawKeyDataPairBeforeCurrentRecord  *
************************************************/

//	DB_BEFORE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void Rbdb_DatabaseCursor_writeRawDataAsDuplicateBeforeCurrent(	Rbdb_DatabaseCursor*	database_cursor, 
																																void*									data_raw,
																																uint32_t							data_size )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																																						DB_BEFORE,
																																						NULL,
																																						0,
																																						data_raw,
																																						data_size );
	Rbdb_Record_free( & record );
}


/*********************************
*  writeRecordBeforeAnyDuplicates  *
*********************************/

void Rbdb_DatabaseCursor_writeRecord(	Rbdb_DatabaseCursor*	database_cursor, 
																			Rbdb_Record*							record )	{

	Rbdb_DatabaseCursor_writeRecordAfterAnyDuplicates(	database_cursor,
																											record );
}

/*****************************************
*  writeKeyDataPair  *
*****************************************/

void Rbdb_DatabaseCursor_writeKeyDataPair(		Rbdb_DatabaseCursor*	database_cursor, 
																							Rbdb_Key*				key,
																							Rbdb_Data*				data )	{

	Rbdb_DatabaseCursor_writeKeyDataPairAfterAnyDuplicates(	database_cursor,
																													key,
																													data	);
}
	
/*****************************************
*  writeRawKeyDataPair  *
*****************************************/

void Rbdb_DatabaseCursor_writeRawKeyDataPair(	Rbdb_DatabaseCursor*	database_cursor, 
																							void*									key_raw,
																							uint32_t							key_size,
																							void*									data_raw,
																							uint32_t							data_size )	{
	
	Rbdb_DatabaseCursor_writeRawKeyDataPairAfterAnyDuplicates(	database_cursor,
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
void Rbdb_DatabaseCursor_writeRecordBeforeAnyDuplicates(	Rbdb_DatabaseCursor*	database_cursor, 
																													Rbdb_Record*							record )	{

	Rbdb_DatabaseCursor_internal_writeRecord(		database_cursor, 
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
void Rbdb_DatabaseCursor_writeKeyDataPairBeforeAnyDuplicates(		Rbdb_DatabaseCursor*	database_cursor, 
																																Rbdb_Key*							key,
																																Rbdb_Data*						data )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																																					DB_KEYFIRST,
																																					key,
																																					data );
	Rbdb_Record_free( & record );
}

/*****************************************
*  writeRawKeyDataPairAsFirstRecord  *
*****************************************/

//	If the key already exists in the database and no duplicate sort function has been specified, 
//	the inserted data item is added as the first of the data items for that key.
//	If duplicate sort function has been specified, it will be used rather than inserting before duplicates. 
//	DB_KEYFIRST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void Rbdb_DatabaseCursor_writeRawKeyDataPairBeforeAnyDuplicates(	Rbdb_DatabaseCursor*	database_cursor, 
																																	void*									key_raw,
																																	uint32_t							key_size,
																																	void*									data_raw,
																																	uint32_t							data_size )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																																						DB_KEYFIRST,
																																						key_raw,
																																						key_size,
																																						data_raw,
																																						data_size );
	Rbdb_Record_free( & record );
}

/********************************
*  writeDataAsLastRecord  *
********************************/

//	If the key already exists in the database and no duplicate sort function has been specified, 
//	the inserted data item is added as the first of the data items for that key.
//	If duplicate sort function has been specified, it will be used rather than inserting after duplicates. 
//	DB_KEYLAST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void Rbdb_DatabaseCursor_writeRecordAfterAnyDuplicates(	Rbdb_DatabaseCursor*	database_cursor, 
																												Rbdb_Record*							record )	{

	Rbdb_DatabaseCursor_internal_writeRecord(	database_cursor, 
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
void Rbdb_DatabaseCursor_writeKeyDataPairAfterAnyDuplicates(	Rbdb_DatabaseCursor*	database_cursor, 
																															Rbdb_Key*							key,
																															Rbdb_Data*						data )	{
	
	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
																																					DB_KEYLAST,
																																					key,
																																					data );
	Rbdb_Record_free( & record );
}

/********************************************
*  writeRawKeyDataPairAsLastRecord  *
********************************************/

//	If the key already exists in the database and no duplicate sort function has been specified, 
//	the inserted data item is added as the first of the data items for that key.
//	If duplicate sort function has been specified, it will be used rather than inserting after duplicates. 
//	DB_KEYLAST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
void Rbdb_DatabaseCursor_writeRawKeyDataPairAfterAnyDuplicates(	Rbdb_DatabaseCursor*	database_cursor, 
																																void*									key_raw,
																																uint32_t							key_size,
																																void*									data_raw,
																																uint32_t							data_size )	{
	
	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
																																						DB_KEYLAST,
																																						key_raw,
																																						key_size,
																																						data_raw,
																																						data_size );
	Rbdb_Record_free( & record );
}


/**************************************
*  writeOnlyIfNonExisting  *
**************************************/

//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
BOOL Rbdb_DatabaseCursor_writeRecordOnlyIfNotInDatabase(	Rbdb_DatabaseCursor*		database_cursor, 
																													Rbdb_Record*						record )	{

	record	=	Rbdb_DatabaseCursor_internal_writeRecord(	database_cursor, 
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
BOOL Rbdb_DatabaseCursor_writeKeyDataPairOnlyIfNotInDatabase(	Rbdb_DatabaseCursor*	database_cursor, 
																															Rbdb_Key*							key,
																															Rbdb_Data*						data )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_writeKeyDataPair(	database_cursor, 
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
BOOL Rbdb_DatabaseCursor_writeRawKeyDataPairOnlyIfNotInDatabase(	Rbdb_DatabaseCursor*	database_cursor, 
																																	void*									key_raw,
																																	uint32_t							key_size,
																																	void*									data_raw,
																																	uint32_t							data_size )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_writeRawKeyDataPair(	database_cursor, 
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

BOOL Rbdb_DatabaseCursor_keyExists(	Rbdb_DatabaseCursor*		database_cursor, 
																		Rbdb_Key*								key )	{

	Rbdb_Record*	record	=	Rbdb_Record_internal_newFromKeyData(	database_cursor->parent_database_cursor_controller->parent_database,
																																key,
																																NULL	);

	record = 	Rbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																													DB_SET, 
																													record );
	
	BOOL	exists_in_database	=	record->data->wrapped_bdb_dbt->size ? TRUE : FALSE;
	
	Rbdb_Record_free( & record );
	
	if ( exists_in_database )	{
		return TRUE;
	}
	return FALSE;
}

/*****************************
*  recordExistsForRawKey  *
*****************************/

BOOL Rbdb_DatabaseCursor_rawKeyExists(	Rbdb_DatabaseCursor*		database_cursor, 
																				void*										key_raw,
																				uint32_t								key_size )	{

	Rbdb_Key*	key	=	Rbdb_Key_new( NULL );
	
	key->wrapped_bdb_dbt->data	= key_raw;
	key->wrapped_bdb_dbt->size	= key_size;

	return Rbdb_DatabaseCursor_keyExists(	database_cursor,
																				key );
}

/*************************
*  retrieveRecord  *
*************************/

Rbdb_Record* Rbdb_DatabaseCursor_retrieveRecord(	Rbdb_DatabaseCursor*		database_cursor, 
																									Rbdb_Record*						record )	{

	return Rbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																											DB_SET, 
																											record );
}

/*****************************
*  retrieveKey  *
*****************************/

Rbdb_Record* Rbdb_DatabaseCursor_retrieveKey(	Rbdb_DatabaseCursor*		database_cursor, 
																							Rbdb_Key*								key_data )	{

	Rbdb_Record*	record	=	Rbdb_Record_new( NULL );
	
	Rbdb_Record_setKey(	record,
											key_data );
	
	if (		Rbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																												DB_SET, 
																												record )->result == FALSE
			||	record->result == DB_KEYEMPTY )	{
		Rbdb_Record_free( & record );
	}
	return record;
}

/********************************
*  retrieveRawKey  *
********************************/

//	DB_SET				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Move the database_cursor to specified location
Rbdb_Record* Rbdb_DatabaseCursor_retrieveRawKey(	Rbdb_DatabaseCursor*		database_cursor, 
																									void*										key_raw,
																									uint32_t								key_size )	{

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_SET, 
																															key_raw,
																															key_size, 
																															NULL,
																															0 );
}

/*********************************************
*  retrieveMatchingKeyDataPair  *
*********************************************/

Rbdb_Record* Rbdb_DatabaseCursor_retrieveMatchingKeyDataPair(	Rbdb_DatabaseCursor*		database_cursor, 
																															Rbdb_Key*								key_data,
																															Rbdb_Data*							data )	{

	Rbdb_Record*	record	=	Rbdb_Record_new( NULL );
	
	Rbdb_Record_setKey(	record,
											key_data );
	Rbdb_Record_setData(	record,
												data );

	if (		Rbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																												DB_GET_BOTH, 
																												record )->result == FALSE
			||	record->result == DB_KEYEMPTY )	{
		Rbdb_Record_free( & record );
	}
	return record;
}

/************************************************
*  retrieveMatchingRawKeyDataPair  *
************************************************/

//	DB_GET_BOTH				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	We need to add key specification here
Rbdb_Record* Rbdb_DatabaseCursor_retrieveMatchingRawKeyDataPair(	Rbdb_DatabaseCursor*		database_cursor,
																																	void*										key_raw,
																																	uint32_t								key_size,
																																	void*										data_raw,
																																	uint32_t								data_size )	{

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
Rbdb_Record* Rbdb_DatabaseCursor_retrieveRecordWithNumber(	Rbdb_DatabaseCursor* 	database_cursor,
																														db_recno_t*									record_id )	{

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																															DB_SET_RECNO,
																															record_id, 
																															sizeof( uint32_t ),
																															NULL,
																															0 );
}

/****************************************
*  retrieveRecordWithNumberInKey  *
****************************************/

Rbdb_Record* Rbdb_DatabaseCursor_retrieveRecordWithNumberAsKey(	Rbdb_DatabaseCursor* 	database_cursor,
																																Rbdb_Key*				key_with_record_number )	{

	//	We should probably make sure here that record ID is an int

	Rbdb_Record*	record	=	Rbdb_Record_new( NULL );
	
	Rbdb_Record_setKey(	record,
											key_with_record_number );

	if (		Rbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																												DB_SET_RECNO, 
																												record )->result == FALSE
			||	record->result == DB_KEYEMPTY )	{
		Rbdb_Record_free( & record );
	}
	return record;
}

/*****************************************
*  retrievePartialRawKey  *
*****************************************/

//	DB_SET_RANGE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Must be Btree and it must have been created with the DB_RECNUM flag.
//	Permits partial key matches and range searches by returning the smallest item matching or including the key
Rbdb_Record* Rbdb_DatabaseCursor_retrievePartialRawKey(	Rbdb_DatabaseCursor*		database_cursor,
																												void*										key_raw,
																												uint32_t								key_size )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																																								DB_SET_RANGE, 
																																								key_raw, 
																																								key_size,
																																								NULL,
																																								0 );

	if ( record->data->wrapped_bdb_dbt->size == 0 )	{
		Rbdb_Record_free( & record );
	}
	return record;
}

/**************************************
*  retrievePartialKeyDataPair  *
**************************************/

//	DB_GET_BOTH_RANGE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Permits partial data matches and range searches by returning the smallest item matching or including the data
Rbdb_Record* Rbdb_DatabaseCursor_retrievePartialKey(	Rbdb_DatabaseCursor*		database_cursor,
																											Rbdb_Key*								partial_key )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_retrieveKeyDataPair(	database_cursor, 
																																						DB_SET_RANGE, 
																																						partial_key, 
																																						NULL  );

	if ( record->data->wrapped_bdb_dbt->size == 0 )	{
		Rbdb_Record_free( & record );
	}
	return record;
}

/**************************************
*  retrievePartialKeyInRecord  *
**************************************/

Rbdb_Record* Rbdb_DatabaseCursor_retrievePartialKeyInRecord(	Rbdb_DatabaseCursor*		database_cursor,
																															Rbdb_Record*						record  )	{
	
	record	=	Rbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																													DB_SET_RANGE, 
																													record  );
	return record;
}

/**************************************************
*  retrieveRawKeyPartialDataPair  *
**************************************************/

Rbdb_Record* Rbdb_DatabaseCursor_retrieveDuplicateMatchingRawData(	Rbdb_DatabaseCursor*		database_cursor,
																																		void*										key_raw,
																																		uint32_t								key_size,
																																		void*										data_raw,
																																		uint32_t								data_size )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
																																								DB_GET_BOTH_RANGE, 
																																								key_raw, 
																																								key_size,
																																								data_raw,
																																								data_size );

	if ( record->data->wrapped_bdb_dbt->size == 0 )	{
		Rbdb_Record_free( & record );
	}
	return record;
}

/**************************************
*  retrievePartialKeyDataPair  *
**************************************/

//	DB_GET_BOTH_RANGE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
//	Permits partial data matches and range searches by returning the smallest item matching or including the data
Rbdb_Record* Rbdb_DatabaseCursor_retrieveDuplicateMatchingPartialData(	Rbdb_DatabaseCursor*		database_cursor,
																																				Rbdb_Key*								partial_key,
																																				Rbdb_Data*							partial_data )	{

	Rbdb_Record*	record	=	Rbdb_DatabaseCursor_internal_retrieveKeyDataPair(	database_cursor, 
																																						DB_GET_BOTH_RANGE, 
																																						partial_key, 
																																						partial_data  );

	if ( record->data->wrapped_bdb_dbt->size == 0 )	{
		Rbdb_Record_free( & record );
	}
	return record;
}

/**************************************
*  retrievePartialKeyDataPairInRecord  *
**************************************/

Rbdb_Record* Rbdb_DatabaseCursor_retrieveDuplicateMatchingPartialDataInRecord(	Rbdb_DatabaseCursor*		database_cursor,
																																								Rbdb_Record*						record  )	{
	
	uint32_t	partial_data_size	=	Rbdb_Record_dataSize( record );
	record	=	Rbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor, 
																													DB_GET_BOTH_RANGE, 
																													record  );
	
	if ( Rbdb_Record_dataSize( record ) == partial_data_size )	{
		Rbdb_Record_setDataFromRawData( record,
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
Rbdb_Record* Rbdb_DatabaseCursor_retrieveCurrent( Rbdb_DatabaseCursor* database_cursor )	{

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
BOOL Rbdb_DatabaseCursor_setToFirst( Rbdb_DatabaseCursor* database_cursor )	{
	Rbdb_Record*	first_record	=	Rbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	
	Rbdb_DatabaseCursor_internal_retrieveFirst(	database_cursor,
																							first_record );
	
	BOOL has_record	=	FALSE;
	if ( first_record->result )	{
		has_record	=	TRUE;
	}

	Rbdb_Record_free( & first_record );

	return has_record;
}

/****************
*  first  *
****************/

//	DB_FIRST				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
Rbdb_Record* Rbdb_DatabaseCursor_retrieveFirst( Rbdb_DatabaseCursor* database_cursor )	{

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
Rbdb_Record* Rbdb_DatabaseCursor_retrieveLast( Rbdb_DatabaseCursor* database_cursor )	{

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor,
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
Rbdb_Record* Rbdb_DatabaseCursor_retrieveNext( Rbdb_DatabaseCursor* database_cursor )	{

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
Rbdb_Record* Rbdb_DatabaseCursor_retrieveNextDuplicate( Rbdb_DatabaseCursor* database_cursor )	{

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
Rbdb_Record* Rbdb_DatabaseCursor_retrieveNextNonDuplicate( Rbdb_DatabaseCursor* database_cursor )	{

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
Rbdb_Record* Rbdb_DatabaseCursor_retrievePrevious( Rbdb_DatabaseCursor* database_cursor )	{

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
Rbdb_Record* Rbdb_DatabaseCursor_retrievePreviousDuplicate( Rbdb_DatabaseCursor* database_cursor )	{

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
Rbdb_Record* Rbdb_DatabaseCursor_retrievePreviousNonDuplicate( Rbdb_DatabaseCursor* database_cursor )	{

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
Rbdb_Record* Rbdb_DatabaseCursor_retrieveCurrentRecordNumber( Rbdb_DatabaseCursor* database_cursor )	{

	Rbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	Rbdb_DatabaseSettingsController*			database_settings_controller			=	Rbdb_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	Rbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
	DBTYPE																database_type											=	Rbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

	//	Make sure we have DB_RECNO
	if ( database_type != DB_RECNO )	{

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ),
																									RP_ERROR_NOT_DB_QUEUE_OR_DB_RECNO, 
																									"Rbdb_Database_append" );
	}

	return Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	database_cursor, 
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
db_recno_t Rbdb_DatabaseCursor_countDuplicatesForCurrentKey( Rbdb_DatabaseCursor* database_cursor )	{

	Rbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	db_recno_t			number_data_items_for_cursor;		

	Rbdb_Environment*						environment	= database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;

	Rbdb_DatabaseSettingsController*				database_settings_controller				=	Rbdb_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	Rbdb_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	Rbdb_DatabaseSettingsController_cursorSettingsController( database_settings_controller );
	
	int	count_data_items_flags	=	Rbdb_DatabaseCursorSettingsController_internal_countDataItemsFlags( database_cursor_settings_controller );

	int	connection_error	= 0;
	if ( ( connection_error = database_cursor->wrapped_bdb_cursor->count(	database_cursor->wrapped_bdb_cursor, 
																																				& number_data_items_for_cursor, 
																																				count_data_items_flags ) ) ) {

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ), 
																									connection_error, 
																									"Rbdb_DatabaseCursor_itemCountForCurrentKey" );
	}

	return number_data_items_for_cursor;
}

/************************
*  resetIteration  *
************************/

void Rbdb_DatabaseCursor_resetIteration( Rbdb_DatabaseCursor* database_cursor )	{
	database_cursor->iteration_started	=	FALSE;
}

/************************
*  resetIteration  *
************************/

void Rbdb_DatabaseCursor_resetDuplicateIteration( Rbdb_DatabaseCursor* database_cursor )	{
	database_cursor->duplicate_iteration_started	=	FALSE;
}
	
/****************************
*  iterate  *
****************************/

// if we have duplicates for db, each iterates duplicates
// if we have no duplicates for db, each iterates records
Rbdb_Record* Rbdb_DatabaseCursor_iterate(	Rbdb_DatabaseCursor*	database_cursor,
																					Rbdb_Record*					record )	{

	Rbdb_DatabaseCursor_internal_ensureOpen( database_cursor );
	
	//	if we have a null record, instantiate it
	//	caller responsible for freeing
	if ( record == NULL )	{
		record = Rbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}
	
	//	Args:
	//	0 args: intelligent iteration
	//	1 arg: if true - force iterate all 

	if ( database_cursor->iteration_started == FALSE )	{
		Rbdb_DatabaseCursor_internal_retrieveCurrent(	database_cursor,
																									record );
		database_cursor->iteration_started = TRUE;
	}
	else {
	
		Rbdb_DatabaseCursor_internal_retrieveNext(	database_cursor,
																								record );
	}
	
	if ( record->result == FALSE )	{
		Rbdb_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return Rbdb_DatabaseCursor_iterate(	database_cursor,
																				record );
	}

	return record;
}

/****************************
*  iterateDuplicates  *
****************************/

//	iterates all records with one or more duplicates
Rbdb_Record* Rbdb_DatabaseCursor_iterateDuplicates( Rbdb_DatabaseCursor*	database_cursor,
																										Rbdb_Record*					record  )	{
	
	Rbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	//	if we have a null record, instantiate it
	//	caller responsible for freeing
	if ( record == NULL )	{
		record = Rbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}

	if ( database_cursor->duplicate_iteration_started == FALSE )	{
		Rbdb_DatabaseCursor_internal_retrieveCurrent( database_cursor,
																									record );
		database_cursor->duplicate_iteration_started = TRUE;
	}
	else {
		Rbdb_DatabaseCursor_internal_retrieveNextDuplicate( database_cursor,
																												record );		
	}
	
	if ( record->result == FALSE )	{
		Rbdb_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return Rbdb_DatabaseCursor_iterateDuplicates(	database_cursor,
																									record );
	}
	
	return record;
}

/****************************
*  iterateKeys  *
****************************/

//	iterates all records without duplicates
Rbdb_Record* Rbdb_DatabaseCursor_iterateKeys( Rbdb_DatabaseCursor* database_cursor,
																							Rbdb_Record*					record  )	{
	
	Rbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	//	if we have a null record, instantiate it
	//	caller responsible for freeing
	if ( record == NULL )	{
		record = Rbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}

	if ( database_cursor->iteration_started == FALSE )	{
		Rbdb_DatabaseCursor_internal_retrieveCurrent( database_cursor,
																									record );
		database_cursor->iteration_started	=	TRUE;
	}
	else {
		Rbdb_DatabaseCursor_internal_retrieveNextNonDuplicate(	database_cursor,
																														record );		
	}
	
	if ( record->result == FALSE )	{
		Rbdb_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return Rbdb_DatabaseCursor_iterateKeys(	database_cursor,
																						record );
	}
	
	return record;
}

/****************************
*  slice  *
****************************/

//	iterates a slice of records
Rbdb_Record* Rbdb_DatabaseCursor_slice( Rbdb_DatabaseCursor*	database_cursor,
																				uint32_t							length,
																				Rbdb_Record*					record )	{

	if ( record == NULL )	{
		database_cursor->slice_length	=	length - 1;
		record = Rbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}
	else {
		database_cursor->slice_length--;
	}

	
	if ( database_cursor->iteration_started == FALSE )	{
		Rbdb_DatabaseCursor_internal_retrieveCurrent(	database_cursor,
																									record );
		database_cursor->iteration_started = TRUE;
	}
	else {
	
		Rbdb_DatabaseCursor_internal_retrieveNext(	database_cursor,
																								record );
	}
	
	if (		record->result == FALSE
			||	database_cursor->slice_length == 0 )	{

		Rbdb_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return Rbdb_DatabaseCursor_iterateKeys(	database_cursor,
																						record );
	}

	return record;
}

/****************************
*  sliceKeys  *
****************************/

//	iterates a slice of records
Rbdb_Record* Rbdb_DatabaseCursor_sliceKeys( Rbdb_DatabaseCursor*	database_cursor,
																						uint32_t							length,
																						Rbdb_Record*					record )	{

	if ( record == NULL )	{
		database_cursor->slice_length	=	length - 1;
		record = Rbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}
	else {
		database_cursor->slice_length--;
	}
	
	if ( database_cursor->iteration_started == FALSE )	{
		Rbdb_DatabaseCursor_internal_retrieveCurrent( database_cursor,
																									record );
		database_cursor->iteration_started	=	TRUE;
	}
	else {
		Rbdb_DatabaseCursor_internal_retrieveNextNonDuplicate(	database_cursor,
																														record );		
	}
	
	if (		record->result == FALSE
			||	database_cursor->slice_length == 0 )	{

		Rbdb_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return Rbdb_DatabaseCursor_iterateKeys(	database_cursor,
																						record );
	}

	return record;
}

/****************************
*  sliceDuplicates  *
****************************/

//	iterates a slice of records
Rbdb_Record* Rbdb_DatabaseCursor_sliceDuplicates( Rbdb_DatabaseCursor*	database_cursor,
																									uint32_t							length,
																									Rbdb_Record*					record )	{

	if ( record == NULL )	{
		database_cursor->slice_length	=	length - 1;
		record = Rbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	}
	else {
		database_cursor->slice_length--;
	}

	if ( database_cursor->duplicate_iteration_started == FALSE )	{
		Rbdb_DatabaseCursor_internal_retrieveCurrent( database_cursor,
																									record );
		database_cursor->duplicate_iteration_started = TRUE;
	}
	else {
		Rbdb_DatabaseCursor_internal_retrieveNextDuplicate( database_cursor,
																												record );		
	}
	
	if (		record->result == FALSE
			||	database_cursor->slice_length == 0 )	{

		Rbdb_Record_free( & record );
	}
	//	if we have an empty key, iterate to the next record (until we have no key)
	else if ( record->result == DB_KEYEMPTY )	{
		return Rbdb_DatabaseCursor_iterateKeys(	database_cursor,
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
Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteCurrentRecord( Rbdb_DatabaseCursor*	database_cursor )	{

	int					connection_error	= 0;

	Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database );
	Rbdb_DatabaseCursorSettingsController*						database_cursor_settings_controller							=	Rbdb_DatabaseSettingsController_cursorSettingsController( database_settings_controller );
	Rbdb_DatabaseCursorReadWriteSettingsController*		database_cursor_record_read_write_settings_controller	=	Rbdb_DatabaseCursorSettingsController_readWriteSettingsController( database_cursor_settings_controller );
	
	uint32_t		flags	=	Rbdb_DatabaseCursorReadWriteSettingsController_internal_deleteFlags( database_cursor_record_read_write_settings_controller );
	
	if ( ( connection_error = database_cursor->wrapped_bdb_cursor->del(	database_cursor->wrapped_bdb_cursor, 
																																			flags ) ) ) {

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ), 
																									connection_error, 
																									"Rbdb_DatabaseCursor_deleteCurrentRecord" );
		return NULL;
	}
	
	return database_cursor;
}

/*****************************
*  deleteRecordWithKey  *
*****************************/

Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteKey(	Rbdb_DatabaseCursor*		database_cursor,
																										Rbdb_Key*								key	)	{
	
	//	Set current record to key/data pair
	Rbdb_DatabaseCursor_retrieveKey(	database_cursor,
																		key );
	
	//	Delete current record
	Rbdb_DatabaseCursor_deleteCurrentRecord( database_cursor );
	
	return database_cursor;
}

/*****************************
*  deleteRecordWithRawKey  *
*****************************/

Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteRawKey(	Rbdb_DatabaseCursor*	database_cursor,
																												void*									key_raw,
																												uint32_t							key_size )	{
	Rbdb_Key*	key	=	Rbdb_Key_new( NULL );
	Rbdb_Key_setKeyData(	key,
												key_raw,
												key_size );
							
	Rbdb_DatabaseCursor_deleteKey(	database_cursor,
																	key );
	return database_cursor;
}

/************************************
*  deleteRecordWithKeyDataPair  *
************************************/

Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteKeyDataPair(	Rbdb_DatabaseCursor*	database_cursor,
																														Rbdb_Key*							key,
																														Rbdb_Data*						data	)	{
	
	//	Set current record to key/data pair
	Rbdb_DatabaseCursor_retrieveMatchingKeyDataPair(	database_cursor,
																										key,
																										data );
	
	//	Delete current record
	Rbdb_DatabaseCursor_deleteCurrentRecord( database_cursor );
	
	return database_cursor;
}

/*************************************
*  deleteRecordWithRawKeyDataPair  *
*************************************/

Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteRawKeyDataPair(	Rbdb_DatabaseCursor*	database_cursor,
																																void*									key_raw,
																																uint32_t							key_size,
																																void*									data_raw,
																																uint32_t							data_size	)	{

	Rbdb_Record*	record	=	Rbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	Rbdb_Record_setKeyFromRawKey(	record,
																key_raw,
																key_size );
	Rbdb_Record_setDataFromRawData(	record,
																	data_raw,
																	data_size );
	Rbdb_DatabaseCursor_deleteKeyDataPair(	database_cursor,
																					record->key,
																					record->data );
	return database_cursor;
}

/******************************
*  deleteRecordWithNumber  *
******************************/

Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteRecordNumber(	Rbdb_DatabaseCursor*	database_cursor,
																															db_recno_t*				record_number	)	{
	
	//	Set current record to record number
	Rbdb_DatabaseCursor_retrieveRawKey( database_cursor ,
																			record_number,
																			sizeof( uint32_t ) );
	
	//	Delete current record
	return Rbdb_DatabaseCursor_deleteCurrentRecord( database_cursor );
}

/********************
*  deleteRecord  *
********************/

Rbdb_DatabaseCursor* Rbdb_DatabaseCursor_deleteRecord(	Rbdb_DatabaseCursor*	database_cursor,
 															Rbdb_Record*			record	)	{
	
	//	Set current record to data
	Rbdb_DatabaseCursor_retrieveRecord( database_cursor ,
																			record );
	
	//	Delete current record
	return Rbdb_DatabaseCursor_deleteCurrentRecord( database_cursor );
}


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Write Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************************
*  ensureInitialized  *
***********************/

void Rbdb_DatabaseCursor_internal_ensureOpen( Rbdb_DatabaseCursor* database_cursor )	{
	
	if ( ! Rbdb_DatabaseCursor_isOpen( database_cursor ) )	{
		Rbdb_DatabaseCursor_open( database_cursor );
	}
}

/*******************
*  writeData  *
*******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_put.html
Rbdb_Record* Rbdb_DatabaseCursor_internal_writeRecord(	Rbdb_DatabaseCursor*	database_cursor, 
																												uint32_t				flags,
																												Rbdb_Record*			record )	{

	Rbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

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
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment ), 
																									connection_error, 
																									"Rbdb_DatabaseCursor_internal_write" );
	}
	return record;
}

/**************************
*  writeKeyDataPair  *
**************************/

Rbdb_Record* Rbdb_DatabaseCursor_internal_writeKeyDataPair(	Rbdb_DatabaseCursor*	database_cursor, 
																														uint32_t							flags,
																														Rbdb_Key*							key,
																														Rbdb_Data*						data )	{

	Rbdb_Record*				record			= Rbdb_Record_internal_newFromKeyData(	database_cursor->parent_database_cursor_controller->parent_database,
																																					key,
																																					data	);

	return Rbdb_DatabaseCursor_internal_writeRecord(	database_cursor,
																										flags,
																										record );
}

/******************************
*  writeRawKeyDataPair  *
******************************/

Rbdb_Record* Rbdb_DatabaseCursor_internal_writeRawKeyDataPair(	Rbdb_DatabaseCursor*	database_cursor, 
																																uint32_t							flags,
																																void*									key,
																																uint32_t							key_size,
																																void*									data,
																																uint32_t							data_size )	{

	Rbdb_Record*				record			= Rbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );
	
	record->key->wrapped_bdb_dbt->data	= key;
	record->key->wrapped_bdb_dbt->size	= key_size;
	record->data->wrapped_bdb_dbt->data			= data;
	record->data->wrapped_bdb_dbt->size			= data_size;
	
	return 	Rbdb_DatabaseCursor_internal_writeRecord(	database_cursor,
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
Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveRawKeyDataPair(	Rbdb_DatabaseCursor*		database_cursor, 
																																	uint32_t								flag, 
																																	void*										key,
																																	uint32_t								key_size,
																																	void*										data,
																																	uint32_t								data_size )	{

	Rbdb_Record*				record				= Rbdb_Record_new( database_cursor->parent_database_cursor_controller->parent_database );

	if ( key != NULL )	{
		record->key->wrapped_bdb_dbt->data = key;
		record->key->wrapped_bdb_dbt->size = key_size;
	}
		
	//	If we have data we're using to retrieve, load it into the DBT
	if ( data != NULL )	{
		
		record->data->wrapped_bdb_dbt->data = data;
		record->data->wrapped_bdb_dbt->size = data_size;
		
	}

	return Rbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor,
																											flag,
																											record );
}

/**************************
*  retrieveRecord  *
**************************/

Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveKeyDataPair(	Rbdb_DatabaseCursor*		database_cursor, 
																																uint32_t								flags, 
																																Rbdb_Key*								key,
																																Rbdb_Data*							data	)	{

	Rbdb_Record*	record	=	Rbdb_Record_internal_newFromKeyData(	database_cursor->parent_database_cursor_controller->parent_database,
																																key,
																																data );
	
	return Rbdb_DatabaseCursor_internal_retrieveRecord(	database_cursor,
																											flags,
																											record );
}

/**************************
*  retrieveRecord  *
**************************/

Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveRecord(	Rbdb_DatabaseCursor*		database_cursor, 
																													uint32_t								flags, 
																													Rbdb_Record*						record)	{

	Rbdb_DatabaseCursor_internal_ensureOpen( database_cursor );

	Rbdb_Environment*	environment	= database_cursor->parent_database_cursor_controller->parent_database->parent_database_controller->parent_environment;
	
	//	We have a flag describing what type of cursor operation we are executing; we need to add in flags
	//	that might apply to all situations.
	flags	|=	Rbdb_DatabaseCursorReadWriteSettingsController_internal_retrieveFlags(	Rbdb_DatabaseCursorSettingsController_readWriteSettingsController( Rbdb_DatabaseSettingsController_cursorSettingsController( Rbdb_Database_settingsController( database_cursor->parent_database_cursor_controller->parent_database ) ) ) );

	int		connection_error	= 0;

	//	If we have a secondary database we are using a secondary key and retrieving a primary key/data pair
	if ( Rbdb_Database_isSecondary( database_cursor->parent_database_cursor_controller->parent_database ) )	{

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

				Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ), 
																											connection_error, 
																											"Rbdb_DatabaseCursor_internal_retrieveRecord" );
			
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

				Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ), 
																											connection_error, 
																											"Rbdb_DatabaseCursor_internal_retrieveRecord" );
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

Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveFirst(	Rbdb_DatabaseCursor*	cursor,
																													Rbdb_Record*					record )	{
	
	return Rbdb_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_FIRST,
																											record );
}

/********************
*  retrieveCurrent  *
********************/

Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveCurrent(	Rbdb_DatabaseCursor*	cursor,
																														Rbdb_Record*					record )	{
	
	return Rbdb_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_CURRENT,
																											record );
}

/*****************
*  retrieveNext  *
*****************/

Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveNext(	Rbdb_DatabaseCursor*	cursor,
																												Rbdb_Record*					record )	{

	return Rbdb_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_NEXT,
																											record );
}

/**************************
*  retrieveNextDuplicate  *
**************************/

Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveNextDuplicate(	Rbdb_DatabaseCursor*	cursor,
																																	Rbdb_Record*					record )	{

	return Rbdb_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_NEXT_DUP,
																											record );
}

/*****************************
*  retrieveNextNonDuplicate  *
*****************************/

Rbdb_Record* Rbdb_DatabaseCursor_internal_retrieveNextNonDuplicate(	Rbdb_DatabaseCursor*	cursor,
																																		Rbdb_Record*					record )	{

	return Rbdb_DatabaseCursor_internal_retrieveRecord(	cursor,
																											DB_NEXT_NODUP,
																											record );
}

