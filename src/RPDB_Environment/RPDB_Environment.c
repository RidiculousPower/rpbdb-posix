/*
 *		RPDB
 *
 *		On the C API		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/frame.html
 *
 *			Getting Started:			http://www.oracle.com/technology/documentation/berkeley-db/db/gsg/C/index.html
 *			Transaction Processing:		http://www.oracle.com/technology/documentation/berkeley-db/db/gsg_txn/C/index.html
 *			Replication:				http://www.oracle.com/technology/documentation/berkeley-db/db/gsg_db_rep/C/index.html
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_Environment.h"
#include "RPDB_Environment_internal.h"

#include "RPDB_DatabaseController.h"
#include "RPDB_Database.h"
#include "RPDB_DatabaseJoinController.h"

#include "RPDB_ErrorController.h"
#include "RPDB_LockController.h"
#include "RPDB_LogController.h"
#include "RPDB_MemoryPoolController.h"
#include "RPDB_MutexController.h"
#include "RPDB_ReplicationController.h"
#include "RPDB_TransactionController.h"

#include "RPDB_SettingsController.h"

#include "RPDB_DatabaseTypeSettingsController.h"
#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_DirectorySettingsController.h"
#include "RPDB_DebugSettingsController.h"
#include "RPDB_ErrorSettingsController.h"
#include "RPDB_FileSettingsController.h"
#include "RPDB_MemoryPoolSettingsController.h"
#include "RPDB_MessageSettingsController.h"
#include "RPDB_LockSettingsController.h"
#include "RPDB_LockDeadlockDetectorSettingsController.h"
#include "RPDB_LogSettingsController.h"
#include "RPDB_TransactionSettingsController.h"
#include "RPDB_ThreadSettingsController.h"

#include "RPDB_SettingsController_internal.h"
#include "RPDB_LockDeadlockDetectorSettingsController_internal.h"
#include "RPDB_LogSettingsController_internal.h"

#include "RPDB_RuntimeStorageController.h"
#include "RPDB_RuntimeStorageController_internal.h"

#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/

RPDB_Environment* RPDB_Environment_new(	char* environment_home_directory )	{

	RPDB_Environment*	environment	=	calloc( 1, sizeof( RPDB_Environment ) );

	environment->is_open			=	FALSE;

	//	If no directory is specified we use current working directory
	if ( environment_home_directory == NULL )	{
		environment->directory		=	DEFAULT_ENVIRONMENT_HOME_DIRECTORY;
	}
	else	{
		environment->directory			=	environment_home_directory;
	}
	
	RPDB_Environment_initDefaults( environment );
	
	return environment;
}

/*********
*  free  *
*********/

void RPDB_Environment_free( RPDB_Environment** environment )	{

	//	close and free transaction controller
	if ( ( *environment )->transaction_controller != NULL )	{
		
		//	If we have a transaction controller we need to close all databases so we can commit the transaction
		//	This is necessary because the databases were opened inside the transaction
		if ( ( *environment )->database_controller != NULL )	{
			RPDB_DatabaseController_closeAllDatabases( ( *environment )->database_controller );
		}
		
		RPDB_TransactionController_free( & ( ( *environment )->transaction_controller ) );
	}
	
	//	if the environment is open, close it
	if ( RPDB_Environment_isOpen( *environment ) )	{
		RPDB_Environment_close( *environment );
	}
	
	//	the order in which calls happen to free child objects is important

	//	free database controller and databases (close if necessary)
	if ( ( *environment )->database_controller != NULL )	{
		RPDB_DatabaseController_free( & ( ( *environment )->database_controller ) );
	}

	//	free error controller
	if ( ( *environment )->error_controller != NULL )	{
		RPDB_ErrorController_free( & ( ( *environment )->error_controller ) );
	}

	//	free memory pool controller
	if ( ( *environment )->memory_pool_controller != NULL )	{
		RPDB_MemoryPoolController_free( & ( ( *environment )->memory_pool_controller ) );
	}
	
	//	free log controller and any open logs
	if ( ( *environment )->log_controller != NULL )	{
		RPDB_LogController_free( & ( ( *environment )->log_controller ) );
	}
	
	//	free replication controller
	if ( ( *environment )->replication_controller != NULL )	{
		RPDB_ReplicationController_free( & ( ( *environment )->replication_controller ) );
	}
	
	//	free mutex controller and mutexes
	if ( ( *environment )->mutex_controller != NULL )	{
		RPDB_MutexController_free( & ( ( *environment )->mutex_controller ) );
	}
	
	//	free lock controller
	if ( ( *environment )->lock_controller != NULL )	{
		RPDB_LockController_free( & ( ( *environment )->lock_controller ) );
	}
	
	//	free all environmental settings controllers
	if ( ( *environment )->settings_controller != NULL )	{
		RPDB_SettingsController_free( & ( ( *environment )->settings_controller ) );
	}

	//	home directory and name are both str_dup creations, so we need to free
	if ( ( *environment )->directory != NULL )	{
		free( ( *environment )->directory );
		( *environment )->directory = NULL;
	}
	if ( ( *environment )->name != NULL )	{
		free( ( *environment )->name );
		( *environment )->name = NULL;
	}
	

	//	and free self
	
	free( *environment );
	*environment	=	NULL;
	environment		=	NULL;
	
}

