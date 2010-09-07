/*
 *		RPDB::DatabaseController::Database::DatabaseSettingsController::DatabaseSettingsVariableRecordController
 *
 *
 */

#ifndef RPDB_DATABASE_VARIABLE_RECORD_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_VARIABLE_RECORD_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseRecordVariableLengthSettingsController*		RPDB_DatabaseRecordVariableLengthSettingsController_new(		RPDB_DatabaseRecordSettingsController*					database_record_settings_controller );

	void												RPDB_DatabaseRecordVariableLengthSettingsController_free(										RPDB_DatabaseRecordVariableLengthSettingsController** database_record_variable_length_settings_controller );
	RPDB_Environment*							RPDB_DatabaseRecordVariableLengthSettingsController_parentEnvironment(				RPDB_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller );
	RPDB_Database* RPDB_DatabaseRecordVariableLengthSettingsController_parentDatabase(	RPDB_DatabaseRecordVariableLengthSettingsController* database_record_variable_length_settings_controller );

	int													RPDB_DatabaseRecordVariableLengthSettingsController_recordDelimeter(								RPDB_DatabaseRecordVariableLengthSettingsController*		database_record_variable_length_settings_controller );
	void												RPDB_DatabaseRecordVariableLengthSettingsController_setRecordDelimeter(							RPDB_DatabaseRecordVariableLengthSettingsController*		database_record_variable_length_settings_controller,
																																					int													record_delimeter );
														
	RPDB_DatabaseRecordVariableLengthSettingsController*		RPDB_DatabaseRecordVariableLengthSettingsController_internal_copyOfDefaultSettingsForInstance(	RPDB_DatabaseRecordVariableLengthSettingsController*		database_record_variable_length_settings_controller );

#endif
