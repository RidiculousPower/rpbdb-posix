/*
 *		RPbdb::SettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "SettingsController.h"

#include "DebugSettingsController.h"
#include "FileSettingsController.h"
#include "ThreadSettingsController.h"
#include "ErrorSettingsController.h"
#include "MessageSettingsController.h"

#include "MemoryPoolSettingsController.h"
#include "TransactionSettingsController.h"
#include "LockSettingsController.h"
#include "LogSettingsController.h"
#include "ReplicationSettingsController.h"
#include "ReplicationVerbositySettingsController.h"
#include "DatabaseVerbositySettingsController.h"
#include "DebugVerbositySettingsController.h"
#include "FileVerbositySettingsController.h"
#include "LockDeadlockDetectorSettingsController.h"
#include "LockDeadlockDetectorVerbositySettingsController.h"
#include "DatabaseSettingsController.h"
#include "Environment.h"
#include "MutexSettingsController.h"
#include "DatabaseJoinSettingsController.h"

#include "RuntimeStorageController.h"
#include "EnvironmentCacheSettingsController.h"
#include "DirectorySettingsController.h"

#include "DatabaseRecordSettingsController.h"
#include "DatabaseRecordReadWriteSettingsController.h"

#include "MemoryPoolReadWriteSettingsController.h"

#include "SettingsController_internal.h"


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_SettingsController* RPbdb_SettingsController_new( RPbdb_Environment* parent_environment )	{

	RPbdb_SettingsController*		settings_controller = calloc( 1, sizeof( RPbdb_SettingsController ) );

	settings_controller->parent_environment = parent_environment;
	
	return settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_SettingsController_free(	RPbdb_SettingsController** settings_controller )	{

	if ( ( *settings_controller )->mutex_settings_controller != NULL )	{
		RPbdb_MutexSettingsController_free( & ( ( *settings_controller )->mutex_settings_controller ) );
	}
	if ( ( *settings_controller )->error_settings_controller != NULL )	{
		RPbdb_ErrorSettingsController_free( & ( ( *settings_controller )->error_settings_controller ) );
	}
	/*
	if ( ( *settings_controller )->status_settings_controller != NULL )	{
		RPbdb_StatusSettingsController_free( & ( ( *settings_controller )->status_settings_controller ) );
	}
	*/
	if ( ( *settings_controller )->transaction_settings_controller != NULL )	{
		RPbdb_TransactionSettingsController_free( & ( ( *settings_controller )->transaction_settings_controller ) );
	}
	if ( ( *settings_controller )->thread_settings_controller != NULL )	{
		RPbdb_ThreadSettingsController_free( & ( ( *settings_controller )->thread_settings_controller ) );
	}
	if ( ( *settings_controller )->debug_settings_controller != NULL )	{
		RPbdb_DebugSettingsController_free( & ( ( *settings_controller )->debug_settings_controller ) );
	}
	if ( ( *settings_controller )->message_settings_controller != NULL )	{
		RPbdb_MessageSettingsController_free( & ( ( *settings_controller )->message_settings_controller ) );
	}
	if ( ( *settings_controller )->replication_settings_controller != NULL )	{
		RPbdb_ReplicationSettingsController_free( & ( ( *settings_controller )->replication_settings_controller ) );
	}
	if ( ( *settings_controller )->cache_settings_controller != NULL )	{
		RPbdb_EnvironmentCacheSettingsController_free( & ( ( *settings_controller )->cache_settings_controller ) );
	}
	if ( ( *settings_controller )->directory_settings_controller != NULL )	{
		RPbdb_DirectorySettingsController_free( & ( ( *settings_controller )->directory_settings_controller ) );
	}
	if ( ( *settings_controller )->lock_settings_controller != NULL )	{
		RPbdb_LockSettingsController_free( & ( ( *settings_controller )->lock_settings_controller ) );
	}
	if ( ( *settings_controller )->log_settings_controller != NULL )	{
		RPbdb_LogSettingsController_free( & ( ( *settings_controller )->log_settings_controller ) );
	}
	if ( ( *settings_controller )->database_settings_controller != NULL )	{
		RPbdb_DatabaseSettingsController_free( & ( ( *settings_controller )->database_settings_controller ) );
	}
	if ( ( *settings_controller )->memory_pool_settings_controller != NULL )	{
		RPbdb_MemoryPoolSettingsController_free( & ( ( *settings_controller )->memory_pool_settings_controller ) );
	}
	if ( ( *settings_controller )->file_settings_controller != NULL )	{
		RPbdb_FileSettingsController_free( & ( ( *settings_controller )->file_settings_controller ) );
	}

	free( *settings_controller );
	*settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_SettingsController_parentEnvironment(	RPbdb_SettingsController* settings_controller )	{
	return settings_controller->parent_environment;
}

