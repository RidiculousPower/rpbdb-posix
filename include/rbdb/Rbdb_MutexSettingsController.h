/*
 *		Rbdb::SettingsController::MutexSettingsController
 *
 *
 */

#ifndef Rbdb_MUTEX_SETTINGS_CONTROLLER
	#define Rbdb_MUTEX_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	Rbdb_MutexSettingsController*	Rbdb_MutexSettingsController_new(							Rbdb_SettingsController*			settings_controller );
	void							Rbdb_MutexSettingsController_free(								Rbdb_MutexSettingsController** mutex_settings_controller );
	Rbdb_Environment*		Rbdb_MutexSettingsController_parentEnvironment(	Rbdb_MutexSettingsController* mutex_settings_controller );

	uint32_t	Rbdb_MutexSettingsController_spinTimesBeforeBlockingForTestAndSpinMutexes(		Rbdb_MutexSettingsController*		mutex_settings_controller );
	void		Rbdb_MutexSettingsController_setSpinTimesBeforeBlockingForTestAndSpinMutexes(	Rbdb_MutexSettingsController*		mutex_settings_controller, 
																								uint32_t							spin_times_before_blocking_for_test_and_spin_mutexes );

	uint32_t	Rbdb_MutexSettingsController_maxAllowableMutexes(								Rbdb_MutexSettingsController*		mutex_settings_controller );
	void		Rbdb_MutexSettingsController_setMaxAllowableMutexes(							Rbdb_MutexSettingsController*		mutex_settings_controller, 
																								uint32_t							max_allowable_mutexes );

	uint32_t	Rbdb_MutexSettingsController_incrementForAddingMutexes(						Rbdb_MutexSettingsController*		mutex_settings_controller );
	void		Rbdb_MutexSettingsController_setIncrementForAddingMutexes(						Rbdb_MutexSettingsController*		mutex_settings_controller, 
																								uint32_t							increment_for_adding_mutexes );

	uint32_t	Rbdb_MutexSettingsController_mutexAlignment(									Rbdb_MutexSettingsController*		mutex_settings_controller );
	void		Rbdb_MutexSettingsController_setMutexAlignment(								Rbdb_MutexSettingsController*		mutex_settings_controller, 
																								uint32_t							increment_for_adding_mutexes );

	BOOL		Rbdb_MutexSettingsController_associatedWithSingleProcess(						Rbdb_MutexSettingsController*		mutex_settings_controller );
	void		Rbdb_MutexSettingsController_turnAssociatedWithSingleProcessOn(				Rbdb_MutexSettingsController*		mutex_settings_controller );
	void		Rbdb_MutexSettingsController_turnAssociatedWithSingleProcessOff(				Rbdb_MutexSettingsController*		mutex_settings_controller );

	BOOL		Rbdb_MutexSettingsController_selfBlocking(										Rbdb_MutexSettingsController*		mutex_settings_controller );
	void		Rbdb_MutexSettingsController_turnSelfBlockingOn(								Rbdb_MutexSettingsController*		mutex_settings_controller );
	void		Rbdb_MutexSettingsController_turnSelfBlockingOff(								Rbdb_MutexSettingsController*		mutex_settings_controller );

#endif

