/*
 *		RPDB::Database::DatabaseSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseSettingsController.h"

//	#include "RPDB_Compact.h"
#include "RPDB_ErrorController.h"
#include "RPDB_Database.h"
#include "RPDB_DatabaseErrorSettingsController.h"
#include "RPDB_DatabaseFixedRecordSettingsController.h"
#include "RPDB_DatabaseCacheSettingsController.h"
#include "RPDB_DatabaseAssociationSettingsController.h"
#include "RPDB_DatabaseCompactSettingsController.h"
#include "RPDB_DatabaseEncryptionSettingsController.h"
#include "RPDB_DatabaseTypeSettingsController.h"
#include "RPDB_DatabaseReadWriteSettingsController.h"
#include "RPDB_DatabaseCursorSettingsController.h"
#include "RPDB_SettingsController.h"
#include "RPDB_Environment.h"
#include "RPDB_DatabaseVerbositySettingsController.h"
#include "RPDB_DatabaseVerificationSettingsController.h"
#include "RPDB_DatabaseSequenceSettingsController.h"
#include "RPDB_DatabaseVariableRecordSettingsController.h"
#include "RPDB_DatabaseRecordSettingsController.h"
#include "RPDB_DatabaseJoinSettingsController.h"

#include "RPDB_DatabaseAssociationSettingsController.h"

#include "RPDB_TransactionSettingsController.h"
#include "RPDB_LockSettingsController.h"
#include "RPDB_LogSettingsController.h"
#include "RPDB_MemoryPoolSettingsController.h"
#include "RPDB_ReplicationSettingsController.h"
#include "RPDB_DebugSettingsController.h"
#include "RPDB_FileSettingsController.h"
#include "RPDB_ThreadSettingsController.h"

#include "RPDB_DatabaseVerbositySettingsController_internal.h"
#include "RPDB_DatabaseSequenceSettingsController_internal.h"
#include "RPDB_DatabaseReadWriteSettingsController_internal.h"
#include "RPDB_DatabaseCursorSettingsController_internal.h"
#include "RPDB_DatabaseVariableRecordSettingsController_internal.h"
#include "RPDB_DatabaseVerificationSettingsController_internal.h"
#include "RPDB_DatabaseRecordSettingsController_internal.h"

#include "RPDB_DatabaseSettingsController_internal.h"
#include "RPDB_DatabaseErrorSettingsController_internal.h"
#include "RPDB_DatabaseFixedRecordSettingsController_internal.h"
#include "RPDB_DatabaseCacheSettingsController_internal.h"
#include "RPDB_DatabaseAssociationSettingsController_internal.h"
#include "RPDB_DatabaseCompactSettingsController_internal.h"
#include "RPDB_DatabaseEncryptionSettingsController_internal.h"
#include "RPDB_DatabaseTypeSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseSettingsController* RPDB_DatabaseSettingsController_new( RPDB_SettingsController* settings_controller )	{

	RPDB_DatabaseSettingsController*		database_settings_controller = calloc( 1, sizeof( RPDB_DatabaseSettingsController ) );
	
	database_settings_controller->parent_settings_controller = settings_controller;

	return database_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseSettingsController_free(	RPDB_DatabaseSettingsController** database_settings_controller )	{

	if ( ( *database_settings_controller )->verification_settings_controller != NULL )	{
		RPDB_DatabaseVerificationSettingsController_free( & ( ( *database_settings_controller )->verification_settings_controller ) );
	}
	if ( ( *database_settings_controller )->error_settings_controller != NULL )	{
		RPDB_DatabaseErrorSettingsController_free( & ( ( *database_settings_controller )->error_settings_controller ) );
	}
	if ( ( *database_settings_controller )->variable_record_settings_controller != NULL )	{
		RPDB_DatabaseVariableRecordSettingsController_free( & ( ( *database_settings_controller )->variable_record_settings_controller ) );
	}
	if ( ( *database_settings_controller )->fixed_record_settings_controller != NULL )	{
		RPDB_DatabaseFixedRecordSettingsController_free( & ( ( *database_settings_controller )->fixed_record_settings_controller ) );
	}
	if ( ( *database_settings_controller )->read_write_settings_controller != NULL )	{
		RPDB_DatabaseReadWriteSettingsController_free( & ( ( *database_settings_controller )->read_write_settings_controller ) );
	}
	if ( ( *database_settings_controller )->cursor_settings_controller != NULL )	{
		RPDB_DatabaseCursorSettingsController_free( & ( ( *database_settings_controller )->cursor_settings_controller ) );
	}
	if ( ( *database_settings_controller )->sequence_settings_controller != NULL )	{
		RPDB_DatabaseSequenceSettingsController_free( & ( ( *database_settings_controller )->sequence_settings_controller ) );
	}
	if ( ( *database_settings_controller )->verbosity_settings_controller != NULL )	{
		RPDB_DatabaseVerbositySettingsController_free( & ( ( *database_settings_controller )->verbosity_settings_controller ) );
	}
	if ( ( *database_settings_controller )->compact_settings_controller != NULL )	{
		RPDB_DatabaseCompactSettingsController_free( & ( ( *database_settings_controller )->compact_settings_controller ) );
	}
	if ( ( *database_settings_controller )->cache_settings_controller != NULL )	{
		RPDB_DatabaseCacheSettingsController_free( & ( ( *database_settings_controller )->cache_settings_controller ) );
	}
	if ( ( *database_settings_controller )->encryption_settings_controller != NULL )	{
		RPDB_DatabaseEncryptionSettingsController_free( & ( ( *database_settings_controller )->encryption_settings_controller ) );
	}
	if ( ( *database_settings_controller )->association_settings_controller != NULL )	{
		RPDB_DatabaseAssociationSettingsController_free( & ( ( *database_settings_controller )->association_settings_controller ) );
	}
	if ( ( *database_settings_controller )->type_settings_controller != NULL )	{
		RPDB_DatabaseTypeSettingsController_free( & ( ( *database_settings_controller )->type_settings_controller ) );
	}
	if ( ( *database_settings_controller )->record_settings_controller != NULL )	{
		RPDB_DatabaseRecordSettingsController_free( & ( ( *database_settings_controller )->record_settings_controller ) );
	}
	
	free( *database_settings_controller );
	*database_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseSettingsController_parentEnvironment(	RPDB_DatabaseSettingsController* database_settings_controller )	{
	return database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseSettingsController_parentDatabase(	RPDB_DatabaseSettingsController* database_settings_controller )	{
	return database_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/****************
*  checksum  *
****************/