/*****************
*  initDefaults  *
*****************/

void RPDB_Environment_initDefaults( RPDB_Environment* environment )	{

	RPDB_SettingsController*							settings_controller								=	RPDB_Environment_settingsController( environment );
	RPDB_DebugSettingsController*					debug_settings_controller					=	RPDB_SettingsController_debugSettingsController( settings_controller );
	RPDB_TransactionSettingsController*		transaction_settings_controller		=	RPDB_SettingsController_transactionSettingsController( settings_controller );
	RPDB_LogSettingsController*						log_settings_controller						=	RPDB_SettingsController_logSettingsController( settings_controller );
	RPDB_LockSettingsController*					lock_settings_controller					=	RPDB_SettingsController_lockSettingsController( settings_controller );
	RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller		=	RPDB_SettingsController_memoryPoolSettingsController( settings_controller );
	RPDB_DirectorySettingsController*			directory_settings_controller			=	RPDB_SettingsController_directorySettingsController( settings_controller );
	RPDB_FileSettingsController*					file_settings_controller					=	RPDB_SettingsController_fileSettingsController( settings_controller );
	RPDB_ThreadSettingsController*				thread_settings_controller				=	RPDB_SettingsController_threadSettingsController( settings_controller );
	RPDB_DatabaseSettingsController*			database_settings_controller			=	RPDB_SettingsController_databaseSettingsController( settings_controller );
	RPDB_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPDB_DatabaseSettingsController_typeSettingsController( database_settings_controller );

	#ifdef RPDB_DEFAULT_MEMORY_POOL_ON
		//	And make sure we actually have a memory pool
		RPDB_MemoryPoolSettingsController_turnOn( memory_pool_settings_controller );
	#endif

	#ifdef RPDB_DEFAULT_TRANSACTION_DATA_STORE_ON
	

		RPDB_TransactionSettingsController_turnOn( transaction_settings_controller );
		RPDB_LogSettingsController_turnOn( log_settings_controller );
		RPDB_LockSettingsController_turnOn( lock_settings_controller );

		//	Enable registration, checking for environmental failure, normal recovery
		//	DB_RECOVER
		RPDB_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOn( debug_settings_controller );

		//	DB_REGISTER, DB_ENV_FAILCHK
//		RPDB_DebugSettingsController_turnRegisterForRecoveryOn( debug_settings_controller );
//		RPDB_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOn( debug_settings_controller );
		
	#else
	
		#ifdef RPDB_DEFAULT_CONCURRENT_DATA_STORE_ON
			RPDB_TransactionSettingsController_turnConcurrentDataStoreLockingOn( transaction_settings_controller );
		#endif
	
	#endif

	#ifdef RPDB_DEFAULT_SET_ENVIRONMENT_PATH_ON

		//	Set our environment home as our database directory
		if ( environment->directory != NULL )	{
			RPDB_DirectorySettingsController_addDataDirectory(	directory_settings_controller,
																													environment->directory );
		}

	#endif
															
	#ifdef RPDB_DEFAULT_CREATE_IF_NECESSARY
		RPDB_FileSettingsController_turnCreateIfNecessaryOn( file_settings_controller );
	#endif
	
	#ifdef RPDB_DEFAULT_TO_BTREE
		//	Unless otherwise specified, all of our runtime storage will be hash - set the environmental default
		RPDB_DatabaseTypeSettingsController_setTypeToBTree( database_type_settings_controller );
	#endif
	
	#ifdef RPDB_MULTIPLE_ACCESS
		RPDB_ThreadSettingsController_turnOn( thread_settings_controller );
	#endif
	
}

