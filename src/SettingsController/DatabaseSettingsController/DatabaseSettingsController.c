/*
 *		RPbdb::Database::DatabaseSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseSettingsController.h"

//	#include "Compact.h"
#include "ErrorController.h"
#include "Database.h"
#include "DatabaseErrorSettingsController.h"
#include "DatabaseRecordFixedLengthSettingsController.h"
#include "DatabaseCacheSettingsController.h"
#include "DatabaseAssociationSettingsController.h"
#include "DatabaseCompactSettingsController.h"
#include "DatabaseEncryptionSettingsController.h"
#include "DatabaseTypeSettingsController.h"
#include "DatabaseRecordReadWriteSettingsController.h"
#include "DatabaseCursorSettingsController.h"
#include "SettingsController.h"
#include "Environment.h"
#include "DatabaseVerbositySettingsController.h"
#include "DatabaseVerificationSettingsController.h"
#include "DatabaseSequenceSettingsController.h"
#include "DatabaseRecordVariableLengthSettingsController.h"
#include "DatabaseRecordSettingsController.h"
#include "DatabaseJoinSettingsController.h"

#include "DatabaseAssociationSettingsController.h"

#include "TransactionSettingsController.h"
#include "LockSettingsController.h"
#include "LogSettingsController.h"
#include "MemoryPoolSettingsController.h"
#include "MemoryPoolReadWriteSettingsController.h"
#include "ReplicationSettingsController.h"
#include "DebugSettingsController.h"
#include "FileSettingsController.h"
#include "ThreadSettingsController.h"

#include "DatabaseVerbositySettingsController_internal.h"
#include "DatabaseSequenceSettingsController_internal.h"
#include "DatabaseRecordReadWriteSettingsController_internal.h"
#include "DatabaseCursorSettingsController_internal.h"
#include "DatabaseRecordVariableLengthSettingsController_internal.h"
#include "DatabaseVerificationSettingsController_internal.h"
#include "DatabaseRecordSettingsController_internal.h"

#include "DatabaseSettingsController_internal.h"
#include "DatabaseErrorSettingsController_internal.h"
#include "DatabaseRecordFixedLengthSettingsController_internal.h"
#include "DatabaseCacheSettingsController_internal.h"
#include "DatabaseAssociationSettingsController_internal.h"
#include "DatabaseCompactSettingsController_internal.h"
#include "DatabaseEncryptionSettingsController_internal.h"
#include "DatabaseTypeSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_DatabaseSettingsController* RPbdb_DatabaseSettingsController_new( RPbdb_SettingsController* settings_controller )	{

	RPbdb_DatabaseSettingsController*		database_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseSettingsController ) );
	
	database_settings_controller->parent_settings_controller = settings_controller;

	return database_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseSettingsController_free(	RPbdb_DatabaseSettingsController** database_settings_controller )	{

	if ( ( *database_settings_controller )->verification_settings_controller != NULL )	{
		RPbdb_DatabaseVerificationSettingsController_free( & ( ( *database_settings_controller )->verification_settings_controller ) );
	}
	if ( ( *database_settings_controller )->error_settings_controller != NULL )	{
		RPbdb_DatabaseErrorSettingsController_free( & ( ( *database_settings_controller )->error_settings_controller ) );
	}
	if ( ( *database_settings_controller )->cursor_settings_controller != NULL )	{
		RPbdb_DatabaseCursorSettingsController_free( & ( ( *database_settings_controller )->cursor_settings_controller ) );
	}
	if ( ( *database_settings_controller )->sequence_settings_controller != NULL )	{
		RPbdb_DatabaseSequenceSettingsController_free( & ( ( *database_settings_controller )->sequence_settings_controller ) );
	}
	if ( ( *database_settings_controller )->verbosity_settings_controller != NULL )	{
		RPbdb_DatabaseVerbositySettingsController_free( & ( ( *database_settings_controller )->verbosity_settings_controller ) );
	}
	if ( ( *database_settings_controller )->compact_settings_controller != NULL )	{
		RPbdb_DatabaseCompactSettingsController_free( & ( ( *database_settings_controller )->compact_settings_controller ) );
	}
	if ( ( *database_settings_controller )->cache_settings_controller != NULL )	{
		RPbdb_DatabaseCacheSettingsController_free( & ( ( *database_settings_controller )->cache_settings_controller ) );
	}
	if ( ( *database_settings_controller )->encryption_settings_controller != NULL )	{
		RPbdb_DatabaseEncryptionSettingsController_free( & ( ( *database_settings_controller )->encryption_settings_controller ) );
	}
	if ( ( *database_settings_controller )->association_settings_controller != NULL )	{
		RPbdb_DatabaseAssociationSettingsController_free( & ( ( *database_settings_controller )->association_settings_controller ) );
	}
	if ( ( *database_settings_controller )->type_settings_controller != NULL )	{
		RPbdb_DatabaseTypeSettingsController_free( & ( ( *database_settings_controller )->type_settings_controller ) );
	}
	if ( ( *database_settings_controller )->record_settings_controller != NULL )	{
		RPbdb_DatabaseRecordSettingsController_free( & ( ( *database_settings_controller )->record_settings_controller ) );
	}
	
	free( *database_settings_controller );
	*database_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseSettingsController_parentEnvironment(	RPbdb_DatabaseSettingsController* database_settings_controller )	{
	return database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseSettingsController_parentDatabase(	RPbdb_DatabaseSettingsController* database_settings_controller )	{
	return database_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/****************
*  checksum  *
****************/

