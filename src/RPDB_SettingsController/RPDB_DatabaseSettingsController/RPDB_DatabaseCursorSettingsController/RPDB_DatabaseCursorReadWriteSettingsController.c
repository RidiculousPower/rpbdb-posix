/*
 *		RPDB::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorReadWriteSettingsController
 *		RPDB::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorReadWriteSettingsController
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseCursorReadWriteSettingsController.h"
#include "RPDB_DatabaseCursorReadWriteSettingsController_internal.h"

#include "RPDB_Environment.h"
#include "RPDB_SettingsController.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_DatabaseCursorReadWriteSettingsController* RPDB_DatabaseCursorReadWriteSettingsController_new( RPDB_DatabaseCursorSettingsController* cursor_settings_controller )	{

	RPDB_DatabaseCursorReadWriteSettingsController*		cursor_write_retrieve_settings_controller = calloc( 1, sizeof( RPDB_DatabaseCursorReadWriteSettingsController ) );
	
	cursor_write_retrieve_settings_controller->parent_database_cursor_settings_controller = cursor_settings_controller;
	
	return cursor_write_retrieve_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseCursorReadWriteSettingsController_free(	RPDB_DatabaseCursorReadWriteSettingsController** database_cursor_record_read_write_settings_controller )	{

	free( *database_cursor_record_read_write_settings_controller );
	*database_cursor_record_read_write_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseCursorReadWriteSettingsController_parentEnvironment(	RPDB_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller )	{
	return database_cursor_record_read_write_settings_controller->parent_database_cursor_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseCursorReadWriteSettingsController_parentDatabase(	RPDB_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller )	{
	return database_cursor_record_read_write_settings_controller->parent_database_cursor_settings_controller->parent_database_settings_controller->parent_database;
}

/***************************************
*  parentDatabaseCursor  *
***************************************/
RPDB_DatabaseCursor* RPDB_DatabaseCursorReadWriteSettingsController_parentDatabaseCursor(	RPDB_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller )	{
	return database_cursor_record_read_write_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/********************
*  permitWrite  *
********************/

//	DB_WRITECURSOR			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
BOOL RPDB_DatabaseCursorReadWriteSettingsController_permitWrite( RPDB_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->permit_write == TRUE )	{
		return DB_WRITECURSOR;
	}

	return FALSE;
}

	/************************
	*  permitWriteOn  *
	************************/

	void RPDB_DatabaseCursorReadWriteSettingsController_turnPermitWriteOn( RPDB_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller )	{
		cursor_write_retrieve_settings_controller->permit_write = TRUE;
	}

	/************************
	*  permitWriteOff  *
	************************/

	void RPDB_DatabaseCursorReadWriteSettingsController_turnPermitWriteOff( RPDB_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller )	{
		cursor_write_retrieve_settings_controller->permit_write = FALSE;
	}

/********************
*  ignoreLease  *
********************/

//	DB_IGNORE_LEASE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL RPDB_DatabaseCursorReadWriteSettingsController_ignoreLease( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->ignore_lease == TRUE )	{
		return DB_IGNORE_LEASE;
	}
	return FALSE;
}

	/************************
	*  ignoreLeaseOn  *
	************************/

	void RPDB_DatabaseCursorReadWriteSettingsController_ignoreLeaseOn( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

		cursor_write_retrieve_settings_controller->ignore_lease = TRUE;
	}

	/************************
	*  ignoreLeaseOff  *
	************************/

	void RPDB_DatabaseCursorReadWriteSettingsController_ignoreLeaseOff( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

		cursor_write_retrieve_settings_controller->ignore_lease = FALSE;
	}

/************************************
*  writeLocksInsteadOfReadLocks  *
************************************/

//	DB_RMW					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL RPDB_DatabaseCursorReadWriteSettingsController_writeLocksInsteadOfReadLocks( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->write_locks_instead_of_read_locks == TRUE )	{
		return DB_RMW;
	}
	return FALSE;
}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	****************************************/

	void RPDB_DatabaseCursorReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{
		cursor_write_retrieve_settings_controller->write_locks_instead_of_read_locks = TRUE;
	}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	****************************************/

	void RPDB_DatabaseCursorReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{
		cursor_write_retrieve_settings_controller->write_locks_instead_of_read_locks = FALSE;
	}

/********************************
*  returnMultipleDataItems  *
********************************/