/*************************
*  initForMemoryStorage  *
*************************/

RPDB_Environment* RPDB_Environment_initForStorageInMemory( RPDB_Environment* environment )	{
	
	RPDB_SettingsController*							settings_controller								=	RPDB_Environment_settingsController( environment );
	RPDB_MemoryPoolSettingsController*		memory_pool_settings_controller		=	RPDB_SettingsController_memoryPoolSettingsController( settings_controller );
	RPDB_LogSettingsController*						log_settings_controller						=	RPDB_SettingsController_logSettingsController( settings_controller );

	//	Don't allow writes to disk - use application memory for storage
	RPDB_MemoryPoolSettingsController_turnApplicationHasExclusiveAccessOn(	RPDB_SettingsController_memoryPoolSettingsController( settings_controller ) );

	//	Don't use a temporary backing file for flushing memory	
	RPDB_MemoryPoolSettingsController_turnDoNotWriteToTemporaryBackingFileOn(	memory_pool_settings_controller );
		
	//	If log in memory is on, log in memory; otherwise, turn logging system off
	if ( ! RPDB_LogSettingsController_logInMemory( log_settings_controller ) )	{

		//	If we're not logging in memory we don't want to log at all (because it would write to disk)
		RPDB_LogSettingsController_turnOff(	log_settings_controller );
	}
	
	return environment;
}

/*******************************************************************************************************************************************************************************************
																		State
*******************************************************************************************************************************************************************************************/

/*********
*  open  *
*********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
//	This should be implied by the attempt to use a database
RPDB_Environment* RPDB_Environment_open( RPDB_Environment* environment )	{

	if ( ! RPDB_Environment_isOpen( environment ) )	{
					
		RPDB_Environment_internal_initWrappedEnvironment( environment, FALSE );
						
		RPDB_Environment_internal_openWithoutRuntimeStorage( environment );

		RPDB_RuntimeStorageController_internal_storeEnvironmentForBDBEnvironment(	RPDB_RuntimeStorageController_sharedInstance(),
																																							environment );
		environment->is_open	=	TRUE;
	}
		
	//	return environment
	return environment;
}

/***********
*  isOpen  *
***********/
	
BOOL RPDB_Environment_isOpen( RPDB_Environment* environment )	{
	return environment->is_open;
}

/******************
*  homeDirectory  *
******************/

char* RPDB_Environment_homeDirectory( RPDB_Environment* environment )	{
	return environment->directory;
}

