/*
 *		RPbdb::MutexController
 *
 *	
 */

#ifndef RPBDB_MUTEX_CONTROLLER
	#define RPBDB_MUTEX_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_MutexController*				RPbdb_MutexController_new(						RPbdb_Environment*							parent_environment );

	void								RPbdb_MutexController_free(	RPbdb_MutexController** mutex_controller );
	RPbdb_MutexSettingsController*		RPbdb_MutexController_settingsController(	RPbdb_MutexController* mutex_controller );
	RPbdb_Environment*			RPbdb_MutexController_parentEnvironment(	RPbdb_MutexController* mutex_controller );

	RPbdb_Mutex*						RPbdb_MutexController_mutexForName(			RPbdb_MutexController*			mutex_controller,
	 									   												char*							mutex_name );
	RPbdb_Mutex*						RPbdb_MutexController_closeMutexForName(		RPbdb_MutexController*			mutex_controller,
	 									   												char*							mutex_name );
	void								RPbdb_MutexController_freeMutexForName(		RPbdb_MutexController*			mutex_controller,
	 									   												char*							mutex_name );
	RPbdb_Mutex**						RPbdb_MutexController_allMutexes(				RPbdb_MutexController*			mutex_controller );
	void									RPbdb_MutexController_closeAllMutexes(			RPbdb_MutexController*			mutex_controller );
	void									RPbdb_MutexController_freeAllMutexes(			RPbdb_MutexController*			mutex_controller );
	RPbdb_MutexSettingsController*		RPbdb_MutexController_settingsController(		RPbdb_MutexController*			mutex_controller );

#endif

