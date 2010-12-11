#ifndef RBDB_DATABASE_CURSOR_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_CURSOR_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int													Rbdb_DatabaseCursorReadWriteSettingsController_internal_deleteFlags(						Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
int Rbdb_DatabaseCursorReadWriteSettingsController_internal_retrieveFlags( Rbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
Rbdb_DatabaseCursorReadWriteSettingsController* Rbdb_DatabaseCursorReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller );

#endif

