#ifndef RPDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPDB_DatabaseReadWriteSettingsController* RPDB_DatabaseReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller );
int												RPDB_DatabaseReadWriteSettingsController_internal_writeFlags(							RPDB_DatabaseReadWriteSettingsController*		database_read_write_settings_controller);
int												RPDB_DatabaseReadWriteSettingsController_internal_deleteFlags(							RPDB_DatabaseReadWriteSettingsController*		database_read_write_settings_controller );
int												RPDB_DatabaseReadWriteSettingsController_internal_existsFlags(							RPDB_DatabaseReadWriteSettingsController*		database_read_write_settings_controller );


#endif

