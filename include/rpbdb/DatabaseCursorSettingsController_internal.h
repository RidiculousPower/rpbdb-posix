#ifndef RPBDB_DATABASE_CURSOR_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_CURSOR_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int											RPbdb_DatabaseCursorSettingsController_internal_countDataItemsFlags(				RPbdb_DatabaseCursorSettingsController*		cursor_settings_controller );
int											RPbdb_DatabaseCursorSettingsController_internal_duplicateFlags(						RPbdb_DatabaseCursorSettingsController*		cursor_settings_controller );
int											RPbdb_DatabaseCursorSettingsController_internal_openFlags(							RPbdb_DatabaseCursorSettingsController*		cursor_settings_controller );
RPbdb_DatabaseCursorSettingsController* RPbdb_DatabaseCursorSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseCursorSettingsController* database_cursor_settings_controller );

#endif

