#ifndef Rbdb_MEMORY_POOL_FILE_SETTINGS_CONTROLLER_INTERNAL
	#define Rbdb_MEMORY_POOL_FILE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

Rbdb_MemoryPoolFileSettingsController*		Rbdb_MemoryPoolFileSettingsController_internal_copyOfDefaultSettingsForInstance(	Rbdb_MemoryPoolFileSettingsController*				memory_pool_file_settings_controller );
int											Rbdb_MemoryPoolFileSettingsController_internal_createFlags(						Rbdb_MemoryPoolFileSettingsController*				memory_pool_file_settings_controller );
int											Rbdb_MemoryPoolFileSettingsController_internal_openFlags(							Rbdb_MemoryPoolFileSettingsController*				memory_pool_file_settings_controller );

Rbdb_MemoryPoolFileSettingsController* Rbdb_MemoryPoolFileSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );

#endif

