/*
 *		RPbdb::DatabaseController::Database
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Database.h"
#include "Database_internal.h"

#include "Environment.h"

#include "ErrorController.h"

#include "DatabaseSequenceController.h"

#include "DatabaseController.h"
#include "DatabaseController_internal.h"
#include "DatabaseCursorController_internal.h"
#include "DatabaseJoinController.h"
#include "DatabaseCursorController.h"
#include "DatabaseCursor.h"

#include "ErrorController_internal.h"

#include "Record.h"
#include "Record_internal.h"
#include "Data.h"
#include "Key.h"
#include "DBT.h"
#include "SecondaryKeys.h"

#include "DBT_internal.h"

#include "TransactionController.h"
#include "TransactionController_internal.h"
#include "Transaction.h"
#include "Transaction_internal.h"

#include "SettingsController.h"
#include "DatabaseSettingsController.h"
#include "DatabaseAssociationSettingsController.h"
#include "DatabaseErrorSettingsController.h"
#include "DatabaseCacheSettingsController.h"
#include "DatabaseEncryptionSettingsController.h"
#include "DatabaseRecordFixedLengthSettingsController.h"
#include "DatabaseRecordReadWriteSettingsController.h"
#include "DatabaseTypeSettingsController.h"
#include "DatabaseTypeBtreeSettingsController.h"
#include "DatabaseTypeHashSettingsController.h"
#include "DatabaseTypeQueueSettingsController.h"
#include "DatabaseTypeRecnoSettingsController.h"
#include "DatabaseRecordSettingsController.h"
#include "DatabaseRecordVariableLengthSettingsController.h"
#include "FileSettingsController.h"

#include "DatabaseSettingsController.h"
#include "DatabaseVerificationSettingsController.h"
#include "DatabaseVerificationSettingsController_internal.h"
#include "DatabaseSettingsController_internal.h"
#include "DatabaseCachePrioritySettingsController_internal.h"
#include "DatabaseCursorSettingsController_internal.h"
#include "DatabaseRecordReadWriteSettingsController_internal.h"
#include "DatabaseTypeBtreeSettingsController_internal.h"
#include "DatabaseTypeHashSettingsController_internal.h"
#include "DatabaseTypeQueueSettingsController_internal.h"
#include "DatabaseTypeRecnoSettingsController_internal.h"

#include "MemoryPoolSettingsController.h"
#include "MemoryPoolReadWriteSettingsController.h"

#include "RuntimeStorageController.h"
#include "RuntimeStorageController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********
*  new  *
********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_class.html
RPbdb_Database* RPbdb_Database_new(	RPbdb_DatabaseController*	parent_database_controller,
																	char*											database_name )	{
	
	/*-----------*
	*  Instance  *
	*-----------*/

	RPbdb_Database*			new_database	= calloc( 1, sizeof( RPbdb_Database ) );

	new_database->record_number	=	1;

	/*------------------*
	*  Parent Database  *
	*------------------*/

  new_database->parent_database_controller = parent_database_controller;

	/*----------------------------*
	*  Local Settings Controller  *
	*----------------------------*/

	//	Make call to instantiate local settings controller
	RPbdb_Environment*											environment																	=	parent_database_controller->parent_environment;
	RPbdb_SettingsController*							settings_controller													=	RPbdb_Environment_settingsController( environment );
	RPbdb_DatabaseSettingsController*			environment_database_settings_controller		=	RPbdb_SettingsController_databaseSettingsController( settings_controller );
	
	new_database->settings_controller	=	RPbdb_DatabaseSettingsController_internal_copyOfSettingsControllerForInstance( environment_database_settings_controller );
	
	//	Set database as a parent (global settings controller is also a parent)
	new_database->settings_controller->parent_database = new_database;

	/*--------------*
	*  Open Status  *
	*--------------*/

	new_database->is_open					=	FALSE;
	new_database->has_associated	=	FALSE;

	/*-------*
	*  Type  *
	*-------*/
	
	//	Set a pointer to the database's type
	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( new_database->settings_controller );
	new_database->type	=	RPbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );
	
	/*---------*
	*  Name  *
	*---------*/

	//	Generally we need a name, but sometimes internally we pass NULL to set the name later
	new_database->name		=	strdup( database_name );
	
	/*-----------*
	*  Filename  *
	*-----------*/
	
	RPbdb_MemoryPoolSettingsController*						memory_pool_settings_controller							=	RPbdb_SettingsController_memoryPoolSettingsController( settings_controller );
	RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller	=	RPbdb_MemoryPoolSettingsController_readWriteSettingsController( memory_pool_settings_controller );
	
	if ( ! RPbdb_MemoryPoolReadWriteSettingsController_isInMemoryEnvironment( memory_pool_read_write_settings_controller ) )	{
	
		new_database->filename	=	RPbdb_Database_internal_filenameForName( new_database->name );		
	}
	
	/*---------------*
	*  Error Output  *
	*---------------*/

	#ifdef RPBDB_DEFAULT_DATABASE_LOG
		#if RPBDB_DEFAULT_DATABASE_LOG == TRUE
			if ( parent_database_controller->runtime_storage_database != NULL )	{
				RPbdb_DatabaseSettingsController*	database_settings_controller	=	RPbdb_Database_settingsController( new_database );
				RPbdb_DatabaseErrorSettingsController*	database_error_settings_controller	=	RPbdb_DatabaseSettingsController_errorSettingsController( database_settings_controller );
				
				if ( RPBDB_DEFAULT_DATABASE_LOG_TO_FILE )	{
					
					char*	log_file_path	=	RPbdb_Database_internal_errorfilePathForDatabase( new_database );
					
					RPbdb_DatabaseErrorSettingsController_setFileFromPath(	database_error_settings_controller,
																																log_file_path );
					free( log_file_path );
				}
				else {

					RPbdb_DatabaseErrorSettingsController_setFile(	database_error_settings_controller,
																												stderr );			
				}
			}
		#endif
	#endif

	/*-----------------------------*
	*  Runtime Storage Identifier  *
	*-----------------------------*/

	//	if parent database controller has a runtime storage database, store our address in it (remove when free)
	if ( parent_database_controller->runtime_storage_database != NULL )	{
		new_database->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_database_controller->runtime_storage_database,
																																										(void*) new_database );
	}
	else {
		new_database->runtime_identifier	=	FALSE;
	}

	return new_database;
}

/*********
*  free  *
*********/

void RPbdb_Database_free( RPbdb_Database** database )	{
	
	if ( ( *database )->parent_database_controller->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *database )->parent_database_controller->runtime_storage_database,
																											( *database )->runtime_identifier );
	}
	
	RPbdb_Database_internal_freeFromRuntimeStorage( database );
}

/***************************
*  freeFromRuntimeStorage  *
***************************/

void RPbdb_Database_internal_freeFromRuntimeStorage( RPbdb_Database** database )	{

	//	verification file
	if ( ( *database )->verification_file_is_open )	{
		fclose( ( *database )->verification_file );
		( *database )->verification_file_is_open	=	FALSE;
		( *database )->verification_file	=	NULL;
	}

	//	close join controller and cursors
	if ( ( *database )->join_controller != NULL )	{
		RPbdb_DatabaseJoinController_free( & ( ( *database )->join_controller ) );
	}

	//	close cursor controller and cursors
	if ( ( *database )->cursor_controller != NULL )	{
//		RPbdb_DatabaseCursorController_free( & ( ( *database )->cursor_controller ) );
	}

	//	close sequence controller and cursors
	if ( ( *database )->sequence_controller != NULL )	{
		RPbdb_DatabaseSequenceController_free( & ( ( *database )->sequence_controller ) );
	}
	
	//	if open, close
	if ( RPbdb_Database_isOpen( *database ) )	{
		RPbdb_Database_close( *database );
	}
	
	if ( ( *database )->settings_controller != NULL )	{
		RPbdb_DatabaseSettingsController_free( & ( ( *database )->settings_controller ) );
	}

	if ( ( *database )->index_name != NULL )	{
		free( ( *database )->index_name );
		( *database )->index_name	=	NULL;
	}

	if ( ( *database )->name != NULL )	{
		free( ( *database )->name );
		( *database )->name	=	NULL;
	}
	
	free( *database );
	*database	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_DatabaseSettingsController* RPbdb_Database_settingsController(	RPbdb_Database* database )	{

	return database->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_Database_parentEnvironment(	RPbdb_Database* database )	{
	return database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabaseController  *
***************************************/
RPbdb_DatabaseController* RPbdb_Database_parentDatabaseController(	RPbdb_Database* database )	{
	return database->parent_database_controller;
}

/*******************************************************************************************************************************************************************************************
																		Actions
*******************************************************************************************************************************************************************************************/

/*************
*  filename  *
*************/

char* RPbdb_Database_filename( RPbdb_Database* database )	{
	
	return database->filename;
}

/*********
*  name  *
*********/

char* RPbdb_Database_name( RPbdb_Database* database )	{
	
	return database->name;
}

/***********
*  rename  *
***********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_rename.html
void RPbdb_Database_rename(	RPbdb_Database*	database,
														char*						new_name )	{
	
	//	retain current db state from outside perspective
	BOOL	was_open	=	FALSE;
	if ( RPbdb_Database_isOpen( database ) )	{
		was_open	=	TRUE;
	}
	
	//	make sure database and related resources are closed
	RPbdb_Database_close( database );

	RPbdb_Environment*	environment	=	database->parent_database_controller->parent_environment;

	RPbdb_Transaction*	current_transaction	=	NULL;
	if ( environment->transaction_controller != NULL )	{
		current_transaction = RPbdb_TransactionController_currentTransaction( environment->transaction_controller );
	}
	
	RPbdb_DatabaseSettingsController*	database_settings_controller	=	RPbdb_Database_settingsController( database );
	int	rename_flags	=	RPbdb_DatabaseSettingsController_internal_renameFlags( database_settings_controller );

	char*	new_database_filename	=	RPbdb_Database_internal_filenameForName( new_name );

	int	connection_error	=	RP_NO_ERROR;
	if ( ( connection_error = environment->wrapped_bdb_environment->dbrename(	environment->wrapped_bdb_environment,
																																						( current_transaction == NULL ? NULL : current_transaction->wrapped_bdb_transaction ),
																																						database->filename,
																																						NULL,	/* no database because we don't allow multiple databases per file */
																																						(const char*) new_database_filename,
																																						rename_flags ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
																										connection_error, 
																										"Database_rename" );
	}

	database->name			= new_name;
	database->filename	=	new_database_filename;
	
	//	restore prior state
	if ( was_open == TRUE )	{
		RPbdb_Database_open( database );
	}
}

