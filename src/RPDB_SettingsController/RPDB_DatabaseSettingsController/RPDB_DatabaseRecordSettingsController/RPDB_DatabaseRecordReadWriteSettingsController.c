/*
*		RPDB::SettingsController::DatabaseSettingsController::DatabaseReadWriteSettingsController
*		RPDB::DatabaseController::Database::DatabaseSettingsController::DatabaseReadWriteSettingsController
*
*/

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseRecordReadWriteSettingsController.h"

#include "RPDB_Environment.h"
#include "RPDB_Database.h"

#include "RPDB_SettingsController.h"
#include "RPDB_DatabaseSettingsController.h"

#include "RPDB_DatabaseRecordReadWriteSettingsController.h"
#include "RPDB_DatabaseTypeSettingsController.h"
#include "RPDB_DatabaseTypeBtreeSettingsController.h"
#include "RPDB_DatabaseTypeHashSettingsController.h"

#include "RPDB_DatabaseTypeBtreeSettingsController_internal.h"
#include "RPDB_DatabaseTypeHashSettingsController_internal.h"
#include "RPDB_DatabaseRecordReadWriteSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseRecordReadWriteSettingsController* RPDB_DatabaseRecordReadWriteSettingsController_new( RPDB_DatabaseRecordSettingsController* database_record_settings_controller )	{

	RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller = calloc( 1, sizeof( RPDB_DatabaseRecordReadWriteSettingsController ) );

	database_record_read_write_settings_controller->parent_database_record_settings_controller = database_record_settings_controller;

	return database_record_read_write_settings_controller;
}


/***************************
*  free  *
***************************/
void RPDB_DatabaseRecordReadWriteSettingsController_free(	RPDB_DatabaseRecordReadWriteSettingsController** database_record_read_write_settings_controller )	{

	free( *database_record_read_write_settings_controller );
	*database_record_read_write_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseRecordReadWriteSettingsController_parentEnvironment(	RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	return database_record_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseRecordReadWriteSettingsController_parentDatabase(	RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	return database_record_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		File Settings
*******************************************************************************************************************************************************************************************/

/*****************
*  filename  *
*****************/

//	In-memory databases never intended to be preserved on disk may be created by setting the file parameter to NULL.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
char* RPDB_DatabaseRecordReadWriteSettingsController_filename( RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller )	{
	
	return database_record_read_write_settings_controller->filename;
}

/*********************
*  setFilename  *
*********************/

void RPDB_DatabaseRecordReadWriteSettingsController_setFilename(	RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller,
															char*											filename	)	{
	
	database_record_read_write_settings_controller->filename = filename;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/****************************
*  prohibitSyncOnClose  *
****************************/

//	DB_NOSYNC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
BOOL RPDB_DatabaseRecordReadWriteSettingsController_prohibitSyncOnClose( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->prohibit_sync_on_close == TRUE )	{
		return DB_NOSYNC;
	}
	return FALSE;
}

	/*********************************
	*  turnProhibitSyncOnCloseOn  *
	*********************************/

	//	DB_NOSYNC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
	void RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitSyncOnCloseOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_sync_on_close = TRUE;
	}

	/************************************
	*  turnProhibitSyncOnCloseOff  *
	************************************/

	//	DB_NOSYNC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
	void RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitSyncOnCloseOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_sync_on_close = FALSE;
	}

/********************
*  ignoreLease  *
********************/

//	DB_IGNORE_LEASE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
BOOL RPDB_DatabaseRecordReadWriteSettingsController_ignoreLease( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->ignore_lease == TRUE )	{
		return DB_IGNORE_LEASE;
	}
	return FALSE;
}

	/****************************
	*  turnIgnoreLeaseOn  *
	****************************/

	//	DB_IGNORE_LEASE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void RPDB_DatabaseRecordReadWriteSettingsController_turnIgnoreLeaseOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->ignore_lease = TRUE;
	}

	/****************************
	*  turnIgnoreLeaseOff  *
	****************************/

	//	DB_IGNORE_LEASE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void RPDB_DatabaseRecordReadWriteSettingsController_turnIgnoreLeaseOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->ignore_lease = FALSE;
	}
		
/**********************
*  returnMultiple  *
**********************/

