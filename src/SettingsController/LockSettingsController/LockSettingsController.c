/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "LockSettingsController.h"

#include "Environment.h"
#include "LockDeadlockDetectorSettingsController.h"

#include "SettingsController.h"

#include "LockSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPbdb_LockSettingsController* RPbdb_LockSettingsController_new( RPbdb_SettingsController* settings_controller )	{
	
	RPbdb_LockSettingsController*		lock_settings_controller = calloc( 1, sizeof( RPbdb_LockSettingsController ) );

	lock_settings_controller->parent_settings_controller = settings_controller;

	return lock_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_LockSettingsController_free(	RPbdb_LockSettingsController** lock_settings_controller )	{

	if ( ( *lock_settings_controller )->deadlock_detector_settings_controller != NULL )	{
		RPbdb_LockDeadlockDetectorSettingsController_free( & ( ( *lock_settings_controller )->deadlock_detector_settings_controller ) );
	}

	free( *lock_settings_controller );
	*lock_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_LockSettingsController_parentEnvironment(	RPbdb_LockSettingsController* lock_settings_controller )	{
	return lock_settings_controller->parent_settings_controller->parent_environment;
}

/*********
*  on  *
*********/

//	DB_INIT_LOCK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPbdb_LockSettingsController_on( RPbdb_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->on == TRUE )	{
		return DB_INIT_LOCK;
	}
	return FALSE;
}

/*************
*  off  *
*************/

//	DB_INIT_LOCK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
BOOL RPbdb_LockSettingsController_off( RPbdb_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

	/*************
	*  turnOn  *
	*************/

	//	DB_INIT_LOCK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPbdb_LockSettingsController_turnOn( RPbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->on = TRUE;
	}

	/*****************
	*  turnOff  *
	*****************/

	//	DB_INIT_LOCK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPbdb_LockSettingsController_turnOff( RPbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->on = FALSE;
	}

/*************************
*  prohibitLocking  *
*************************/

//	DB_NOLOCKING			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPbdb_LockSettingsController_prohibitLocking( RPbdb_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->prohibit_locking == TRUE)	{
		return DB_NOLOCKING;
	}
	return FALSE;
}

	/*****************************
	*  turnProhibitLockingOff  *
	*****************************/

	//	DB_NOLOCKING			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPbdb_LockSettingsController_turnProhibitLockingOn( RPbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->prohibit_locking = TRUE;
	}

	/*****************************
	*  turnProhibitLockingOff  *
	*****************************/

	//	DB_NOLOCKING			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPbdb_LockSettingsController_turnProhibitLockingOff( RPbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->prohibit_locking = FALSE;
	}

/*********************************************
*  timeoutReturnsReturnDenyNotDeadlock  *
*********************************************/

//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPbdb_LockSettingsController_timeoutReturnsDenyNotDeadlock( RPbdb_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->timeout_returns_deny_not_deadlock == TRUE )	{
		return DB_TIME_NOTGRANTED;
	}
	return FALSE;
}

	/*************************************************
	*  turnTimeoutReturnsReturnDenyNotDeadlockOn  *
	*************************************************/

	//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPbdb_LockSettingsController_turnTimeoutReturnsDenyNotDeadlockOn( RPbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->timeout_returns_deny_not_deadlock = TRUE;
	}

	/*************************************************
	*  turnTimeoutReturnsReturnDenyNotDeadlockOff  *
	*************************************************/

	//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPbdb_LockSettingsController_turnTimeoutReturnsDenyNotDeadlockOff( RPbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->timeout_returns_deny_not_deadlock = FALSE;
	}

/*************
*  wait  *
*************/

//	DB_LOCK_NOWAIT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_get.html
int RPbdb_LockSettingsController_noWaitingForConflicts( RPbdb_LockSettingsController* lock_settings_controller )	{

	if ( lock_settings_controller->not_waiting_for_conflicts == TRUE)	{
		return DB_LOCK_NOWAIT;
	}
	return FALSE;
}

	/*****************
	*  turnWaitOn  *
	*****************/

	//	DB_LOCK_NOWAIT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_get.html
	void RPbdb_LockSettingsController_turnNoWaitingForConflictsOn( RPbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->not_waiting_for_conflicts = TRUE;
	}

	/*********************
	*  turnWaitOff  *
	*********************/

	//	DB_LOCK_NOWAIT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_get.html
	void RPbdb_LockSettingsController_turnNoWaitingForConflictsOff( RPbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->not_waiting_for_conflicts = FALSE;
	}

/*************************************
*  lockForEnvironmentNotDatabase  *
*************************************/

