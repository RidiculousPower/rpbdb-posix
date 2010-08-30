#ifndef RPDB_DATABASE_CURSOR_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_CURSOR_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int													RPDB_DatabaseCursorReadWriteSettingsController_internal_deleteFlags(						RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
int RPDB_DatabaseCursorReadWriteSettingsController_internal_retrieveFlags( RPDB_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
RPDB_DatabaseCursorReadWriteSettingsController* RPDB_DatabaseCursorReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseCursorReadWriteSettingsController* database_cursor_read_write_settings_controller );

#endif

