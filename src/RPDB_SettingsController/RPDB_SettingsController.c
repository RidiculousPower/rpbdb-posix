/*
 *		RPDB::SettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_SettingsController.h"

#include "RPDB_DebugSettingsController.h"
#include "RPDB_FileSettingsController.h"
#include "RPDB_ThreadSettingsController.h"
#include "RPDB_ErrorSettingsController.h"
#include "RPDB_MessageSettingsController.h"

#include "RPDB_MemoryPoolSettingsController.h"
#include "RPDB_TransactionSettingsController.h"
#include "RPDB_LockSettingsController.h"
#include "RPDB_LogSettingsController.h"
#include "RPDB_ReplicationSettingsController.h"
#include "RPDB_ReplicationVerbositySettingsController.h"
#include "RPDB_DatabaseVerbositySettingsController.h"
#include "RPDB_DebugVerbositySettingsController.h"
#include "RPDB_FileVerbositySettingsController.h"
#include "RPDB_LockDeadlockDetectorSettingsController.h"
#include "RPDB_LockDeadlockDetectorVerbositySettingsController.h"
#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_Environment.h"
#include "RPDB_MutexSettingsController.h"
#include "RPDB_DatabaseJoinSettingsController.h"

#include "RPDB_RuntimeStorageController.h"
#include "RPDB_EnvironmentCacheSettingsController.h"
#include "RPDB_DirectorySettingsController.h"

#include "RPDB_DatabaseRecordSettingsController.h"

#include "RPDB_MemoryPoolReadWriteSettingsController.h"

#include "RPDB_SettingsController_internal.h"


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_SettingsController* RPDB_SettingsController_new( RPDB_Environment* parent_environment )	{

	RPDB_SettingsController*		settings_controller = calloc( 1, sizeof( RPDB_SettingsController ) );

	settings_controller->parent_environment = parent_environment;
	
	return settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_SettingsController_free(	RPDB_SettingsController** settings_controller )	{

	if ( ( *settings_controller )->mutex_settings_controller != NULL )	{
		RPDB_MutexSettingsController_free( & ( ( *settings_controller )->mutex_settings_controller ) );
	}
	if ( ( *settings_controller )->error_settings_controller != NULL )	{
		RPDB_ErrorSettingsController_free( & ( ( *settings_controller )->error_settings_controller ) );
	}
	/*
	if ( ( *settings_controller )->status_settings_controller != NULL )	{
		RPDB_StatusSettingsController_free( & ( ( *settings_controller )->status_settings_controller ) );
	}
	*/
	if ( ( *settings_controller )->transaction_settings_controller != NULL )	{
		RPDB_TransactionSettingsController_free( & ( ( *settings_controller )->transaction_settings_controller ) );
	}
	if ( ( *settings_controller )->thread_settings_controller != NULL )	{
		RPDB_ThreadSettingsController_free( & ( ( *settings_controller )->thread_settings_controller ) );
	}
	if ( ( *settings_controller )->debug_settings_controller != NULL )	{
		RPDB_DebugSettingsController_free( & ( ( *settings_controller )->debug_settings_controller ) );
	}
	if ( ( *settings_controller )->message_settings_controller != NULL )	{
		RPDB_MessageSettingsController_free( & ( ( *settings_controller )->message_settings_controller ) );
	}
	if ( ( *settings_controller )->replication_settings_controller != NULL )	{
		RPDB_ReplicationSettingsController_free( & ( ( *settings_controller )->replication_settings_controller ) );
	}
	if ( ( *settings_controller )->cache_settings_controller != NULL )	{
		RPDB_EnvironmentCacheSettingsController_free( & ( ( *settings_controller )->cache_settings_controller ) );
	}
	if ( ( *settings_controller )->directory_settings_controller != NULL )	{
		RPDB_DirectorySettingsController_free( & ( ( *settings_controller )->directory_settings_controller ) );
	}
	if ( ( *settings_controller )->lock_settings_controller != NULL )	{
		RPDB_LockSettingsController_free( & ( ( *settings_controller )->lock_settings_controller ) );
	}
	if ( ( *settings_controller )->log_settings_controller != NULL )	{
		RPDB_LogSettingsController_free( & ( ( *settings_controller )->log_settings_controller ) );
	}
	if ( ( *settings_controller )->database_settings_controller != NULL )	{
		RPDB_DatabaseSettingsController_free( & ( ( *settings_controller )->database_settings_controller ) );
	}
	if ( ( *settings_controller )->memory_pool_settings_controller != NULL )	{
		RPDB_MemoryPoolSettingsController_free( & ( ( *settings_controller )->memory_pool_settings_controller ) );
	}
	if ( ( *settings_controller )->file_settings_controller != NULL )	{
		RPDB_FileSettingsController_free( & ( ( *settings_controller )->file_settings_controller ) );
	}

	free( *settings_controller );
	*settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_SettingsController_parentEnvironment(	RPDB_SettingsController* settings_controller )	{
	return settings_controller->parent_environment;
}

