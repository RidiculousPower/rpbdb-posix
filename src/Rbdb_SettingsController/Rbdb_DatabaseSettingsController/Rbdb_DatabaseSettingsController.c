/*
 *		Rbdb::Database::DatabaseSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseSettingsController.h"

//	#include "Rbdb_Compact.h"
#include "Rbdb_ErrorController.h"
#include "Rbdb_Database.h"
#include "Rbdb_DatabaseErrorSettingsController.h"
#include "Rbdb_DatabaseRecordFixedLengthSettingsController.h"
#include "Rbdb_DatabaseCacheSettingsController.h"
#include "Rbdb_DatabaseAssociationSettingsController.h"
#include "Rbdb_DatabaseCompactSettingsController.h"
#include "Rbdb_DatabaseEncryptionSettingsController.h"
#include "Rbdb_DatabaseTypeSettingsController.h"
#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"
#include "Rbdb_DatabaseCursorSettingsController.h"
#include "Rbdb_SettingsController.h"
#include "Rbdb_Environment.h"
#include "Rbdb_DatabaseVerbositySettingsController.h"
#include "Rbdb_DatabaseVerificationSettingsController.h"
#include "Rbdb_DatabaseSequenceSettingsController.h"
#include "Rbdb_DatabaseRecordVariableLengthSettingsController.h"
#include "Rbdb_DatabaseRecordSettingsController.h"
#include "Rbdb_DatabaseJoinSettingsController.h"

#include "Rbdb_DatabaseAssociationSettingsController.h"

#include "Rbdb_TransactionSettingsController.h"
#include "Rbdb_LockSettingsController.h"
#include "Rbdb_LogSettingsController.h"
#include "Rbdb_MemoryPoolSettingsController.h"
#include "Rbdb_MemoryPoolReadWriteSettingsController.h"
#include "Rbdb_ReplicationSettingsController.h"
#include "Rbdb_DebugSettingsController.h"
#include "Rbdb_FileSettingsController.h"
#include "Rbdb_ThreadSettingsController.h"

#include "Rbdb_DatabaseVerbositySettingsController_internal.h"
#include "Rbdb_DatabaseSequenceSettingsController_internal.h"
#include "Rbdb_DatabaseRecordReadWriteSettingsController_internal.h"
#include "Rbdb_DatabaseCursorSettingsController_internal.h"
#include "Rbdb_DatabaseRecordVariableLengthSettingsController_internal.h"
#include "Rbdb_DatabaseVerificationSettingsController_internal.h"
#include "Rbdb_DatabaseRecordSettingsController_internal.h"

#include "Rbdb_DatabaseSettingsController_internal.h"
#include "Rbdb_DatabaseErrorSettingsController_internal.h"
#include "Rbdb_DatabaseRecordFixedLengthSettingsController_internal.h"
#include "Rbdb_DatabaseCacheSettingsController_internal.h"
#include "Rbdb_DatabaseAssociationSettingsController_internal.h"
#include "Rbdb_DatabaseCompactSettingsController_internal.h"
#include "Rbdb_DatabaseEncryptionSettingsController_internal.h"
#include "Rbdb_DatabaseTypeSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_DatabaseSettingsController* Rbdb_DatabaseSettingsController_new( Rbdb_SettingsController* settings_controller )	{

	Rbdb_DatabaseSettingsController*		database_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseSettingsController ) );
	
	database_settings_controller->parent_settings_controller = settings_controller;

	return database_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseSettingsController_free(	Rbdb_DatabaseSettingsController** database_settings_controller )	{

	if ( ( *database_settings_controller )->verification_settings_controller != NULL )	{
		Rbdb_DatabaseVerificationSettingsController_free( & ( ( *database_settings_controller )->verification_settings_controller ) );
	}
	if ( ( *database_settings_controller )->error_settings_controller != NULL )	{
		Rbdb_DatabaseErrorSettingsController_free( & ( ( *database_settings_controller )->error_settings_controller ) );
	}
	if ( ( *database_settings_controller )->cursor_settings_controller != NULL )	{
		Rbdb_DatabaseCursorSettingsController_free( & ( ( *database_settings_controller )->cursor_settings_controller ) );
	}
	if ( ( *database_settings_controller )->sequence_settings_controller != NULL )	{
		Rbdb_DatabaseSequenceSettingsController_free( & ( ( *database_settings_controller )->sequence_settings_controller ) );
	}
	if ( ( *database_settings_controller )->verbosity_settings_controller != NULL )	{
		Rbdb_DatabaseVerbositySettingsController_free( & ( ( *database_settings_controller )->verbosity_settings_controller ) );
	}
	if ( ( *database_settings_controller )->compact_settings_controller != NULL )	{
		Rbdb_DatabaseCompactSettingsController_free( & ( ( *database_settings_controller )->compact_settings_controller ) );
	}
	if ( ( *database_settings_controller )->cache_settings_controller != NULL )	{
		Rbdb_DatabaseCacheSettingsController_free( & ( ( *database_settings_controller )->cache_settings_controller ) );
	}
	if ( ( *database_settings_controller )->encryption_settings_controller != NULL )	{
		Rbdb_DatabaseEncryptionSettingsController_free( & ( ( *database_settings_controller )->encryption_settings_controller ) );
	}
	if ( ( *database_settings_controller )->association_settings_controller != NULL )	{
		Rbdb_DatabaseAssociationSettingsController_free( & ( ( *database_settings_controller )->association_settings_controller ) );
	}
	if ( ( *database_settings_controller )->type_settings_controller != NULL )	{
		Rbdb_DatabaseTypeSettingsController_free( & ( ( *database_settings_controller )->type_settings_controller ) );
	}
	if ( ( *database_settings_controller )->record_settings_controller != NULL )	{
		Rbdb_DatabaseRecordSettingsController_free( & ( ( *database_settings_controller )->record_settings_controller ) );
	}
	
	free( *database_settings_controller );
	*database_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseSettingsController_parentEnvironment(	Rbdb_DatabaseSettingsController* database_settings_controller )	{
	return database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseSettingsController_parentDatabase(	Rbdb_DatabaseSettingsController* database_settings_controller )	{
	return database_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/****************
*  checksum  *
****************/