/*************
*  SHMKey  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_shm_key.html
//	For getting the SHMKey
long RPbdb_SettingsController_SHMkey( RPbdb_SettingsController* settings_controller )	{

	RPbdb_Environment*			environment = settings_controller->parent_environment;
	
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
void RPbdb_SettingsController_setSHMkey(	RPbdb_SettingsController*	settings_controller, 
											long						shm_key )	{

	RPbdb_Environment*			environment = settings_controller->parent_environment;
	
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

RPbdb_DebugSettingsController* RPbdb_SettingsController_debugSettingsController( RPbdb_SettingsController* settings_controller )	{

	if ( settings_controller->debug_settings_controller == NULL )	{
		settings_controller->debug_settings_controller = RPbdb_DebugSettingsController_new( settings_controller );
	}

	return settings_controller->debug_settings_controller;
}

/*****************************
*  fileSettingsController  *
*****************************/

RPbdb_FileSettingsController* RPbdb_SettingsController_fileSettingsController( RPbdb_SettingsController* settings_controller )	{

	if ( settings_controller->file_settings_controller == NULL )	{
		settings_controller->file_settings_controller = RPbdb_FileSettingsController_new( settings_controller );
	}

	return settings_controller->file_settings_controller;
}

/*********************************
*  threadSettingsController  *
*********************************/

RPbdb_ThreadSettingsController* RPbdb_SettingsController_threadSettingsController( RPbdb_SettingsController* settings_controller )	{

	if ( settings_controller->thread_settings_controller == NULL )	{
		settings_controller->thread_settings_controller = RPbdb_ThreadSettingsController_new( settings_controller );
	}

	return settings_controller->thread_settings_controller;

}

/*********************************
*  errorSettingsController  *
*********************************/

RPbdb_ErrorSettingsController* RPbdb_SettingsController_errorSettingsController( RPbdb_SettingsController* settings_controller )	{

	if ( settings_controller->error_settings_controller == NULL )	{
		settings_controller->error_settings_controller = RPbdb_ErrorSettingsController_new( settings_controller );
	}

	return settings_controller->error_settings_controller;

}

/*********************************
*  messageSettingsController  *
*********************************/

RPbdb_MessageSettingsController* RPbdb_SettingsController_messageSettingsController( RPbdb_SettingsController* settings_controller )	{

	if ( settings_controller->message_settings_controller == NULL )	{
		settings_controller->message_settings_controller = RPbdb_MessageSettingsController_new( settings_controller );
	}

	return settings_controller->message_settings_controller;

}

/*********************************
*  statusSettingsController  *
*********************************/
/*
RPbdb_StatusSettingsController* RPbdb_SettingsController_statusSettingsController( RPbdb_SettingsController* settings_controller )	{

	if ( settings_controller->status_settings_controller == NULL )	{
		settings_controller->status_settings_controller = RPbdb_StatusSettingsController_new( settings_controller );
	}

	return settings_controller->status_settings_controller;
}
*/
/*************************************
*  memoryPoolSettingsController  *
************************************/

RPbdb_MemoryPoolSettingsController* RPbdb_SettingsController_memoryPoolSettingsController( RPbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->memory_pool_settings_controller == NULL )	{
		settings_controller->memory_pool_settings_controller = RPbdb_MemoryPoolSettingsController_new( settings_controller );
	}
	
	return settings_controller->memory_pool_settings_controller;
}

/*************************************
*  transactionSettingsController  *
************************************/

RPbdb_TransactionSettingsController* RPbdb_SettingsController_transactionSettingsController( RPbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->transaction_settings_controller == NULL )	{
		settings_controller->transaction_settings_controller = RPbdb_TransactionSettingsController_new( settings_controller );
	}
	
	return settings_controller->transaction_settings_controller;
}

/*************************************
*  lockSettingsController  *
************************************/

RPbdb_LockSettingsController* RPbdb_SettingsController_lockSettingsController( RPbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->lock_settings_controller == NULL )	{
		settings_controller->lock_settings_controller = RPbdb_LockSettingsController_new( settings_controller );
	}
	
	return settings_controller->lock_settings_controller;
}

/*************************************
*  logSettingsController  *
************************************/