/*************
*  SHMKey  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_shm_key.html
//	For getting the SHMKey
long RPDB_SettingsController_SHMkey( RPDB_SettingsController* settings_controller )	{

	RPDB_Environment*			environment = settings_controller->parent_environment;
	
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
void RPDB_SettingsController_setSHMkey(	RPDB_SettingsController*	settings_controller, 
											long						shm_key )	{

	RPDB_Environment*			environment = settings_controller->parent_environment;
	
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

RPDB_DebugSettingsController* RPDB_SettingsController_debugSettingsController( RPDB_SettingsController* settings_controller )	{

	if ( settings_controller->debug_settings_controller == NULL )	{
		settings_controller->debug_settings_controller = RPDB_DebugSettingsController_new( settings_controller );
	}

	return settings_controller->debug_settings_controller;
}

/*****************************
*  fileSettingsController  *
*****************************/

RPDB_FileSettingsController* RPDB_SettingsController_fileSettingsController( RPDB_SettingsController* settings_controller )	{

	if ( settings_controller->file_settings_controller == NULL )	{
		settings_controller->file_settings_controller = RPDB_FileSettingsController_new( settings_controller );
	}

	return settings_controller->file_settings_controller;
}

/*********************************
*  threadSettingsController  *
*********************************/

RPDB_ThreadSettingsController* RPDB_SettingsController_threadSettingsController( RPDB_SettingsController* settings_controller )	{

	if ( settings_controller->thread_settings_controller == NULL )	{
		settings_controller->thread_settings_controller = RPDB_ThreadSettingsController_new( settings_controller );
	}

	return settings_controller->thread_settings_controller;

}

/*********************************
*  errorSettingsController  *
*********************************/

RPDB_ErrorSettingsController* RPDB_SettingsController_errorSettingsController( RPDB_SettingsController* settings_controller )	{

	if ( settings_controller->error_settings_controller == NULL )	{
		settings_controller->error_settings_controller = RPDB_ErrorSettingsController_new( settings_controller );
	}

	return settings_controller->error_settings_controller;

}

/*********************************
*  messageSettingsController  *
*********************************/

RPDB_MessageSettingsController* RPDB_SettingsController_messageSettingsController( RPDB_SettingsController* settings_controller )	{

	if ( settings_controller->message_settings_controller == NULL )	{
		settings_controller->message_settings_controller = RPDB_MessageSettingsController_new( settings_controller );
	}

	return settings_controller->message_settings_controller;

}

/*********************************
*  statusSettingsController  *
*********************************/
/*
RPDB_StatusSettingsController* RPDB_SettingsController_statusSettingsController( RPDB_SettingsController* settings_controller )	{

	if ( settings_controller->status_settings_controller == NULL )	{
		settings_controller->status_settings_controller = RPDB_StatusSettingsController_new( settings_controller );
	}

	return settings_controller->status_settings_controller;
}
*/
/*************************************
*  memoryPoolSettingsController  *
************************************/

RPDB_MemoryPoolSettingsController* RPDB_SettingsController_memoryPoolSettingsController( RPDB_SettingsController* settings_controller )	{
	
	if ( settings_controller->memory_pool_settings_controller == NULL )	{
		settings_controller->memory_pool_settings_controller = RPDB_MemoryPoolSettingsController_new( settings_controller );
	}
	
	return settings_controller->memory_pool_settings_controller;
}

/*************************************
*  transactionSettingsController  *
************************************/

RPDB_TransactionSettingsController* RPDB_SettingsController_transactionSettingsController( RPDB_SettingsController* settings_controller )	{
	
	if ( settings_controller->transaction_settings_controller == NULL )	{
		settings_controller->transaction_settings_controller = RPDB_TransactionSettingsController_new( settings_controller );
	}
	
	return settings_controller->transaction_settings_controller;
}

/*************************************
*  lockSettingsController  *
************************************/

