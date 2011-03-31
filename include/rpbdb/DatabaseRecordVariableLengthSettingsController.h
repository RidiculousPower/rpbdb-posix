/*
 *		RPbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseSettingsVariableRecordController
 *
 *
 */

#ifndef RPBDB_DATABASE_VARIABLE_RECORD_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_VARIABLE_RECORD_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseRecordVariableLengthSettingsController*		RPbdb_DatabaseRecordVariableLengthSettingsController_new(		RPbdb_DatabaseRecordSettingsController*					database_record_settings_controller );

	void												RPbdb_DatabaseRecordVariableLengthSettingsController_free(										RPbdb_DatabaseRecordVariableLengthSettingsController** database_record_variable_length_settings_controller );
	RPbdb_Environment*							RPbdb_DatabaseRecordVariableLengthSettingsController_parentEnvironment(				RPbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller );
	RPbdb_Database* RPbdb_DatabaseRecordVariableLengthSettingsController_parentDatabase(	RPbdb_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller );

	int													RPbdb_DatabaseRecordVariableLengthSettingsController_delimeterByte(								RPbdb_DatabaseRecordVariableLengthSettingsController*		database_record_variable_length_settings_controller );
	void												RPbdb_DatabaseRecordVariableLengthSettingsController_setDelimeterByte(							RPbdb_DatabaseRecordVariableLengthSettingsController*		database_record_variable_length_settings_controller,
																																					int													delimeter_byte );
														
	RPbdb_DatabaseRecordVariableLengthSettingsController*		RPbdb_DatabaseRecordVariableLengthSettingsController_internal_copyOfDefaultSettingsForInstance(	RPbdb_DatabaseRecordVariableLengthSettingsController*		database_record_variable_length_settings_controller );

#endif
