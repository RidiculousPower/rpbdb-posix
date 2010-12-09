/*
 *		Rbdb::DatabaseController::Database::DatabaseVerificationController
 *
 *
 */

#ifndef Rbdb_DATABASE_VERIFICATION_CONTROLLER
	#define Rbdb_DATABASE_VERIFICATION_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseVerificationController*			Rbdb_DatabaseVerificationController_new(					Rbdb_Database*							parent_database );

	void											Rbdb_DatabaseVerificationController_free(	Rbdb_DatabaseVerificationController** database_verification_controller );
	Rbdb_DatabaseVerificationSettingsController*	Rbdb_DatabaseVerificationController_settingsController(	Rbdb_DatabaseVerificationController* database_verification_controller );
	Rbdb_Environment*						Rbdb_DatabaseVerificationController_parentEnvironment(	Rbdb_DatabaseVerificationController* database_verification_controller );
	Rbdb_Database* Rbdb_DatabaseVerificationController_parentDatabase(	Rbdb_DatabaseVerificationController* database_verification_controller );

	Rbdb_Database*									Rbdb_DatabaseVerificationController_verifyDatabase(		Rbdb_DatabaseVerificationController*	database_verification_controller );
	Rbdb_DatabaseVerificationSettingsController*	Rbdb_DatabaseVerificationController_settingsController(	Rbdb_DatabaseVerificationController* 	database_verification_controller );

#endif

