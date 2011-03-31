/*
 *		RPbdb::Database::DatabaseSettingsController::DatabaseSettingsEncryptionController
 *
 *
 */

#ifndef RPBDB_DATABASE_ENCRYPTION_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_ENCRYPTION_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseEncryptionSettingsController*			RPbdb_DatabaseEncryptionSettingsController_new(											RPbdb_DatabaseSettingsController*				database_settings_controller );

	void												RPbdb_DatabaseEncryptionSettingsController_free(									RPbdb_DatabaseEncryptionSettingsController** database_encryption_settings_controller );
	RPbdb_Environment*							RPbdb_DatabaseEncryptionSettingsController_parentEnvironment(			RPbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller );
	RPbdb_Database* RPbdb_DatabaseEncryptionSettingsController_parentDatabase(	RPbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller );

	uint32_t											RPbdb_DatabaseEncryptionSettingsController_encrypted(									RPbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller );
	void												RPbdb_DatabaseEncryptionSettingsController_turnEncryptionOn(							RPbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller, 
																																				char*											encryption_password );
	void												RPbdb_DatabaseEncryptionSettingsController_turnEncryptionOff(							RPbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller, 
																																				char*											encryption_password );
	RPbdb_DatabaseEncryptionSettingsController*			RPbdb_DatabaseEncryptionSettingsController_internal_copyOfDefaultSettingsForInstance(	RPbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller );


#endif