//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL RPDB_DatabaseCursorReadWriteSettingsController_returnMultipleDataItems( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->multiple_data_items == TRUE )	{
		return DB_MULTIPLE;
	}
	return FALSE;
}

	/************************************
	*  returnMultipleDataItemsOn  *
	************************************/

	void RPDB_DatabaseCursorReadWriteSettingsController_turnReturnMultipleDataItemsOn( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{
		
		cursor_write_retrieve_settings_controller->multiple_data_items = TRUE;
	}

	/************************************
	*  returnMultipleDataItemsOff  *
	************************************/

	void RPDB_DatabaseCursorReadWriteSettingsController_turnReturnMultipleDataItemsOff( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{
		
		cursor_write_retrieve_settings_controller->multiple_data_items = FALSE;
	}

/***********************************
*  returnMultipleKeyDataPairs  *
***********************************/

//	FIX - this is only for put, and only to organize key/data pairs in a particular way. We should hide this functionality and only 
//	enable one multiple data item. 

//	In the case of Btree or Hash databases, the multiple key and data pairs can be iterated over using the DB_MULTIPLE_KEY_NEXT macro.
//	In the case of Queue or Recno databases, the multiple record number and data pairs can be iterated over using the DB_MULTIPLE_RECNO_NEXT macro.
//	DB_MULTIPLE_KEY			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL RPDB_DatabaseCursorReadWriteSettingsController_returnMultipleKeyDataPairs( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->return_multiple_key_data_pairs == TRUE )	{
		return DB_MULTIPLE_KEY;
	}
	return FALSE;
}

	/***************************************
	*  returnMultipleKeyDataPairsOn  *
	***************************************/

	void RPDB_DatabaseCursorReadWriteSettingsController_turnReturnMultipleKeyDataPairsOn( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

		cursor_write_retrieve_settings_controller->return_multiple_key_data_pairs = TRUE;
	}

	/***************************************
	*  returnMultipleKeyDataPairsOff  *
	***************************************/

	void RPDB_DatabaseCursorReadWriteSettingsController_turnReturnMultipleKeyDataPairsOff( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

		cursor_write_retrieve_settings_controller->return_multiple_key_data_pairs = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/**********************
*  deleteFlags  *
**********************/

//	See http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_del.html
int RPDB_DatabaseCursorReadWriteSettingsController_internal_deleteFlags( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller __attribute__((unused)) )	{
	//	Currently unused - always returns 0
	return FALSE;
}	

/**********************
*  retrieveFlags  *
**********************/

int RPDB_DatabaseCursorReadWriteSettingsController_internal_retrieveFlags( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	return RPDB_DatabaseCursorReadWriteSettingsController_ignoreLease( cursor_write_retrieve_settings_controller )
				//	Secondary databases can't use DB_MULTIPLE
			|	( cursor_write_retrieve_settings_controller->parent_database_cursor_settings_controller->parent_database_settings_controller->parent_database->is_secondary ? FALSE : RPDB_DatabaseCursorReadWriteSettingsController_returnMultipleDataItems( cursor_write_retrieve_settings_controller ) )
			|	RPDB_DatabaseCursorReadWriteSettingsController_writeLocksInsteadOfReadLocks( cursor_write_retrieve_settings_controller );
}	

/********************************************
*  copyOfDefaultSettingsForInstance  *
********************************************/

RPDB_DatabaseCursorReadWriteSettingsController* RPDB_DatabaseCursorReadWriteSettingsController_internal_copyOfDefaultSettingsForInstance( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	RPDB_DatabaseCursorReadWriteSettingsController*		cursor_write_retrieve_settings_copy = RPDB_DatabaseCursorReadWriteSettingsController_new( NULL );

	//	Copy each setting
	cursor_write_retrieve_settings_copy->permit_write = cursor_write_retrieve_settings_controller->permit_write;
	cursor_write_retrieve_settings_copy->ignore_lease = cursor_write_retrieve_settings_controller->ignore_lease;
	cursor_write_retrieve_settings_copy->write_locks_instead_of_read_locks = cursor_write_retrieve_settings_controller->write_locks_instead_of_read_locks;
	cursor_write_retrieve_settings_copy->multiple_data_items = cursor_write_retrieve_settings_controller->multiple_data_items;
	
	return cursor_write_retrieve_settings_copy;
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseCursorReadWriteSettingsController* RPDB_DatabaseCursorReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller )	{

	RPDB_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller_copy	=	RPDB_DatabaseCursorReadWriteSettingsController_new( database_cursor_record_read_write_settings_controller->parent_database_cursor_settings_controller );

	//	Instances and Pointers
	database_cursor_record_read_write_settings_controller_copy->write_locks_instead_of_read_locks	=	database_cursor_record_read_write_settings_controller->write_locks_instead_of_read_locks;
	database_cursor_record_read_write_settings_controller_copy->multiple_data_items	=	database_cursor_record_read_write_settings_controller->multiple_data_items;
	database_cursor_record_read_write_settings_controller_copy->ignore_lease	=	database_cursor_record_read_write_settings_controller->ignore_lease;
	database_cursor_record_read_write_settings_controller_copy->permit_write	=	database_cursor_record_read_write_settings_controller->permit_write;
	database_cursor_record_read_write_settings_controller_copy->return_multiple_key_data_pairs	=	database_cursor_record_read_write_settings_controller->return_multiple_key_data_pairs;

	return database_cursor_record_read_write_settings_controller_copy;
}

