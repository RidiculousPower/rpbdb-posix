/*
 *		RPDB::DatabaseController::Database::DatabaseVerificationController
 *
 *
 */

#ifndef RPDB_DATABASE_VERIFICATION_CONTROLLER
	#define RPDB_DATABASE_VERIFICATION_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseVerificationController*			RPDB_DatabaseVerificationController_new(					RPDB_Database*							parent_database );

	void											RPDB_DatabaseVerificationController_free(	RPDB_DatabaseVerificationController** database_verification_controller );
	RPDB_DatabaseVerificationSettingsController*	RPDB_DatabaseVerificationController_settingsController(	RPDB_DatabaseVerificationController* database_verification_controller );
	RPDB_Environment*						RPDB_DatabaseVerificationController_parentEnvironment(	RPDB_DatabaseVerificationController* database_verification_controller );
	RPDB_Database* RPDB_DatabaseVerificationController_parentDatabase(	RPDB_DatabaseVerificationController* database_verification_controller );

	RPDB_Database*									RPDB_DatabaseVerificationController_verifyDatabase(		RPDB_DatabaseVerificationController*	database_verification_controller );
	RPDB_DatabaseVerificationSettingsController*	RPDB_DatabaseVerificationController_settingsController(	RPDB_DatabaseVerificationController* 	database_verification_controller );

#endif

