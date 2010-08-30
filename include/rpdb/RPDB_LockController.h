/*
 *		RPDB::LockController
 *
 *
 */

#ifndef RPDB_LOCK_CONTROLLER
	#define RPDB_LOCK_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
	
	RPDB_LockController*			RPDB_LockController_new(											RPDB_Environment*				parent_environment );

	void							RPDB_LockController_free(	RPDB_LockController** lock_controller );
	RPDB_LockSettingsController*	RPDB_LockController_settingsController(	RPDB_LockController* lock_controller );
	RPDB_Environment*		RPDB_LockController_parentEnvironment(	RPDB_LockController* lock_controller );

	void							RPDB_LockController_free(											RPDB_LockController**			lock_controller );
	uint32_t						RPDB_LockController_lockerID(										RPDB_LockController*			lock_controller );
	RPDB_Lock*						RPDB_LockController_createLock(									RPDB_LockController*			lock_controller );
	void							RPDB_LockController_queueLock(										RPDB_LockController*							lock_controller,
									   																	RPDB_Lock*						lock_for_queue );
	void							RPDB_LockController_removeLockFromQueue(							RPDB_LockController*							lock_controller,
									   																	RPDB_Lock*						queued_lock );
	RPDB_Lock**					RPDB_LockController_obtainQueuedLocks(								RPDB_LockController*			lock_controller	);
	RPDB_Lock**					RPDB_LockController_releaseQueuedLocks(							RPDB_LockController*			lock_controller	);
	RPDB_Lock**					RPDB_LockController_obtainLocks(									RPDB_LockController*			lock_controller,
									   																	RPDB_Lock**					locks_to_obtain,
									   																	int								number_of_locks_to_obtain	);
	RPDB_Lock**					RPDB_LockController_obtainLocksAndOverrideTimeout(					RPDB_LockController*			lock_controller,
									   																	RPDB_Lock**					locks_to_obtain,
									   																	int								number_of_locks_to_obtain,
									   																	uint32_t						timeout	);
	RPDB_Lock**					RPDB_LockController_releaseLocks(									RPDB_LockController*			lock_controller,
									   																	RPDB_Lock**					locks_to_release,
									   																	int								number_of_locks_to_release	);
	void							RPDB_LockController_releaseAllLocks(								RPDB_LockController*			lock_controller	);
	void							RPDB_LockController_releaseAllLocksOnObject(						RPDB_LockController*			lock_controller,
									   																	RPDB_Record*					record	);
	int								RPDB_LockController_clearDefaultLocks(								RPDB_LockController*			lock_controller );
	int								RPDB_LockController_clearExpiredLocks(								RPDB_LockController*			lock_controller );
	int								RPDB_LockController_clearLockRequestForLockerWithMostLocks(		RPDB_LockController*			lock_controller );
	int								RPDB_LockController_clearLockRequestForLockerWithMostWriteLocks(	RPDB_LockController*			lock_controller );
	int								RPDB_LockController_clearLockRequestForLockerWithLeastLocks(		RPDB_LockController*			lock_controller );
	int								RPDB_LockController_clearLockRequestForLockerWithLeastWriteLocks(	RPDB_LockController*			lock_controller );
	int								RPDB_LockController_clearLockRequestForLockerWithOldestLock(		RPDB_LockController*			lock_controller );
	int								RPDB_LockController_clearLockRequestForLockerWithYoungestLock(		RPDB_LockController*			lock_controller );
	int								RPDB_LockController_clearLockRequestForRandomLocker(				RPDB_LockController*			lock_controller );
	void							RPDB_LockController_closeAllLocks(									RPDB_LockController*			lock_controller );
	RPDB_LockSettingsController*	RPDB_LockController_settingsController(							RPDB_LockController*			lock_controller );

#endif

