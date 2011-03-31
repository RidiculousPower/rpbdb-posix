#ifndef RPBDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPbdb_DatabaseRecordReadWriteSettingsController* RPbdb_DatabaseRecordReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
int												RPbdb_DatabaseRecordReadWriteSettingsController_internal_writeFlags(							RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller);
int												RPbdb_DatabaseRecordReadWriteSettingsController_internal_deleteFlags(							RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );
int												RPbdb_DatabaseRecordReadWriteSettingsController_internal_existsFlags(							RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );
void RPbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_internal_hasFooter( RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );
void RPbdb_DatabaseRecordReadWriteSettingsController_internal_determineIfHasFooter( RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );


#endif