RPbdb_LogSettingsController* RPbdb_SettingsController_logSettingsController( RPbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->log_settings_controller == NULL )	{
		settings_controller->log_settings_controller = RPbdb_LogSettingsController_new( settings_controller );
	}
	
	return settings_controller->log_settings_controller;
}

/*************************************
*  replicationSettingsController  *
************************************/

RPbdb_ReplicationSettingsController* RPbdb_SettingsController_replicationSettingsController( RPbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->replication_settings_controller == NULL )	{
		settings_controller->replication_settings_controller = RPbdb_ReplicationSettingsController_new( settings_controller );
	}
	
	return settings_controller->replication_settings_controller;
}

/*************************************
*  databaseSettingsController  *
************************************/

RPbdb_DatabaseSettingsController* RPbdb_SettingsController_databaseSettingsController( RPbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->database_settings_controller == NULL )	{
		settings_controller->database_settings_controller = RPbdb_DatabaseSettingsController_new( settings_controller );
	}
	
	return settings_controller->database_settings_controller;
}

/*************************************
*  mutexSettingsController  *
************************************/

RPbdb_MutexSettingsController* RPbdb_SettingsController_mutexSettingsController( RPbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->mutex_settings_controller == NULL )	{
		settings_controller->mutex_settings_controller = RPbdb_MutexSettingsController_new( settings_controller );
	}
	
	return settings_controller->mutex_settings_controller;
}

/*************************************
*  cacheSettingsController  *
************************************/

RPbdb_EnvironmentCacheSettingsController* RPbdb_SettingsController_cacheSettingsController( RPbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->cache_settings_controller == NULL )	{
		settings_controller->cache_settings_controller = RPbdb_EnvironmentCacheSettingsController_new( settings_controller );
	}
	
	return settings_controller->cache_settings_controller;
}

/*************************************
*  DirectorySettingsController  *
************************************/