//	DB_CHKSUM				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
int RPbdb_DatabaseSettingsController_checksum( RPbdb_DatabaseSettingsController* database_settings_controller )	{
	if ( database_settings_controller->checksum == TRUE )	{
		return DB_CHKSUM;
	}
	return FALSE;
}

	/************************
	*  turnChecksumOn  *
	************************/

	//	DB_CHKSUM				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
	void RPbdb_DatabaseSettingsController_turnChecksumOn( RPbdb_DatabaseSettingsController* database_settings_controller )	{
		database_settings_controller->checksum = TRUE;
	}

	/************************
	*  turnChecksumOff  *
	************************/

	//	DB_CHKSUM				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
	void RPbdb_DatabaseSettingsController_turnChecksumOff( RPbdb_DatabaseSettingsController* database_settings_controller )	{
		database_settings_controller->checksum = FALSE;
	}

/*************
*  logs  *
*************/

//	DB_TXN_NOT_DURABLE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
int RPbdb_DatabaseSettingsController_transactionDurability( RPbdb_DatabaseSettingsController* database_settings_controller )	{
	if ( database_settings_controller->transaction_durability_off == TRUE )	{
		return DB_TXN_NOT_DURABLE;
	}
	return FALSE;
}

	/******************
	*  turnLogsOn  *
	******************/

	//	DB_TXN_NOT_DURABLE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
	void RPbdb_DatabaseSettingsController_turnTransactionDurabilityOn( RPbdb_DatabaseSettingsController* database_settings_controller )	{
		database_settings_controller->transaction_durability_off = TRUE;
	}

	/********************
	*  turnLogsOff  *
	********************/

	//	DB_TXN_NOT_DURABLE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
	void RPbdb_DatabaseSettingsController_turnTransactionDurabilityOff( RPbdb_DatabaseSettingsController* database_settings_controller )	{
		database_settings_controller->transaction_durability_off = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/****************
*  pagesize  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_pagesize.html
uint32_t RPbdb_DatabaseSettingsController_pagesize( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_Database*	database = database_settings_controller->parent_database;
	
	int				connection_error	= 0;

	//	If it's already set we don't need to grab it - it is up to date
	if (	database_settings_controller->pagesize == 0
		&&	database != NULL
		&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->get_pagesize(	database->wrapped_bdb_database, 
																																						&( database_settings_controller->pagesize ) ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"DatabaseType" );
		}
	}
	
	return database_settings_controller->pagesize;
}

/********************
*  setPageSize  *
********************/

void RPbdb_DatabaseSettingsController_setPageSize(	RPbdb_DatabaseSettingsController*	database_settings_controller, 
																									uint32_t							pagesize )	{

	RPbdb_Database*	database = database_settings_controller->parent_database;

	int			connection_error	= RP_NO_ERROR;

	database_settings_controller->pagesize = pagesize;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
		if ( ( connection_error = database->wrapped_bdb_database->set_pagesize(	database->wrapped_bdb_database, 
																																						pagesize ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"DatabaseType" );
		}
	}
}

/*********************
*  isBigEndian  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_lorder.html
//	Byte order for stored integers in database
BOOL RPbdb_DatabaseSettingsController_isBigEndian( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_Database*	database = database_settings_controller->parent_database;

	int			load_order;
	
	int			connection_error	= 0;

	if (	! database_settings_controller->little_endian
		&&	! database_settings_controller->big_endian
		&&	database != NULL
		&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->get_lorder(	database->wrapped_bdb_database, 
																				& load_order )) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"DatabaseType" );
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
void RPbdb_DatabaseSettingsController_setByteOrderToBigEndian( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_Database*	database = database_settings_controller->parent_database;
	
	int			connection_error	= 0;

	database_settings_controller->big_endian = TRUE;
	database_settings_controller->little_endian = FALSE;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
		if ( ( connection_error = database->wrapped_bdb_database->set_lorder(	database->wrapped_bdb_database,
																				4321 )) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"DatabaseType" );
		}
	}
}

/*********************
*  isLittleEndian  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_lorder.html
//	Byte order for stored integers in database
BOOL RPbdb_DatabaseSettingsController_isLittleEndian( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_Database*	database = database_settings_controller->parent_database;

	int			load_order;

	int			connection_error	= 0;

	if (	! database_settings_controller->little_endian
		&&	! database_settings_controller->big_endian
		&&	database != NULL
		&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->get_lorder(	database->wrapped_bdb_database, 
																																					& load_order ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"DatabaseType" );
		}
		database_settings_controller->little_endian = load_order == 1234 ? TRUE : FALSE;
	}

	return database_settings_controller->little_endian;	
}

/*************************************
*  setByteOrderToLittleEndian  *
*************************************/

void RPbdb_DatabaseSettingsController_setByteOrderToLittleEndian( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_Database*	database = database_settings_controller->parent_database;
	
	int			connection_error	= 0;

	database_settings_controller->little_endian = TRUE;
	database_settings_controller->big_endian = FALSE;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
		if ( ( connection_error = database->wrapped_bdb_database->set_lorder(	database->wrapped_bdb_database, 
																																					1234 ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"DatabaseType" );
		}
	}
}

/********************
*  isByteswapped  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get_byteswapped.html
BOOL RPbdb_DatabaseSettingsController_isByteswapped( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_Database*	database = database_settings_controller->parent_database;
	
	int			connection_error	= 0;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL)	{

		if ( ( connection_error = database->wrapped_bdb_database->get_byteswapped(	database->wrapped_bdb_database, 
																																								(int*) &( database_settings_controller->is_byteswapped ) )) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																																											connection_error, 
																																											"DatabaseType" );
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
int RPbdb_DatabaseSettingsController_maxSizePageIn( RPbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	
	//	FIX
	return 0;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/*************************************
*  recordSettingsController  *
************************************/

RPbdb_DatabaseRecordSettingsController* RPbdb_DatabaseSettingsController_recordSettingsController( RPbdb_DatabaseSettingsController*	database_settings_controller )	{
	
	if ( database_settings_controller->record_settings_controller == NULL )	{
		database_settings_controller->record_settings_controller = RPbdb_DatabaseRecordSettingsController_new( database_settings_controller );
	}
	
	return database_settings_controller->record_settings_controller;
}



/********************************
*  errorSettingsController  *
********************************/

RPbdb_DatabaseErrorSettingsController* RPbdb_DatabaseSettingsController_errorSettingsController( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->error_settings_controller == NULL )	{
		database_settings_controller->error_settings_controller = RPbdb_DatabaseErrorSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->error_settings_controller;
}

/************************
*  cacheController  *
************************/

RPbdb_DatabaseCacheSettingsController* RPbdb_DatabaseSettingsController_cacheSettingsController( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->cache_settings_controller == NULL )	{
		database_settings_controller->cache_settings_controller = RPbdb_DatabaseCacheSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->cache_settings_controller;
}

/****************************
*  associateController  *
****************************/

RPbdb_DatabaseAssociationSettingsController* RPbdb_DatabaseSettingsController_associationSettingsController( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->association_settings_controller == NULL )	{
		database_settings_controller->association_settings_controller = RPbdb_DatabaseAssociationSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->association_settings_controller;
}

/*************************
*  compactController  *
*************************/

RPbdb_DatabaseCompactSettingsController* RPbdb_DatabaseSettingsController_compactSettingsController( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->compact_settings_controller == NULL )	{
		database_settings_controller->compact_settings_controller = RPbdb_DatabaseCompactSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->compact_settings_controller;
}

/*****************************
*  encryptionController  *
*****************************/

RPbdb_DatabaseEncryptionSettingsController* RPbdb_DatabaseSettingsController_encryptionSettingsController( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->encryption_settings_controller == NULL )	{
		database_settings_controller->encryption_settings_controller = RPbdb_DatabaseEncryptionSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->encryption_settings_controller;
}

/*****************************
*  verbosityController  *
*****************************/

RPbdb_DatabaseVerbositySettingsController* RPbdb_DatabaseSettingsController_verbositySettingsController( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->verbosity_settings_controller == NULL )	{
		database_settings_controller->verbosity_settings_controller = RPbdb_DatabaseVerbositySettingsController_new( database_settings_controller );
	}

	return database_settings_controller->verbosity_settings_controller;
}

