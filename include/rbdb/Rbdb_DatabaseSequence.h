/*
 *		Rbdb::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence
 *
 *
 */

#ifndef Rbdb_DATABASE_SEQUENCE
	#define Rbdb_DATABASE_SEQUENCE

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseSequence*		Rbdb_DatabaseSequence_new(				Rbdb_DatabaseSequenceController*	parent_database_sequence_controller );

	void						Rbdb_DatabaseSequence_free(	Rbdb_DatabaseSequence** database_sequence );
	Rbdb_DatabaseSequenceSettingsController*	Rbdb_DatabaseSequence_settingsController(	Rbdb_DatabaseSequence* database_sequence );
	Rbdb_Environment*					Rbdb_DatabaseSequence_parentEnvironment(	Rbdb_DatabaseSequence* database_sequence );
	Rbdb_Database* Rbdb_DatabaseSequence_parentDatabase(	Rbdb_DatabaseSequence* database_sequence );

	Rbdb_DatabaseSequence*		Rbdb_DatabaseSequence_openSequence(	Rbdb_DatabaseSequence*				database_sequence,
																		Rbdb_Record*						stored_at_key	);
	void						Rbdb_DatabaseSequence_closeSequence(	Rbdb_DatabaseSequence*				database_sequence );
	void						Rbdb_DatabaseSequence_deleteSequence(	Rbdb_DatabaseSequence*				database_sequence );
	int32_t						Rbdb_DatabaseSequence_step(			Rbdb_DatabaseSequence*				database_sequence );
	int32_t						Rbdb_DatabaseSequence_stepBy(			Rbdb_DatabaseSequence*				database_sequence,
																		int32_t								step_value	);
	int32_t Rbdb_DatabaseSequence_stepBackward( Rbdb_DatabaseSequence*	database_sequence );
	int32_t Rbdb_DatabaseSequence_stepBackwardBy(	Rbdb_DatabaseSequence*	database_sequence,
																								int32_t									step_value	);
#endif

