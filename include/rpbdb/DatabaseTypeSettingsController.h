/*
 *		RPbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController
 *
 *
 */

#ifndef RPBDB_DATABASE_TYPE_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_TYPE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseTypeSettingsController*			RPbdb_DatabaseTypeSettingsController_new(				RPbdb_DatabaseSettingsController*		database_settings_controller );

	void											RPbdb_DatabaseTypeSettingsController_free(				RPbdb_DatabaseTypeSettingsController** database_type_settings_controller );
	RPbdb_Environment*						RPbdb_DatabaseTypeSettingsController_parentEnvironment(		RPbdb_DatabaseTypeSettingsController* database_type_settings_controller );
	RPbdb_Database* RPbdb_DatabaseTypeSettingsController_parentDatabase(	RPbdb_DatabaseTypeSettingsController* database_type_settings_controller );

	DBTYPE											RPbdb_DatabaseTypeSettingsController_databaseType(		RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	BOOL											RPbdb_DatabaseTypeSettingsController_isBTree(			RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	void											RPbdb_DatabaseTypeSettingsController_setTypeToBTree(	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	BOOL											RPbdb_DatabaseTypeSettingsController_isHash(			RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	void											RPbdb_DatabaseTypeSettingsController_setTypeToHash(		RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	BOOL											RPbdb_DatabaseTypeSettingsController_isRecno(			RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	void											RPbdb_DatabaseTypeSettingsController_setTypeToRecno(	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	BOOL											RPbdb_DatabaseTypeSettingsController_isQueue(			RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	void											RPbdb_DatabaseTypeSettingsController_setTypeToQueue(	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	RPbdb_DatabaseTypeBtreeSettingsController*		RPbdb_DatabaseTypeSettingsController_btreeController(	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	RPbdb_DatabaseTypeHashSettingsController* RPbdb_DatabaseTypeSettingsController_hashController( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller );
	RPbdb_DatabaseTypeQueueSettingsController* RPbdb_DatabaseTypeSettingsController_queueController( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller );
	RPbdb_DatabaseTypeRecnoSettingsController* RPbdb_DatabaseTypeSettingsController_recnoController( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller );

#endif