//	Bulk operations
//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
BOOL RPDB_DatabaseRecordReadWriteSettingsController_returnMultiple( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->return_multiple == TRUE )	{
		return DB_MULTIPLE;
	}
	return FALSE;
}

	/******************************
	*  turnReturnMultipleOn  *
	******************************/

	//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void RPDB_DatabaseRecordReadWriteSettingsController_turnReturnMultipleOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->return_multiple = TRUE;
	}

	/******************************
	*  turnReturnMultipleOff  *
	******************************/

	//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void RPDB_DatabaseRecordReadWriteSettingsController_turnReturnMultipleOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->return_multiple = FALSE;
	}

/****************************
*  prohibitDuplicateData  *
****************************/

//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
//	Btree and Hash only
BOOL RPDB_DatabaseRecordReadWriteSettingsController_prohibitDuplicateData( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->prohibit_duplicate_data == TRUE )	{
		return DB_NODUPDATA;
	}
	return FALSE;
}

	/*************************************
	*  turnProhibitDuplicateDataOn  *
	*************************************/

	//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	//	Btree and Hash only
	void RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitDuplicateDataOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_duplicate_data = TRUE;
		RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOff( database_record_read_write_settings_controller );
	}

	/************************************
	*  turnProhibitDuplicateDataOff  *
	************************************/

	//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	//	Btree and Hash only
	void RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitDuplicateDataOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_duplicate_data = FALSE;
	}

/*************************
*  prohibitOverwrite  *
*************************/

//	DB_NOOVERWRITE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
BOOL RPDB_DatabaseRecordReadWriteSettingsController_prohibitOverwrite( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->prohibit_overwrite == TRUE )	{
		return DB_NOOVERWRITE;
	}
	return FALSE;
}

	/********************************
	*  turnProhibitOverwriteOn  *
	********************************/

	//	DB_NOOVERWRITE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_overwrite = TRUE;
		RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitDuplicateDataOff( database_record_read_write_settings_controller );
	}

	/********************************
	*  turnProhibitOverwriteOff  *
	********************************/

	//	DB_NOOVERWRITE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_overwrite = FALSE;
	}

/********************************
*  prohibitPageCompaction  *
********************************/

//	DB_FREELIST_ONLY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	Must be set for Hash
BOOL RPDB_DatabaseRecordReadWriteSettingsController_prohibitPageCompaction( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->prohibit_page_compaction == TRUE )	{
		return DB_FREELIST_ONLY;
	}
	return FALSE;
}

	/*************************************
	*  turnProhibitPageCompactionOn  *
	*************************************/

	//	DB_FREELIST_ONLY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
	//	Must be set for Hash
	void RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitPageCompactionOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_page_compaction = TRUE;
	}

	/*************************************
	*  turnProhibitPageCompactionOff  *
	*************************************/

	//	DB_FREELIST_ONLY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
	//	Must be set for Hash
	void RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitPageCompactionOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_page_compaction = FALSE;
	}

/********************************
*  returnPagesToFilesystem  *
********************************/

//	DB_FREE_SPACE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
BOOL RPDB_DatabaseRecordReadWriteSettingsController_returnPagesToFilesystem( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->return_pages_to_filesystem == TRUE )	{
		return DB_FREE_SPACE;
	}
	return FALSE;
}

	/*************************************
	*  turnReturnPagesToFilesystemOn  *
	*************************************/

	//	DB_FREE_SPACE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void RPDB_DatabaseRecordReadWriteSettingsController_turnReturnPagesToFilesystemOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->return_pages_to_filesystem = TRUE;
	}

	/****************************************
	*  turnReturnPagesToFilesystemOff  *
	****************************************/

	//	DB_FREE_SPACE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void RPDB_DatabaseRecordReadWriteSettingsController_turnReturnPagesToFilesystemOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->return_pages_to_filesystem = FALSE;
	}

/*****************************
*  truncateFileOnOpen  *
*****************************/

//	DB_TRUNCATE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
BOOL RPDB_DatabaseRecordReadWriteSettingsController_truncateFileOnOpen( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	if ( database_record_read_write_settings_controller->truncate )	{
		return DB_TRUNCATE;
	}
	return FALSE;
}

	/************************************
	*  turnTruncateFileOnOpenOn  *
	************************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnTruncateFileOnOpenOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->truncate = TRUE;
	}

	/*********************************
	*  turnTruncateFileOnOpenOff  *
	*********************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnTruncateFileOnOpenOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->truncate = FALSE;
	}

/************************************
*  writeLocksInsteadOfReadLocks  *
************************************/

