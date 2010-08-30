/*
 *		RPDB::DatabaseController::Database::DatabaseSettingsController::DatabaseSettingsFixedRecordController
 *
 *
 */

#ifndef RPDB_DATABASE_FIXED_RECORD_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_FIXED_RECORD_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseFixedRecordSettingsController*	RPDB_DatabaseFixedRecordSettingsController_new(					RPDB_DatabaseSettingsController*					database_settings_controller );

	void											RPDB_DatabaseFixedRecordSettingsController_free(					RPDB_DatabaseFixedRecordSettingsController** database_fixed_record_settings_controller );
	RPDB_Environment*						RPDB_DatabaseFixedRecordSettingsController_parentEnvironment(	RPDB_DatabaseFixedRecordSettingsController* database_fixed_record_settings_controller );
	RPDB_Database* RPDB_DatabaseFixedRecordSettingsController_parentDatabase(	RPDB_DatabaseFixedRecordSettingsController* database_fixed_record_settings_controller );

	uint32_t										RPDB_DatabaseFixedRecordSettingsController_recordLength(			RPDB_DatabaseFixedRecordSettingsController*		database_fixed_record_settings_controller );
	void											RPDB_DatabaseFixedRecordSettingsController_setRecordLength(		RPDB_DatabaseFixedRecordSettingsController*		database_fixed_record_settings_controller,
																														uint32_t											record_length );
	int												RPDB_DatabaseFixedRecordSettingsController_paddingByte(			RPDB_DatabaseFixedRecordSettingsController*		database_fixed_record_settings_controller );
	void											RPDB_DatabaseFixedRecordSettingsController_setPaddingByte(			RPDB_DatabaseFixedRecordSettingsController*		database_fixed_record_settings_controller, 
																														int													record_padding_byte );

#endif