//	DB_CDB_ALLDB            http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPbdb_LockSettingsController_lockForEnvironmentNotDatabase( RPbdb_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->lock_for_environment_not_database == TRUE )	{
		return DB_CDB_ALLDB;
	}
	return FALSE;
}

	/*********************************************
	*  turnLockForEnvironmentNotDatabaseOn  *
	*********************************************/

		void RPbdb_LockSettingsController_turnLockForEnvironmentNotDatabaseOn( RPbdb_LockSettingsController* lock_settings_controller )	{
			lock_settings_controller->lock_for_environment_not_database = TRUE;
		}

	/*********************************************
	*  turnLockForEnvironmentNotDatabaseOff  *
	*********************************************/

		void RPbdb_LockSettingsController_turnLockForEnvironmentNotDatabaseOff( RPbdb_LockSettingsController* lock_settings_controller )	{
			lock_settings_controller->lock_for_environment_not_database = FALSE;
		}

/*****************
*  timeout  *
*****************/

//	DB_SET_LOCK_TIMEOUT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_timeout.html
int RPbdb_LockSettingsController_timeout( RPbdb_LockSettingsController* lock_settings_controller )	{

	RPbdb_Environment*		environment = lock_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->get_timeout(	environment->wrapped_bdb_environment, 
															&( lock_settings_controller->timeout ), 
															DB_SET_LOCK_TIMEOUT );
	}
	return lock_settings_controller->timeout;
}

/*****************
*  setTimeout  *
*****************/

//	DB_SET_LOCK_TIMEOUT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_timeout.html
void RPbdb_LockSettingsController_setTimeout(	RPbdb_LockSettingsController* lock_settings_controller,
												uint32_t	timeout )	{

	RPbdb_Environment*		environment = lock_settings_controller->parent_settings_controller->parent_environment;

	lock_settings_controller->timeout	=	timeout;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->set_timeout(	environment->wrapped_bdb_environment, 
															lock_settings_controller->timeout, 
															DB_SET_LOCK_TIMEOUT );
	}
}

/*********************
*  conflictMatrix  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_conflicts.html
uint8_t* RPbdb_LockSettingsController_conflictMatrix( RPbdb_LockSettingsController* lock_settings_controller )	{
	
	RPbdb_Environment*		environment;

	environment = lock_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lk_conflicts(	environment->wrapped_bdb_environment, 
										(const u_int8_t**) &( lock_settings_controller->conflict_matrix ), 
										(int*) &( lock_settings_controller->conflict_matrix_size ) );
	}
	
	return lock_settings_controller->conflict_matrix;	
}

/*************************
*  setConflictMatrix  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_conflicts.html
void RPbdb_LockSettingsController_setConflictMatrix( 	RPbdb_LockSettingsController*	lock_settings_controller,
														uint8_t*						conflict_matrix )	{

	RPbdb_Environment*		environment;

	environment = lock_settings_controller->parent_settings_controller->parent_environment;
	
	lock_settings_controller->conflict_matrix = conflict_matrix;
	lock_settings_controller->conflict_matrix_size = sizeof( conflict_matrix );	
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_lk_conflicts(	environment->wrapped_bdb_environment, 
										conflict_matrix, 
										lock_settings_controller->conflict_matrix_size );
	}
}

/*****************
*  maxLockers  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_max_lockers.html
int RPbdb_LockSettingsController_maxLockers( RPbdb_LockSettingsController* lock_settings_controller )	{
	
	RPbdb_Environment*		environment;

	environment = lock_settings_controller->parent_settings_controller->parent_environment;
	
	if (	lock_settings_controller->max_lockers == 0
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lk_max_lockers(	environment->wrapped_bdb_environment, 
											(uint32_t*) &( lock_settings_controller->max_lockers ) );
	}
	
	return lock_settings_controller->max_lockers;
}

/*********************
*  setMaxLockers  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_max_lockers.html
void RPbdb_LockSettingsController_setMaxLockers( RPbdb_LockSettingsController* lock_settings_controller, uint32_t max_lockers )	{
	
	RPbdb_Environment*		environment;

	environment = lock_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_lk_max_lockers(	environment->wrapped_bdb_environment, 
											max_lockers );
	}
	
	lock_settings_controller->max_lockers = max_lockers;
}

/*****************
*  maxLocks  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_max_locks.html
int RPbdb_LockSettingsController_maxLocks( RPbdb_LockSettingsController* lock_settings_controller )	{

	RPbdb_Environment*		environment;

	environment = lock_settings_controller->parent_settings_controller->parent_environment;
	
	if (	lock_settings_controller->max_locks == 0
		&&	environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->get_lk_max_locks(	environment->wrapped_bdb_environment, 
										(uint32_t*) &( lock_settings_controller->max_locks ) );
	}
	
	return lock_settings_controller->max_locks;
}

/*********************
*  setMaxLocks  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_max_locks.html
void RPbdb_LockSettingsController_setMaxLocks( RPbdb_LockSettingsController* lock_settings_controller, uint32_t max_locks )	{
	
	RPbdb_Environment*		environment;

	environment = lock_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_lk_max_locks(	environment->wrapped_bdb_environment, 
										max_locks );
	}
	
	lock_settings_controller->max_locks = max_locks;
}

/*****************
*  maxObjects  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_max_objects.html
int RPbdb_LockSettingsController_maxObjects( RPbdb_LockSettingsController* lock_settings_controller )	{

	RPbdb_Environment*		environment;

	environment = lock_settings_controller->parent_settings_controller->parent_environment;
	
	if (	lock_settings_controller->max_objects == 0
		&&	environment->wrapped_bdb_environment != NULL )	{
	
		environment->wrapped_bdb_environment->get_lk_max_objects(	environment->wrapped_bdb_environment, 
											(uint32_t*) &( lock_settings_controller->max_objects ) );
	}
	
	return lock_settings_controller->max_objects;
}

/*********************
*  setMaxObjects  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_max_objects.html
void RPbdb_LockSettingsController_setMaxObjects( RPbdb_LockSettingsController* lock_settings_controller, uint32_t max_objects )	{

	RPbdb_Environment*		environment;

	environment = lock_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_lk_max_objects(	environment->wrapped_bdb_environment, 
											max_objects );
	}

	lock_settings_controller->max_objects = max_objects;
}

/*************************
*  numberOfPartitions  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_partitions.html
int RPbdb_LockSettingsController_numberOfPartitions( RPbdb_LockSettingsController* lock_settings_controller )	{

	RPbdb_Environment*		environment;

	environment = lock_settings_controller->parent_settings_controller->parent_environment;
	
	if (	lock_settings_controller->partitions == 0
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lk_partitions(	environment->wrapped_bdb_environment, 
										(uint32_t*) &( lock_settings_controller->partitions ) );
	}
	
	return lock_settings_controller->partitions;
}

/*****************************
*  setNumberOfPartitions  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lk_partitions.html
void RPbdb_LockSettingsController_setNumberOfPartitions( RPbdb_LockSettingsController* lock_settings_controller, uint32_t partitions )	{

	RPbdb_Environment*		environment;

	environment = lock_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_lk_partitions(	environment->wrapped_bdb_environment, 
										partitions );
	}

	lock_settings_controller->partitions = partitions;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/*********************************
*  deadlockDetectorController  *
*********************************/

