/*
 *		RPbdb
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

#include "Environment.h"
#include "Environment_internal.h"

#include "DatabaseController.h"
#include "Database.h"
#include "DatabaseJoinController.h"

#include "ErrorController.h"
#include "LockController.h"
#include "LogController.h"
#include "MemoryPoolController.h"
#include "MutexController.h"
#include "ReplicationController.h"
#include "TransactionController.h"

#include "SettingsController.h"

#include "DatabaseCursorSettingsController.h"
#include "DatabaseTypeSettingsController.h"
#include "DatabaseSettingsController.h"
#include "DirectorySettingsController.h"
#include "DebugSettingsController.h"
#include "ErrorSettingsController.h"
#include "FileSettingsController.h"
#include "MemoryPoolSettingsController.h"
#include "MemoryPoolReadWriteSettingsController.h"
#include "MessageSettingsController.h"
#include "LockSettingsController.h"
#include "LockDeadlockDetectorSettingsController.h"
#include "LogSettingsController.h"
#include "TransactionSettingsController.h"
#include "ThreadSettingsController.h"
#include "DatabaseSequenceSettingsController.h"

#include "SettingsController_internal.h"
#include "LockDeadlockDetectorSettingsController_internal.h"
#include "LogSettingsController_internal.h"

#include "RuntimeStorageController.h"
#include "RuntimeStorageController_internal.h"

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

RPbdb_Environment* RPbdb_Environment_new(	char* environment_home_directory )	{

	RPbdb_Environment*	environment	=	calloc( 1, sizeof( RPbdb_Environment ) );

	environment->is_open			=	FALSE;

	int		directory_length	=	0;
	//	If no directory is specified we use current working directory
	if ( environment_home_directory == NULL )	{
		environment_home_directory	=	RPBDB_DEFAULT_ENVIRONMENT_HOME_DIRECTORY;
	}
	
	//	if we have environment in memory, don't check path (it has none)
	if ( environment_home_directory[ 0 ] != '\0' )	{

		directory_length	=	strlen( environment_home_directory );

		//	make sure our home directory ends with '/'
		BOOL	home_directory_needs_slash	=	FALSE;
		if ( environment_home_directory[ directory_length - 1 ] != '/' )	{
			home_directory_needs_slash	=	TRUE;
		}
		environment->directory	=	calloc( directory_length + home_directory_needs_slash + 1, sizeof( char ) );
		sprintf( environment->directory, "%s%s",	environment_home_directory,
																							( home_directory_needs_slash ? "/" : "" ) );
		
	}
	
	RPbdb_Environment_initDefaults( environment );
	
	return environment;
}

/*********
*  free  *
*********/

