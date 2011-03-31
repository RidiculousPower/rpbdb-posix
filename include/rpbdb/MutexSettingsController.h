/*
 *		RPbdb::SettingsController::MutexSettingsController
 *
 *
 */

#ifndef RPBDB_MUTEX_SETTINGS_CONTROLLER
	#define RPBDB_MUTEX_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPbdb_MutexSettingsController*	RPbdb_MutexSettingsController_new(							RPbdb_SettingsController*			settings_controller );
	void							RPbdb_MutexSettingsController_free(								RPbdb_MutexSettingsController** mutex_settings_controller );
	RPbdb_Environment*		RPbdb_MutexSettingsController_parentEnvironment(	RPbdb_MutexSettingsController* mutex_settings_controller );

	uint32_t	RPbdb_MutexSettingsController_spinTimesBeforeBlockingForTestAndSpinMutexes(		RPbdb_MutexSettingsController*		mutex_settings_controller );
	void		RPbdb_MutexSettingsController_setSpinTimesBeforeBlockingForTestAndSpinMutexes(	RPbdb_MutexSettingsController*		mutex_settings_controller, 
																								uint32_t							spin_times_before_blocking_for_test_and_spin_mutexes );

	uint32_t	RPbdb_MutexSettingsController_maxAllowableMutexes(								RPbdb_MutexSettingsController*		mutex_settings_controller );
	void		RPbdb_MutexSettingsController_setMaxAllowableMutexes(							RPbdb_MutexSettingsController*		mutex_settings_controller, 
																								uint32_t							max_allowable_mutexes );

	uint32_t	RPbdb_MutexSettingsController_incrementForAddingMutexes(						RPbdb_MutexSettingsController*		mutex_settings_controller );
	void		RPbdb_MutexSettingsController_setIncrementForAddingMutexes(						RPbdb_MutexSettingsController*		mutex_settings_controller, 
																								uint32_t							increment_for_adding_mutexes );

	uint32_t	RPbdb_MutexSettingsController_mutexAlignment(									RPbdb_MutexSettingsController*		mutex_settings_controller );
	void		RPbdb_MutexSettingsController_setMutexAlignment(								RPbdb_MutexSettingsController*		mutex_settings_controller, 
																								uint32_t							increment_for_adding_mutexes );

	BOOL		RPbdb_MutexSettingsController_associatedWithSingleProcess(						RPbdb_MutexSettingsController*		mutex_settings_controller );
	void		RPbdb_MutexSettingsController_turnAssociatedWithSingleProcessOn(				RPbdb_MutexSettingsController*		mutex_settings_controller );
	void		RPbdb_MutexSettingsController_turnAssociatedWithSingleProcessOff(				RPbdb_MutexSettingsController*		mutex_settings_controller );

	BOOL		RPbdb_MutexSettingsController_selfBlocking(										RPbdb_MutexSettingsController*		mutex_settings_controller );
	void		RPbdb_MutexSettingsController_turnSelfBlockingOn(								RPbdb_MutexSettingsController*		mutex_settings_controller );
	void		RPbdb_MutexSettingsController_turnSelfBlockingOff(								RPbdb_MutexSettingsController*		mutex_settings_controller );

#endif

