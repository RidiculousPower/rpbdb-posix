/*
 *		RPDB::SettingsController::LogSettingsController
 *
 *
 */

#ifndef RPDB_LOG_SETTINGS_CONTROLLER
	#define RPDB_LOG_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_LogSettingsController*		RPDB_LogSettingsController_new(									RPDB_SettingsController*			parent_settings_controller );

	void								RPDB_LogSettingsController_free(									RPDB_LogSettingsController**		log_settings_controller );
	RPDB_Environment*			RPDB_LogSettingsController_parentEnvironment(			RPDB_LogSettingsController*		log_settings_controller );

	int								RPDB_LogSettingsController_on(										RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnOn(									RPDB_LogSettingsController*		log_settings_controller );
	BOOL								RPDB_LogSettingsController_off(									RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnOff(								RPDB_LogSettingsController*		log_settings_controller );

	int								RPDB_LogSettingsController_disableSystemBuffering(								RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnDisableSystemBufferingOn(						RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnDisableSystemBufferingOff(						RPDB_LogSettingsController*		log_settings_controller );

	int								RPDB_LogSettingsController_flushBeforeReturnFromWrite(				RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnFlushBeforeReturnFromWriteOn(		RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnFlushBeforeReturnFromWriteOff(		RPDB_LogSettingsController*		log_settings_controller );

	int								RPDB_LogSettingsController_autoremoveLogs(							RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnAutoremoveLogsOn(					RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnAutoremoveOff(						RPDB_LogSettingsController*		log_settings_controller );

	int								RPDB_LogSettingsController_logInMemory(							RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnLogInMemoryOn(						RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnLogInMemoryOff(						RPDB_LogSettingsController*		log_settings_controller );

	int								RPDB_LogSettingsController_zeroAtCreation(							RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnZeroAtCreationOn(					RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnZeroAtCreationOff(					RPDB_LogSettingsController*		log_settings_controller );

	int									RPDB_LogSettingsController_forceFlushAfterRecordWrite(				RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnForceFlushAfterRecordWriteOn(		RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_turnForceFlushAfterRecordWriteOff(		RPDB_LogSettingsController*		log_settings_controller );

	uint32_t							RPDB_LogSettingsController_bufferSize(								RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_setBufferSize(							RPDB_LogSettingsController*		log_settings_controller, 
																											uint32_t							buffer_size );

	char*								RPDB_LogSettingsController_directory(								RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_setDirectory(							RPDB_LogSettingsController*		log_settings_controller, 
																											char*								directory );

	int									RPDB_LogSettingsController_mode(									RPDB_LogSettingsController*		log_settings_controller );
	void									RPDB_LogSettingsController_setMode(								RPDB_LogSettingsController*		log_settings_controller, 
																											int									mode );
																											
	int									RPDB_LogSettingsController_maxLogSize(								RPDB_LogSettingsController*		log_settings_controller );
	void									RPDB_LogSettingsController_setMaxLogSize(							RPDB_LogSettingsController*		log_settings_controller, 
																											uint32_t							max_size );

	int									RPDB_LogSettingsController_maxRegionSize(							RPDB_LogSettingsController*		log_settings_controller );
	void								RPDB_LogSettingsController_setMaxRegionSize(						RPDB_LogSettingsController*		log_settings_controller, 
																											uint32_t							max_region_size );

#endif

