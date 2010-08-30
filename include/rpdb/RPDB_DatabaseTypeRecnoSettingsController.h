/*
 *		RPDB::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeRecnoSettingsController
 *
 *
 */

#ifndef RPDB_DATABASE_TYPE_RECNO_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_TYPE_RECNO_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseTypeRecnoSettingsController*						RPDB_DatabaseTypeRecnoSettingsController_new(								RPDB_DatabaseTypeSettingsController*						parent_database_type_settings_controller );

	void															RPDB_DatabaseTypeRecnoSettingsController_free(	RPDB_DatabaseTypeRecnoSettingsController** database_type_recno_settings_controller );
	RPDB_Environment*										RPDB_DatabaseTypeRecnoSettingsController_parentEnvironment(	RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller );
	RPDB_Database* RPDB_DatabaseTypeRecnoSettingsController_parentDatabase(	RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller );

	BOOL																RPDB_DatabaseTypeRecnoSettingsController_recordRenumbering(				RPDB_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															RPDB_DatabaseTypeRecnoSettingsController_turnRecordRenumberingOn(			RPDB_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															RPDB_DatabaseTypeRecnoSettingsController_turnRecordRenumberingOff( 		RPDB_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );

	BOOL																RPDB_DatabaseTypeRecnoSettingsController_snapshotIsolation(				RPDB_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															RPDB_DatabaseTypeRecnoSettingsController_turnSnapshotIsolationOn(			RPDB_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															RPDB_DatabaseTypeRecnoSettingsController_turnSnapshotIsolationOff(			RPDB_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );

	char*																RPDB_DatabaseTypeRecnoSettingsController_sourceFile(						RPDB_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															RPDB_DatabaseTypeRecnoSettingsController_setSourceFile(					RPDB_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller, char* file_path );

/*
	void															RPDB_DatabaseTypeRecnoSettingsController_setAppendCallbackMethod(			RPDB_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller,
																																				int (*append_callback_method)(	RPDB_Database*		database,
																																												RPDB_Record*		record ) );
	void (*append_callback_method)(	RPDB_Database*		database,
									RPDB_Record*		record )	RPDB_DatabaseTypeRecnoSettingsController_appendCallback( RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller );
*/
#endif

