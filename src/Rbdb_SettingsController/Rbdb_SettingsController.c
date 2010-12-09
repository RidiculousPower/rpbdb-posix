/*
 *		Rbdb::SettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_SettingsController.h"

#include "Rbdb_DebugSettingsController.h"
#include "Rbdb_FileSettingsController.h"
#include "Rbdb_ThreadSettingsController.h"
#include "Rbdb_ErrorSettingsController.h"
#include "Rbdb_MessageSettingsController.h"

#include "Rbdb_MemoryPoolSettingsController.h"
#include "Rbdb_TransactionSettingsController.h"
#include "Rbdb_LockSettingsController.h"
#include "Rbdb_LogSettingsController.h"
#include "Rbdb_ReplicationSettingsController.h"
#include "Rbdb_ReplicationVerbositySettingsController.h"
#include "Rbdb_DatabaseVerbositySettingsController.h"
#include "Rbdb_DebugVerbositySettingsController.h"
#include "Rbdb_FileVerbositySettingsController.h"
#include "Rbdb_LockDeadlockDetectorSettingsController.h"
#include "Rbdb_LockDeadlockDetectorVerbositySettingsController.h"
#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_Environment.h"
#include "Rbdb_MutexSettingsController.h"
#include "Rbdb_DatabaseJoinSettingsController.h"

#include "Rbdb_RuntimeStorageController.h"
#include "Rbdb_EnvironmentCacheSettingsController.h"
#include "Rbdb_DirectorySettingsController.h"

#include "Rbdb_DatabaseRecordSettingsController.h"
#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"

#include "Rbdb_MemoryPoolReadWriteSettingsController.h"

#include "Rbdb_SettingsController_internal.h"


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_SettingsController* Rbdb_SettingsController_new( Rbdb_Environment* parent_environment )	{

	Rbdb_SettingsController*		settings_controller = calloc( 1, sizeof( Rbdb_SettingsController ) );

	settings_controller->parent_environment = parent_environment;
	
	return settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_SettingsController_free(	Rbdb_SettingsController** settings_controller )	{

	if ( ( *settings_controller )->mutex_settings_controller != NULL )	{
		Rbdb_MutexSettingsController_free( & ( ( *settings_controller )->mutex_settings_controller ) );
	}
	if ( ( *settings_controller )->error_settings_controller != NULL )	{
		Rbdb_ErrorSettingsController_free( & ( ( *settings_controller )->error_settings_controller ) );
	}
	/*
	if ( ( *settings_controller )->status_settings_controller != NULL )	{
		Rbdb_StatusSettingsController_free( & ( ( *settings_controller )->status_settings_controller ) );
	}
	*/
	if ( ( *settings_controller )->transaction_settings_controller != NULL )	{
		Rbdb_TransactionSettingsController_free( & ( ( *settings_controller )->transaction_settings_controller ) );
	}
	if ( ( *settings_controller )->thread_settings_controller != NULL )	{
		Rbdb_ThreadSettingsController_free( & ( ( *settings_controller )->thread_settings_controller ) );
	}
	if ( ( *settings_controller )->debug_settings_controller != NULL )	{
		Rbdb_DebugSettingsController_free( & ( ( *settings_controller )->debug_settings_controller ) );
	}
	if ( ( *settings_controller )->message_settings_controller != NULL )	{
		Rbdb_MessageSettingsController_free( & ( ( *settings_controller )->message_settings_controller ) );
	}
	if ( ( *settings_controller )->replication_settings_controller != NULL )	{
		Rbdb_ReplicationSettingsController_free( & ( ( *settings_controller )->replication_settings_controller ) );
	}
	if ( ( *settings_controller )->cache_settings_controller != NULL )	{
		Rbdb_EnvironmentCacheSettingsController_free( & ( ( *settings_controller )->cache_settings_controller ) );
	}
	if ( ( *settings_controller )->directory_settings_controller != NULL )	{
		Rbdb_DirectorySettingsController_free( & ( ( *settings_controller )->directory_settings_controller ) );
	}
	if ( ( *settings_controller )->lock_settings_controller != NULL )	{
		Rbdb_LockSettingsController_free( & ( ( *settings_controller )->lock_settings_controller ) );
	}
	if ( ( *settings_controller )->log_settings_controller != NULL )	{
		Rbdb_LogSettingsController_free( & ( ( *settings_controller )->log_settings_controller ) );
	}
	if ( ( *settings_controller )->database_settings_controller != NULL )	{
		Rbdb_DatabaseSettingsController_free( & ( ( *settings_controller )->database_settings_controller ) );
	}
	if ( ( *settings_controller )->memory_pool_settings_controller != NULL )	{
		Rbdb_MemoryPoolSettingsController_free( & ( ( *settings_controller )->memory_pool_settings_controller ) );
	}
	if ( ( *settings_controller )->file_settings_controller != NULL )	{
		Rbdb_FileSettingsController_free( & ( ( *settings_controller )->file_settings_controller ) );
	}

	free( *settings_controller );
	*settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_SettingsController_parentEnvironment(	Rbdb_SettingsController* settings_controller )	{
	return settings_controller->parent_environment;
}

