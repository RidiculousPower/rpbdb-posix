#ifndef RPBDB_MUTEX_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_MUTEX_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

BOOL		RPbdb_MutexSettingsController_internal_openFlags(		RPbdb_MutexSettingsController*		mutex_settings_controller );

RPbdb_MutexSettingsController* RPbdb_MutexSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MutexSettingsController* mutex_settings_controller );
	
#endif