/*****************************
*  verificationController  *
*****************************/

RPbdb_DatabaseVerificationSettingsController* RPbdb_DatabaseSettingsController_verificationSettingsController( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->verification_settings_controller == NULL )	{
		database_settings_controller->verification_settings_controller = RPbdb_DatabaseVerificationSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->verification_settings_controller;
}

/*****************************
*  cursorController  *
*****************************/

RPbdb_DatabaseCursorSettingsController* RPbdb_DatabaseSettingsController_cursorSettingsController( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->cursor_settings_controller == NULL )	{
		database_settings_controller->cursor_settings_controller = RPbdb_DatabaseCursorSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->cursor_settings_controller;
}

/*****************************
*  sequenceController  *
*****************************/

RPbdb_DatabaseSequenceSettingsController* RPbdb_DatabaseSettingsController_sequenceSettingsController( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->sequence_settings_controller == NULL )	{
		database_settings_controller->sequence_settings_controller = RPbdb_DatabaseSequenceSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->sequence_settings_controller;
}

/*****************************
*  typeSettingsController  *
*****************************/

RPbdb_DatabaseTypeSettingsController* RPbdb_DatabaseSettingsController_typeSettingsController( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->type_settings_controller == NULL )	{
		database_settings_controller->type_settings_controller = RPbdb_DatabaseTypeSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->type_settings_controller;
}

