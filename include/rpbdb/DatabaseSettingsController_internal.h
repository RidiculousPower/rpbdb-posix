#ifndef RPBDB_DATABASE_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int												RPbdb_DatabaseSettingsController_internal_createFlags(							RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_openFlags(							RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_closeFlags(							RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_renameFlags(							RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_emptyFlags(							RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_eraseFlags(							RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_upgradeFlags(							RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_resetIDFlags(							RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_syncFlags(							RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_associateFlags(						RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_keyRangeFlags(						RPbdb_DatabaseSettingsController*	database_settings_controller );
DB_COMPACT*										RPbdb_DatabaseSettingsController_internal_compactParameters(					RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_compactFlags(							RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_associateFlags(						RPbdb_DatabaseSettingsController*	database_settings_controller );
int												RPbdb_DatabaseSettingsController_internal_prepareDatabaseForFileTransferFlags(	RPbdb_DatabaseSettingsController*	database_settings_controller );
RPbdb_DatabaseSettingsController* RPbdb_DatabaseSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseSettingsController* database_settings_controller );

#endif

