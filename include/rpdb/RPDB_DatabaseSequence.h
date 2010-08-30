/*
 *		RPDB::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence
 *
 *
 */

#ifndef RPDB_DATABASE_SEQUENCE
	#define RPDB_DATABASE_SEQUENCE

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseSequence*		RPDB_DatabaseSequence_new(				RPDB_DatabaseSequenceController*	parent_database_sequence_controller );

	void						RPDB_DatabaseSequence_free(	RPDB_DatabaseSequence** database_sequence );
	RPDB_DatabaseSequenceSettingsController*	RPDB_DatabaseSequence_settingsController(	RPDB_DatabaseSequence* database_sequence );
	RPDB_Environment*					RPDB_DatabaseSequence_parentEnvironment(	RPDB_DatabaseSequence* database_sequence );
	RPDB_Database* RPDB_DatabaseSequence_parentDatabase(	RPDB_DatabaseSequence* database_sequence );

	RPDB_DatabaseSequence*		RPDB_DatabaseSequence_openSequence(	RPDB_DatabaseSequence*				database_sequence,
																		RPDB_Record*						stored_at_key	);
	void						RPDB_DatabaseSequence_closeSequence(	RPDB_DatabaseSequence*				database_sequence );
	void						RPDB_DatabaseSequence_deleteSequence(	RPDB_DatabaseSequence*				database_sequence );
	int32_t						RPDB_DatabaseSequence_step(			RPDB_DatabaseSequence*				database_sequence );
	int32_t						RPDB_DatabaseSequence_stepBy(			RPDB_DatabaseSequence*				database_sequence,
																		int32_t								step_value	);
	int32_t RPDB_DatabaseSequence_stepBackward( RPDB_DatabaseSequence*	database_sequence );
	int32_t RPDB_DatabaseSequence_stepBackwardBy(	RPDB_DatabaseSequence*	database_sequence,
																								int32_t									step_value	);
#endif

