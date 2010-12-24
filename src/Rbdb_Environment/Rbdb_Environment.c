/*
 *		Rbdb
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

#include "Rbdb_Environment.h"
#include "Rbdb_Environment_internal.h"

#include "Rbdb_DatabaseController.h"
#include "Rbdb_Database.h"
#include "Rbdb_DatabaseJoinController.h"

#include "Rbdb_ErrorController.h"
#include "Rbdb_LockController.h"
#include "Rbdb_LogController.h"
#include "Rbdb_MemoryPoolController.h"
#include "Rbdb_MutexController.h"
#include "Rbdb_ReplicationController.h"
#include "Rbdb_TransactionController.h"

#include "Rbdb_SettingsController.h"

#include "Rbdb_DatabaseCursorSettingsController.h"
#include "Rbdb_DatabaseTypeSettingsController.h"
#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DirectorySettingsController.h"
#include "Rbdb_DebugSettingsController.h"
#include "Rbdb_ErrorSettingsController.h"
#include "Rbdb_FileSettingsController.h"
#include "Rbdb_MemoryPoolSettingsController.h"
#include "Rbdb_MemoryPoolReadWriteSettingsController.h"
#include "Rbdb_MessageSettingsController.h"
#include "Rbdb_LockSettingsController.h"
#include "Rbdb_LockDeadlockDetectorSettingsController.h"
#include "Rbdb_LogSettingsController.h"
#include "Rbdb_TransactionSettingsController.h"
#include "Rbdb_ThreadSettingsController.h"
#include "Rbdb_DatabaseSequenceSettingsController.h"

#include "Rbdb_SettingsController_internal.h"
#include "Rbdb_LockDeadlockDetectorSettingsController_internal.h"
#include "Rbdb_LogSettingsController_internal.h"

#include "Rbdb_RuntimeStorageController.h"
#include "Rbdb_RuntimeStorageController_internal.h"

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

Rbdb_Environment* Rbdb_Environment_new(	char* environment_home_directory )	{

	Rbdb_Environment*	environment	=	calloc( 1, sizeof( Rbdb_Environment ) );

	environment->is_open			=	FALSE;

	int		directory_length	=	0;
	//	If no directory is specified we use current working directory
	if ( environment_home_directory == NULL )	{
		environment_home_directory	=	RBDB_DEFAULT_ENVIRONMENT_HOME_DIRECTORY;
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
	
	Rbdb_Environment_initDefaults( environment );
	
	return environment;
}

/*********
*  free  *
*********/

