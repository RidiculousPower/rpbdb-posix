/*
 *		RPDB::Database::DatabaseSettingsController::DatabaseAssociationSettingsController
 *
 *
 */

#ifndef RPDB_DATABASE_ASSOCIATION_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_ASSOCIATION_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseAssociationSettingsController*		RPDB_DatabaseAssociationSettingsController_new(								RPDB_DatabaseSettingsController*		database_settings_controller );

	void												RPDB_DatabaseAssociationSettingsController_free(	RPDB_DatabaseAssociationSettingsController** database_association_settings_controller );
	RPDB_Environment*							RPDB_DatabaseAssociationSettingsController_parentEnvironment(	RPDB_DatabaseAssociationSettingsController* database_association_settings_controller );
	RPDB_Database* RPDB_DatabaseAssociationSettingsController_parentDatabase(	RPDB_DatabaseAssociationSettingsController* database_association_settings_controller );

	BOOL												RPDB_DatabaseAssociationSettingsController_secondaryAssociationCreatesIndex(						RPDB_DatabaseAssociationSettingsController*		database_association_settings_controller );
	void												RPDB_DatabaseAssociationSettingsController_turnSecondaryAssociationCreatesIndexOn(					RPDB_DatabaseAssociationSettingsController*		database_association_settings_controller );
	void												RPDB_DatabaseAssociationSettingsController_turnSecondaryAssociationCreatesIndexOff(				RPDB_DatabaseAssociationSettingsController*		database_association_settings_controller );
	BOOL												RPDB_DatabaseAssociationSettingsController_immutableSecondaryKey(				RPDB_DatabaseAssociationSettingsController*		database_association_settings_controller );
	void												RPDB_DatabaseAssociationSettingsController_turnImmutableSecondaryKeyOn(		RPDB_DatabaseAssociationSettingsController*		database_association_settings_controller );
	void													RPDB_DatabaseAssociationSettingsController_turnImmutableSecondaryKeyOff(		RPDB_DatabaseAssociationSettingsController*		database_association_settings_controller );

#endif

