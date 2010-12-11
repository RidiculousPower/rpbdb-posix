#ifndef RBDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

Rbdb_DatabaseReadWriteSettingsController* Rbdb_DatabaseReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseReadWriteSettingsController* database_read_write_settings_controller );
int												Rbdb_DatabaseReadWriteSettingsController_internal_writeFlags(							Rbdb_DatabaseReadWriteSettingsController*		database_read_write_settings_controller);
int												Rbdb_DatabaseReadWriteSettingsController_internal_deleteFlags(							Rbdb_DatabaseReadWriteSettingsController*		database_read_write_settings_controller );
int												Rbdb_DatabaseReadWriteSettingsController_internal_existsFlags(							Rbdb_DatabaseReadWriteSettingsController*		database_read_write_settings_controller );


#endif

