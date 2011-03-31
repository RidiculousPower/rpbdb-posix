/*
 *		RPbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeRecnoSettingsController
 *
 *
 */

#ifndef RPBDB_DATABASE_TYPE_RECNO_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_TYPE_RECNO_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseTypeRecnoSettingsController*						RPbdb_DatabaseTypeRecnoSettingsController_new(								RPbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller );

	void															RPbdb_DatabaseTypeRecnoSettingsController_free(	RPbdb_DatabaseTypeRecnoSettingsController** database_type_recno_settings_controller );
	RPbdb_Environment*										RPbdb_DatabaseTypeRecnoSettingsController_parentEnvironment(	RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller );
	RPbdb_Database* RPbdb_DatabaseTypeRecnoSettingsController_parentDatabase(	RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller );

	BOOL																RPbdb_DatabaseTypeRecnoSettingsController_recordRenumbering(				RPbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															RPbdb_DatabaseTypeRecnoSettingsController_turnRecordRenumberingOn(			RPbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															RPbdb_DatabaseTypeRecnoSettingsController_turnRecordRenumberingOff( 		RPbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );

	BOOL																RPbdb_DatabaseTypeRecnoSettingsController_snapshotIsolation(				RPbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															RPbdb_DatabaseTypeRecnoSettingsController_turnSnapshotIsolationOn(			RPbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															RPbdb_DatabaseTypeRecnoSettingsController_turnSnapshotIsolationOff(			RPbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );

	char*																RPbdb_DatabaseTypeRecnoSettingsController_sourceFile(						RPbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															RPbdb_DatabaseTypeRecnoSettingsController_setSourceFile(					RPbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller, char* file_path );

/*
	void															RPbdb_DatabaseTypeRecnoSettingsController_setAppendCallbackMethod(			RPbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller,
																																				int (*append_callback_method)(	RPbdb_Database*		database,
																																												RPbdb_Record*		record ) );
	void (*append_callback_method)(	RPbdb_Database*		database,
									RPbdb_Record*		record )	RPbdb_DatabaseTypeRecnoSettingsController_appendCallback( RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller );
*/
#endif