/*************
*  SHMKey  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_shm_key.html
//	For getting the SHMKey
long Rbdb_SettingsController_SHMkey( Rbdb_SettingsController* settings_controller )	{

	Rbdb_Environment*			environment = settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->get_shm_key(	environment->wrapped_bdb_environment, 
									&( settings_controller->shm_key ) );
	}
	
	return settings_controller->shm_key;
}

/*****************
*  setSHMKey  *
*****************/

//	For setting the SHMKey
void Rbdb_SettingsController_setSHMkey(	Rbdb_SettingsController*	settings_controller, 
											long						shm_key )	{

	Rbdb_Environment*			environment = settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_shm_key( environment->wrapped_bdb_environment, shm_key );
	}
	
	settings_controller->shm_key = shm_key;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/*****************************
*  debugSettingController  *
*****************************/

Rbdb_DebugSettingsController* Rbdb_SettingsController_debugSettingsController( Rbdb_SettingsController* settings_controller )	{

	if ( settings_controller->debug_settings_controller == NULL )	{
		settings_controller->debug_settings_controller = Rbdb_DebugSettingsController_new( settings_controller );
	}

	return settings_controller->debug_settings_controller;
}

/*****************************
*  fileSettingsController  *
*****************************/

Rbdb_FileSettingsController* Rbdb_SettingsController_fileSettingsController( Rbdb_SettingsController* settings_controller )	{

	if ( settings_controller->file_settings_controller == NULL )	{
		settings_controller->file_settings_controller = Rbdb_FileSettingsController_new( settings_controller );
	}

	return settings_controller->file_settings_controller;
}

/*********************************
*  threadSettingsController  *
*********************************/

Rbdb_ThreadSettingsController* Rbdb_SettingsController_threadSettingsController( Rbdb_SettingsController* settings_controller )	{

	if ( settings_controller->thread_settings_controller == NULL )	{
		settings_controller->thread_settings_controller = Rbdb_ThreadSettingsController_new( settings_controller );
	}

	return settings_controller->thread_settings_controller;

}

/*********************************
*  errorSettingsController  *
*********************************/

Rbdb_ErrorSettingsController* Rbdb_SettingsController_errorSettingsController( Rbdb_SettingsController* settings_controller )	{

	if ( settings_controller->error_settings_controller == NULL )	{
		settings_controller->error_settings_controller = Rbdb_ErrorSettingsController_new( settings_controller );
	}

	return settings_controller->error_settings_controller;

}

/*********************************
*  messageSettingsController  *
*********************************/

Rbdb_MessageSettingsController* Rbdb_SettingsController_messageSettingsController( Rbdb_SettingsController* settings_controller )	{

	if ( settings_controller->message_settings_controller == NULL )	{
		settings_controller->message_settings_controller = Rbdb_MessageSettingsController_new( settings_controller );
	}

	return settings_controller->message_settings_controller;

}

