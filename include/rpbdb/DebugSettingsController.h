/*
 *		RPbdb_settingsController:RPbdb_DebugSettingsController
 *
 *
 */

#ifndef RPBDB_DEBUG_SETTINGS_CONTROLLER
	#define RPBDB_DEBUG_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DebugSettingsController*				RPbdb_DebugSettingsController_new(														RPbdb_SettingsController*			settings_controller );

	void										RPbdb_DebugSettingsController_free(														RPbdb_DebugSettingsController**		debug_settings_controller );
	RPbdb_Environment*					RPbdb_DebugSettingsController_parentEnvironment(							RPbdb_DebugSettingsController*		debug_settings_controller );

	int										RPbdb_DebugSettingsController_checkForEnvironmentFailureDuringOpen( RPbdb_DebugSettingsController* debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOn( RPbdb_DebugSettingsController* debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOff( RPbdb_DebugSettingsController* debug_settings_controller );

	int										RPbdb_DebugSettingsController_runNormalRecoveryBeforeOpeningEnvironment(				RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOn(			RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOff(			RPbdb_DebugSettingsController*		debug_settings_controller );

	int										RPbdb_DebugSettingsController_runCatastrophicRecoveryBeforeOpeningEnvironment(			RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnRunCatastrophicRecoveryBeforeOpeningEnvironmentOn(	RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnRunCatastrophicRecoveryBeforeOpeningEnvironmentOff(	RPbdb_DebugSettingsController*		debug_settings_controller );

	int										RPbdb_DebugSettingsController_openInLockdown(											RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnOpenInLockdownOn(										RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnOpenInLockdownOff(									RPbdb_DebugSettingsController*		debug_settings_controller );

	int										RPbdb_DebugSettingsController_registerForRecovery(					RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnRegisterForRecoveryOn(			RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnRegisterForRecoveryOff(			RPbdb_DebugSettingsController*		debug_settings_controller );

	int										RPbdb_DebugSettingsController_prohibitPanic(											RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnProhibitPanicOn(										RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnProhibitPanicOff(										RPbdb_DebugSettingsController*		debug_settings_controller );

	int										RPbdb_DebugSettingsController_panic(													RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnPanicOn(												RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnPanicOff( 											RPbdb_DebugSettingsController*		debug_settings_controller );

	int										RPbdb_DebugSettingsController_yieldCPUForStressTest(									RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnYieldCPUForStressTestOn(								RPbdb_DebugSettingsController*		debug_settings_controller );
	void										RPbdb_DebugSettingsController_turnYieldCPUForStressTestOff(								RPbdb_DebugSettingsController*		debug_settings_controller );

	RPbdb_DebugVerbositySettingsController* 	RPbdb_DebugSettingsController_verbositySettingsController(								RPbdb_DebugSettingsController*		debug_settings_controller );


#endif

