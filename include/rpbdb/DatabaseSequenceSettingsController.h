/*
 *		RPbdb::SettingsController::SequenceSettingsController
 *		RPbdb::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence::DatabaseSequenceSettingsController
 *
 */

#ifndef RPBDB_DATABASE_SEQUENCE_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_SEQUENCE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseSequenceSettingsController*		RPbdb_DatabaseSequenceSettingsController_new(						RPbdb_DatabaseSettingsController*			settings_controller );

	void											RPbdb_DatabaseSequenceSettingsController_free(						RPbdb_DatabaseSequenceSettingsController** database_sequence_settings_controller );
	RPbdb_Environment*						RPbdb_DatabaseSequenceSettingsController_parentEnvironment(	RPbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller );
	RPbdb_Database* RPbdb_DatabaseSequenceSettingsController_parentDatabase(	RPbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller );

	BOOL											RPbdb_DatabaseSequenceSettingsController_increasing(				RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPbdb_DatabaseSequenceSettingsController_setAsIncreasing(			RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	BOOL											RPbdb_DatabaseSequenceSettingsController_decreasing(				RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPbdb_DatabaseSequenceSettingsController_setAsDecreasing(			RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	BOOL											RPbdb_DatabaseSequenceSettingsController_wrap(						RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPbdb_DatabaseSequenceSettingsController_setToWrap(				RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	int												RPbdb_DatabaseSequenceSettingsController_rangeMinimum(				RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPbdb_DatabaseSequenceSettingsController_setRangeMinimum(			RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller, 
																														db_seq_t									range_minimum );
	int												RPbdb_DatabaseSequenceSettingsController_rangeMaximum(				RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPbdb_DatabaseSequenceSettingsController_setRangeMaximum(			RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														db_seq_t									range_maximum );
	int												RPbdb_DatabaseSequenceSettingsController_cacheSize(					RPbdb_DatabaseSequenceSettingsController* 	sequence_settings_controller );
	void											RPbdb_DatabaseSequenceSettingsController_setCacheSize(				RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														uint32_t										number_of_cached_elements	);
	db_seq_t										RPbdb_DatabaseSequenceSettingsController_initialValue(				RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPbdb_DatabaseSequenceSettingsController_setInitialValue(			RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														db_seq_t									initial_value );
	int32_t											RPbdb_DatabaseSequenceSettingsController_defaultStepValue(			RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPbdb_DatabaseSequenceSettingsController_setDefaultStepValue(		RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														int32_t										default_step_value	);

#endif

