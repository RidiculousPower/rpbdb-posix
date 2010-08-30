/*
 *		RPDB::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController
 *
 *
 */

#ifndef RPDB_DATABASE_TYPE_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_TYPE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseTypeSettingsController*			RPDB_DatabaseTypeSettingsController_new(				RPDB_DatabaseSettingsController*		database_settings_controller );

	void											RPDB_DatabaseTypeSettingsController_free(				RPDB_DatabaseTypeSettingsController** database_type_settings_controller );
	RPDB_Environment*						RPDB_DatabaseTypeSettingsController_parentEnvironment(		RPDB_DatabaseTypeSettingsController* database_type_settings_controller );
	RPDB_Database* RPDB_DatabaseTypeSettingsController_parentDatabase(	RPDB_DatabaseTypeSettingsController* database_type_settings_controller );

	DBTYPE											RPDB_DatabaseTypeSettingsController_databaseType(		RPDB_DatabaseTypeSettingsController*	database_type_settings_controller );
	BOOL											RPDB_DatabaseTypeSettingsController_isBTree(			RPDB_DatabaseTypeSettingsController*	database_type_settings_controller );
	void											RPDB_DatabaseTypeSettingsController_setTypeToBTree(	RPDB_DatabaseTypeSettingsController*	database_type_settings_controller );
	BOOL											RPDB_DatabaseTypeSettingsController_isHash(			RPDB_DatabaseTypeSettingsController*	database_type_settings_controller );
	void											RPDB_DatabaseTypeSettingsController_setTypeToHash(		RPDB_DatabaseTypeSettingsController*	database_type_settings_controller );
	BOOL											RPDB_DatabaseTypeSettingsController_isRecno(			RPDB_DatabaseTypeSettingsController*	database_type_settings_controller );
	void											RPDB_DatabaseTypeSettingsController_setTypeToRecno(	RPDB_DatabaseTypeSettingsController*	database_type_settings_controller );
	BOOL											RPDB_DatabaseTypeSettingsController_isQueue(			RPDB_DatabaseTypeSettingsController*	database_type_settings_controller );
	void											RPDB_DatabaseTypeSettingsController_setTypeToQueue(	RPDB_DatabaseTypeSettingsController*	database_type_settings_controller );
	RPDB_DatabaseTypeBtreeSettingsController*		RPDB_DatabaseTypeSettingsController_btreeController(	RPDB_DatabaseTypeSettingsController*	database_type_settings_controller );
	RPDB_DatabaseTypeHashSettingsController* RPDB_DatabaseTypeSettingsController_hashController( RPDB_DatabaseTypeSettingsController* database_type_settings_controller );

#endif