/**********
*  close  *
**********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_close.html
RPDB_Environment* RPDB_Environment_close( RPDB_Environment* environment )	{

	if ( environment->is_open )	{
	
		//	remove entry in runtime storage for this environment - we do this before closing so we have the bdb address, which is the key
		RPDB_RuntimeStorageController_internal_removeStoredEnvironment(	RPDB_RuntimeStorageController_sharedInstance(),
																																		environment );
		
		//	Tell all locks to release
		if ( environment->lock_controller != NULL )	{
			RPDB_LockController_closeAllLocks( environment->lock_controller );
		}
		
		if ( environment->mutex_controller != NULL )	{
			//	Tell all mutex to release
			RPDB_MutexController_closeAllMutexes( environment->mutex_controller );
		}
			
		if ( environment->transaction_controller != NULL )	{
			RPDB_TransactionController_commitAllTransactions( environment->transaction_controller );
		}
		
		if ( environment->database_controller != NULL )	{
			//	Tell all databases to close (and to name their subsystems)
			RPDB_DatabaseController_closeAllDatabases( environment->database_controller );
		}
		
		//	Close environment
		environment->wrapped_bdb_environment->close(	environment->wrapped_bdb_environment, 
														RPDB_SettingsController_internal_closeFlags( RPDB_Environment_settingsController( environment ) ) );

		//	BDB environment is not re-entrant - nullify environment
		environment->wrapped_bdb_environment = NULL;
		
		//	record that environment is closed
		environment->is_open = FALSE;
	}

	return environment;
}

/**********
*  erase  *
**********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_remove.html
RPDB_Environment* RPDB_Environment_erase( RPDB_Environment* environment )	{
	
	int connection_error	= 0;
	
	//	An environment that has been opened should not be used to erase
	//	We create a new wrapped environment instance to deal with it
	if ( RPDB_Environment_isOpen( environment ) )	{
		RPDB_Environment_close( environment );
	}

	//	whether or not our environment was opened we need a new environment instance to use for erase
	if ( ( connection_error = db_env_create(	&( environment->wrapped_bdb_environment ), 
																						RPDB_SettingsController_internal_createFlags(	RPDB_Environment_settingsController( environment ) ) ) ) ) {
		
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
																									connection_error, 
																									"RPDB_Environment_erase" );
	}		
	
	int	flags	=	RPDB_SettingsController_internal_eraseFlags( RPDB_Environment_settingsController( environment ) );
	connection_error	= 0;
	if ( ( connection_error = environment->wrapped_bdb_environment->remove(	environment->wrapped_bdb_environment, 
																			environment->directory,
																			flags ) ) ) {
																					
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ), 
																									connection_error, 
																									"RPDB_Environment_erase" );
	}
	
	//	After DB_ENV->remove has been called, regardless of its return, the Berkeley DB environment name may not be accessed again.
	//	A DB_ENV name that has already been used to open an environment should not be used to call the DB_ENV->remove method; 
	//	a new DB_ENV name should be created for that purpose.
	//	We name this by setting the pointer to NULL so a new DB_ENV name will be created if we try. 
	environment->wrapped_bdb_environment = NULL;
	
	return environment;
}

/*******************************
*  checkForEnvironmentFailure  *
*******************************/

void RPDB_Environment_checkForEnvironmentFailure( RPDB_Environment* environment )	{
	environment->wrapped_bdb_environment->failchk(	environment->wrapped_bdb_environment,
																									RPDB_NO_FLAGS );
}	

/***********
*  name  *
***********/

char* RPDB_Environment_name( RPDB_Environment* environment )	{
	return environment->name;
}
	
/**************
*  setName  *
**************/

void RPDB_Environment_setName(	RPDB_Environment*		environment,
																char*								name )	{
	environment->name	=	strdup( name );
}
	
/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/********************
*  errorController  *
********************/

RPDB_ErrorController* RPDB_Environment_errorController( RPDB_Environment* environment )	{

	if (	! environment 
		||	! environment->error_controller )	{
		return RPDB_ErrorController_new( environment );
	}
	
	return environment->error_controller;
}

/***********************
*  databaseController  *
***********************/

RPDB_DatabaseController* RPDB_Environment_databaseController( RPDB_Environment* environment )	{

	if ( environment->database_controller == NULL )	{
		environment->database_controller = RPDB_DatabaseController_new( environment );
	}
	
	return environment->database_controller;
}

/*******************
*  lockController  *
*******************/

RPDB_LockController* RPDB_Environment_lockController( RPDB_Environment* environment )	{

	if ( ! environment->lock_controller )	{
		environment->lock_controller = RPDB_LockController_new( environment );
	}
	
	return environment->lock_controller;	
}

/*************************
*  memoryPoolController  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get_mpf.html
RPDB_MemoryPoolController* RPDB_Environment_memoryPoolController( RPDB_Environment* environment )	{

	if ( ! environment->memory_pool_controller )	{
		environment->memory_pool_controller = RPDB_MemoryPoolController_new( environment );
	}
	
	return environment->memory_pool_controller;		
}

/********************
*  mutexController  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_unlock.html
RPDB_MutexController* RPDB_Environment_mutexController( RPDB_Environment* environment )	{

	if ( ! environment->mutex_controller )	{
		environment->mutex_controller = RPDB_MutexController_new( environment );
	}
	
	return environment->mutex_controller;			
}

/**************************
*  replicationController  *
**************************/

