/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_LockSettingsController.h"

#include "Rbdb_Environment.h"
#include "Rbdb_LockDeadlockDetectorSettingsController.h"

#include "Rbdb_SettingsController.h"

#include "Rbdb_LockSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
Rbdb_LockSettingsController* Rbdb_LockSettingsController_new( Rbdb_SettingsController* settings_controller )	{
	
	Rbdb_LockSettingsController*		lock_settings_controller = calloc( 1, sizeof( Rbdb_LockSettingsController ) );

	lock_settings_controller->parent_settings_controller = settings_controller;

	return lock_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_LockSettingsController_free(	Rbdb_LockSettingsController** lock_settings_controller )	{

	if ( ( *lock_settings_controller )->deadlock_detector_settings_controller != NULL )	{
		Rbdb_LockDeadlockDetectorSettingsController_free( & ( ( *lock_settings_controller )->deadlock_detector_settings_controller ) );
	}

	free( *lock_settings_controller );
	*lock_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_LockSettingsController_parentEnvironment(	Rbdb_LockSettingsController* lock_settings_controller )	{
	return lock_settings_controller->parent_settings_controller->parent_environment;
}

/*********
*  on  *
*********/

//	DB_INIT_LOCK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int Rbdb_LockSettingsController_on( Rbdb_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->on == TRUE )	{
		return DB_INIT_LOCK;
	}
	return FALSE;
}

/*************
*  off  *
*************/

//	DB_INIT_LOCK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
BOOL Rbdb_LockSettingsController_off( Rbdb_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

	/*************
	*  turnOn  *
	*************/

	//	DB_INIT_LOCK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void Rbdb_LockSettingsController_turnOn( Rbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->on = TRUE;
	}

	/*****************
	*  turnOff  *
	*****************/

	//	DB_INIT_LOCK			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void Rbdb_LockSettingsController_turnOff( Rbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->on = FALSE;
	}

/*************************
*  prohibitLocking  *
*************************/

//	DB_NOLOCKING			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int Rbdb_LockSettingsController_prohibitLocking( Rbdb_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->prohibit_locking == TRUE)	{
		return DB_NOLOCKING;
	}
	return FALSE;
}

	/*****************************
	*  turnProhibitLockingOff  *
	*****************************/

	//	DB_NOLOCKING			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void Rbdb_LockSettingsController_turnProhibitLockingOn( Rbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->prohibit_locking = TRUE;
	}

	/*****************************
	*  turnProhibitLockingOff  *
	*****************************/

	//	DB_NOLOCKING			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void Rbdb_LockSettingsController_turnProhibitLockingOff( Rbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->prohibit_locking = FALSE;
	}

/*********************************************
*  timeoutReturnsReturnDenyNotDeadlock  *
*********************************************/

//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int Rbdb_LockSettingsController_timeoutReturnsDenyNotDeadlock( Rbdb_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->timeout_returns_deny_not_deadlock == TRUE )	{
		return DB_TIME_NOTGRANTED;
	}
	return FALSE;
}

	/*************************************************
	*  turnTimeoutReturnsReturnDenyNotDeadlockOn  *
	*************************************************/

	//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void Rbdb_LockSettingsController_turnTimeoutReturnsDenyNotDeadlockOn( Rbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->timeout_returns_deny_not_deadlock = TRUE;
	}

	/*************************************************
	*  turnTimeoutReturnsReturnDenyNotDeadlockOff  *
	*************************************************/

	//	DB_TIME_NOTGRANTED      http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void Rbdb_LockSettingsController_turnTimeoutReturnsDenyNotDeadlockOff( Rbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->timeout_returns_deny_not_deadlock = FALSE;
	}

/*************
*  wait  *
*************/

//	DB_LOCK_NOWAIT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_get.html
int Rbdb_LockSettingsController_noWaitingForConflicts( Rbdb_LockSettingsController* lock_settings_controller )	{

	if ( lock_settings_controller->not_waiting_for_conflicts == TRUE)	{
		return DB_LOCK_NOWAIT;
	}
	return FALSE;
}

	/*****************
	*  turnWaitOn  *
	*****************/

	//	DB_LOCK_NOWAIT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_get.html
	void Rbdb_LockSettingsController_turnNoWaitingForConflictsOn( Rbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->not_waiting_for_conflicts = TRUE;
	}

	/*********************
	*  turnWaitOff  *
	*********************/

	//	DB_LOCK_NOWAIT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/lock_get.html
	void Rbdb_LockSettingsController_turnNoWaitingForConflictsOff( Rbdb_LockSettingsController* lock_settings_controller )	{
		lock_settings_controller->not_waiting_for_conflicts = FALSE;
	}

/*************************************
*  lockForEnvironmentNotDatabase  *
*************************************/