/*********
*  open  *
*********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
RPbdb_Database* RPbdb_Database_open( RPbdb_Database* database )	{
	
	//	Only open if we aren't already open
	if ( database->is_open == FALSE )	{

		RPbdb_Database_internal_openWithoutRuntimeStorage( database );

		RPbdb_RuntimeStorageController_internal_storeDatabaseForBDBDatabase(	RPbdb_RuntimeStorageController_sharedInstance(),
																																				database );
		
		//	if we are in a transaction and this is a primary database, add this database to the list of databases opened during transaction
		//	secondaries are closed by primary close, so no need to track them
		RPbdb_TransactionController*	transaction_controller	=	database->parent_database_controller->parent_environment->transaction_controller;
		RPbdb_Transaction* transaction_id	=	NULL;
		if (	transaction_controller != NULL
			&&	( transaction_id = RPbdb_TransactionController_currentTransaction( transaction_controller ) ) != NULL )	{

			RPbdb_Transaction_internal_addDatabaseToListOpenedDuringTransaction(	transaction_id,
																																					database );
		}
		
		//	if we previously opened and have secondaries defined, associate them now
		RPbdb_Database**	this_secondary_database	=	& database;
		while (		( *this_secondary_database )->secondary_database != NULL
			   &&	( this_secondary_database = &( ( *this_secondary_database )->secondary_database ) ) ) {
			
			//	create index with database (createIndex... should name the rest)
			RPbdb_Database_createSecondaryIndexWithDatabase(	database,
																											*this_secondary_database,
																											( *this_secondary_database )->index_name,
																											( *this_secondary_database )->secondary_key_creation_callback_method );
		}
	}

	return database;
}

/************
*  isOpen  *
************/

BOOL RPbdb_Database_isOpen( RPbdb_Database* database )	{
	
	return database->is_open;
}

/*************
*  close  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
void RPbdb_Database_close( RPbdb_Database* database )	{
	
	int	connection_error	=	RP_NO_ERROR;
	
	//	Only close if we're open
	if ( database->is_open == TRUE )	{
		
		RPbdb_RuntimeStorageController_internal_removeDatabaseStoredForBDBDatabase(	RPbdb_RuntimeStorageController_sharedInstance(),
																																								database );
		
		if ( database->join_controller != NULL )	{
			//	shut own join cursors
			RPbdb_DatabaseJoinController_closeAllCursors( database->join_controller );
		}
		
		if ( database->cursor_controller != NULL )	{
			//	Tell self's cursor controller to shut everything down
			RPbdb_DatabaseCursorController_closeAllCursors( database->cursor_controller );
		}

		if ( database->sequence_controller != NULL )	{
			//	Tell self's cursor controller to shut everything down
			RPbdb_DatabaseSequenceController_closeAllSequences( database->sequence_controller );
		}
		
		//	first, if this database is primary, close its secondary databases before closing self
		if ( RPbdb_Database_isPrimary( database ) )	{
			
      if ( database->secondary_database ) {
        RPbdb_Database_closeAllSecondaryDatabases( database );
        RPbdb_Database_freeAllSecondaryDatabases( database );
      }
		}
		
		RPbdb_Environment*	environment	=	database->parent_database_controller->parent_environment;
		
		RPbdb_DatabaseSettingsController*	database_settings_controller	=	RPbdb_Database_settingsController( database );
		
		uint32_t	close_flags	=	RPbdb_DatabaseSettingsController_internal_closeFlags( database_settings_controller );
		
		if ( ( connection_error	=	database->wrapped_bdb_database->close(	database->wrapped_bdb_database,
																																			close_flags ) ) )	{
			
			
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
																										connection_error, 
																										"Database_close" );
		}

		database->opened_in_transaction	=	FALSE;	
		database->is_open								=	FALSE;
		database->has_associated				=	FALSE;

		//	set wrapped db to null so we know that we need to create a new instance if we call open again
		database->wrapped_bdb_database	=	NULL;
	}
}

/**********
*  empty  *
**********/

uint32_t RPbdb_Database_empty( RPbdb_Database* database )	{

	RPbdb_Environment*	environment	=	database->parent_database_controller->parent_environment;

	RPbdb_Transaction*	current_transaction	=	NULL;
	if ( database->parent_database_controller->parent_environment->transaction_controller != NULL )	{
		RPbdb_TransactionController*	transaction_controller	=	RPbdb_Environment_transactionController( environment );
		current_transaction	=	RPbdb_TransactionController_currentTransaction( transaction_controller );
	}

	uint32_t	number_of_records_emptied	=	0;
	
	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{

		int	connection_error	=	RP_NO_ERROR;
		if ( ( connection_error = database->wrapped_bdb_database->truncate(	database->wrapped_bdb_database,
																																				( current_transaction ? current_transaction->wrapped_bdb_transaction : NULL ),
																																				& number_of_records_emptied,
																																				RPBDB_FUNCTION_HAS_NO_FLAGS ) ) )	{
		
				RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
																											connection_error, 
																											"Database_empty" );
		}
	}
	
	return number_of_records_emptied;
}

/*********
*  sync  *
*********/

void RPbdb_Database_sync( RPbdb_Database* database )	{

	int	connection_error	=	RP_NO_ERROR;
	if ( ( connection_error = database->wrapped_bdb_database->sync(	database->wrapped_bdb_database,
																																	RPBDB_FUNCTION_HAS_NO_FLAGS ) ) )	{
	
			RPbdb_Environment*	environment	=	database->parent_database_controller->parent_environment;
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
																										connection_error, 
																										"Database_sync" );
	}
}

/**********
*  erase  *
**********/

void RPbdb_Database_erase( RPbdb_Database* database )	{

	RPbdb_Environment*	environment	=	database->parent_database_controller->parent_environment;
	
	RPbdb_Database_close( database );

	RPbdb_Transaction*	current_transaction	=	NULL;
	if ( environment->transaction_controller != NULL )	{
		current_transaction = RPbdb_TransactionController_currentTransaction( environment->transaction_controller );
	}
	
	RPbdb_DatabaseSettingsController*	database_settings_controller	=	RPbdb_Database_settingsController( database );

	uint32_t	erase_flags	=	RPbdb_DatabaseSettingsController_internal_eraseFlags( database_settings_controller );

	int	connection_error	=	RP_NO_ERROR;
	if ( ( connection_error = environment->wrapped_bdb_environment->dbremove(	environment->wrapped_bdb_environment,
																																						( current_transaction == NULL ? NULL : current_transaction->wrapped_bdb_transaction ),
																																						database->filename,
																																						NULL,	/*	we force one db per file, so no db name	*/
																																						erase_flags ) ) )	{
	
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
																										connection_error, 
																										"Database_erase" );
	}
	
}

/*********************************
*  closeAllSecondaryDatabases  *
*********************************/

void RPbdb_Database_closeAllSecondaryDatabases( RPbdb_Database* database )	{

	if ( database->secondary_database != NULL )	{
		RPbdb_Database*	this_secondary_database	=	database->secondary_database;
		do {
			RPbdb_Database_close( this_secondary_database );
		}	while( ( this_secondary_database = this_secondary_database->secondary_database ) != NULL );
	}
}

/*********************************
*  freeAllSecondaryDatabases  *
*********************************/

void RPbdb_Database_freeAllSecondaryDatabases( RPbdb_Database* database )	{
	
	RPbdb_Database**	current_secondary_database	=	NULL;
	RPbdb_Database**	next_secondary_database     =	NULL;
	
	if ( database->secondary_database != NULL )	{
	
		current_secondary_database = &( database->secondary_database );
		
		//	for each database->secondary_database 
		do	{
      
			//	if secondary_database->secondary_database is set, save it
			if (		*current_secondary_database
					&&	( *current_secondary_database )->secondary_database != NULL )	{
				next_secondary_database	=	&( ( *current_secondary_database )->secondary_database );
			
			}

      //	free secondary_database
      RPbdb_Database_free( current_secondary_database );
      
			//	set secondary_database to saved secondary_database->secondary_database and repeat
			current_secondary_database = next_secondary_database;
			
		} while(		current_secondary_database != NULL
						&&	*current_secondary_database != NULL );
	}
}

/****************
*  associate  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_associate.html
//
//	Note that it is not safe to associate as a secondary database a name that is in use by another thread of control or has open cursors.
//
//	The callback parameter is a callback function that creates the set of secondary keys corresponding to a given primary key and data pair.
//
//	Callback can return:
//	- DB_DBT_APPMALLOC
//	- DB_DBT_MULTIPLE
//	- DB_DONOTINDEX
//
//	Secondary indices can be created manually by the application; there is no disadvantage, other than complexity, to doing so. 
//	However, when the secondary key can be mechanically derived from the primary key and datum that it points to, as is frequently the case, 
//	Berkeley DB can automatically and transparently manage secondary indices.
//
//	After a DB->associate call is made, the secondary indices become alternate interfaces to the primary database. 
//	All updates to the primary will be automatically reflected in each secondary index that has been associated with it.
//
//	It is generally unsafe, but not forbidden by Berkeley DB, to modify a database that has secondary indices without having those indices open and associated.
//	Similarly, it is generally unsafe, but not forbidden, to modify a secondary index directly. 
//	
//	If a secondary index becomes outdated for any reason, it should be discarded using the DB->remove method and a new one created using the DB->associate method. 
//	If a secondary index is no longer needed, all of its names should be closed using the DB->close method, and then the database should be removed 
//	using a new database name and the DB->remove method.
//
//	Closing a primary database name automatically dis-associates all secondary database names associated with it.
BOOL RPbdb_Database_associateSecondaryDatabase(	RPbdb_Database*		primary_database, 
																								RPbdb_Database*		secondary_database )	{

	//	we track database association (which must be done at each open) in database->has_associated
	//	when associate is called we check to see if the database has already associated with its primary
	//	when a database is closed that has secondaries, they are closed
	//	if the same db is re-opened, they are re-opened and re-associated automatically
	//	we can't associate twice
	if ( secondary_database->has_associated == TRUE )	{
		
		return FALSE;
	}

	RPbdb_Database_internal_ensureOpen( primary_database );
	RPbdb_Database_internal_ensureOpen( secondary_database );

	RPbdb_Environment*	environment	=	primary_database->parent_database_controller->parent_environment;

	//	store primary in secondary
	secondary_database->is_secondary		=	TRUE;	
	secondary_database->primary_database	=	primary_database;
			
	int			(*associate_callback)(	DB*, const DBT*, const DBT*, DBT*)	=	NULL;	

	//	If we have a callback method set, we will associate it with the secondary => primary relationship
	if ( secondary_database->secondary_key_creation_callback_method != NULL )	{
		
		//	If we have a secondary key creation callback method, we need to attach our own internal method to BDB's callback
		//	The internal callback will call the user-specified secondary key creation callback method. 
		associate_callback = & RPbdb_Database_internal_secondaryKeyCreationCallbackMethod;
	}
	else	{
		
		//	While it is not technically proper to leave the secondary_key_creation_callback_method NULL, it is allowable
		//	Manual creation of secondary keys is improper, but nevertheless possible. Applications that choose to do so in spite
		//	of recommendations are responsible for ensuring the secondary database does not become outdated. 
		associate_callback = NULL;
	}
	
	DB_TXN*	transaction_id	=	NULL;
	if ( primary_database->opened_in_transaction )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	RPbdb_DatabaseSettingsController*	database_settings_controller	=	RPbdb_Database_settingsController( secondary_database );
	uint32_t													associate_flags								=	RPbdb_DatabaseSettingsController_internal_associateFlags( database_settings_controller );
	
	//	If the secondary_database is not open, open it; if we can't open it, fail and raise an error
	int			connection_error	= RP_NO_ERROR;
	if ( ( connection_error = primary_database->wrapped_bdb_database->associate(	primary_database->wrapped_bdb_database,
																																								transaction_id,
																																								secondary_database->wrapped_bdb_database,
																																								associate_callback,
																																								associate_flags ) ) )	{
		
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( primary_database->parent_database_controller->parent_environment ),
																									connection_error, 
																									"Database_associateSecondaryDatabase" );
	}
	
	//	and secondary in primary
	//	we're currently storing secondary databases for the primary in a linked list
	//	when we associate a new secondary database we need to get the last in the chain and add the new one to it
	RPbdb_Database**	last_in_chain	=	NULL;
	last_in_chain = & primary_database;
	if ( *last_in_chain != NULL )	{
		//	navigate to end of chain
		BOOL	already_added	=	FALSE;
		while (		( *last_in_chain )->secondary_database != NULL 
			   &&	( last_in_chain = & ( ( *last_in_chain )->secondary_database ) ) )	{

			//	make sure we haven't already added this db
			if ( *last_in_chain == secondary_database )	{
				already_added = TRUE;
			}
		}
		
		if ( already_added == FALSE )	{
			( *last_in_chain )->secondary_database	=	secondary_database;
		}
	}

	secondary_database->has_associated		=	TRUE;
	
	return TRUE;
}

/********************
*  isPrimary  *
********************/

