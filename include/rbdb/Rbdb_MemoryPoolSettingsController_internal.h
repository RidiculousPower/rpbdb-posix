#ifndef Rbdb_MEMORY_POOL_SETTINGS_CONTROLLER_INTERNAL
	#define Rbdb_MEMORY_POOL_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void		Rbdb_MemoryPoolSettingsController_internal_initDefaultSettings(	Rbdb_MemoryPoolSettingsController*		memory_pool_settings_controller );
int			Rbdb_MemoryPoolSettingsController_internal_closeFlags(				Rbdb_MemoryPoolFile*					memory_pool_file );

Rbdb_MemoryPoolSettingsController* Rbdb_MemoryPoolSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MemoryPoolSettingsController* memory_pool_settings_controller );

#endif

