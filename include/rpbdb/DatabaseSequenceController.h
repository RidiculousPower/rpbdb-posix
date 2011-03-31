/*
 *		RPbdb::DatabaseController::Database::DatabaseSequenceController
 *
 *
 */

#ifndef RPBDB_DATABASE_SEQUENCE_CONTROLLER
	#define RPBDB_DATABASE_SEQUENCE_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseSequenceController*			RPbdb_DatabaseSequenceController_new(					RPbdb_Database*						parent_database );

	void										RPbdb_DatabaseSequenceController_free(	RPbdb_DatabaseSequenceController** database_sequence_controller );

	void RPbdb_DatabaseSequenceController_closeAllSequences( RPbdb_DatabaseSequenceController* database_sequence_controller );
	void RPbdb_DatabaseSequenceController_freeAllSequences( RPbdb_DatabaseSequenceController* database_sequence_controller );

	RPbdb_DatabaseSequenceSettingsController*	RPbdb_DatabaseSequenceController_settingsController(	RPbdb_DatabaseSequenceController* database_sequence_controller );
	RPbdb_Environment*					RPbdb_DatabaseSequenceController_parentEnvironment(	RPbdb_DatabaseSequenceController* database_sequence_controller );
	RPbdb_Database* RPbdb_DatabaseSequenceController_parentDatabase(	RPbdb_DatabaseSequenceController* database_sequence_controller );

	RPbdb_DatabaseSequenceSettingsController*	RPbdb_DatabaseSequenceController_settingsController(	RPbdb_DatabaseSequenceController* 	database_sequence_controller );
	RPbdb_DatabaseSequence* RPbdb_DatabaseSequenceController_sequence(	RPbdb_DatabaseSequenceController*	database_sequence_controller,
																																					char*															storage_key );
	RPbdb_DatabaseSequence* RPbdb_DatabaseSequenceController_retrieveSequence(	RPbdb_DatabaseSequenceController*	database_sequence_controller,
																																						char*															storage_key );
	RPbdb_DatabaseSequence* RPbdb_DatabaseSequenceController_deleteSequence(	RPbdb_DatabaseSequenceController*	database_sequence_controller,
																																					char*															storage_key );
	RPbdb_DatabaseSequence* RPbdb_DatabaseSequenceController_renameSequence(	RPbdb_DatabaseSequenceController*	database_sequence_controller,
																																					char*															storage_key,
																																					char*															new_storage_key );

#endif