RPDB_ReplicationController* 	RPDB_Environment_replicationController( RPDB_Environment* environment )	{

	if ( ! environment->replication_controller )	{
		environment->replication_controller = RPDB_ReplicationController_new( environment );
	}
	
	return environment->replication_controller;	
}

/*********************
*  objectController  *
*********************/
/*
RPDB_ObjectController* RPDB_Environment_objectController( RPDB_Environment* environment )	{

	if ( ! environment->object_controller )	{
		environment->object_controller = RPDB_ObjectController_new( environment );
	}
	
	return environment->object_controller;	
}
*/

/*************************
*  controllerController  *
*************************/
/*
RPDB_Controller* RPDB_Environment_controllerController( RPDB_Environment* environment )	{

	if ( ! environment->controller_controller )	{
		environment->controller_controller = RPDB_controllerController_new( environment );
	}
	
	return environment->controller_controller;	
}
*/

/******************
*  logController  *
******************/

RPDB_LogController* RPDB_Environment_logController( RPDB_Environment* environment )	{

	if ( ! environment->log_controller )	{
		environment->log_controller = RPDB_LogController_new( environment );
	}
	
	return environment->log_controller;		
}

/*********************
*  statusController  *
*********************/
/*
RPDB_StatusController* RPDB_Environment_statusController( RPDB_Environment* environment )	{

	if ( ! environment->status_controller )	{
		environment->status_controller = RPDB_StatusController_new( environment );
	}
	
	return environment->status_controller;			
}
*/

/**************************
*  transactionController  *
**************************/

RPDB_TransactionController* RPDB_Environment_transactionController( RPDB_Environment* environment )	{

	if ( ! environment->transaction_controller )	{
		environment->transaction_controller = RPDB_TransactionController_new( environment );
	}
	
	return environment->transaction_controller;		
}

/***********************
*  settingsController  *
***********************/

RPDB_SettingsController* RPDB_Environment_settingsController( RPDB_Environment* environment )	{

	if ( environment->settings_controller == NULL )	{
		environment->settings_controller = RPDB_SettingsController_new( environment );
	}
	
	return environment->settings_controller;		
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
														Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/******************************
*  openWithoutRuntimeStorage  *
******************************/

void RPDB_Environment_internal_openWithoutRuntimeStorage( RPDB_Environment* environment )	{

	int						connection_error	= 0;
	
	int	flags	=	RPDB_SettingsController_internal_openFlags( RPDB_Environment_settingsController( environment ) );
	int	mode	=	RPDB_FileSettingsController_fileCreationMode( RPDB_SettingsController_fileSettingsController( RPDB_Environment_settingsController( environment ) ) );
	
	//	Create if necessary only creates the db; we have to create the directory if it doesn't yet exist
	if ( RPDB_FileSettingsController_createIfNecessary( RPDB_SettingsController_fileSettingsController( RPDB_Environment_settingsController( environment ) ) )	 ){
		
		//	check whether the directory exists
		if( access( environment->directory, F_OK ) == -1 ) {		
			//	if it doesn't, create it
			mkdir(	environment->directory, S_IRWXU );
		}		
	}
	
	//	Open the environment itself (regardless of whether we had to create it on this call to RPDB_open)
	if ( ( connection_error = environment->wrapped_bdb_environment->open(	environment->wrapped_bdb_environment, 
																			environment->directory, 
																			flags,
																			mode ) ) ) {
																			
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ), 
														connection_error, 
														"RPDB_Environment_internal_openWithoutRuntimeStorage" );
	}
	
	//	record that this environment has been opened
	environment->is_open = TRUE;
	
}

/***************************
*  initWrappedEnvironment  *
***************************/

