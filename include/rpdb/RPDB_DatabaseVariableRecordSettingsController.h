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

	RPDB_DatabaseVariableRecordSettingsController*		RPDB_DatabaseVariableRecordSettingsController_new(											RPDB_DatabaseSettingsController*					database_settings_controller );

	void												RPDB_DatabaseVariableRecordSettingsController_free(										RPDB_DatabaseVariableRecordSettingsController** database_variable_record_settings_controller );
	RPDB_Environment*							RPDB_DatabaseVariableRecordSettingsController_parentEnvironment(				RPDB_DatabaseVariableRecordSettingsController* database_variable_record_settings_controller );
	RPDB_Database* RPDB_DatabaseVariableRecordSettingsController_parentDatabase(	RPDB_DatabaseVariableRecordSettingsController* database_variable_record_settings_controller );

	int													RPDB_DatabaseVariableRecordSettingsController_recordDelimeter(								RPDB_DatabaseVariableRecordSettingsController*		database_variable_record_settings_controller );
	void												RPDB_DatabaseVariableRecordSettingsController_setRecordDelimeter(							RPDB_DatabaseVariableRecordSettingsController*		database_variable_record_settings_controller,
																																					int													record_delimeter );
														
	RPDB_DatabaseVariableRecordSettingsController*		RPDB_DatabaseVariableRecordSettingsController_internal_copyOfDefaultSettingsForInstance(	RPDB_DatabaseVariableRecordSettingsController*		database_variable_record_settings_controller );

#endif
