/*
 *		Rbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController
 *
 *
 */

#ifndef Rbdb_DATABASE_TYPE_SETTINGS_CONTROLLER
	#define Rbdb_DATABASE_TYPE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseTypeSettingsController*			Rbdb_DatabaseTypeSettingsController_new(				Rbdb_DatabaseSettingsController*		database_settings_controller );

	void											Rbdb_DatabaseTypeSettingsController_free(				Rbdb_DatabaseTypeSettingsController** database_type_settings_controller );
	Rbdb_Environment*						Rbdb_DatabaseTypeSettingsController_parentEnvironment(		Rbdb_DatabaseTypeSettingsController* database_type_settings_controller );
	Rbdb_Database* Rbdb_DatabaseTypeSettingsController_parentDatabase(	Rbdb_DatabaseTypeSettingsController* database_type_settings_controller );

	DBTYPE											Rbdb_DatabaseTypeSettingsController_databaseType(		Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	BOOL											Rbdb_DatabaseTypeSettingsController_isBTree(			Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	void											Rbdb_DatabaseTypeSettingsController_setTypeToBTree(	Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	BOOL											Rbdb_DatabaseTypeSettingsController_isHash(			Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	void											Rbdb_DatabaseTypeSettingsController_setTypeToHash(		Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	BOOL											Rbdb_DatabaseTypeSettingsController_isRecno(			Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	void											Rbdb_DatabaseTypeSettingsController_setTypeToRecno(	Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	BOOL											Rbdb_DatabaseTypeSettingsController_isQueue(			Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	void											Rbdb_DatabaseTypeSettingsController_setTypeToQueue(	Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	Rbdb_DatabaseTypeBtreeSettingsController*		Rbdb_DatabaseTypeSettingsController_btreeController(	Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller );
	Rbdb_DatabaseTypeHashSettingsController* Rbdb_DatabaseTypeSettingsController_hashController( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller );
	Rbdb_DatabaseTypeQueueSettingsController* Rbdb_DatabaseTypeSettingsController_queueController( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller );
	Rbdb_DatabaseTypeRecnoSettingsController* Rbdb_DatabaseTypeSettingsController_recnoController( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller );

#endif

