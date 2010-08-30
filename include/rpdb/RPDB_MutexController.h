/*
 *		RPDB::MutexController
 *
 *	
 */

#ifndef RPDB_MUTEX_CONTROLLER
	#define RPDB_MUTEX_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_MutexController*				RPDB_MutexController_new(						RPDB_Environment*							parent_environment );

	void								RPDB_MutexController_free(	RPDB_MutexController** mutex_controller );
	RPDB_MutexSettingsController*		RPDB_MutexController_settingsController(	RPDB_MutexController* mutex_controller );
	RPDB_Environment*			RPDB_MutexController_parentEnvironment(	RPDB_MutexController* mutex_controller );

	RPDB_Mutex*						RPDB_MutexController_mutexForName(			RPDB_MutexController*			mutex_controller,
	 									   												char*							mutex_name );
	RPDB_Mutex*						RPDB_MutexController_closeMutexForName(		RPDB_MutexController*			mutex_controller,
	 									   												char*							mutex_name );
	void								RPDB_MutexController_freeMutexForName(		RPDB_MutexController*			mutex_controller,
	 									   												char*							mutex_name );
	RPDB_Mutex**						RPDB_MutexController_allMutexes(				RPDB_MutexController*			mutex_controller );
	void									RPDB_MutexController_closeAllMutexes(			RPDB_MutexController*			mutex_controller );
	void									RPDB_MutexController_freeAllMutexes(			RPDB_MutexController*			mutex_controller );
	RPDB_MutexSettingsController*		RPDB_MutexController_settingsController(		RPDB_MutexController*			mutex_controller );

#endif