//	DB_CHKSUM				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
int Rbdb_DatabaseSettingsController_checksum( Rbdb_DatabaseSettingsController* database_settings_controller )	{
	if ( database_settings_controller->checksum == TRUE )	{
		return DB_CHKSUM;
	}
	return FALSE;
}

	/************************
	*  turnChecksumOn  *
	************************/

	//	DB_CHKSUM				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
	void Rbdb_DatabaseSettingsController_turnChecksumOn( Rbdb_DatabaseSettingsController* database_settings_controller )	{
		database_settings_controller->checksum = TRUE;
	}

	/************************
	*  turnChecksumOff  *
	************************/

	//	DB_CHKSUM				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
	void Rbdb_DatabaseSettingsController_turnChecksumOff( Rbdb_DatabaseSettingsController* database_settings_controller )	{
		database_settings_controller->checksum = FALSE;
	}

/*************
*  logs  *
*************/

//	DB_TXN_NOT_DURABLE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
int Rbdb_DatabaseSettingsController_transactionDurability( Rbdb_DatabaseSettingsController* database_settings_controller )	{
	if ( database_settings_controller->transaction_durability_off == TRUE )	{
		return DB_TXN_NOT_DURABLE;
	}
	return FALSE;
}

	/******************
	*  turnLogsOn  *
	******************/

	//	DB_TXN_NOT_DURABLE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
	void Rbdb_DatabaseSettingsController_turnTransactionDurabilityOn( Rbdb_DatabaseSettingsController* database_settings_controller )	{
		database_settings_controller->transaction_durability_off = TRUE;
	}

	/********************
	*  turnLogsOff  *
	********************/

	//	DB_TXN_NOT_DURABLE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
	void Rbdb_DatabaseSettingsController_turnTransactionDurabilityOff( Rbdb_DatabaseSettingsController* database_settings_controller )	{
		database_settings_controller->transaction_durability_off = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/****************
*  pagesize  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_pagesize.html
uint32_t Rbdb_DatabaseSettingsController_pagesize( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_Database*	database = database_settings_controller->parent_database;
	
	int				connection_error	= 0;

	//	If it's already set we don't need to grab it - it is up to date
	if (	database_settings_controller->pagesize == 0
		&&	database != NULL
		&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->get_pagesize(	database->wrapped_bdb_database, 
																																						&( database_settings_controller->pagesize ) ) ) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"Rbdb_DatabaseType" );
		}
	}
	
	return database_settings_controller->pagesize;
}

/********************
*  setPageSize  *
********************/

void Rbdb_DatabaseSettingsController_setPageSize(	Rbdb_DatabaseSettingsController*	database_settings_controller, 
																									uint32_t							pagesize )	{

	Rbdb_Database*	database = database_settings_controller->parent_database;

	int			connection_error	= RP_NO_ERROR;

	database_settings_controller->pagesize = pagesize;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
		if ( ( connection_error = database->wrapped_bdb_database->set_pagesize(	database->wrapped_bdb_database, 
																																						pagesize ) ) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"Rbdb_DatabaseType" );
		}
	}
}

