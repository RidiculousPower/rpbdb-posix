/*
*		RPbdb::SettingsController::DatabaseSettingsController::DatabaseReadWriteSettingsController
*		RPbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseReadWriteSettingsController
*
*/

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseRecordReadWriteSettingsController.h"

#include "Environment.h"
#include "Database.h"

#include "SettingsController.h"
#include "DatabaseSettingsController.h"

#include "DatabaseRecordReadWriteSettingsController.h"
#include "DatabaseTypeSettingsController.h"
#include "DatabaseTypeBtreeSettingsController.h"
#include "DatabaseTypeHashSettingsController.h"

#include "DatabaseTypeBtreeSettingsController_internal.h"
#include "DatabaseTypeHashSettingsController_internal.h"
#include "DatabaseRecordReadWriteSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_DatabaseRecordReadWriteSettingsController* RPbdb_DatabaseRecordReadWriteSettingsController_new( RPbdb_DatabaseRecordSettingsController* database_record_settings_controller )	{

	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseRecordReadWriteSettingsController ) );

	database_record_read_write_settings_controller->parent_database_record_settings_controller = database_record_settings_controller;

	return database_record_read_write_settings_controller;
}


/***************************
*  free  *
***************************/
void RPbdb_DatabaseRecordReadWriteSettingsController_free(	RPbdb_DatabaseRecordReadWriteSettingsController** database_record_read_write_settings_controller )	{

	free( *database_record_read_write_settings_controller );
	*database_record_read_write_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseRecordReadWriteSettingsController_parentEnvironment(	RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	return database_record_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseRecordReadWriteSettingsController_parentDatabase(	RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
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
char* RPbdb_DatabaseRecordReadWriteSettingsController_filename( RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller )	{
	
	return database_record_read_write_settings_controller->filename;
}

/*********************
*  setFilename  *
*********************/

void RPbdb_DatabaseRecordReadWriteSettingsController_setFilename(	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller,
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
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_prohibitSyncOnClose( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->prohibit_sync_on_close == TRUE )	{
		return DB_NOSYNC;
	}
	return FALSE;
}

	/*********************************
	*  turnProhibitSyncOnCloseOn  *
	*********************************/

	//	DB_NOSYNC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitSyncOnCloseOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_sync_on_close = TRUE;
	}

	/************************************
	*  turnProhibitSyncOnCloseOff  *
	************************************/

	//	DB_NOSYNC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitSyncOnCloseOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_sync_on_close = FALSE;
	}

/********************
*  ignoreLease  *
********************/

//	DB_IGNORE_LEASE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_ignoreLease( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->ignore_lease == TRUE )	{
		return DB_IGNORE_LEASE;
	}
	return FALSE;
}

	/****************************
	*  turnIgnoreLeaseOn  *
	****************************/

	//	DB_IGNORE_LEASE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnIgnoreLeaseOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->ignore_lease = TRUE;
	}

	/****************************
	*  turnIgnoreLeaseOff  *
	****************************/

	//	DB_IGNORE_LEASE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnIgnoreLeaseOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->ignore_lease = FALSE;
	}
		
/**********************
*  returnMultiple  *
**********************/

//	Bulk operations
//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_returnMultiple( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->return_multiple == TRUE )	{
		return DB_MULTIPLE;
	}
	return FALSE;
}

	/******************************
	*  turnReturnMultipleOn  *
	******************************/

	//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnReturnMultipleOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->return_multiple = TRUE;
	}

	/******************************
	*  turnReturnMultipleOff  *
	******************************/

	//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnReturnMultipleOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->return_multiple = FALSE;
	}

/****************************
*  writeDataOnlyIfNonDuplicate  *
****************************/

//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
//	Btree and Hash only
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_writeDataOnlyIfNonDuplicate( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->write_data_only_if_non_duplicate == TRUE )	{
		return DB_NODUPDATA;
	}
	return FALSE;
}

	/*************************************
	*  turnWriteDataOnlyIfNonDuplicateOn  *
	*************************************/

	//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	//	Btree and Hash only
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->write_data_only_if_non_duplicate = TRUE;
		RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOff( database_record_read_write_settings_controller );
	}

	/************************************
	*  turnWriteDataOnlyIfNonDuplicateOff  *
	************************************/

	//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	//	Btree and Hash only
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->write_data_only_if_non_duplicate = FALSE;
	}

