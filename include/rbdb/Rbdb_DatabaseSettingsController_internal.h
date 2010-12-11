#ifndef RBDB_DATABASE_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int												Rbdb_DatabaseSettingsController_internal_createFlags(							Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_openFlags(							Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_closeFlags(							Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_renameFlags(							Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_emptyFlags(							Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_eraseFlags(							Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_upgradeFlags(							Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_resetIDFlags(							Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_syncFlags(							Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_associateFlags(						Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_keyRangeFlags(						Rbdb_DatabaseSettingsController*	database_settings_controller );
DB_COMPACT*										Rbdb_DatabaseSettingsController_internal_compactParameters(					Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_compactFlags(							Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_associateFlags(						Rbdb_DatabaseSettingsController*	database_settings_controller );
int												Rbdb_DatabaseSettingsController_internal_prepareDatabaseForFileTransferFlags(	Rbdb_DatabaseSettingsController*	database_settings_controller );
Rbdb_DatabaseSettingsController* Rbdb_DatabaseSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseSettingsController* database_settings_controller );

#endif