//	DB_RMW					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL RPDB_DatabaseRecordReadWriteSettingsController_writeLocksInsteadOfReadLocks( RPDB_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{

	if ( database_read_write_settings_controller->write_locks_instead_of_read_locks == TRUE )	{
		return DB_RMW;
	}
	return FALSE;
}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	****************************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn( RPDB_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->write_locks_instead_of_read_locks = TRUE;
	}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	****************************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff( RPDB_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->write_locks_instead_of_read_locks = FALSE;
	}

/*******************************************************************************************************************************************************************************************
												Switch Settings
*******************************************************************************************************************************************************************************************/

/*************************
*  duplicates  *
*************************/

//	DB_DUP				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPDB_DatabaseRecordReadWriteSettingsController_unsortedDuplicates( RPDB_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
	
	//	If hash or btree, return ->permit_duplicates
	//	Otherwise, return false
	
	DBTYPE	database_type	=	RPDB_DatabaseTypeSettingsController_databaseType( RPDB_DatabaseSettingsController_typeSettingsController( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller ) );
	
	if (	(	database_type == DB_BTREE
			||	database_type == DB_HASH )
		&&	database_read_write_settings_controller->permit_duplicates )	{
		
		return DB_DUP;
	}
	
	return FALSE;
}

	/*******************************
	 *  turnPermitDuplicatesOn  *
	 *******************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOn( RPDB_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		
		//	If hash or btree, set ->permit_duplicates
		//	Otherwise, throw an error

		RPDB_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPDB_DatabaseSettingsController_typeSettingsController( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller );
		DBTYPE	database_type	=	RPDB_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

		if ( ! (	database_type == DB_BTREE
				||	database_type == DB_HASH ) )	{
			
			RPDB_ErrorController_throwError(	RPDB_ErrorController_new( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
												RPDB_ERROR_DUPLICATES_NOT_SUPPORTED,
												"RPDB_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOn",
												"Duplicate records are only supported by Btree and Hash database types." );
		}
		
		database_read_write_settings_controller->permit_duplicates = TRUE;
	}

	/*********************************
	 *  turnPermitDuplicatesOff  *
	 *********************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOff( RPDB_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		
		RPDB_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPDB_DatabaseSettingsController_typeSettingsController( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller );
		DBTYPE	database_type	=	RPDB_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

		//	If hash or btree, set ->permit_duplicates
		//	Otherwise, throw an error
		if ( ! (	database_type == DB_BTREE
				||	database_type == DB_HASH ) )	{
			
			RPDB_ErrorController_throwError(	RPDB_ErrorController_new( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
											 RPDB_ERROR_DUPLICATES_NOT_SUPPORTED,
											 "RPDB_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOff",
											 "Duplicate records are only supported by Btree and Hash database types." );
		}
	}

/*********************
*  sortDuplicates  *
*********************/

