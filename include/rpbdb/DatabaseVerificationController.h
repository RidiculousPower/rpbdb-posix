/*
 *		RPbdb::DatabaseController::Database::DatabaseVerificationController
 *
 *
 */

#ifndef RPBDB_DATABASE_VERIFICATION_CONTROLLER
	#define RPBDB_DATABASE_VERIFICATION_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseVerificationController*			RPbdb_DatabaseVerificationController_new(					RPbdb_Database*							parent_database );

	void											RPbdb_DatabaseVerificationController_free(	RPbdb_DatabaseVerificationController** database_verification_controller );
	RPbdb_DatabaseVerificationSettingsController*	RPbdb_DatabaseVerificationController_settingsController(	RPbdb_DatabaseVerificationController* database_verification_controller );
	RPbdb_Environment*						RPbdb_DatabaseVerificationController_parentEnvironment(	RPbdb_DatabaseVerificationController* database_verification_controller );
	RPbdb_Database* RPbdb_DatabaseVerificationController_parentDatabase(	RPbdb_DatabaseVerificationController* database_verification_controller );

	RPbdb_Database*									RPbdb_DatabaseVerificationController_verifyDatabase(		RPbdb_DatabaseVerificationController*	database_verification_controller );
	RPbdb_DatabaseVerificationSettingsController*	RPbdb_DatabaseVerificationController_settingsController(	RPbdb_DatabaseVerificationController* 	database_verification_controller );

#endif

