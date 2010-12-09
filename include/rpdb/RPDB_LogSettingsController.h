/*
 *		Rbdb::SettingsController::LogSettingsController
 *
 *
 */

#ifndef Rbdb_LOG_SETTINGS_CONTROLLER
	#define Rbdb_LOG_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_LogSettingsController*		Rbdb_LogSettingsController_new(									Rbdb_SettingsController*			parent_settings_controller );

	void								Rbdb_LogSettingsController_free(									Rbdb_LogSettingsController**		log_settings_controller );
	Rbdb_Environment*			Rbdb_LogSettingsController_parentEnvironment(			Rbdb_LogSettingsController*		log_settings_controller );

	int								Rbdb_LogSettingsController_on(										Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnOn(									Rbdb_LogSettingsController*		log_settings_controller );
	BOOL								Rbdb_LogSettingsController_off(									Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnOff(								Rbdb_LogSettingsController*		log_settings_controller );

	int								Rbdb_LogSettingsController_disableSystemBuffering(								Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnDisableSystemBufferingOn(						Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnDisableSystemBufferingOff(						Rbdb_LogSettingsController*		log_settings_controller );

	int								Rbdb_LogSettingsController_flushBeforeReturnFromWrite(				Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnFlushBeforeReturnFromWriteOn(		Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnFlushBeforeReturnFromWriteOff(		Rbdb_LogSettingsController*		log_settings_controller );

	int								Rbdb_LogSettingsController_autoremoveLogs(							Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnAutoremoveLogsOn(					Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnAutoremoveOff(						Rbdb_LogSettingsController*		log_settings_controller );

	int								Rbdb_LogSettingsController_logInMemory(							Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnLogInMemoryOn(						Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnLogInMemoryOff(						Rbdb_LogSettingsController*		log_settings_controller );

	int								Rbdb_LogSettingsController_zeroAtCreation(							Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnZeroAtCreationOn(					Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnZeroAtCreationOff(					Rbdb_LogSettingsController*		log_settings_controller );

	int									Rbdb_LogSettingsController_forceFlushAfterRecordWrite(				Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnForceFlushAfterRecordWriteOn(		Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_turnForceFlushAfterRecordWriteOff(		Rbdb_LogSettingsController*		log_settings_controller );

	uint32_t							Rbdb_LogSettingsController_bufferSize(								Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_setBufferSize(							Rbdb_LogSettingsController*		log_settings_controller, 
																											uint32_t							buffer_size );

	char*								Rbdb_LogSettingsController_directory(								Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_setDirectory(							Rbdb_LogSettingsController*		log_settings_controller, 
																											char*								directory );

	int									Rbdb_LogSettingsController_mode(									Rbdb_LogSettingsController*		log_settings_controller );
	void									Rbdb_LogSettingsController_setMode(								Rbdb_LogSettingsController*		log_settings_controller, 
																											int									mode );
																											
	int									Rbdb_LogSettingsController_maxLogSize(								Rbdb_LogSettingsController*		log_settings_controller );
	void									Rbdb_LogSettingsController_setMaxLogSize(							Rbdb_LogSettingsController*		log_settings_controller, 
																											uint32_t							max_size );

	int									Rbdb_LogSettingsController_maxRegionSize(							Rbdb_LogSettingsController*		log_settings_controller );
	void								Rbdb_LogSettingsController_setMaxRegionSize(						Rbdb_LogSettingsController*		log_settings_controller, 
																											uint32_t							max_region_size );

#endif

