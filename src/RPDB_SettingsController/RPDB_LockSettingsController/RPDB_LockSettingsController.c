/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_LockSettingsController.h"

#include "RPDB_Environment.h"
#include "RPDB_LockDeadlockDetectorSettingsController.h"

#include "RPDB_SettingsController.h"

#include "RPDB_LockSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_LockSettingsController* RPDB_LockSettingsController_new( RPDB_SettingsController* settings_controller )	{
	
	RPDB_LockSettingsController*		lock_settings_controller = calloc( 1, sizeof( RPDB_LockSettingsController ) );

	lock_settings_controller->parent_settings_controller = settings_controller;

	return lock_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_LockSettingsController_free(	RPDB_LockSettingsController** lock_settings_controller )	{

	if ( ( *lock_settings_controller )->deadlock_detector_settings_controller != NULL )	{
		RPDB_LockDeadlockDetectorSettingsController_free( & ( ( *lock_settings_controller )->deadlock_detector_settings_controller ) );
	}

	free( *lock_settings_controller );
	*lock_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_LockSettingsController_parentEnvironment(	RPDB_LockSettingsController* lock_settings_controller )	{
	return lock_settings_controller->parent_settings_controller->parent_environment;
}

/*********
*  on  *
*********/

//	DB_INIT_LOCK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPDB_LockSettingsController_on( RPDB_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->on == TRUE )	{
		return DB_INIT_LOCK;
	}
	return FALSE;
}

/*************
*  off  *
*************/

//	DB_INIT_LOCK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
BOOL RPDB_LockSettingsController_off( RPDB_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

	/*************
	*  turnOn  *
	*************/

	//	DB_INIT_LOCK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_LockSettingsController_turnOn( RPDB_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->on = TRUE;
	}

	/*****************
	*  turnOff  *
	*****************/

	//	DB_INIT_LOCK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_LockSettingsController_turnOff( RPDB_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->on = FALSE;
	}

/*************************
*  prohibitLocking  *
*************************/

//	DB_NOLOCKING			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPDB_LockSettingsController_prohibitLocking( RPDB_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->prohibit_locking == TRUE)	{
		return DB_NOLOCKING;
	}
	return FALSE;
}

	/*****************************
	*  turnProhibitLockingOff  *
	*****************************/

	//	DB_NOLOCKING			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_LockSettingsController_turnProhibitLockingOn( RPDB_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->prohibit_locking = TRUE;
	}

	/*****************************
	*  turnProhibitLockingOff  *
	*****************************/

	//	DB_NOLOCKING			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_LockSettingsController_turnProhibitLockingOff( RPDB_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->prohibit_locking = FALSE;
	}

/*********************************************
*  timeoutReturnsReturnDenyNotDeadlock  *
*********************************************/

//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPDB_LockSettingsController_timeoutReturnsReturnDenyNotDeadlock( RPDB_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->timeout_returns_deny_not_deadlock == TRUE )	{
		return DB_TIME_NOTGRANTED;
	}
	return FALSE;
}

	/*************************************************
	*  turnTimeoutReturnsReturnDenyNotDeadlockOn  *
	*************************************************/

	//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_LockSettingsController_turnTimeoutReturnsReturnDenyNotDeadlockOn( RPDB_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->timeout_returns_deny_not_deadlock = TRUE;
	}

	/*************************************************
	*  turnTimeoutReturnsReturnDenyNotDeadlockOff  *
	*************************************************/

	//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_LockSettingsController_turnTimeoutReturnsReturnDenyNotDeadlockOff( RPDB_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->timeout_returns_deny_not_deadlock = FALSE;
	}

/*************
*  wait  *
*************/

//	DB_LOCK_NOWAIT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_get.html
int RPDB_LockSettingsController_noWaitingForConflicts( RPDB_LockSettingsController* lock_settings_controller )	{

	if ( lock_settings_controller->not_waiting_for_conflicts == TRUE)	{
		return DB_LOCK_NOWAIT;
	}
	return FALSE;
}

	/*****************
	*  turnWaitOn  *
	*****************/

	//	DB_LOCK_NOWAIT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_get.html
	void RPDB_LockSettingsController_turnNoWaitingForConflictsOn( RPDB_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->not_waiting_for_conflicts = TRUE;
	}

	/*********************
	*  turnWaitOff  *
	*********************/

	//	DB_LOCK_NOWAIT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_get.html
	void RPDB_LockSettingsController_turnNoWaitingForConflictsOff( RPDB_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->not_waiting_for_conflicts = FALSE;
	}

/*************************************
*  lockForEnvironmentNotDatabase  *
*************************************/