RPbdb_DirectorySettingsController* RPbdb_SettingsController_directorySettingsController( RPbdb_SettingsController* settings_controller )	{
	
	if ( settings_controller->directory_settings_controller == NULL )	{
		settings_controller->directory_settings_controller = RPbdb_DirectorySettingsController_new( settings_controller );
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
int RPbdb_SettingsController_internal_createFlags( RPbdb_SettingsController* settings_controller __attribute__((unused)) )	{
	//	Was RPC I think now none
	return FALSE;
}

/********************
*  eraseFlags  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_remove.html
int RPbdb_SettingsController_internal_eraseFlags( RPbdb_SettingsController* settings_controller )	{
		
	return RPbdb_FileSettingsController_forceRemoval( RPbdb_SettingsController_fileSettingsController( settings_controller ) )
			| RPbdb_FileSettingsController_permitEnvironmentBasedFileNaming( RPbdb_SettingsController_fileSettingsController( settings_controller ) ) 
			| RPbdb_FileSettingsController_useEnvironmentHomePermissionsForFileNaming( RPbdb_SettingsController_fileSettingsController( settings_controller ) );
}

/****************
*  openFlags  *
****************/

//	DB_INIT_LOG
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPbdb_SettingsController_internal_openFlags( RPbdb_SettingsController* settings_controller )	{
	
	RPbdb_DebugSettingsController*									debug_settings_controller										=	RPbdb_SettingsController_debugSettingsController( settings_controller );
	RPbdb_TransactionSettingsController*						transaction_settings_controller							=	RPbdb_SettingsController_transactionSettingsController( settings_controller );
	RPbdb_FileSettingsController*									file_settings_controller										=	RPbdb_SettingsController_fileSettingsController( settings_controller );
	RPbdb_MemoryPoolSettingsController*						memory_pool_settings_controller							=	RPbdb_SettingsController_memoryPoolSettingsController( settings_controller );
	RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller	=	RPbdb_MemoryPoolSettingsController_readWriteSettingsController( memory_pool_settings_controller );
	
	int	lock_settings_controller_on														=	RPbdb_LockSettingsController_on( RPbdb_SettingsController_lockSettingsController( settings_controller ) );
	int	memory_pool_settings_controller_on										=	RPbdb_MemoryPoolSettingsController_on( memory_pool_settings_controller );
	int	transaction_settings_controller_on										=	RPbdb_TransactionSettingsController_on( transaction_settings_controller );
	int	concurrent_data_store_locking_on											=	RPbdb_TransactionSettingsController_concurrentDataStoreLocking( transaction_settings_controller );
	int	log_settings_controller_on														=	RPbdb_LogSettingsController_on( RPbdb_SettingsController_logSettingsController( settings_controller ) );
	int	replication_settings_controller_on										=	RPbdb_ReplicationSettingsController_on( RPbdb_SettingsController_replicationSettingsController( settings_controller ) );

	int	create_if_necessary																		=	RPbdb_FileSettingsController_createIfNecessary( file_settings_controller );
	int	application_has_exclusive_access											=	RPbdb_MemoryPoolReadWriteSettingsController_applicationHasExclusiveAccess( memory_pool_read_write_settings_controller );
	int	run_normal_recovery_before_opening_environment				=	RPbdb_DebugSettingsController_runNormalRecoveryBeforeOpeningEnvironment(	debug_settings_controller );
	int	run_catastrophic_recovery_before_opening_environment	=	RPbdb_DebugSettingsController_runCatastrophicRecoveryBeforeOpeningEnvironment(	debug_settings_controller );
	int	register_for_recovery																	=	RPbdb_DebugSettingsController_registerForRecovery( debug_settings_controller );
	int	check_for_environment_failure_during_open							=	RPbdb_DebugSettingsController_checkForEnvironmentFailureDuringOpen( debug_settings_controller );
	int	permit_environment_based_file_naming									=	RPbdb_FileSettingsController_permitEnvironmentBasedFileNaming( file_settings_controller );
	int	use_environment_home_permissions_for_file_naming			=	RPbdb_FileSettingsController_useEnvironmentHomePermissionsForFileNaming( file_settings_controller );
	int	open_in_lockdown																			=	RPbdb_DebugSettingsController_openInLockdown( debug_settings_controller );
	
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
int RPbdb_SettingsController_internal_closeFlags( RPbdb_SettingsController* settings_controller __attribute__((unused)) )	{

	//	currently unused- set to 0
	return RPBDB_NO_FLAGS;
}

/****************
*  setFlags  * 
****************/

void RPbdb_SettingsController_internal_setFlags( RPbdb_SettingsController* settings_controller )	{

	RPbdb_Environment*	environment = settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		RPbdb_EnvironmentCacheSettingsController*					cache_settings_controller												=	RPbdb_SettingsController_cacheSettingsController( settings_controller );
		RPbdb_DatabaseSettingsController*									database_settings_controller										=	RPbdb_SettingsController_databaseSettingsController( settings_controller );
		RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
		RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
		RPbdb_DebugSettingsController*											debug_settings_controller												=	RPbdb_SettingsController_debugSettingsController( settings_controller );
		RPbdb_TransactionSettingsController*								transaction_settings_controller									=	RPbdb_SettingsController_transactionSettingsController( settings_controller );
		RPbdb_MemoryPoolSettingsController*								memory_pool_settings_controller									=	RPbdb_SettingsController_memoryPoolSettingsController( settings_controller );
		RPbdb_MemoryPoolReadWriteSettingsController*				memory_pool_read_write_settings_controller			=	RPbdb_MemoryPoolSettingsController_readWriteSettingsController( memory_pool_settings_controller );
		RPbdb_LockSettingsController*											lock_settings_controller												=	RPbdb_SettingsController_lockSettingsController( settings_controller );
		
		environment->wrapped_bdb_environment->set_flags(	environment->wrapped_bdb_environment,
																											RPbdb_EnvironmentCacheSettingsController_buffering( cache_settings_controller )
																											|	RPbdb_DatabaseRecordReadWriteSettingsController_syncPriorToWriteReturn( database_record_read_write_settings_controller )
																											|	RPbdb_DebugSettingsController_prohibitPanic( debug_settings_controller )
																											|	RPbdb_DebugSettingsController_panic( debug_settings_controller )
																											|	RPbdb_DebugSettingsController_yieldCPUForStressTest( debug_settings_controller )
																											|	RPbdb_LockSettingsController_prohibitLocking( lock_settings_controller )
																											|	RPbdb_LockSettingsController_timeoutReturnsDenyNotDeadlock( lock_settings_controller )
																											|	RPbdb_LockSettingsController_lockForEnvironmentNotDatabase( lock_settings_controller )
																											|	RPbdb_MemoryPoolSettingsController_memoryMapping( memory_pool_settings_controller )
																											|	RPbdb_MemoryPoolReadWriteSettingsController_pagefaultSharedRegions( memory_pool_read_write_settings_controller )
																											|	RPbdb_TransactionSettingsController_prohibitSyncOnWrite( transaction_settings_controller )
																											|	RPbdb_TransactionSettingsController_prohibitSyncOnCommit( transaction_settings_controller )
																											|	RPbdb_TransactionSettingsController_timeoutInMicrosecondsReturnsDenyNotDeadlock( transaction_settings_controller )
																											|	RPbdb_TransactionSettingsController_snapshotIsolation( transaction_settings_controller )
																											|	RPbdb_TransactionSettingsController_encloseAllActivityInTransaction( transaction_settings_controller )
																											|	RPbdb_TransactionSettingsController_environmentalSnapshotIsolation( transaction_settings_controller ),
																											1 );
	}	
}	


/****************
*  getFlags  * 
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_close.html
uint32_t RPbdb_SettingsController_internal_getFlags( RPbdb_SettingsController* settings_controller )	{

	//	why is parent_environment NULL?
	RPbdb_Environment*	environment = settings_controller->parent_environment;
	
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
RPbdb_SettingsController* RPbdb_SettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_SettingsController* settings_controller )	{

	RPbdb_SettingsController* settings_controller_copy	=	RPbdb_SettingsController_new( settings_controller->parent_environment );

	//	Instances and Pointers
	settings_controller_copy->shm_key	=	settings_controller->shm_key;

	return settings_controller_copy;
}

/********************
*  setVerbosity  * 
*******************/

void RPbdb_SettingsController_internal_setVerbosity( RPbdb_SettingsController* settings_controller )	{

	RPbdb_Environment*	environment = settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->set_verbose(	environment->wrapped_bdb_environment,
															RPbdb_ReplicationVerbositySettingsController_displayAllReplicationInformation( RPbdb_ReplicationSettingsController_verbositySettingsController( RPbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPbdb_ReplicationVerbositySettingsController_displayElectionInformation( RPbdb_ReplicationSettingsController_verbositySettingsController( RPbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPbdb_ReplicationVerbositySettingsController_displayReplicationMasterLeaseInformation( RPbdb_ReplicationSettingsController_verbositySettingsController( RPbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPbdb_ReplicationVerbositySettingsController_displayMiscProcessingInformation( RPbdb_ReplicationSettingsController_verbositySettingsController( RPbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPbdb_ReplicationVerbositySettingsController_displayMessageProcessingInformation( RPbdb_ReplicationSettingsController_verbositySettingsController( RPbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPbdb_ReplicationVerbositySettingsController_displayClientSynchronizationInformation( RPbdb_ReplicationSettingsController_verbositySettingsController( RPbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPbdb_ReplicationVerbositySettingsController_displayManagerConnectionFailureInformation( RPbdb_ReplicationSettingsController_verbositySettingsController( RPbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPbdb_ReplicationVerbositySettingsController_displayManagerMiscProcessing( RPbdb_ReplicationSettingsController_verbositySettingsController( RPbdb_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPbdb_DatabaseVerbositySettingsController_displayAdditionalInformationForDBRegisterFlag( RPbdb_DatabaseSettingsController_verbositySettingsController( RPbdb_SettingsController_databaseSettingsController( settings_controller ) ) )
															|	RPbdb_DebugVerbositySettingsController_displayAdditionalInformationDuringRecovery( RPbdb_DebugSettingsController_verbositySettingsController( RPbdb_SettingsController_debugSettingsController( settings_controller ) ) )
 															|	RPbdb_FileVerbositySettingsController_displayAdditionalInformationDuringOpenCloseRenameFileOperations( RPbdb_FileSettingsController_verbositySettingsController( RPbdb_SettingsController_fileSettingsController( settings_controller ) ) )
															|	RPbdb_FileVerbositySettingsController_displayAdditionalInformationDuringAllFileOperations( RPbdb_FileSettingsController_verbositySettingsController( RPbdb_SettingsController_fileSettingsController( settings_controller ) ) )
															|	RPbdb_LockDeadlockDetectorVerbositySettingsController_displayAdditionalInformationDuringDeadlockDetection( RPbdb_LockDeadlockDetectorSettingsController_verbositySettingsController( RPbdb_LockSettingsController_deadlockDetectorSettingsController( RPbdb_SettingsController_lockSettingsController( settings_controller ) ) ) )
															|	RPbdb_LockDeadlockDetectorVerbositySettingsController_displayWaitTableDuringDeadlockDetection( RPbdb_LockDeadlockDetectorSettingsController_verbositySettingsController( RPbdb_LockSettingsController_deadlockDetectorSettingsController( RPbdb_SettingsController_lockSettingsController( settings_controller ) ) ) ),
															1 );
	}	
}
	
