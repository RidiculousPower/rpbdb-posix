/*
 *		Rbdb::Database::DatabaseSettingsController::DatabaseAssociationSettingsController
 *
 *
 */

#ifndef Rbdb_DATABASE_ASSOCIATION_SETTINGS_CONTROLLER
	#define Rbdb_DATABASE_ASSOCIATION_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseAssociationSettingsController*		Rbdb_DatabaseAssociationSettingsController_new(								Rbdb_DatabaseSettingsController*		database_settings_controller );

	void												Rbdb_DatabaseAssociationSettingsController_free(	Rbdb_DatabaseAssociationSettingsController** database_association_settings_controller );
	Rbdb_Environment*							Rbdb_DatabaseAssociationSettingsController_parentEnvironment(	Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller );
	Rbdb_Database* Rbdb_DatabaseAssociationSettingsController_parentDatabase(	Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller );

	BOOL												Rbdb_DatabaseAssociationSettingsController_secondaryAssociationCreatesIndex(						Rbdb_DatabaseAssociationSettingsController*		database_association_settings_controller );
	void												Rbdb_DatabaseAssociationSettingsController_turnSecondaryAssociationCreatesIndexOn(					Rbdb_DatabaseAssociationSettingsController*		database_association_settings_controller );
	void												Rbdb_DatabaseAssociationSettingsController_turnSecondaryAssociationCreatesIndexOff(				Rbdb_DatabaseAssociationSettingsController*		database_association_settings_controller );
	BOOL												Rbdb_DatabaseAssociationSettingsController_immutableSecondaryKey(				Rbdb_DatabaseAssociationSettingsController*		database_association_settings_controller );
	void												Rbdb_DatabaseAssociationSettingsController_turnImmutableSecondaryKeyOn(		Rbdb_DatabaseAssociationSettingsController*		database_association_settings_controller );
	void													Rbdb_DatabaseAssociationSettingsController_turnImmutableSecondaryKeyOff(		Rbdb_DatabaseAssociationSettingsController*		database_association_settings_controller );

#endif

