/*
 *		RPDB::MutexController::Mutex
 *
 *	
 */

#ifndef RPDB_MUTEX
	#define RPDB_MUTEX

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_Mutex*					RPDB_Mutex_new(					RPDB_MutexController*				parent_mutex_controller );

	void							RPDB_Mutex_free(	RPDB_Mutex** mutex );
	RPDB_MutexSettingsController*	RPDB_Mutex_settingsController(	RPDB_Mutex* mutex );
	RPDB_Environment*		RPDB_Mutex_parentEnvironment(	RPDB_Mutex* mutex );

	void								RPDB_Mutex_free(					RPDB_Mutex**						mutex );
	RPDB_Mutex*					RPDB_Mutex_open(					RPDB_Mutex*						mutex );
	void							RPDB_Mutex_close(					RPDB_Mutex*						mutex );
	RPDB_Mutex*					RPDB_Mutex_lock(					RPDB_Mutex*						mutex );
	RPDB_Mutex*					RPDB_Mutex_unlock(					RPDB_Mutex*						mutex );
	RPDB_MutexSettingsController*	RPDB_Mutex_settingsController(		RPDB_Mutex*						mutex );


#endif

