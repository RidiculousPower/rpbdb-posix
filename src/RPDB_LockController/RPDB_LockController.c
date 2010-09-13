/*
 *		RPDB::LockController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_LockController.h"
#include "RPDB_LockController_internal.h"

#include "RPDB_Database.h"
#include "RPDB_Database_internal.h"
#include "RPDB_DatabaseCursor.h"

#include "RPDB_Lock.h"
#include "RPDB_Lock_internal.h"

#include "RPDB_Environment.h"

#include "RPDB_Record.h"

#include "RPDB_SettingsController.h"
#include "RPDB_LockSettingsController.h"
#include "RPDB_LockSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_LockController* RPDB_LockController_new( RPDB_Environment* parent_environment )	{

	RPDB_LockController*		lock_controller = calloc( 1, sizeof( RPDB_LockController ) );
	
	lock_controller->parent_environment = parent_environment;
		
	return lock_controller;
}


/***************************
*  free  *
***************************/
void RPDB_LockController_free(	RPDB_LockController** lock_controller )	{

	if ( ( *lock_controller )->queued_locks != NULL )	{
		RPDB_LockController_free( & ( *lock_controller ) );
	}

	free( *lock_controller );
	*lock_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_LockSettingsController* RPDB_LockController_settingsController(	RPDB_LockController* lock_controller )	{
	return lock_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_LockController_parentEnvironment(	RPDB_LockController* lock_controller )	{
	return lock_controller->parent_environment;
}

/*****************
*  lockerID  *
*****************/

//	Our lock controller serves as a locker to gather a collection of locks - it needs a unique locker ID for identification
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_id.html
uint32_t RPDB_LockController_lockerID( RPDB_LockController* lock_controller )	{

	if ( lock_controller->locker_id == 0 )	{
		
		lock_controller->parent_environment->wrapped_bdb_environment->lock_id(	lock_controller->parent_environment->wrapped_bdb_environment,
																				&( lock_controller->locker_id ) );
	}

	return lock_controller->locker_id;
}

/*****************
*  createLock  *
*****************/

RPDB_Lock* RPDB_LockController_createLock( RPDB_LockController* lock_controller )	{

	//	Create a lock instance
	RPDB_Lock*		new_lock	=	RPDB_Lock_new(	lock_controller );
	
	//	Queue the lock
	RPDB_LockController_queueLock(		lock_controller,
										new_lock );
	
	return new_lock;
}

/*****************
*  queueLock  *
*****************/

void RPDB_LockController_queueLock(	RPDB_LockController*		lock_controller __attribute__((unused)),
									RPDB_Lock*					lock_for_queue __attribute__((unused)) )	{

	//	FIX - not yet implemented


	//	using runtime data storage
	
}

/*****************************
*  removeLockFromQueue  *
*****************************/

void RPDB_LockController_removeLockFromQueue(	RPDB_LockController*			lock_controller __attribute__((unused)),
												RPDB_Lock*						queued_lock __attribute__((unused)) )	{

	//	FIX - not yet implemented

	//	using runtime data storage
	
}

/*************************
*  obtainQueuedLocks  *
*************************/

RPDB_Lock** RPDB_LockController_obtainQueuedLocks(	RPDB_LockController*	lock_controller	)	{

	return RPDB_LockController_internal_obtainOrReleaseQueuedLocks(	lock_controller,
	 																	DB_LOCK_GET	);
}

/*************************
*  releaseQueuedLocks  *
*************************/

RPDB_Lock** RPDB_LockController_releaseQueuedLocks(	RPDB_LockController*	lock_controller	)	{

	return RPDB_LockController_internal_obtainOrReleaseQueuedLocks(	lock_controller,
																		DB_LOCK_PUT	);
}

/*********************
*  obtainLocks  *
*********************/

RPDB_Lock** RPDB_LockController_obtainLocks(	RPDB_LockController*	lock_controller,
												RPDB_Lock**			locks_to_obtain,
												int						number_of_locks_to_obtain	)	{

	return RPDB_LockController_internal_obtainOrReleaseLocks(	lock_controller,
	 															locks_to_obtain,
																number_of_locks_to_obtain,
																DB_LOCK_GET,
																0	);
}

/*************************************
*  obtainLocksAndOverrideTimeout  *
*************************************/

RPDB_Lock** RPDB_LockController_obtainLocksAndOverrideTimeout(	RPDB_LockController*	lock_controller,
																	RPDB_Lock**			locks_to_obtain,
																	int						number_of_locks_to_obtain,
																	uint32_t				timeout	)	{

	return RPDB_LockController_internal_obtainOrReleaseLocks(	lock_controller,
	 															locks_to_obtain,
																number_of_locks_to_obtain,
																DB_LOCK_GET_TIMEOUT,
																timeout	);
}

/*********************
*  releaseLocks  *
*********************/

RPDB_Lock** RPDB_LockController_releaseLocks(	RPDB_LockController*	lock_controller,
												RPDB_Lock**			locks_to_release,
												int						number_of_locks_to_release	)	{

	return RPDB_LockController_internal_obtainOrReleaseLocks(	lock_controller,
	 															locks_to_release,
																number_of_locks_to_release,
																DB_LOCK_PUT,
																0	);
}

/*************************
*  releaseAllLocks  *
*************************/

void RPDB_LockController_releaseAllLocks(	RPDB_LockController*	lock_controller	)	{

	//	We only need 1 item in the array and its settings shouldn't matter (do we even need to allocate the DB_LOCKREQ?)
	DB_LOCKREQ		release_all_locks[ 1 ];
	
	//	DB_LOCKREQ lock and mode are ignored for DB_LOCK_PUT_OBJ

	release_all_locks[ 0 ].op		=	DB_LOCK_PUT_ALL;
	release_all_locks[ 0 ].timeout	=	0;

	lock_controller->parent_environment->wrapped_bdb_environment->lock_vec(	lock_controller->parent_environment->wrapped_bdb_environment,
							RPDB_LockController_lockerID( lock_controller ),
							RPDB_LockSettingsController_internal_obtainAndReleaseFlags( RPDB_SettingsController_lockSettingsController( RPDB_Environment_settingsController( lock_controller->parent_environment ) ) ),
							release_all_locks,
							1,
							NULL );
}

/*********************************
*  releaseAllLocksOnObject  *
*********************************/

void RPDB_LockController_releaseAllLocksOnObject(	RPDB_LockController*	lock_controller,
													RPDB_Record*				record	)	{

	DB_LOCKREQ		release_all_locks[ 1 ];
	
	//	DB_LOCKREQ lock and mode are ignored for DB_LOCK_PUT_OBJ

	release_all_locks[ 0 ].obj		=	record->data->wrapped_bdb_dbt->data;
	release_all_locks[ 0 ].op		=	DB_LOCK_PUT_OBJ;
	release_all_locks[ 0 ].timeout	=	0;

	lock_controller->parent_environment->wrapped_bdb_environment->lock_vec(	lock_controller->parent_environment->wrapped_bdb_environment,
							RPDB_LockController_lockerID( lock_controller ),
						   RPDB_LockSettingsController_internal_obtainAndReleaseFlags( RPDB_SettingsController_lockSettingsController( RPDB_Environment_settingsController( lock_controller->parent_environment ) ) ),
							release_all_locks,
							1,
							NULL );
}

/*************************
*  clearDefaultLocks  *
*************************/

//	If no default has been set, will randomly select for what types of locks to do deadlock detection
int RPDB_LockController_clearDefaultLocks( RPDB_LockController* lock_controller )	{

	return RPDB_LockController_internal_clearDeadlocks(	lock_controller,
															DB_LOCK_DEFAULT	);
}

/*************************
*  clearExpiredLocks  *
*************************/

int RPDB_LockController_clearExpiredLocks( RPDB_LockController* lock_controller )	{

	return RPDB_LockController_internal_clearDeadlocks(	lock_controller,
															DB_LOCK_EXPIRE	);
}

/*********************************************
*  clearLockRequestForLockerWithMostLocks  *
*********************************************/

int RPDB_LockController_clearLockRequestForLockerWithMostLocks( RPDB_LockController* lock_controller )	{

	return RPDB_LockController_internal_clearDeadlocks(	lock_controller,
															DB_LOCK_MAXLOCKS	);
}

/*****************************************************
*  clearLockRequestForLockerWithMostWriteLocks  *
*****************************************************/

int RPDB_LockController_clearLockRequestForLockerWithMostWriteLocks( RPDB_LockController* lock_controller )	{

	return RPDB_LockController_internal_clearDeadlocks(	lock_controller,
															DB_LOCK_MAXWRITE	);
}

/*************
*  clearLockRequestForLockerWithLeastLocks  *
*************/

int RPDB_LockController_clearLockRequestForLockerWithLeastLocks( RPDB_LockController* lock_controller )	{

	return RPDB_LockController_internal_clearDeadlocks(	lock_controller,
															DB_LOCK_MINLOCKS	);
}

/*****************************************************
*  clearLockRequestForLockerWithLeastWriteLocks  *
*****************************************************/

int RPDB_LockController_clearLockRequestForLockerWithLeastWriteLocks( RPDB_LockController* lock_controller )	{

	return RPDB_LockController_internal_clearDeadlocks(	lock_controller,
															DB_LOCK_MINWRITE	);
}

/*************************************************
*  clearLockRequestForLockerWithOldestLock  *
*************************************************/

int RPDB_LockController_clearLockRequestForLockerWithOldestLock( RPDB_LockController* lock_controller )	{

	return RPDB_LockController_internal_clearDeadlocks(	lock_controller,
															DB_LOCK_OLDEST	);
}

/*************************************************
*  clearLockRequestForLockerWithYoungestLock  *
*************************************************/

int RPDB_LockController_clearLockRequestForLockerWithYoungestLock( RPDB_LockController* lock_controller )	{

	return RPDB_LockController_internal_clearDeadlocks(	lock_controller,
															DB_LOCK_YOUNGEST	);
}

/*****************************************
*  clearLockRequestForRandomLocker  *
*****************************************/

int RPDB_LockController_clearLockRequestForRandomLocker( RPDB_LockController* lock_controller )	{

	return RPDB_LockController_internal_clearDeadlocks(	lock_controller,
																											DB_LOCK_RANDOM	);
}

/*********************
*  closeAllLocks  *
*********************/

void RPDB_LockController_closeAllLocks( RPDB_LockController* lock_controller )	{
	
	RPDB_Database_internal_closeAllStoredRuntimeAddresses(	lock_controller->runtime_storage_database,
																													(void *(*)(void*)) & RPDB_Lock_unlock );
}

/*********************
*  freeAllLocks  *
*********************/

void RPDB_LockController_freeAllLocks( RPDB_LockController* lock_controller )	{

	RPDB_LockController_closeAllLocks( lock_controller );
	RPDB_Database_internal_freeAllStoredRuntimeAddresses(	lock_controller->runtime_storage_database,
																												(void *(*)(void**)) & RPDB_Lock_internal_freeFromRuntimeStorage );
}


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*********************
*  clearDeadlocks  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_detect.html
int RPDB_LockController_internal_clearDeadlocks(	RPDB_LockController*	lock_controller,
 													uint32_t				which_locks	)	{

	RPDB_Environment*		environment	= lock_controller->parent_environment;

	environment->wrapped_bdb_environment->lock_detect(	environment->wrapped_bdb_environment,
								RPDB_LockSettingsController_internal_clearDeadlocksFlags( RPDB_SettingsController_lockSettingsController( RPDB_Environment_settingsController( environment ) ) ),
								which_locks,
								&( lock_controller->number_of_locks_last_cleared ) );

	return lock_controller->number_of_locks_last_cleared;
}

/*********************************
*  obtainOrReleaseQueuedLocks  *
*********************************/

RPDB_Lock** RPDB_LockController_internal_obtainOrReleaseQueuedLocks(	RPDB_LockController*	lock_controller,
																		u_int					action	)	{

	return RPDB_LockController_internal_obtainOrReleaseLocks(	lock_controller,
																lock_controller->queued_locks,
																lock_controller->number_of_queued_locks,
																action,
																0 );
}

/*****************************
*  obtainOrReleaseLocks  *
*****************************/

//	The DB_ENV->lock_vec method atomically obtains and releases one or more locks from the lock table. 
//	The DB_ENV->lock_vec method is intended to support acquisition or trading of multiple locks under one lock table semaphore, 
//	as is needed for lock coupling or in multigranularity locking for lock escalation.
//	If any of the requested locks cannot be acquired, or any of the locks to be released cannot be released, 
//	the operations before the failing operation are guaranteed to have completed successfully, and DB_ENV->lock_vec returns a non-zero value. 
//	In addition, if elistp is not NULL, it is set to point to the DB_LOCKREQ entry that was being processed when the error occurred.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_vec.html
RPDB_Lock** RPDB_LockController_internal_obtainOrReleaseLocks(	RPDB_LockController*	lock_controller,
 																	RPDB_Lock**			lock_array,
																	u_int					number_of_locks,
																	u_int					action,
																	uint32_t				timeout	)	{

	RPDB_Environment*			environment	= lock_controller->parent_environment;

	DB_LOCKREQ		lock_request_array[ number_of_locks ];
	//	If we don't succeed in performing action on all of the locks then we get a pointer to the point failure occurred
	DB_LOCKREQ*		lock_request_failure_point;

	u_int			current_lock_index;

	RPDB_Lock*		this_lock;
	DB_LOCKREQ*		this_lock_request;

	//	We need to build a DB_LOCKREQ* array from our requested lock objects
	for ( current_lock_index = 0 ; current_lock_index < number_of_locks ; current_lock_index++ )	{
		
		//	convenience accessors for the loop
		this_lock			=	lock_array[ 		current_lock_index ];
		this_lock_request	=	&( lock_request_array[	current_lock_index ] );
		
		//	copy settings to our DB_LOCKREQ, which is internal
		this_lock_request->op		= action;
		this_lock_request->lock			= this_lock->wrapped_bdb_lock;
		this_lock_request->mode			= this_lock->mode;
		this_lock_request->obj			= this_lock->object;
		
		if ( timeout != 0 )	{			
			
			this_lock_request->timeout		= timeout;
		}
		else	{
			
			this_lock_request->timeout		= this_lock->timeout;
		}
	}
	
	environment->wrapped_bdb_environment->lock_vec(	environment->wrapped_bdb_environment,
							RPDB_LockController_lockerID( lock_controller ),
							RPDB_LockSettingsController_internal_obtainAndReleaseFlags( RPDB_SettingsController_lockSettingsController( RPDB_Environment_settingsController( environment ) ) ),
							lock_request_array,
							number_of_locks,
							& lock_request_failure_point );
	
	//	If we had an error, we need to convert lock_request_failure_point to an RPDB_Lock* array and return it	
	
	//	How do we know the length remaining after lock_request_failure_point? Is this what is returned? 
	//	Documentation says "a non-zero number" is returned - does not specify if this is a count of failed elements. 
	//	Otherwise we have to step back in memory until we match the first pointer? Doesn't seem like that should be necessary. 
	
	
	//	Free lock_request_array
	free( lock_request_array );
	
	return lock_array;
}


