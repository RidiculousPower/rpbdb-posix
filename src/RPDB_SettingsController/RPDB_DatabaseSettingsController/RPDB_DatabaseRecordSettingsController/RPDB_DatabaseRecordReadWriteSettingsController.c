/*
*		Rbdb::SettingsController::DatabaseSettingsController::DatabaseReadWriteSettingsController
*		Rbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseReadWriteSettingsController
*
*/

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"

#include "Rbdb_Environment.h"
#include "Rbdb_Database.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_DatabaseSettingsController.h"

#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"
#include "Rbdb_DatabaseTypeSettingsController.h"
#include "Rbdb_DatabaseTypeBtreeSettingsController.h"
#include "Rbdb_DatabaseTypeHashSettingsController.h"

#include "Rbdb_DatabaseTypeBtreeSettingsController_internal.h"
#include "Rbdb_DatabaseTypeHashSettingsController_internal.h"
#include "Rbdb_DatabaseRecordReadWriteSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_DatabaseRecordReadWriteSettingsController* Rbdb_DatabaseRecordReadWriteSettingsController_new( Rbdb_DatabaseRecordSettingsController* database_record_settings_controller )	{

	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseRecordReadWriteSettingsController ) );

	database_record_read_write_settings_controller->parent_database_record_settings_controller = database_record_settings_controller;

	return database_record_read_write_settings_controller;
}


/***************************
*  free  *
***************************/
void Rbdb_DatabaseRecordReadWriteSettingsController_free(	Rbdb_DatabaseRecordReadWriteSettingsController** database_record_read_write_settings_controller )	{

	free( *database_record_read_write_settings_controller );
	*database_record_read_write_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseRecordReadWriteSettingsController_parentEnvironment(	Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	return database_record_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseRecordReadWriteSettingsController_parentDatabase(	Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
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
char* Rbdb_DatabaseRecordReadWriteSettingsController_filename( Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller )	{
	
	return database_record_read_write_settings_controller->filename;
}

/*********************
*  setFilename  *
*********************/

void Rbdb_DatabaseRecordReadWriteSettingsController_setFilename(	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller,
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
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_prohibitSyncOnClose( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->prohibit_sync_on_close == TRUE )	{
		return DB_NOSYNC;
	}
	return FALSE;
}

	/*********************************
	*  turnProhibitSyncOnCloseOn  *
	*********************************/

	//	DB_NOSYNC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitSyncOnCloseOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_sync_on_close = TRUE;
	}

	/************************************
	*  turnProhibitSyncOnCloseOff  *
	************************************/

	//	DB_NOSYNC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitSyncOnCloseOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_sync_on_close = FALSE;
	}

/********************
*  ignoreLease  *
********************/

//	DB_IGNORE_LEASE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_ignoreLease( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->ignore_lease == TRUE )	{
		return DB_IGNORE_LEASE;
	}
	return FALSE;
}

	/****************************
	*  turnIgnoreLeaseOn  *
	****************************/

	//	DB_IGNORE_LEASE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnIgnoreLeaseOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->ignore_lease = TRUE;
	}

	/****************************
	*  turnIgnoreLeaseOff  *
	****************************/

	//	DB_IGNORE_LEASE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnIgnoreLeaseOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->ignore_lease = FALSE;
	}
		
/**********************
*  returnMultiple  *
**********************/

//	Bulk operations
//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_returnMultiple( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->return_multiple == TRUE )	{
		return DB_MULTIPLE;
	}
	return FALSE;
}

	/******************************
	*  turnReturnMultipleOn  *
	******************************/

	//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnReturnMultipleOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->return_multiple = TRUE;
	}

	/******************************
	*  turnReturnMultipleOff  *
	******************************/

	//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnReturnMultipleOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->return_multiple = FALSE;
	}

/****************************
*  writeDataOnlyIfNonDuplicate  *
****************************/