/*********************
*  isBigEndian  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_lorder.html
//	Byte order for stored integers in database
BOOL Rbdb_DatabaseSettingsController_isBigEndian( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_Database*	database = database_settings_controller->parent_database;

	int			load_order;
	
	int			connection_error	= 0;

	if (	! database_settings_controller->little_endian
		&&	! database_settings_controller->big_endian
		&&	database != NULL
		&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->get_lorder(	database->wrapped_bdb_database, 
																				& load_order )) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"Rbdb_DatabaseType" );
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
void Rbdb_DatabaseSettingsController_setByteOrderToBigEndian( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_Database*	database = database_settings_controller->parent_database;
	
	int			connection_error	= 0;

	database_settings_controller->big_endian = TRUE;
	database_settings_controller->little_endian = FALSE;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
		if ( ( connection_error = database->wrapped_bdb_database->set_lorder(	database->wrapped_bdb_database,
																				4321 )) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"Rbdb_DatabaseType" );
		}
	}
}

/*********************
*  isLittleEndian  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_lorder.html
//	Byte order for stored integers in database
BOOL Rbdb_DatabaseSettingsController_isLittleEndian( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_Database*	database = database_settings_controller->parent_database;

	int			load_order;

	int			connection_error	= 0;

	if (	! database_settings_controller->little_endian
		&&	! database_settings_controller->big_endian
		&&	database != NULL
		&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->get_lorder(	database->wrapped_bdb_database, 
																																					& load_order ) ) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"Rbdb_DatabaseType" );
		}
		database_settings_controller->little_endian = load_order == 1234 ? TRUE : FALSE;
	}

	return database_settings_controller->little_endian;	
}

/*************************************
*  setByteOrderToLittleEndian  *
*************************************/

void Rbdb_DatabaseSettingsController_setByteOrderToLittleEndian( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_Database*	database = database_settings_controller->parent_database;
	
	int			connection_error	= 0;

	database_settings_controller->little_endian = TRUE;
	database_settings_controller->big_endian = FALSE;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
		if ( ( connection_error = database->wrapped_bdb_database->set_lorder(	database->wrapped_bdb_database, 
																																					1234 ) ) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"Rbdb_DatabaseType" );
		}
	}
}

/********************
*  isByteswapped  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get_byteswapped.html
BOOL Rbdb_DatabaseSettingsController_isByteswapped( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_Database*	database = database_settings_controller->parent_database;
	
	int			connection_error	= 0;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL)	{

		if ( ( connection_error = database->wrapped_bdb_database->get_byteswapped(	database->wrapped_bdb_database, 
																																								(int*) &( database_settings_controller->is_byteswapped ) )) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																																											connection_error, 
																																											"Rbdb_DatabaseType" );
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
int Rbdb_DatabaseSettingsController_maxSizePageIn( Rbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	
	//	FIX
	return 0;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/*************************************
*  recordSettingsController  *
************************************/

