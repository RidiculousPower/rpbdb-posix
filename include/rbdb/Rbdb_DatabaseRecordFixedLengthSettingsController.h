/*
 *		Rbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseSettingsFixedRecordController
 *
 *
 */

#ifndef RBDB_DATABASE_FIXED_RECORD_SETTINGS_CONTROLLER
	#define RBDB_DATABASE_FIXED_RECORD_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseRecordFixedLengthSettingsController*	Rbdb_DatabaseRecordFixedLengthSettingsController_new(					Rbdb_DatabaseRecordSettingsController*					database_settings_controller );

	void											Rbdb_DatabaseRecordFixedLengthSettingsController_free(					Rbdb_DatabaseRecordFixedLengthSettingsController** database_record_fixed_length_settings_controller );
	Rbdb_Environment*						Rbdb_DatabaseRecordFixedLengthSettingsController_parentEnvironment(	Rbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller );
	Rbdb_Database* Rbdb_DatabaseRecordFixedLengthSettingsController_parentDatabase(	Rbdb_DatabaseRecordFixedLengthSettingsController* database_record_fixed_length_settings_controller );

	uint32_t										Rbdb_DatabaseRecordFixedLengthSettingsController_recordLength(			Rbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller );
	void											Rbdb_DatabaseRecordFixedLengthSettingsController_setRecordLength(		Rbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller,
																														uint32_t											record_length );
	int												Rbdb_DatabaseRecordFixedLengthSettingsController_paddingByte(			Rbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller );
	void											Rbdb_DatabaseRecordFixedLengthSettingsController_setPaddingByte(			Rbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller, 
																														int													record_padding_byte );

#endif