//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
//	Btree and Hash only
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_writeDataOnlyIfNonDuplicate( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

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
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->write_data_only_if_non_duplicate = TRUE;
		Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOff( database_record_read_write_settings_controller );
	}

	/************************************
	*  turnWriteDataOnlyIfNonDuplicateOff  *
	************************************/

	//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	//	Btree and Hash only
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->write_data_only_if_non_duplicate = FALSE;
	}

/*************************
*  prohibitOverwrite  *
*************************/

//	DB_NOOVERWRITE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_prohibitOverwrite( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->prohibit_overwrite == TRUE )	{
		return DB_NOOVERWRITE;
	}
	return FALSE;
}

	/********************************
	*  turnProhibitOverwriteOn  *
	********************************/

	//	DB_NOOVERWRITE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_overwrite = TRUE;
		Rbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOff( database_record_read_write_settings_controller );
	}

	/********************************
	*  turnProhibitOverwriteOff  *
	********************************/

	//	DB_NOOVERWRITE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_overwrite = FALSE;
	}

/********************************
*  prohibitPageCompaction  *
********************************/

//	DB_FREELIST_ONLY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	Must be set for Hash
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_prohibitPageCompaction( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

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
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitPageCompactionOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_page_compaction = TRUE;
	}

	/*************************************
	*  turnProhibitPageCompactionOff  *
	*************************************/

	//	DB_FREELIST_ONLY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
	//	Must be set for Hash
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitPageCompactionOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->prohibit_page_compaction = FALSE;
	}

/********************************
*  returnPagesToFilesystem  *
********************************/

//	DB_FREE_SPACE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_returnPagesToFilesystem( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->return_pages_to_filesystem == TRUE )	{
		return DB_FREE_SPACE;
	}
	return FALSE;
}

	/*************************************
	*  turnReturnPagesToFilesystemOn  *
	*************************************/

	//	DB_FREE_SPACE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnReturnPagesToFilesystemOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->return_pages_to_filesystem = TRUE;
	}

	/****************************************
	*  turnReturnPagesToFilesystemOff  *
	****************************************/

	//	DB_FREE_SPACE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnReturnPagesToFilesystemOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->return_pages_to_filesystem = FALSE;
	}

/*****************************
*  truncateFileOnOpen  *
*****************************/

//	DB_TRUNCATE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_truncateFileOnOpen( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	if ( database_record_read_write_settings_controller->truncate )	{
		return DB_TRUNCATE;
	}
	return FALSE;
}

	/************************************
	*  turnTruncateFileOnOpenOn  *
	************************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnTruncateFileOnOpenOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->truncate = TRUE;
	}

	/*********************************
	*  turnTruncateFileOnOpenOff  *
	*********************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnTruncateFileOnOpenOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
		database_record_read_write_settings_controller->truncate = FALSE;
	}

/************************************
*  writeLocksInsteadOfReadLocks  *
************************************/

//	DB_RMW					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_writeLocksInsteadOfReadLocks( Rbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{

	if ( database_read_write_settings_controller->write_locks_instead_of_read_locks == TRUE )	{
		return DB_RMW;
	}
	return FALSE;
}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	****************************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->write_locks_instead_of_read_locks = TRUE;
	}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	****************************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->write_locks_instead_of_read_locks = FALSE;
	}

/*************************
*  duplicates  *
*************************/

