/*
 *		RPbdb_settingsController:RPbdb_DebugSettingsController
 *
 *
 */

#ifndef RPBDB_DATABASE_VERBOSITY_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_VERBOSITY_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseVerbositySettingsController*	RPbdb_DatabaseVerbositySettingsController_new(															RPbdb_DatabaseSettingsController*					database_settings_controller );
	void										RPbdb_DatabaseVerbositySettingsController_free(															RPbdb_DatabaseVerbositySettingsController**			database_verbosity_settings_controller );
	RPbdb_Environment*					RPbdb_DatabaseVerbositySettingsController_parentEnvironment(								RPbdb_DatabaseVerbositySettingsController*			database_verbosity_settings_controller );
	RPbdb_Database* RPbdb_DatabaseVerbositySettingsController_parentDatabase(	RPbdb_DatabaseVerbositySettingsController* database_verbosity_settings_controller );

	int											RPbdb_DatabaseVerbositySettingsController_displayAdditionalInformationForDBRegisterFlag(				RPbdb_DatabaseVerbositySettingsController*			database_verbosity_settings_controller );
	void										RPbdb_DatabaseVerbositySettingsController_turnDisplayAdditionalInformationForDBRegisterFlagOn(			RPbdb_DatabaseVerbositySettingsController*			database_verbosity_settings_controller );
	void										RPbdb_DatabaseVerbositySettingsController_turnDisplayAdditionalInformationForDBRegisterFlagOff(			RPbdb_DatabaseVerbositySettingsController*			database_verbosity_settings_controller );

#endif

