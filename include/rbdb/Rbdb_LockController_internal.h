#ifndef Rbdb_LOCK_CONTROLLER_INTERNAL
	#define Rbdb_LOCK_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int					Rbdb_LockController_internal_clearDeadlocks(				Rbdb_LockController*		lock_controller,
   																				uint32_t					which_locks	);
Rbdb_Lock**		Rbdb_LockController_internal_obtainOrReleaseQueuedLocks(	Rbdb_LockController*		lock_controller,
					   															u_int						action	);
Rbdb_Lock**		Rbdb_LockController_internal_obtainOrReleaseLocks(			Rbdb_LockController*		lock_controller,
 					   															Rbdb_Lock**				lock_array,
					   															u_int						number_of_locks,
					   															u_int						action,
					   															uint32_t					timeout	);


#endif