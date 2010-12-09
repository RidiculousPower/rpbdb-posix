/*
 *		Rbdb_settingsController:Rbdb_DebugSettingsController
 *
 *
 */

#ifndef Rbdb_DEBUG_VERBOSITY_SETTINGS_CONTROLLER
	#define Rbdb_DEBUG_VERBOSITY_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DebugVerbositySettingsController*		Rbdb_DebugVerbositySettingsController_new(													Rbdb_DebugSettingsController*			debug_settings_controller );

	void										Rbdb_DebugVerbositySettingsController_free(												Rbdb_DebugVerbositySettingsController** debug_verbosity_settings_controller );
	Rbdb_Environment*					Rbdb_DebugVerbositySettingsController_parentEnvironment(						Rbdb_DebugVerbositySettingsController* debug_verbosity_settings_controller );

	BOOL										Rbdb_DebugVerbositySettingsController_displayAdditionalInformationDuringRecovery(			Rbdb_DebugVerbositySettingsController*		debug_verbosity_settings_controller );
	void										Rbdb_DebugVerbositySettingsController_turnDisplayAdditionalInformationDuringRecoveryOn(	Rbdb_DebugVerbositySettingsController*		debug_verbosity_settings_controller );
	void										Rbdb_DebugVerbositySettingsController_turnDisplayAdditionalInformationDuringRecoveryOff(	Rbdb_DebugVerbositySettingsController*		debug_verbosity_settings_controller );


#endif

