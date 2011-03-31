/*
 *		RPbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorReadWriteSettingsController
 *		RPbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorReadWriteSettingsController
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseCursorReadWriteSettingsController.h"
#include "DatabaseCursorReadWriteSettingsController_internal.h"

#include "Environment.h"
#include "SettingsController.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_DatabaseCursorReadWriteSettingsController* RPbdb_DatabaseCursorReadWriteSettingsController_new( RPbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{

	RPbdb_DatabaseCursorReadWriteSettingsController*		cursor_write_retrieve_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseCursorReadWriteSettingsController ) );
	
	cursor_write_retrieve_settings_controller->parent_database_cursor_settings_controller = cursor_settings_controller;
	
	return cursor_write_retrieve_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseCursorReadWriteSettingsController_free(	RPbdb_DatabaseCursorReadWriteSettingsController** database_cursor_record_read_write_settings_controller )	{

	free( *database_cursor_record_read_write_settings_controller );
	*database_cursor_record_read_write_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseCursorReadWriteSettingsController_parentEnvironment(	RPbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller )	{
	return database_cursor_record_read_write_settings_controller->parent_database_cursor_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseCursorReadWriteSettingsController_parentDatabase(	RPbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller )	{
	return database_cursor_record_read_write_settings_controller->parent_database_cursor_settings_controller->parent_database_settings_controller->parent_database;
}

/***************************************
*  parentDatabaseCursor  *
***************************************/
RPbdb_DatabaseCursor* RPbdb_DatabaseCursorReadWriteSettingsController_parentDatabaseCursor(	RPbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller )	{
	return database_cursor_record_read_write_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/********************
*  permitWrite  *
********************/

//	DB_WRITECURSOR			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
BOOL RPbdb_DatabaseCursorReadWriteSettingsController_permitWrite( RPbdb_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->permit_write == TRUE )	{
		return DB_WRITECURSOR;
	}

	return FALSE;
}

	/************************
	*  permitWriteOn  *
	************************/

	void RPbdb_DatabaseCursorReadWriteSettingsController_turnPermitWriteOn( RPbdb_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller )	{
		cursor_write_retrieve_settings_controller->permit_write = TRUE;
	}

	/************************
	*  permitWriteOff  *
	************************/

	void RPbdb_DatabaseCursorReadWriteSettingsController_turnPermitWriteOff( RPbdb_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller )	{
		cursor_write_retrieve_settings_controller->permit_write = FALSE;
	}

/********************
*  ignoreLease  *
********************/

//	DB_IGNORE_LEASE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL RPbdb_DatabaseCursorReadWriteSettingsController_ignoreLease( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->ignore_lease == TRUE )	{
		return DB_IGNORE_LEASE;
	}
	return FALSE;
}

	/************************
	*  ignoreLeaseOn  *
	************************/

	void RPbdb_DatabaseCursorReadWriteSettingsController_ignoreLeaseOn( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

		cursor_write_retrieve_settings_controller->ignore_lease = TRUE;
	}

	/************************
	*  ignoreLeaseOff  *
	************************/

	void RPbdb_DatabaseCursorReadWriteSettingsController_ignoreLeaseOff( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

		cursor_write_retrieve_settings_controller->ignore_lease = FALSE;
	}

/************************************
*  writeLocksInsteadOfReadLocks  *
************************************/

//	DB_RMW					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL RPbdb_DatabaseCursorReadWriteSettingsController_writeLocksInsteadOfReadLocks( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->write_locks_instead_of_read_locks == TRUE )	{
		return DB_RMW;
	}
	return FALSE;
}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	****************************************/

	void RPbdb_DatabaseCursorReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{
		cursor_write_retrieve_settings_controller->write_locks_instead_of_read_locks = TRUE;
	}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	****************************************/

	void RPbdb_DatabaseCursorReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{
		cursor_write_retrieve_settings_controller->write_locks_instead_of_read_locks = FALSE;
	}