/*************************
*  prohibitOverwrite  *
*************************/

//	DB_NOOVERWRITE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_prohibitOverwrite( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->prohibit_overwrite == TRUE )	{
		return DB_NOOVERWRITE;
	}
	return FALSE;
}

	/********************************
	*  turnProhibitOverwriteOn  *
	********************************/

	//	DB_NOOVERWRITE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_overwrite = TRUE;
		RPbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOff( database_record_read_write_settings_controller );
	}

	/********************************
	*  turnProhibitOverwriteOff  *
	********************************/

	//	DB_NOOVERWRITE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_overwrite = FALSE;
	}

/********************************
*  prohibitPageCompaction  *
********************************/

//	DB_FREELIST_ONLY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	Must be set for Hash
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_prohibitPageCompaction( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

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
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitPageCompactionOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_page_compaction = TRUE;
	}

	/*************************************
	*  turnProhibitPageCompactionOff  *
	*************************************/

	//	DB_FREELIST_ONLY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
	//	Must be set for Hash
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitPageCompactionOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_page_compaction = FALSE;
	}

/********************************
*  returnPagesToFilesystem  *
********************************/

//	DB_FREE_SPACE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_returnPagesToFilesystem( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->return_pages_to_filesystem == TRUE )	{
		return DB_FREE_SPACE;
	}
	return FALSE;
}

	/*************************************
	*  turnReturnPagesToFilesystemOn  *
	*************************************/

	//	DB_FREE_SPACE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnReturnPagesToFilesystemOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->return_pages_to_filesystem = TRUE;
	}

	/****************************************
	*  turnReturnPagesToFilesystemOff  *
	****************************************/

	//	DB_FREE_SPACE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnReturnPagesToFilesystemOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->return_pages_to_filesystem = FALSE;
	}

/*****************************
*  truncateFileOnOpen  *
*****************************/

//	DB_TRUNCATE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_truncateFileOnOpen( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	if ( database_record_read_write_settings_controller->truncate )	{
		return DB_TRUNCATE;
	}
	return FALSE;
}

	/************************************
	*  turnTruncateFileOnOpenOn  *
	************************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnTruncateFileOnOpenOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->truncate = TRUE;
	}

	/*********************************
	*  turnTruncateFileOnOpenOff  *
	*********************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnTruncateFileOnOpenOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->truncate = FALSE;
	}

/************************************
*  writeLocksInsteadOfReadLocks  *
************************************/

//	DB_RMW					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_writeLocksInsteadOfReadLocks( RPbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{

	if ( database_read_write_settings_controller->write_locks_instead_of_read_locks == TRUE )	{
		return DB_RMW;
	}
	return FALSE;
}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	****************************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->write_locks_instead_of_read_locks = TRUE;
	}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	****************************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->write_locks_instead_of_read_locks = FALSE;
	}

/*************************
*  duplicates  *
*************************/

//	DB_DUP				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_unsortedDuplicates( RPbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
	
	//	If hash or btree, return ->permit_duplicates
	//	Otherwise, return false
	RPbdb_DatabaseSettingsController*			database_settings_controller			=	database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller;
	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
	DBTYPE	database_type	=	RPbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );
	
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

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		
		//	If hash or btree, set ->permit_duplicates
		//	Otherwise, throw an error

		RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller );
		DBTYPE	database_type	=	RPbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

		if ( ! (	database_type == DB_BTREE
				||	database_type == DB_HASH ) )	{
			
			RPbdb_ErrorController_throwError(	RPbdb_ErrorController_new( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																				RPBDB_ERROR_DUPLICATES_NOT_SUPPORTED,
																				"DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOn",
																				"Duplicate records are only supported by Btree and Hash database types." );
		}
		
		database_read_write_settings_controller->permit_duplicates = TRUE;
	}

	/*********************************
	 *  turnPermitDuplicatesOff  *
	 *********************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		
		RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller );
		DBTYPE	database_type	=	RPbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

		//	If hash or btree, set ->permit_duplicates
		//	Otherwise, throw an error
		if ( ! (	database_type == DB_BTREE
				||	database_type == DB_HASH ) )	{
			
			RPbdb_ErrorController_throwError(	RPbdb_ErrorController_new( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																				 RPBDB_ERROR_DUPLICATES_NOT_SUPPORTED,
																				 "DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOff",
																				 "Duplicate records are only supported by Btree and Hash database types." );
		}
		database_read_write_settings_controller->sort_duplicates		= FALSE;
		database_read_write_settings_controller->permit_duplicates	= FALSE;
	}

/*********************
*  sortedDuplicates  *
*********************/