//	DB_CHKSUM				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
int RPDB_DatabaseSettingsController_checksum( RPDB_DatabaseSettingsController* database_settings_controller )	{
	if ( database_settings_controller->checksum == TRUE )	{
		return DB_CHKSUM;
	}
	return FALSE;
}

	/************************
	*  turnChecksumOn  *
	************************/

	//	DB_CHKSUM				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
	void RPDB_DatabaseSettingsController_turnChecksumOn( RPDB_DatabaseSettingsController* database_settings_controller )	{
		database_settings_controller->checksum = TRUE;
	}

	/************************
	*  turnChecksumOff  *
	************************/

	//	DB_CHKSUM				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
	void RPDB_DatabaseSettingsController_turnChecksumOff( RPDB_DatabaseSettingsController* database_settings_controller )	{
		database_settings_controller->checksum = FALSE;
	}

/*************
*  logs  *
*************/

//	DB_TXN_NOT_DURABLE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
int RPDB_DatabaseSettingsController_transactionDurability( RPDB_DatabaseSettingsController* database_settings_controller )	{
	if ( database_settings_controller->transaction_durability_off == TRUE )	{
		return DB_TXN_NOT_DURABLE;
	}
	return FALSE;
}

	/******************
	*  turnLogsOn  *
	******************/

	//	DB_TXN_NOT_DURABLE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
	void RPDB_DatabaseSettingsController_turnTransactionDurabilityOn( RPDB_DatabaseSettingsController* database_settings_controller )	{
		database_settings_controller->transaction_durability_off = TRUE;
	}

	/********************
	*  turnLogsOff  *
	********************/

	//	DB_TXN_NOT_DURABLE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
	void RPDB_DatabaseSettingsController_turnTransactionDurabilityOff( RPDB_DatabaseSettingsController* database_settings_controller )	{
		database_settings_controller->transaction_durability_off = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/****************
*  pagesize  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_pagesize.html
uint32_t RPDB_DatabaseSettingsController_pagesize( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_Database*	database = database_settings_controller->parent_database;
	
	int				connection_error	= 0;

	//	If it's already set we don't need to grab it - it is up to date
	if (	database_settings_controller->pagesize == 0
		&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->get_pagesize(	database->wrapped_bdb_database, 
																				&( database_settings_controller->pagesize ) ) ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"RPDB_DatabaseType" );
		}
	}
	
	return database_settings_controller->pagesize;
}

/********************
*  setPageSize  *
********************/

void RPDB_DatabaseSettingsController_setPageSize(	RPDB_DatabaseSettingsController*	database_settings_controller, 
																									uint32_t							pagesize )	{

	RPDB_Database*	database = database_settings_controller->parent_database;

	int			connection_error	= RP_NO_ERROR;

	database_settings_controller->pagesize = pagesize;

	if ( database->wrapped_bdb_database != NULL )	{
		if ( ( connection_error = database->wrapped_bdb_database->set_pagesize(	database->wrapped_bdb_database, 
																																						pagesize ) ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"RPDB_DatabaseType" );
		}
	}
}

/*********************
*  isBigEndian  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_lorder.html
//	Byte order for stored integers in database
BOOL RPDB_DatabaseSettingsController_isBigEndian( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_Database*	database = database_settings_controller->parent_database;

	int			load_order;
	
	int			connection_error	= 0;

	if (	! database_settings_controller->little_endian
		&&	! database_settings_controller->big_endian
		&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->get_lorder(	database->wrapped_bdb_database, 
																				& load_order )) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"RPDB_DatabaseType" );
		}

		database_settings_controller->big_endian = load_order == 4321 ? TRUE : FALSE;
	}	
	
	return database_settings_controller->big_endian;	
}

/*********************************
*  setByteOrderToBigEndian  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_lorder.html
//	Byte order for stored integers in database
void RPDB_DatabaseSettingsController_setByteOrderToBigEndian( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_Database*	database = database_settings_controller->parent_database;
	
	int			connection_error	= 0;

	database_settings_controller->big_endian = TRUE;
	database_settings_controller->little_endian = FALSE;

	if ( database->wrapped_bdb_database != NULL )	{
		if ( ( connection_error = database->wrapped_bdb_database->set_lorder(	database->wrapped_bdb_database,
																				4321 )) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"RPDB_DatabaseType" );
		}
	}
}

/*********************
*  isLittleEndian  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_lorder.html
//	Byte order for stored integers in database
BOOL RPDB_DatabaseSettingsController_isLittleEndian( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_Database*	database = database_settings_controller->parent_database;

	int			load_order;

	int			connection_error	= 0;

	if (	! database_settings_controller->little_endian
		&&	! database_settings_controller->big_endian
		&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->get_lorder(	database->wrapped_bdb_database, 
																				& load_order ) ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"RPDB_DatabaseType" );
		}
		database_settings_controller->little_endian = load_order == 1234 ? TRUE : FALSE;
	}

	return database_settings_controller->little_endian;	
}

/*************************************
*  setByteOrderToLittleEndian  *
*************************************/

void RPDB_DatabaseSettingsController_setByteOrderToLittleEndian( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_Database*	database = database_settings_controller->parent_database;
	
	int			connection_error	= 0;

	database_settings_controller->little_endian = TRUE;
	database_settings_controller->big_endian = FALSE;

	if ( database->wrapped_bdb_database != NULL )	{
		if ( ( connection_error = database->wrapped_bdb_database->set_lorder(	database->wrapped_bdb_database, 
																				1234 ) ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"RPDB_DatabaseType" );
		}
	}
}

/********************
*  isByteswapped  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get_byteswapped.html
BOOL RPDB_DatabaseSettingsController_isByteswapped( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_Database*	database = database_settings_controller->parent_database;
	
	int			connection_error	= 0;

	if ( database->wrapped_bdb_database != NULL)	{

		if ( ( connection_error = database->wrapped_bdb_database->get_byteswapped(	database->wrapped_bdb_database, 
																					(int*) &( database_settings_controller->is_byteswapped ) )) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"RPDB_DatabaseType" );
		}
	}
	
	return database_settings_controller->is_byteswapped;
}

/*****************
*  maxSizeIn  *
*****************/

//	Return the maximum size possible for the database given page size, etc. 
//	http://www.oracle.com/technology/documentation/berkeley-db/db/ref/am_misc/dbsizes.html
//	Not a built in function - we will have to get page size, etc. in order to calculate.
int RPDB_DatabaseSettingsController_maxSizePageIn( RPDB_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	
	//	FIX
	return 0;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/********************************
*  errorSettingsController  *
********************************/

RPDB_DatabaseErrorSettingsController* RPDB_DatabaseSettingsController_errorSettingsController( RPDB_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->error_settings_controller == NULL )	{
		database_settings_controller->error_settings_controller = RPDB_DatabaseErrorSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->error_settings_controller;
}

/*****************************
*  fixedRecordController  *
*****************************/

RPDB_DatabaseFixedRecordSettingsController* RPDB_DatabaseSettingsController_fixedRecordSettingsController( RPDB_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->fixed_record_settings_controller == NULL )	{
		database_settings_controller->fixed_record_settings_controller = RPDB_DatabaseFixedRecordSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->fixed_record_settings_controller;
}

/************************
*  cacheController  *
************************/

RPDB_DatabaseCacheSettingsController* RPDB_DatabaseSettingsController_cacheSettingsController( RPDB_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->cache_settings_controller == NULL )	{
		database_settings_controller->cache_settings_controller = RPDB_DatabaseCacheSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->cache_settings_controller;
}

/****************************
*  associateController  *
****************************/

RPDB_DatabaseAssociationSettingsController* RPDB_DatabaseSettingsController_associationSettingsController( RPDB_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->association_settings_controller == NULL )	{
		database_settings_controller->association_settings_controller = RPDB_DatabaseAssociationSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->association_settings_controller;
}

/*************************
*  compactController  *
*************************/

RPDB_DatabaseCompactSettingsController* RPDB_DatabaseSettingsController_compactSettingsController( RPDB_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->compact_settings_controller == NULL )	{
		database_settings_controller->compact_settings_controller = RPDB_DatabaseCompactSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->compact_settings_controller;
}

/*****************************
*  encryptionController  *
*****************************/

RPDB_DatabaseEncryptionSettingsController* RPDB_DatabaseSettingsController_encryptionSettingsController( RPDB_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->encryption_settings_controller == NULL )	{
		database_settings_controller->encryption_settings_controller = RPDB_DatabaseEncryptionSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->encryption_settings_controller;
}

/*****************************
*  verbosityController  *
*****************************/

RPDB_DatabaseVerbositySettingsController* RPDB_DatabaseSettingsController_verbositySettingsController( RPDB_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->verbosity_settings_controller == NULL )	{
		database_settings_controller->verbosity_settings_controller = RPDB_DatabaseVerbositySettingsController_new( database_settings_controller );
	}

	return database_settings_controller->verbosity_settings_controller;
}

/*****************************
*  verificationController  *
*****************************/

RPDB_DatabaseVerificationSettingsController* RPDB_DatabaseSettingsController_verificationSettingsController( RPDB_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->verification_settings_controller == NULL )	{
		database_settings_controller->verification_settings_controller = RPDB_DatabaseVerificationSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->verification_settings_controller;
}

/*****************************
*  cursorController  *
*****************************/

RPDB_DatabaseCursorSettingsController* RPDB_DatabaseSettingsController_cursorSettingsController( RPDB_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->cursor_settings_controller == NULL )	{
		database_settings_controller->cursor_settings_controller = RPDB_DatabaseCursorSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->cursor_settings_controller;
}

/*****************************
*  sequenceController  *
*****************************/

RPDB_DatabaseSequenceSettingsController* RPDB_DatabaseSettingsController_sequenceSettingsController( RPDB_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->sequence_settings_controller == NULL )	{
		database_settings_controller->sequence_settings_controller = RPDB_DatabaseSequenceSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->sequence_settings_controller;
}

/*****************************
*  typeSettingsController  *
*****************************/

RPDB_DatabaseTypeSettingsController* RPDB_DatabaseSettingsController_typeSettingsController( RPDB_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->type_settings_controller == NULL )	{
		database_settings_controller->type_settings_controller = RPDB_DatabaseTypeSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->type_settings_controller;
}

/*************************************
*  readWriteSettingsController  *
*************************************/

RPDB_DatabaseReadWriteSettingsController*		RPDB_DatabaseSettingsController_readWriteSettingsController(					RPDB_DatabaseSettingsController*	database_settings_controller )	{

	if ( database_settings_controller->read_write_settings_controller == NULL )	{
		database_settings_controller->read_write_settings_controller = RPDB_DatabaseReadWriteSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->read_write_settings_controller;
}

/*************************************
*  recordSettingsController  *
************************************/

RPDB_DatabaseRecordSettingsController* RPDB_DatabaseSettingsController_recordSettingsController( RPDB_DatabaseSettingsController*	database_settings_controller )	{
	
	if ( database_settings_controller->record_settings_controller == NULL )	{
		database_settings_controller->record_settings_controller = RPDB_DatabaseRecordSettingsController_new( database_settings_controller );
	}
	
	return database_settings_controller->record_settings_controller;
}

/*************************************
*  joinSettingsController  *
************************************/

RPDB_DatabaseJoinSettingsController* RPDB_DatabaseSettingsController_joinSettingsController( RPDB_DatabaseSettingsController*	database_settings_controller )	{
	
	if ( database_settings_controller->join_settings_controller == NULL )	{
		database_settings_controller->join_settings_controller = RPDB_DatabaseJoinSettingsController_new( database_settings_controller );
	}
	
	return database_settings_controller->join_settings_controller;
}


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/**********************
*  createFlags  *
**********************/

int RPDB_DatabaseSettingsController_internal_createFlags( RPDB_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	//	FIX
	return FALSE;
}

/******************
*  openFlags  *
******************/

int RPDB_DatabaseSettingsController_internal_openFlags( RPDB_DatabaseSettingsController* database_settings_controller )	{
	
	return	RPDB_FileSettingsController_permitEnvironmentBasedFileNaming(	RPDB_SettingsController_fileSettingsController( RPDB_Environment_settingsController( database_settings_controller->parent_settings_controller->parent_environment ) ) )
			|	RPDB_FileSettingsController_useEnvironmentHomePermissionsForFileNaming(	RPDB_SettingsController_fileSettingsController( RPDB_Environment_settingsController( database_settings_controller->parent_settings_controller->parent_environment ) ) )
			|	RPDB_FileSettingsController_createIfNecessary(	RPDB_SettingsController_fileSettingsController( RPDB_Environment_settingsController( database_settings_controller->parent_settings_controller->parent_environment ) ) )
			|	RPDB_DebugSettingsController_openInLockdown(	RPDB_SettingsController_debugSettingsController( RPDB_Environment_settingsController( database_settings_controller->parent_settings_controller->parent_environment ) ) )
			|	RPDB_MemoryPoolSettingsController_useSystemMemoryForStorage(	RPDB_SettingsController_memoryPoolSettingsController( RPDB_Environment_settingsController( database_settings_controller->parent_settings_controller->parent_environment ) ) );
}

/********************
*  closeFlags  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
//	DB_NOSYNC
int RPDB_DatabaseSettingsController_internal_closeFlags( RPDB_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	//	FIX
	return FALSE;
}

/********************
*  renameFlags  *
********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_rename.html
int RPDB_DatabaseSettingsController_internal_renameFlags( RPDB_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return FALSE;
}

/********************
*  emptyFlags  *
********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_truncate.html
int RPDB_DatabaseSettingsController_internal_emptyFlags( RPDB_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return FALSE;
}

/********************
*  eraseFlags  *
********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_remove.html
int RPDB_DatabaseSettingsController_internal_eraseFlags( RPDB_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return FALSE;
}

/*********************
*  upgradeFlags  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_upgrade.html
int RPDB_DatabaseSettingsController_internal_upgradeFlags( RPDB_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{

	//	FIX
	return FALSE;
}

/*********************
*  resetIDFlags  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_fileid_reset.html
int RPDB_DatabaseSettingsController_internal_resetIDFlags( RPDB_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{

	//	FIX
	return FALSE;
}

/*****************
*  syncFlags  *
*****************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_sync.html
int RPDB_DatabaseSettingsController_internal_syncFlags( RPDB_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return FALSE;
}

/*************************
*  associateFlags  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_associate.html
int RPDB_DatabaseSettingsController_internal_associateFlags( RPDB_DatabaseSettingsController* database_settings_controller )	{

	//	FIX
	//	if DB_CREATE is set then we want to return it unless createSecondaryIndexOnAssociation is false
	
	return RPDB_DatabaseAssociationSettingsController_secondaryAssociationCreatesIndex( RPDB_DatabaseSettingsController_associationSettingsController( database_settings_controller ) )
			|	RPDB_DatabaseAssociationSettingsController_immutableSecondaryKey( RPDB_DatabaseSettingsController_associationSettingsController( database_settings_controller ) );
}

/*********************
*  keyRangeFlags  *
*********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_key_range.html
int RPDB_DatabaseSettingsController_internal_keyRangeFlags( RPDB_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return RPDB_NO_FLAGS;
}

/**************************
*  compactParameters  *
**************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
DB_COMPACT* RPDB_DatabaseSettingsController_internal_compactParameters( RPDB_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{

	//	FIX
//	return &( database->database_status_controller->compact_status );
	return NULL;
}

/**********************
*  compactFlags  *
**********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
int RPDB_DatabaseSettingsController_internal_compactFlags( RPDB_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return RPDB_NO_FLAGS;
}

/**********************************************
*  prepareDatabaseForFileTransferFlags  *
**********************************************/

int RPDB_DatabaseSettingsController_internal_prepareDatabaseForFileTransferFlags( RPDB_DatabaseSettingsController* database_settings_controller )	{

	return RPDB_DatabaseEncryptionSettingsController_encrypted( 
					RPDB_DatabaseSettingsController_encryptionSettingsController( 
						RPDB_SettingsController_databaseSettingsController( 
							RPDB_Environment_settingsController( database_settings_controller->parent_database->parent_database_controller->parent_environment ) ) ) );	
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseSettingsController* RPDB_DatabaseSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseSettingsController* database_settings_controller_copy	=	RPDB_DatabaseSettingsController_new( database_settings_controller->parent_settings_controller );
	
	//	Instances and Pointers
	database_settings_controller_copy->is_byteswapped				=	database_settings_controller->is_byteswapped;
	database_settings_controller_copy->checksum						=	database_settings_controller->checksum;
	database_settings_controller_copy->little_endian				=	database_settings_controller->little_endian;
	database_settings_controller_copy->pagesize						=	database_settings_controller->pagesize;
	database_settings_controller_copy->big_endian					=	database_settings_controller->big_endian;
	database_settings_controller_copy->transaction_durability_off	=	database_settings_controller->transaction_durability_off;
	database_settings_controller_copy->on							=	database_settings_controller->on;

	//	Tell Controllers to copy
	if ( database_settings_controller->error_settings_controller != NULL )	{
		database_settings_controller_copy->error_settings_controller										=	RPDB_DatabaseErrorSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->error_settings_controller );
		database_settings_controller_copy->error_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->fixed_record_settings_controller != NULL )	{
		database_settings_controller_copy->fixed_record_settings_controller									=	RPDB_DatabaseFixedRecordSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->fixed_record_settings_controller );
		database_settings_controller_copy->fixed_record_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->cache_settings_controller != NULL )	{
		database_settings_controller_copy->cache_settings_controller										=	RPDB_DatabaseCacheSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->cache_settings_controller );
		database_settings_controller_copy->cache_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->association_settings_controller != NULL )	{
		database_settings_controller_copy->association_settings_controller									=	RPDB_DatabaseAssociationSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->association_settings_controller );
		database_settings_controller_copy->association_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->compact_settings_controller != NULL )	{
		database_settings_controller_copy->compact_settings_controller										=	RPDB_DatabaseCompactSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->compact_settings_controller );
		database_settings_controller_copy->compact_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->encryption_settings_controller != NULL )	{
		database_settings_controller_copy->encryption_settings_controller									=	RPDB_DatabaseEncryptionSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->encryption_settings_controller );
		database_settings_controller_copy->encryption_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->verbosity_settings_controller != NULL )	{
		database_settings_controller_copy->verbosity_settings_controller									=	RPDB_DatabaseVerbositySettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->verbosity_settings_controller );
		database_settings_controller_copy->verbosity_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->type_settings_controller != NULL )	{
		database_settings_controller_copy->type_settings_controller											=	RPDB_DatabaseTypeSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->type_settings_controller );
		database_settings_controller_copy->type_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->sequence_settings_controller != NULL )	{
		database_settings_controller_copy->sequence_settings_controller										=	RPDB_DatabaseSequenceSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->sequence_settings_controller );
		database_settings_controller_copy->sequence_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->read_write_settings_controller != NULL )	{
		database_settings_controller_copy->read_write_settings_controller									=	RPDB_DatabaseReadWriteSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->read_write_settings_controller );
		database_settings_controller_copy->read_write_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->cursor_settings_controller != NULL )	{
		database_settings_controller_copy->cursor_settings_controller										=	RPDB_DatabaseCursorSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->cursor_settings_controller );
		database_settings_controller_copy->cursor_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->variable_record_settings_controller != NULL )	{
		database_settings_controller_copy->variable_record_settings_controller								=	RPDB_DatabaseVariableRecordSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->variable_record_settings_controller );
		database_settings_controller_copy->variable_record_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->verification_settings_controller != NULL )	{
		database_settings_controller_copy->verification_settings_controller									=	RPDB_DatabaseVerificationSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->verification_settings_controller );
		database_settings_controller_copy->verification_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->record_settings_controller != NULL )	{
		database_settings_controller_copy->record_settings_controller										=	RPDB_DatabaseRecordSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->record_settings_controller );
		database_settings_controller_copy->record_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	
	return database_settings_controller_copy;
}