//	DB_DUP				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_unsortedDuplicates( Rbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
	
	//	If hash or btree, return ->permit_duplicates
	//	Otherwise, return false
	Rbdb_DatabaseSettingsController*			database_settings_controller			=	database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller;
	Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	Rbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
	DBTYPE	database_type	=	Rbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );
	
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

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		
		//	If hash or btree, set ->permit_duplicates
		//	Otherwise, throw an error

		Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	Rbdb_DatabaseSettingsController_typeSettingsController( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller );
		DBTYPE	database_type	=	Rbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

		if ( ! (	database_type == DB_BTREE
				||	database_type == DB_HASH ) )	{
			
			Rbdb_ErrorController_throwError(	Rbdb_ErrorController_new( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																				Rbdb_ERROR_DUPLICATES_NOT_SUPPORTED,
																				"Rbdb_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOn",
																				"Duplicate records are only supported by Btree and Hash database types." );
		}
		
		database_read_write_settings_controller->permit_duplicates = TRUE;
	}

	/*********************************
	 *  turnPermitDuplicatesOff  *
	 *********************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		
		Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	Rbdb_DatabaseSettingsController_typeSettingsController( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller );
		DBTYPE	database_type	=	Rbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

		//	If hash or btree, set ->permit_duplicates
		//	Otherwise, throw an error
		if ( ! (	database_type == DB_BTREE
				||	database_type == DB_HASH ) )	{
			
			Rbdb_ErrorController_throwError(	Rbdb_ErrorController_new( database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																				 Rbdb_ERROR_DUPLICATES_NOT_SUPPORTED,
																				 "Rbdb_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOff",
																				 "Duplicate records are only supported by Btree and Hash database types." );
		}
		database_read_write_settings_controller->permit_duplicates = FALSE;
	}

/*********************
*  sortDuplicates  *
*********************/

//	DB_DUPSORT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_sortedDuplicates( Rbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{

	Rbdb_DatabaseSettingsController*			parent_database_settings_controller	=	database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller;

	Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller		=	Rbdb_DatabaseSettingsController_typeSettingsController( parent_database_settings_controller );

	DBTYPE	database_type	=	Rbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );
	
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

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{
		
		//	FIX - apply this to all errors		
		Rbdb_Environment*	environment	=	NULL;
		Rbdb_DatabaseSettingsController*			database_settings_controller			=	database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller;

		//	environmental settings controller
		if ( database_settings_controller->parent_settings_controller->parent_environment != NULL )	{
		
			environment	=	database_settings_controller->parent_settings_controller->parent_environment;
		}
		//	instance settings controller
		else {

			Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	Rbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
			DBTYPE	database_type	=	Rbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

			if ( ! (	database_type == DB_BTREE
						||	database_type == DB_HASH ) )	{
				environment	=	database_settings_controller->parent_database->parent_database_controller->parent_environment;				
				Rbdb_ErrorController_throwError(	Rbdb_ErrorController_new(  environment ),
																					Rbdb_ERROR_DUPLICATES_NOT_SUPPORTED,
																					"Rbdb_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOn",
																					"Duplicate records are only supported by Btree and Hash database types." );
			}
		}
		
		//	if we are sorting duplicates we don't want errors for overwriting the same record - just ignore
		Rbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOn( database_read_write_settings_controller );
		
		database_read_write_settings_controller->sort_duplicates = TRUE;
	}

	/******************************
	 *  turnSortDuplicatesOff  *
	 ******************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller )	{

		Rbdb_Environment*	environment	=	NULL;
		Rbdb_DatabaseSettingsController*			database_settings_controller			=	database_read_write_settings_controller->parent_database_record_settings_controller->parent_database_settings_controller;

		//	environmental settings controller
		if ( database_settings_controller->parent_settings_controller->parent_environment != NULL )	{
		
			environment	=	database_settings_controller->parent_settings_controller->parent_environment;
		}
		//	instance settings controller
		else {

			Rbdb_DatabaseTypeSettingsController*	database_type_settings_controller	=	Rbdb_DatabaseSettingsController_typeSettingsController( database_settings_controller );
			DBTYPE	database_type	=	Rbdb_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

			if ( ! (	database_type == DB_BTREE
					||	database_type == DB_HASH ) )	{

				environment	=	database_settings_controller->parent_database->parent_database_controller->parent_environment;
				Rbdb_ErrorController_throwError(	Rbdb_ErrorController_new(		environment ),
																																			Rbdb_ERROR_DUPLICATES_NOT_SUPPORTED,
																																			"Rbdb_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOff",
																																			"Duplicate records are only supported by Btree and Hash database types." );
			}
		}

		//	this flag only makes sense with sorted duplicates, so if they're not on it goes off
		Rbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOff( database_read_write_settings_controller );
		
		database_read_write_settings_controller->sort_duplicates = FALSE;
	}

/*****************************************
*  databaseAllocatesMemoryUsingMalloc  *
*****************************************/