//	DB_CDB_ALLDB            http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
int Rbdb_LockSettingsController_lockForEnvironmentNotDatabase( Rbdb_LockSettingsController* lock_settings_controller )	{
	if ( lock_settings_controller->lock_for_environment_not_database == TRUE )	{
		return DB_CDB_ALLDB;
	}
	return FALSE;
}

	/*********************************************
	*  turnLockForEnvironmentNotDatabaseOn  *
	*********************************************/

		void Rbdb_LockSettingsController_turnLockForEnvironmentNotDatabaseOn( Rbdb_LockSettingsController* lock_settings_controller )	{
			lock_settings_controller->lock_for_environment_not_database = TRUE;
		}

	/*********************************************
	*  turnLockForEnvironmentNotDatabaseOff  *
	*********************************************/

		void Rbdb_LockSettingsController_turnLockForEnvironmentNotDatabaseOff( Rbdb_LockSettingsController* lock_settings_controller )	{
			lock_settings_controller->lock_for_environment_not_database = FALSE;
		}

/*****************
*  timeout  *
*****************/

//	DB_SET_LOCK_TIMEOUT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_timeout.html
int Rbdb_LockSettingsController_timeout( Rbdb_LockSettingsController* lock_settings_controller )	{

	Rbdb_Environment*		environment = lock_settings_controller->parent_settings_controller->parent_environment;

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
void Rbdb_LockSettingsController_setTimeout(	Rbdb_LockSettingsController* lock_settings_controller,
												uint32_t	timeout )	{

	Rbdb_Environment*		environment = lock_settings_controller->parent_settings_controller->parent_environment;

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
uint8_t* Rbdb_LockSettingsController_conflictMatrix( Rbdb_LockSettingsController* lock_settings_controller )	{
	
	Rbdb_Environment*		environment;

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
void Rbdb_LockSettingsController_setConflictMatrix( 	Rbdb_LockSettingsController*	lock_settings_controller,
														uint8_t*						conflict_matrix )	{

	Rbdb_Environment*		environment;

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
int Rbdb_LockSettingsController_maxLockers( Rbdb_LockSettingsController* lock_settings_controller )	{
	
	Rbdb_Environment*		environment;

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
void Rbdb_LockSettingsController_setMaxLockers( Rbdb_LockSettingsController* lock_settings_controller, uint32_t max_lockers )	{
	
	Rbdb_Environment*		environment;

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
int Rbdb_LockSettingsController_maxLocks( Rbdb_LockSettingsController* lock_settings_controller )	{

	Rbdb_Environment*		environment;

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
void Rbdb_LockSettingsController_setMaxLocks( Rbdb_LockSettingsController* lock_settings_controller, uint32_t max_locks )	{
	
	Rbdb_Environment*		environment;

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
int Rbdb_LockSettingsController_maxObjects( Rbdb_LockSettingsController* lock_settings_controller )	{

	Rbdb_Environment*		environment;

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
void Rbdb_LockSettingsController_setMaxObjects( Rbdb_LockSettingsController* lock_settings_controller, uint32_t max_objects )	{

	Rbdb_Environment*		environment;

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
int Rbdb_LockSettingsController_numberOfPartitions( Rbdb_LockSettingsController* lock_settings_controller )	{

	Rbdb_Environment*		environment;

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
void Rbdb_LockSettingsController_setNumberOfPartitions( Rbdb_LockSettingsController* lock_settings_controller, uint32_t partitions )	{

	Rbdb_Environment*		environment;

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

Rbdb_LockDeadlockDetectorSettingsController* Rbdb_LockSettingsController_deadlockDetectorSettingsController( Rbdb_LockSettingsController* lock_settings_controller )	{
	
	if ( lock_settings_controller->deadlock_detector_settings_controller == NULL )	{
		lock_settings_controller->deadlock_detector_settings_controller = Rbdb_LockDeadlockDetectorSettingsController_new( lock_settings_controller ); 
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

int Rbdb_LockSettingsController_internal_openFlags( Rbdb_LockSettingsController* lock_settings_controller )	{

	return Rbdb_LockSettingsController_noWaitingForConflicts(
				Rbdb_SettingsController_lockSettingsController( 
					Rbdb_Environment_settingsController( lock_settings_controller->parent_settings_controller->parent_environment ) ) );
	
}

/*************************
*  clearDeadlocksFlags  *
*************************/

int Rbdb_LockSettingsController_internal_clearDeadlocksFlags( Rbdb_LockSettingsController*	lock_settings_controller __attribute__((unused)) )	{
	
	// Currently unused - returns 0
	return Rbdb_NO_FLAGS;
}

/*****************************
*  obtainAndReleaseFlags  *
*****************************/

int Rbdb_LockSettingsController_internal_obtainAndReleaseFlags( Rbdb_LockSettingsController*	lock_settings_controller )	{
	
	return Rbdb_LockSettingsController_noWaitingForConflicts(
			  Rbdb_SettingsController_lockSettingsController( 
					  Rbdb_Environment_settingsController( lock_settings_controller->parent_settings_controller->parent_environment ) ) );
	
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_LockSettingsController* Rbdb_LockSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_LockSettingsController* lock_settings_controller )	{

	Rbdb_LockSettingsController* lock_settings_controller_copy	=	Rbdb_LockSettingsController_new( lock_settings_controller->parent_settings_controller );

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

