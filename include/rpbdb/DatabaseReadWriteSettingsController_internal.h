#ifndef RPBDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPbdb_DatabaseReadWriteSettingsController* RPbdb_DatabaseReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseReadWriteSettingsController* database_read_write_settings_controller );
int												RPbdb_DatabaseReadWriteSettingsController_internal_writeFlags(							RPbdb_DatabaseReadWriteSettingsController*		database_read_write_settings_controller);
int												RPbdb_DatabaseReadWriteSettingsController_internal_deleteFlags(							RPbdb_DatabaseReadWriteSettingsController*		database_read_write_settings_controller );
int												RPbdb_DatabaseReadWriteSettingsController_internal_existsFlags(							RPbdb_DatabaseReadWriteSettingsController*		database_read_write_settings_controller );


#endif

