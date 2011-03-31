/*
 *		RPbdb::LockController::Lock
 *
 *		Reference - http://www.oracle.com/technology/documentation/berkeley-db/db/ref/lock/am_conv.html
 */

#ifndef RPBDB_LOCK
	#define RPBDB_LOCK

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_Lock*			RPbdb_Lock_new(								RPbdb_LockController*			parent_lock_controller );

	void				RPbdb_Lock_free(	RPbdb_Lock** lock );
	RPbdb_LockSettingsController*	RPbdb_Lock_settingsController(	RPbdb_Lock* lock );
	RPbdb_Environment*		RPbdb_Lock_parentEnvironment(	RPbdb_Lock* lock );

	RPbdb_Lock*			RPbdb_Lock_lock(							RPbdb_Lock*						lock, 
																	RPbdb_Record*					record );
	void				RPbdb_Lock_unlock(							RPbdb_Lock*						lock );
	BOOL					RPbdb_Lock_isReadLock(						RPbdb_Lock*						lock );
	void				RPbdb_Lock_setToReadLock(					RPbdb_Lock*						lock );
	BOOL					RPbdb_Lock_isWriteLock(						RPbdb_Lock*						lock );
	void				RPbdb_Lock_setToWriteLock(					RPbdb_Lock*						lock );
	BOOL					RPbdb_Lock_isIntentToWriteLock(				RPbdb_Lock*						lock );
	void				RPbdb_Lock_setToIntentToWriteLock(			RPbdb_Lock*						lock );
	BOOL					RPbdb_Lock_isIntentToReadLock(				RPbdb_Lock*						lock );
	void				RPbdb_Lock_setToIntentToReadLock(			RPbdb_Lock*						lock );
	BOOL					RPbdb_Lock_isIntentToReadAndWriteLock(		RPbdb_Lock*						lock );
	void				RPbdb_Lock_setToIntentToReadAndWriteLock(	RPbdb_Lock*						lock );

#endif

