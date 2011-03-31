#ifndef RPBDB_MEMORY_POOL_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_MEMORY_POOL_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void		RPbdb_MemoryPoolSettingsController_internal_initDefaultSettings(	RPbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
int			RPbdb_MemoryPoolSettingsController_internal_closeFlags(				RPbdb_MemoryPoolFile*					memory_pool_file );

RPbdb_MemoryPoolSettingsController* RPbdb_MemoryPoolSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MemoryPoolSettingsController* memory_pool_settings_controller );

#endif

