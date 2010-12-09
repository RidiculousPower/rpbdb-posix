/*
 *		Rbdb::LockController::Lock
 *
 *		Reference - http://www.oracle.com/technology/documentation/berkeley-db/db/ref/lock/am_conv.html
 */

#ifndef Rbdb_LOCK
	#define Rbdb_LOCK

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_Lock*			Rbdb_Lock_new(								Rbdb_LockController*			parent_lock_controller );

	void				Rbdb_Lock_free(	Rbdb_Lock** lock );
	Rbdb_LockSettingsController*	Rbdb_Lock_settingsController(	Rbdb_Lock* lock );
	Rbdb_Environment*		Rbdb_Lock_parentEnvironment(	Rbdb_Lock* lock );

	Rbdb_Lock*			Rbdb_Lock_lock(							Rbdb_Lock*						lock, 
																	Rbdb_Record*					record );
	void				Rbdb_Lock_unlock(							Rbdb_Lock*						lock );
	BOOL					Rbdb_Lock_isReadLock(						Rbdb_Lock*						lock );
	void				Rbdb_Lock_setToReadLock(					Rbdb_Lock*						lock );
	BOOL					Rbdb_Lock_isWriteLock(						Rbdb_Lock*						lock );
	void				Rbdb_Lock_setToWriteLock(					Rbdb_Lock*						lock );
	BOOL					Rbdb_Lock_isIntentToWriteLock(				Rbdb_Lock*						lock );
	void				Rbdb_Lock_setToIntentToWriteLock(			Rbdb_Lock*						lock );
	BOOL					Rbdb_Lock_isIntentToReadLock(				Rbdb_Lock*						lock );
	void				Rbdb_Lock_setToIntentToReadLock(			Rbdb_Lock*						lock );
	BOOL					Rbdb_Lock_isIntentToReadAndWriteLock(		Rbdb_Lock*						lock );
	void				Rbdb_Lock_setToIntentToReadAndWriteLock(	Rbdb_Lock*						lock );

#endif

