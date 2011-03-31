/*
 *		RPbdb::LockController
 *
 *
 */

#ifndef RPBDB_LOCK_CONTROLLER
	#define RPBDB_LOCK_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
	
	RPbdb_LockController*			RPbdb_LockController_new(											RPbdb_Environment*				parent_environment );

	void							RPbdb_LockController_free(	RPbdb_LockController** lock_controller );
	RPbdb_LockSettingsController*	RPbdb_LockController_settingsController(	RPbdb_LockController* lock_controller );
	RPbdb_Environment*		RPbdb_LockController_parentEnvironment(	RPbdb_LockController* lock_controller );

	void							RPbdb_LockController_free(											RPbdb_LockController**			lock_controller );
	uint32_t						RPbdb_LockController_lockerID(										RPbdb_LockController*			lock_controller );
	RPbdb_Lock*						RPbdb_LockController_createLock(									RPbdb_LockController*			lock_controller );
	void							RPbdb_LockController_queueLock(										RPbdb_LockController*							lock_controller,
									   																	RPbdb_Lock*						lock_for_queue );
	void							RPbdb_LockController_removeLockFromQueue(							RPbdb_LockController*							lock_controller,
									   																	RPbdb_Lock*						queued_lock );
	RPbdb_Lock**					RPbdb_LockController_obtainQueuedLocks(								RPbdb_LockController*			lock_controller	);
	RPbdb_Lock**					RPbdb_LockController_releaseQueuedLocks(							RPbdb_LockController*			lock_controller	);
	RPbdb_Lock**					RPbdb_LockController_obtainLocks(									RPbdb_LockController*			lock_controller,
									   																	RPbdb_Lock**					locks_to_obtain,
									   																	int								number_of_locks_to_obtain	);
	RPbdb_Lock**					RPbdb_LockController_obtainLocksAndOverrideTimeout(					RPbdb_LockController*			lock_controller,
									   																	RPbdb_Lock**					locks_to_obtain,
									   																	int								number_of_locks_to_obtain,
									   																	uint32_t						timeout	);
	RPbdb_Lock**					RPbdb_LockController_releaseLocks(									RPbdb_LockController*			lock_controller,
									   																	RPbdb_Lock**					locks_to_release,
									   																	int								number_of_locks_to_release	);
	void							RPbdb_LockController_releaseAllLocks(								RPbdb_LockController*			lock_controller	);
	void							RPbdb_LockController_releaseAllLocksOnObject(						RPbdb_LockController*			lock_controller,
									   																	RPbdb_Record*					record	);
	int								RPbdb_LockController_clearDefaultLocks(								RPbdb_LockController*			lock_controller );
	int								RPbdb_LockController_clearExpiredLocks(								RPbdb_LockController*			lock_controller );
	int								RPbdb_LockController_clearLockRequestForLockerWithMostLocks(		RPbdb_LockController*			lock_controller );
	int								RPbdb_LockController_clearLockRequestForLockerWithMostWriteLocks(	RPbdb_LockController*			lock_controller );
	int								RPbdb_LockController_clearLockRequestForLockerWithLeastLocks(		RPbdb_LockController*			lock_controller );
	int								RPbdb_LockController_clearLockRequestForLockerWithLeastWriteLocks(	RPbdb_LockController*			lock_controller );
	int								RPbdb_LockController_clearLockRequestForLockerWithOldestLock(		RPbdb_LockController*			lock_controller );
	int								RPbdb_LockController_clearLockRequestForLockerWithYoungestLock(		RPbdb_LockController*			lock_controller );
	int								RPbdb_LockController_clearLockRequestForRandomLocker(				RPbdb_LockController*			lock_controller );
	void							RPbdb_LockController_closeAllLocks(									RPbdb_LockController*			lock_controller );
	RPbdb_LockSettingsController*	RPbdb_LockController_settingsController(							RPbdb_LockController*			lock_controller );

#endif