BOOL RPbdb_Database_isPrimary( RPbdb_Database*	database )	{
	
	return ! database->is_secondary;
}

/********************
*  isSecondary  *
********************/

BOOL RPbdb_Database_isSecondary( RPbdb_Database*	database )	{
	
	return database->is_secondary;
}

/***********************
*  secondaryIndexName  *
***********************/

char* RPbdb_Database_secondaryIndexName( RPbdb_Database*	database )	{
	
	return database->index_name;
}

/********************
*  primaryDatabase  *
********************/

RPbdb_Database* RPbdb_Database_primaryDatabase( RPbdb_Database*	secondary_database )	{
	return secondary_database->primary_database;
}

/********************************************
*  setSecondaryKeyCreationCallbackMethod  *
********************************************/

void RPbdb_Database_setSecondaryKeyCreationCallbackMethod(	RPbdb_Database*						secondary_database,
															RPbdb_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method )	{
	
	secondary_database->secondary_key_creation_callback_method		= secondary_key_creation_callback_method;
}

/****************************************
*  secondaryKeyCreationCallbackMethod  *
****************************************/

RPbdb_SecondaryKeyCallbackMethod RPbdb_Database_secondaryKeyCreationCallbackMethod(	RPbdb_Database*		secondary_database )	{
	
	return secondary_database->secondary_key_creation_callback_method;
}

/*************************
*  createSecondaryIndex  *
*************************/

RPbdb_Database* RPbdb_Database_createSecondaryIndex(	RPbdb_Database*						primary_database,
																										char*											index_name,
																										RPbdb_SecondaryKeyCallbackMethod	secondary_key_creation_callback_method)	{
	
	//	check to see if we already have a secondary database for this index_name
	//	if we do, make sure it's open
	//	if not, create it
	
	RPbdb_Database*	secondary_database	=	RPbdb_Database_databaseForSecondaryIndex(	primary_database,
																																									index_name );
	
	if ( secondary_database == NULL )	{
	
		RPbdb_Database*	secondary_database	=	RPbdb_Database_new(	primary_database->parent_database_controller,
																															index_name );
		
		RPbdb_Database_internal_configureDatabaseInstanceForSecondaryIndexOnPrimaryDatabase(	primary_database,
																																												secondary_database,
																																												index_name,
																																												FALSE,
																																												FALSE );
	}
	
	//	ensure database is working as secondary index on primary; if already configured, ignore gracefully
	RPbdb_Database_createSecondaryIndexWithDatabase(	primary_database,
																									secondary_database,
																									index_name,
																									secondary_key_creation_callback_method );
	return secondary_database;
}

/*************************
*  databaseForSecondaryIndex  *
*************************/

RPbdb_Database* RPbdb_Database_databaseForSecondaryIndex(	RPbdb_Database*		primary_database,
																												char*				index_name )	{
	
	//	walk through secondary databases on primary and see for each if it matches index_name, if it does return it
	RPbdb_Database**	this_database	=	NULL;
	if ( primary_database->secondary_database != NULL )	{
	
		this_database	=	&( primary_database->secondary_database );
		do {
			
			if ( ( *this_database )->index_name == index_name )	{
				return *this_database;
			}
			
		} while (	( *this_database )->secondary_database != NULL
				 &&	( this_database = &( ( *this_database )->secondary_database ) ) );
	}
	
	//	otherwise return NULL
	return NULL;
}

/*************************
*  createSecondaryIndex  *
*************************/

// FIX:
// when a database is opened the first time, secondary indexes have to be declared
// every time the database is opened after this we need to make sure the same indexes are declared
// the first time we open the database we store the secondary indexes in the database
// so all we have to do to ensure this is the case for the same database instance is to open secondary databases when a primary is re-opened
// but we also have the case of other instances of the same database being opened
// in that case, the new instance will not have secondary databases set already, so if it opens it will be opened out of sync
// we want to prevent this so that the secondary databases only have to be defined once (although this won't prevent them from being defined in multiple places)
// so the first time that a secondary database is defined its configuration should be added to a central storage location
// when an instance of this secondary database is created it should be duplicated from the first instance of the same database in the thread
// when an instance of the primary database is created it should automatically grab instances of the secondary databases kept in central storage
RPbdb_Database* RPbdb_Database_createSecondaryIndexWithDuplicates(	RPbdb_Database*										primary_database,
																																	char*															index_name,
																																	RPbdb_SecondaryKeyCallbackMethod		secondary_key_creation_callback_method)	{
	
	RPbdb_Database*	secondary_database	=	RPbdb_Database_new(	primary_database->parent_database_controller,
																														NULL );
	
	RPbdb_Database_internal_configureDatabaseInstanceForSecondaryIndexOnPrimaryDatabase(	primary_database,
																																											secondary_database,
																																											index_name,
																																											TRUE,
																																											FALSE );
	RPbdb_Database_createSecondaryIndexWithDatabase(	primary_database,
																									secondary_database,
																									index_name,
																									secondary_key_creation_callback_method );
	return secondary_database;
}

/*************************
*  createSecondaryIndex  *
*************************/

RPbdb_Database* RPbdb_Database_createSecondaryIndexWithSortedDuplicates(	RPbdb_Database*										primary_database,
																																				char*															index_name,
																																				RPbdb_SecondaryKeyCallbackMethod		secondary_key_creation_callback_method)	{
	
	RPbdb_Database*	secondary_database	=	RPbdb_Database_new(	primary_database->parent_database_controller,
																														NULL );
	
	RPbdb_Database_internal_configureDatabaseInstanceForSecondaryIndexOnPrimaryDatabase(	primary_database,
																																											secondary_database,
																																											index_name,
																																											TRUE,
																																											TRUE );
	RPbdb_Database_createSecondaryIndexWithDatabase(	primary_database,
																									secondary_database,
																									index_name,
																									secondary_key_creation_callback_method );
	return secondary_database;
}

/*************************
*  createSecondaryIndex  *
*************************/

void RPbdb_Database_createSecondaryIndexWithDatabase(	RPbdb_Database*										primary_database,
																											RPbdb_Database*										secondary_database,
																											char*															index_name,
																											RPbdb_SecondaryKeyCallbackMethod		secondary_key_creation_callback_method)	{
	
	//	We set the callback to our passed method
	RPbdb_Database_setSecondaryKeyCreationCallbackMethod(	secondary_database,
																												secondary_key_creation_callback_method );
	
	//	Set so that association with index automatically creates index for all existing records
	RPbdb_DatabaseAssociationSettingsController_turnSecondaryAssociationCreatesIndexOn( RPbdb_DatabaseSettingsController_associationSettingsController( secondary_database->settings_controller ) );
	
	//	Actually associate secondary database and update index of records for all existing records in primary
	RPbdb_Database_associateSecondaryDatabase(	primary_database,
																						secondary_database );
	
	secondary_database->index_name	=	strdup( index_name );
}

/*************************
*  cursorController  *
*************************/

RPbdb_DatabaseCursor* RPbdb_Database_cursor( RPbdb_Database* database )	{
	RPbdb_Database_internal_ensureOpen( database );
	return RPbdb_DatabaseCursorController_cursor( RPbdb_Database_cursorController( database ) );
}
	
/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/*************************
*  cursorController  *
*************************/

RPbdb_DatabaseCursorController* RPbdb_Database_cursorController( RPbdb_Database* database )	{

	if ( database->cursor_controller == NULL )	{
		database->cursor_controller = RPbdb_DatabaseCursorController_new( database );
	}
	return database->cursor_controller;
}

/**********************
*  joinController  *
**********************/

RPbdb_DatabaseJoinController* RPbdb_Database_joinController( RPbdb_Database* database )	{
	
	if ( database->join_controller == NULL )	{
		
		database->join_controller = RPbdb_DatabaseJoinController_new( database );
	}
	
	return database->join_controller;
}

/**********************
*  sequenceController  *
**********************/

RPbdb_DatabaseSequenceController* RPbdb_Database_sequenceController( RPbdb_Database* database )	{
	
	if ( database->sequence_controller == NULL )	{
		
		database->sequence_controller = RPbdb_DatabaseSequenceController_new( database );
	}
	
	return database->sequence_controller;
}

/*******************************************************************************************************************************************************************************************
																		Write Actions
*******************************************************************************************************************************************************************************************/

/**********************
*  write  *
**********************/

