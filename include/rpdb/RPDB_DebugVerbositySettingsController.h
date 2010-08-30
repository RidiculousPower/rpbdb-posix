/*
 *		RPDB_settingsController:RPDB_DebugSettingsController
 *
 *
 */

#ifndef RPDB_DEBUG_VERBOSITY_SETTINGS_CONTROLLER
	#define RPDB_DEBUG_VERBOSITY_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DebugVerbositySettingsController*		RPDB_DebugVerbositySettingsController_new(													RPDB_DebugSettingsController*			debug_settings_controller );

	void										RPDB_DebugVerbositySettingsController_free(												RPDB_DebugVerbositySettingsController** debug_verbosity_settings_controller );
	RPDB_Environment*					RPDB_DebugVerbositySettingsController_parentEnvironment(						RPDB_DebugVerbositySettingsController* debug_verbosity_settings_controller );

	BOOL										RPDB_DebugVerbositySettingsController_displayAdditionalInformationDuringRecovery(			RPDB_DebugVerbositySettingsController*		debug_verbosity_settings_controller );
	void										RPDB_DebugVerbositySettingsController_turnDisplayAdditionalInformationDuringRecoveryOn(	RPDB_DebugVerbositySettingsController*		debug_verbosity_settings_controller );
	void										RPDB_DebugVerbositySettingsController_turnDisplayAdditionalInformationDuringRecoveryOff(	RPDB_DebugVerbositySettingsController*		debug_verbosity_settings_controller );


#endif

