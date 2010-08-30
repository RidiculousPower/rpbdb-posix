/*
 *		RPDB_settingsController:RPDB_DebugSettingsController
 *
 *
 */

#ifndef RPDB_DATABASE_VERBOSITY_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_VERBOSITY_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseVerbositySettingsController*	RPDB_DatabaseVerbositySettingsController_new(															RPDB_DatabaseSettingsController*					database_settings_controller );
	void										RPDB_DatabaseVerbositySettingsController_free(															RPDB_DatabaseVerbositySettingsController**			database_verbosity_settings_controller );
	RPDB_Environment*					RPDB_DatabaseVerbositySettingsController_parentEnvironment(								RPDB_DatabaseVerbositySettingsController*			database_verbosity_settings_controller );
	RPDB_Database* RPDB_DatabaseVerbositySettingsController_parentDatabase(	RPDB_DatabaseVerbositySettingsController* database_verbosity_settings_controller );

	int											RPDB_DatabaseVerbositySettingsController_displayAdditionalInformationForDBRegisterFlag(				RPDB_DatabaseVerbositySettingsController*			database_verbosity_settings_controller );
	void										RPDB_DatabaseVerbositySettingsController_turnDisplayAdditionalInformationForDBRegisterFlagOn(			RPDB_DatabaseVerbositySettingsController*			database_verbosity_settings_controller );
	void										RPDB_DatabaseVerbositySettingsController_turnDisplayAdditionalInformationForDBRegisterFlagOff(			RPDB_DatabaseVerbositySettingsController*			database_verbosity_settings_controller );

#endif