BOOL Rbdb_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->database_allocates_memory_using_malloc == TRUE )	{
		return DB_DBT_MALLOC;
	}
	return FALSE;
}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOn  *
	*************************************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_allocates_memory_using_malloc = TRUE;
		Rbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOff  *
	*************************************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_allocates_memory_using_malloc = FALSE;
		Rbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*********************************************
*  databaseAllocatesMemoryUsingRealloc  *
*********************************************/

BOOL Rbdb_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->database_allocates_memory_using_realloc == TRUE )	{
		return DB_DBT_REALLOC;
	}
	return FALSE;
}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOn  *
	*************************************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_allocates_memory_using_realloc = TRUE;
		Rbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOff  *
	*************************************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_allocates_memory_using_realloc = FALSE;
		Rbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*********************************
*  applicationAllocatesMemory  *
*********************************/

BOOL Rbdb_DatabaseRecordReadWriteSettingsController_applicationAllocatesMemory( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->application_allocates_memory == TRUE )	{
		return DB_DBT_USERMEM;
	}
	return FALSE;
}

	/*****************************************
	*  turnApplicationAllocatesMemoryOn  *
	*****************************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnApplicationAllocatesMemoryOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->application_allocates_memory = TRUE;
		Rbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*****************************************
	*  turnApplicationAllocatesMemoryOff  *
	*****************************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnApplicationAllocatesMemoryOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->application_allocates_memory = FALSE;
		Rbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*****************************
*  databaseFreesMemory  *
*****************************/

BOOL Rbdb_DatabaseRecordReadWriteSettingsController_databaseFreesMemory( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->database_free_memory == TRUE )	{
		return DB_DBT_APPMALLOC;
	}
	return FALSE;
}

	/*********************************
	*  turnDatabaseFreesMemoryOn  *
	*********************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseFreesMemoryOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_free_memory = TRUE;
		Rbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*********************************
	*  turnDatabaseFreesMemoryOff  *
	*********************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseFreesMemoryOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->database_free_memory = FALSE;
		Rbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

/*********************
*  partialAccess  *
*********************/

BOOL Rbdb_DatabaseRecordReadWriteSettingsController_partialAccess( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
	if ( database_record_read_write_settings_controller->partial_access == TRUE )	{
		return DB_DBT_PARTIAL;
	}
	return FALSE;
}

	/*****************************
	*  turnPartialAccessOn  *
	*****************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnPartialAccessOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->partial_access = TRUE;
		Rbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}

	/*****************************
	*  turnPartialAccessOff  *
	*****************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnPartialAccessOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{
	
		database_record_read_write_settings_controller->partial_access = FALSE;
		Rbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( database_record_read_write_settings_controller );
	}
	
/*****************************
*  syncPriorToWriteReturn  *
*****************************/

//	DB_DSYNC_DB             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_syncPriorToWriteReturn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	if ( database_record_read_write_settings_controller->sync_prior_to_write_return == TRUE )	{
		return DB_DSYNC_DB;
	}
	return FALSE;
}

	/**************************************
	*  turnSyncPriorToWriteReturnOn  *
	**************************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnSyncPriorToWriteReturnOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

		database_record_read_write_settings_controller->sync_prior_to_write_return = TRUE;
	}

	/************************************
	*  turnSyncPriorToWriteReturnOff  *
	************************************/

	void Rbdb_DatabaseRecordReadWriteSettingsController_turnSyncPriorToWriteReturnOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

		database_record_read_write_settings_controller->sync_prior_to_write_return = FALSE;
	}

/*********************
*  dataBufferSize  *
*********************/

