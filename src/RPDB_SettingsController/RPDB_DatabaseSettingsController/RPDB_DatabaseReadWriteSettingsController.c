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

#include "RPDB_DatabaseReadWriteSettingsController.h"

#include "RPDB_Environment.h"
#include "RPDB_Database.h"

#include "RPDB_SettingsController.h"
#include "RPDB_DatabaseSettingsController.h"

#include "RPDB_DatabaseReadWriteSettingsController.h"
#include "RPDB_DatabaseTypeSettingsController.h"
#include "RPDB_DatabaseTypeBtreeSettingsController.h"
#include "RPDB_DatabaseTypeHashSettingsController.h"

#include "RPDB_DatabaseTypeBtreeSettingsController_internal.h"
#include "RPDB_DatabaseTypeHashSettingsController_internal.h"
#include "RPDB_DatabaseReadWriteSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseReadWriteSettingsController* RPDB_DatabaseReadWriteSettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseReadWriteSettingsController*		database_read_write_settings_controller = calloc( 1, sizeof( RPDB_DatabaseReadWriteSettingsController ) );

	database_read_write_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_read_write_settings_controller;
}


/***************************
*  free  *
***************************/
void RPDB_DatabaseReadWriteSettingsController_free(	RPDB_DatabaseReadWriteSettingsController** database_read_write_settings_controller )	{

	free( *database_read_write_settings_controller );
	*database_read_write_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseReadWriteSettingsController_parentEnvironment(	RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
	return database_read_write_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseReadWriteSettingsController_parentDatabase(	RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
	return database_read_write_settings_controller->parent_database_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		File Settings
*******************************************************************************************************************************************************************************************/

/*****************
*  filename  *
*****************/

//	In-memory databases never intended to be preserved on disk may be created by setting the file parameter to NULL.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
char* RPDB_DatabaseReadWriteSettingsController_filename( RPDB_DatabaseReadWriteSettingsController*		database_read_write_settings_controller )	{
	
	return database_read_write_settings_controller->filename;
}

/*********************
*  setFilename  *
*********************/

void RPDB_DatabaseReadWriteSettingsController_setFilename(	RPDB_DatabaseReadWriteSettingsController*		database_read_write_settings_controller,
															char*											filename	)	{
	
	database_read_write_settings_controller->filename = filename;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/****************************
*  prohibitSyncOnClose  *
****************************/

//	DB_NOSYNC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
BOOL RPDB_DatabaseReadWriteSettingsController_prohibitSyncOnClose( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{

	if ( database_read_write_settings_controller->prohibit_sync_on_close == TRUE )	{
		return DB_NOSYNC;
	}
	return FALSE;
}

	/*********************************
	*  turnProhibitSyncOnCloseOn  *
	*********************************/

	//	DB_NOSYNC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
	void RPDB_DatabaseReadWriteSettingsController_turnProhibitSyncOnCloseOn( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->prohibit_sync_on_close = TRUE;
	}

	/************************************
	*  turnProhibitSyncOnCloseOff  *
	************************************/

	//	DB_NOSYNC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_close.html
	void RPDB_DatabaseReadWriteSettingsController_turnProhibitSyncOnCloseOff( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->prohibit_sync_on_close = FALSE;
	}

/********************
*  ignoreLease  *
********************/

//	DB_IGNORE_LEASE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
BOOL RPDB_DatabaseReadWriteSettingsController_ignoreLease( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{

	if ( database_read_write_settings_controller->ignore_lease == TRUE )	{
		return DB_IGNORE_LEASE;
	}
	return FALSE;
}

	/****************************
	*  turnIgnoreLeaseOn  *
	****************************/

	//	DB_IGNORE_LEASE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void RPDB_DatabaseReadWriteSettingsController_turnIgnoreLeaseOn( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->ignore_lease = TRUE;
	}

	/****************************
	*  turnIgnoreLeaseOff  *
	****************************/

	//	DB_IGNORE_LEASE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void RPDB_DatabaseReadWriteSettingsController_turnIgnoreLeaseOff( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->ignore_lease = FALSE;
	}
		
/**********************
*  returnMultiple  *
**********************/

//	Bulk operations
//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
BOOL RPDB_DatabaseReadWriteSettingsController_returnMultiple( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{

	if ( database_read_write_settings_controller->return_multiple == TRUE )	{
		return DB_MULTIPLE;
	}
	return FALSE;
}

	/******************************
	*  turnReturnMultipleOn  *
	******************************/

	//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void RPDB_DatabaseReadWriteSettingsController_turnReturnMultipleOn( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->return_multiple = TRUE;
	}

	/******************************
	*  turnReturnMultipleOff  *
	******************************/

	//	DB_MULTIPLE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get.html
	void RPDB_DatabaseReadWriteSettingsController_turnReturnMultipleOff( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->return_multiple = FALSE;
	}

/****************************
*  prohibitDuplicateData  *
****************************/

//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
//	Btree and Hash only
BOOL RPDB_DatabaseReadWriteSettingsController_prohibitDuplicateData( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{

	if ( database_read_write_settings_controller->prohibit_duplicate_data == TRUE )	{
		return DB_NODUPDATA;
	}
	return FALSE;
}

	/*************************************
	*  turnProhibitDuplicateDataOn  *
	*************************************/

	//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	//	Btree and Hash only
	void RPDB_DatabaseReadWriteSettingsController_turnProhibitDuplicateDataOn( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->prohibit_duplicate_data = TRUE;
		RPDB_DatabaseReadWriteSettingsController_turnProhibitOverwriteOff( database_read_write_settings_controller );
	}

	/************************************
	*  turnProhibitDuplicateDataOff  *
	************************************/

	//	DB_NODUPDATA			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	//	Btree and Hash only
	void RPDB_DatabaseReadWriteSettingsController_turnProhibitDuplicateDataOff( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->prohibit_duplicate_data = FALSE;
	}

/*************************
*  prohibitOverwrite  *
*************************/

//	DB_NOOVERWRITE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
BOOL RPDB_DatabaseReadWriteSettingsController_prohibitOverwrite( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{

	if ( database_read_write_settings_controller->prohibit_overwrite == TRUE )	{
		return DB_NOOVERWRITE;
	}
	return FALSE;
}

	/********************************
	*  turnProhibitOverwriteOn  *
	********************************/

	//	DB_NOOVERWRITE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void RPDB_DatabaseReadWriteSettingsController_turnProhibitOverwriteOn( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->prohibit_overwrite = TRUE;
		RPDB_DatabaseReadWriteSettingsController_turnProhibitDuplicateDataOff( database_read_write_settings_controller );
	}

	/********************************
	*  turnProhibitOverwriteOff  *
	********************************/

	//	DB_NOOVERWRITE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void RPDB_DatabaseReadWriteSettingsController_turnProhibitOverwriteOff( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->prohibit_overwrite = FALSE;
	}

/********************************
*  prohibitPageCompaction  *
********************************/

//	DB_FREELIST_ONLY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
//	Must be set for Hash
BOOL RPDB_DatabaseReadWriteSettingsController_prohibitPageCompaction( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{

	if ( database_read_write_settings_controller->prohibit_page_compaction == TRUE )	{
		return DB_FREELIST_ONLY;
	}
	return FALSE;
}

	/*************************************
	*  turnProhibitPageCompactionOn  *
	*************************************/

	//	DB_FREELIST_ONLY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
	//	Must be set for Hash
	void RPDB_DatabaseReadWriteSettingsController_turnProhibitPageCompactionOn( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->prohibit_page_compaction = TRUE;
	}

	/*************************************
	*  turnProhibitPageCompactionOff  *
	*************************************/

	//	DB_FREELIST_ONLY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_compact.html
	//	Must be set for Hash
	void RPDB_DatabaseReadWriteSettingsController_turnProhibitPageCompactionOff( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->prohibit_page_compaction = FALSE;
	}

/********************************
*  returnPagesToFilesystem  *
********************************/

//	DB_FREE_SPACE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
BOOL RPDB_DatabaseReadWriteSettingsController_returnPagesToFilesystem( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{

	if ( database_read_write_settings_controller->return_pages_to_filesystem == TRUE )	{
		return DB_FREE_SPACE;
	}
	return FALSE;
}

	/*************************************
	*  turnReturnPagesToFilesystemOn  *
	*************************************/

	//	DB_FREE_SPACE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void RPDB_DatabaseReadWriteSettingsController_turnReturnPagesToFilesystemOn( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->return_pages_to_filesystem = TRUE;
	}

	/****************************************
	*  turnReturnPagesToFilesystemOff  *
	****************************************/

	//	DB_FREE_SPACE			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
	void RPDB_DatabaseReadWriteSettingsController_turnReturnPagesToFilesystemOff( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->return_pages_to_filesystem = FALSE;
	}

/*********************
*  partialAccess  *
*********************/

//	DB_DBT_PARTIAL		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
BOOL RPDB_DatabaseReadWriteSettingsController_partialAccess( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{

	if ( database_read_write_settings_controller->partial_access == TRUE )	{
		return DB_DBT_PARTIAL;
	}
	return FALSE;
}

	/*****************************
	*  turnPartialAccessOn  *
	*****************************/

	//	DB_DBT_PARTIAL		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_DatabaseReadWriteSettingsController_turnPartialAccessOn( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->partial_access = TRUE;
	}

	/*****************************
	*  turnPartialAccessOff  *
	*****************************/

	//	DB_DBT_PARTIAL		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbt_class.html
	void RPDB_DatabaseReadWriteSettingsController_turnPartialAccessOff( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->partial_access = FALSE;
	}

/*****************************
*  truncateFileOnOpen  *
*****************************/

//	DB_TRUNCATE		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
BOOL RPDB_DatabaseReadWriteSettingsController_truncateFileOnOpen( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
	if ( database_read_write_settings_controller->truncate )	{
		return DB_TRUNCATE;
	}
	return FALSE;
}

	/************************************
	*  turnTruncateFileOnOpenOn  *
	************************************/

	void RPDB_DatabaseReadWriteSettingsController_turnTruncateFileOnOpenOn( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->truncate = TRUE;
	}

	/*********************************
	*  turnTruncateFileOnOpenOff  *
	*********************************/

	void RPDB_DatabaseReadWriteSettingsController_turnTruncateFileOnOpenOff( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{
		database_read_write_settings_controller->truncate = FALSE;
	}

/************************************
*  writeLocksInsteadOfReadLocks  *
************************************/

//	DB_RMW					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/dbc_get.html
BOOL RPDB_DatabaseReadWriteSettingsController_writeLocksInsteadOfReadLocks( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller )	{

	if ( database_write_retrieve_settings_controller->write_locks_instead_of_read_locks == TRUE )	{
		return DB_RMW;
	}
	return FALSE;
}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	****************************************/

	void RPDB_DatabaseReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller )	{
		database_write_retrieve_settings_controller->write_locks_instead_of_read_locks = TRUE;
	}

	/****************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	****************************************/

	void RPDB_DatabaseReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller )	{
		database_write_retrieve_settings_controller->write_locks_instead_of_read_locks = FALSE;
	}

/*******************************************************************************************************************************************************************************************
												Switch Settings
*******************************************************************************************************************************************************************************************/

/*************************
*  duplicates  *
*************************/

//	DB_DUP				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPDB_DatabaseReadWriteSettingsController_unsortedDuplicates( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller )	{
	
	//	If hash or btree, return ->permit_duplicates
	//	Otherwise, return false
	
	DBTYPE	database_type	=	RPDB_DatabaseTypeSettingsController_databaseType( RPDB_DatabaseSettingsController_typeSettingsController( database_write_retrieve_settings_controller->parent_database_settings_controller ) );
	
	if (	(	database_type == DB_BTREE
			||	database_type == DB_HASH )
		&&	database_write_retrieve_settings_controller->permit_duplicates )	{
		
		return DB_DUP;
	}
	
	return FALSE;
}

	/*******************************
	 *  turnPermitDuplicatesOn  *
	 *******************************/

	void RPDB_DatabaseReadWriteSettingsController_turnUnsortedDuplicatesOn( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller )	{
		
		//	If hash or btree, set ->permit_duplicates
		//	Otherwise, throw an error

		RPDB_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPDB_DatabaseSettingsController_typeSettingsController( database_write_retrieve_settings_controller->parent_database_settings_controller );
		DBTYPE	database_type	=	RPDB_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

		if ( ! (	database_type == DB_BTREE
				||	database_type == DB_HASH ) )	{
			
			RPDB_ErrorController_throwError(	RPDB_ErrorController_new( database_write_retrieve_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
												RPDB_ERROR_DUPLICATES_NOT_SUPPORTED,
												"RPDB_DatabaseReadWriteSettingsController_turnUnsortedDuplicatesOn",
												"Duplicate records are only supported by Btree and Hash database types." );
		}
		
		database_write_retrieve_settings_controller->permit_duplicates = TRUE;
	}

	/*********************************
	 *  turnPermitDuplicatesOff  *
	 *********************************/

	void RPDB_DatabaseReadWriteSettingsController_turnUnsortedDuplicatesOff( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller )	{
		
		RPDB_DatabaseTypeSettingsController*	database_type_settings_controller	=	RPDB_DatabaseSettingsController_typeSettingsController( database_write_retrieve_settings_controller->parent_database_settings_controller );
		DBTYPE	database_type	=	RPDB_DatabaseTypeSettingsController_databaseType( database_type_settings_controller );

		//	If hash or btree, set ->permit_duplicates
		//	Otherwise, throw an error
		if ( ! (	database_type == DB_BTREE
				||	database_type == DB_HASH ) )	{
			
			RPDB_ErrorController_throwError(	RPDB_ErrorController_new( database_write_retrieve_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
											 RPDB_ERROR_DUPLICATES_NOT_SUPPORTED,
											 "RPDB_DatabaseReadWriteSettingsController_turnUnsortedDuplicatesOff",
											 "Duplicate records are only supported by Btree and Hash database types." );
		}
	}

/*********************
*  sortDuplicates  *
*********************/

//	DB_DUPSORT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPDB_DatabaseReadWriteSettingsController_sortedDuplicates( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller )	{

	DBTYPE	database_type	=	RPDB_DatabaseTypeSettingsController_databaseType( RPDB_DatabaseSettingsController_typeSettingsController( database_write_retrieve_settings_controller->parent_database_settings_controller ) );
	
	if (	(	database_type == DB_BTREE
			 ||	database_type == DB_HASH )
		&&	database_write_retrieve_settings_controller->sort_duplicates )	{
		
		return DB_DUPSORT;
	}
	
	return FALSE;
}

	/*****************************
	 *  turnSortDuplicatesOn  *
	 *****************************/

	void RPDB_DatabaseReadWriteSettingsController_turnSortedDuplicatesOn( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller )	{
		
		DBTYPE	database_type	=	RPDB_DatabaseTypeSettingsController_databaseType( RPDB_DatabaseSettingsController_typeSettingsController( database_write_retrieve_settings_controller->parent_database_settings_controller ) );

		if ( ! (	database_type == DB_BTREE
				||	database_type == DB_HASH ) )	{
			
			RPDB_ErrorController_throwError(	RPDB_ErrorController_new( database_write_retrieve_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
											 RPDB_ERROR_DUPLICATES_NOT_SUPPORTED,
											 "RPDB_DatabaseReadWriteSettingsController_turnSortedDuplicatesOn",
											 "Duplicate records are only supported by Btree and Hash database types." );
		}
		
		database_write_retrieve_settings_controller->sort_duplicates = TRUE;
	}

	/******************************
	 *  turnSortDuplicatesOff  *
	 ******************************/

	void RPDB_DatabaseReadWriteSettingsController_turnSortedDuplicatesOff( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller )	{

		DBTYPE	database_type	=	RPDB_DatabaseTypeSettingsController_databaseType( RPDB_DatabaseSettingsController_typeSettingsController( database_write_retrieve_settings_controller->parent_database_settings_controller ) );

		if ( ! (	database_type == DB_BTREE
				||	database_type == DB_HASH ) )	{
			
			RPDB_ErrorController_throwError(	RPDB_ErrorController_new( database_write_retrieve_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
											 RPDB_ERROR_DUPLICATES_NOT_SUPPORTED,
											 "RPDB_DatabaseReadWriteSettingsController_turnSortedDuplicatesOff",
											 "Duplicate records are only supported by Btree and Hash database types." );
		}
		
		database_write_retrieve_settings_controller->sort_duplicates = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/******************************************
*  copyOfDefaultSettingsForInstance  *
******************************************/

//	Returns a copy of cursor_settings_controller to be used for instance
RPDB_DatabaseReadWriteSettingsController* RPDB_DatabaseReadWriteSettingsController_internal_copyOfDefaultSettingsForInstance( RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{

	//	create a new database_cursor settings controller without a parent
	RPDB_DatabaseReadWriteSettingsController*	database_read_write_settings_controller_copy = RPDB_DatabaseReadWriteSettingsController_new( NULL );

	//	copy settings from passed controller into new controller
	database_read_write_settings_controller_copy->prohibit_sync_on_close		= database_read_write_settings_controller->prohibit_sync_on_close;
	database_read_write_settings_controller_copy->ignore_lease					= database_read_write_settings_controller->ignore_lease;	

	database_read_write_settings_controller_copy->return_multiple				= database_read_write_settings_controller->return_multiple;	
	database_read_write_settings_controller_copy->append_data					= database_read_write_settings_controller->append_data;	
	database_read_write_settings_controller_copy->prohibit_duplicate_data		= database_read_write_settings_controller->prohibit_duplicate_data;	
	
	database_read_write_settings_controller_copy->prohibit_overwrite			= database_read_write_settings_controller->prohibit_overwrite;	
	database_read_write_settings_controller_copy->prohibit_page_compaction		= database_read_write_settings_controller->prohibit_page_compaction;	
	database_read_write_settings_controller_copy->return_pages_to_filesystem	= database_read_write_settings_controller->return_pages_to_filesystem;	
	database_read_write_settings_controller_copy->multiple_targets				= database_read_write_settings_controller->multiple_targets;	
	database_read_write_settings_controller_copy->partial_access				= database_read_write_settings_controller->partial_access;		

	//	return new controller
	return database_read_write_settings_controller_copy;
}
	
/**********************
*  writeFlags  *
**********************/
	
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_put.html
int RPDB_DatabaseReadWriteSettingsController_internal_writeFlags( RPDB_DatabaseReadWriteSettingsController*		database_read_write_settings_controller)	{
	//	Setter functions ensure exclusivity, so we should be able to simply | together the results
	return	RPDB_DatabaseReadWriteSettingsController_prohibitDuplicateData( database_read_write_settings_controller )
			|	RPDB_DatabaseReadWriteSettingsController_prohibitOverwrite( database_read_write_settings_controller );
}

/*********************
*  deleteFlags  *
*********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_del.html
int RPDB_DatabaseReadWriteSettingsController_internal_deleteFlags( RPDB_DatabaseReadWriteSettingsController*		database_read_write_settings_controller __attribute__((unused)) )	{

	return RPDB_NO_FLAGS;
}

/*********************
*  existsFlags  *
*********************/

//	Flags is currently unused (0) - this could change. Who knows what the future may hold! :o
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_del.html
int RPDB_DatabaseReadWriteSettingsController_internal_existsFlags( RPDB_DatabaseReadWriteSettingsController*		database_read_write_settings_controller )	{

	return RPDB_DatabaseReadWriteSettingsController_writeLocksInsteadOfReadLocks(	RPDB_DatabaseSettingsController_readWriteSettingsController( RPDB_Database_settingsController( database_read_write_settings_controller->parent_database_settings_controller->parent_database ) ) );
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseReadWriteSettingsController* RPDB_DatabaseReadWriteSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller )	{

	RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller_copy	=	RPDB_DatabaseReadWriteSettingsController_new( database_read_write_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_read_write_settings_controller_copy->write_locks_instead_of_read_locks	=	database_read_write_settings_controller->write_locks_instead_of_read_locks;
	database_read_write_settings_controller_copy->prohibit_overwrite				=	database_read_write_settings_controller->prohibit_overwrite;
	database_read_write_settings_controller_copy->return_multiple					=	database_read_write_settings_controller->return_multiple;
	database_read_write_settings_controller_copy->prohibit_page_compaction			=	database_read_write_settings_controller->prohibit_page_compaction;
	database_read_write_settings_controller_copy->return_pages_to_filesystem		=	database_read_write_settings_controller->return_pages_to_filesystem;
	database_read_write_settings_controller_copy->partial_access					=	database_read_write_settings_controller->partial_access;
	database_read_write_settings_controller_copy->append_data						=	database_read_write_settings_controller->append_data;
	database_read_write_settings_controller_copy->ignore_lease						=	database_read_write_settings_controller->ignore_lease;
	database_read_write_settings_controller_copy->filename							=	database_read_write_settings_controller->filename;
	database_read_write_settings_controller_copy->truncate							=	database_read_write_settings_controller->truncate;
	database_read_write_settings_controller_copy->multiple_targets					=	database_read_write_settings_controller->multiple_targets;
	database_read_write_settings_controller_copy->prohibit_duplicate_data			=	database_read_write_settings_controller->prohibit_duplicate_data;
	database_read_write_settings_controller_copy->prohibit_sync_on_close			=	database_read_write_settings_controller->prohibit_sync_on_close;
	database_read_write_settings_controller_copy->permit_duplicates					=	database_read_write_settings_controller->permit_duplicates;
	database_read_write_settings_controller_copy->sort_duplicates					=	database_read_write_settings_controller->sort_duplicates;

	return database_read_write_settings_controller_copy;
}

