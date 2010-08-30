/*
 *		RPDB::DatabaseController::Database::DatabaseSequenceController
 *
 *
 */

#ifndef RPDB_DATABASE_SEQUENCE_CONTROLLER
	#define RPDB_DATABASE_SEQUENCE_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseSequenceController*			RPDB_DatabaseSequenceController_new(					RPDB_Database*						parent_database );

	void										RPDB_DatabaseSequenceController_free(	RPDB_DatabaseSequenceController** database_sequence_controller );
	RPDB_DatabaseSequenceSettingsController*	RPDB_DatabaseSequenceController_settingsController(	RPDB_DatabaseSequenceController* database_sequence_controller );
	RPDB_Environment*					RPDB_DatabaseSequenceController_parentEnvironment(	RPDB_DatabaseSequenceController* database_sequence_controller );
	RPDB_Database* RPDB_DatabaseSequenceController_parentDatabase(	RPDB_DatabaseSequenceController* database_sequence_controller );

	RPDB_DatabaseSequence*						RPDB_DatabaseSequenceController_createSequence(		RPDB_DatabaseSequenceController*	database_sequence_controller );
	RPDB_DatabaseSequenceSettingsController*	RPDB_DatabaseSequenceController_settingsController(	RPDB_DatabaseSequenceController* 	database_sequence_controller );

#endif