/*********************************
*  statusSettingsController  *
*********************************/
/*
Rbdb_StatusSettingsController* Rbdb_SettingsController_statusSettingsController( Rbdb_SettingsController* settings_controller )	{

	if ( settings_controller->status_settings_controller == NULL )	{
		settings_controller->status_settings_controller = Rbdb_StatusSettingsController_new( settings_controller );
	}

	return settings_controller->status_settings_controller;
}
*/
/*************************************
*  memoryPoolSettingsController  *
************************************/

Rbdb_MemoryPoolSettingsController* Rbdb_SettingsController_memoryPoolSettingsController( Rbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->memory_pool_settings_controller == NULL )	{
		settings_controller->memory_pool_settings_controller = Rbdb_MemoryPoolSettingsController_new( settings_controller );
	}
	
	return settings_controller->memory_pool_settings_controller;
}

/*************************************
*  transactionSettingsController  *
************************************/

Rbdb_TransactionSettingsController* Rbdb_SettingsController_transactionSettingsController( Rbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->transaction_settings_controller == NULL )	{
		settings_controller->transaction_settings_controller = Rbdb_TransactionSettingsController_new( settings_controller );
	}
	
	return settings_controller->transaction_settings_controller;
}

/*************************************
*  lockSettingsController  *
************************************/

Rbdb_LockSettingsController* Rbdb_SettingsController_lockSettingsController( Rbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->lock_settings_controller == NULL )	{
		settings_controller->lock_settings_controller = Rbdb_LockSettingsController_new( settings_controller );
	}
	
	return settings_controller->lock_settings_controller;
}

/*************************************
*  logSettingsController  *
************************************/

Rbdb_LogSettingsController* Rbdb_SettingsController_logSettingsController( Rbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->log_settings_controller == NULL )	{
		settings_controller->log_settings_controller = Rbdb_LogSettingsController_new( settings_controller );
	}
	
	return settings_controller->log_settings_controller;
}

/*************************************
*  replicationSettingsController  *
************************************/

Rbdb_ReplicationSettingsController* Rbdb_SettingsController_replicationSettingsController( Rbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->replication_settings_controller == NULL )	{
		settings_controller->replication_settings_controller = Rbdb_ReplicationSettingsController_new( settings_controller );
	}
	
	return settings_controller->replication_settings_controller;
}

/*************************************
*  databaseSettingsController  *
************************************/

Rbdb_DatabaseSettingsController* Rbdb_SettingsController_databaseSettingsController( Rbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->database_settings_controller == NULL )	{
		settings_controller->database_settings_controller = Rbdb_DatabaseSettingsController_new( settings_controller );
	}
	
	return settings_controller->database_settings_controller;
}

/*************************************
*  mutexSettingsController  *
************************************/

Rbdb_MutexSettingsController* Rbdb_SettingsController_mutexSettingsController( Rbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->mutex_settings_controller == NULL )	{
		settings_controller->mutex_settings_controller = Rbdb_MutexSettingsController_new( settings_controller );
	}
	
	return settings_controller->mutex_settings_controller;
}

/*************************************
*  cacheSettingsController  *
************************************/

Rbdb_EnvironmentCacheSettingsController* Rbdb_SettingsController_cacheSettingsController( Rbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->cache_settings_controller == NULL )	{
		settings_controller->cache_settings_controller = Rbdb_EnvironmentCacheSettingsController_new( settings_controller );
	}
	
	return settings_controller->cache_settings_controller;
}

/*************************************
*  DirectorySettingsController  *
************************************/

Rbdb_DirectorySettingsController* Rbdb_SettingsController_directorySettingsController( Rbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->directory_settings_controller == NULL )	{
		settings_controller->directory_settings_controller = Rbdb_DirectorySettingsController_new( settings_controller );
	}
	
	return settings_controller->directory_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********************
*  createFlags  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
//	Return environment's bit-wised | flags as int
int Rbdb_SettingsController_internal_createFlags( Rbdb_SettingsController* settings_controller __attribute__((unused)) )	{
	//	Was RPC I think now none
	return FALSE;
}

