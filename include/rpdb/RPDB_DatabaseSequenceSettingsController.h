/*
 *		RPDB::SettingsController::SequenceSettingsController
 *		RPDB::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence::DatabaseSequenceSettingsController
 *
 */

#ifndef RPDB_DATABASE_SEQUENCE_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_SEQUENCE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseSequenceSettingsController*		RPDB_DatabaseSequenceSettingsController_new(						RPDB_DatabaseSettingsController*			settings_controller );

	void											RPDB_DatabaseSequenceSettingsController_free(						RPDB_DatabaseSequenceSettingsController** database_sequence_settings_controller );
	RPDB_Environment*						RPDB_DatabaseSequenceSettingsController_parentEnvironment(	RPDB_DatabaseSequenceSettingsController* database_sequence_settings_controller );
	RPDB_Database* RPDB_DatabaseSequenceSettingsController_parentDatabase(	RPDB_DatabaseSequenceSettingsController* database_sequence_settings_controller );

	BOOL											RPDB_DatabaseSequenceSettingsController_increasing(				RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPDB_DatabaseSequenceSettingsController_setAsIncreasing(			RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller );
	BOOL											RPDB_DatabaseSequenceSettingsController_decreasing(				RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPDB_DatabaseSequenceSettingsController_setAsDecreasing(			RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller );
	BOOL											RPDB_DatabaseSequenceSettingsController_wrap(						RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPDB_DatabaseSequenceSettingsController_setToWrap(				RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller );
	int												RPDB_DatabaseSequenceSettingsController_rangeMinimum(				RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPDB_DatabaseSequenceSettingsController_setRangeMinimum(			RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller, 
																														db_seq_t									range_minimum );
	int												RPDB_DatabaseSequenceSettingsController_rangeMaximum(				RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPDB_DatabaseSequenceSettingsController_setRangeMaximum(			RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														db_seq_t									range_maximum );
	int												RPDB_DatabaseSequenceSettingsController_cacheSize(					RPDB_DatabaseSequenceSettingsController* 	sequence_settings_controller );
	void											RPDB_DatabaseSequenceSettingsController_setCacheSize(				RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														uint32_t										number_of_cached_elements	);
	db_seq_t										RPDB_DatabaseSequenceSettingsController_initialValue(				RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPDB_DatabaseSequenceSettingsController_setInitialValue(			RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														db_seq_t									initial_value );
	int32_t											RPDB_DatabaseSequenceSettingsController_defaultStepValue(			RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller );
	void											RPDB_DatabaseSequenceSettingsController_setDefaultStepValue(		RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														int32_t										default_step_value	);

#endif