/********************************
*  returnMultipleDataItems  *
********************************/

//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL RPbdb_DatabaseCursorReadWriteSettingsController_returnMultipleDataItems( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->multiple_data_items == TRUE )	{
		return DB_MULTIPLE;
	}
	return FALSE;
}

	/************************************
	*  returnMultipleDataItemsOn  *
	************************************/

	void RPbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleDataItemsOn( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{
		
		cursor_write_retrieve_settings_controller->multiple_data_items = TRUE;
	}

	/************************************
	*  returnMultipleDataItemsOff  *
	************************************/

	void RPbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleDataItemsOff( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{
		
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
BOOL RPbdb_DatabaseCursorReadWriteSettingsController_returnMultipleKeyDataPairs( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->return_multiple_key_data_pairs == TRUE )	{
		return DB_MULTIPLE_KEY;
	}
	return FALSE;
}

	/***************************************
	*  returnMultipleKeyDataPairsOn  *
	***************************************/

	void RPbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleKeyDataPairsOn( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

		cursor_write_retrieve_settings_controller->return_multiple_key_data_pairs = TRUE;
	}

	/***************************************
	*  returnMultipleKeyDataPairsOff  *
	***************************************/

	void RPbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleKeyDataPairsOff( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

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
int RPbdb_DatabaseCursorReadWriteSettingsController_internal_deleteFlags( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller __attribute__((unused)) )	{
	//	Currently unused - always returns 0
	return FALSE;
}	

/**********************
*  retrieveFlags  *
**********************/

int RPbdb_DatabaseCursorReadWriteSettingsController_internal_retrieveFlags( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	return RPbdb_DatabaseCursorReadWriteSettingsController_ignoreLease( cursor_write_retrieve_settings_controller )
				//	Secondary databases can't use DB_MULTIPLE
			|	( cursor_write_retrieve_settings_controller->parent_database_cursor_settings_controller->parent_database_settings_controller->parent_database->is_secondary ? FALSE : RPbdb_DatabaseCursorReadWriteSettingsController_returnMultipleDataItems( cursor_write_retrieve_settings_controller ) )
			|	RPbdb_DatabaseCursorReadWriteSettingsController_writeLocksInsteadOfReadLocks( cursor_write_retrieve_settings_controller );
}	

/********************************************
*  copyOfDefaultSettingsForInstance  *
********************************************/

RPbdb_DatabaseCursorReadWriteSettingsController* RPbdb_DatabaseCursorReadWriteSettingsController_internal_copyOfDefaultSettingsForInstance( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	RPbdb_DatabaseCursorReadWriteSettingsController*		cursor_write_retrieve_settings_copy = RPbdb_DatabaseCursorReadWriteSettingsController_new( NULL );

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
RPbdb_DatabaseCursorReadWriteSettingsController* RPbdb_DatabaseCursorReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller )	{

	RPbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller_copy	=	RPbdb_DatabaseCursorReadWriteSettingsController_new( database_cursor_record_read_write_settings_controller->parent_database_cursor_settings_controller );

	//	Instances and Pointers
	database_cursor_record_read_write_settings_controller_copy->write_locks_instead_of_read_locks	=	database_cursor_record_read_write_settings_controller->write_locks_instead_of_read_locks;
	database_cursor_record_read_write_settings_controller_copy->multiple_data_items	=	database_cursor_record_read_write_settings_controller->multiple_data_items;
	database_cursor_record_read_write_settings_controller_copy->ignore_lease	=	database_cursor_record_read_write_settings_controller->ignore_lease;
	database_cursor_record_read_write_settings_controller_copy->permit_write	=	database_cursor_record_read_write_settings_controller->permit_write;
	database_cursor_record_read_write_settings_controller_copy->return_multiple_key_data_pairs	=	database_cursor_record_read_write_settings_controller->return_multiple_key_data_pairs;

	return database_cursor_record_read_write_settings_controller_copy;
}

