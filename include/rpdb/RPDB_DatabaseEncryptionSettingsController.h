/*
 *		RPDB::Database::DatabaseSettingsController::DatabaseSettingsEncryptionController
 *
 *
 */

#ifndef RPDB_DATABASE_ENCRYPTION_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_ENCRYPTION_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseEncryptionSettingsController*			RPDB_DatabaseEncryptionSettingsController_new(											RPDB_DatabaseSettingsController*				database_settings_controller );

	void												RPDB_DatabaseEncryptionSettingsController_free(									RPDB_DatabaseEncryptionSettingsController** database_encryption_settings_controller );
	RPDB_Environment*							RPDB_DatabaseEncryptionSettingsController_parentEnvironment(			RPDB_DatabaseEncryptionSettingsController* database_encryption_settings_controller );
	RPDB_Database* RPDB_DatabaseEncryptionSettingsController_parentDatabase(	RPDB_DatabaseEncryptionSettingsController* database_encryption_settings_controller );

	uint32_t											RPDB_DatabaseEncryptionSettingsController_encrypted(									RPDB_DatabaseEncryptionSettingsController*		database_encryption_settings_controller );
	void												RPDB_DatabaseEncryptionSettingsController_turnEncryptionOn(							RPDB_DatabaseEncryptionSettingsController*		database_encryption_settings_controller, 
																																				char*											encryption_password );
	void												RPDB_DatabaseEncryptionSettingsController_turnEncryptionOff(							RPDB_DatabaseEncryptionSettingsController*		database_encryption_settings_controller, 
																																				char*											encryption_password );
	RPDB_DatabaseEncryptionSettingsController*			RPDB_DatabaseEncryptionSettingsController_internal_copyOfDefaultSettingsForInstance(	RPDB_DatabaseEncryptionSettingsController*		database_encryption_settings_controller );


#endif

