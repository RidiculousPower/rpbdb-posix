/*
 *		Rbdb::MutexController::Mutex
 *
 *	
 */

#ifndef Rbdb_MUTEX
	#define Rbdb_MUTEX

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_Mutex*					Rbdb_Mutex_new(					Rbdb_MutexController*				parent_mutex_controller );

	void							Rbdb_Mutex_free(	Rbdb_Mutex** mutex );
	Rbdb_MutexSettingsController*	Rbdb_Mutex_settingsController(	Rbdb_Mutex* mutex );
	Rbdb_Environment*		Rbdb_Mutex_parentEnvironment(	Rbdb_Mutex* mutex );

	void								Rbdb_Mutex_free(					Rbdb_Mutex**						mutex );
	Rbdb_Mutex*					Rbdb_Mutex_open(					Rbdb_Mutex*						mutex );
	void							Rbdb_Mutex_close(					Rbdb_Mutex*						mutex );
	Rbdb_Mutex*					Rbdb_Mutex_lock(					Rbdb_Mutex*						mutex );
	Rbdb_Mutex*					Rbdb_Mutex_unlock(					Rbdb_Mutex*						mutex );
	Rbdb_MutexSettingsController*	Rbdb_Mutex_settingsController(		Rbdb_Mutex*						mutex );


#endif

