/*
 *		RPDB_settingsController:RPDB_DebugSettingsController
 *
 *
 */

#ifndef RPDB_DEBUG_SETTINGS_CONTROLLER
	#define RPDB_DEBUG_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DebugSettingsController*				RPDB_DebugSettingsController_new(														RPDB_SettingsController*			settings_controller );

	void										RPDB_DebugSettingsController_free(														RPDB_DebugSettingsController**		debug_settings_controller );
	RPDB_Environment*					RPDB_DebugSettingsController_parentEnvironment(							RPDB_DebugSettingsController*		debug_settings_controller );

	int										RPDB_DebugSettingsController_checkForEnvironmentFailureDuringOpen( RPDB_DebugSettingsController* debug_settings_controller );
	void										RPDB_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOn( RPDB_DebugSettingsController* debug_settings_controller );
	void										RPDB_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOff( RPDB_DebugSettingsController* debug_settings_controller );

	int										RPDB_DebugSettingsController_runNormalRecoveryBeforeOpeningEnvironment(				RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOn(			RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOff(			RPDB_DebugSettingsController*		debug_settings_controller );

	int										RPDB_DebugSettingsController_runCatastrophicRecoveryBeforeOpeningEnvironment(			RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnRunCatastrophicRecoveryBeforeOpeningEnvironmentOn(	RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnRunCatastrophicRecoveryBeforeOpeningEnvironmentOff(	RPDB_DebugSettingsController*		debug_settings_controller );

	int										RPDB_DebugSettingsController_openInLockdown(											RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnOpenInLockdownOn(										RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnOpenInLockdownOff(									RPDB_DebugSettingsController*		debug_settings_controller );

	int										RPDB_DebugSettingsController_registerForRecovery(					RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnRegisterForRecoveryOn(			RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnRegisterForRecoveryOff(			RPDB_DebugSettingsController*		debug_settings_controller );

	int										RPDB_DebugSettingsController_prohibitPanic(											RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnProhibitPanicOn(										RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnProhibitPanicOff(										RPDB_DebugSettingsController*		debug_settings_controller );

	int										RPDB_DebugSettingsController_panic(													RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnPanicOn(												RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnPanicOff( 											RPDB_DebugSettingsController*		debug_settings_controller );

	int										RPDB_DebugSettingsController_yieldCPUForStressTest(									RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnYieldCPUForStressTestOn(								RPDB_DebugSettingsController*		debug_settings_controller );
	void										RPDB_DebugSettingsController_turnYieldCPUForStressTestOff(								RPDB_DebugSettingsController*		debug_settings_controller );

	RPDB_DebugVerbositySettingsController* 	RPDB_DebugSettingsController_verbositySettingsController(								RPDB_DebugSettingsController*		debug_settings_controller );


#endif

