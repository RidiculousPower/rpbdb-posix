/*
 *		RPbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorReadWriteSettingsController
 *		RPbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorReadWriteSettingsController
 *
 */

#ifndef RPBDB_DATABASE_CURSOR_READ_WRITE_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_CURSOR_READ_WRITE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

/*
 *		RPbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorReadWriteSettingsController
 *		RPbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorReadWriteSettingsController
 *
 */

#include "DatabaseCursorReadWriteSettingsController.h"

	#include "DatabaseCursorReadWriteSettingsController.h"

	#include "Environment.h"
	#include "SettingsController.h"

	#include "DatabaseCursorReadWriteSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPbdb_DatabaseCursorReadWriteSettingsController* RPbdb_DatabaseCursorReadWriteSettingsController_new( RPbdb_DatabaseCursorSettingsController* cursor_settings_controller );
void RPbdb_DatabaseCursorReadWriteSettingsController_free(	RPbdb_DatabaseCursorReadWriteSettingsController** database_cursor_record_read_write_settings_controller );
RPbdb_Environment* RPbdb_DatabaseCursorReadWriteSettingsController_parentEnvironment(	RPbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller );
RPbdb_Database* RPbdb_DatabaseCursorReadWriteSettingsController_parentDatabase(	RPbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller );
RPbdb_DatabaseCursor* RPbdb_DatabaseCursorReadWriteSettingsController_parentDatabaseCursor(	RPbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller );
BOOL RPbdb_DatabaseCursorReadWriteSettingsController_permitWrite( RPbdb_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller );
	void RPbdb_DatabaseCursorReadWriteSettingsController_turnPermitWriteOn( RPbdb_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller );
	void RPbdb_DatabaseCursorReadWriteSettingsController_turnPermitWriteOff( RPbdb_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller );
BOOL RPbdb_DatabaseCursorReadWriteSettingsController_ignoreLease( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPbdb_DatabaseCursorReadWriteSettingsController_ignoreLeaseOn( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPbdb_DatabaseCursorReadWriteSettingsController_ignoreLeaseOff( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
BOOL RPbdb_DatabaseCursorReadWriteSettingsController_writeLocksInsteadOfReadLocks( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPbdb_DatabaseCursorReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPbdb_DatabaseCursorReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
BOOL RPbdb_DatabaseCursorReadWriteSettingsController_returnMultipleDataItems( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
void RPbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleDataItemsOn( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleDataItemsOff( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	BOOL RPbdb_DatabaseCursorReadWriteSettingsController_returnMultipleKeyDataPairs( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleKeyDataPairsOn( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleKeyDataPairsOff( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
int RPbdb_DatabaseCursorReadWriteSettingsController_internal_deleteFlags( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
int RPbdb_DatabaseCursorReadWriteSettingsController_internal_retrieveFlags( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
RPbdb_DatabaseCursorReadWriteSettingsController* RPbdb_DatabaseCursorReadWriteSettingsController_internal_copyOfDefaultSettingsForInstance( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
RPbdb_DatabaseCursorReadWriteSettingsController* RPbdb_DatabaseCursorReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller );
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_storeFileNotPath( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreFileNotPathOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreFileNotPathOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );


#endif