RPbdb_LockDeadlockDetectorSettingsController* RPbdb_LockSettingsController_deadlockDetectorSettingsController( RPbdb_LockSettingsController* lock_settings_controller )	{
	
	if ( lock_settings_controller->deadlock_detector_settings_controller == NULL )	{
		lock_settings_controller->deadlock_detector_settings_controller = RPbdb_LockDeadlockDetectorSettingsController_new( lock_settings_controller ); 
	}
	return lock_settings_controller->deadlock_detector_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************
*  openFlags  *
*****************/

int RPbdb_LockSettingsController_internal_openFlags( RPbdb_LockSettingsController* lock_settings_controller )	{

	return RPbdb_LockSettingsController_noWaitingForConflicts(
				RPbdb_SettingsController_lockSettingsController( 
					RPbdb_Environment_settingsController( lock_settings_controller->parent_settings_controller->parent_environment ) ) );
	
}

/*************************
*  clearDeadlocksFlags  *
*************************/

int RPbdb_LockSettingsController_internal_clearDeadlocksFlags( RPbdb_LockSettingsController*	lock_settings_controller __attribute__((unused)) )	{
	
	// Currently unused - returns 0
	return RPBDB_NO_FLAGS;
}

/*****************************
*  obtainAndReleaseFlags  *
*****************************/

int RPbdb_LockSettingsController_internal_obtainAndReleaseFlags( RPbdb_LockSettingsController*	lock_settings_controller )	{
	
	return RPbdb_LockSettingsController_noWaitingForConflicts(
			  RPbdb_SettingsController_lockSettingsController( 
					  RPbdb_Environment_settingsController( lock_settings_controller->parent_settings_controller->parent_environment ) ) );
	
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_LockSettingsController* RPbdb_LockSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_LockSettingsController* lock_settings_controller )	{

	RPbdb_LockSettingsController* lock_settings_controller_copy	=	RPbdb_LockSettingsController_new( lock_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	lock_settings_controller_copy->partitions	=	lock_settings_controller->partitions;
	lock_settings_controller_copy->max_lockers	=	lock_settings_controller->max_lockers;
	lock_settings_controller_copy->conflict_matrix	=	lock_settings_controller->conflict_matrix;
	lock_settings_controller_copy->prohibit_locking	=	lock_settings_controller->prohibit_locking;
	lock_settings_controller_copy->not_waiting_for_conflicts	=	lock_settings_controller->not_waiting_for_conflicts;
	lock_settings_controller_copy->timeout	=	lock_settings_controller->timeout;
	lock_settings_controller_copy->max_locks	=	lock_settings_controller->max_locks;
	lock_settings_controller_copy->max_objects	=	lock_settings_controller->max_objects;
	lock_settings_controller_copy->conflict_matrix_size	=	lock_settings_controller->conflict_matrix_size;
	lock_settings_controller_copy->lock_for_environment_not_database	=	lock_settings_controller->lock_for_environment_not_database;
	lock_settings_controller_copy->timeout_returns_deny_not_deadlock	=	lock_settings_controller->timeout_returns_deny_not_deadlock;
	lock_settings_controller_copy->on	=	lock_settings_controller->on;

	return lock_settings_controller_copy;
}

