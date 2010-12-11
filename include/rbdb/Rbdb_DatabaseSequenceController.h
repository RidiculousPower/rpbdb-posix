/*
 *		Rbdb::DatabaseController::Database::DatabaseSequenceController
 *
 *
 */

#ifndef RBDB_DATABASE_SEQUENCE_CONTROLLER
	#define RBDB_DATABASE_SEQUENCE_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseSequenceController*			Rbdb_DatabaseSequenceController_new(					Rbdb_Database*						parent_database );

	void										Rbdb_DatabaseSequenceController_free(	Rbdb_DatabaseSequenceController** database_sequence_controller );

	void Rbdb_DatabaseSequenceController_closeAllSequences( Rbdb_DatabaseSequenceController* database_sequence_controller );
	void Rbdb_DatabaseSequenceController_freeAllSequences( Rbdb_DatabaseSequenceController* database_sequence_controller );

	Rbdb_DatabaseSequenceSettingsController*	Rbdb_DatabaseSequenceController_settingsController(	Rbdb_DatabaseSequenceController* database_sequence_controller );
	Rbdb_Environment*					Rbdb_DatabaseSequenceController_parentEnvironment(	Rbdb_DatabaseSequenceController* database_sequence_controller );
	Rbdb_Database* Rbdb_DatabaseSequenceController_parentDatabase(	Rbdb_DatabaseSequenceController* database_sequence_controller );

	Rbdb_DatabaseSequenceSettingsController*	Rbdb_DatabaseSequenceController_settingsController(	Rbdb_DatabaseSequenceController* 	database_sequence_controller );
	Rbdb_DatabaseSequence* Rbdb_DatabaseSequenceController_sequence(	Rbdb_DatabaseSequenceController*	database_sequence_controller,
																																					char*															storage_key );
	Rbdb_DatabaseSequence* Rbdb_DatabaseSequenceController_retrieveSequence(	Rbdb_DatabaseSequenceController*	database_sequence_controller,
																																						char*															storage_key );
	Rbdb_DatabaseSequence* Rbdb_DatabaseSequenceController_deleteSequence(	Rbdb_DatabaseSequenceController*	database_sequence_controller,
																																					char*															storage_key );
	Rbdb_DatabaseSequence* Rbdb_DatabaseSequenceController_renameSequence(	Rbdb_DatabaseSequenceController*	database_sequence_controller,
																																					char*															storage_key,
																																					char*															new_storage_key );

#endif

