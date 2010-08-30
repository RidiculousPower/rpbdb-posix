/*
 *		RPDB::SettingsController::MutexSettingsController
 *
 *
 */

#ifndef RPDB_MUTEX_SETTINGS_CONTROLLER
	#define RPDB_MUTEX_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPDB_MutexSettingsController*	RPDB_MutexSettingsController_new(							RPDB_SettingsController*			settings_controller );
	void							RPDB_MutexSettingsController_free(								RPDB_MutexSettingsController** mutex_settings_controller );
	RPDB_Environment*		RPDB_MutexSettingsController_parentEnvironment(	RPDB_MutexSettingsController* mutex_settings_controller );

	uint32_t	RPDB_MutexSettingsController_spinTimesBeforeBlockingForTestAndSpinMutexes(		RPDB_MutexSettingsController*		mutex_settings_controller );
	void		RPDB_MutexSettingsController_setSpinTimesBeforeBlockingForTestAndSpinMutexes(	RPDB_MutexSettingsController*		mutex_settings_controller, 
																								uint32_t							spin_times_before_blocking_for_test_and_spin_mutexes );

	uint32_t	RPDB_MutexSettingsController_maxAllowableMutexes(								RPDB_MutexSettingsController*		mutex_settings_controller );
	void		RPDB_MutexSettingsController_setMaxAllowableMutexes(							RPDB_MutexSettingsController*		mutex_settings_controller, 
																								uint32_t							max_allowable_mutexes );

	uint32_t	RPDB_MutexSettingsController_incrementForAddingMutexes(						RPDB_MutexSettingsController*		mutex_settings_controller );
	void		RPDB_MutexSettingsController_setIncrementForAddingMutexes(						RPDB_MutexSettingsController*		mutex_settings_controller, 
																								uint32_t							increment_for_adding_mutexes );

	uint32_t	RPDB_MutexSettingsController_mutexAlignment(									RPDB_MutexSettingsController*		mutex_settings_controller );
	void		RPDB_MutexSettingsController_setMutexAlignment(								RPDB_MutexSettingsController*		mutex_settings_controller, 
																								uint32_t							increment_for_adding_mutexes );

	BOOL		RPDB_MutexSettingsController_associatedWithSingleProcess(						RPDB_MutexSettingsController*		mutex_settings_controller );
	void		RPDB_MutexSettingsController_turnAssociatedWithSingleProcessOn(				RPDB_MutexSettingsController*		mutex_settings_controller );
	void		RPDB_MutexSettingsController_turnAssociatedWithSingleProcessOff(				RPDB_MutexSettingsController*		mutex_settings_controller );

	BOOL		RPDB_MutexSettingsController_selfBlocking(										RPDB_MutexSettingsController*		mutex_settings_controller );
	void		RPDB_MutexSettingsController_turnSelfBlockingOn(								RPDB_MutexSettingsController*		mutex_settings_controller );
	void		RPDB_MutexSettingsController_turnSelfBlockingOff(								RPDB_MutexSettingsController*		mutex_settings_controller );

#endif

