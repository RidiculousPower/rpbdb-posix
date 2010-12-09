/*
 *		Rbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorReadWriteSettingsController
 *		Rbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorReadWriteSettingsController
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseCursorReadWriteSettingsController.h"
#include "Rbdb_DatabaseCursorReadWriteSettingsController_internal.h"

#include "Rbdb_Environment.h"
#include "Rbdb_SettingsController.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

Rbdb_DatabaseCursorReadWriteSettingsController* Rbdb_DatabaseCursorReadWriteSettingsController_new( Rbdb_DatabaseCursorSettingsController* cursor_settings_controller )	{

	Rbdb_DatabaseCursorReadWriteSettingsController*		cursor_write_retrieve_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseCursorReadWriteSettingsController ) );
	
	cursor_write_retrieve_settings_controller->parent_database_cursor_settings_controller = cursor_settings_controller;
	
	return cursor_write_retrieve_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseCursorReadWriteSettingsController_free(	Rbdb_DatabaseCursorReadWriteSettingsController** database_cursor_record_read_write_settings_controller )	{

	free( *database_cursor_record_read_write_settings_controller );
	*database_cursor_record_read_write_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseCursorReadWriteSettingsController_parentEnvironment(	Rbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller )	{
	return database_cursor_record_read_write_settings_controller->parent_database_cursor_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseCursorReadWriteSettingsController_parentDatabase(	Rbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller )	{
	return database_cursor_record_read_write_settings_controller->parent_database_cursor_settings_controller->parent_database_settings_controller->parent_database;
}

/***************************************
*  parentDatabaseCursor  *
***************************************/
Rbdb_DatabaseCursor* Rbdb_DatabaseCursorReadWriteSettingsController_parentDatabaseCursor(	Rbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller )	{
	return database_cursor_record_read_write_settings_controller->parent_database_cursor_settings_controller->parent_database_cursor;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/********************
*  permitWrite  *
********************/

//	DB_WRITECURSOR			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_cursor.html
BOOL Rbdb_DatabaseCursorReadWriteSettingsController_permitWrite( Rbdb_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->permit_write == TRUE )	{
		return DB_WRITECURSOR;
	}

	return FALSE;
}

	/************************
	*  permitWriteOn  *
	************************/

	void Rbdb_DatabaseCursorReadWriteSettingsController_turnPermitWriteOn( Rbdb_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller )	{
		cursor_write_retrieve_settings_controller->permit_write = TRUE;
	}

	/************************
	*  permitWriteOff  *
	************************/

	void Rbdb_DatabaseCursorReadWriteSettingsController_turnPermitWriteOff( Rbdb_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller )	{
		cursor_write_retrieve_settings_controller->permit_write = FALSE;
	}

/********************
*  ignoreLease  *
********************/

//	DB_IGNORE_LEASE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL Rbdb_DatabaseCursorReadWriteSettingsController_ignoreLease( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->ignore_lease == TRUE )	{
		return DB_IGNORE_LEASE;
	}
	return FALSE;
}

	/************************
	*  ignoreLeaseOn  *
	************************/

	void Rbdb_DatabaseCursorReadWriteSettingsController_ignoreLeaseOn( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

		cursor_write_retrieve_settings_controller->ignore_lease = TRUE;
	}

	/************************
	*  ignoreLeaseOff  *
	************************/

	void Rbdb_DatabaseCursorReadWriteSettingsController_ignoreLeaseOff( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

		cursor_write_retrieve_settings_controller->ignore_lease = FALSE;
	}

/************************************
*  writeLocksInsteadOfReadLocks  *
************************************/

//	DB_RMW					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL Rbdb_DatabaseCursorReadWriteSettingsController_writeLocksInsteadOfReadLocks( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->write_locks_instead_of_read_locks == TRUE )	{
		return DB_RMW;
	}
	return FALSE;
}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	****************************************/

	void Rbdb_DatabaseCursorReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{
		cursor_write_retrieve_settings_controller->write_locks_instead_of_read_locks = TRUE;
	}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	****************************************/

	void Rbdb_DatabaseCursorReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{
		cursor_write_retrieve_settings_controller->write_locks_instead_of_read_locks = FALSE;
	}