/********************
*  eraseFlags  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_remove.html
int Rbdb_SettingsController_internal_eraseFlags( Rbdb_SettingsController* settings_controller )	{
		
	return Rbdb_FileSettingsController_forceRemoval( Rbdb_SettingsController_fileSettingsController( settings_controller ) )
			| Rbdb_FileSettingsController_permitEnvironmentBasedFileNaming( Rbdb_SettingsController_fileSettingsController( settings_controller ) ) 
			| Rbdb_FileSettingsController_useEnvironmentHomePermissionsForFileNaming( Rbdb_SettingsController_fileSettingsController( settings_controller ) );
}

/****************
*  openFlags  *
****************/

//	DB_INIT_LOG
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int Rbdb_SettingsController_internal_openFlags( Rbdb_SettingsController* settings_controller )	{
	
	Rbdb_DebugSettingsController*									debug_settings_controller										=	Rbdb_SettingsController_debugSettingsController( settings_controller );
	Rbdb_TransactionSettingsController*						transaction_settings_controller							=	Rbdb_SettingsController_transactionSettingsController( settings_controller );
	Rbdb_FileSettingsController*									file_settings_controller										=	Rbdb_SettingsController_fileSettingsController( settings_controller );
	Rbdb_MemoryPoolSettingsController*						memory_pool_settings_controller							=	Rbdb_SettingsController_memoryPoolSettingsController( settings_controller );
	Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller	=	Rbdb_MemoryPoolSettingsController_readWriteSettingsController( memory_pool_settings_controller );
	
	int	lock_settings_controller_on														=	Rbdb_LockSettingsController_on( Rbdb_SettingsController_lockSettingsController( settings_controller ) );
	int	memory_pool_settings_controller_on										=	Rbdb_MemoryPoolSettingsController_on( memory_pool_settings_controller );
	int	transaction_settings_controller_on										=	Rbdb_TransactionSettingsController_on( transaction_settings_controller );
	int	concurrent_data_store_locking_on											=	Rbdb_TransactionSettingsController_concurrentDataStoreLocking( transaction_settings_controller );
	int	log_settings_controller_on														=	Rbdb_LogSettingsController_on( Rbdb_SettingsController_logSettingsController( settings_controller ) );
	int	replication_settings_controller_on										=	Rbdb_ReplicationSettingsController_on( Rbdb_SettingsController_replicationSettingsController( settings_controller ) );

	int	create_if_necessary																		=	Rbdb_FileSettingsController_createIfNecessary( file_settings_controller );
	int	application_has_exclusive_access											=	Rbdb_MemoryPoolReadWriteSettingsController_applicationHasExclusiveAccess( memory_pool_read_write_settings_controller );
	int	run_normal_recovery_before_opening_environment				=	Rbdb_DebugSettingsController_runNormalRecoveryBeforeOpeningEnvironment(	debug_settings_controller );
	int	run_catastrophic_recovery_before_opening_environment	=	Rbdb_DebugSettingsController_runCatastrophicRecoveryBeforeOpeningEnvironment(	debug_settings_controller );
	int	register_for_recovery																	=	Rbdb_DebugSettingsController_registerForRecovery( debug_settings_controller );
	int	check_for_environment_failure_during_open							=	Rbdb_DebugSettingsController_checkForEnvironmentFailureDuringOpen( debug_settings_controller );
	int	permit_environment_based_file_naming									=	Rbdb_FileSettingsController_permitEnvironmentBasedFileNaming( file_settings_controller );
	int	use_environment_home_permissions_for_file_naming			=	Rbdb_FileSettingsController_useEnvironmentHomePermissionsForFileNaming( file_settings_controller );
	int	open_in_lockdown																			=	Rbdb_DebugSettingsController_openInLockdown( debug_settings_controller );
	
	return	concurrent_data_store_locking_on
			|		lock_settings_controller_on
			|		log_settings_controller_on
			|		memory_pool_settings_controller_on
			|		replication_settings_controller_on
			|		transaction_settings_controller_on
			|		run_normal_recovery_before_opening_environment
			|		run_catastrophic_recovery_before_opening_environment
			|		register_for_recovery
			|		check_for_environment_failure_during_open
			|		permit_environment_based_file_naming
			|		use_environment_home_permissions_for_file_naming
			|		create_if_necessary
			|		open_in_lockdown
			|		application_has_exclusive_access;
}

