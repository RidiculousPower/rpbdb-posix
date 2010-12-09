/*
 *		Rbdb::Database::DatabaseSettingsController::DatabaseSettingsEncryptionController
 *
 *
 */

#ifndef Rbdb_DATABASE_ENCRYPTION_SETTINGS_CONTROLLER
	#define Rbdb_DATABASE_ENCRYPTION_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseEncryptionSettingsController*			Rbdb_DatabaseEncryptionSettingsController_new(											Rbdb_DatabaseSettingsController*				database_settings_controller );

	void												Rbdb_DatabaseEncryptionSettingsController_free(									Rbdb_DatabaseEncryptionSettingsController** database_encryption_settings_controller );
	Rbdb_Environment*							Rbdb_DatabaseEncryptionSettingsController_parentEnvironment(			Rbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller );
	Rbdb_Database* Rbdb_DatabaseEncryptionSettingsController_parentDatabase(	Rbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller );

	uint32_t											Rbdb_DatabaseEncryptionSettingsController_encrypted(									Rbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller );
	void												Rbdb_DatabaseEncryptionSettingsController_turnEncryptionOn(							Rbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller, 
																																				char*											encryption_password );
	void												Rbdb_DatabaseEncryptionSettingsController_turnEncryptionOff(							Rbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller, 
																																				char*											encryption_password );
	Rbdb_DatabaseEncryptionSettingsController*			Rbdb_DatabaseEncryptionSettingsController_internal_copyOfDefaultSettingsForInstance(	Rbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller );


#endif

