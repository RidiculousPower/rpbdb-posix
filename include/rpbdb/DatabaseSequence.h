/*
 *		RPbdb::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence
 *
 *
 */

#ifndef RPBDB_DATABASE_SEQUENCE
	#define RPBDB_DATABASE_SEQUENCE

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseSequence* RPbdb_DatabaseSequence_new( RPbdb_DatabaseSequenceController*	parent_database_sequence_controller,
																										RPbdb_Database*										storage_database,
																										char*															storage_key );
	void						RPbdb_DatabaseSequence_free(	RPbdb_DatabaseSequence** database_sequence );
	RPbdb_DatabaseSequenceSettingsController*	RPbdb_DatabaseSequence_settingsController(	RPbdb_DatabaseSequence* database_sequence );
	RPbdb_Environment*					RPbdb_DatabaseSequence_parentEnvironment(	RPbdb_DatabaseSequence* database_sequence );
	RPbdb_Database* RPbdb_DatabaseSequence_parentDatabase(	RPbdb_DatabaseSequence* database_sequence );

	BOOL RPbdb_DatabaseSequence_isOpen( RPbdb_DatabaseSequence* database_sequence );
	RPbdb_DatabaseSequence*		RPbdb_DatabaseSequence_openSequence(	RPbdb_DatabaseSequence*				database_sequence	);
	void						RPbdb_DatabaseSequence_closeSequence(	RPbdb_DatabaseSequence*				database_sequence );
	void RPbdb_DatabaseSequence_renameSequence(	RPbdb_DatabaseSequence*	database_sequence,
																							char*										new_storage_key );
	void						RPbdb_DatabaseSequence_deleteSequence(	RPbdb_DatabaseSequence*				database_sequence );
int32_t RPbdb_DatabaseSequence_currentValue( RPbdb_DatabaseSequence*	database_sequence );
	int32_t						RPbdb_DatabaseSequence_step(			RPbdb_DatabaseSequence*				database_sequence );
	int32_t						RPbdb_DatabaseSequence_stepBy(			RPbdb_DatabaseSequence*				database_sequence,
																											int32_t								step_value	);
#endif

