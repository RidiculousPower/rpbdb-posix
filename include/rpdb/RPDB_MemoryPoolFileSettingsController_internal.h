#ifndef RPDB_MEMORY_POOL_FILE_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_MEMORY_POOL_FILE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPDB_MemoryPoolFileSettingsController*		RPDB_MemoryPoolFileSettingsController_internal_copyOfDefaultSettingsForInstance(	RPDB_MemoryPoolFileSettingsController*				memory_pool_file_settings_controller );
int											RPDB_MemoryPoolFileSettingsController_internal_createFlags(						RPDB_MemoryPoolFileSettingsController*				memory_pool_file_settings_controller );
int											RPDB_MemoryPoolFileSettingsController_internal_openFlags(							RPDB_MemoryPoolFileSettingsController*				memory_pool_file_settings_controller );

RPDB_MemoryPoolFileSettingsController* RPDB_MemoryPoolFileSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MemoryPoolFileSettingsController* memory_pool_file_settings_controller );

#endif