RPDB_LockSettingsController* RPDB_SettingsController_lockSettingsController( RPDB_SettingsController* settings_controller )	{
	
	if ( settings_controller->lock_settings_controller == NULL )	{
		settings_controller->lock_settings_controller = RPDB_LockSettingsController_new( settings_controller );
	}
	
	return settings_controller->lock_settings_controller;
}

/*************************************
*  logSettingsController  *
************************************/

RPDB_LogSettingsController* RPDB_SettingsController_logSettingsController( RPDB_SettingsController* settings_controller )	{
	
	if ( settings_controller->log_settings_controller == NULL )	{
		settings_controller->log_settings_controller = RPDB_LogSettingsController_new( settings_controller );
	}
	
	return settings_controller->log_settings_controller;
}

/*************************************
*  replicationSettingsController  *
************************************/

RPDB_ReplicationSettingsController* RPDB_SettingsController_replicationSettingsController( RPDB_SettingsController* settings_controller )	{
	
	if ( settings_controller->replication_settings_controller == NULL )	{
		settings_controller->replication_settings_controller = RPDB_ReplicationSettingsController_new( settings_controller );
	}
	
	return settings_controller->replication_settings_controller;
}

/*************************************
*  databaseSettingsController  *
************************************/

RPDB_DatabaseSettingsController* RPDB_SettingsController_databaseSettingsController( RPDB_SettingsController* settings_controller )	{
	
	if ( settings_controller->database_settings_controller == NULL )	{
		settings_controller->database_settings_controller = RPDB_DatabaseSettingsController_new( settings_controller );
	}
	
	return settings_controller->database_settings_controller;
}

/*************************************
*  mutexSettingsController  *
************************************/

RPDB_MutexSettingsController* RPDB_SettingsController_mutexSettingsController( RPDB_SettingsController* settings_controller )	{
	
	if ( settings_controller->mutex_settings_controller == NULL )	{
		settings_controller->mutex_settings_controller = RPDB_MutexSettingsController_new( settings_controller );
	}
	
	return settings_controller->mutex_settings_controller;
}

/*************************************
*  cacheSettingsController  *
************************************/

RPDB_EnvironmentCacheSettingsController* RPDB_SettingsController_cacheSettingsController( RPDB_SettingsController* settings_controller )	{
	
	if ( settings_controller->cache_settings_controller == NULL )	{
		settings_controller->cache_settings_controller = RPDB_EnvironmentCacheSettingsController_new( settings_controller );
	}
	
	return settings_controller->cache_settings_controller;
}

/*************************************
*  DirectorySettingsController  *
************************************/

