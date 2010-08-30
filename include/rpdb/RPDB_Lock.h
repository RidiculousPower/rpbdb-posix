/*
 *		RPDB::LockController::Lock
 *
 *		Reference - http://www.oracle.com/technology/documentation/berkeley-db/db/ref/lock/am_conv.html
 */

#ifndef RPDB_LOCK
	#define RPDB_LOCK

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_Lock*			RPDB_Lock_new(								RPDB_LockController*			parent_lock_controller );

	void				RPDB_Lock_free(	RPDB_Lock** lock );
	RPDB_LockSettingsController*	RPDB_Lock_settingsController(	RPDB_Lock* lock );
	RPDB_Environment*		RPDB_Lock_parentEnvironment(	RPDB_Lock* lock );

	RPDB_Lock*			RPDB_Lock_lock(							RPDB_Lock*						lock, 
																	RPDB_Record*					record );
	void				RPDB_Lock_unlock(							RPDB_Lock*						lock );
	BOOL					RPDB_Lock_isReadLock(						RPDB_Lock*						lock );
	void				RPDB_Lock_setToReadLock(					RPDB_Lock*						lock );
	BOOL					RPDB_Lock_isWriteLock(						RPDB_Lock*						lock );
	void				RPDB_Lock_setToWriteLock(					RPDB_Lock*						lock );
	BOOL					RPDB_Lock_isIntentToWriteLock(				RPDB_Lock*						lock );
	void				RPDB_Lock_setToIntentToWriteLock(			RPDB_Lock*						lock );
	BOOL					RPDB_Lock_isIntentToReadLock(				RPDB_Lock*						lock );
	void				RPDB_Lock_setToIntentToReadLock(			RPDB_Lock*						lock );
	BOOL					RPDB_Lock_isIntentToReadAndWriteLock(		RPDB_Lock*						lock );
	void				RPDB_Lock_setToIntentToReadAndWriteLock(	RPDB_Lock*						lock );

#endif