void RPDB_Environment_internal_initWrappedEnvironment(	RPDB_Environment*		environment, 
																												BOOL								for_runtime_environment )	{
	
	//	if we don't have a wrapped_bdb_environment then we need to create one before we can open it
	//	FIX - if we created a new wrapped_bdb_environment then we need to make sure any settings
	//	are applied to the new one so that its creation is transparent.
	//	FIX - this probably means moving all settings to two layers, one where the RPDB instance is set
	//	and one where the bdb instance is set (right before it opens)
	
	//	create bdb DB_ENV instance
	int	connection_error	=	RP_NO_ERROR;
	if ( ( connection_error = db_env_create(	&( environment->wrapped_bdb_environment ), 
																						RPDB_SettingsController_internal_createFlags(	RPDB_Environment_settingsController( environment ) ) ) ) ) {
		
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( environment ),
														connection_error, 
														"RPDB_Environment_internal_initWrappedEnvironment" );
	}
	
	//	now we have to set the wrapped bdb environment with all of our settings from our rpdb environment wrapper
	if (	for_runtime_environment == FALSE
		&&	environment->settings_controller != NULL )	{
	
		RPDB_SettingsController*	settings_controller	=	environment->settings_controller;
	
		//	DB_ENV->set_flags()
		RPDB_SettingsController_internal_setFlags( settings_controller );
		
		//	DB_ENV->set_verbose()
		RPDB_SettingsController_internal_setVerbosity( settings_controller );

		//	DB_ENV->set_shm_key()
		if ( settings_controller->shm_key )	{
			RPDB_SettingsController_setSHMkey(	settings_controller,
												settings_controller->shm_key );
		}
/*
		if ( settings_controller->debug_settings_controller != NULL )	{

			RPDB_DebugSettingsController*	debug_settings_controller	=	settings_controller->debug_settings_controller;
			
		}
		*/
		if ( settings_controller->directory_settings_controller != NULL )	{

			RPDB_DirectorySettingsController*	directory_settings_controller	=	settings_controller->directory_settings_controller;
			
			//	DB_ENV->add_data_dir()
			if ( directory_settings_controller->directories )	{
				RPDB_Directory**	this_directory	=	NULL;
				this_directory	=	& ( directory_settings_controller->directories );
				do	{
					environment->wrapped_bdb_environment->add_data_dir(	environment->wrapped_bdb_environment, 
																		( *this_directory )->path );					
				}	while (		this_directory = & ( ( *this_directory)->next ), 
								*this_directory != NULL );				
			}
			
			//	DB_ENV->set_create_dir()
			if ( environment->create_directory )	{
				RPDB_DirectorySettingsController_setCreateDirectory(	directory_settings_controller,
																		environment->create_directory );
			}
		}
		
		if ( settings_controller->error_settings_controller != NULL )	{
		
			RPDB_ErrorSettingsController*	error_settings_controller	=	settings_controller->error_settings_controller;

			//	DB_ENV->set_errfile()
			if ( error_settings_controller->file )	{
				RPDB_ErrorSettingsController_setFile(	error_settings_controller,
														error_settings_controller->file );
			}
			
			//	DB_ENV->set_errpfx()
			if ( error_settings_controller->prefix )	{
				RPDB_ErrorSettingsController_setPrefix(	error_settings_controller,
															error_settings_controller->prefix );
			}
			
		}
		
		if ( settings_controller->message_settings_controller != NULL )	{
		
			RPDB_MessageSettingsController*	message_settings_controller	=	settings_controller->message_settings_controller;

			//	DB_ENV->set_msgfile()
			if ( message_settings_controller->message_file )	{
				RPDB_MessageSettingsController_setFile(	message_settings_controller,
															message_settings_controller->message_file );
			}
		}
		
		if (	settings_controller->thread_settings_controller != NULL
			&&	RPDB_LogSettingsController_on( settings_controller->log_settings_controller ) )	{
		
			RPDB_ThreadSettingsController*	thread_settings_controller	=	settings_controller->thread_settings_controller;

			//	DB_ENV->set_thread_count()
			if ( thread_settings_controller->thread_count )	{
				RPDB_ThreadSettingsController_setThreadCount(	thread_settings_controller,
																thread_settings_controller->thread_count );
			}
			
			if ( thread_settings_controller->is_thread_alive_callback_method )	{
//				RPDB_ThreadSettingsController_setIsThreadAliveCallback(	thread_settings_controller,
//																			thread_settings_controller->is_thread_alive_callback_method	);
			}
		}
		
		if ( settings_controller->file_settings_controller != NULL )	{
		
			RPDB_FileSettingsController*	file_settings_controller	=	settings_controller->file_settings_controller;

			//	DB_ENV->set_intermediate_dir_mode()
			if ( file_settings_controller->intermediate_directory_mode )	{
				RPDB_FileSettingsController_setIntermediateDirectoryMode(	file_settings_controller,
																			file_settings_controller->intermediate_directory_mode );
			}
			
			//	DB_ENV->set_tmp_dir()
			if ( file_settings_controller->temp_directory )	{
				RPDB_FileSettingsController_setTempDirectory(	file_settings_controller,
															  file_settings_controller->temp_directory );
			}
		}

		if (	settings_controller->lock_settings_controller != NULL
			&&	RPDB_LockSettingsController_on( settings_controller->lock_settings_controller ) )	{
		
			RPDB_LockSettingsController*	lock_settings_controller	=	settings_controller->lock_settings_controller;
			
			//	DB_ENV->set_timeout()
			if ( lock_settings_controller->timeout )	{
				RPDB_LockSettingsController_setTimeout(	lock_settings_controller,
															lock_settings_controller->timeout );
			}
			
			if ( lock_settings_controller->conflict_matrix )	{
				//	DB_ENV->set_lk_conflicts()
				RPDB_LockSettingsController_setConflictMatrix(	lock_settings_controller,
																lock_settings_controller->conflict_matrix );
			}
			
			if ( lock_settings_controller->max_lockers )	{
				//	DB_ENV->set_lk_max_lockers()
				RPDB_LockSettingsController_setMaxLockers(	lock_settings_controller,
															lock_settings_controller->max_lockers );
			}
			
			
			if ( lock_settings_controller->max_locks )	{
				//	DB_ENV->set_lk_max_locks()
				RPDB_LockSettingsController_setMaxLocks(	lock_settings_controller,
															lock_settings_controller->max_locks );
			}
				
			if ( lock_settings_controller->max_objects )	{
				//	DB_ENV->set_lk_max_objects()
				RPDB_LockSettingsController_setMaxObjects(	lock_settings_controller,
															lock_settings_controller->max_objects );
			}
				
			if ( lock_settings_controller->partitions )	{
				//	DB_ENV->set_lk_partitions()
				RPDB_LockSettingsController_setNumberOfPartitions(	lock_settings_controller,
																	lock_settings_controller->partitions );
			}
				
			if ( lock_settings_controller->deadlock_detector_settings_controller != NULL )	{

				RPDB_LockDeadlockDetectorSettingsController*	deadlock_detector_settings_controller	=	lock_settings_controller->deadlock_detector_settings_controller;

				if ( deadlock_detector_settings_controller->deadlock_settings )	{
					//	DB_ENV->set_lk_detect()
					RPDB_LockDeadlockDetectorSettingsController_internal_setTo(	deadlock_detector_settings_controller,
																					deadlock_detector_settings_controller->deadlock_settings	);
				}
			}
		}
		
		if (	settings_controller->transaction_settings_controller != NULL
			&&	RPDB_TransactionSettingsController_on( settings_controller->transaction_settings_controller ) )	{
		
			RPDB_TransactionSettingsController*	transaction_settings_controller	=	settings_controller->transaction_settings_controller;

			//	DB_ENV->set_timeout()
			if ( transaction_settings_controller->timeout_in_microseconds )	{
				RPDB_TransactionSettingsController_setTimeoutInMicroseconds(	transaction_settings_controller,
																				transaction_settings_controller->timeout_in_microseconds );
			}
		}
		
		if (	settings_controller->log_settings_controller != NULL
			&&	RPDB_LogSettingsController_on( settings_controller->log_settings_controller ) )	{
		
			RPDB_LogSettingsController*	log_settings_controller	=	settings_controller->log_settings_controller;

			//	DB_ENV->log_set_config()
			RPDB_LogSettingsController_internal_setLogConfig(	log_settings_controller );
			
			//	DB_ENV->set_lg_bsize()
			if ( log_settings_controller->buffer_size )	{
				RPDB_LogSettingsController_setBufferSize(	log_settings_controller,
															log_settings_controller->buffer_size );
			}
			
			//	DB_ENV->set_lg_dir()
			if ( log_settings_controller->directory )	{
				RPDB_LogSettingsController_setDirectory(	log_settings_controller,
															log_settings_controller->directory );
			}
			
			//	DB_ENV->set_lg_filemode()
			if ( log_settings_controller->mode )	{
				RPDB_LogSettingsController_setMode(	log_settings_controller,
														log_settings_controller->mode );
			}
			
			//	DB_ENV->set_lg_max()
			if ( log_settings_controller->max_size )	{
				RPDB_LogSettingsController_setMaxLogSize(	log_settings_controller,
															log_settings_controller->max_size );
			}
			
			//	DB_ENV->set_lg_regionmax()
			if ( log_settings_controller->max_region_size )	{
				RPDB_LogSettingsController_setMaxRegionSize(	log_settings_controller,
																log_settings_controller->max_region_size );
			}
		}

		#ifdef RPDB_DEFAULT_FAILCHECK
			RPDB_ThreadSettingsController_setThreadCount(	RPDB_SettingsController_threadSettingsController( settings_controller ),
																										RPDB_DEFAULT_THREAD_COUNT );
			
			//	Set callback method for is_alive
			//	we have to call the internal function here rather than our own wrapper b/c at this point the bdb database has not been stored in runtime storage
			//	FIX - our wrapper function won't function at all for this reason
			//	i think the only way to fix this is to make the wrapper call from our internal function
			environment->wrapped_bdb_environment->set_isalive(	environment->wrapped_bdb_environment,
																													& RPDB_Environment_internal_defaultIsThreadAliveCallback );	
		#endif
	}
	
	/*
	 	 
	 //	FIX - not implemented
	 //	DB_ENV->set_data_dir(), DB_ENV->get_data_dirs()	Set/get the environment data directory
	 //	DB_ENV->set_encrypt(), DB_ENV->get_encrypt_flags()	Set/get the environment cryptographic key

	 Callbacks (not yet implemented):
	 
	 DB_ENV->set_alloc()	Set local space allocation functions
	 DB_ENV->set_app_dispatch()	Configure application recovery callback
	 DB_ENV->set_event_notify()	Set event notification callback
	 DB_ENV->set_feedback()	Set feedback callback
	 DB_ENV->set_isalive()	Set thread is-alive callback
	 DB_ENV->set_msgcall()	Set informational message callback
	 DB_ENV->set_errcall()	Set error message callbacks
	 DB_ENV->set_thread_id()	Set thread of control ID function
	 RPDB_ThreadSettingsController_setUniqueThreadIdentifierCallbackMethod
	 
	 DB_ENV->set_thread_id_string()	Set thread of control ID format function
	 
	 
	 */
	 
}

/*********************************
*  defaultIsThreadAliveCallback  *
*********************************/

int RPDB_Environment_internal_defaultIsThreadAliveCallback(	DB_ENV*			bdb_environment,
															pid_t			process_id,
															db_threadid_t	thread_id,
															uint32_t		flags )	{

	//	If we don't have a process id, return false
	if ( ! process_id )	{
		return FALSE;
	}
	//	Otherwise check if our process id exists (signal 0 does not kill)
	BOOL process_is_alive = ( kill( process_id, 0 ) == 0 );
	if ( ! process_is_alive )	{
		return FALSE;
	}
	
	//	Does BDB want us to ignore the TxID status?
	if ( flags == DB_MUTEX_PROCESS_ONLY )	{
		return TRUE;
	}
	
	//	Make sure we have a thread id - 0 is root thread
	if ( ! thread_id )	{
		return TRUE;
	}

	//	Otherwise check if thread is alive
	int thread_is_alive = ( pthread_kill( thread_id, 0 ) == 0 );
	if ( ! thread_is_alive )	{
		return FALSE;
	}
	
	//	Finally, mostly to get rid of the warning for being unused, test if bdb_environment is null
	if ( bdb_environment == NULL )	{
		return FALSE;
	}
	
	return TRUE;
}
