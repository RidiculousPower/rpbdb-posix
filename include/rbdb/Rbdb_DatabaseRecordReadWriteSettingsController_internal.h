#ifndef RBDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

Rbdb_DatabaseRecordReadWriteSettingsController* Rbdb_DatabaseRecordReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
int												Rbdb_DatabaseRecordReadWriteSettingsController_internal_writeFlags(							Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller);
int												Rbdb_DatabaseRecordReadWriteSettingsController_internal_deleteFlags(							Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );
int												Rbdb_DatabaseRecordReadWriteSettingsController_internal_existsFlags(							Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );
void Rbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_internal_hasFooter( Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );
void Rbdb_DatabaseRecordReadWriteSettingsController_internal_determineIfHasFooter( Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller );


#endif