//	DB_DUPSORT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPDB_DatabaseRecordReadWriteSettingsController_sortedDuplicates( RPDB_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{

	DBTYPE	database_type	=	RPDB_DatabaseTypeSettingsController_databaseType( RPDB_DatabaseSettingsController_typeSettingsController( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller ) );
	
	if (	(	database_type == DB_BTREE
			 ||	database_type == DB_HASH )
		&&	database_read_write_settings_controller->sort_duplicates )	{
		
		return DB_DUPSORT;
	}
	
	return FALSE;
}

	/*****************************
	 *  turnSortDuplicatesOn  *
	 *****************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOn( RPDB_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		
		//	FIX - apply this to all errors		
		RPDB_Environment*	environment	=	NULL;
		RPDB_DatabaseSettingsController*			database_settings_controller			=	database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller;

		//	environmental settings controller
		if ( database_settings_controller->parent_settings_controller->parent_environment != NULL )	{
		
			environment	=	database_settings_controller->parent_settings_controller->parent_environment;
		}
		//	instance settings controller
		else {

			RPDB_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPDB_DatabaseSettingsController_typeSettingsController( database_settings_controller );
			DBTYPE	database_type	=	RPDB_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

			if ( ! (	database_type == DB_BTREE
						||	database_type == DB_HASH ) )	{
				environment	=	database_settings_controller->parent_database->parent_database_controller->parent_environment;				
				RPDB_ErrorController_throwError(	RPDB_ErrorController_new(  environment ),
																					RPDB_ERROR_DUPLICATES_NOT_SUPPORTED,
																					"RPDB_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOn",
																					"Duplicate records are only supported by Btree and Hash database types." );
			}
		}
		
		database_read_write_settings_controller->sort_duplicates = TRUE;
	}

	/******************************
	 *  turnSortDuplicatesOff  *
	 ******************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOff( RPDB_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{

		RPDB_Environment*	environment	=	NULL;
		RPDB_DatabaseSettingsController*			database_settings_controller			=	database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller;

		//	environmental settings controller
		if ( database_settings_controller->parent_settings_controller->parent_environment != NULL )	{
		
			environment	=	database_settings_controller->parent_settings_controller->parent_environment;
		}
		//	instance settings controller
		else {

			RPDB_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPDB_DatabaseSettingsController_typeSettingsController( database_settings_controller );
			DBTYPE	database_type	=	RPDB_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

			if ( ! (	database_type == DB_BTREE
					||	database_type == DB_HASH ) )	{

				environment	=	database_settings_controller->parent_database->parent_database_controller->parent_environment;
				RPDB_ErrorController_throwError(	RPDB_ErrorController_new(		environment ),
																																			RPDB_ERROR_DUPLICATES_NOT_SUPPORTED,
																																			"RPDB_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOff",
																																			"Duplicate records are only supported by Btree and Hash database types." );
			}
		}
		
		database_read_write_settings_controller->sort_duplicates = FALSE;
	}

/*****************************************
*  databaseAllocatesMemoryUsingMalloc  *
*****************************************/

BOOL RPDB_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->database_allocates_memory_using_malloc == TRUE )	{
		return DB_DBT_MALLOC;
	}
	return FALSE;
}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOn  *
	*************************************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_allocates_memory_using_malloc = TRUE;
		RPDB_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOff  *
	*************************************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_allocates_memory_using_malloc = FALSE;
		RPDB_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*********************************************
*  databaseAllocatesMemoryUsingRealloc  *
*********************************************/

BOOL RPDB_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->database_allocates_memory_using_malloc == TRUE )	{
		return DB_DBT_REALLOC;
	}
	return FALSE;
}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOn  *
	*************************************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_allocates_memory_using_realloc = TRUE;
		RPDB_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOff  *
	*************************************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_allocates_memory_using_realloc = FALSE;
		RPDB_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*********************************
*  applicationAllocatesMemory  *
*********************************/

BOOL RPDB_DatabaseRecordReadWriteSettingsController_applicationAllocatesMemory( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->database_allocates_memory_using_malloc == TRUE )	{
		return DB_DBT_USERMEM;
	}
	return FALSE;
}

	/*****************************************
	*  turnApplicationAllocatesMemoryOn  *
	*****************************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnApplicationAllocatesMemoryOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->application_allocates_memory = TRUE;
		RPDB_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*****************************************
	*  turnApplicationAllocatesMemoryOff  *
	*****************************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnApplicationAllocatesMemoryOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->application_allocates_memory = FALSE;
		RPDB_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*****************************
*  databaseFreesMemory  *
*****************************/

BOOL RPDB_DatabaseRecordReadWriteSettingsController_databaseFreesMemory( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->database_allocates_memory_using_malloc == TRUE )	{
		return DB_DBT_APPMALLOC;
	}
	return FALSE;
}

	/*********************************
	*  turnDatabaseFreesMemoryOn  *
	*********************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnDatabaseFreesMemoryOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_free_memory = TRUE;
		RPDB_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*********************************
	*  turnDatabaseFreesMemoryOff  *
	*********************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnDatabaseFreesMemoryOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_free_memory = FALSE;
		RPDB_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*********************
*  partialAccess  *
*********************/

BOOL RPDB_DatabaseRecordReadWriteSettingsController_partialAccess( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->database_allocates_memory_using_malloc == TRUE )	{
		return DB_DBT_PARTIAL;
	}
	return FALSE;
}

	/*****************************
	*  turnPartialAccessOn  *
	*****************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnPartialAccessOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->partial_access = TRUE;
		RPDB_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*****************************
	*  turnPartialAccessOff  *
	*****************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnPartialAccessOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->partial_access = FALSE;
		RPDB_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}
	
/*****************************
*  syncPriorToWriteReturn  *
*****************************/