/****************************
*  closeEnvironmentFlags  *
****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_close.html
int Rbdb_SettingsController_internal_closeFlags( Rbdb_SettingsController* settings_controller __attribute__((unused)) )	{

	//	currently unused- set to 0
	return Rbdb_NO_FLAGS;
}

/****************
*  setFlags  * 
****************/

void Rbdb_SettingsController_internal_setFlags( Rbdb_SettingsController* settings_controller )	{

	Rbdb_Environment*	environment = settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		Rbdb_EnvironmentCacheSettingsController*					cache_settings_controller												=	Rbdb_SettingsController_cacheSettingsController( settings_controller );
		Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_SettingsController_databaseSettingsController( settings_controller );
		Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
		Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
		Rbdb_DebugSettingsController*											debug_settings_controller												=	Rbdb_SettingsController_debugSettingsController( settings_controller );
		Rbdb_TransactionSettingsController*								transaction_settings_controller									=	Rbdb_SettingsController_transactionSettingsController( settings_controller );
		Rbdb_MemoryPoolSettingsController*								memory_pool_settings_controller									=	Rbdb_SettingsController_memoryPoolSettingsController( settings_controller );
		Rbdb_MemoryPoolReadWriteSettingsController*				memory_pool_read_write_settings_controller			=	Rbdb_MemoryPoolSettingsController_readWriteSettingsController( memory_pool_settings_controller );
		Rbdb_LockSettingsController*											lock_settings_controller												=	Rbdb_SettingsController_lockSettingsController( settings_controller );
		
		environment->wrapped_bdb_environment->set_flags(	environment->wrapped_bdb_environment,
																											Rbdb_EnvironmentCacheSettingsController_buffering( cache_settings_controller )
																											|	Rbdb_DatabaseRecordReadWriteSettingsController_syncPriorToWriteReturn( database_record_read_write_settings_controller )
																											|	Rbdb_DebugSettingsController_prohibitPanic( debug_settings_controller )
																											|	Rbdb_DebugSettingsController_panic( debug_settings_controller )
																											|	Rbdb_DebugSettingsController_yieldCPUForStressTest( debug_settings_controller )
																											|	Rbdb_LockSettingsController_prohibitLocking( lock_settings_controller )
																											|	Rbdb_LockSettingsController_timeoutReturnsDenyNotDeadlock( lock_settings_controller )
																											|	Rbdb_LockSettingsController_lockForEnvironmentNotDatabase( lock_settings_controller )
																											|	Rbdb_MemoryPoolSettingsController_memoryMapping( memory_pool_settings_controller )
																											|	Rbdb_MemoryPoolReadWriteSettingsController_pagefaultSharedRegions( memory_pool_read_write_settings_controller )
																											|	Rbdb_TransactionSettingsController_prohibitSyncOnWrite( transaction_settings_controller )
																											|	Rbdb_TransactionSettingsController_prohibitSyncOnCommit( transaction_settings_controller )
																											|	Rbdb_TransactionSettingsController_timeoutInMicrosecondsReturnsDenyNotDeadlock( transaction_settings_controller )
																											|	Rbdb_TransactionSettingsController_snapshotIsolation( transaction_settings_controller )
																											|	Rbdb_TransactionSettingsController_encloseAllActivityInTransaction( transaction_settings_controller )
																											|	Rbdb_TransactionSettingsController_environmentalSnapshotIsolation( transaction_settings_controller ),
																											1 );
	}	
}	


