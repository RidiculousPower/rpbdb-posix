/*
 *		RPbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseSettingsFixedRecordController
 *
 *
 */

#ifndef RPBDB_DATABASE_FIXED_RECORD_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_FIXED_RECORD_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseRecordFixedLengthSettingsController*	RPbdb_DatabaseRecordFixedLengthSettingsController_new(					RPbdb_DatabaseRecordSettingsController*					database_settings_controller );

	void											RPbdb_DatabaseRecordFixedLengthSettingsController_free(					RPbdb_DatabaseRecordFixedLengthSettingsController** database_record_fixed_length_settings_controller );
	RPbdb_Environment*						RPbdb_DatabaseRecordFixedLengthSettingsController_parentEnvironment(	RPbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller );
	RPbdb_Database* RPbdb_DatabaseRecordFixedLengthSettingsController_parentDatabase(	RPbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller );

	uint32_t										RPbdb_DatabaseRecordFixedLengthSettingsController_recordLength(			RPbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller );
	void											RPbdb_DatabaseRecordFixedLengthSettingsController_setRecordLength(		RPbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller,
																														uint32_t											record_length );
	int												RPbdb_DatabaseRecordFixedLengthSettingsController_paddingByte(			RPbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller );
	void											RPbdb_DatabaseRecordFixedLengthSettingsController_setPaddingByte(			RPbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller, 
																														int													record_padding_byte );

#endif

