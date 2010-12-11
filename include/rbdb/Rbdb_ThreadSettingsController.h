/*
 *		Rbdb::SettingsController::ThreadSettingsController
 *
 *
 */

#ifndef RBDB_THREAD_SETTINGS_CONTROLLER
	#define RBDB_THREAD_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_ThreadSettingsController*		Rbdb_ThreadSettingsController_new(								Rbdb_SettingsController*			settings_controller );
	void								Rbdb_ThreadSettingsController_free(							Rbdb_ThreadSettingsController**		thread_settings_controller );
	Rbdb_Environment*			Rbdb_ThreadSettingsController_parentEnvironment(	Rbdb_ThreadSettingsController*		thread_settings_controller );
	int								Rbdb_ThreadSettingsController_on(								Rbdb_ThreadSettingsController*		thread_settings_controller );
	BOOL								Rbdb_ThreadSettingsController_off(								Rbdb_ThreadSettingsController*		thread_settings_controller );
	void								Rbdb_ThreadSettingsController_turnOn(							Rbdb_ThreadSettingsController*		thread_settings_controller );
	void								Rbdb_ThreadSettingsController_turnOff(							Rbdb_ThreadSettingsController*		thread_settings_controller );
																																			
	int									Rbdb_ThreadSettingsController_threadCount(						Rbdb_ThreadSettingsController*		thread_settings_controller );
	void								Rbdb_ThreadSettingsController_setThreadCount(					Rbdb_ThreadSettingsController*		thread_settings_controller, 
																										uint32_t							thread_count );

void Rbdb_ThreadSettingsController_setUniqueThreadIdentifierCallbackMethod(	Rbdb_ThreadSettingsController*					thread_settings_controller,
																			Rbdb_UniqueThreadIdentifierCallbackMethod		unique_thread_identifier_callback_method );
Rbdb_UniqueThreadIdentifierCallbackMethod Rbdb_ThreadSettingsController_uniqueThreadIdentifierCallbackMethod( Rbdb_ThreadSettingsController* thread_settings_controller );
void Rbdb_ThreadSettingsController_setFormatThreadAndProcessIdentifierForDisplayCallbackMethod(	Rbdb_ThreadSettingsController*										thread_settings_controller,
																								Rbdb_FormatThreadAndProcessIdentifierForDisplayCallbackMethod		format_thread_and_process_identifier_for_display_callback_method );
Rbdb_FormatThreadAndProcessIdentifierForDisplayCallbackMethod Rbdb_ThreadSettingsController_formatThreadAndProcessIDForDisplayCallbackMethod(	Rbdb_ThreadSettingsController* thread_settings_controller	);
void Rbdb_ThreadSettingsController_setIsThreadAliveCallback(	Rbdb_ThreadSettingsController* 	thread_settings_controller,
															 Rbdb_IsThreadAliveCallbackMethod		is_thread_alive_callback_method );
Rbdb_IsThreadAliveCallbackMethod Rbdb_ThreadSettingsController_isThreadAliveCallbackMethod( Rbdb_ThreadSettingsController* thread_settings_controller );
	
#endif