//	DB_DUPSORT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_sortedDuplicates( RPbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{

	RPbdb_DatabaseSettingsController*			parent_database_settings_controller	=	database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller;

	RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller		=	RPbdb_DatabaseSettingsController_typeSettingsController( parent_database_settings_controller );

	DBTYPE	database_type	=	RPbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );
	
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

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		
		//	FIX - apply this to all errors		
		RPbdb_Environment*	environment	=	NULL;
		RPbdb_DatabaseSettingsController*			database_settings_controller			=	database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller;

		//	environmental settings controller
		if ( database_settings_controller->parent_settings_controller->parent_environment != NULL )	{
		
			environment	=	database_settings_controller->parent_settings_controller->parent_environment;
		}
		//	instance settings controller
		else {

			RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
			DBTYPE	database_type	=	RPbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

			if ( ! (	database_type == DB_BTREE
						||	database_type == DB_HASH ) )	{
				environment	=	database_settings_controller->parent_database->parent_database_controller->parent_environment;				
				RPbdb_ErrorController_throwError(	RPbdb_ErrorController_new(  environment ),
																					RPBDB_ERROR_DUPLICATES_NOT_SUPPORTED,
																					"DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOn",
																					"Duplicate records are only supported by Btree and Hash database types." );
			}
		}
		
		//	if we are sorting duplicates we don't want errors for overwriting the same record - just ignore
		RPbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOn( database_read_write_settings_controller );
		
		database_read_write_settings_controller->sort_duplicates = TRUE;
	}

	/******************************
	 *  turnSortDuplicatesOff  *
	 ******************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{

		RPbdb_Environment*	environment	=	NULL;
		RPbdb_DatabaseSettingsController*			database_settings_controller			=	database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller;

		//	environmental settings controller
		if ( database_settings_controller->parent_settings_controller->parent_environment != NULL )	{
		
			environment	=	database_settings_controller->parent_settings_controller->parent_environment;
		}
		//	instance settings controller
		else {

			RPbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
			DBTYPE	database_type	=	RPbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

			if ( ! (	database_type == DB_BTREE
					||	database_type == DB_HASH ) )	{

				environment	=	database_settings_controller->parent_database->parent_database_controller->parent_environment;
				RPbdb_ErrorController_throwError(	RPbdb_ErrorController_new(		environment ),
																																			RPBDB_ERROR_DUPLICATES_NOT_SUPPORTED,
																																			"DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOff",
																																			"Duplicate records are only supported by Btree and Hash database types." );
			}
		}

		//	this flag only makes sense with sorted duplicates, so if they're not on it goes off
		RPbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOff( database_read_write_settings_controller );
		
		database_read_write_settings_controller->sort_duplicates		= FALSE;
		database_read_write_settings_controller->permit_duplicates	= FALSE;
	}

/***************
*  duplicates  *
***************/

BOOL RPbdb_DatabaseRecordReadWriteSettingsController_duplicates( RPbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{

	BOOL	c_has_duplicates	=	FALSE;

	if (		RPbdb_DatabaseRecordReadWriteSettingsController_sortedDuplicates( database_read_write_settings_controller )
			||	RPbdb_DatabaseRecordReadWriteSettingsController_unsortedDuplicates( database_read_write_settings_controller ) )	{
	
		c_has_duplicates	=	TRUE;
	}
	
	return c_has_duplicates;
}

/*****************************************
*  databaseAllocatesMemoryUsingMalloc  *
*****************************************/

BOOL RPbdb_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->database_allocates_memory_using_malloc == TRUE )	{
		return DB_DBT_MALLOC;
	}
	return FALSE;
}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOn  *
	*************************************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_allocates_memory_using_malloc = TRUE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOff  *
	*************************************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_allocates_memory_using_malloc = FALSE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*********************************************