/********************************
*  returnMultipleDataItems  *
********************************/

//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL Rbdb_DatabaseCursorReadWriteSettingsController_returnMultipleDataItems( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->multiple_data_items == TRUE )	{
		return DB_MULTIPLE;
	}
	return FALSE;
}

	/************************************
	*  returnMultipleDataItemsOn  *
	************************************/

	void Rbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleDataItemsOn( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{
		
		cursor_write_retrieve_settings_controller->multiple_data_items = TRUE;
	}

	/************************************
	*  returnMultipleDataItemsOff  *
	************************************/

	void Rbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleDataItemsOff( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{
		
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
BOOL Rbdb_DatabaseCursorReadWriteSettingsController_returnMultipleKeyDataPairs( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	if ( cursor_write_retrieve_settings_controller->return_multiple_key_data_pairs == TRUE )	{
		return DB_MULTIPLE_KEY;
	}
	return FALSE;
}

	/***************************************
	*  returnMultipleKeyDataPairsOn  *
	***************************************/

	void Rbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleKeyDataPairsOn( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

		cursor_write_retrieve_settings_controller->return_multiple_key_data_pairs = TRUE;
	}

	/***************************************
	*  returnMultipleKeyDataPairsOff  *
	***************************************/

	void Rbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleKeyDataPairsOff( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

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
int Rbdb_DatabaseCursorReadWriteSettingsController_internal_deleteFlags( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller __attribute__((unused)) )	{
	//	Currently unused - always returns 0
	return FALSE;
}	

/**********************
*  retrieveFlags  *
**********************/

int Rbdb_DatabaseCursorReadWriteSettingsController_internal_retrieveFlags( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	return Rbdb_DatabaseCursorReadWriteSettingsController_ignoreLease( cursor_write_retrieve_settings_controller )
				//	Secondary databases can't use DB_MULTIPLE
			|	( cursor_write_retrieve_settings_controller->parent_database_cursor_settings_controller->parent_database_settings_controller->parent_database->is_secondary ? FALSE : Rbdb_DatabaseCursorReadWriteSettingsController_returnMultipleDataItems( cursor_write_retrieve_settings_controller ) )
			|	Rbdb_DatabaseCursorReadWriteSettingsController_writeLocksInsteadOfReadLocks( cursor_write_retrieve_settings_controller );
}	

/********************************************
*  copyOfDefaultSettingsForInstance  *
********************************************/

Rbdb_DatabaseCursorReadWriteSettingsController* Rbdb_DatabaseCursorReadWriteSettingsController_internal_copyOfDefaultSettingsForInstance( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller )	{

	Rbdb_DatabaseCursorReadWriteSettingsController*		cursor_write_retrieve_settings_copy = Rbdb_DatabaseCursorReadWriteSettingsController_new( NULL );

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
Rbdb_DatabaseCursorReadWriteSettingsController* Rbdb_DatabaseCursorReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller )	{

	Rbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller_copy	=	Rbdb_DatabaseCursorReadWriteSettingsController_new( database_cursor_record_read_write_settings_controller->parent_database_cursor_settings_controller );

	//	Instances and Pointers
	database_cursor_record_read_write_settings_controller_copy->write_locks_instead_of_read_locks	=	database_cursor_record_read_write_settings_controller->write_locks_instead_of_read_locks;
	database_cursor_record_read_write_settings_controller_copy->multiple_data_items	=	database_cursor_record_read_write_settings_controller->multiple_data_items;
	database_cursor_record_read_write_settings_controller_copy->ignore_lease	=	database_cursor_record_read_write_settings_controller->ignore_lease;
	database_cursor_record_read_write_settings_controller_copy->permit_write	=	database_cursor_record_read_write_settings_controller->permit_write;
	database_cursor_record_read_write_settings_controller_copy->return_multiple_key_data_pairs	=	database_cursor_record_read_write_settings_controller->return_multiple_key_data_pairs;

	return database_cursor_record_read_write_settings_controller_copy;
}

