/*
 *		RPDB::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorReadWriteSettingsController
 *		RPDB::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorReadWriteSettingsController
 *
 */

#ifndef RPDB_DATABASE_CURSOR_READ_WRITE_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_CURSOR_READ_WRITE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

/*
 *		RPDB::SettingsController::DatabaseSettingsController::CursorSettingsController::CursorReadWriteSettingsController
 *		RPDB::DatabaseController::Database::CursorController::Cursor::CursorSettingsController::CursorReadWriteSettingsController
 *
 */

#include "RPDB_DatabaseCursorReadWriteSettingsController.h"

	#include "RPDB_DatabaseCursorReadWriteSettingsController.h"

	#include "RPDB_Environment.h"
	#include "RPDB_SettingsController.h"

	#include "RPDB_DatabaseCursorReadWriteSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/

RPDB_DatabaseCursorReadWriteSettingsController* RPDB_DatabaseCursorReadWriteSettingsController_new( RPDB_DatabaseCursorSettingsController* cursor_settings_controller );
void RPDB_DatabaseCursorReadWriteSettingsController_free(	RPDB_DatabaseCursorReadWriteSettingsController** database_cursor_read_write_settings_controller );
RPDB_Environment* RPDB_DatabaseCursorReadWriteSettingsController_parentEnvironment(	RPDB_DatabaseCursorReadWriteSettingsController* database_cursor_read_write_settings_controller );
RPDB_Database* RPDB_DatabaseCursorReadWriteSettingsController_parentDatabase(	RPDB_DatabaseCursorReadWriteSettingsController* database_cursor_read_write_settings_controller );
RPDB_DatabaseCursor* RPDB_DatabaseCursorReadWriteSettingsController_parentDatabaseCursor(	RPDB_DatabaseCursorReadWriteSettingsController* database_cursor_read_write_settings_controller );
BOOL RPDB_DatabaseCursorReadWriteSettingsController_permitWrite( RPDB_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller );
	void RPDB_DatabaseCursorReadWriteSettingsController_turnPermitWriteOn( RPDB_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller );
	void RPDB_DatabaseCursorReadWriteSettingsController_turnPermitWriteOff( RPDB_DatabaseCursorReadWriteSettingsController*	cursor_write_retrieve_settings_controller );
BOOL RPDB_DatabaseCursorReadWriteSettingsController_ignoreLease( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPDB_DatabaseCursorReadWriteSettingsController_ignoreLeaseOn( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPDB_DatabaseCursorReadWriteSettingsController_ignoreLeaseOff( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
BOOL RPDB_DatabaseCursorReadWriteSettingsController_writeLocksInsteadOfReadLocks( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPDB_DatabaseCursorReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPDB_DatabaseCursorReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
BOOL RPDB_DatabaseCursorReadWriteSettingsController_returnMultipleDataItems( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
void RPDB_DatabaseCursorReadWriteSettingsController_turnReturnMultipleDataItemsOn( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPDB_DatabaseCursorReadWriteSettingsController_turnReturnMultipleDataItemsOff( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	BOOL RPDB_DatabaseCursorReadWriteSettingsController_returnMultipleKeyDataPairs( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPDB_DatabaseCursorReadWriteSettingsController_turnReturnMultipleKeyDataPairsOn( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
	void RPDB_DatabaseCursorReadWriteSettingsController_turnReturnMultipleKeyDataPairsOff( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
int RPDB_DatabaseCursorReadWriteSettingsController_internal_deleteFlags( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
int RPDB_DatabaseCursorReadWriteSettingsController_internal_retrieveFlags( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
RPDB_DatabaseCursorReadWriteSettingsController* RPDB_DatabaseCursorReadWriteSettingsController_internal_copyOfDefaultSettingsForInstance( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
RPDB_DatabaseCursorReadWriteSettingsController* RPDB_DatabaseCursorReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseCursorReadWriteSettingsController* database_cursor_read_write_settings_controller );


#endif