*  databaseAllocatesMemoryUsingRealloc  *
*********************************************/

BOOL RPbdb_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->database_allocates_memory_using_realloc == TRUE )	{
		return DB_DBT_REALLOC;
	}
	return FALSE;
}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOn  *
	*************************************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_allocates_memory_using_realloc = TRUE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOff  *
	*************************************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_allocates_memory_using_realloc = FALSE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*********************************
*  applicationAllocatesMemory  *
*********************************/

BOOL RPbdb_DatabaseRecordReadWriteSettingsController_applicationAllocatesMemory( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->application_allocates_memory == TRUE )	{
		return DB_DBT_USERMEM;
	}
	return FALSE;
}

	/*****************************************
	*  turnApplicationAllocatesMemoryOn  *
	*****************************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnApplicationAllocatesMemoryOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->application_allocates_memory = TRUE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*****************************************
	*  turnApplicationAllocatesMemoryOff  *
	*****************************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnApplicationAllocatesMemoryOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->application_allocates_memory = FALSE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*****************************
*  databaseFreesMemory  *
*****************************/

BOOL RPbdb_DatabaseRecordReadWriteSettingsController_databaseFreesMemory( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->database_free_memory == TRUE )	{
		return DB_DBT_APPMALLOC;
	}
	return FALSE;
}

	/*********************************
	*  turnDatabaseFreesMemoryOn  *
	*********************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseFreesMemoryOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_free_memory = TRUE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*********************************
	*  turnDatabaseFreesMemoryOff  *
	*********************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseFreesMemoryOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_free_memory = FALSE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*********************
*  partialAccess  *
*********************/

BOOL RPbdb_DatabaseRecordReadWriteSettingsController_partialAccess( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->partial_access == TRUE )	{
		return DB_DBT_PARTIAL;
	}
	return FALSE;
}

	/*****************************
	*  turnPartialAccessOn  *
	*****************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnPartialAccessOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->partial_access = TRUE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*************************
	*  turnPartialAccessOff  *
	*************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnPartialAccessOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->partial_access = FALSE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*****************************
*  syncPriorToWriteReturn  *
*****************************/

//	DB_DSYNC_DB             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_syncPriorToWriteReturn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	return database_record_read_write_settings_controller->sync_prior_to_write_return;
}

	/**************************************
	*  turnSyncPriorToWriteReturnOn  *
	**************************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnSyncPriorToWriteReturnOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

		database_record_read_write_settings_controller->sync_prior_to_write_return = TRUE;
	}

	/************************************
	*  turnSyncPriorToWriteReturnOff  *
	************************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnSyncPriorToWriteReturnOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

		database_record_read_write_settings_controller->sync_prior_to_write_return = FALSE;
	}

/*******************
*  storeKeyTyping  *
*******************/

CerializeType RPbdb_DatabaseRecordReadWriteSettingsController_storeKeyTyping( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	return database_record_read_write_settings_controller->store_key_typing;
}

	/*************************
	*  turnStoreKeyTypingOn  *
	*************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreKeyTypingOn(	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller,
																																						CerializeType										database_record_storage_type	)	{
	
		database_record_read_write_settings_controller->store_key_typing = database_record_storage_type;
	}

	/**************************
	*  turnStoreKeyTypingOff  *
	**************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreKeyTypingOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->store_key_typing = FALSE;
	}

/********************
*  storeDataTyping  *
********************/

CerializeType RPbdb_DatabaseRecordReadWriteSettingsController_storeDataTyping( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	return database_record_read_write_settings_controller->store_data_typing;
}

	/**************************
	*  turnStoreDataTypingOn  *
	**************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreDataTypingOn(	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller,
																																							CerializeType										database_record_storage_type	)	{
	
		database_record_read_write_settings_controller->store_data_typing = database_record_storage_type;
	}

	/***************************
	*  turnStoreDataTypingOff  *
	***************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreDataTypingOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->store_data_typing = FALSE;
	}

/*****************
*  recordTyping  *
*****************/

