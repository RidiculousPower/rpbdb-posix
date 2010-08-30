#ifndef RPDB_MUTEX_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_MUTEX_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

BOOL		RPDB_MutexSettingsController_internal_openFlags(		RPDB_MutexSettingsController*		mutex_settings_controller );

RPDB_MutexSettingsController* RPDB_MutexSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MutexSettingsController* mutex_settings_controller );
	
#endif