Rbdb_DatabaseRecordSettingsController* Rbdb_DatabaseSettingsController_recordSettingsController( Rbdb_DatabaseSettingsController*	database_settings_controller )	{
	
	if ( database_settings_controller->record_settings_controller == NULL )	{
		database_settings_controller->record_settings_controller = Rbdb_DatabaseRecordSettingsController_new( database_settings_controller );
	}
	
	return database_settings_controller->record_settings_controller;
}



/********************************
*  errorSettingsController  *
********************************/

Rbdb_DatabaseErrorSettingsController* Rbdb_DatabaseSettingsController_errorSettingsController( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->error_settings_controller == NULL )	{
		database_settings_controller->error_settings_controller = Rbdb_DatabaseErrorSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->error_settings_controller;
}

/************************
*  cacheController  *
************************/

Rbdb_DatabaseCacheSettingsController* Rbdb_DatabaseSettingsController_cacheSettingsController( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->cache_settings_controller == NULL )	{
		database_settings_controller->cache_settings_controller = Rbdb_DatabaseCacheSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->cache_settings_controller;
}

/****************************
*  associateController  *
****************************/

Rbdb_DatabaseAssociationSettingsController* Rbdb_DatabaseSettingsController_associationSettingsController( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->association_settings_controller == NULL )	{
		database_settings_controller->association_settings_controller = Rbdb_DatabaseAssociationSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->association_settings_controller;
}

/*************************
*  compactController  *
*************************/

Rbdb_DatabaseCompactSettingsController* Rbdb_DatabaseSettingsController_compactSettingsController( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->compact_settings_controller == NULL )	{
		database_settings_controller->compact_settings_controller = Rbdb_DatabaseCompactSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->compact_settings_controller;
}

/*****************************
*  encryptionController  *
*****************************/

Rbdb_DatabaseEncryptionSettingsController* Rbdb_DatabaseSettingsController_encryptionSettingsController( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->encryption_settings_controller == NULL )	{
		database_settings_controller->encryption_settings_controller = Rbdb_DatabaseEncryptionSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->encryption_settings_controller;
}

/*****************************
*  verbosityController  *
*****************************/

Rbdb_DatabaseVerbositySettingsController* Rbdb_DatabaseSettingsController_verbositySettingsController( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->verbosity_settings_controller == NULL )	{
		database_settings_controller->verbosity_settings_controller = Rbdb_DatabaseVerbositySettingsController_new( database_settings_controller );
	}

	return database_settings_controller->verbosity_settings_controller;
}

/*****************************
*  verificationController  *
*****************************/

Rbdb_DatabaseVerificationSettingsController* Rbdb_DatabaseSettingsController_verificationSettingsController( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->verification_settings_controller == NULL )	{
		database_settings_controller->verification_settings_controller = Rbdb_DatabaseVerificationSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->verification_settings_controller;
}

/*****************************
*  cursorController  *
*****************************/

Rbdb_DatabaseCursorSettingsController* Rbdb_DatabaseSettingsController_cursorSettingsController( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->cursor_settings_controller == NULL )	{
		database_settings_controller->cursor_settings_controller = Rbdb_DatabaseCursorSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->cursor_settings_controller;
}

/*****************************
*  sequenceController  *
*****************************/

Rbdb_DatabaseSequenceSettingsController* Rbdb_DatabaseSettingsController_sequenceSettingsController( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->sequence_settings_controller == NULL )	{
		database_settings_controller->sequence_settings_controller = Rbdb_DatabaseSequenceSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->sequence_settings_controller;
}

/*****************************
*  typeSettingsController  *
*****************************/

Rbdb_DatabaseTypeSettingsController* Rbdb_DatabaseSettingsController_typeSettingsController( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	if ( database_settings_controller->type_settings_controller == NULL )	{
		database_settings_controller->type_settings_controller = Rbdb_DatabaseTypeSettingsController_new( database_settings_controller );
	}

	return database_settings_controller->type_settings_controller;
}