void RPbdb_Database_write(	RPbdb_Database*		database, 
													RPbdb_Record*			write_record )	{

	RPbdb_DatabaseSettingsController*									database_settings_controller						=	RPbdb_Database_settingsController(	database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller			=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	uint32_t	flags	=	RPbdb_DatabaseRecordReadWriteSettingsController_internal_writeFlags( database_record_read_write_settings_controller );

	RPbdb_Database_internal_writeRecord(	database,
																			flags,
																			write_record );
}

/**************************
*  writeKeyDataPair  *
**************************/

//	It is an error to attempt a partial put using the DB->put function in a database that supports duplicate records.
//	Partial puts in databases supporting duplicate records must be done using a DBcursor->put function.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
void RPbdb_Database_writeKeyDataPair(	RPbdb_Database*	database, 
																			RPbdb_Key*						write_key, 
																			RPbdb_Data*						write_data )	{

	RPbdb_DatabaseSettingsController*						database_settings_controller						=	RPbdb_Database_settingsController(	database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller			=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	uint32_t	flags	=	RPbdb_DatabaseRecordReadWriteSettingsController_internal_writeFlags( database_record_read_write_settings_controller );

	RPbdb_Database_internal_writeKeyDataPair(	database,
																						flags,
																						write_key,
																						write_data );
}	

/**************************
*  writeRawKeyDataPair  *
**************************/

//	It is an error to attempt a partial put using the DB->put function in a database that supports duplicate records.
//	Partial puts in databases supporting duplicate records must be done using a DBcursor->put function.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
RPbdb_Record* RPbdb_Database_writeRawKeyDataPair(	RPbdb_Database*		database, 
																							 void*							write_key, 
																							 uint32_t						key_size,
																							 void*							write_data,
																							 uint32_t						data_size	 )	{

	RPbdb_DatabaseSettingsController*						database_settings_controller						=	RPbdb_Database_settingsController(	database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller			=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	uint32_t	flags	=	RPbdb_DatabaseRecordReadWriteSettingsController_internal_writeFlags( database_record_read_write_settings_controller );

	return RPbdb_Database_internal_writeRawKeyDataPair(	database,
																											flags,
																											write_key,
																											key_size,
																											write_data,
																											data_size );
}

/***************************
*  appendRawKeyDataPair  *
***************************/

void RPbdb_Database_appendRawKeyDataPair(	RPbdb_Database*			database, 
																					void*								primary_key,
																					uint32_t						key_size,
																					void*								write_data,
																					uint32_t						data_size )	{

	RPbdb_DatabaseSettingsController*						database_settings_controller						=	RPbdb_Database_settingsController(	database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller			=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	uint32_t	flags	=	RPbdb_DatabaseRecordReadWriteSettingsController_internal_writeFlags( database_record_read_write_settings_controller );
	
	RPbdb_Database_internal_writeRawKeyDataPair(	database,
																							flags | DB_APPEND,
																							primary_key,
																							key_size,
																							write_data,
																							data_size );
}

/***************************
*  appendRawData  *
***************************/

db_recno_t RPbdb_Database_appendRawData(	RPbdb_Database*			database, 
																				void*								write_data,
																				uint32_t						data_size )	{
				
	RPbdb_DatabaseSettingsController*									database_settings_controller										=	RPbdb_Database_settingsController(	database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	uint32_t	flags	=	RPbdb_DatabaseRecordReadWriteSettingsController_internal_writeFlags( database_record_read_write_settings_controller );
	
	RPbdb_Record*	record	=		RPbdb_Database_internal_writeRawKeyDataPair(	database,
																																				flags | DB_APPEND,
																																				& database->record_number,
																																				sizeof( db_recno_t ),
																																				write_data,
																																				data_size );
	
	RPbdb_Record_free( & record );
	
	return database->record_number++;
}

/***************************
*  appendData  *
***************************/

db_recno_t RPbdb_Database_appendData(	RPbdb_Database*			database, 
																			RPbdb_Data*					write_data )	{
	
	RPbdb_DatabaseSettingsController*						database_settings_controller						=	RPbdb_Database_settingsController(	database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller			=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	uint32_t	flags	=	RPbdb_DatabaseRecordReadWriteSettingsController_internal_writeFlags( database_record_read_write_settings_controller );

	RPbdb_Key*	write_key	=	RPbdb_Key_new( NULL );
	RPbdb_Key_setRawData(	write_key,
										& database->record_number,
										sizeof( db_recno_t ) );

	RPbdb_Database_internal_writeKeyDataPair(	database,
																						flags | DB_APPEND,
																						write_key,
																						write_data );

	RPbdb_Key_free( & write_key );

	return database->record_number++;
}

/***************************
*  appendKeyDataPair  *
***************************/

db_recno_t RPbdb_Database_appendKeyDataPair(	RPbdb_Database*			database, 
																						RPbdb_Key*						primary_key,
																						RPbdb_Data*					write_data )	{
	
	RPbdb_DatabaseSettingsController*						database_settings_controller						=	RPbdb_Database_settingsController(	database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller			=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	uint32_t	flags	=	RPbdb_DatabaseRecordReadWriteSettingsController_internal_writeFlags( database_record_read_write_settings_controller );

	RPbdb_Database_internal_writeKeyDataPair(	database,
																						flags | DB_APPEND,
																						primary_key,
																						write_data );
	return database->record_number++;
}

/***************************
*  appendRecord  *
***************************/

db_recno_t RPbdb_Database_appendRecord(	RPbdb_Database*			database, 
																				RPbdb_Record*				record )	{
	
	RPbdb_DatabaseSettingsController*						database_settings_controller						=	RPbdb_Database_settingsController(	database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller			=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	uint32_t	flags	=	RPbdb_DatabaseRecordReadWriteSettingsController_internal_writeFlags( database_record_read_write_settings_controller );

	RPbdb_Database_internal_writeRecord(	database,
																			flags | DB_APPEND,
																			record );
	return database->record_number++;
}

/*******************************************************************************************************************************************************************************************
																		Key Retrieval
*******************************************************************************************************************************************************************************************/

/*******************
*  keyExists  *
*******************/

//	returns if the specified key appears in the database
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_exists.html	
BOOL RPbdb_Database_keyExists(	RPbdb_Database*		database,
															RPbdb_Key*					key_data )	{

	RPbdb_Database_internal_ensureOpen( database );

	int		connection_error	= 0;
	
	RPbdb_Environment*	environment	=	database->parent_database_controller->parent_environment;
	
	DB_TXN*	transaction_id	=	NULL;
	if ( database->opened_in_transaction )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}

	RPbdb_DatabaseSettingsController*						database_settings_controller						=	RPbdb_Database_settingsController(	database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller			=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	uint32_t	exists_flags	=	RPbdb_DatabaseRecordReadWriteSettingsController_internal_existsFlags( database_record_read_write_settings_controller );
	
	if ( ( connection_error = database->wrapped_bdb_database->exists(	database->wrapped_bdb_database,												
																																		transaction_id,
																																		key_data->wrapped_bdb_dbt,
																																		exists_flags ) ) )	{
		switch ( connection_error )	{
		
			case DB_NOTFOUND:
				return FALSE;
				break;
				
			case DB_KEYEMPTY:
				return RPBDB_EMPTY_KEY_EXISTS;
				break;
			
			default:				
				RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ),
																											connection_error, 
																											"Database_keyExists" );
				break;
		}
	}
	return TRUE;	
}

/********************
*  rawKeyExists  *
********************/

BOOL RPbdb_Database_rawKeyExists(	RPbdb_Database*	database,
																	void*						key_raw,
																	uint32_t				key_size )	{

	RPbdb_Key*	key	=	RPbdb_Key_new( NULL );
	RPbdb_Key_setRawData(	key,
												key_raw,
												key_size );
	return RPbdb_Database_keyExists(	database,
																	key );
}

/*******************************************************************************************************************************************************************************************
																		Data Retrieval
*******************************************************************************************************************************************************************************************/

/*****************************
*  retrieveRecord  *
*****************************/

//	Retrieval of duplicates requires the use of database_cursor operations.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
RPbdb_Record* RPbdb_Database_retrieveRecord(	RPbdb_Database*		database, 
																						RPbdb_Record*			record )	{
	
	return RPbdb_Database_internal_retrieveRecord(	database, 
																								RPBDB_NO_FLAGS, 
																								record );
}

/*****************************
*  retrieveKey  *
*****************************/

//	Retrieval of duplicates requires the use of database_cursor operations.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
RPbdb_Record* RPbdb_Database_retrieveKey(	RPbdb_Database*		database, 
																				RPbdb_Key*					key_data )	{

	RPbdb_Record*	record	=	RPbdb_Record_new( database );
	
	RPbdb_Record_setKey(	record,
											key_data );
	
	return RPbdb_Database_internal_retrieveRecord(	database, 
																								RPBDB_NO_FLAGS, 
																								record );
}

/******************************
*  retrieveRawKey  *
******************************/

//	DB_SET				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
//	Move the database_cursor to specified location
RPbdb_Record* RPbdb_Database_retrieveRawKey(	RPbdb_Database*		database, 
																						void*							key_raw,
																						uint32_t					key_size )	{

	return RPbdb_Database_internal_retrieveRawKeyDataPair(	database, 
																												RPBDB_NO_FLAGS, 
																												key_raw,
																												key_size, 
																												NULL,
																												0 );
}

/************************************************
*  retrieveMatchingRawKeyDataPair  *
************************************************/

//	DB_GET_BOTH				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
//	We need to add key specification here
RPbdb_Record* RPbdb_Database_retrieveMatchingRawKeyDataPair(	RPbdb_Database*		database,
																														void*							key_raw,
																														uint32_t					key_size,
																														void*							raw_data,
																														uint32_t					data_size )	{

	return RPbdb_Database_internal_retrieveRawKeyDataPair(	database, 
																												DB_GET_BOTH, 
																												key_raw,
																												key_size, 
																												raw_data,
																												data_size );
}

/*********************************************
*  retrieveMatchingKeyDataPair  *
*********************************************/

RPbdb_Record* RPbdb_Database_retrieveMatchingKeyDataPair(	RPbdb_Database*		database, 
																												RPbdb_Key*					key_data,
																												RPbdb_Data*				data )	{

	RPbdb_Record*	record	=	RPbdb_Record_new( database );
	
	RPbdb_Record_setKey(	record,
											key_data );
	RPbdb_Record_setData(	record,
												data );
	
	return RPbdb_Database_internal_retrieveRecord(	database, 
																								DB_GET_BOTH, 
																								record );
}

/*********************************************
*  retrieveMatchingRecord  *
*********************************************/

RPbdb_Record* RPbdb_Database_retrieveMatchingRecord(	RPbdb_Database*		database, 
																										RPbdb_Record*			record )	{

	return RPbdb_Database_internal_retrieveRecord(	database, 
																								DB_GET_BOTH, 
																								record );
}

/**************************************
*  retrieveRawRecordID  *
**************************************/

//	DB_SET_RECNO			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
//	Must be Btree created with Recnum
RPbdb_Record* RPbdb_Database_retrieveRawRecordID(	RPbdb_Database*		database,
																								db_recno_t*				record_id )	{

	return RPbdb_Database_internal_retrieveRawKeyDataPair(	database, 
																												DB_SET_RECNO,
																												record_id,
																												sizeof( uint32_t ),
																												NULL,
																												0 );
}

/**********************************
*  retrieveRecordID  *
**********************************/

RPbdb_Record* RPbdb_Database_retrieveRecordID(	RPbdb_Database*		database,
																							RPbdb_Key*					key_data_record_id )	{

	//	We should probably make sure here that record ID is an int

	RPbdb_Record*	record	=	RPbdb_Record_new( database );
	
	RPbdb_Record_setKey(	record,
											key_data_record_id );
	
	return RPbdb_Database_internal_retrieveRecord(	database, 
																								DB_SET_RECNO, 
																								record );
}

/*************************************
*  retrievePartialRawKey  *
*************************************/

//	FIX - these functions should be modified to return new cursors for their cursor counterparts
/*

RPbdb_Record* RPbdb_Database_retrievePartialRawKey(	RPbdb_Database*		database,
 																   				void*									key_raw )	{

	//	Make sure type is Btree
	
	//	Make sure was created with DB_RECNUM

	return RPbdb_Database_internal_retrieveRawKeyDataPair(	database, 
																				DB_SET_RANGE, 
																				key_raw, 
																				NULL );
}
*/
/************************************
*  retrievePartialKey  *
************************************/
/*
//	DB_SET_RANGE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
//	Must be Btree and it must have been created with the DB_RECNUM flag.
//	Permits partial key matches and range searches by returning the smallest item matching or including the key
RPbdb_Record* RPbdb_Database_retrievePartialKey(	RPbdb_Database*		database,
 																			RPbdb_Key*						partial_key )	{
	
	RPbdb_Record*	record	=	RPbdb_Record_new( database );
	
	RPbdb_Record_setKey(	record,
						partial_key );
	
	
	return RPbdb_Database_internal_retrieveRecord(	database, 
																		DB_SET_RANGE, 
																		record );
}
*/
/************************************
*  retrievePartialObject  *
************************************/
/*
//	DB_GET_BOTH_RANGE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
//	Permits partial data matches and range searches by returning the smallest item matching or including the data
RPbdb_Record* RPbdb_Database_retrievePartialData(	RPbdb_Database*		database,
 																				RPbdb_Data*						data )	{

	RPbdb_Record*	record	=	RPbdb_Record_new( database );
	
	RPbdb_Record_setData(	record,
						 data );
	
	return RPbdb_Database_internal_retrieveRecord(	database, 
																		DB_GET_BOTH_RANGE, 
																		record );
}
*/
/**************************************************
*  retrieveRawKeyPartialObjectPair  *
**************************************************/
/*
RPbdb_Record* RPbdb_Database_retrieveRawKeyPartialObjectPair(	RPbdb_Database*	database,
																							void*								key_raw,
																							void*								raw_data )	{

	return RPbdb_Database_internal_retrieveRawKeyDataPair(	database, 
																				DB_GET_BOTH_RANGE, 
																				key_raw, 
																				raw_data );
}
*/

/*******************************************************************************************************************************************************************************************
																		Btree Specific
*******************************************************************************************************************************************************************************************/

/*****************************
*  relativePositionOfKey  *
*****************************/
/*

//	returns an estimate of the proportion of keys that are less than, equal to, and greater than the specified key
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_key_range.html
//	Requires Btree
RPbdb_KeyRange* RPbdb_Database_relativePositionOfKey(	RPbdb_Database*	database,
 																		RPbdb_Key*							key_data )	{

 RPbdb_Database_internal_ensureOpen( database );

	DB_KEY_RANGE			key_range;
	int						connection_error	= 0;

	 DB_TXN*	transaction_id	=	NULL;
	 if ( database->opened_in_transaction )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	 }
 
	if ( ( connection_error = database->wrapped_bdb_database->key_range(	database->wrapped_bdb_database,												
																			tranaction_id,
																			key_data->wrapped_bdb_dbt,
																			& key_range,
																			RPbdb_Database_internal_keyRangeFlags() ) ) ) {

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_controller->parent_environment ),
												connection_error, 
												"Database_relativePositionOfRawKey" );
		return NULL;
	}
	return key_range;
}
*/
/*********************************
*  relativePositionOfRawKey  *
*********************************/
/*
RPbdb_KeyRange* RPbdb_Database_relativePositionOfRawKey(	RPbdb_Database*	database,
 																			void*				key_raw )	{

 RPbdb_Database_internal_ensureOpen( database );

}
*/
/*******************************************************************************************************************************************************************************************
																		Queue Specific
*******************************************************************************************************************************************************************************************/

/******************
*  shiftQueue  *
******************/
	
//	Only relevant for Queue databases
//	DB_CONSUME				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
RPbdb_Record* RPbdb_Database_shiftQueue( RPbdb_Database*	database, RPbdb_Record* record )	{
	
	RPbdb_Database_internal_ensureOpen( database );

	RPbdb_DatabaseSettingsController*			database_settings_controller			=	RPbdb_Database_settingsController( database );
	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
	DBTYPE																database_type											=	RPbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

	//	Make sure we have DBTYPE QUEUE
	if ( database_type != DB_QUEUE )	{
	
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ),
																									RP_ERROR_NOT_DB_QUEUE, 
																									"Database_shiftQueue" );
	}

	if ( record == NULL )	{
		record	=	RPbdb_Record_new( database );
	}
	if ( RPbdb_Database_internal_retrieveRecord(	database, 
																							DB_CONSUME, 
																							record )->result == FALSE )	{
		RPbdb_Record_free( & record );
	}
	//	if we have an empty key get the next queue
	//	this makes sense for queue, because we want the first available data
	else while( record->result == DB_KEYEMPTY )	{
		if ( RPbdb_Database_internal_retrieveRecord(	database, 
																								DB_CONSUME, 
																								record )->result == FALSE )	{
			RPbdb_Record_free( & record );
			break;
		}
	}
	return record;
}

/**************************
*  shiftQueueOrWait  *
**************************/

//	Only relevant for Queue databases
//	DB_CONSUME_WAIT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
RPbdb_Record* RPbdb_Database_shiftQueueOrWait( RPbdb_Database*	database, RPbdb_Record* record )	{

	RPbdb_DatabaseSettingsController*			database_settings_controller			=	RPbdb_Database_settingsController( database );
	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
	DBTYPE																database_type											=	RPbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

	//	Make sure we have DBTYPE QUEUE
	if ( database_type != DB_QUEUE )	{
	
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ),
																									RP_ERROR_NOT_DB_QUEUE, 
																									"Database_shiftQueueOrWait" );
	}
	
	if ( record == NULL )	{
		record	=	RPbdb_Record_new( database );
	}
	if ( RPbdb_Database_internal_retrieveRecord(	database, 
																							DB_CONSUME_WAIT, 
																							record )->result == FALSE )	{
		RPbdb_Record_free( & record );
	}
	//	if we have an empty key get the next queue
	//	this makes sense for queue, because we want the first available data
	else while( record->result == DB_KEYEMPTY )	{
		if ( RPbdb_Database_internal_retrieveRecord(	database, 
																								DB_CONSUME_WAIT, 
																								record )->result == FALSE )	{
			RPbdb_Record_free( & record );
			break;
		}
	}
	return record;
}

/*******************************************************************************************************************************************************************************************
																		Data Deletion
*******************************************************************************************************************************************************************************************/

/***************************
*  deleteRecord  *
***************************/

RPbdb_Database* RPbdb_Database_deleteRecord(	RPbdb_Database* 	database,
																						RPbdb_Record*		record )	{
	
	RPbdb_Database_internal_ensureOpen( database );

	RPbdb_Database_internal_prepareRecordForWriteRetrieveDelete(	database,
																															record,
																															FALSE );

	RPbdb_Environment*	environment	=	database->parent_database_controller->parent_environment;

	DB_TXN*	transaction_id	=	NULL;
	if ( database->opened_in_transaction )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}

	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	RPbdb_Record_settingsController( record );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );		
	uint32_t	delete_flags	=	RPbdb_DatabaseRecordReadWriteSettingsController_internal_deleteFlags( database_record_read_write_settings_controller );
	
	int				connection_error	= RP_NO_ERROR;
	if ( ( connection_error = database->wrapped_bdb_database->del(	database->wrapped_bdb_database,												
																																	transaction_id,
																																	record->key->wrapped_bdb_dbt,
																																	delete_flags ) ) ) {

		 RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ),
																																										connection_error, 
																																										"Database_deleteDataForKey" );
		 return NULL;
	 }
	
	return database;
}