/*************************************
*  joinSettingsController  *
************************************/

RPbdb_DatabaseJoinSettingsController* RPbdb_DatabaseSettingsController_joinSettingsController( RPbdb_DatabaseSettingsController*	database_settings_controller )	{
	
	if ( database_settings_controller->join_settings_controller == NULL )	{
		database_settings_controller->join_settings_controller = RPbdb_DatabaseJoinSettingsController_new( database_settings_controller );
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

int RPbdb_DatabaseSettingsController_internal_createFlags( RPbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	//	FIX
	return FALSE;
}

/******************
*  openFlags  *
******************/

int RPbdb_DatabaseSettingsController_internal_openFlags( RPbdb_DatabaseSettingsController* database_settings_controller )	{
	
	RPbdb_SettingsController*											settings_controller													=	RPbdb_Environment_settingsController( database_settings_controller->parent_settings_controller->parent_environment );
	RPbdb_MemoryPoolSettingsController*						memory_pool_settings_controller							=	RPbdb_SettingsController_memoryPoolSettingsController( settings_controller );
	RPbdb_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller	=	RPbdb_MemoryPoolSettingsController_readWriteSettingsController( memory_pool_settings_controller );
	
	return	RPbdb_FileSettingsController_permitEnvironmentBasedFileNaming(	RPbdb_SettingsController_fileSettingsController( settings_controller ) )
			|	RPbdb_FileSettingsController_useEnvironmentHomePermissionsForFileNaming(	RPbdb_SettingsController_fileSettingsController( RPbdb_Environment_settingsController( database_settings_controller->parent_settings_controller->parent_environment ) ) )
			|	RPbdb_FileSettingsController_createIfNecessary(	RPbdb_SettingsController_fileSettingsController( settings_controller ) )
			|	RPbdb_DebugSettingsController_openInLockdown(	RPbdb_SettingsController_debugSettingsController( settings_controller ) )
			|	RPbdb_MemoryPoolReadWriteSettingsController_useSystemMemoryForStorage(	memory_pool_read_write_settings_controller );
}

/********************
*  closeFlags  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
//	DB_NOSYNC
int RPbdb_DatabaseSettingsController_internal_closeFlags( RPbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	//	FIX
	return FALSE;
}

/********************
*  renameFlags  *
********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_rename.html
int RPbdb_DatabaseSettingsController_internal_renameFlags( RPbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return FALSE;
}

/********************
*  emptyFlags  *
********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_truncate.html
int RPbdb_DatabaseSettingsController_internal_emptyFlags( RPbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return FALSE;
}

/********************
*  eraseFlags  *
********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_remove.html
int RPbdb_DatabaseSettingsController_internal_eraseFlags( RPbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return FALSE;
}

/*********************
*  upgradeFlags  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_upgrade.html
int RPbdb_DatabaseSettingsController_internal_upgradeFlags( RPbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{

	//	FIX
	return FALSE;
}

/*********************
*  resetIDFlags  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_fileid_reset.html
int RPbdb_DatabaseSettingsController_internal_resetIDFlags( RPbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{

	//	FIX
	return FALSE;
}

/*****************
*  syncFlags  *
*****************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_sync.html
int RPbdb_DatabaseSettingsController_internal_syncFlags( RPbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return FALSE;
}

/*************************
*  associateFlags  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_associate.html
int RPbdb_DatabaseSettingsController_internal_associateFlags( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	//	FIX
	//	if DB_CREATE is set then we want to return it unless createSecondaryIndexOnAssociation is false
	
	return RPbdb_DatabaseAssociationSettingsController_secondaryAssociationCreatesIndex( RPbdb_DatabaseSettingsController_associationSettingsController( database_settings_controller ) )
			|	RPbdb_DatabaseAssociationSettingsController_immutableSecondaryKey( RPbdb_DatabaseSettingsController_associationSettingsController( database_settings_controller ) );
}

/*********************
*  keyRangeFlags  *
*********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_key_range.html
int RPbdb_DatabaseSettingsController_internal_keyRangeFlags( RPbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return RPBDB_NO_FLAGS;
}

/**************************
*  compactParameters  *
**************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
DB_COMPACT* RPbdb_DatabaseSettingsController_internal_compactParameters( RPbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{

	//	FIX
//	return &( database->database_status_controller->compact_status );
	return NULL;
}

/**********************
*  compactFlags  *
**********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
int RPbdb_DatabaseSettingsController_internal_compactFlags( RPbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return RPBDB_NO_FLAGS;
}

/**********************************************
*  prepareDatabaseForFileTransferFlags  *
**********************************************/

int RPbdb_DatabaseSettingsController_internal_prepareDatabaseForFileTransferFlags( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	return RPbdb_DatabaseEncryptionSettingsController_encrypted( 
					RPbdb_DatabaseSettingsController_encryptionSettingsController( 
						RPbdb_SettingsController_databaseSettingsController( 
							RPbdb_Environment_settingsController( database_settings_controller->parent_database->parent_database_controller->parent_environment ) ) ) );	
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseSettingsController* RPbdb_DatabaseSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_DatabaseSettingsController* database_settings_controller_copy	=	RPbdb_DatabaseSettingsController_new( database_settings_controller->parent_settings_controller );
	
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
		database_settings_controller_copy->error_settings_controller										=	RPbdb_DatabaseErrorSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->error_settings_controller );
		database_settings_controller_copy->error_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->cache_settings_controller != NULL )	{
		database_settings_controller_copy->cache_settings_controller										=	RPbdb_DatabaseCacheSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->cache_settings_controller );
		database_settings_controller_copy->cache_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->association_settings_controller != NULL )	{
		database_settings_controller_copy->association_settings_controller									=	RPbdb_DatabaseAssociationSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->association_settings_controller );
		database_settings_controller_copy->association_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->compact_settings_controller != NULL )	{
		database_settings_controller_copy->compact_settings_controller										=	RPbdb_DatabaseCompactSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->compact_settings_controller );
		database_settings_controller_copy->compact_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->encryption_settings_controller != NULL )	{
		database_settings_controller_copy->encryption_settings_controller									=	RPbdb_DatabaseEncryptionSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->encryption_settings_controller );
		database_settings_controller_copy->encryption_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->verbosity_settings_controller != NULL )	{
		database_settings_controller_copy->verbosity_settings_controller									=	RPbdb_DatabaseVerbositySettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->verbosity_settings_controller );
		database_settings_controller_copy->verbosity_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->type_settings_controller != NULL )	{
		database_settings_controller_copy->type_settings_controller											=	RPbdb_DatabaseTypeSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->type_settings_controller );
		database_settings_controller_copy->type_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->sequence_settings_controller != NULL )	{
		database_settings_controller_copy->sequence_settings_controller										=	RPbdb_DatabaseSequenceSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->sequence_settings_controller );
		database_settings_controller_copy->sequence_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->cursor_settings_controller != NULL )	{
		database_settings_controller_copy->cursor_settings_controller										=	RPbdb_DatabaseCursorSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->cursor_settings_controller );
		database_settings_controller_copy->cursor_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->verification_settings_controller != NULL )	{
		database_settings_controller_copy->verification_settings_controller									=	RPbdb_DatabaseVerificationSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->verification_settings_controller );
		database_settings_controller_copy->verification_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->record_settings_controller != NULL )	{
		database_settings_controller_copy->record_settings_controller										=	RPbdb_DatabaseRecordSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->record_settings_controller );
		database_settings_controller_copy->record_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	
	return database_settings_controller_copy;
}