/****************
*  getFlags  * 
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_close.html
uint32_t Rbdb_SettingsController_internal_getFlags( Rbdb_SettingsController* settings_controller )	{

	//	why is parent_environment NULL?
	Rbdb_Environment*	environment = settings_controller->parent_environment;
	
	uint32_t		flags;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_flags(	environment->wrapped_bdb_environment,
															& flags );
	}

	//	currently unused- set to 0
	return flags;
}



/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_SettingsController* Rbdb_SettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_SettingsController* settings_controller )	{

	Rbdb_SettingsController* settings_controller_copy	=	Rbdb_SettingsController_new( settings_controller->parent_environment );

	//	Instances and Pointers
	settings_controller_copy->shm_key	=	settings_controller->shm_key;

	return settings_controller_copy;
}

/********************
*  setVerbosity  * 
*******************/

void Rbdb_SettingsController_internal_setVerbosity( Rbdb_SettingsController* settings_controller )	{

	Rbdb_Environment*	environment = settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->set_verbose(	environment->wrapped_bdb_environment,
															Rbdb_ReplicationVerbositySettingsController_displayAllReplicationInformation( Rbdb_ReplicationSettingsController_verbositySettingsController( Rbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	Rbdb_ReplicationVerbositySettingsController_displayElectionInformation( Rbdb_ReplicationSettingsController_verbositySettingsController( Rbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	Rbdb_ReplicationVerbositySettingsController_displayReplicationMasterLeaseInformation( Rbdb_ReplicationSettingsController_verbositySettingsController( Rbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	Rbdb_ReplicationVerbositySettingsController_displayMiscProcessingInformation( Rbdb_ReplicationSettingsController_verbositySettingsController( Rbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	Rbdb_ReplicationVerbositySettingsController_displayMessageProcessingInformation( Rbdb_ReplicationSettingsController_verbositySettingsController( Rbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	Rbdb_ReplicationVerbositySettingsController_displayClientSynchronizationInformation( Rbdb_ReplicationSettingsController_verbositySettingsController( Rbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	Rbdb_ReplicationVerbositySettingsController_displayManagerConnectionFailureInformation( Rbdb_ReplicationSettingsController_verbositySettingsController( Rbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	Rbdb_ReplicationVerbositySettingsController_displayManagerMiscProcessing( Rbdb_ReplicationSettingsController_verbositySettingsController( Rbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	Rbdb_DatabaseVerbositySettingsController_displayAdditionalInformationForDBRegisterFlag( Rbdb_DatabaseSettingsController_verbositySettingsController( Rbdb_SettingsController_databaseSettingsController( settings_controller ) ) )
															|	Rbdb_DebugVerbositySettingsController_displayAdditionalInformationDuringRecovery( Rbdb_DebugSettingsController_verbositySettingsController( Rbdb_SettingsController_debugSettingsController( settings_controller ) ) )
 															|	Rbdb_FileVerbositySettingsController_displayAdditionalInformationDuringOpenCloseRenameFileOperations( Rbdb_FileSettingsController_verbositySettingsController( Rbdb_SettingsController_fileSettingsController( settings_controller ) ) )
															|	Rbdb_FileVerbositySettingsController_displayAdditionalInformationDuringAllFileOperations( Rbdb_FileSettingsController_verbositySettingsController( Rbdb_SettingsController_fileSettingsController( settings_controller ) ) )
															|	Rbdb_LockDeadlockDetectorVerbositySettingsController_displayAdditionalInformationDuringDeadlockDetection( Rbdb_LockDeadlockDetectorSettingsController_verbositySettingsController( Rbdb_LockSettingsController_deadlockDetectorSettingsController( Rbdb_SettingsController_lockSettingsController( settings_controller ) ) ) )
															|	Rbdb_LockDeadlockDetectorVerbositySettingsController_displayWaitTableDuringDeadlockDetection( Rbdb_LockDeadlockDetectorSettingsController_verbositySettingsController( Rbdb_LockSettingsController_deadlockDetectorSettingsController( Rbdb_SettingsController_lockSettingsController( settings_controller ) ) ) ),
															1 );
	}	
}
	
