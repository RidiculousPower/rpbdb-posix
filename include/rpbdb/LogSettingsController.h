/*
 *		RPbdb::SettingsController::LogSettingsController
 *
 *
 */

#ifndef RPBDB_LOG_SETTINGS_CONTROLLER
	#define RPBDB_LOG_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_LogSettingsController*		RPbdb_LogSettingsController_new(									RPbdb_SettingsController*			parent_settings_controller );

	void								RPbdb_LogSettingsController_free(									RPbdb_LogSettingsController**		log_settings_controller );
	RPbdb_Environment*			RPbdb_LogSettingsController_parentEnvironment(			RPbdb_LogSettingsController*		log_settings_controller );

	int								RPbdb_LogSettingsController_on(										RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnOn(									RPbdb_LogSettingsController*		log_settings_controller );
	BOOL								RPbdb_LogSettingsController_off(									RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnOff(								RPbdb_LogSettingsController*		log_settings_controller );

	int								RPbdb_LogSettingsController_disableSystemBuffering(								RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnDisableSystemBufferingOn(						RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnDisableSystemBufferingOff(						RPbdb_LogSettingsController*		log_settings_controller );

	int								RPbdb_LogSettingsController_flushBeforeReturnFromWrite(				RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnFlushBeforeReturnFromWriteOn(		RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnFlushBeforeReturnFromWriteOff(		RPbdb_LogSettingsController*		log_settings_controller );

	int								RPbdb_LogSettingsController_autoremoveLogs(							RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnAutoremoveLogsOn(					RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnAutoremoveOff(						RPbdb_LogSettingsController*		log_settings_controller );

	int								RPbdb_LogSettingsController_logInMemory(							RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnLogInMemoryOn(						RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnLogInMemoryOff(						RPbdb_LogSettingsController*		log_settings_controller );

	int								RPbdb_LogSettingsController_zeroAtCreation(							RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnZeroAtCreationOn(					RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnZeroAtCreationOff(					RPbdb_LogSettingsController*		log_settings_controller );

	int									RPbdb_LogSettingsController_forceFlushAfterRecordWrite(				RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnForceFlushAfterRecordWriteOn(		RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_turnForceFlushAfterRecordWriteOff(		RPbdb_LogSettingsController*		log_settings_controller );

	uint32_t							RPbdb_LogSettingsController_bufferSize(								RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_setBufferSize(							RPbdb_LogSettingsController*		log_settings_controller, 
																											uint32_t							buffer_size );

	char*								RPbdb_LogSettingsController_directory(								RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_setDirectory(							RPbdb_LogSettingsController*		log_settings_controller, 
																											char*								directory );

	int									RPbdb_LogSettingsController_mode(									RPbdb_LogSettingsController*		log_settings_controller );
	void									RPbdb_LogSettingsController_setMode(								RPbdb_LogSettingsController*		log_settings_controller, 
																											int									mode );
																											
	int									RPbdb_LogSettingsController_maxLogSize(								RPbdb_LogSettingsController*		log_settings_controller );
	void									RPbdb_LogSettingsController_setMaxLogSize(							RPbdb_LogSettingsController*		log_settings_controller, 
																											uint32_t							max_size );

	int									RPbdb_LogSettingsController_maxRegionSize(							RPbdb_LogSettingsController*		log_settings_controller );
	void								RPbdb_LogSettingsController_setMaxRegionSize(						RPbdb_LogSettingsController*		log_settings_controller, 
																											uint32_t							max_region_size );

#endif

