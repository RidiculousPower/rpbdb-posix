#ifndef RPBDB_MEMORY_POOL_FILE_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_MEMORY_POOL_FILE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPbdb_MemoryPoolFileSettingsController*		RPbdb_MemoryPoolFileSettingsController_internal_copyOfDefaultSettingsForInstance(	RPbdb_MemoryPoolFileSettingsController*				memory_pool_file_settings_controller );
int											RPbdb_MemoryPoolFileSettingsController_internal_createFlags(						RPbdb_MemoryPoolFileSettingsController*				memory_pool_file_settings_controller );
int											RPbdb_MemoryPoolFileSettingsController_internal_openFlags(							RPbdb_MemoryPoolFileSettingsController*				memory_pool_file_settings_controller );

RPbdb_MemoryPoolFileSettingsController* RPbdb_MemoryPoolFileSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );

#endif

