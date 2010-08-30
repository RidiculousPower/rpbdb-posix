#ifndef RPDB_DATABASE_CURSOR_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_CURSOR_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int											RPDB_DatabaseCursorSettingsController_internal_countDataItemsFlags(				RPDB_DatabaseCursorSettingsController*		cursor_settings_controller );
int											RPDB_DatabaseCursorSettingsController_internal_duplicateFlags(						RPDB_DatabaseCursorSettingsController*		cursor_settings_controller );
int											RPDB_DatabaseCursorSettingsController_internal_openFlags(							RPDB_DatabaseCursorSettingsController*		cursor_settings_controller );
RPDB_DatabaseCursorSettingsController* RPDB_DatabaseCursorSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseCursorSettingsController* database_cursor_settings_controller );

#endif

