/*
 *		Rbdb_settingsController:Rbdb_DebugSettingsController
 *
 *
 */

#ifndef RBDB_DEBUG_SETTINGS_CONTROLLER
	#define RBDB_DEBUG_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DebugSettingsController*				Rbdb_DebugSettingsController_new(														Rbdb_SettingsController*			settings_controller );

	void										Rbdb_DebugSettingsController_free(														Rbdb_DebugSettingsController**		debug_settings_controller );
	Rbdb_Environment*					Rbdb_DebugSettingsController_parentEnvironment(							Rbdb_DebugSettingsController*		debug_settings_controller );

	int										Rbdb_DebugSettingsController_checkForEnvironmentFailureDuringOpen( Rbdb_DebugSettingsController* debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOn( Rbdb_DebugSettingsController* debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOff( Rbdb_DebugSettingsController* debug_settings_controller );

	int										Rbdb_DebugSettingsController_runNormalRecoveryBeforeOpeningEnvironment(				Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOn(			Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOff(			Rbdb_DebugSettingsController*		debug_settings_controller );

	int										Rbdb_DebugSettingsController_runCatastrophicRecoveryBeforeOpeningEnvironment(			Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnRunCatastrophicRecoveryBeforeOpeningEnvironmentOn(	Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnRunCatastrophicRecoveryBeforeOpeningEnvironmentOff(	Rbdb_DebugSettingsController*		debug_settings_controller );

	int										Rbdb_DebugSettingsController_openInLockdown(											Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnOpenInLockdownOn(										Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnOpenInLockdownOff(									Rbdb_DebugSettingsController*		debug_settings_controller );

	int										Rbdb_DebugSettingsController_registerForRecovery(					Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnRegisterForRecoveryOn(			Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnRegisterForRecoveryOff(			Rbdb_DebugSettingsController*		debug_settings_controller );

	int										Rbdb_DebugSettingsController_prohibitPanic(											Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnProhibitPanicOn(										Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnProhibitPanicOff(										Rbdb_DebugSettingsController*		debug_settings_controller );

	int										Rbdb_DebugSettingsController_panic(													Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnPanicOn(												Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnPanicOff( 											Rbdb_DebugSettingsController*		debug_settings_controller );

	int										Rbdb_DebugSettingsController_yieldCPUForStressTest(									Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnYieldCPUForStressTestOn(								Rbdb_DebugSettingsController*		debug_settings_controller );
	void										Rbdb_DebugSettingsController_turnYieldCPUForStressTestOff(								Rbdb_DebugSettingsController*		debug_settings_controller );

	Rbdb_DebugVerbositySettingsController* 	Rbdb_DebugSettingsController_verbositySettingsController(								Rbdb_DebugSettingsController*		debug_settings_controller );


#endif

