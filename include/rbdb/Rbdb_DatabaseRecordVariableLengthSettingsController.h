/*
 *		Rbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseSettingsVariableRecordController
 *
 *
 */

#ifndef RBDB_DATABASE_VARIABLE_RECORD_SETTINGS_CONTROLLER
	#define RBDB_DATABASE_VARIABLE_RECORD_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseRecordVariableLengthSettingsController*		Rbdb_DatabaseRecordVariableLengthSettingsController_new(		Rbdb_DatabaseRecordSettingsController*					database_record_settings_controller );

	void												Rbdb_DatabaseRecordVariableLengthSettingsController_free(										Rbdb_DatabaseRecordVariableLengthSettingsController** database_record_variable_length_settings_controller );
	Rbdb_Environment*							Rbdb_DatabaseRecordVariableLengthSettingsController_parentEnvironment(				Rbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller );
	Rbdb_Database* Rbdb_DatabaseRecordVariableLengthSettingsController_parentDatabase(	Rbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller );

	int													Rbdb_DatabaseRecordVariableLengthSettingsController_delimeterByte(								Rbdb_DatabaseRecordVariableLengthSettingsController*		database_record_variable_length_settings_controller );
	void												Rbdb_DatabaseRecordVariableLengthSettingsController_setDelimeterByte(							Rbdb_DatabaseRecordVariableLengthSettingsController*		database_record_variable_length_settings_controller,
																																					int													delimeter_byte );
														
	Rbdb_DatabaseRecordVariableLengthSettingsController*		Rbdb_DatabaseRecordVariableLengthSettingsController_internal_copyOfDefaultSettingsForInstance(	Rbdb_DatabaseRecordVariableLengthSettingsController*		database_record_variable_length_settings_controller );

#endif
