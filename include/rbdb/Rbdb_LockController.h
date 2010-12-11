/*
 *		Rbdb::LockController
 *
 *
 */

#ifndef RBDB_LOCK_CONTROLLER
	#define RBDB_LOCK_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
	
	Rbdb_LockController*			Rbdb_LockController_new(											Rbdb_Environment*				parent_environment );

	void							Rbdb_LockController_free(	Rbdb_LockController** lock_controller );
	Rbdb_LockSettingsController*	Rbdb_LockController_settingsController(	Rbdb_LockController* lock_controller );
	Rbdb_Environment*		Rbdb_LockController_parentEnvironment(	Rbdb_LockController* lock_controller );

	void							Rbdb_LockController_free(											Rbdb_LockController**			lock_controller );
	uint32_t						Rbdb_LockController_lockerID(										Rbdb_LockController*			lock_controller );
	Rbdb_Lock*						Rbdb_LockController_createLock(									Rbdb_LockController*			lock_controller );
	void							Rbdb_LockController_queueLock(										Rbdb_LockController*							lock_controller,
									   																	Rbdb_Lock*						lock_for_queue );
	void							Rbdb_LockController_removeLockFromQueue(							Rbdb_LockController*							lock_controller,
									   																	Rbdb_Lock*						queued_lock );
	Rbdb_Lock**					Rbdb_LockController_obtainQueuedLocks(								Rbdb_LockController*			lock_controller	);
	Rbdb_Lock**					Rbdb_LockController_releaseQueuedLocks(							Rbdb_LockController*			lock_controller	);
	Rbdb_Lock**					Rbdb_LockController_obtainLocks(									Rbdb_LockController*			lock_controller,
									   																	Rbdb_Lock**					locks_to_obtain,
									   																	int								number_of_locks_to_obtain	);
	Rbdb_Lock**					Rbdb_LockController_obtainLocksAndOverrideTimeout(					Rbdb_LockController*			lock_controller,
									   																	Rbdb_Lock**					locks_to_obtain,
									   																	int								number_of_locks_to_obtain,
									   																	uint32_t						timeout	);
	Rbdb_Lock**					Rbdb_LockController_releaseLocks(									Rbdb_LockController*			lock_controller,
									   																	Rbdb_Lock**					locks_to_release,
									   																	int								number_of_locks_to_release	);
	void							Rbdb_LockController_releaseAllLocks(								Rbdb_LockController*			lock_controller	);
	void							Rbdb_LockController_releaseAllLocksOnObject(						Rbdb_LockController*			lock_controller,
									   																	Rbdb_Record*					record	);
	int								Rbdb_LockController_clearDefaultLocks(								Rbdb_LockController*			lock_controller );
	int								Rbdb_LockController_clearExpiredLocks(								Rbdb_LockController*			lock_controller );
	int								Rbdb_LockController_clearLockRequestForLockerWithMostLocks(		Rbdb_LockController*			lock_controller );
	int								Rbdb_LockController_clearLockRequestForLockerWithMostWriteLocks(	Rbdb_LockController*			lock_controller );
	int								Rbdb_LockController_clearLockRequestForLockerWithLeastLocks(		Rbdb_LockController*			lock_controller );
	int								Rbdb_LockController_clearLockRequestForLockerWithLeastWriteLocks(	Rbdb_LockController*			lock_controller );
	int								Rbdb_LockController_clearLockRequestForLockerWithOldestLock(		Rbdb_LockController*			lock_controller );
	int								Rbdb_LockController_clearLockRequestForLockerWithYoungestLock(		Rbdb_LockController*			lock_controller );
	int								Rbdb_LockController_clearLockRequestForRandomLocker(				Rbdb_LockController*			lock_controller );
	void							Rbdb_LockController_closeAllLocks(									Rbdb_LockController*			lock_controller );
	Rbdb_LockSettingsController*	Rbdb_LockController_settingsController(							Rbdb_LockController*			lock_controller );

#endif

