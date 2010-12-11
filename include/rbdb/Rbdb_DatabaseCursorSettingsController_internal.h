#ifndef RBDB_DATABASE_CURSOR_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_CURSOR_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int											Rbdb_DatabaseCursorSettingsController_internal_countDataItemsFlags(				Rbdb_DatabaseCursorSettingsController*		cursor_settings_controller );
int											Rbdb_DatabaseCursorSettingsController_internal_duplicateFlags(						Rbdb_DatabaseCursorSettingsController*		cursor_settings_controller );
int											Rbdb_DatabaseCursorSettingsController_internal_openFlags(							Rbdb_DatabaseCursorSettingsController*		cursor_settings_controller );
Rbdb_DatabaseCursorSettingsController* Rbdb_DatabaseCursorSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseCursorSettingsController* database_cursor_settings_controller );

#endif

