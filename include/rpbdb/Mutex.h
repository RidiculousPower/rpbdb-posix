/*
 *		RPbdb::MutexController::Mutex
 *
 *	
 */

#ifndef RPBDB_MUTEX
	#define RPBDB_MUTEX

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_Mutex*					RPbdb_Mutex_new(					RPbdb_MutexController*				parent_mutex_controller );

	void							RPbdb_Mutex_free(	RPbdb_Mutex** mutex );
	RPbdb_MutexSettingsController*	RPbdb_Mutex_settingsController(	RPbdb_Mutex* mutex );
	RPbdb_Environment*		RPbdb_Mutex_parentEnvironment(	RPbdb_Mutex* mutex );

	void								RPbdb_Mutex_free(					RPbdb_Mutex**						mutex );
	RPbdb_Mutex*					RPbdb_Mutex_open(					RPbdb_Mutex*						mutex );
	void							RPbdb_Mutex_close(					RPbdb_Mutex*						mutex );
	RPbdb_Mutex*					RPbdb_Mutex_lock(					RPbdb_Mutex*						mutex );
	RPbdb_Mutex*					RPbdb_Mutex_unlock(					RPbdb_Mutex*						mutex );
	RPbdb_MutexSettingsController*	RPbdb_Mutex_settingsController(		RPbdb_Mutex*						mutex );


#endif

