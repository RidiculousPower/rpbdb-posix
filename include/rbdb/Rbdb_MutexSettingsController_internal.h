#ifndef RBDB_MUTEX_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_MUTEX_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

BOOL		Rbdb_MutexSettingsController_internal_openFlags(		Rbdb_MutexSettingsController*		mutex_settings_controller );

Rbdb_MutexSettingsController* Rbdb_MutexSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MutexSettingsController* mutex_settings_controller );
	
#endif