RPDB_DirectorySettingsController* RPDB_SettingsController_directorySettingsController( RPDB_SettingsController* settings_controller )	{
	
	if ( settings_controller->directory_settings_controller == NULL )	{
		settings_controller->directory_settings_controller = RPDB_DirectorySettingsController_new( settings_controller );
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
int RPDB_SettingsController_internal_createFlags( RPDB_SettingsController* settings_controller __attribute__((unused)) )	{
	//	Was RPC I think now none
	return FALSE;
}

/********************
*  eraseFlags  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_remove.html
int RPDB_SettingsController_internal_eraseFlags( RPDB_SettingsController* settings_controller )	{
		
	return RPDB_FileSettingsController_forceRemoval( RPDB_SettingsController_fileSettingsController( settings_controller ) )
			| RPDB_FileSettingsController_permitEnvironmentBasedFileNaming( RPDB_SettingsController_fileSettingsController( settings_controller ) ) 
			| RPDB_FileSettingsController_useEnvironmentHomePermissionsForFileNaming( RPDB_SettingsController_fileSettingsController( settings_controller ) );
}

/****************
*  openFlags  *
****************/

//	DB_INIT_LOG
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPDB_SettingsController_internal_openFlags( RPDB_SettingsController* settings_controller )	{
	
	RPDB_DebugSettingsController*					debug_settings_controller						=	RPDB_SettingsController_debugSettingsController( settings_controller );
	RPDB_TransactionSettingsController*		transaction_settings_controller			=	RPDB_SettingsController_transactionSettingsController( settings_controller );
	RPDB_FileSettingsController*					file_settings_controller						=	RPDB_SettingsController_fileSettingsController( settings_controller );
	RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller			=	RPDB_SettingsController_memoryPoolSettingsController( settings_controller );
	
	int	lock_settings_controller_on														=	RPDB_LockSettingsController_on( RPDB_SettingsController_lockSettingsController( settings_controller ) );
	int	memory_pool_settings_controller_on										=	RPDB_MemoryPoolSettingsController_on( memory_pool_settings_controller );
	int	transaction_settings_controller_on										=	RPDB_TransactionSettingsController_on( transaction_settings_controller );
	int	concurrent_data_store_locking_on											=	RPDB_TransactionSettingsController_concurrentDataStoreLocking( transaction_settings_controller );
	int	log_settings_controller_on														=	RPDB_LogSettingsController_on( RPDB_SettingsController_logSettingsController( settings_controller ) );
	int	replication_settings_controller_on										=	RPDB_ReplicationSettingsController_on( RPDB_SettingsController_replicationSettingsController( settings_controller ) );

	int	create_if_necessary																		=	RPDB_FileSettingsController_createIfNecessary( file_settings_controller );
	int	application_has_exclusive_access											=	RPDB_MemoryPoolSettingsController_applicationHasExclusiveAccess( memory_pool_settings_controller );
	int	run_normal_recovery_before_opening_environment				=	RPDB_DebugSettingsController_runNormalRecoveryBeforeOpeningEnvironment(	debug_settings_controller );
	int	run_catastrophic_recovery_before_opening_environment	=	RPDB_DebugSettingsController_runCatastrophicRecoveryBeforeOpeningEnvironment(	debug_settings_controller );
	int	register_for_recovery																	=	RPDB_DebugSettingsController_registerForRecovery( debug_settings_controller );
	int	check_for_environment_failure_during_open							=	RPDB_DebugSettingsController_checkForEnvironmentFailureDuringOpen( debug_settings_controller );
	int	permit_environment_based_file_naming									=	RPDB_FileSettingsController_permitEnvironmentBasedFileNaming( file_settings_controller );
	int	use_environment_home_permissions_for_file_naming			=	RPDB_FileSettingsController_useEnvironmentHomePermissionsForFileNaming( file_settings_controller );
	int	open_in_lockdown																			=	RPDB_DebugSettingsController_openInLockdown( debug_settings_controller );
	
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
int RPDB_SettingsController_internal_closeFlags( RPDB_SettingsController* settings_controller __attribute__((unused)) )	{

	//	currently unused- set to 0
	return RPDB_NO_FLAGS;
}

/****************
*  setFlags  * 
****************/

void RPDB_SettingsController_internal_setFlags( RPDB_SettingsController* settings_controller )	{

	RPDB_Environment*	environment = settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->set_flags(	environment->wrapped_bdb_environment,
															RPDB_EnvironmentCacheSettingsController_buffering( RPDB_SettingsController_cacheSettingsController( settings_controller ) )
															|	RPDB_DatabaseRecordSettingsController_syncPriorToWriteReturn( RPDB_DatabaseSettingsController_recordSettingsController( RPDB_SettingsController_databaseSettingsController( settings_controller ) ) )
															|	RPDB_DebugSettingsController_prohibitPanic( RPDB_SettingsController_debugSettingsController( settings_controller ) )
															|	RPDB_DebugSettingsController_panic( RPDB_SettingsController_debugSettingsController( settings_controller ) )
															|	RPDB_DebugSettingsController_yieldCPUForStressTest( RPDB_SettingsController_debugSettingsController( settings_controller ) )
															|	RPDB_LockSettingsController_prohibitLocking( RPDB_SettingsController_lockSettingsController( settings_controller ) )
															|	RPDB_LockSettingsController_timeoutReturnsReturnDenyNotDeadlock( RPDB_SettingsController_lockSettingsController( settings_controller ) )
															|	RPDB_LockSettingsController_lockForEnvironmentNotDatabase( RPDB_SettingsController_lockSettingsController( settings_controller ) )
															|	RPDB_MemoryPoolSettingsController_memoryMapping( RPDB_SettingsController_memoryPoolSettingsController( settings_controller ) )
															|	RPDB_MemoryPoolReadWriteSettingsController_pagefaultSharedRegions( RPDB_MemoryPoolSettingsController_readWriteSettingsController( RPDB_SettingsController_memoryPoolSettingsController( settings_controller ) ) )
															|	RPDB_TransactionSettingsController_prohibitSyncOnWrite( RPDB_SettingsController_transactionSettingsController( settings_controller ) )
															|	RPDB_TransactionSettingsController_prohibitSyncOnCommit( RPDB_SettingsController_transactionSettingsController( settings_controller ) )
															|	RPDB_TransactionSettingsController_timeoutInMicrosecondsReturnsDenyNotDeadlock( RPDB_SettingsController_transactionSettingsController( settings_controller ) )
															|	RPDB_TransactionSettingsController_snapshotIsolation( RPDB_SettingsController_transactionSettingsController( settings_controller ) )
															|	RPDB_TransactionSettingsController_encloseAllActivityInTransaction( RPDB_SettingsController_transactionSettingsController( settings_controller ) )
															|	RPDB_TransactionSettingsController_environmentalSnapshotIsolation( RPDB_SettingsController_transactionSettingsController( settings_controller ) ),
															1 );
	}	
}	


/****************
*  getFlags  * 
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_close.html
uint32_t RPDB_SettingsController_internal_getFlags( RPDB_SettingsController* settings_controller )	{

	//	why is parent_environment NULL?
	RPDB_Environment*	environment = settings_controller->parent_environment;
	
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
RPDB_SettingsController* RPDB_SettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_SettingsController* settings_controller )	{

	RPDB_SettingsController* settings_controller_copy	=	RPDB_SettingsController_new( settings_controller->parent_environment );

	//	Instances and Pointers
	settings_controller_copy->shm_key	=	settings_controller->shm_key;

	return settings_controller_copy;
}

/********************
*  setVerbosity  * 
*******************/

void RPDB_SettingsController_internal_setVerbosity( RPDB_SettingsController* settings_controller )	{

	RPDB_Environment*	environment = settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		
		environment->wrapped_bdb_environment->set_verbose(	environment->wrapped_bdb_environment,
															RPDB_ReplicationVerbositySettingsController_displayAllReplicationInformation( RPDB_ReplicationSettingsController_verbositySettingsController( RPDB_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPDB_ReplicationVerbositySettingsController_displayElectionInformation( RPDB_ReplicationSettingsController_verbositySettingsController( RPDB_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPDB_ReplicationVerbositySettingsController_displayReplicationMasterLeaseInformation( RPDB_ReplicationSettingsController_verbositySettingsController( RPDB_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPDB_ReplicationVerbositySettingsController_displayMiscProcessingInformation( RPDB_ReplicationSettingsController_verbositySettingsController( RPDB_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPDB_ReplicationVerbositySettingsController_displayMessageProcessingInformation( RPDB_ReplicationSettingsController_verbositySettingsController( RPDB_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPDB_ReplicationVerbositySettingsController_displayClientSynchronizationInformation( RPDB_ReplicationSettingsController_verbositySettingsController( RPDB_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPDB_ReplicationVerbositySettingsController_displayManagerConnectionFailureInformation( RPDB_ReplicationSettingsController_verbositySettingsController( RPDB_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPDB_ReplicationVerbositySettingsController_displayManagerMiscProcessing( RPDB_ReplicationSettingsController_verbositySettingsController( RPDB_SettingsController_replicationSettingsController( settings_controller ) ) )
															|	RPDB_DatabaseVerbositySettingsController_displayAdditionalInformationForDBRegisterFlag( RPDB_DatabaseSettingsController_verbositySettingsController( RPDB_SettingsController_databaseSettingsController( settings_controller ) ) )
															|	RPDB_DebugVerbositySettingsController_displayAdditionalInformationDuringRecovery( RPDB_DebugSettingsController_verbositySettingsController( RPDB_SettingsController_debugSettingsController( settings_controller ) ) )
 															|	RPDB_FileVerbositySettingsController_displayAdditionalInformationDuringOpenCloseRenameFileOperations( RPDB_FileSettingsController_verbositySettingsController( RPDB_SettingsController_fileSettingsController( settings_controller ) ) )
															|	RPDB_FileVerbositySettingsController_displayAdditionalInformationDuringAllFileOperations( RPDB_FileSettingsController_verbositySettingsController( RPDB_SettingsController_fileSettingsController( settings_controller ) ) )
															|	RPDB_LockDeadlockDetectorVerbositySettingsController_displayAdditionalInformationDuringDeadlockDetection( RPDB_LockDeadlockDetectorSettingsController_verbositySettingsController( RPDB_LockSettingsController_deadlockDetectorSettingsController( RPDB_SettingsController_lockSettingsController( settings_controller ) ) ) )
															|	RPDB_LockDeadlockDetectorVerbositySettingsController_displayWaitTableDuringDeadlockDetection( RPDB_LockDeadlockDetectorSettingsController_verbositySettingsController( RPDB_LockSettingsController_deadlockDetectorSettingsController( RPDB_SettingsController_lockSettingsController( settings_controller ) ) ) ),
															1 );
	}	
}
	
