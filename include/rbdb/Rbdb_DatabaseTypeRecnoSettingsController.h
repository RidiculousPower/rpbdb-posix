/*
 *		Rbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeRecnoSettingsController
 *
 *
 */

#ifndef Rbdb_DATABASE_TYPE_RECNO_SETTINGS_CONTROLLER
	#define Rbdb_DATABASE_TYPE_RECNO_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseTypeRecnoSettingsController*						Rbdb_DatabaseTypeRecnoSettingsController_new(								Rbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller );

	void															Rbdb_DatabaseTypeRecnoSettingsController_free(	Rbdb_DatabaseTypeRecnoSettingsController** database_type_recno_settings_controller );
	Rbdb_Environment*										Rbdb_DatabaseTypeRecnoSettingsController_parentEnvironment(	Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller );
	Rbdb_Database* Rbdb_DatabaseTypeRecnoSettingsController_parentDatabase(	Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller );

	BOOL																Rbdb_DatabaseTypeRecnoSettingsController_recordRenumbering(				Rbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															Rbdb_DatabaseTypeRecnoSettingsController_turnRecordRenumberingOn(			Rbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															Rbdb_DatabaseTypeRecnoSettingsController_turnRecordRenumberingOff( 		Rbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );

	BOOL																Rbdb_DatabaseTypeRecnoSettingsController_snapshotIsolation(				Rbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															Rbdb_DatabaseTypeRecnoSettingsController_turnSnapshotIsolationOn(			Rbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															Rbdb_DatabaseTypeRecnoSettingsController_turnSnapshotIsolationOff(			Rbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );

	char*																Rbdb_DatabaseTypeRecnoSettingsController_sourceFile(						Rbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller );
	void															Rbdb_DatabaseTypeRecnoSettingsController_setSourceFile(					Rbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller, char* file_path );

/*
	void															Rbdb_DatabaseTypeRecnoSettingsController_setAppendCallbackMethod(			Rbdb_DatabaseTypeRecnoSettingsController*			database_type_recno_settings_controller,
																																				int (*append_callback_method)(	Rbdb_Database*		database,
																																												Rbdb_Record*		record ) );
	void (*append_callback_method)(	Rbdb_Database*		database,
									Rbdb_Record*		record )	Rbdb_DatabaseTypeRecnoSettingsController_appendCallback( Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller );
*/
#endif