/***************************
*  deleteDataForKey  *
***************************/

RPbdb_Database* RPbdb_Database_deleteDataForKey(	RPbdb_Database*		database,
																								RPbdb_Key*					deletion_key )	{

	RPbdb_Database_internal_ensureOpen( database );

	int				connection_error	= 0;

	RPbdb_Environment*	environment	=	database->parent_database_controller->parent_environment;

	DB_TXN*	transaction_id	=	NULL;
	if ( database->opened_in_transaction )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}

	RPbdb_DatabaseSettingsController*						database_settings_controller						=	RPbdb_Database_settingsController(	database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller			=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	uint32_t	delete_flags	=	RPbdb_DatabaseRecordReadWriteSettingsController_internal_deleteFlags( database_record_read_write_settings_controller ) ;
	
	if ( ( connection_error = database->wrapped_bdb_database->del(	database->wrapped_bdb_database,												
																																	transaction_id,
																																	deletion_key->wrapped_bdb_dbt,
																																	delete_flags ) ) ) {

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ),
																									connection_error, 
																									"Database_deleteDataForKey" );
		return NULL;
	}
	
	return database;
}

/*******************************
*  deleteDataForRawKey  *
*******************************/

//	Delete record for given key
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_del.html
RPbdb_Database* RPbdb_Database_deleteDataForRawKey(	RPbdb_Database* 	database,
																									void*								raw_deletion_key,
																									uint32_t							key_size )	{

	RPbdb_Key*	deletion_key	=	RPbdb_Key_new( NULL );
	
	RPbdb_Key_setRawData(	deletion_key,
												raw_deletion_key,
												key_size );

	return RPbdb_Database_deleteDataForKey(	database,
																					deletion_key );
}	

/*******************************************************************************************************************************************************************************************
																		Verification
*******************************************************************************************************************************************************************************************/

/***********
*  verify  *
***********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
RPbdb_Database* RPbdb_Database_verify( RPbdb_Database* database )	{

	int			opened_file_locally = FALSE;
	int			connection_error	= 0;
	
	//	If we have a file path but no file, open the file in the local scope and close it when we're done
	if ( !	database->verification_file 
		&&		database->verification_file_path )	{
		
		//	So we know if we should close it later
		opened_file_locally = TRUE;
		
		database->verification_file = fopen( database->verification_file_path, "w");

		if ( database->verification_file == NULL )	{
			RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ),
																				-1,
																				"Database_verify",
																				"Could not open file at path." );
			return NULL;
		}
	}
	
	RPbdb_DatabaseSettingsController*							database_settings_controller							=	RPbdb_Database_settingsController( database );
	RPbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller	=	RPbdb_DatabaseSettingsController_verificationSettingsController( database_settings_controller );

	if ( database->wrapped_bdb_database != NULL )	{

		uint32_t	verification_flags	=	RPbdb_DatabaseVerificationSettingsController_internal_verifyFlags( database_verification_settings_controller );

		if ( ( connection_error = database->wrapped_bdb_database->verify(	database->wrapped_bdb_database,
																																			database->filename, 
																																			database->name, 
																																			database->verification_file, 
																																			verification_flags ) ) ) {
			
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"DatabaseVerificationController_verify" );
			return NULL;
		}
	}

	//	If we opened the file locally we should close it too
	if ( opened_file_locally )	{
		fclose( database->verification_file );
	}

	//	If we verified the database without ordered check, set the flag so we can do ordered check
	if ( RPbdb_DatabaseVerificationSettingsController_skipOrderCheck( database_verification_settings_controller ) )	{
		
		RPbdb_DatabaseVerificationSettingsController_internal_hasDoneUnorderedCheck( database_verification_settings_controller, TRUE );
	}
	//	And if we complete an ordered check, reset our flag (no reason to do it twice in a row unless we start from the beginning). 
	else if ( RPbdb_DatabaseVerificationSettingsController_onlyOrderCheck( database_verification_settings_controller ) )	{
		
		RPbdb_DatabaseVerificationSettingsController_internal_hasDoneUnorderedCheck( database_verification_settings_controller, FALSE );
	}
	
	return database;		
}


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************************
*  ensureInitialized  *
***********************/