//	DB_CDB_ALLDB            http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int RPDB_LockSettingsController_lockForEnvironmentNotDatabase( RPDB_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->lock_for_environment_not_database == TRUE )	{
		return DB_CDB_ALLDB;
	}
	return FALSE;
}

	/*********************************************
	*  turnLockForEnvironmentNotDatabaseOn  *
	*********************************************/

		void RPDB_LockSettingsController_turnLockForEnvironmentNotDatabaseOn( RPDB_LockSettingsController* lock_settings_controller )	{
			lock_settings_controller->lock_for_environment_not_database = TRUE;
		}

	/*********************************************
	*  turnLockForEnvironmentNotDatabaseOff  *
	*********************************************/

		void RPDB_LockSettingsController_turnLockForEnvironmentNotDatabaseOff( RPDB_LockSettingsController* lock_settings_controller )	{
			lock_settings_controller->lock_for_environment_not_database = FALSE;
		}

/*****************
*  timeout  *
*****************/

//	DB_SET_LOCK_TIMEOUT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_timeout.html
int RPDB_LockSettingsController_timeout( RPDB_LockSettingsController* lock_settings_controller )	{

	RPDB_Environment*		environment = lock_settings_controller->parent_settings_controller->parent_environment;

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
void RPDB_LockSettingsController_setTimeout(	RPDB_LockSettingsController* lock_settings_controller,
												uint32_t	timeout )	{

	RPDB_Environment*		environment = lock_settings_controller->parent_settings_controller->parent_environment;

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
uint8_t* RPDB_LockSettingsController_conflictMatrix( RPDB_LockSettingsController* lock_settings_controller )	{
	
	RPDB_Environment*		environment;

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
void RPDB_LockSettingsController_setConflictMatrix( 	RPDB_LockSettingsController*	lock_settings_controller,
														uint8_t*						conflict_matrix )	{

	RPDB_Environment*		environment;

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
int RPDB_LockSettingsController_maxLockers( RPDB_LockSettingsController* lock_settings_controller )	{
	
	RPDB_Environment*		environment;

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
void RPDB_LockSettingsController_setMaxLockers( RPDB_LockSettingsController* lock_settings_controller, uint32_t max_lockers )	{
	
	RPDB_Environment*		environment;

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
int RPDB_LockSettingsController_maxLocks( RPDB_LockSettingsController* lock_settings_controller )	{

	RPDB_Environment*		environment;

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
void RPDB_LockSettingsController_setMaxLocks( RPDB_LockSettingsController* lock_settings_controller, uint32_t max_locks )	{
	
	RPDB_Environment*		environment;

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
int RPDB_LockSettingsController_maxObjects( RPDB_LockSettingsController* lock_settings_controller )	{

	RPDB_Environment*		environment;

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
void RPDB_LockSettingsController_setMaxObjects( RPDB_LockSettingsController* lock_settings_controller, uint32_t max_objects )	{

	RPDB_Environment*		environment;

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
int RPDB_LockSettingsController_numberOfPartitions( RPDB_LockSettingsController* lock_settings_controller )	{

	RPDB_Environment*		environment;

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
void RPDB_LockSettingsController_setNumberOfPartitions( RPDB_LockSettingsController* lock_settings_controller, uint32_t partitions )	{

	RPDB_Environment*		environment;

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

RPDB_LockDeadlockDetectorSettingsController* RPDB_LockSettingsController_deadlockDetectorSettingsController( RPDB_LockSettingsController* lock_settings_controller )	{
	
	if ( lock_settings_controller->deadlock_detector_settings_controller == NULL )	{
		lock_settings_controller->deadlock_detector_settings_controller = RPDB_LockDeadlockDetectorSettingsController_new( lock_settings_controller ); 
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

int RPDB_LockSettingsController_internal_openFlags( RPDB_LockSettingsController* lock_settings_controller )	{

	return RPDB_LockSettingsController_noWaitingForConflicts(
				RPDB_SettingsController_lockSettingsController( 
					RPDB_Environment_settingsController( lock_settings_controller->parent_settings_controller->parent_environment ) ) );
	
}

/*************************
*  clearDeadlocksFlags  *
*************************/

int RPDB_LockSettingsController_internal_clearDeadlocksFlags( RPDB_LockSettingsController*	lock_settings_controller __attribute__((unused)) )	{
	
	// Currently unused - returns 0
	return RPDB_NO_FLAGS;
}

/*****************************
*  obtainAndReleaseFlags  *
*****************************/

int RPDB_LockSettingsController_internal_obtainAndReleaseFlags( RPDB_LockSettingsController*	lock_settings_controller )	{
	
	return RPDB_LockSettingsController_noWaitingForConflicts(
			  RPDB_SettingsController_lockSettingsController( 
					  RPDB_Environment_settingsController( lock_settings_controller->parent_settings_controller->parent_environment ) ) );
	
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_LockSettingsController* RPDB_LockSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_LockSettingsController* lock_settings_controller )	{

	RPDB_LockSettingsController* lock_settings_controller_copy	=	RPDB_LockSettingsController_new( lock_settings_controller->parent_settings_controller );

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

