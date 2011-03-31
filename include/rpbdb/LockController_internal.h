#ifndef RPBDB_LOCK_CONTROLLER_INTERNAL
	#define RPBDB_LOCK_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int					RPbdb_LockController_internal_clearDeadlocks(				RPbdb_LockController*		lock_controller,
   																				uint32_t					which_locks	);
RPbdb_Lock**		RPbdb_LockController_internal_obtainOrReleaseQueuedLocks(	RPbdb_LockController*		lock_controller,
					   															u_int						action	);
RPbdb_Lock**		RPbdb_LockController_internal_obtainOrReleaseLocks(			RPbdb_LockController*		lock_controller,
 					   															RPbdb_Lock**				lock_array,
					   															u_int						number_of_locks,
					   															u_int						action,
					   															uint32_t					timeout	);


#endif