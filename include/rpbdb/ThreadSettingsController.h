/*
 *		RPbdb::SettingsController::ThreadSettingsController
 *
 *
 */

#ifndef RPBDB_THREAD_SETTINGS_CONTROLLER
	#define RPBDB_THREAD_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_ThreadSettingsController*		RPbdb_ThreadSettingsController_new(								RPbdb_SettingsController*			settings_controller );
	void								RPbdb_ThreadSettingsController_free(							RPbdb_ThreadSettingsController**		thread_settings_controller );
	RPbdb_Environment*			RPbdb_ThreadSettingsController_parentEnvironment(	RPbdb_ThreadSettingsController*		thread_settings_controller );
	int								RPbdb_ThreadSettingsController_on(								RPbdb_ThreadSettingsController*		thread_settings_controller );
	BOOL								RPbdb_ThreadSettingsController_off(								RPbdb_ThreadSettingsController*		thread_settings_controller );
	void								RPbdb_ThreadSettingsController_turnOn(							RPbdb_ThreadSettingsController*		thread_settings_controller );
	void								RPbdb_ThreadSettingsController_turnOff(							RPbdb_ThreadSettingsController*		thread_settings_controller );
																																			
	int									RPbdb_ThreadSettingsController_threadCount(						RPbdb_ThreadSettingsController*		thread_settings_controller );
	void								RPbdb_ThreadSettingsController_setThreadCount(					RPbdb_ThreadSettingsController*		thread_settings_controller, 
																										uint32_t							thread_count );

void RPbdb_ThreadSettingsController_setUniqueThreadIdentifierCallbackMethod(	RPbdb_ThreadSettingsController*					thread_settings_controller,
																			RPbdb_UniqueThreadIdentifierCallbackMethod		unique_thread_identifier_callback_method );
RPbdb_UniqueThreadIdentifierCallbackMethod RPbdb_ThreadSettingsController_uniqueThreadIdentifierCallbackMethod( RPbdb_ThreadSettingsController* thread_settings_controller );
void RPbdb_ThreadSettingsController_setFormatThreadAndProcessIdentifierForDisplayCallbackMethod(	RPbdb_ThreadSettingsController*										thread_settings_controller,
																								RPbdb_FormatThreadAndProcessIdentifierForDisplayCallbackMethod		format_thread_and_process_identifier_for_display_callback_method );
RPbdb_FormatThreadAndProcessIdentifierForDisplayCallbackMethod RPbdb_ThreadSettingsController_formatThreadAndProcessIDForDisplayCallbackMethod(	RPbdb_ThreadSettingsController* thread_settings_controller	);
void RPbdb_ThreadSettingsController_setIsThreadAliveCallback(	RPbdb_ThreadSettingsController* 	thread_settings_controller,
															 RPbdb_IsThreadAliveCallbackMethod		is_thread_alive_callback_method );
RPbdb_IsThreadAliveCallbackMethod RPbdb_ThreadSettingsController_isThreadAliveCallbackMethod( RPbdb_ThreadSettingsController* thread_settings_controller );
	
#endif

