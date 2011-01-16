/*
 *		Rbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorReadWriteSettingsController
 *		Rbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorReadWriteSettingsController
 *
 */

#ifndef RBDB_DATABASE_CURSOR_READ_WRITE_SETTINGS_CONTROLLER
	#define RBDB_DATABASE_CURSOR_READ_WRITE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

/*
 *		Rbdb::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorReadWriteSettingsController
 *		Rbdb::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorReadWriteSettingsController
 *
 */

#include "Rbdb_DatabaseCursorReadWriteSettingsController.h"

	#include "Rbdb_DatabaseCursorReadWriteSettingsController.h"

	#include "Rbdb_Environment.h"
	#include "Rbdb_SettingsController.h"

	#include "Rbdb_DatabaseCursorReadWriteSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

Rbdb_DatabaseCursorReadWriteSettingsController* Rbdb_DatabaseCursorReadWriteSettingsController_new( Rbdb_DatabaseCursorSettingsController* cursor_settings_controller );
void Rbdb_DatabaseCursorReadWriteSettingsController_free(	Rbdb_DatabaseCursorReadWriteSettingsController** database_cursor_record_read_write_settings_controller );
Rbdb_Environment* Rbdb_DatabaseCursorReadWriteSettingsController_parentEnvironment(	Rbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller );
Rbdb_Database* Rbdb_DatabaseCursorReadWriteSettingsController_parentDatabase(	Rbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller );
Rbdb_DatabaseCursor* Rbdb_DatabaseCursorReadWriteSettingsController_parentDatabaseCursor(	Rbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller );
BOOL Rbdb_DatabaseCursorReadWriteSettingsController_permitWrite( Rbdb_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller );
	void Rbdb_DatabaseCursorReadWriteSettingsController_turnPermitWriteOn( Rbdb_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller );
	void Rbdb_DatabaseCursorReadWriteSettingsController_turnPermitWriteOff( Rbdb_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller );
BOOL Rbdb_DatabaseCursorReadWriteSettingsController_ignoreLease( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void Rbdb_DatabaseCursorReadWriteSettingsController_ignoreLeaseOn( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void Rbdb_DatabaseCursorReadWriteSettingsController_ignoreLeaseOff( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
BOOL Rbdb_DatabaseCursorReadWriteSettingsController_writeLocksInsteadOfReadLocks( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void Rbdb_DatabaseCursorReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void Rbdb_DatabaseCursorReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
BOOL Rbdb_DatabaseCursorReadWriteSettingsController_returnMultipleDataItems( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
void Rbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleDataItemsOn( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void Rbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleDataItemsOff( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	BOOL Rbdb_DatabaseCursorReadWriteSettingsController_returnMultipleKeyDataPairs( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void Rbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleKeyDataPairsOn( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void Rbdb_DatabaseCursorReadWriteSettingsController_turnReturnMultipleKeyDataPairsOff( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
int Rbdb_DatabaseCursorReadWriteSettingsController_internal_deleteFlags( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
int Rbdb_DatabaseCursorReadWriteSettingsController_internal_retrieveFlags( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
Rbdb_DatabaseCursorReadWriteSettingsController* Rbdb_DatabaseCursorReadWriteSettingsController_internal_copyOfDefaultSettingsForInstance( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
Rbdb_DatabaseCursorReadWriteSettingsController* Rbdb_DatabaseCursorReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller );
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_storeFileNotPath( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnStoreFileNotPathOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnStoreFileNotPathOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );


#endif

