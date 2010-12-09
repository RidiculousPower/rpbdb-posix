/*
 *		Rbdb::SettingsController::MemoryPoolSettingsController::MemoryPoolFileSettingsController::MemoryPoolFileCachePrioritySettingsController
 *
 *
 */

#ifndef Rbdb_MEMORY_POOL_FILE_CACHE_PRIORITY_SETTINGS_CONTROLLER
	#define Rbdb_MEMORY_POOL_FILE_CACHE_PRIORITY_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
					
Rbdb_MemoryPoolFileCachePrioritySettingsController* Rbdb_MemoryPoolFileCachePrioritySettingsController_new( Rbdb_MemoryPoolFileCacheSettingsController*	memory_pool_file_cache_settings_controller );

	void													Rbdb_MemoryPoolFileCachePrioritySettingsController_free(	Rbdb_MemoryPoolFileCachePrioritySettingsController** memory_pool_file_cache_priority_settings_controller );
	Rbdb_Environment*								Rbdb_MemoryPoolFileCachePrioritySettingsController_parentEnvironment(	Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );

	DB_CACHE_PRIORITY			Rbdb_MemoryPoolFileCachePrioritySettingsController_currentPriority(			Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );

	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_veryLow(					Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		Rbdb_MemoryPoolFileCachePrioritySettingsController_setVeryLow(					Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastVeryLow(			Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostVeryLow(			Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
																								
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_low(						Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		Rbdb_MemoryPoolFileCachePrioritySettingsController_setLow(						Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastLow(				Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostLow(				Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
																								
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_default(					Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		Rbdb_MemoryPoolFileCachePrioritySettingsController_setDefault(					Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastDefault(			Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostDefault(			Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
																								
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_high(						Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		Rbdb_MemoryPoolFileCachePrioritySettingsController_setHigh(					Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastHigh(				Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostHigh(				Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
																								
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_veryHigh(					Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	void		Rbdb_MemoryPoolFileCachePrioritySettingsController_setVeryHigh(				Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtLeastVeryHigh(			Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );
	BOOL		Rbdb_MemoryPoolFileCachePrioritySettingsController_isAtMostVeryHigh(			Rbdb_MemoryPoolFileCachePrioritySettingsController* memory_pool_file_cache_priority_settings_controller );

#endif

