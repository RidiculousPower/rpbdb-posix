/*
 *		Rbdb::SettingsController::SequenceSettingsController
 *		Rbdb::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence::DatabaseSequenceSettingsController
 *
 */

#ifndef Rbdb_DATABASE_SEQUENCE_SETTINGS_CONTROLLER
	#define Rbdb_DATABASE_SEQUENCE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseSequenceSettingsController*		Rbdb_DatabaseSequenceSettingsController_new(						Rbdb_DatabaseSettingsController*			settings_controller );

	void											Rbdb_DatabaseSequenceSettingsController_free(						Rbdb_DatabaseSequenceSettingsController** database_sequence_settings_controller );
	Rbdb_Environment*						Rbdb_DatabaseSequenceSettingsController_parentEnvironment(	Rbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller );
	Rbdb_Database* Rbdb_DatabaseSequenceSettingsController_parentDatabase(	Rbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller );

	BOOL											Rbdb_DatabaseSequenceSettingsController_increasing(				Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											Rbdb_DatabaseSequenceSettingsController_setAsIncreasing(			Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	BOOL											Rbdb_DatabaseSequenceSettingsController_decreasing(				Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											Rbdb_DatabaseSequenceSettingsController_setAsDecreasing(			Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	BOOL											Rbdb_DatabaseSequenceSettingsController_wrap(						Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											Rbdb_DatabaseSequenceSettingsController_setToWrap(				Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	int												Rbdb_DatabaseSequenceSettingsController_rangeMinimum(				Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											Rbdb_DatabaseSequenceSettingsController_setRangeMinimum(			Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller, 
																														db_seq_t									range_minimum );
	int												Rbdb_DatabaseSequenceSettingsController_rangeMaximum(				Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											Rbdb_DatabaseSequenceSettingsController_setRangeMaximum(			Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														db_seq_t									range_maximum );
	int												Rbdb_DatabaseSequenceSettingsController_cacheSize(					Rbdb_DatabaseSequenceSettingsController* 	sequence_settings_controller );
	void											Rbdb_DatabaseSequenceSettingsController_setCacheSize(				Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														uint32_t										number_of_cached_elements	);
	db_seq_t										Rbdb_DatabaseSequenceSettingsController_initialValue(				Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											Rbdb_DatabaseSequenceSettingsController_setInitialValue(			Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														db_seq_t									initial_value );
	int32_t											Rbdb_DatabaseSequenceSettingsController_defaultStepValue(			Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											Rbdb_DatabaseSequenceSettingsController_setDefaultStepValue(		Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														int32_t										default_step_value	);

#endif

