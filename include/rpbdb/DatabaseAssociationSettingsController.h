/*
 *		RPbdb::Database::DatabaseSettingsController::DatabaseAssociationSettingsController
 *
 *
 */

#ifndef RPBDB_DATABASE_ASSOCIATION_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_ASSOCIATION_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseAssociationSettingsController*		RPbdb_DatabaseAssociationSettingsController_new(								RPbdb_DatabaseSettingsController*		database_settings_controller );

	void												RPbdb_DatabaseAssociationSettingsController_free(	RPbdb_DatabaseAssociationSettingsController** database_association_settings_controller );
	RPbdb_Environment*							RPbdb_DatabaseAssociationSettingsController_parentEnvironment(	RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller );
	RPbdb_Database* RPbdb_DatabaseAssociationSettingsController_parentDatabase(	RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller );

	BOOL												RPbdb_DatabaseAssociationSettingsController_secondaryAssociationCreatesIndex(						RPbdb_DatabaseAssociationSettingsController*		database_association_settings_controller );
	void												RPbdb_DatabaseAssociationSettingsController_turnSecondaryAssociationCreatesIndexOn(					RPbdb_DatabaseAssociationSettingsController*		database_association_settings_controller );
	void												RPbdb_DatabaseAssociationSettingsController_turnSecondaryAssociationCreatesIndexOff(				RPbdb_DatabaseAssociationSettingsController*		database_association_settings_controller );
	BOOL												RPbdb_DatabaseAssociationSettingsController_immutableSecondaryKey(				RPbdb_DatabaseAssociationSettingsController*		database_association_settings_controller );
	void												RPbdb_DatabaseAssociationSettingsController_turnImmutableSecondaryKeyOn(		RPbdb_DatabaseAssociationSettingsController*		database_association_settings_controller );
	void													RPbdb_DatabaseAssociationSettingsController_turnImmutableSecondaryKeyOff(		RPbdb_DatabaseAssociationSettingsController*		database_association_settings_controller );

#endif

