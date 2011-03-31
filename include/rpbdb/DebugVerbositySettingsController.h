/*
 *		RPbdb_settingsController:RPbdb_DebugSettingsController
 *
 *
 */

#ifndef RPBDB_DEBUG_VERBOSITY_SETTINGS_CONTROLLER
	#define RPBDB_DEBUG_VERBOSITY_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DebugVerbositySettingsController*		RPbdb_DebugVerbositySettingsController_new(													RPbdb_DebugSettingsController*			debug_settings_controller );

	void										RPbdb_DebugVerbositySettingsController_free(												RPbdb_DebugVerbositySettingsController** debug_verbosity_settings_controller );
	RPbdb_Environment*					RPbdb_DebugVerbositySettingsController_parentEnvironment(						RPbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller );

	BOOL										RPbdb_DebugVerbositySettingsController_displayAdditionalInformationDuringRecovery(			RPbdb_DebugVerbositySettingsController*		debug_verbosity_settings_controller );
	void										RPbdb_DebugVerbositySettingsController_turnDisplayAdditionalInformationDuringRecoveryOn(	RPbdb_DebugVerbositySettingsController*		debug_verbosity_settings_controller );
	void										RPbdb_DebugVerbositySettingsController_turnDisplayAdditionalInformationDuringRecoveryOff(	RPbdb_DebugVerbositySettingsController*		debug_verbosity_settings_controller );


#endif