//	DB_DSYNC_DB             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
BOOL RPDB_DatabaseRecordReadWriteSettingsController_syncPriorToWriteReturn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->sync_prior_to_write_return == TRUE )	{
		return DB_DSYNC_DB;
	}
	return FALSE;
}

	/**************************************
	*  turnSyncPriorToWriteReturnOn  *
	**************************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnSyncPriorToWriteReturnOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

		database_record_read_write_settings_controller->sync_prior_to_write_return = TRUE;
	}

	/************************************
	*  turnSyncPriorToWriteReturnOff  *
	************************************/

	void RPDB_DatabaseRecordReadWriteSettingsController_turnSyncPriorToWriteReturnOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

		database_record_read_write_settings_controller->sync_prior_to_write_return = FALSE;
	}

/*********************
*  dataBufferSize  *
*********************/

uint32_t RPDB_DatabaseRecordReadWriteSettingsController_dataBufferSize( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	//	If we are a local settings controller, return the actual buffer length, otherwise return the global setting
	if ( database_record_read_write_settings_controller->parent_database_record_settings_controller->parent_record == NULL )	{
		
		return database_record_read_write_settings_controller->data_buffer_size;
	}
	else	{

		//	FIX
		//		return database_record_read_write_settings_controller->parent_record->wrapped_bdb_dbt->ulen;	
		return 0;	
	}
}	

/*************************
*  setDataBufferSize  *
*************************/

void RPDB_DatabaseRecordReadWriteSettingsController_setDataBufferSize(	RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
													uint32_t							buffer_size )	{

	//	If we are a local settings controller, return the actual buffer length, otherwise return the global setting
	if ( database_record_read_write_settings_controller->parent_database_record_settings_controller->parent_record == NULL )	{
		
		database_record_read_write_settings_controller->data_buffer_size = buffer_size;
	}
	else	{

		//	FIX
//		database_record_read_write_settings_controller->parent_record->wrapped_bdb_dbt->ulen = buffer_size;
	}
}	

/*****************************
*  partialReadWriteSize  *
*****************************/

//	Returns size of partial write (if applicable)
//	It is an error to attempt a partial put using the DB->put function in a database that supports duplicate records. 
//	Partial puts in databases supporting duplicate records must be done using a DBcursor->put function.
uint32_t RPDB_DatabaseRecordReadWriteSettingsController_partialReadWriteSize( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	//	If we are a local settings controller, return the actual buffer length, otherwise return the global setting
	if ( database_record_read_write_settings_controller->parent_database_record_settings_controller->parent_record == NULL )	{
		
		return database_record_read_write_settings_controller->partial_read_write_size;
	}
	else	{

//	FIX
//		return database_record_read_write_settings_controller->parent_record->wrapped_bdb_dbt->dlen;
		return 0;	
	}

}	

/*********************************
*  setPartialReadWriteSize  *
*********************************/

void RPDB_DatabaseRecordReadWriteSettingsController_setPartialReadWriteSize(	RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
																																		uint32_t							partial_read_write_size )	{

	//	If we are a local settings controller, return the actual buffer length, otherwise return the global setting
	if ( database_record_read_write_settings_controller->parent_database_record_settings_controller->parent_record == NULL )	{
		
		database_record_read_write_settings_controller->partial_read_write_size = partial_read_write_size;
	}
	else	{

		//	FIX
//		database_record_read_write_settings_controller->parent_record->wrapped_bdb_dbt->dlen = partial_read_write_size;
	}
}	

/*****************************
*  partialReadWriteOffset  *
*****************************/

uint32_t RPDB_DatabaseRecordReadWriteSettingsController_partialReadWriteOffset( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	//	If we are a local settings controller, return the actual buffer length, otherwise return the global setting
	if ( database_record_read_write_settings_controller->parent_database_record_settings_controller->parent_record == NULL )	{
		
		return database_record_read_write_settings_controller->partial_read_write_offset;
	}
	else	{

		//	FIX
//		return database_record_read_write_settings_controller->parent_record->wrapped_bdb_dbt->doff;
		return 0;	
	}

}	

/*********************************
*  setPartialReadWriteOffset  *
*********************************/