void RPbdb_Database_internal_ensureOpen( RPbdb_Database* database )	{

	if ( ! RPbdb_Database_isOpen( database ) )	{
		RPbdb_Database_open( database );
	}
}

/****************************
*  initWrappedDatabase  *
****************************/

//	This function initializes all settings for wrapped bdb instance that are set in rpbdb wrapper and must be set before database open
void RPbdb_Database_internal_initWrappedDatabase(	RPbdb_Database* database )	{
	
	RPbdb_Environment*	environment	=	database->parent_database_controller->parent_environment;
	
	RPbdb_SettingsController*						settings_controller						=	RPbdb_Environment_settingsController( environment );
	RPbdb_DatabaseSettingsController*		database_settings_controller	=	RPbdb_SettingsController_databaseSettingsController( settings_controller );
	
	uint32_t	create_flags	=	RPbdb_DatabaseSettingsController_internal_createFlags( database_settings_controller );

	int	connection_error	=	RP_NO_ERROR;
	if ( ( connection_error = db_create(	&( database->wrapped_bdb_database ), 
																				environment->wrapped_bdb_environment, 
																				create_flags ) ) )	{

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ),
																									connection_error, 
																									"Database_internal_initWrappedDatabase" );
	}
	
	//	We have to instantiate settings in our wrapped instance that are set in our rpbdb wrapper
	if (	database->settings_controller != NULL )	{
		
		RPbdb_DatabaseSettingsController*	database_settings_controller	=	database->settings_controller;
		
		//	DB->set_lorder()
		if ( database_settings_controller->little_endian )	{		
			RPbdb_DatabaseSettingsController_setByteOrderToLittleEndian( database_settings_controller );
		}
		else if ( database_settings_controller->big_endian	)	{
			RPbdb_DatabaseSettingsController_setByteOrderToBigEndian( database_settings_controller );
		}
		
		//	DB->set_pagesize()
		if ( database_settings_controller->pagesize )	{
			RPbdb_DatabaseSettingsController_setPageSize(	database_settings_controller,
																										database_settings_controller->pagesize );
		}
		
		if ( database_settings_controller->record_settings_controller != NULL )	{
			
			RPbdb_DatabaseRecordSettingsController*	database_record_settings_controller	=	database_settings_controller->record_settings_controller;
			
			if (	database_record_settings_controller->record_variable_length_settings_controller != NULL )	{
			
				RPbdb_DatabaseRecordVariableLengthSettingsController*	record_variable_length_settings_controller	=	database_record_settings_controller->record_variable_length_settings_controller;

				//	DB->set_re_delim()
				if ( record_variable_length_settings_controller->delimeter_byte )	{
					RPbdb_DatabaseRecordVariableLengthSettingsController_setDelimeterByte(	record_variable_length_settings_controller,
																																						record_variable_length_settings_controller->delimeter_byte );
				}
			}

			if (	database_record_settings_controller->record_fixed_length_settings_controller != NULL )	{

				RPbdb_DatabaseRecordFixedLengthSettingsController*	record_fixed_length_settings_controller	=	database_record_settings_controller->record_fixed_length_settings_controller;
				
				//	DB->set_re_len()
				if ( record_fixed_length_settings_controller->record_length )	{
					RPbdb_DatabaseRecordFixedLengthSettingsController_setRecordLength(	record_fixed_length_settings_controller,
																																			record_fixed_length_settings_controller->record_length );
				}
				
				//	DB->set_re_pad()
				if ( record_fixed_length_settings_controller->record_padding_byte )	{
					RPbdb_DatabaseRecordFixedLengthSettingsController_setPaddingByte(	record_fixed_length_settings_controller,
																																			record_fixed_length_settings_controller->record_padding_byte );
				}
			}

			if ( database_record_settings_controller->record_read_write_settings_controller != NULL )	{
				
				RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
				DBTYPE	database_type	=	RPbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );
				
				if ( database_type == DB_BTREE )	{
					//	DB->set_flags()
					RPbdb_DatabaseTypeBtreeSettingsController_internal_setFlags( RPbdb_DatabaseTypeSettingsController_btreeController( database_type_settings_controller ) );
				}
				else if ( database_type == DB_HASH )	{
					RPbdb_DatabaseTypeHashSettingsController_internal_setFlags( RPbdb_DatabaseTypeSettingsController_hashController( database_type_settings_controller ) );				
				}
			}
		}
		
		if (	database_settings_controller->type_settings_controller != NULL )	{

			RPbdb_DatabaseTypeSettingsController*	type_settings_controller	=	database_settings_controller->type_settings_controller;

			if ( type_settings_controller->btree_settings_controller != NULL )	{

				RPbdb_DatabaseTypeBtreeSettingsController*	btree_type_settings_controller	=	type_settings_controller->btree_settings_controller;
			
				//	DB->set_bt_minkey()
				if ( btree_type_settings_controller->minimum_keys_per_page )	{
					RPbdb_DatabaseTypeBtreeSettingsController_setMinimumKeysPerPage(	btree_type_settings_controller,
																																					btree_type_settings_controller->minimum_keys_per_page );
				}
			}
			if ( type_settings_controller->hash_settings_controller != NULL )	{
				
				RPbdb_DatabaseTypeHashSettingsController*	hash_type_settings_controller	=	type_settings_controller->hash_settings_controller;
				
				//	DB->set_flags()
				RPbdb_DatabaseTypeHashSettingsController_internal_setFlags( hash_type_settings_controller );
				
				//	DB->set_h_ffactor()
				if ( hash_type_settings_controller->density )	{
					RPbdb_DatabaseTypeHashSettingsController_setHashDensityFactor(	hash_type_settings_controller,
																																				hash_type_settings_controller->density );
				}
				
				//	DB->set_h_nelem()
				if ( hash_type_settings_controller->table_size )	{
					RPbdb_DatabaseTypeHashSettingsController_setTableSize(	hash_type_settings_controller,
																																hash_type_settings_controller->table_size );
				}
			}
			if ( type_settings_controller->recno_settings_controller != NULL )	{

				RPbdb_DatabaseTypeRecnoSettingsController*	recno_type_settings_controller	=	type_settings_controller->recno_settings_controller;
				
				//	DB->set_flags()
				RPbdb_DatabaseTypeRecnoSettingsController_internal_setFlags( recno_type_settings_controller );

				//	DB->set_re_source()
				if ( recno_type_settings_controller->source_file_path )	{
					RPbdb_DatabaseTypeRecnoSettingsController_setSourceFile(	recno_type_settings_controller,
																																	recno_type_settings_controller->source_file_path );
				}
			}
			if ( type_settings_controller->queue_settings_controller != NULL )	{

				RPbdb_DatabaseTypeQueueSettingsController*	queue_type_settings_controller	=	type_settings_controller->queue_settings_controller;
				
				//	DB->set_flags()
				RPbdb_DatabaseTypeQueueSettingsController_internal_setFlags( queue_type_settings_controller );
				
				//	DB->set_q_extentsize()
				if ( queue_type_settings_controller->number_of_pages_for_underlying_data )	{
					RPbdb_DatabaseTypeQueueSettingsController_setNumberOfPagesForUnderlyingData(	queue_type_settings_controller,
																																											queue_type_settings_controller->number_of_pages_for_underlying_data );
				}
			}
		}
		
		if ( database_settings_controller->cache_settings_controller != NULL )	{
		
			RPbdb_DatabaseCacheSettingsController*	cache_settings_controller	=	database_settings_controller->cache_settings_controller;
			
			//	DB->set_cachesize()
			if ( cache_settings_controller->max_size_in_bytes )	{
				RPbdb_DatabaseCacheSettingsController_setMaxSizeInBytes(	cache_settings_controller,
																																cache_settings_controller->max_size_in_bytes );
			}
			
			if ( cache_settings_controller->priority_settings_controller != NULL )	{
			
				RPbdb_DatabaseCachePrioritySettingsController*	cache_priority_settings_controller	=	cache_settings_controller->priority_settings_controller;

				//	DB->set_priority()
				if ( cache_priority_settings_controller->priority )	{
					RPbdb_DatabaseCachePrioritySettingsController_internal_setPriorityTo(	cache_priority_settings_controller,
																																								cache_priority_settings_controller->priority );
				}
			}
		}
		
		if ( database_settings_controller->encryption_settings_controller != NULL )	{
		
			RPbdb_DatabaseEncryptionSettingsController*	encryption_settings_controller	=	database_settings_controller->encryption_settings_controller;

			//	DB->set_encrypt()
			if ( encryption_settings_controller->password )	{
				RPbdb_DatabaseEncryptionSettingsController_turnEncryptionOn(	encryption_settings_controller,
																																		encryption_settings_controller->password	);
			}
		}
		
		if ( database_settings_controller->error_settings_controller != NULL )	{
		
			RPbdb_DatabaseErrorSettingsController*	error_settings_controller	=	database_settings_controller->error_settings_controller;

			//	DB->set_errfile()
			if ( error_settings_controller->error_file )	{
				RPbdb_DatabaseErrorSettingsController_setFile(	error_settings_controller,
																											error_settings_controller->error_file	);
			}
			
			//	DB->set_errpfx()
			if ( error_settings_controller->error_prefix )	{
				RPbdb_DatabaseErrorSettingsController_setPrefix(	error_settings_controller,
																												error_settings_controller->error_prefix	);
			}
		}
		
	}
	
	
	/*

	 //	FIX - may be called at any time, not implemented
	 DB->set_partition()	Set database partitioning
	 DB->set_msgfile(), DB->get_msgfile()	Set/get informational message FILE
	 
	 
	 //	FIX - may only be called before open, not implemented
	 DB->set_create_dir(), DB->get_create_dir()	Set/get the directory in which a database is placed
	 DB->set_partition_dirs(), DB->get_partition_dirs()	Set/get the directories used for database partitions
	 	 
	 Callbacks - not yet implemented
	 
	 //	DB->set_alloc()	Set local space allocation functions
	 //	DB->set_append_recno()	Set record append callback
	 //	DB->set_bt_compare()	Set a Btree comparison function
	 //	DB->set_bt_compress()	Set Btree compression functions
	 //	DB->set_dup_compare()	Set a duplicate comparison function
	 //	DB->set_errcall()	Set error message callback
	 //	DB->set_feedback()	Set feedback callback
	 //	DB->set_h_compare()	Set a Hash comparison function
	 //	DB->set_h_hash()	Set a hashing function
	 //	DB->set_msgcall()	Set informational message callback
	 //	DB->set_bt_prefix()	Set a Btree prefix comparison function
	 
	 */
}