BOOL RPbdb_DatabaseRecordReadWriteSettingsController_recordTyping( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	return database_record_read_write_settings_controller->record_typing;
}

	/***********************
	*  turnRecordTypingOn  *
	***********************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnRecordTypingOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->record_typing = TRUE;
		database_record_read_write_settings_controller->has_footer	=	TRUE;
	}

	/************************
	*  turnRecordTypingOff  *
	************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnRecordTypingOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->record_typing = FALSE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_determineIfHasFooter( database_record_read_write_settings_controller );
	}

/******************
*  creationStamp  *
******************/

BOOL RPbdb_DatabaseRecordReadWriteSettingsController_creationStamp( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	return database_record_read_write_settings_controller->creation_stamp;
}

	/************************
	*  turnCreationStampOn  *
	************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnCreationStampOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->creation_stamp = TRUE;
		database_record_read_write_settings_controller->has_footer	=	TRUE;
	}

	/*************************
	*  turnCreationStampOff  *
	*************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnCreationStampOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->creation_stamp = FALSE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_determineIfHasFooter( database_record_read_write_settings_controller );
	}

/**********************
*  modificationStamp  *
**********************/

BOOL RPbdb_DatabaseRecordReadWriteSettingsController_modificationStamp( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->modification_stamp == TRUE )	{
		return TRUE;
	}
	return FALSE;
}

	/****************************
	*  turnModificationStampOn  *
	****************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnModificationStampOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->modification_stamp = TRUE;
		database_record_read_write_settings_controller->has_footer	=	TRUE;
	}

	/*****************************
	*  turnModificationStampOff  *
	*****************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnModificationStampOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->modification_stamp = FALSE;
		RPbdb_DatabaseRecordReadWriteSettingsController_internal_determineIfHasFooter( database_record_read_write_settings_controller );
	}

/*********************
*  storeFileNotPath  *
*********************/

BOOL RPbdb_DatabaseRecordReadWriteSettingsController_storeFileNotPath( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->store_file_not_path == TRUE )	{
		return TRUE;
	}
	return FALSE;
}

	/***************************
	*  turnStoreFileNotPathOn  *
	***************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreFileNotPathOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->store_file_not_path = TRUE;
	}

	/****************************
	*  turnStoreFileNotPathOff  *
	****************************/

	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreFileNotPathOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->store_file_not_path = FALSE;
	}
	
/*******************************************************************************************************************************************************************************************
																													Setter Methods
*******************************************************************************************************************************************************************************************/

/*********************
*  dataBufferSize  *
*********************/

