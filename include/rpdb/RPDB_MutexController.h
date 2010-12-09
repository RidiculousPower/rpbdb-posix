/*
 *		Rbdb::MutexController
 *
 *	
 */

#ifndef Rbdb_MUTEX_CONTROLLER
	#define Rbdb_MUTEX_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_MutexController*				Rbdb_MutexController_new(						Rbdb_Environment*							parent_environment );

	void								Rbdb_MutexController_free(	Rbdb_MutexController** mutex_controller );
	Rbdb_MutexSettingsController*		Rbdb_MutexController_settingsController(	Rbdb_MutexController* mutex_controller );
	Rbdb_Environment*			Rbdb_MutexController_parentEnvironment(	Rbdb_MutexController* mutex_controller );

	Rbdb_Mutex*						Rbdb_MutexController_mutexForName(			Rbdb_MutexController*			mutex_controller,
	 									   												char*							mutex_name );
	Rbdb_Mutex*						Rbdb_MutexController_closeMutexForName(		Rbdb_MutexController*			mutex_controller,
	 									   												char*							mutex_name );
	void								Rbdb_MutexController_freeMutexForName(		Rbdb_MutexController*			mutex_controller,
	 									   												char*							mutex_name );
	Rbdb_Mutex**						Rbdb_MutexController_allMutexes(				Rbdb_MutexController*			mutex_controller );
	void									Rbdb_MutexController_closeAllMutexes(			Rbdb_MutexController*			mutex_controller );
	void									Rbdb_MutexController_freeAllMutexes(			Rbdb_MutexController*			mutex_controller );
	Rbdb_MutexSettingsController*		Rbdb_MutexController_settingsController(		Rbdb_MutexController*			mutex_controller );

#endif