/********************************************
*  secondaryKeyCreationCallbackMethod  *
*******************************************/

int RPbdb_Database_internal_secondaryKeyCreationCallbackMethod(	DB*						bdb_secondary_database, 
																																const DBT*		bdb_key, 
																																const DBT*		bdb_data, 
																																DBT*					bdb_return_data )	{
	
	//	Get our RPbdb database reference for this BDB instance
	RPbdb_Database*	secondary_database	= RPbdb_RuntimeStorageController_internal_databaseForBDBDatabase(	RPbdb_RuntimeStorageController_sharedInstance(),
																																																				bdb_secondary_database );
	
	RPbdb_Record*	record				= RPbdb_Record_internal_newFromKeyDBTDataDBT(	secondary_database,
																																						(DBT*) bdb_key,
																																						(DBT*) bdb_data	);

	//	This needs to be made to correspond to bdb_return_data
	RPbdb_SecondaryKeys*		secondary_keys			= (RPbdb_SecondaryKeys*) RPbdb_DBT_new( record );

	free( secondary_keys->wrapped_bdb_dbt );
	secondary_keys->wrapped_bdb_dbt	=	bdb_return_data;

	//	Call the user-specified callback function
	int	callback_method_return	=	secondary_database->secondary_key_creation_callback_method(	secondary_database,
																																														record,
																																														secondary_keys );
	
	switch ( callback_method_return )	{

		//	If the function was unable to create secondary keys it can optionally return this (no secondary keys will be created)
		case RPBDB_SECONDARY_KEY_CREATION_FAILED_DO_NOT_INDEX:
			return DB_DONOTINDEX;
			break;
			
		//	If the application allocated memory for the record							
		case RPBDB_RECORD_ALLOCATED_BY_APPLICATION:
			secondary_keys->wrapped_bdb_dbt->flags	|= DB_DBT_APPMALLOC;
			break;
			
		case RPBDB_RECORD_CONTAINS_MULTIPLE_SECONDARY_KEYS:
			secondary_keys->wrapped_bdb_dbt->flags	|=	DB_DBT_MULTIPLE;
			break;

		case RPBDB_RECORD_ALLOCATED_BY_APPLICATION_FOR_MULTIPLE_SECONDARY_KEYS:
			secondary_keys->wrapped_bdb_dbt->flags	|=	DB_DBT_APPMALLOC
													|	DB_DBT_MULTIPLE;
		case FALSE:
		default:
			break;
	}

	return FALSE;
}

void RPbdb_Database_internal_openWithoutRuntimeStorage( RPbdb_Database* database )	{

	RPbdb_Database_internal_initWrappedDatabase( database );

	RPbdb_Environment*	environment	=	database->parent_database_controller->parent_environment;
	
	//	we open in a transaction if the environment has an open transaction
	
	DB_TXN*	transaction_id	=	NULL;
	if ( environment->transaction_controller != NULL )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
		database->opened_in_transaction	=	TRUE;
	}
	
	RPbdb_SettingsController*			settings_controller				=	RPbdb_Environment_settingsController( environment );
	RPbdb_FileSettingsController*	file_settings_controller	=	RPbdb_SettingsController_fileSettingsController( settings_controller );
	
	uint32_t	file_creation_mode	=	RPbdb_FileSettingsController_fileCreationMode( file_settings_controller );
	
	RPbdb_DatabaseSettingsController*			database_settings_controller			=	RPbdb_Database_settingsController( database );
	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
	DBTYPE																database_type											=	RPbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );
	
	uint32_t	open_flags	=	RPbdb_DatabaseSettingsController_internal_openFlags( database_settings_controller );
	
	int		connection_error	= RP_NO_ERROR;
	if ( ( connection_error = database->wrapped_bdb_database->open(	database->wrapped_bdb_database, 
																																	transaction_id,
																																	database->filename,
																																	database->name,
																																	database_type,
																																	open_flags,
																																	file_creation_mode ) ) ) {
		
		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ),
																									connection_error, 
																									"Database_open" );
	}
	
	database->is_open	=	TRUE;
		
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Write Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/**************************
*  writeKeyDataPair  *
**************************/

RPbdb_Record* RPbdb_Database_internal_writeRawKeyDataPair(	RPbdb_Database*		database, 
																													uint32_t					flags,
																													void*							primary_key,
																													uint32_t					key_size,
																													void*							data,
																													uint32_t					data_size )	{

	RPbdb_Record*			record			= RPbdb_Record_new( database );
	
	RPbdb_Key_setRawData(	record->key,
										primary_key,
										key_size );

	RPbdb_Data_setRawData(	record->data,
											data,
											data_size );
	
	return RPbdb_Database_internal_writeRecord(	database,
																							flags,
																							record );
}

/***************************
*  writeKeyDataPair  *
***************************/

RPbdb_Record* RPbdb_Database_internal_writeKeyDataPair(		RPbdb_Database*		database, 
																												uint32_t					flags,
																												RPbdb_Key*					primary_key,
																												RPbdb_Data*				write_data )	{

	RPbdb_Record*	record	=	RPbdb_Record_internal_newFromKeyData(	database,
																																primary_key,
																																write_data);
	
	if ( RPbdb_Database_internal_writeRecord(	database,
																						flags,
																						record ) == NULL )	{
		RPbdb_Record_free( & record );
	}
	
	return record;
}


/*******************
*  writeData  *
*******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
RPbdb_Record* RPbdb_Database_internal_writeRecord(	RPbdb_Database*		database, 
																									uint32_t					flags,
																									RPbdb_Record*			record )	{
	
	RPbdb_Database_internal_ensureOpen( database );

	RPbdb_Database_internal_prepareRecordForWriteRetrieveDelete(	database,
																															record,
																															TRUE );

	RPbdb_Environment*	environment	=	database->parent_database_controller->parent_environment;

	DB_TXN*	transaction_id	=	NULL;
	if ( database->opened_in_transaction )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}

	int		connection_error	= RP_NO_ERROR;
	if ( ( connection_error = database->wrapped_bdb_database->put(	database->wrapped_bdb_database,
																																	transaction_id,
																																	record->key->wrapped_bdb_dbt,
																																	record->data->wrapped_bdb_dbt,
																																	flags ) ) ) {
		
		if ( connection_error != DB_KEYEXIST )	{
			record->result = FALSE;
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ), 
																										connection_error, 
																										"Database_internal_writeRecord" );
		}
	}
	else {
		record->result = TRUE;
	}
	
	return record;
}

/****************************************
*  prepareRecordForWriteRetrieveDelete  *
****************************************/

void RPbdb_Database_internal_prepareRecordForWriteRetrieveDelete(	RPbdb_Database*		database __attribute__ ((unused)), 
																																	RPbdb_Record*			record,
																																	BOOL							prepare_data_in_record )	{

	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	RPbdb_Record_settingsController( record );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	//	check and see if we are supposed to have key-type/data-footer
	//	if so, create/update as appropriate
	if ( RPbdb_DatabaseRecordReadWriteSettingsController_internal_hasFooter( database_record_read_write_settings_controller ) )	{
		RPbdb_Record_internal_createOrUpdateKeyTypeAndDataFooter(	record,
																															prepare_data_in_record );
	}
	
	//	check and see if we have store key typing
	//	if so, verify key type
	CerializeType	key_type;
	if ( ( key_type = RPbdb_DatabaseRecordReadWriteSettingsController_storeKeyTyping( database_record_read_write_settings_controller ) ) )	{
		RPbdb_DBT_internal_verifyKeyDataTyping(	(RPbdb_DBT*) record->key,
																						key_type );
	}
	//	check and see if we have store data typing
	//	if so, verify data type
	CerializeType	data_type;
	if ( ( data_type = RPbdb_DatabaseRecordReadWriteSettingsController_storeDataTyping( database_record_read_write_settings_controller ) ) )	{
		RPbdb_DBT_internal_verifyKeyDataTyping(	(RPbdb_DBT*) record->data,
																						data_type );
	}
	
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Retrieval Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/******************************
*  retrieveKeyDataPair  *
******************************/

//	Retrieves data using data->keyData->data as the key and copying data into data->data->data
//	The only difference between get and pget, so far as I can tell, is that pget also returns the primary key from the primary database
//	pget should never be used on a primary database
RPbdb_Record* RPbdb_Database_internal_retrieveRawKeyDataPair(	RPbdb_Database*			database, 
																														uint32_t						flag, 
																														void*								key,
																														uint32_t						key_size,
																														void*								data,
																														uint32_t						data_size )	{

	RPbdb_Record*		record		= RPbdb_Record_new( database );
	
	//	If we have data we're using to retrieve, load it into the DBT
	if ( data != NULL )	{
		
		RPbdb_Data_setRawData(	record->data,
												data,
												data_size );
	}

	if ( key != NULL )	{

		RPbdb_Key_setRawData(	record->key,
											key,
											key_size );

	}

	if (		RPbdb_Database_internal_retrieveRecord(	database,
																									flag,
																									record )->result == FALSE
			||	record->result == DB_KEYEMPTY )	{
		RPbdb_Record_free( & record );
	}
	return record;
}

/**************************
*  retrieveRecord  *
**************************/

//	FIX	- flag should also include supplemental flags by |'ing

RPbdb_Record* RPbdb_Database_internal_retrieveRecord(	RPbdb_Database*		database, 
																										uint32_t					flag, 
																										RPbdb_Record*			record )	{

	RPbdb_Database_internal_ensureOpen( database );

	RPbdb_Database_internal_prepareRecordForWriteRetrieveDelete(	database,
																															record,
																															( flag == DB_GET_BOTH ? TRUE : FALSE ) );

	RPbdb_Environment*				environment			= database->parent_database_controller->parent_environment;
	
	int	connection_error	= 0;

	DB_TXN*	transaction_id	=	NULL;
	if ( database->opened_in_transaction )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}

	//	If we have a secondary database we are using a secondary key and retrieving a primary key/data pair
	if ( RPbdb_Database_isSecondary( database ) )	{

		//	Get data via secondary key or throw error
		if ( ( connection_error = database->wrapped_bdb_database->pget(	database->wrapped_bdb_database, 
																																		transaction_id,
																																		record->key->wrapped_bdb_dbt, 
																																		record->primary_key->wrapped_bdb_dbt, 
																																		record->data->wrapped_bdb_dbt, 
																																		flag ) ) ) {

			if (	connection_error == DB_NOTFOUND )	{				
				record->result = FALSE;
			}
			else if ( connection_error == DB_KEYEMPTY )	{
				record->result = DB_KEYEMPTY;
			}
			else {
				
				RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ), 
																											connection_error, 
																											"Database_internal_retrieveRecord" );
			}
		}
		else {
			record->result = TRUE;
		}

	}
	//	Otherwise we are retrieving a primary key/data pair
	else	{
			
		if ( ( connection_error = ( database->wrapped_bdb_database->get(	database->wrapped_bdb_database, 
																																			transaction_id,
																																			record->key->wrapped_bdb_dbt, 
																																			record->data->wrapped_bdb_dbt, 
																																			flag ) ) ) ) {

			if (	connection_error == DB_NOTFOUND )	{				
				record->result = FALSE;
			}
			else if ( connection_error == DB_KEYEMPTY )	{
				record->result = DB_KEYEMPTY;
			}
			else {
				
				RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( environment ), 
																											connection_error, 
																											"Database_internal_retrieveRecord" );
			}
		}
		else {
			record->result = TRUE;
		}

		//	primary key is our retrieval key, so set both the same
		//	but if both are already the same, we've alredy done this - don't do it twice!
		if ( record->primary_key != record->key )	{
			RPbdb_Key_free( & record->primary_key );
			record->primary_key	=	record->key;
		}
		
	}

	//	if we have record typing, our records have a footer, so we need to note
	RPbdb_DatabaseSettingsController*									database_settings_controller										=	RPbdb_Database_settingsController( database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	if ( RPbdb_DatabaseRecordReadWriteSettingsController_recordTyping( database_record_read_write_settings_controller ) )	{
		record->data->has_footer = TRUE;
	}
	
	return record;
}

