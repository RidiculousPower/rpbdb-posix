#ifndef RPBDB_DATABASE_CURSOR_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_CURSOR_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int													RPbdb_DatabaseCursorReadWriteSettingsController_internal_deleteFlags(						RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
int RPbdb_DatabaseCursorReadWriteSettingsController_internal_retrieveFlags( RPbdb_DatabaseCursorReadWriteSettingsController* cursor_write_retrieve_settings_controller );
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_internal_hasFooter( RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );
void RPbdb_DatabaseRecordReadWriteSettingsController_internal_determineIfHasFooter( RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );
RPbdb_DatabaseCursorReadWriteSettingsController* RPbdb_DatabaseCursorReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseCursorReadWriteSettingsController* database_cursor_record_read_write_settings_controller );

#endif

