#ifndef RPDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPDB_DatabaseRecordReadWriteSettingsController* RPDB_DatabaseRecordReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
int												RPDB_DatabaseRecordReadWriteSettingsController_internal_writeFlags(							RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller);
int												RPDB_DatabaseRecordReadWriteSettingsController_internal_deleteFlags(							RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );
int												RPDB_DatabaseRecordReadWriteSettingsController_internal_existsFlags(							RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );
void RPDB_DatabaseRecordReadWriteSettingsController_internal_updateFlags( RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );


#endif

