/*
 *		Rbdb_settingsController:Rbdb_DebugSettingsController
 *
 *
 */

#ifndef RBDB_DATABASE_VERBOSITY_SETTINGS_CONTROLLER
	#define RBDB_DATABASE_VERBOSITY_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseVerbositySettingsController*	Rbdb_DatabaseVerbositySettingsController_new(															Rbdb_DatabaseSettingsController*					database_settings_controller );
	void										Rbdb_DatabaseVerbositySettingsController_free(															Rbdb_DatabaseVerbositySettingsController**			database_verbosity_settings_controller );
	Rbdb_Environment*					Rbdb_DatabaseVerbositySettingsController_parentEnvironment(								Rbdb_DatabaseVerbositySettingsController*			database_verbosity_settings_controller );
	Rbdb_Database* Rbdb_DatabaseVerbositySettingsController_parentDatabase(	Rbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller );

	int											Rbdb_DatabaseVerbositySettingsController_displayAdditionalInformationForDBRegisterFlag(				Rbdb_DatabaseVerbositySettingsController*			database_verbosity_settings_controller );
	void										Rbdb_DatabaseVerbositySettingsController_turnDisplayAdditionalInformationForDBRegisterFlagOn(			Rbdb_DatabaseVerbositySettingsController*			database_verbosity_settings_controller );
	void										Rbdb_DatabaseVerbositySettingsController_turnDisplayAdditionalInformationForDBRegisterFlagOff(			Rbdb_DatabaseVerbositySettingsController*			database_verbosity_settings_controller );

#endif

