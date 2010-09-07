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

	RPDB_DatabaseRecordFixedLengthSettingsController*	RPDB_DatabaseRecordFixedLengthSettingsController_new(					RPDB_DatabaseRecordSettingsController*					database_settings_controller );

	void											RPDB_DatabaseRecordFixedLengthSettingsController_free(					RPDB_DatabaseRecordFixedLengthSettingsController** database_record_fixed_length_settings_controller );
	RPDB_Environment*						RPDB_DatabaseRecordFixedLengthSettingsController_parentEnvironment(	RPDB_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller );
	RPDB_Database* RPDB_DatabaseRecordFixedLengthSettingsController_parentDatabase(	RPDB_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller );

	uint32_t										RPDB_DatabaseRecordFixedLengthSettingsController_recordLength(			RPDB_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller );
	void											RPDB_DatabaseRecordFixedLengthSettingsController_setRecordLength(		RPDB_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller,
																														uint32_t											record_length );
	int												RPDB_DatabaseRecordFixedLengthSettingsController_paddingByte(			RPDB_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller );
	void											RPDB_DatabaseRecordFixedLengthSettingsController_setPaddingByte(			RPDB_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller, 
																														int													record_padding_byte );

#endif

