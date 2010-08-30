/*
 *		RPDB::SettingsController::ThreadSettingsController
 *
 *
 */

#ifndef RPDB_THREAD_SETTINGS_CONTROLLER
	#define RPDB_THREAD_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_ThreadSettingsController*		RPDB_ThreadSettingsController_new(								RPDB_SettingsController*			settings_controller );
	void								RPDB_ThreadSettingsController_free(							RPDB_ThreadSettingsController**		thread_settings_controller );
	RPDB_Environment*			RPDB_ThreadSettingsController_parentEnvironment(	RPDB_ThreadSettingsController*		thread_settings_controller );
	int								RPDB_ThreadSettingsController_on(								RPDB_ThreadSettingsController*		thread_settings_controller );
	BOOL								RPDB_ThreadSettingsController_off(								RPDB_ThreadSettingsController*		thread_settings_controller );
	void								RPDB_ThreadSettingsController_turnOn(							RPDB_ThreadSettingsController*		thread_settings_controller );
	void								RPDB_ThreadSettingsController_turnOff(							RPDB_ThreadSettingsController*		thread_settings_controller );
																																			
	int									RPDB_ThreadSettingsController_threadCount(						RPDB_ThreadSettingsController*		thread_settings_controller );
	void								RPDB_ThreadSettingsController_setThreadCount(					RPDB_ThreadSettingsController*		thread_settings_controller, 
																										uint32_t							thread_count );

void RPDB_ThreadSettingsController_setUniqueThreadIdentifierCallbackMethod(	RPDB_ThreadSettingsController*					thread_settings_controller,
																			RPDB_UniqueThreadIdentifierCallbackMethod		unique_thread_identifier_callback_method );
RPDB_UniqueThreadIdentifierCallbackMethod RPDB_ThreadSettingsController_uniqueThreadIdentifierCallbackMethod( RPDB_ThreadSettingsController* thread_settings_controller );
void RPDB_ThreadSettingsController_setFormatThreadAndProcessIdentifierForDisplayCallbackMethod(	RPDB_ThreadSettingsController*										thread_settings_controller,
																								RPDB_FormatThreadAndProcessIdentifierForDisplayCallbackMethod		format_thread_and_process_identifier_for_display_callback_method );
RPDB_FormatThreadAndProcessIdentifierForDisplayCallbackMethod RPDB_ThreadSettingsController_formatThreadAndProcessIDForDisplayCallbackMethod(	RPDB_ThreadSettingsController* thread_settings_controller	);
void RPDB_ThreadSettingsController_setIsThreadAliveCallback(	RPDB_ThreadSettingsController* 	thread_settings_controller,
															 RPDB_IsThreadAliveCallbackMethod		is_thread_alive_callback_method );
RPDB_IsThreadAliveCallbackMethod RPDB_ThreadSettingsController_isThreadAliveCallbackMethod( RPDB_ThreadSettingsController* thread_settings_controller );
	
#endif