void RPbdb_Environment_free( RPbdb_Environment** environment )	{

	//	close and free transaction controller
	if ( ( *environment )->transaction_controller != NULL )	{
		
		//	If we have a transaction controller we need to close all databases so we can commit the transaction
		//	This is necessary because the databases were opened inside the transaction
		if ( ( *environment )->database_controller != NULL )	{
			RPbdb_DatabaseController_closeAllDatabases( ( *environment )->database_controller );
		}
		
		RPbdb_TransactionController_free( & ( ( *environment )->transaction_controller ) );
	}
	
	//	if the environment is open, close it
	if ( RPbdb_Environment_isOpen( *environment ) )	{
		RPbdb_Environment_close( *environment );
	}
	
	//	the order in which calls happen to free child objects is important

	//	free database controller and databases (close if necessary)
	if ( ( *environment )->database_controller != NULL )	{
		RPbdb_DatabaseController_free( & ( ( *environment )->database_controller ) );
	}

	//	free error controller
	if ( ( *environment )->error_controller != NULL )	{
		RPbdb_ErrorController_free( & ( ( *environment )->error_controller ) );
	}

	//	free memory pool controller
	if ( ( *environment )->memory_pool_controller != NULL )	{
		RPbdb_MemoryPoolController_free( & ( ( *environment )->memory_pool_controller ) );
	}
	
	//	free log controller and any open logs
	if ( ( *environment )->log_controller != NULL )	{
		RPbdb_LogController_free( & ( ( *environment )->log_controller ) );
	}
	
	//	free replication controller
	if ( ( *environment )->replication_controller != NULL )	{
		RPbdb_ReplicationController_free( & ( ( *environment )->replication_controller ) );
	}
	
	//	free mutex controller and mutexes
	if ( ( *environment )->mutex_controller != NULL )	{
		RPbdb_MutexController_free( & ( ( *environment )->mutex_controller ) );
	}
	
	//	free lock controller
	if ( ( *environment )->lock_controller != NULL )	{
		RPbdb_LockController_free( & ( ( *environment )->lock_controller ) );
	}
	
	//	free all environmental settings controllers
	if ( ( *environment )->settings_controller != NULL )	{
		RPbdb_SettingsController_free( & ( ( *environment )->settings_controller ) );
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

void RPbdb_Environment_initDefaults( RPbdb_Environment* environment )	{

	RPbdb_SettingsController*								settings_controller								=	RPbdb_Environment_settingsController( environment );
	RPbdb_ErrorSettingsController*						error_settings_controller					=	RPbdb_SettingsController_errorSettingsController( settings_controller );
//	RPbdb_DebugSettingsController*						debug_settings_controller					=	RPbdb_SettingsController_debugSettingsController( settings_controller );
	RPbdb_TransactionSettingsController*			transaction_settings_controller		=	RPbdb_SettingsController_transactionSettingsController( settings_controller );
	RPbdb_LogSettingsController*							log_settings_controller						=	RPbdb_SettingsController_logSettingsController( settings_controller );
	RPbdb_LockSettingsController*						lock_settings_controller					=	RPbdb_SettingsController_lockSettingsController( settings_controller );
	RPbdb_MemoryPoolSettingsController*			memory_pool_settings_controller		=	RPbdb_SettingsController_memoryPoolSettingsController( settings_controller );
	RPbdb_DirectorySettingsController*				directory_settings_controller			=	RPbdb_SettingsController_directorySettingsController( settings_controller );
	RPbdb_FileSettingsController*						file_settings_controller					=	RPbdb_SettingsController_fileSettingsController( settings_controller );
	RPbdb_ThreadSettingsController*					thread_settings_controller				=	RPbdb_SettingsController_threadSettingsController( settings_controller );
	RPbdb_DatabaseSettingsController*				database_settings_controller			=	RPbdb_SettingsController_databaseSettingsController( settings_controller );
	RPbdb_DatabaseTypeSettingsController*		database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
	RPbdb_DatabaseSequenceSettingsController*		database_sequence_settings_controller	=	RPbdb_DatabaseSettingsController_sequenceSettingsController( database_settings_controller );

	RPbdb_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	RPbdb_DatabaseSettingsController_cursorSettingsController( database_settings_controller );

	//	we always want default cursor duplication to actually duplicate the cursor
	RPbdb_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOn( database_cursor_settings_controller );

	#ifdef RPBDB_DEFAULT_MEMORY_POOL_ON
		//	And make sure we actually have a memory pool
		RPbdb_MemoryPoolSettingsController_turnOn( memory_pool_settings_controller );
	#endif

	#ifdef RPBDB_DEFAULT_TRANSACTION_DATA_STORE_ON
	

		RPbdb_TransactionSettingsController_turnOn( transaction_settings_controller );
		RPbdb_LogSettingsController_turnOn( log_settings_controller );
		RPbdb_LockSettingsController_turnOn( lock_settings_controller );

		//	Enable registration, checking for environmental failure, normal recovery
		//	DB_RECOVER
//		RPbdb_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOn( debug_settings_controller );

		//	DB_REGISTER, DB_ENV_FAILCHK
//		RPbdb_DebugSettingsController_turnRegisterForRecoveryOn( debug_settings_controller );
//		RPbdb_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOn( debug_settings_controller );
		
	#else
	
		#ifdef RPBDB_DEFAULT_CONCURRENT_DATA_STORE_ON
			RPbdb_TransactionSettingsController_turnConcurrentDataStoreLockingOn( transaction_settings_controller );
		#endif
	
	#endif

	#ifdef RPBDB_DEFAULT_SET_ENVIRONMENT_PATH_ON

		//	Set our environment home as our database directory
		if ( environment->directory != NULL )	{
			RPbdb_DirectorySettingsController_addDataDirectory(	directory_settings_controller,
																													environment->directory );
		}

	#endif
															
	#ifdef RPBDB_DEFAULT_CREATE_IF_NECESSARY
		RPbdb_FileSettingsController_turnCreateIfNecessaryOn( file_settings_controller );
	#endif
	
	#ifdef RPBDB_DEFAULT_TO_BTREE
		//	Unless otherwise specified, all of our runtime storage will be hash - set the environmental default
		RPbdb_DatabaseTypeSettingsController_setTypeToBTree( database_type_settings_controller );
	#endif
	
	#ifdef RPBDB_MULTIPLE_ACCESS
		RPbdb_ThreadSettingsController_turnOn( thread_settings_controller );
	#endif

	#ifdef RPBDB_DEFAULT_ENVIRONMENT_LOG
		#if RPBDB_DEFAULT_ENVIRONMENT_LOG == TRUE
			if (		environment->directory 
					&&	environment->directory[0] != '\0' )	{			
				if ( RPBDB_DEFAULT_ENVIRONMENT_LOG_TO_FILE )	{
					char*	log_file_path	=	RPbdb_Environment_internal_errorfilePathForEnvironment(	environment );
					RPbdb_ErrorSettingsController_setFileFromPath(	error_settings_controller,
																												log_file_path );
					free( log_file_path );
				}
				else {
					RPbdb_ErrorSettingsController_setFile(	error_settings_controller,
																								stderr );			
				}
			}
		#endif
	#endif

	RPbdb_DatabaseSequenceSettingsController_setAsIncreasing(			database_sequence_settings_controller );
	RPbdb_DatabaseSequenceSettingsController_setAsIncreasing(			database_sequence_settings_controller );
	RPbdb_DatabaseSequenceSettingsController_setInitialValue(			database_sequence_settings_controller, 0 );
	RPbdb_DatabaseSequenceSettingsController_setDefaultStepValue(	database_sequence_settings_controller, 1 );

}

/*************************
*  initForMemoryStorage  *
*************************/

RPbdb_Environment* RPbdb_Environment_initForStorageInMemory( RPbdb_Environment* environment )	{
	
	RPbdb_SettingsController*											settings_controller													=	RPbdb_Environment_settingsController( environment );
	RPbdb_LogSettingsController*										log_settings_controller											=	RPbdb_SettingsController_logSettingsController( settings_controller );
	RPbdb_MemoryPoolSettingsController*						memory_pool_settings_controller							=	RPbdb_SettingsController_memoryPoolSettingsController( settings_controller );
	RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller	=	RPbdb_MemoryPoolSettingsController_readWriteSettingsController( memory_pool_settings_controller );

	//	Don't allow writes to disk - use application memory for storage
	RPbdb_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOn(	memory_pool_read_write_settings_controller );

	//	Don't use a temporary backing file for flushing memory	
	RPbdb_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOn(	memory_pool_read_write_settings_controller );
		
	//	If log in memory is on, log in memory; otherwise, turn logging system off
	if ( ! RPbdb_LogSettingsController_logInMemory( log_settings_controller ) )	{

		//	If we're not logging in memory we don't want to log at all (because it would write to disk)
		RPbdb_LogSettingsController_turnOff(	log_settings_controller );
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
RPbdb_Environment* RPbdb_Environment_open( RPbdb_Environment* environment )	{

	if ( ! RPbdb_Environment_isOpen( environment ) )	{
					
		RPbdb_Environment_internal_initWrappedEnvironment( environment, FALSE );
						
		RPbdb_Environment_internal_openWithoutRuntimeStorage( environment );

		RPbdb_RuntimeStorageController_internal_storeEnvironmentForBDBEnvironment(	RPbdb_RuntimeStorageController_sharedInstance(),
																																							environment );
		environment->is_open	=	TRUE;
	}
		
	//	return environment
	return environment;
}

/***********
*  isOpen  *
***********/
	
BOOL RPbdb_Environment_isOpen( RPbdb_Environment* environment )	{
	return environment->is_open;
}

/******************
*  homeDirectory  *
******************/

char* RPbdb_Environment_homeDirectory( RPbdb_Environment* environment )	{
	return environment->directory;
}

/**********
*  close  *
**********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_close.html
RPbdb_Environment* RPbdb_Environment_close( RPbdb_Environment* environment )	{

	if ( environment->is_open )	{
	
		//	remove entry in runtime storage for this environment - we do this before closing so we have the bdb address, which is the key
		RPbdb_RuntimeStorageController_internal_removeStoredEnvironment(	RPbdb_RuntimeStorageController_sharedInstance(),
																																		environment );
		
		//	Tell all locks to release
		if ( environment->lock_controller != NULL )	{
			RPbdb_LockController_closeAllLocks( environment->lock_controller );
		}
		
		if ( environment->mutex_controller != NULL )	{
			//	Tell all mutex to release
			RPbdb_MutexController_closeAllMutexes( environment->mutex_controller );
		}
			
		if ( environment->transaction_controller != NULL )	{
			RPbdb_TransactionController_commitAllTransactions( environment->transaction_controller );
		}
		
		if ( environment->database_controller != NULL )	{
			//	Tell all databases to close (and to name their subsystems)
			RPbdb_DatabaseController_closeAllDatabases( environment->database_controller );
		}
		
		//	Close environment
		environment->wrapped_bdb_environment->close(	environment->wrapped_bdb_environment, 
														RPbdb_SettingsController_internal_closeFlags( RPbdb_Environment_settingsController( environment ) ) );

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
RPbdb_Environment* RPbdb_Environment_erase( RPbdb_Environment* environment )	{
	
	int connection_error	= 0;
	
	//	An environment that has been opened should not be used to erase
	//	We create a new wrapped environment instance to deal with it
	if ( RPbdb_Environment_isOpen( environment ) )	{
		RPbdb_Environment_close( environment );
	}

	//	whether or not our environment was opened we need a new environment instance to use for erase
	if ( ( connection_error = db_env_create(	&( environment->wrapped_bdb_environment ), 
																						RPbdb_SettingsController_internal_createFlags(	RPbdb_Environment_settingsController( environment ) ) ) ) ) {
		
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
																									connection_error, 
																									"Environment_erase" );
	}		
	
	int	flags	=	RPbdb_SettingsController_internal_eraseFlags( RPbdb_Environment_settingsController( environment ) );
	connection_error	= 0;
	if ( ( connection_error = environment->wrapped_bdb_environment->remove(	environment->wrapped_bdb_environment, 
																			environment->directory,
																			flags ) ) ) {
																					
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ), 
																									connection_error, 
																									"Environment_erase" );
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

void RPbdb_Environment_checkForEnvironmentFailure( RPbdb_Environment* environment )	{
	environment->wrapped_bdb_environment->failchk(	environment->wrapped_bdb_environment,
																									RPBDB_NO_FLAGS );
}	

/***********
*  name  *
***********/

char* RPbdb_Environment_name( RPbdb_Environment* environment )	{
	return environment->name;
}
	
/**************
*  setName  *
**************/

void RPbdb_Environment_setName(	RPbdb_Environment*		environment,
																char*								name )	{
	environment->name	=	strdup( name );
}
	
/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/********************
*  errorController  *
********************/

RPbdb_ErrorController* RPbdb_Environment_errorController( RPbdb_Environment* environment )	{

	if (	! environment 
		||	! environment->error_controller )	{
		return RPbdb_ErrorController_new( environment );
	}
	
	return environment->error_controller;
}

/***********************
*  databaseController  *
***********************/

RPbdb_DatabaseController* RPbdb_Environment_databaseController( RPbdb_Environment* environment )	{

	if ( environment->database_controller == NULL )	{
		environment->database_controller = RPbdb_DatabaseController_new( environment );
	}
	
	return environment->database_controller;
}

/*******************
*  lockController  *
*******************/

RPbdb_LockController* RPbdb_Environment_lockController( RPbdb_Environment* environment )	{

	if ( ! environment->lock_controller )	{
		environment->lock_controller = RPbdb_LockController_new( environment );
	}
	
	return environment->lock_controller;	
}

/*************************
*  memoryPoolController  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get_mpf.html
RPbdb_MemoryPoolController* RPbdb_Environment_memoryPoolController( RPbdb_Environment* environment )	{

	if ( ! environment->memory_pool_controller )	{
		environment->memory_pool_controller = RPbdb_MemoryPoolController_new( environment );
	}
	
	return environment->memory_pool_controller;		
}

/********************
*  mutexController  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_unlock.html
RPbdb_MutexController* RPbdb_Environment_mutexController( RPbdb_Environment* environment )	{

	if ( ! environment->mutex_controller )	{
		environment->mutex_controller = RPbdb_MutexController_new( environment );
	}
	
	return environment->mutex_controller;			
}

/**************************
*  replicationController  *
**************************/

RPbdb_ReplicationController* 	RPbdb_Environment_replicationController( RPbdb_Environment* environment )	{

	if ( ! environment->replication_controller )	{
		environment->replication_controller = RPbdb_ReplicationController_new( environment );
	}
	
	return environment->replication_controller;	
}

/*********************
*  objectController  *
*********************/
/*
RPbdb_ObjectController* RPbdb_Environment_objectController( RPbdb_Environment* environment )	{

	if ( ! environment->object_controller )	{
		environment->object_controller = RPbdb_ObjectController_new( environment );
	}
	
	return environment->object_controller;	
}
*/

/*************************
*  controllerController  *
*************************/
/*
RPbdb_Controller* RPbdb_Environment_controllerController( RPbdb_Environment* environment )	{

	if ( ! environment->controller_controller )	{
		environment->controller_controller = RPbdb_controllerController_new( environment );
	}
	
	return environment->controller_controller;	
}
*/

/******************
*  logController  *
******************/

RPbdb_LogController* RPbdb_Environment_logController( RPbdb_Environment* environment )	{

	if ( ! environment->log_controller )	{
		environment->log_controller = RPbdb_LogController_new( environment );
	}
	
	return environment->log_controller;		
}

/*********************
*  statusController  *
*********************/
/*
RPbdb_StatusController* RPbdb_Environment_statusController( RPbdb_Environment* environment )	{

	if ( ! environment->status_controller )	{
		environment->status_controller = RPbdb_StatusController_new( environment );
	}
	
	return environment->status_controller;			
}
*/

/**************************
*  transactionController  *
**************************/

RPbdb_TransactionController* RPbdb_Environment_transactionController( RPbdb_Environment* environment )	{

	if ( ! environment->transaction_controller )	{
		environment->transaction_controller = RPbdb_TransactionController_new( environment );
	}
	
	return environment->transaction_controller;		
}

/***********************
*  settingsController  *
***********************/

RPbdb_SettingsController* RPbdb_Environment_settingsController( RPbdb_Environment* environment )	{

	if ( environment->settings_controller == NULL )	{
		environment->settings_controller = RPbdb_SettingsController_new( environment );
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

void RPbdb_Environment_internal_openWithoutRuntimeStorage( RPbdb_Environment* environment )	{

	int						connection_error	= 0;
	
	int	flags	=	RPbdb_SettingsController_internal_openFlags( RPbdb_Environment_settingsController( environment ) );
	int	mode	=	RPbdb_FileSettingsController_fileCreationMode( RPbdb_SettingsController_fileSettingsController( RPbdb_Environment_settingsController( environment ) ) );
	
	//	Create if necessary only creates the db; we have to create the directory if it doesn't yet exist
	if ( RPbdb_FileSettingsController_createIfNecessary( RPbdb_SettingsController_fileSettingsController( RPbdb_Environment_settingsController( environment ) ) )	 ){
		
		//	check whether the directory exists
		if( access( environment->directory, F_OK ) == -1 ) {		
			//	if it doesn't, create it
			mkdir(	environment->directory, S_IRWXU );
		}		
	}
	
	//	Open the environment itself (regardless of whether we had to create it on this call to RPbdb_open)
	if ( ( connection_error = environment->wrapped_bdb_environment->open(	environment->wrapped_bdb_environment, 
																																				environment->directory, 
																																				flags,
																																				mode ) ) ) {
																			
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ), 
														connection_error, 
														"Environment_internal_openWithoutRuntimeStorage" );
	}
	
	//	record that this environment has been opened
	environment->is_open = TRUE;
	
}

/***************************
*  initWrappedEnvironment  *
***************************/

void RPbdb_Environment_internal_initWrappedEnvironment(	RPbdb_Environment*		environment, 
																												BOOL								for_runtime_environment )	{
	
	//	if we don't have a wrapped_bdb_environment then we need to create one before we can open it
	//	FIX - if we created a new wrapped_bdb_environment then we need to make sure any settings
	//	are applied to the new one so that its creation is transparent.
	//	FIX - this probably means moving all settings to two layers, one where the RPbdb instance is set
	//	and one where the bdb instance is set (right before it opens)
	
	//	create bdb DB_ENV instance
	int	connection_error	=	RP_NO_ERROR;
	if ( ( connection_error = db_env_create(	&( environment->wrapped_bdb_environment ), 
																						RPbdb_SettingsController_internal_createFlags(	RPbdb_Environment_settingsController( environment ) ) ) ) ) {
		
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
														connection_error, 
														"Environment_internal_initWrappedEnvironment" );
	}
	
	//	now we have to set the wrapped bdb environment with all of our settings from our rpbdb environment wrapper
	if (	for_runtime_environment == FALSE
		&&	environment->settings_controller != NULL )	{
	
		RPbdb_SettingsController*	settings_controller	=	environment->settings_controller;
	
		//	DB_ENV->set_flags()
		RPbdb_SettingsController_internal_setFlags( settings_controller );
		
		//	DB_ENV->set_verbose()
		RPbdb_SettingsController_internal_setVerbosity( settings_controller );

		//	DB_ENV->set_shm_key()
		if ( settings_controller->shm_key )	{
			RPbdb_SettingsController_setSHMkey(	settings_controller,
												settings_controller->shm_key );
		}
/*
		if ( settings_controller->debug_settings_controller != NULL )	{

			RPbdb_DebugSettingsController*	debug_settings_controller	=	settings_controller->debug_settings_controller;
			
		}
		*/
		if ( settings_controller->directory_settings_controller != NULL )	{

			RPbdb_DirectorySettingsController*	directory_settings_controller	=	settings_controller->directory_settings_controller;
			
			//	DB_ENV->add_data_dir()
			if ( directory_settings_controller->directories )	{
				RPbdb_Directory**	this_directory	=	NULL;
				this_directory	=	& ( directory_settings_controller->directories );
				do	{
					environment->wrapped_bdb_environment->add_data_dir(	environment->wrapped_bdb_environment, 
																		( *this_directory )->path );					
				}	while (		this_directory = & ( ( *this_directory)->next ), 
								*this_directory != NULL );				
			}
			
			//	DB_ENV->set_create_dir()
			if ( environment->create_directory )	{
				RPbdb_DirectorySettingsController_setCreateDirectory(	directory_settings_controller,
																		environment->create_directory );
			}
		}
		
		if ( settings_controller->error_settings_controller != NULL )	{
		
			RPbdb_ErrorSettingsController*	error_settings_controller	=	settings_controller->error_settings_controller;

			//	DB_ENV->set_errfile()
			if ( error_settings_controller->error_file )	{
				RPbdb_ErrorSettingsController_setFile(	error_settings_controller,
																							error_settings_controller->error_file );
			}	
			
			//	DB_ENV->set_errpfx()
			if ( error_settings_controller->prefix )	{
				RPbdb_ErrorSettingsController_setPrefix(	error_settings_controller,
																								error_settings_controller->prefix );
			}
			
		}
		
		if ( settings_controller->message_settings_controller != NULL )	{
		
			RPbdb_MessageSettingsController*	message_settings_controller	=	settings_controller->message_settings_controller;

			//	DB_ENV->set_msgfile()
			if ( message_settings_controller->message_file )	{
				RPbdb_MessageSettingsController_setFile(	message_settings_controller,
															message_settings_controller->message_file );
			}
		}
		
		if (	settings_controller->thread_settings_controller != NULL
			&&	RPbdb_LogSettingsController_on( settings_controller->log_settings_controller ) )	{
		
			RPbdb_ThreadSettingsController*	thread_settings_controller	=	settings_controller->thread_settings_controller;

			//	DB_ENV->set_thread_count()
			if ( thread_settings_controller->thread_count )	{
				RPbdb_ThreadSettingsController_setThreadCount(	thread_settings_controller,
																thread_settings_controller->thread_count );
			}
			
			if ( thread_settings_controller->is_thread_alive_callback_method )	{
				RPbdb_ThreadSettingsController_setIsThreadAliveCallback(	thread_settings_controller,
																																thread_settings_controller->is_thread_alive_callback_method	);
			}
		}
		
		if ( settings_controller->file_settings_controller != NULL )	{
		
			RPbdb_FileSettingsController*	file_settings_controller	=	settings_controller->file_settings_controller;

			//	DB_ENV->set_intermediate_dir_mode()
			if ( file_settings_controller->intermediate_directory_mode )	{
				RPbdb_FileSettingsController_setIntermediateDirectoryMode(	file_settings_controller,
																			file_settings_controller->intermediate_directory_mode );
			}
			
			//	DB_ENV->set_tmp_dir()
			if ( file_settings_controller->temp_directory )	{
				RPbdb_FileSettingsController_setTempDirectory(	file_settings_controller,
															  file_settings_controller->temp_directory );
			}
		}

		if (	settings_controller->lock_settings_controller != NULL
			&&	RPbdb_LockSettingsController_on( settings_controller->lock_settings_controller ) )	{
		
			RPbdb_LockSettingsController*	lock_settings_controller	=	settings_controller->lock_settings_controller;
			
			//	DB_ENV->set_timeout()
			if ( lock_settings_controller->timeout )	{
				RPbdb_LockSettingsController_setTimeout(	lock_settings_controller,
															lock_settings_controller->timeout );
			}
			
			if ( lock_settings_controller->conflict_matrix )	{
				//	DB_ENV->set_lk_conflicts()
				RPbdb_LockSettingsController_setConflictMatrix(	lock_settings_controller,
																lock_settings_controller->conflict_matrix );
			}
			
			if ( lock_settings_controller->max_lockers )	{
				//	DB_ENV->set_lk_max_lockers()
				RPbdb_LockSettingsController_setMaxLockers(	lock_settings_controller,
															lock_settings_controller->max_lockers );
			}
			
			
			if ( lock_settings_controller->max_locks )	{
				//	DB_ENV->set_lk_max_locks()
				RPbdb_LockSettingsController_setMaxLocks(	lock_settings_controller,
															lock_settings_controller->max_locks );
			}
				
			if ( lock_settings_controller->max_objects )	{
				//	DB_ENV->set_lk_max_objects()
				RPbdb_LockSettingsController_setMaxObjects(	lock_settings_controller,
															lock_settings_controller->max_objects );
			}
				
			if ( lock_settings_controller->partitions )	{
				//	DB_ENV->set_lk_partitions()
				RPbdb_LockSettingsController_setNumberOfPartitions(	lock_settings_controller,
																	lock_settings_controller->partitions );
			}
				
			if ( lock_settings_controller->deadlock_detector_settings_controller != NULL )	{

				RPbdb_LockDeadlockDetectorSettingsController*	deadlock_detector_settings_controller	=	lock_settings_controller->deadlock_detector_settings_controller;

				if ( deadlock_detector_settings_controller->deadlock_settings )	{
					//	DB_ENV->set_lk_detect()
					RPbdb_LockDeadlockDetectorSettingsController_internal_setTo(	deadlock_detector_settings_controller,
																					deadlock_detector_settings_controller->deadlock_settings	);
				}
			}
		}
		
		if (	settings_controller->transaction_settings_controller != NULL
			&&	RPbdb_TransactionSettingsController_on( settings_controller->transaction_settings_controller ) )	{
		
			RPbdb_TransactionSettingsController*	transaction_settings_controller	=	settings_controller->transaction_settings_controller;

			//	DB_ENV->set_timeout()
			if ( transaction_settings_controller->timeout_in_microseconds )	{
				RPbdb_TransactionSettingsController_setTimeoutInMicroseconds(	transaction_settings_controller,
																				transaction_settings_controller->timeout_in_microseconds );
			}
		}
		
		if (	settings_controller->log_settings_controller != NULL
			&&	RPbdb_LogSettingsController_on( settings_controller->log_settings_controller ) )	{
		
			RPbdb_LogSettingsController*	log_settings_controller	=	settings_controller->log_settings_controller;

			//	DB_ENV->log_set_config()
			RPbdb_LogSettingsController_internal_setLogConfig(	log_settings_controller );
			
			//	DB_ENV->set_lg_bsize()
			if ( log_settings_controller->buffer_size )	{
				RPbdb_LogSettingsController_setBufferSize(	log_settings_controller,
															log_settings_controller->buffer_size );
			}
			
			//	DB_ENV->set_lg_dir()
			if ( log_settings_controller->directory )	{
				RPbdb_LogSettingsController_setDirectory(	log_settings_controller,
															log_settings_controller->directory );
			}
			
			//	DB_ENV->set_lg_filemode()
			if ( log_settings_controller->mode )	{
				RPbdb_LogSettingsController_setMode(	log_settings_controller,
														log_settings_controller->mode );
			}
			
			//	DB_ENV->set_lg_max()
			if ( log_settings_controller->max_size )	{
				RPbdb_LogSettingsController_setMaxLogSize(	log_settings_controller,
															log_settings_controller->max_size );
			}
			
			//	DB_ENV->set_lg_regionmax()
			if ( log_settings_controller->max_region_size )	{
				RPbdb_LogSettingsController_setMaxRegionSize(	log_settings_controller,
																log_settings_controller->max_region_size );
			}
		}

		#ifdef RPBDB_DEFAULT_FAILCHECK
			RPbdb_ThreadSettingsController_setThreadCount(	RPbdb_SettingsController_threadSettingsController( settings_controller ),
																										RPBDB_DEFAULT_THREAD_COUNT );
			
			//	Set callback method for is_alive
			//	we have to call the internal function here rather than our own wrapper b/c at this point the bdb database has not been stored in runtime storage
			//	FIX - our wrapper function won't function at all for this reason
			//	i think the only way to fix this is to make the wrapper call from our internal function
			environment->wrapped_bdb_environment->set_isalive(	environment->wrapped_bdb_environment,
																													& RPbdb_Environment_internal_defaultIsThreadAliveCallback );	
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
	 RPbdb_ThreadSettingsController_setUniqueThreadIdentifierCallbackMethod
	 
	 DB_ENV->set_thread_id_string()	Set thread of control ID format function
	 
	 
	 */
	 
}

/*********************************
*  defaultIsThreadAliveCallback  *
*********************************/

int RPbdb_Environment_internal_defaultIsThreadAliveCallback(	DB_ENV*			bdb_environment,
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

/******************************
*  errorfilePathForEnvironment  *
******************************/

//	environment home directory + RPBDB_DEFAULT_ENVIRONMENT_LOG_DIRECTORY + RPBDB_DEFAULT_ENVIRONMENT_LOG_FILE + RPBDB_DEFAULT_ENVIRONMENT_LOG_FILE_SUFFIX
char* RPbdb_Environment_internal_errorfilePathForEnvironment( RPbdb_Environment*		environment )	{
	
	//	get environment home directory
	char*	environment_home_directory		=	RPbdb_Environment_homeDirectory( environment );
	int		environment_directory_length	=	strlen( environment_home_directory );

	int		log_directory_length	=	strlen( RPBDB_DEFAULT_ENVIRONMENT_LOG_DIRECTORY );

	BOOL	logfile_needs_slash	=	FALSE;
	if (		log_directory_length
			&&	RPBDB_DEFAULT_ENVIRONMENT_LOG_DIRECTORY[ log_directory_length - 1 ] != '/' )	{

		logfile_needs_slash	=	TRUE;
	}

	int	return_path_length	=	environment_directory_length
													+	log_directory_length
													+ strlen( RPBDB_DEFAULT_ENVIRONMENT_LOG_FILE )
													+ strlen( RPBDB_DEFAULT_ENVIRONMENT_LOG_FILE_SUFFIX );
	
	char*	path_to_return	=	calloc( return_path_length + 1, sizeof( char ) );
	
	sprintf( path_to_return, "%s%s%s%s%s",	environment_home_directory,
																					RPBDB_DEFAULT_ENVIRONMENT_LOG_DIRECTORY,
																					( logfile_needs_slash ? "/" : "" ),
																					RPBDB_DEFAULT_ENVIRONMENT_LOG_FILE,
																					RPBDB_DEFAULT_ENVIRONMENT_LOG_FILE_SUFFIX );
	return path_to_return;
}

