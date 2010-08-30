/*
 *		RPDB::SettingsController::MemoryPoolSettingsController::MemoryPoolFileSettingsController::MemoryPoolFileCachePrioritySettingsController
 *
 *
 */

#ifndef RPDB_MEMORY_POOL_FILE_CACHE_PRIORITY_SETTINGS_CONTROLLER
	#define RPDB_MEMORY_POOL_FILE_CACHE_PRIORITY_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
					
	RPDB_MemoryPoolFileCachePrioritySettingsController*	RPDB_MemoryPoolFileCachePrioritySettingsController_new(	RPDB_MemoryPoolFileSettingsController*	memory_pool_file_settings_controller );

	void													RPDB_MemoryPoolFileCachePrioritySettingsController_free(	RPDB_MemoryPoolFileCachePrioritySettingsController** memory_pool_file_cache_priority_settings_controller );
	RPDB_Environment*								RPDB_MemoryPoolFileCachePrioritySettingsController_parentEnvironment(	RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );

	DB_CACHE_PRIORITY			RPDB_MemoryPoolFileCachePrioritySettingsController_currentPriority(			RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );

	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_veryLow(					RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		RPDB_MemoryPoolFileCachePrioritySettingsController_setVeryLow(					RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_isAtLeastVeryLow(			RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_isAtMostVeryLow(			RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
																								
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_low(						RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		RPDB_MemoryPoolFileCachePrioritySettingsController_setLow(						RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_isAtLeastLow(				RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_isAtMostLow(				RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
																								
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_default(					RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		RPDB_MemoryPoolFileCachePrioritySettingsController_setDefault(					RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_isAtLeastDefault(			RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_isAtMostDefault(			RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
																								
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_high(						RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		RPDB_MemoryPoolFileCachePrioritySettingsController_setHigh(					RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_isAtLeastHigh(				RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_isAtMostHigh(				RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
																								
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_veryHigh(					RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		RPDB_MemoryPoolFileCachePrioritySettingsController_setVeryHigh(				RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_isAtLeastVeryHigh(			RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPDB_MemoryPoolFileCachePrioritySettingsController_isAtMostVeryHigh(			RPDB_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );

#endif