/*************************************
*  joinSettingsController  *
************************************/

Rbdb_DatabaseJoinSettingsController* Rbdb_DatabaseSettingsController_joinSettingsController( Rbdb_DatabaseSettingsController*	database_settings_controller )	{
	
	if ( database_settings_controller->join_settings_controller == NULL )	{
		database_settings_controller->join_settings_controller = Rbdb_DatabaseJoinSettingsController_new( database_settings_controller );
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

int Rbdb_DatabaseSettingsController_internal_createFlags( Rbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	//	FIX
	return FALSE;
}

/******************
*  openFlags  *
******************/

int Rbdb_DatabaseSettingsController_internal_openFlags( Rbdb_DatabaseSettingsController* database_settings_controller )	{
	
	Rbdb_SettingsController*											settings_controller													=	Rbdb_Environment_settingsController( database_settings_controller->parent_settings_controller->parent_environment );
	Rbdb_MemoryPoolSettingsController*						memory_pool_settings_controller							=	Rbdb_SettingsController_memoryPoolSettingsController( settings_controller );
	Rbdb_MemoryPoolReadWriteSettingsController*		memory_pool_read_write_settings_controller	=	Rbdb_MemoryPoolSettingsController_readWriteSettingsController( memory_pool_settings_controller );
	
	return	Rbdb_FileSettingsController_permitEnvironmentBasedFileNaming(	Rbdb_SettingsController_fileSettingsController( settings_controller ) )
			|	Rbdb_FileSettingsController_useEnvironmentHomePermissionsForFileNaming(	Rbdb_SettingsController_fileSettingsController( Rbdb_Environment_settingsController( database_settings_controller->parent_settings_controller->parent_environment ) ) )
			|	Rbdb_FileSettingsController_createIfNecessary(	Rbdb_SettingsController_fileSettingsController( settings_controller ) )
			|	Rbdb_DebugSettingsController_openInLockdown(	Rbdb_SettingsController_debugSettingsController( settings_controller ) )
			|	Rbdb_MemoryPoolReadWriteSettingsController_useSystemMemoryForStorage(	memory_pool_read_write_settings_controller );
}

/********************
*  closeFlags  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
//	DB_NOSYNC
int Rbdb_DatabaseSettingsController_internal_closeFlags( Rbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	//	FIX
	return FALSE;
}

/********************
*  renameFlags  *
********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_rename.html
int Rbdb_DatabaseSettingsController_internal_renameFlags( Rbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return FALSE;
}

/********************
*  emptyFlags  *
********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_truncate.html
int Rbdb_DatabaseSettingsController_internal_emptyFlags( Rbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return FALSE;
}

/********************
*  eraseFlags  *
********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_remove.html
int Rbdb_DatabaseSettingsController_internal_eraseFlags( Rbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return FALSE;
}

/*********************
*  upgradeFlags  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_upgrade.html
int Rbdb_DatabaseSettingsController_internal_upgradeFlags( Rbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{

	//	FIX
	return FALSE;
}

/*********************
*  resetIDFlags  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_fileid_reset.html
int Rbdb_DatabaseSettingsController_internal_resetIDFlags( Rbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{

	//	FIX
	return FALSE;
}

/*****************
*  syncFlags  *
*****************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_sync.html
int Rbdb_DatabaseSettingsController_internal_syncFlags( Rbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return FALSE;
}

/*************************
*  associateFlags  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_associate.html
int Rbdb_DatabaseSettingsController_internal_associateFlags( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	//	FIX
	//	if DB_CREATE is set then we want to return it unless createSecondaryIndexOnAssociation is false
	
	return Rbdb_DatabaseAssociationSettingsController_secondaryAssociationCreatesIndex( Rbdb_DatabaseSettingsController_associationSettingsController( database_settings_controller ) )
			|	Rbdb_DatabaseAssociationSettingsController_immutableSecondaryKey( Rbdb_DatabaseSettingsController_associationSettingsController( database_settings_controller ) );
}

/*********************
*  keyRangeFlags  *
*********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_key_range.html
int Rbdb_DatabaseSettingsController_internal_keyRangeFlags( Rbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return RBDB_NO_FLAGS;
}

/**************************
*  compactParameters  *
**************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
DB_COMPACT* Rbdb_DatabaseSettingsController_internal_compactParameters( Rbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{

	//	FIX
//	return &( database->database_status_controller->compact_status );
	return NULL;
}

/**********************
*  compactFlags  *
**********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
int Rbdb_DatabaseSettingsController_internal_compactFlags( Rbdb_DatabaseSettingsController* database_settings_controller __attribute__((unused)) )	{
	return RBDB_NO_FLAGS;
}

/**********************************************
*  prepareDatabaseForFileTransferFlags  *
**********************************************/

int Rbdb_DatabaseSettingsController_internal_prepareDatabaseForFileTransferFlags( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	return Rbdb_DatabaseEncryptionSettingsController_encrypted( 
					Rbdb_DatabaseSettingsController_encryptionSettingsController( 
						Rbdb_SettingsController_databaseSettingsController( 
							Rbdb_Environment_settingsController( database_settings_controller->parent_database->parent_database_controller->parent_environment ) ) ) );	
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_DatabaseSettingsController* Rbdb_DatabaseSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_DatabaseSettingsController* database_settings_controller_copy	=	Rbdb_DatabaseSettingsController_new( database_settings_controller->parent_settings_controller );
	
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
		database_settings_controller_copy->error_settings_controller										=	Rbdb_DatabaseErrorSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->error_settings_controller );
		database_settings_controller_copy->error_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->cache_settings_controller != NULL )	{
		database_settings_controller_copy->cache_settings_controller										=	Rbdb_DatabaseCacheSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->cache_settings_controller );
		database_settings_controller_copy->cache_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->association_settings_controller != NULL )	{
		database_settings_controller_copy->association_settings_controller									=	Rbdb_DatabaseAssociationSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->association_settings_controller );
		database_settings_controller_copy->association_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->compact_settings_controller != NULL )	{
		database_settings_controller_copy->compact_settings_controller										=	Rbdb_DatabaseCompactSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->compact_settings_controller );
		database_settings_controller_copy->compact_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->encryption_settings_controller != NULL )	{
		database_settings_controller_copy->encryption_settings_controller									=	Rbdb_DatabaseEncryptionSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->encryption_settings_controller );
		database_settings_controller_copy->encryption_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->verbosity_settings_controller != NULL )	{
		database_settings_controller_copy->verbosity_settings_controller									=	Rbdb_DatabaseVerbositySettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->verbosity_settings_controller );
		database_settings_controller_copy->verbosity_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->type_settings_controller != NULL )	{
		database_settings_controller_copy->type_settings_controller											=	Rbdb_DatabaseTypeSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->type_settings_controller );
		database_settings_controller_copy->type_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->sequence_settings_controller != NULL )	{
		database_settings_controller_copy->sequence_settings_controller										=	Rbdb_DatabaseSequenceSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->sequence_settings_controller );
		database_settings_controller_copy->sequence_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->cursor_settings_controller != NULL )	{
		database_settings_controller_copy->cursor_settings_controller										=	Rbdb_DatabaseCursorSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->cursor_settings_controller );
		database_settings_controller_copy->cursor_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->verification_settings_controller != NULL )	{
		database_settings_controller_copy->verification_settings_controller									=	Rbdb_DatabaseVerificationSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->verification_settings_controller );
		database_settings_controller_copy->verification_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	if ( database_settings_controller->record_settings_controller != NULL )	{
		database_settings_controller_copy->record_settings_controller										=	Rbdb_DatabaseRecordSettingsController_internal_copyOfSettingsControllerForInstance( database_settings_controller->record_settings_controller );
		database_settings_controller_copy->record_settings_controller->parent_database_settings_controller	=	database_settings_controller_copy;
	}
	
	return database_settings_controller_copy;
}