void RPDB_DatabaseRecordReadWriteSettingsController_setPartialReadWriteOffset(	RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
															uint32_t							partial_read_write_offset )	{

	//	If we are a local settings controller, return the actual buffer length, otherwise return the global setting
	if ( database_record_read_write_settings_controller->parent_database_record_settings_controller->parent_record == NULL )	{
		
		database_record_read_write_settings_controller->partial_read_write_offset = partial_read_write_offset;
	}
	else	{

		//	FIX
//		database_record_read_write_settings_controller->parent_record->wrapped_bdb_dbt->doff = partial_read_write_offset;
	}
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  flags  *
************/

//	Most every other time flags are used when a function is called, so they can be composited on the fly
//	Here flags go in a variable rather than parameter, so we have to update them when we change a setting,
//	and then store the flags for use when appropriate (which is determined by the database handling the DBT). 
void RPDB_DatabaseRecordReadWriteSettingsController_internal_updateFlags( RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller )	{
	
	uint32_t*	flags_pointer	=	NULL;
			
	//	Make sure we're addressing the settings controller belonging to the instance
	//	If we don't have a parent_settings_controller then get our parent_record
	if ( database_record_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller == NULL )	{
		//	FIX
//		flags_pointer = &( database_record_settings_controller->parent_record->wrapped_bdb_dbt->flags );
	}
	//	Or otherwise the universal settings controller
	else	{
		flags_pointer = &( database_record_read_write_settings_controller->update_flags );
	}

	//	Update the flags stored in the DBT
	*flags_pointer =	RPDB_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( database_record_read_write_settings_controller )
						|	RPDB_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( database_record_read_write_settings_controller )
						|	RPDB_DatabaseRecordReadWriteSettingsController_applicationAllocatesMemory( database_record_read_write_settings_controller )
						|	RPDB_DatabaseRecordReadWriteSettingsController_partialAccess( database_record_read_write_settings_controller )
						|	RPDB_DatabaseRecordReadWriteSettingsController_databaseFreesMemory( database_record_read_write_settings_controller );
}	

/******************************************
*  copyOfDefaultSettingsForInstance  *
******************************************/

//	Returns a copy of cursor_settings_controller to be used for instance
RPDB_DatabaseRecordReadWriteSettingsController* RPDB_DatabaseRecordReadWriteSettingsController_internal_copyOfDefaultSettingsForInstance( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	//	create a new database_cursor settings controller without a parent
	RPDB_DatabaseRecordReadWriteSettingsController*	database_record_read_write_settings_controller_copy = RPDB_DatabaseRecordReadWriteSettingsController_new( NULL );

	//	copy settings from passed controller into new controller
	database_record_read_write_settings_controller_copy->prohibit_sync_on_close		= database_record_read_write_settings_controller->prohibit_sync_on_close;
	database_record_read_write_settings_controller_copy->ignore_lease					= database_record_read_write_settings_controller->ignore_lease;	

	database_record_read_write_settings_controller_copy->return_multiple				= database_record_read_write_settings_controller->return_multiple;	
	database_record_read_write_settings_controller_copy->append_data					= database_record_read_write_settings_controller->append_data;	
	database_record_read_write_settings_controller_copy->prohibit_duplicate_data		= database_record_read_write_settings_controller->prohibit_duplicate_data;	
	
	database_record_read_write_settings_controller_copy->prohibit_overwrite			= database_record_read_write_settings_controller->prohibit_overwrite;	
	database_record_read_write_settings_controller_copy->prohibit_page_compaction		= database_record_read_write_settings_controller->prohibit_page_compaction;	
	database_record_read_write_settings_controller_copy->return_pages_to_filesystem	= database_record_read_write_settings_controller->return_pages_to_filesystem;	
	database_record_read_write_settings_controller_copy->multiple_targets				= database_record_read_write_settings_controller->multiple_targets;	
	database_record_read_write_settings_controller_copy->partial_access				= database_record_read_write_settings_controller->partial_access;		

	//	return new controller
	return database_record_read_write_settings_controller_copy;
}
	
/**********************
*  writeFlags  *
**********************/
	
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
int RPDB_DatabaseRecordReadWriteSettingsController_internal_writeFlags( RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller)	{
	//	Setter functions ensure exclusivity, so we should be able to simply | together the results
	return	RPDB_DatabaseRecordReadWriteSettingsController_prohibitDuplicateData( database_record_read_write_settings_controller )
			|	RPDB_DatabaseRecordReadWriteSettingsController_prohibitOverwrite( database_record_read_write_settings_controller );
}

/*********************
*  deleteFlags  *
*********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_del.html
int RPDB_DatabaseRecordReadWriteSettingsController_internal_deleteFlags( RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller __attribute__((unused)) )	{

	return RPDB_NO_FLAGS;
}

/*********************
*  existsFlags  *
*********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_del.html
int RPDB_DatabaseRecordReadWriteSettingsController_internal_existsFlags( RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller )	{

	return RPDB_DatabaseRecordReadWriteSettingsController_writeLocksInsteadOfReadLocks(	database_record_read_write_settings_controller );
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseRecordReadWriteSettingsController* RPDB_DatabaseRecordReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller_copy	=	RPDB_DatabaseRecordReadWriteSettingsController_new( database_record_read_write_settings_controller->parent_database_record_settings_controller );

	//	Instances and Pointers
	database_record_read_write_settings_controller_copy->write_locks_instead_of_read_locks	=	database_record_read_write_settings_controller->write_locks_instead_of_read_locks;
	database_record_read_write_settings_controller_copy->prohibit_overwrite				=	database_record_read_write_settings_controller->prohibit_overwrite;
	database_record_read_write_settings_controller_copy->return_multiple					=	database_record_read_write_settings_controller->return_multiple;
	database_record_read_write_settings_controller_copy->prohibit_page_compaction			=	database_record_read_write_settings_controller->prohibit_page_compaction;
	database_record_read_write_settings_controller_copy->return_pages_to_filesystem		=	database_record_read_write_settings_controller->return_pages_to_filesystem;
	database_record_read_write_settings_controller_copy->partial_access					=	database_record_read_write_settings_controller->partial_access;
	database_record_read_write_settings_controller_copy->append_data						=	database_record_read_write_settings_controller->append_data;
	database_record_read_write_settings_controller_copy->ignore_lease						=	database_record_read_write_settings_controller->ignore_lease;
	database_record_read_write_settings_controller_copy->filename							=	database_record_read_write_settings_controller->filename;
	database_record_read_write_settings_controller_copy->truncate							=	database_record_read_write_settings_controller->truncate;
	database_record_read_write_settings_controller_copy->multiple_targets					=	database_record_read_write_settings_controller->multiple_targets;
	database_record_read_write_settings_controller_copy->prohibit_duplicate_data			=	database_record_read_write_settings_controller->prohibit_duplicate_data;
	database_record_read_write_settings_controller_copy->prohibit_sync_on_close			=	database_record_read_write_settings_controller->prohibit_sync_on_close;
	database_record_read_write_settings_controller_copy->permit_duplicates					=	database_record_read_write_settings_controller->permit_duplicates;
	database_record_read_write_settings_controller_copy->sort_duplicates					=	database_record_read_write_settings_controller->sort_duplicates;

	database_record_read_write_settings_controller_copy->update_flags	=	database_record_read_write_settings_controller->update_flags;
	database_record_read_write_settings_controller_copy->database_allocates_memory_using_malloc	=	database_record_read_write_settings_controller->database_allocates_memory_using_malloc;
	database_record_read_write_settings_controller_copy->data_buffer_size	=	database_record_read_write_settings_controller->data_buffer_size;
	database_record_read_write_settings_controller_copy->database_allocates_memory_using_realloc	=	database_record_read_write_settings_controller->database_allocates_memory_using_realloc;
	database_record_read_write_settings_controller_copy->partial_read_write_size	=	database_record_read_write_settings_controller->partial_read_write_size;
	database_record_read_write_settings_controller_copy->partial_access	=	database_record_read_write_settings_controller->partial_access;
	database_record_read_write_settings_controller_copy->sync_prior_to_write_return	=	database_record_read_write_settings_controller->sync_prior_to_write_return;
	database_record_read_write_settings_controller_copy->database_free_memory	=	database_record_read_write_settings_controller->database_free_memory;
	database_record_read_write_settings_controller_copy->application_allocates_memory	=	database_record_read_write_settings_controller->application_allocates_memory;
	database_record_read_write_settings_controller_copy->partial_read_write_offset	=	database_record_read_write_settings_controller->partial_read_write_offset;

	return database_record_read_write_settings_controller_copy;
}

