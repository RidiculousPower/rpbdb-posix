#ifndef RPDB_LOCK_CONTROLLER_INTERNAL
	#define RPDB_LOCK_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int					RPDB_LockController_internal_clearDeadlocks(				RPDB_LockController*		lock_controller,
   																				uint32_t					which_locks	);
RPDB_Lock**		RPDB_LockController_internal_obtainOrReleaseQueuedLocks(	RPDB_LockController*		lock_controller,
					   															u_int						action	);
RPDB_Lock**		RPDB_LockController_internal_obtainOrReleaseLocks(			RPDB_LockController*		lock_controller,
 					   															RPDB_Lock**				lock_array,
					   															u_int						number_of_locks,
					   															u_int						action,
					   															uint32_t					timeout	);


#endif