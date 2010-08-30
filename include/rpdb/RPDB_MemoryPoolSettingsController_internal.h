#ifndef RPDB_MEMORY_POOL_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_MEMORY_POOL_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void		RPDB_MemoryPoolSettingsController_internal_initDefaultSettings(	RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller );
int			RPDB_MemoryPoolSettingsController_internal_closeFlags(				RPDB_MemoryPoolFile*					memory_pool_file );

RPDB_MemoryPoolSettingsController* RPDB_MemoryPoolSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MemoryPoolSettingsController* memory_pool_settings_controller );

#endif