void Rbdb_Environment_free( Rbdb_Environment** environment )	{

	//	close and free transaction controller
	if ( ( *environment )->transaction_controller != NULL )	{
		
		//	If we have a transaction controller we need to close all databases so we can commit the transaction
		//	This is necessary because the databases were opened inside the transaction
		if ( ( *environment )->database_controller != NULL )	{
			Rbdb_DatabaseController_closeAllDatabases( ( *environment )->database_controller );
		}
		
		Rbdb_TransactionController_free( & ( ( *environment )->transaction_controller ) );
	}
	
	//	if the environment is open, close it
	if ( Rbdb_Environment_isOpen( *environment ) )	{
		Rbdb_Environment_close( *environment );
	}
	
	//	the order in which calls happen to free child objects is important

	//	free database controller and databases (close if necessary)
	if ( ( *environment )->database_controller != NULL )	{
		Rbdb_DatabaseController_free( & ( ( *environment )->database_controller ) );
	}

	//	free error controller
	if ( ( *environment )->error_controller != NULL )	{
		Rbdb_ErrorController_free( & ( ( *environment )->error_controller ) );
	}

	//	free memory pool controller
	if ( ( *environment )->memory_pool_controller != NULL )	{
		Rbdb_MemoryPoolController_free( & ( ( *environment )->memory_pool_controller ) );
	}
	
	//	free log controller and any open logs
	if ( ( *environment )->log_controller != NULL )	{
		Rbdb_LogController_free( & ( ( *environment )->log_controller ) );
	}
	
	//	free replication controller
	if ( ( *environment )->replication_controller != NULL )	{
		Rbdb_ReplicationController_free( & ( ( *environment )->replication_controller ) );
	}
	
	//	free mutex controller and mutexes
	if ( ( *environment )->mutex_controller != NULL )	{
		Rbdb_MutexController_free( & ( ( *environment )->mutex_controller ) );
	}
	
	//	free lock controller
	if ( ( *environment )->lock_controller != NULL )	{
		Rbdb_LockController_free( & ( ( *environment )->lock_controller ) );
	}
	
	//	free all environmental settings controllers
	if ( ( *environment )->settings_controller != NULL )	{
		Rbdb_SettingsController_free( & ( ( *environment )->settings_controller ) );
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

void Rbdb_Environment_initDefaults( Rbdb_Environment* environment )	{

	Rbdb_SettingsController*								settings_controller								=	Rbdb_Environment_settingsController( environment );
	Rbdb_ErrorSettingsController*						error_settings_controller					=	Rbdb_SettingsController_errorSettingsController( settings_controller );
//	Rbdb_DebugSettingsController*						debug_settings_controller					=	Rbdb_SettingsController_debugSettingsController( settings_controller );
	Rbdb_TransactionSettingsController*			transaction_settings_controller		=	Rbdb_SettingsController_transactionSettingsController( settings_controller );
	Rbdb_LogSettingsController*							log_settings_controller						=	Rbdb_SettingsController_logSettingsController( settings_controller );
	Rbdb_LockSettingsController*						lock_settings_controller					=	Rbdb_SettingsController_lockSettingsController( settings_controller );
	Rbdb_MemoryPoolSettingsController*			memory_pool_settings_controller		=	Rbdb_SettingsController_memoryPoolSettingsController( settings_controller );
	Rbdb_DirectorySettingsController*				directory_settings_controller			=	Rbdb_SettingsController_directorySettingsController( settings_controller );
	Rbdb_FileSettingsController*						file_settings_controller					=	Rbdb_SettingsController_fileSettingsController( settings_controller );
	Rbdb_ThreadSettingsController*					thread_settings_controller				=	Rbdb_SettingsController_threadSettingsController( settings_controller );
	Rbdb_DatabaseSettingsController*				database_settings_controller			=	Rbdb_SettingsController_databaseSettingsController( settings_controller );
	Rbdb_DatabaseTypeSettingsController*		database_type_settings_controller	=	Rbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
	Rbdb_DatabaseSequenceSettingsController*		database_sequence_settings_controller	=	Rbdb_DatabaseSettingsController_sequenceSettingsController( database_settings_controller );

	Rbdb_DatabaseCursorSettingsController*	database_cursor_settings_controller	=	Rbdb_DatabaseSettingsController_cursorSettingsController( database_settings_controller );

	//	we always want default cursor duplication to actually duplicate the cursor
	Rbdb_DatabaseCursorSettingsController_turnDuplicateRetainsLocationOn( database_cursor_settings_controller );

	#ifdef RBDB_DEFAULT_MEMORY_POOL_ON
		//	And make sure we actually have a memory pool
		Rbdb_MemoryPoolSettingsController_turnOn( memory_pool_settings_controller );
	#endif

	#ifdef RBDB_DEFAULT_TRANSACTION_DATA_STORE_ON
	

		Rbdb_TransactionSettingsController_turnOn( transaction_settings_controller );
		Rbdb_LogSettingsController_turnOn( log_settings_controller );
		Rbdb_LockSettingsController_turnOn( lock_settings_controller );

		//	Enable registration, checking for environmental failure, normal recovery
		//	DB_RECOVER
//		Rbdb_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOn( debug_settings_controller );

		//	DB_REGISTER, DB_ENV_FAILCHK
//		Rbdb_DebugSettingsController_turnRegisterForRecoveryOn( debug_settings_controller );
//		Rbdb_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOn( debug_settings_controller );
		
	#else
	
		#ifdef RBDB_DEFAULT_CONCURRENT_DATA_STORE_ON
			Rbdb_TransactionSettingsController_turnConcurrentDataStoreLockingOn( transaction_settings_controller );
		#endif
	
	#endif

	#ifdef RBDB_DEFAULT_SET_ENVIRONMENT_PATH_ON

		//	Set our environment home as our database directory
		if ( environment->directory != NULL )	{
			Rbdb_DirectorySettingsController_addDataDirectory(	directory_settings_controller,
																													environment->directory );
		}

	#endif
															
	#ifdef RBDB_DEFAULT_CREATE_IF_NECESSARY
		Rbdb_FileSettingsController_turnCreateIfNecessaryOn( file_settings_controller );
	#endif
	
	#ifdef RBDB_DEFAULT_TO_BTREE
		//	Unless otherwise specified, all of our runtime storage will be hash - set the environmental default
		Rbdb_DatabaseTypeSettingsController_setTypeToBTree( database_type_settings_controller );
	#endif
	
	#ifdef RBDB_MULTIPLE_ACCESS
		Rbdb_ThreadSettingsController_turnOn( thread_settings_controller );
	#endif

	#ifdef RBDB_DEFAULT_ENVIRONMENT_LOG
		#if RBDB_DEFAULT_ENVIRONMENT_LOG == TRUE
			if (		environment->directory 
					&&	environment->directory[0] != '\0' )	{			
				if ( RBDB_DEFAULT_ENVIRONMENT_LOG_TO_FILE )	{
					char*	log_file_path	=	Rbdb_Environment_internal_errorfilePathForEnvironment(	environment );
					Rbdb_ErrorSettingsController_setFileFromPath(	error_settings_controller,
																												log_file_path );
					free( log_file_path );
				}
				else {
					Rbdb_ErrorSettingsController_setFile(	error_settings_controller,
																								stderr );			
				}
			}
		#endif
	#endif

	Rbdb_DatabaseSequenceSettingsController_setAsIncreasing(			database_sequence_settings_controller );
	Rbdb_DatabaseSequenceSettingsController_setAsIncreasing(			database_sequence_settings_controller );
	Rbdb_DatabaseSequenceSettingsController_setInitialValue(			database_sequence_settings_controller, 0 );
	Rbdb_DatabaseSequenceSettingsController_setDefaultStepValue(	database_sequence_settings_controller, 1 );

}

/*************************
*  initForMemoryStorage  *
*************************/

Rbdb_Environment* Rbdb_Environment_initForStorageInMemory( Rbdb_Environment* environment )	{
	
	Rbdb_SettingsController*											settings_controller													=	Rbdb_Environment_settingsController( environment );
	Rbdb_LogSettingsController*										log_settings_controller											=	Rbdb_SettingsController_logSettingsController( settings_controller );
	Rbdb_MemoryPoolSettingsController*						memory_pool_settings_controller							=	Rbdb_SettingsController_memoryPoolSettingsController( settings_controller );
	Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller	=	Rbdb_MemoryPoolSettingsController_readWriteSettingsController( memory_pool_settings_controller );

	//	Don't allow writes to disk - use application memory for storage
	Rbdb_MemoryPoolReadWriteSettingsController_turnApplicationHasExclusiveAccessOn(	memory_pool_read_write_settings_controller );

	//	Don't use a temporary backing file for flushing memory	
	Rbdb_MemoryPoolReadWriteSettingsController_turnDoNotWriteToTemporaryBackingFileOn(	memory_pool_read_write_settings_controller );
		
	//	If log in memory is on, log in memory; otherwise, turn logging system off
	if ( ! Rbdb_LogSettingsController_logInMemory( log_settings_controller ) )	{

		//	If we're not logging in memory we don't want to log at all (because it would write to disk)
		Rbdb_LogSettingsController_turnOff(	log_settings_controller );
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
Rbdb_Environment* Rbdb_Environment_open( Rbdb_Environment* environment )	{

	if ( ! Rbdb_Environment_isOpen( environment ) )	{
					
		Rbdb_Environment_internal_initWrappedEnvironment( environment, FALSE );
						
		Rbdb_Environment_internal_openWithoutRuntimeStorage( environment );

		Rbdb_RuntimeStorageController_internal_storeEnvironmentForBDBEnvironment(	Rbdb_RuntimeStorageController_sharedInstance(),
																																							environment );
		environment->is_open	=	TRUE;
	}
		
	//	return environment
	return environment;
}

/***********
*  isOpen  *
***********/
	
BOOL Rbdb_Environment_isOpen( Rbdb_Environment* environment )	{
	return environment->is_open;
}

/******************
*  homeDirectory  *
******************/

char* Rbdb_Environment_homeDirectory( Rbdb_Environment* environment )	{
	return environment->directory;
}

/**********
*  close  *
**********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_close.html
Rbdb_Environment* Rbdb_Environment_close( Rbdb_Environment* environment )	{

	if ( environment->is_open )	{
	
		//	remove entry in runtime storage for this environment - we do this before closing so we have the bdb address, which is the key
		Rbdb_RuntimeStorageController_internal_removeStoredEnvironment(	Rbdb_RuntimeStorageController_sharedInstance(),
																																		environment );
		
		//	Tell all locks to release
		if ( environment->lock_controller != NULL )	{
			Rbdb_LockController_closeAllLocks( environment->lock_controller );
		}
		
		if ( environment->mutex_controller != NULL )	{
			//	Tell all mutex to release
			Rbdb_MutexController_closeAllMutexes( environment->mutex_controller );
		}
			
		if ( environment->transaction_controller != NULL )	{
			Rbdb_TransactionController_commitAllTransactions( environment->transaction_controller );
		}
		
		if ( environment->database_controller != NULL )	{
			//	Tell all databases to close (and to name their subsystems)
			Rbdb_DatabaseController_closeAllDatabases( environment->database_controller );
		}
		
		//	Close environment
		environment->wrapped_bdb_environment->close(	environment->wrapped_bdb_environment, 
														Rbdb_SettingsController_internal_closeFlags( Rbdb_Environment_settingsController( environment ) ) );

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
Rbdb_Environment* Rbdb_Environment_erase( Rbdb_Environment* environment )	{
	
	int connection_error	= 0;
	
	//	An environment that has been opened should not be used to erase
	//	We create a new wrapped environment instance to deal with it
	if ( Rbdb_Environment_isOpen( environment ) )	{
		Rbdb_Environment_close( environment );
	}

	//	whether or not our environment was opened we need a new environment instance to use for erase
	if ( ( connection_error = db_env_create(	&( environment->wrapped_bdb_environment ), 
																						Rbdb_SettingsController_internal_createFlags(	Rbdb_Environment_settingsController( environment ) ) ) ) ) {
		
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
																									connection_error, 
																									"Rbdb_Environment_erase" );
	}		
	
	int	flags	=	Rbdb_SettingsController_internal_eraseFlags( Rbdb_Environment_settingsController( environment ) );
	connection_error	= 0;
	if ( ( connection_error = environment->wrapped_bdb_environment->remove(	environment->wrapped_bdb_environment, 
																			environment->directory,
																			flags ) ) ) {
																					
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ), 
																									connection_error, 
																									"Rbdb_Environment_erase" );
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

void Rbdb_Environment_checkForEnvironmentFailure( Rbdb_Environment* environment )	{
	environment->wrapped_bdb_environment->failchk(	environment->wrapped_bdb_environment,
																									RBDB_NO_FLAGS );
}	

/***********
*  name  *
***********/

char* Rbdb_Environment_name( Rbdb_Environment* environment )	{
	return environment->name;
}
	
/**************
*  setName  *
**************/

void Rbdb_Environment_setName(	Rbdb_Environment*		environment,
																char*								name )	{
	environment->name	=	strdup( name );
}
	
/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/********************
*  errorController  *
********************/

Rbdb_ErrorController* Rbdb_Environment_errorController( Rbdb_Environment* environment )	{

	if (	! environment 
		||	! environment->error_controller )	{
		return Rbdb_ErrorController_new( environment );
	}
	
	return environment->error_controller;
}

/***********************
*  databaseController  *
***********************/

Rbdb_DatabaseController* Rbdb_Environment_databaseController( Rbdb_Environment* environment )	{

	if ( environment->database_controller == NULL )	{
		environment->database_controller = Rbdb_DatabaseController_new( environment );
	}
	
	return environment->database_controller;
}

/*******************
*  lockController  *
*******************/

Rbdb_LockController* Rbdb_Environment_lockController( Rbdb_Environment* environment )	{

	if ( ! environment->lock_controller )	{
		environment->lock_controller = Rbdb_LockController_new( environment );
	}
	
	return environment->lock_controller;	
}

/*************************
*  memoryPoolController  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get_mpf.html
Rbdb_MemoryPoolController* Rbdb_Environment_memoryPoolController( Rbdb_Environment* environment )	{

	if ( ! environment->memory_pool_controller )	{
		environment->memory_pool_controller = Rbdb_MemoryPoolController_new( environment );
	}
	
	return environment->memory_pool_controller;		
}

/********************
*  mutexController  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_unlock.html
Rbdb_MutexController* Rbdb_Environment_mutexController( Rbdb_Environment* environment )	{

	if ( ! environment->mutex_controller )	{
		environment->mutex_controller = Rbdb_MutexController_new( environment );
	}
	
	return environment->mutex_controller;			
}

/**************************
*  replicationController  *
**************************/

Rbdb_ReplicationController* 	Rbdb_Environment_replicationController( Rbdb_Environment* environment )	{

	if ( ! environment->replication_controller )	{
		environment->replication_controller = Rbdb_ReplicationController_new( environment );
	}
	
	return environment->replication_controller;	
}

/*********************
*  objectController  *
*********************/
/*
Rbdb_ObjectController* Rbdb_Environment_objectController( Rbdb_Environment* environment )	{

	if ( ! environment->object_controller )	{
		environment->object_controller = Rbdb_ObjectController_new( environment );
	}
	
	return environment->object_controller;	
}
*/

/*************************
*  controllerController  *
*************************/
/*
Rbdb_Controller* Rbdb_Environment_controllerController( Rbdb_Environment* environment )	{

	if ( ! environment->controller_controller )	{
		environment->controller_controller = Rbdb_controllerController_new( environment );
	}
	
	return environment->controller_controller;	
}
*/

/******************
*  logController  *
******************/

Rbdb_LogController* Rbdb_Environment_logController( Rbdb_Environment* environment )	{

	if ( ! environment->log_controller )	{
		environment->log_controller = Rbdb_LogController_new( environment );
	}
	
	return environment->log_controller;		
}

/*********************
*  statusController  *
*********************/
/*
Rbdb_StatusController* Rbdb_Environment_statusController( Rbdb_Environment* environment )	{

	if ( ! environment->status_controller )	{
		environment->status_controller = Rbdb_StatusController_new( environment );
	}
	
	return environment->status_controller;			
}
*/

/**************************
*  transactionController  *
**************************/

Rbdb_TransactionController* Rbdb_Environment_transactionController( Rbdb_Environment* environment )	{

	if ( ! environment->transaction_controller )	{
		environment->transaction_controller = Rbdb_TransactionController_new( environment );
	}
	
	return environment->transaction_controller;		
}

/***********************
*  settingsController  *
***********************/

Rbdb_SettingsController* Rbdb_Environment_settingsController( Rbdb_Environment* environment )	{

	if ( environment->settings_controller == NULL )	{
		environment->settings_controller = Rbdb_SettingsController_new( environment );
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

void Rbdb_Environment_internal_openWithoutRuntimeStorage( Rbdb_Environment* environment )	{

	int						connection_error	= 0;
	
	int	flags	=	Rbdb_SettingsController_internal_openFlags( Rbdb_Environment_settingsController( environment ) );
	int	mode	=	Rbdb_FileSettingsController_fileCreationMode( Rbdb_SettingsController_fileSettingsController( Rbdb_Environment_settingsController( environment ) ) );
	
	//	Create if necessary only creates the db; we have to create the directory if it doesn't yet exist
	if ( Rbdb_FileSettingsController_createIfNecessary( Rbdb_SettingsController_fileSettingsController( Rbdb_Environment_settingsController( environment ) ) )	 ){
		
		//	check whether the directory exists
		if( access( environment->directory, F_OK ) == -1 ) {		
			//	if it doesn't, create it
			mkdir(	environment->directory, S_IRWXU );
		}		
	}
	
	//	Open the environment itself (regardless of whether we had to create it on this call to Rbdb_open)
	if ( ( connection_error = environment->wrapped_bdb_environment->open(	environment->wrapped_bdb_environment, 
																																				environment->directory, 
																																				flags,
																																				mode ) ) ) {
																			
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ), 
														connection_error, 
														"Rbdb_Environment_internal_openWithoutRuntimeStorage" );
	}
	
	//	record that this environment has been opened
	environment->is_open = TRUE;
	
}

/***************************
*  initWrappedEnvironment  *
***************************/

void Rbdb_Environment_internal_initWrappedEnvironment(	Rbdb_Environment*		environment, 
																												BOOL								for_runtime_environment )	{
	
	//	if we don't have a wrapped_bdb_environment then we need to create one before we can open it
	//	FIX - if we created a new wrapped_bdb_environment then we need to make sure any settings
	//	are applied to the new one so that its creation is transparent.
	//	FIX - this probably means moving all settings to two layers, one where the Rbdb instance is set
	//	and one where the bdb instance is set (right before it opens)
	
	//	create bdb DB_ENV instance
	int	connection_error	=	RP_NO_ERROR;
	if ( ( connection_error = db_env_create(	&( environment->wrapped_bdb_environment ), 
																						Rbdb_SettingsController_internal_createFlags(	Rbdb_Environment_settingsController( environment ) ) ) ) ) {
		
		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( environment ),
														connection_error, 
														"Rbdb_Environment_internal_initWrappedEnvironment" );
	}
	
	//	now we have to set the wrapped bdb environment with all of our settings from our rbdb environment wrapper
	if (	for_runtime_environment == FALSE
		&&	environment->settings_controller != NULL )	{
	
		Rbdb_SettingsController*	settings_controller	=	environment->settings_controller;
	
		//	DB_ENV->set_flags()
		Rbdb_SettingsController_internal_setFlags( settings_controller );
		
		//	DB_ENV->set_verbose()
		Rbdb_SettingsController_internal_setVerbosity( settings_controller );

		//	DB_ENV->set_shm_key()
		if ( settings_controller->shm_key )	{
			Rbdb_SettingsController_setSHMkey(	settings_controller,
												settings_controller->shm_key );
		}
/*
		if ( settings_controller->debug_settings_controller != NULL )	{

			Rbdb_DebugSettingsController*	debug_settings_controller	=	settings_controller->debug_settings_controller;
			
		}
		*/
		if ( settings_controller->directory_settings_controller != NULL )	{

			Rbdb_DirectorySettingsController*	directory_settings_controller	=	settings_controller->directory_settings_controller;
			
			//	DB_ENV->add_data_dir()
			if ( directory_settings_controller->directories )	{
				Rbdb_Directory**	this_directory	=	NULL;
				this_directory	=	& ( directory_settings_controller->directories );
				do	{
					environment->wrapped_bdb_environment->add_data_dir(	environment->wrapped_bdb_environment, 
																		( *this_directory )->path );					
				}	while (		this_directory = & ( ( *this_directory)->next ), 
								*this_directory != NULL );				
			}
			
			//	DB_ENV->set_create_dir()
			if ( environment->create_directory )	{
				Rbdb_DirectorySettingsController_setCreateDirectory(	directory_settings_controller,
																		environment->create_directory );
			}
		}
		
		if ( settings_controller->error_settings_controller != NULL )	{
		
			Rbdb_ErrorSettingsController*	error_settings_controller	=	settings_controller->error_settings_controller;

			//	DB_ENV->set_errfile()
			if ( error_settings_controller->error_file )	{
				Rbdb_ErrorSettingsController_setFile(	error_settings_controller,
																							error_settings_controller->error_file );
			}	
			
			//	DB_ENV->set_errpfx()
			if ( error_settings_controller->prefix )	{
				Rbdb_ErrorSettingsController_setPrefix(	error_settings_controller,
																								error_settings_controller->prefix );
			}
			
		}
		
		if ( settings_controller->message_settings_controller != NULL )	{
		
			Rbdb_MessageSettingsController*	message_settings_controller	=	settings_controller->message_settings_controller;

			//	DB_ENV->set_msgfile()
			if ( message_settings_controller->message_file )	{
				Rbdb_MessageSettingsController_setFile(	message_settings_controller,
															message_settings_controller->message_file );
			}
		}
		
		if (	settings_controller->thread_settings_controller != NULL
			&&	Rbdb_LogSettingsController_on( settings_controller->log_settings_controller ) )	{
		
			Rbdb_ThreadSettingsController*	thread_settings_controller	=	settings_controller->thread_settings_controller;

			//	DB_ENV->set_thread_count()
			if ( thread_settings_controller->thread_count )	{
				Rbdb_ThreadSettingsController_setThreadCount(	thread_settings_controller,
																thread_settings_controller->thread_count );
			}
			
			if ( thread_settings_controller->is_thread_alive_callback_method )	{
				Rbdb_ThreadSettingsController_setIsThreadAliveCallback(	thread_settings_controller,
																																thread_settings_controller->is_thread_alive_callback_method	);
			}
		}
		
		if ( settings_controller->file_settings_controller != NULL )	{
		
			Rbdb_FileSettingsController*	file_settings_controller	=	settings_controller->file_settings_controller;

			//	DB_ENV->set_intermediate_dir_mode()
			if ( file_settings_controller->intermediate_directory_mode )	{
				Rbdb_FileSettingsController_setIntermediateDirectoryMode(	file_settings_controller,
																			file_settings_controller->intermediate_directory_mode );
			}
			
			//	DB_ENV->set_tmp_dir()
			if ( file_settings_controller->temp_directory )	{
				Rbdb_FileSettingsController_setTempDirectory(	file_settings_controller,
															  file_settings_controller->temp_directory );
			}
		}

		if (	settings_controller->lock_settings_controller != NULL
			&&	Rbdb_LockSettingsController_on( settings_controller->lock_settings_controller ) )	{
		
			Rbdb_LockSettingsController*	lock_settings_controller	=	settings_controller->lock_settings_controller;
			
			//	DB_ENV->set_timeout()
			if ( lock_settings_controller->timeout )	{
				Rbdb_LockSettingsController_setTimeout(	lock_settings_controller,
															lock_settings_controller->timeout );
			}
			
			if ( lock_settings_controller->conflict_matrix )	{
				//	DB_ENV->set_lk_conflicts()
				Rbdb_LockSettingsController_setConflictMatrix(	lock_settings_controller,
																lock_settings_controller->conflict_matrix );
			}
			
			if ( lock_settings_controller->max_lockers )	{
				//	DB_ENV->set_lk_max_lockers()
				Rbdb_LockSettingsController_setMaxLockers(	lock_settings_controller,
															lock_settings_controller->max_lockers );
			}
			
			
			if ( lock_settings_controller->max_locks )	{
				//	DB_ENV->set_lk_max_locks()
				Rbdb_LockSettingsController_setMaxLocks(	lock_settings_controller,
															lock_settings_controller->max_locks );
			}
				
			if ( lock_settings_controller->max_objects )	{
				//	DB_ENV->set_lk_max_objects()
				Rbdb_LockSettingsController_setMaxObjects(	lock_settings_controller,
															lock_settings_controller->max_objects );
			}
				
			if ( lock_settings_controller->partitions )	{
				//	DB_ENV->set_lk_partitions()
				Rbdb_LockSettingsController_setNumberOfPartitions(	lock_settings_controller,
																	lock_settings_controller->partitions );
			}
				
			if ( lock_settings_controller->deadlock_detector_settings_controller != NULL )	{

				Rbdb_LockDeadlockDetectorSettingsController*	deadlock_detector_settings_controller	=	lock_settings_controller->deadlock_detector_settings_controller;

				if ( deadlock_detector_settings_controller->deadlock_settings )	{
					//	DB_ENV->set_lk_detect()
					Rbdb_LockDeadlockDetectorSettingsController_internal_setTo(	deadlock_detector_settings_controller,
																					deadlock_detector_settings_controller->deadlock_settings	);
				}
			}
		}
		
		if (	settings_controller->transaction_settings_controller != NULL
			&&	Rbdb_TransactionSettingsController_on( settings_controller->transaction_settings_controller ) )	{
		
			Rbdb_TransactionSettingsController*	transaction_settings_controller	=	settings_controller->transaction_settings_controller;

			//	DB_ENV->set_timeout()
			if ( transaction_settings_controller->timeout_in_microseconds )	{
				Rbdb_TransactionSettingsController_setTimeoutInMicroseconds(	transaction_settings_controller,
																				transaction_settings_controller->timeout_in_microseconds );
			}
		}
		
		if (	settings_controller->log_settings_controller != NULL
			&&	Rbdb_LogSettingsController_on( settings_controller->log_settings_controller ) )	{
		
			Rbdb_LogSettingsController*	log_settings_controller	=	settings_controller->log_settings_controller;

			//	DB_ENV->log_set_config()
			Rbdb_LogSettingsController_internal_setLogConfig(	log_settings_controller );
			
			//	DB_ENV->set_lg_bsize()
			if ( log_settings_controller->buffer_size )	{
				Rbdb_LogSettingsController_setBufferSize(	log_settings_controller,
															log_settings_controller->buffer_size );
			}
			
			//	DB_ENV->set_lg_dir()
			if ( log_settings_controller->directory )	{
				Rbdb_LogSettingsController_setDirectory(	log_settings_controller,
															log_settings_controller->directory );
			}
			
			//	DB_ENV->set_lg_filemode()
			if ( log_settings_controller->mode )	{
				Rbdb_LogSettingsController_setMode(	log_settings_controller,
														log_settings_controller->mode );
			}
			
			//	DB_ENV->set_lg_max()
			if ( log_settings_controller->max_size )	{
				Rbdb_LogSettingsController_setMaxLogSize(	log_settings_controller,
															log_settings_controller->max_size );
			}
			
			//	DB_ENV->set_lg_regionmax()
			if ( log_settings_controller->max_region_size )	{
				Rbdb_LogSettingsController_setMaxRegionSize(	log_settings_controller,
																log_settings_controller->max_region_size );
			}
		}

		#ifdef RBDB_DEFAULT_FAILCHECK
			Rbdb_ThreadSettingsController_setThreadCount(	Rbdb_SettingsController_threadSettingsController( settings_controller ),
																										RBDB_DEFAULT_THREAD_COUNT );
			
			//	Set callback method for is_alive
			//	we have to call the internal function here rather than our own wrapper b/c at this point the bdb database has not been stored in runtime storage
			//	FIX - our wrapper function won't function at all for this reason
			//	i think the only way to fix this is to make the wrapper call from our internal function
			environment->wrapped_bdb_environment->set_isalive(	environment->wrapped_bdb_environment,
																													& Rbdb_Environment_internal_defaultIsThreadAliveCallback );	
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
	 Rbdb_ThreadSettingsController_setUniqueThreadIdentifierCallbackMethod
	 
	 DB_ENV->set_thread_id_string()	Set thread of control ID format function
	 
	 
	 */
	 
}

/*********************************
*  defaultIsThreadAliveCallback  *
*********************************/

int Rbdb_Environment_internal_defaultIsThreadAliveCallback(	DB_ENV*			bdb_environment,
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

//	environment home directory + RBDB_DEFAULT_ENVIRONMENT_LOG_DIRECTORY + RBDB_DEFAULT_ENVIRONMENT_LOG_FILE + RBDB_DEFAULT_ENVIRONMENT_LOG_FILE_SUFFIX
char* Rbdb_Environment_internal_errorfilePathForEnvironment( Rbdb_Environment*		environment )	{
	
	//	get environment home directory
	char*	environment_home_directory		=	Rbdb_Environment_homeDirectory( environment );
	int		environment_directory_length	=	strlen( environment_home_directory );

	int		log_directory_length	=	strlen( RBDB_DEFAULT_ENVIRONMENT_LOG_DIRECTORY );

	BOOL	logfile_needs_slash	=	FALSE;
	if (		log_directory_length
			&&	RBDB_DEFAULT_ENVIRONMENT_LOG_DIRECTORY[ log_directory_length - 1 ] != '/' )	{

		logfile_needs_slash	=	TRUE;
	}

	int	return_path_length	=	environment_directory_length
													+	log_directory_length
													+ strlen( RBDB_DEFAULT_ENVIRONMENT_LOG_FILE )
													+ strlen( RBDB_DEFAULT_ENVIRONMENT_LOG_FILE_SUFFIX );
	
	char*	path_to_return	=	calloc( return_path_length + 1, sizeof( char ) );
	
	sprintf( path_to_return, "%s%s%s%s%s",	environment_home_directory,
																					RBDB_DEFAULT_ENVIRONMENT_LOG_DIRECTORY,
																					( logfile_needs_slash ? "/" : "" ),
																					RBDB_DEFAULT_ENVIRONMENT_LOG_FILE,
																					RBDB_DEFAULT_ENVIRONMENT_LOG_FILE_SUFFIX );
	return path_to_return;
}