uint32_t RPbdb_DatabaseRecordReadWriteSettingsController_dataBufferSize( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

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

void RPbdb_DatabaseRecordReadWriteSettingsController_setDataBufferSize(	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
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
uint32_t RPbdb_DatabaseRecordReadWriteSettingsController_partialReadWriteSize( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

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

void RPbdb_DatabaseRecordReadWriteSettingsController_setPartialReadWriteSize(	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
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

uint32_t RPbdb_DatabaseRecordReadWriteSettingsController_partialReadWriteOffset( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

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

void RPbdb_DatabaseRecordReadWriteSettingsController_setPartialReadWriteOffset(	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
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
																													Callback Methods
*******************************************************************************************************************************************************************************************/

/*************************************
*  setWriteFailedCallbackMethod  *
*************************************/
/*
void RPbdb_MessageSettingsController_setWriteFailedCallbackMethod(	RPbdb_MessageSettingsController*				message_settings_controller,
 																	void *(write_failed_callback_method)( RPbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;
	
	message_settings_controller->write_failed_callback_method = write_failed_callback_method;
	//	Make sure we have our internal callback enabled
	
	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& RPbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*********************************
*  writeFailedCallbackMethod  *
*********************************/
/*
void *(write_failed_callback_method)( RPbdb_Environment*	environment ) RPbdb_MessageSettingsController_writeFailedCallbackMethod(	RPbdb_MessageSettingsController*		message_settings_controller )	{
	
	return message_settings_controller->write_failed_callback_method;
}
*/

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
void RPbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller )	{
	
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
	*flags_pointer =	RPbdb_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( database_record_read_write_settings_controller )
										|	RPbdb_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( database_record_read_write_settings_controller )
										|	RPbdb_DatabaseRecordReadWriteSettingsController_applicationAllocatesMemory( database_record_read_write_settings_controller )
										|	RPbdb_DatabaseRecordReadWriteSettingsController_partialAccess( database_record_read_write_settings_controller )
										|	RPbdb_DatabaseRecordReadWriteSettingsController_databaseFreesMemory( database_record_read_write_settings_controller );
}	

/******************************************
*  copyOfDefaultSettingsForInstance  *
******************************************/

//	Returns a copy of cursor_settings_controller to be used for instance
RPbdb_DatabaseRecordReadWriteSettingsController* RPbdb_DatabaseRecordReadWriteSettingsController_internal_copyOfDefaultSettingsForInstance( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	//	create a new database_cursor settings controller without a parent
	RPbdb_DatabaseRecordReadWriteSettingsController*	database_record_read_write_settings_controller_copy = RPbdb_DatabaseRecordReadWriteSettingsController_new( NULL );

	//	copy settings from passed controller into new controller
	database_record_read_write_settings_controller_copy->prohibit_sync_on_close		= database_record_read_write_settings_controller->prohibit_sync_on_close;
	database_record_read_write_settings_controller_copy->ignore_lease					= database_record_read_write_settings_controller->ignore_lease;	

	database_record_read_write_settings_controller_copy->return_multiple				= database_record_read_write_settings_controller->return_multiple;	
	database_record_read_write_settings_controller_copy->append_data					= database_record_read_write_settings_controller->append_data;	
	database_record_read_write_settings_controller_copy->write_data_only_if_non_duplicate		= database_record_read_write_settings_controller->write_data_only_if_non_duplicate;	
	
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
int RPbdb_DatabaseRecordReadWriteSettingsController_internal_writeFlags( RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller)	{
	//	Setter functions ensure exclusivity, so we should be able to simply | together the results
	return	RPbdb_DatabaseRecordReadWriteSettingsController_writeDataOnlyIfNonDuplicate( database_record_read_write_settings_controller )
			|	RPbdb_DatabaseRecordReadWriteSettingsController_prohibitOverwrite( database_record_read_write_settings_controller );
}

/*********************
*  deleteFlags  *
*********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_del.html
int RPbdb_DatabaseRecordReadWriteSettingsController_internal_deleteFlags( RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller __attribute__((unused)) )	{

	return RPBDB_NO_FLAGS;
}

/*********************
*  existsFlags  *
*********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_del.html
int RPbdb_DatabaseRecordReadWriteSettingsController_internal_existsFlags( RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller )	{

	return RPbdb_DatabaseRecordReadWriteSettingsController_writeLocksInsteadOfReadLocks(	database_record_read_write_settings_controller );
}

/**************
*  hasFooter  *
**************/

BOOL RPbdb_DatabaseRecordReadWriteSettingsController_internal_hasFooter( RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller )	{

	return database_record_read_write_settings_controller->has_footer;
}

/*************************
*  determineIfHasFooter  *
*************************/

void RPbdb_DatabaseRecordReadWriteSettingsController_internal_determineIfHasFooter( RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller )	{
	
	if (		database_record_read_write_settings_controller->record_typing
			||	database_record_read_write_settings_controller->creation_stamp
			||	database_record_read_write_settings_controller->modification_stamp )	{
		
		database_record_read_write_settings_controller->has_footer = TRUE;	

	}
	else {

		database_record_read_write_settings_controller->has_footer = FALSE;
		
	}

}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseRecordReadWriteSettingsController* RPbdb_DatabaseRecordReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller_copy	=	RPbdb_DatabaseRecordReadWriteSettingsController_new( database_record_read_write_settings_controller->parent_database_record_settings_controller );

	//	Instances and Pointers
	database_record_read_write_settings_controller_copy->write_locks_instead_of_read_locks				=	database_record_read_write_settings_controller->write_locks_instead_of_read_locks;
	database_record_read_write_settings_controller_copy->prohibit_overwrite												=	database_record_read_write_settings_controller->prohibit_overwrite;
	database_record_read_write_settings_controller_copy->return_multiple													=	database_record_read_write_settings_controller->return_multiple;
	database_record_read_write_settings_controller_copy->prohibit_page_compaction									=	database_record_read_write_settings_controller->prohibit_page_compaction;
	database_record_read_write_settings_controller_copy->return_pages_to_filesystem								=	database_record_read_write_settings_controller->return_pages_to_filesystem;
	database_record_read_write_settings_controller_copy->partial_access														=	database_record_read_write_settings_controller->partial_access;
	database_record_read_write_settings_controller_copy->append_data															=	database_record_read_write_settings_controller->append_data;
	database_record_read_write_settings_controller_copy->ignore_lease															=	database_record_read_write_settings_controller->ignore_lease;
	database_record_read_write_settings_controller_copy->filename																	=	database_record_read_write_settings_controller->filename;
	database_record_read_write_settings_controller_copy->truncate																	=	database_record_read_write_settings_controller->truncate;
	database_record_read_write_settings_controller_copy->multiple_targets													=	database_record_read_write_settings_controller->multiple_targets;
	database_record_read_write_settings_controller_copy->write_data_only_if_non_duplicate					=	database_record_read_write_settings_controller->write_data_only_if_non_duplicate;
	database_record_read_write_settings_controller_copy->prohibit_sync_on_close										=	database_record_read_write_settings_controller->prohibit_sync_on_close;
	database_record_read_write_settings_controller_copy->permit_duplicates												=	database_record_read_write_settings_controller->permit_duplicates;
	database_record_read_write_settings_controller_copy->sort_duplicates													=	database_record_read_write_settings_controller->sort_duplicates;

	database_record_read_write_settings_controller_copy->update_flags															=	database_record_read_write_settings_controller->update_flags;
	database_record_read_write_settings_controller_copy->database_allocates_memory_using_malloc		=	database_record_read_write_settings_controller->database_allocates_memory_using_malloc;
	database_record_read_write_settings_controller_copy->data_buffer_size													=	database_record_read_write_settings_controller->data_buffer_size;
	database_record_read_write_settings_controller_copy->database_allocates_memory_using_realloc	=	database_record_read_write_settings_controller->database_allocates_memory_using_realloc;
	database_record_read_write_settings_controller_copy->partial_read_write_size									=	database_record_read_write_settings_controller->partial_read_write_size;
	database_record_read_write_settings_controller_copy->partial_access														=	database_record_read_write_settings_controller->partial_access;
	database_record_read_write_settings_controller_copy->sync_prior_to_write_return								=	database_record_read_write_settings_controller->sync_prior_to_write_return;
	database_record_read_write_settings_controller_copy->database_free_memory											=	database_record_read_write_settings_controller->database_free_memory;
	database_record_read_write_settings_controller_copy->application_allocates_memory							=	database_record_read_write_settings_controller->application_allocates_memory;
	database_record_read_write_settings_controller_copy->partial_read_write_offset								=	database_record_read_write_settings_controller->partial_read_write_offset;

	database_record_read_write_settings_controller_copy->store_key_typing													=	database_record_read_write_settings_controller->store_key_typing;
	database_record_read_write_settings_controller_copy->store_data_typing												=	database_record_read_write_settings_controller->store_data_typing;
	database_record_read_write_settings_controller_copy->record_typing														=	database_record_read_write_settings_controller->record_typing;
	database_record_read_write_settings_controller_copy->creation_stamp														=	database_record_read_write_settings_controller->creation_stamp;
	database_record_read_write_settings_controller_copy->modification_stamp												=	database_record_read_write_settings_controller->modification_stamp;
	database_record_read_write_settings_controller_copy->has_footer																=	database_record_read_write_settings_controller->has_footer;

	return database_record_read_write_settings_controller_copy;
}

