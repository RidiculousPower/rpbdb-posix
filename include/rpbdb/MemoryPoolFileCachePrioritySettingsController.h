/*
 *		RPbdb::SettingsController::MemoryPoolSettingsController::MemoryPoolFileSettingsController::MemoryPoolFileCachePrioritySettingsController
 *
 *
 */

#ifndef RPBDB_MEMORY_POOL_FILE_CACHE_PRIORITY_SETTINGS_CONTROLLER
	#define RPBDB_MEMORY_POOL_FILE_CACHE_PRIORITY_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
					
RPbdb_MemoryPoolFileCachePrioritySettingsController* RPbdb_MemoryPoolFileCachePrioritySettingsController_new( RPbdb_MemoryPoolFileCacheSettingsController*	memory_pool_file_cache_settings_controller );

	void													RPbdb_MemoryPoolFileCachePrioritySettingsController_free(	RPbdb_MemoryPoolFileCachePrioritySettingsController** memory_pool_file_cache_priority_settings_controller );
	RPbdb_Environment*								RPbdb_MemoryPoolFileCachePrioritySettingsController_parentEnvironment(	RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );

	DB_CACHE_PRIORITY			RPbdb_MemoryPoolFileCachePrioritySettingsController_currentPriority(			RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );

	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_veryLow(					RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		RPbdb_MemoryPoolFileCachePrioritySettingsController_setVeryLow(					RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastVeryLow(			RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostVeryLow(			RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
																								
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_low(						RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		RPbdb_MemoryPoolFileCachePrioritySettingsController_setLow(						RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastLow(				RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostLow(				RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
																								
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_default(					RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		RPbdb_MemoryPoolFileCachePrioritySettingsController_setDefault(					RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastDefault(			RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostDefault(			RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
																								
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_high(						RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		RPbdb_MemoryPoolFileCachePrioritySettingsController_setHigh(					RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastHigh(				RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostHigh(				RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
																								
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_veryHigh(					RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		RPbdb_MemoryPoolFileCachePrioritySettingsController_setVeryHigh(				RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastVeryHigh(			RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		RPbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostVeryHigh(			RPbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );

#endif