uint32_t Rbdb_DatabaseRecordReadWriteSettingsController_dataBufferSize( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

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

void Rbdb_DatabaseRecordReadWriteSettingsController_setDataBufferSize(	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
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
uint32_t Rbdb_DatabaseRecordReadWriteSettingsController_partialReadWriteSize( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

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

void Rbdb_DatabaseRecordReadWriteSettingsController_setPartialReadWriteSize(	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
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

uint32_t Rbdb_DatabaseRecordReadWriteSettingsController_partialReadWriteOffset( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

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

void Rbdb_DatabaseRecordReadWriteSettingsController_setPartialReadWriteOffset(	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
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

/*************************************
*  setWriteFailedCallbackMethod  *
*************************************/
/*
void Rbdb_MessageSettingsController_setWriteFailedCallbackMethod(	Rbdb_MessageSettingsController*				message_settings_controller,
 																	void *(write_failed_callback_method)( Rbdb_Environment*	environment ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;
	
	message_settings_controller->write_failed_callback_method = write_failed_callback_method;
	//	Make sure we have our internal callback enabled
	
	 if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_event_notify(	environment->wrapped_bdb_environment, 
																& Rbdb_MessageSettingsController_internal_eventCallbackMethod );
	}
}
*/
/*********************************
*  writeFailedCallbackMethod  *
*********************************/
/*
void *(write_failed_callback_method)( Rbdb_Environment*	environment ) Rbdb_MessageSettingsController_writeFailedCallbackMethod(	Rbdb_MessageSettingsController*		message_settings_controller )	{
	
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
void Rbdb_DatabaseRecordReadWriteSettingsController_internal_updateFlags( Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller )	{
	
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
	*flags_pointer =	Rbdb_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( database_record_read_write_settings_controller )
										|	Rbdb_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( database_record_read_write_settings_controller )
										|	Rbdb_DatabaseRecordReadWriteSettingsController_applicationAllocatesMemory( database_record_read_write_settings_controller )
										|	Rbdb_DatabaseRecordReadWriteSettingsController_partialAccess( database_record_read_write_settings_controller )
										|	Rbdb_DatabaseRecordReadWriteSettingsController_databaseFreesMemory( database_record_read_write_settings_controller );
}	

/******************************************
*  copyOfDefaultSettingsForInstance  *
******************************************/

//	Returns a copy of cursor_settings_controller to be used for instance
Rbdb_DatabaseRecordReadWriteSettingsController* Rbdb_DatabaseRecordReadWriteSettingsController_internal_copyOfDefaultSettingsForInstance( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	//	create a new database_cursor settings controller without a parent
	Rbdb_DatabaseRecordReadWriteSettingsController*	database_record_read_write_settings_controller_copy = Rbdb_DatabaseRecordReadWriteSettingsController_new( NULL );

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
int Rbdb_DatabaseRecordReadWriteSettingsController_internal_writeFlags( Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller)	{
	//	Setter functions ensure exclusivity, so we should be able to simply | together the results
	return	Rbdb_DatabaseRecordReadWriteSettingsController_writeDataOnlyIfNonDuplicate( database_record_read_write_settings_controller )
			|	Rbdb_DatabaseRecordReadWriteSettingsController_prohibitOverwrite( database_record_read_write_settings_controller );
}

/*********************
*  deleteFlags  *
*********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_del.html
int Rbdb_DatabaseRecordReadWriteSettingsController_internal_deleteFlags( Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller __attribute__((unused)) )	{

	return Rbdb_NO_FLAGS;
}

/*********************
*  existsFlags  *
*********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_del.html
int Rbdb_DatabaseRecordReadWriteSettingsController_internal_existsFlags( Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller )	{

	return Rbdb_DatabaseRecordReadWriteSettingsController_writeLocksInsteadOfReadLocks(	database_record_read_write_settings_controller );
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_DatabaseRecordReadWriteSettingsController* Rbdb_DatabaseRecordReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller )	{

	Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller_copy	=	Rbdb_DatabaseRecordReadWriteSettingsController_new( database_record_read_write_settings_controller->parent_database_record_settings_controller );

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
	database_record_read_write_settings_controller_copy->write_data_only_if_non_duplicate			=	database_record_read_write_settings_controller->write_data_only_if_non_duplicate;
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

