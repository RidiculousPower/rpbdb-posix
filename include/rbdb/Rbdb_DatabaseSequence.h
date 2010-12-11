/*
 *		Rbdb::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence
 *
 *
 */

#ifndef RBDB_DATABASE_SEQUENCE
	#define RBDB_DATABASE_SEQUENCE

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseSequence* Rbdb_DatabaseSequence_new( Rbdb_DatabaseSequenceController*	parent_database_sequence_controller,
																										Rbdb_Database*										storage_database,
																										char*															storage_key );
	void						Rbdb_DatabaseSequence_free(	Rbdb_DatabaseSequence** database_sequence );
	Rbdb_DatabaseSequenceSettingsController*	Rbdb_DatabaseSequence_settingsController(	Rbdb_DatabaseSequence* database_sequence );
	Rbdb_Environment*					Rbdb_DatabaseSequence_parentEnvironment(	Rbdb_DatabaseSequence* database_sequence );
	Rbdb_Database* Rbdb_DatabaseSequence_parentDatabase(	Rbdb_DatabaseSequence* database_sequence );

	BOOL Rbdb_DatabaseSequence_isOpen( Rbdb_DatabaseSequence* database_sequence );
	Rbdb_DatabaseSequence*		Rbdb_DatabaseSequence_openSequence(	Rbdb_DatabaseSequence*				database_sequence	);
	void						Rbdb_DatabaseSequence_closeSequence(	Rbdb_DatabaseSequence*				database_sequence );
	void Rbdb_DatabaseSequence_renameSequence(	Rbdb_DatabaseSequence*	database_sequence,
																							char*										new_storage_key );
	void						Rbdb_DatabaseSequence_deleteSequence(	Rbdb_DatabaseSequence*				database_sequence );
int32_t Rbdb_DatabaseSequence_currentValue( Rbdb_DatabaseSequence*	database_sequence );
	int32_t						Rbdb_DatabaseSequence_step(			Rbdb_DatabaseSequence*				database_sequence );
	int32_t						Rbdb_DatabaseSequence_stepBy(			Rbdb_DatabaseSequence*				database_sequence,
																											int32_t								step_value	);
#endif

