#ifndef RPDB_DATABASE_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int												RPDB_DatabaseSettingsController_internal_createFlags(							RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_openFlags(							RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_closeFlags(							RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_renameFlags(							RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_emptyFlags(							RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_eraseFlags(							RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_upgradeFlags(							RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_resetIDFlags(							RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_syncFlags(							RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_associateFlags(						RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_keyRangeFlags(						RPDB_DatabaseSettingsController*	database_settings_controller );
DB_COMPACT*										RPDB_DatabaseSettingsController_internal_compactParameters(					RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_compactFlags(							RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_associateFlags(						RPDB_DatabaseSettingsController*	database_settings_controller );
int												RPDB_DatabaseSettingsController_internal_prepareDatabaseForFileTransferFlags(	RPDB_DatabaseSettingsController*	database_settings_controller );
RPDB_DatabaseSettingsController* RPDB_DatabaseSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseSettingsController* database_settings_controller );

#endif