/**********************************
*  secondaryDatabaseNameForIndex  *
**********************************/

char* RPbdb_Database_internal_secondaryDatabaseNameForIndex( char* index_name,
																														char*	primary_database_name )	{
	
	int		secondary_database_name_length	=	( strlen( primary_database_name ) 
																				+ strlen( RPBDB_SECONDARY_DATABASE_INDEX_DELIMITER ) 
																				+ strlen( index_name ) );
																				
	char*	secondary_database_name	=	calloc( secondary_database_name_length + 1, sizeof( char ) );
	
	//	Our new secondary will be named primary_name__idx__index_name
	sprintf( secondary_database_name, "%s%s%s", primary_database_name, 
																							RPBDB_SECONDARY_DATABASE_INDEX_DELIMITER, 
																							index_name );
	return secondary_database_name;
}

/*************************************************************
*  createDatabaseInstanceForSecondaryIndexOnPrimaryDatabase  *
*************************************************************/

RPbdb_Database* RPbdb_Database_internal_configureDatabaseInstanceForSecondaryIndexOnPrimaryDatabase(	RPbdb_Database*		primary_database,
																																																		RPbdb_Database*		secondary_database,
																																																		char*							index_name,
																																																		BOOL							enable_duplicates,
																																																		BOOL							enable_sorted_duplicates )	{
														
	
	secondary_database->name			= RPbdb_Database_internal_secondaryDatabaseNameForIndex( index_name,
																																												primary_database->name);
	secondary_database->filename	=	RPbdb_Database_internal_filenameForName( secondary_database->name );		
	
	secondary_database->index_name				=	strdup( index_name );
	secondary_database->primary_database	=	primary_database;

	if ( enable_duplicates == TRUE )	{
		RPbdb_DatabaseSettingsController*									database_settings_controller										=	RPbdb_Database_settingsController( secondary_database );
		RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
		RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
		
		if ( enable_sorted_duplicates == TRUE )	{
			RPbdb_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOn( database_record_read_write_settings_controller );
		}
		else {
			RPbdb_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOn( database_record_read_write_settings_controller );			
		}
	}
	
	//	We're not doing config beyond here because this function only gets called internal
	//	to convenience functions that hide secondary databases entirely
	RPbdb_Database_open( secondary_database );
	//	and if the primary isn't open, open it now too
	//	since associate doesn't hold beyond close, any association implies open
	RPbdb_Database_open( primary_database );

	return secondary_database;
}

/********************
*  filenameForName  *
********************/

char* RPbdb_Database_internal_filenameForName( char* database_name )	{
	
		//	For some reason this is necessary to avoid trash from the string constant
	char* extension = strdup( RPBDB_DATABASE_FILENAME_EXTENSION );

	int		filename_length	=			strlen( database_name ) 
													+		1 
													+		1	/*  period  */
													+		strlen( extension )
													+		1;

	char* filename	=	calloc( filename_length, sizeof( char ) );

	//	Create database filename
	sprintf(	filename, 
						"%s.%s",		database_name, 
												extension );
	
	free( extension );
	
	return filename;
}


/**************************
*  initForRuntimeStorage  *
**************************/

RPbdb_Database* RPbdb_Database_internal_initForRuntimeStorage(	RPbdb_Database*		runtime_storage_database )	{
		
	RPbdb_DatabaseSettingsController*			database_settings_controller			=	RPbdb_Database_settingsController( runtime_storage_database );
	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
	
	//	Set the database type - Queue
	RPbdb_DatabaseTypeSettingsController_setTypeToQueue( database_type_settings_controller );	
	RPbdb_DatabaseRecordSettingsController*							database_record_settings_controller								=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordFixedLengthSettingsController*		database_record_fixed_length_settings_controller	=	RPbdb_DatabaseRecordSettingsController_fixedLengthSettingsController( database_record_settings_controller );

	//	set fixed record length to store pointer addresses
	RPbdb_DatabaseRecordFixedLengthSettingsController_setRecordLength(	database_record_fixed_length_settings_controller,
																																		sizeof( uintptr_t ) );

	//	Open the database with our settings
	RPbdb_Database_internal_openWithoutRuntimeStorage( runtime_storage_database );
	
	return runtime_storage_database;
}

/************************
*  storeRuntimeAddress  *
************************/

db_recno_t RPbdb_Database_internal_storeRuntimeAddress(	RPbdb_Database*	runtime_database,
																												void*						runtime_pointer )	{

	uintptr_t	runtime_pointer_address	=	(uintptr_t) runtime_pointer;

	db_recno_t	record_number	=	RPbdb_Database_appendRawData(	runtime_database,
																														& runtime_pointer_address,
																														sizeof( uintptr_t ) );
		
	return record_number;
}

/*****************************
*  freeStoredRuntimeAddress  *
*****************************/

void RPbdb_Database_internal_freeStoredRuntimeAddress(	RPbdb_Database*	runtime_database,
																											db_recno_t			runtime_record_number	)	{
	
	if ( RPbdb_Database_rawKeyExists(	runtime_database,
																		& runtime_record_number,
																		sizeof( db_recno_t ) ) )	{
		RPbdb_Database_deleteDataForRawKey(	runtime_database,
																				& runtime_record_number,
																				sizeof( db_recno_t ) );
	}
}

/***********************************
*  closeAllStoredRuntimeAddresses  *
***********************************/

void RPbdb_Database_internal_closeAllStoredRuntimeAddresses(	RPbdb_Database*	runtime_database,
																														void *close_function( void* )	)	{
	//	something is happening causing us to iterate our cursor database and close it along with the databases included in it
	RPbdb_DatabaseCursorController*	cursor_controller	=	RPbdb_DatabaseCursorController_internal_newWithoutRuntimeStorage( runtime_database );
	RPbdb_DatabaseCursor*						cursor						=	RPbdb_DatabaseCursor_new( cursor_controller );
	
	if ( RPbdb_DatabaseCursor_setToFirst( cursor )	)	{
	
		RPbdb_Record*	record	=	NULL;
		while ( ( record = RPbdb_DatabaseCursor_iterate( cursor, record ) ) )	{
			void**	rpbdb_instance	=	RPbdb_Record_rawData( record );
			//	call the RPbdb free function specified
			close_function( *rpbdb_instance );
		}
	}
	
	RPbdb_DatabaseCursor_free( & cursor );
}

/**********************************
*  freeAllStoredRuntimeAddresses  *
**********************************/

void RPbdb_Database_internal_freeAllStoredRuntimeAddresses(	RPbdb_Database*	runtime_database,
																														void *free_function( void** ) )	{

	RPbdb_Record*	record	=	NULL;
	while ( ( record = RPbdb_Database_shiftQueue( runtime_database, record ) ) != NULL )	{
		//	our raw data points to the address of a pointer
		void**	rpbdb_instance	=	RPbdb_Record_rawData( record );
		//	call the RPbdb free function specified
		free_function( rpbdb_instance );
	}
	
}

/***************************
*  errorfilePathForDatabase  *
***************************/

//	environment home directory + RPBDB_DEFAULT_DATABASE_LOG_IN_DIRECTORY + RPBDB_DEFAULT_DATABASE_LOG_FILE_SUFFIX
//	or
//	environment home directory + database filename + .err.log
char* RPbdb_Database_internal_errorfilePathForDatabase( RPbdb_Database* database )	{
	
	//	get environment home directory
	char*	environment_home_directory		=	RPbdb_Environment_homeDirectory( database->parent_database_controller->parent_environment );
	int		environment_directory_length	=	strlen( environment_home_directory );

	char*	path_to_return	=	NULL;
	
	if ( RPBDB_DEFAULT_DATABASE_LOG_IN_PLACE )	{
	
		int	return_path_length	=	environment_directory_length
														+	strlen( database->filename )
														+ strlen( RPBDB_DEFAULT_DATABASE_LOG_FILE_SUFFIX );
		
		path_to_return	=	calloc( return_path_length + 1, sizeof( char ) );
		
		sprintf( path_to_return, "%s%s%s",	environment_home_directory,
																				database->filename,
																				RPBDB_DEFAULT_DATABASE_LOG_FILE_SUFFIX );		
	}
	else {

		int		log_directory_length	=	strlen( RPBDB_DEFAULT_DATABASE_LOG_IN_DIRECTORY );

		BOOL	logfile_needs_slash	=	FALSE;
		if (		log_directory_length
				&&	RPBDB_DEFAULT_DATABASE_LOG_IN_DIRECTORY[ log_directory_length - 1 ] != '/' )	{

			logfile_needs_slash	=	TRUE;
		}

		int	directory_length	=	strlen( RPBDB_DEFAULT_DATABASE_LOG_IN_DIRECTORY );
		int	filename_length		=	strlen( database->filename );
		int	suffix_length			=	strlen( RPBDB_DEFAULT_DATABASE_LOG_FILE_SUFFIX );
		int	return_path_length	=	environment_directory_length
														+	directory_length
														+ (int) logfile_needs_slash
														+ filename_length
														+ suffix_length;
		
		path_to_return	=	calloc( return_path_length + 1, sizeof( char ) );
		
		sprintf( path_to_return, "%s%s%s%s%s",	environment_home_directory,
																						RPBDB_DEFAULT_DATABASE_LOG_IN_DIRECTORY,
																						( logfile_needs_slash ? "/" : "" ),
																						database->filename,
																						RPBDB_DEFAULT_DATABASE_LOG_FILE_SUFFIX );		
	}

	return path_to_return;
}
