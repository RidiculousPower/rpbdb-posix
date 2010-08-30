/*
 *		RPDB::LogController
 *
 *		BDB logging implementation for applications described here: 
 *      http://www.oracle.com/technology/documentation/berkeley-db/db/ref/apprec/def.html
 *
 *		Description of process for full backup with BDB:
 *      http://www.oracle.com/technology/documentation/berkeley-db/db/ref/transapp/archival.html
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_LogController.h"

#include "RPDB_Log.h"
#include "RPDB_LogSequenceNumber.h"
#include "RPDB_LogCursorController.h"

#include "RPDB_DatabaseCursorController.h"

#include "RPDB_Environment.h"

#include "RPDB_TransactionController.h"
#include "RPDB_TransactionController_internal.h"

#include "RPDB_SettingsController.h"
#include "RPDB_LogSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_LogController* RPDB_LogController_new( RPDB_Environment* parent_environment )	{
	
	RPDB_LogController*		log_controller = calloc( 1, sizeof( RPDB_LogController ) );

	log_controller->parent_environment = parent_environment;
	
	return log_controller;
}

/***************************
*  free  *
***************************/
void RPDB_LogController_free(	RPDB_LogController** log_controller )	{

	if ( ( *log_controller )->cursor_controller != NULL )	{
		RPDB_LogCursorController_free( & ( ( *log_controller )->cursor_controller ) );
	}

	free( *log_controller );
	*log_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_LogSettingsController* RPDB_LogController_settingsController(	RPDB_LogController* log_controller )	{
	return log_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_LogController_parentEnvironment(	RPDB_LogController* log_controller )	{
	return log_controller->parent_environment;
}

/*********************
*  appendString  *
*********************/

//	The DB_ENV->log_printf method appends an informational message to the Berkeley DB database environment log files.
//	The DB_ENV->log_printf method allows applications to include information in the database environment log files, 
//	for later review using the db_printlog utility. This method is intended for debugging and performance tuning.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_printf.html
void RPDB_LogController_appendStringToCurrentLog(	RPDB_LogController*		log_controller,
																									char*					log_string,
																									... )	{
	
	RPDB_Environment*		environment	=	log_controller->parent_environment;
	//	FIX - var args needs to be implemented

	DB_TXN*	transaction_id	=	NULL;
	if ( environment->transaction_controller != NULL )	{
		transaction_id	=	RPDB_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
		 
	environment->wrapped_bdb_environment->log_printf(	environment->wrapped_bdb_environment,
														transaction_id,
														log_string
														//	This doesn't work yet - needs to pass format
														);

}

/*************************
*  flushLogsToDisk  *
*************************/

//	All log records with DB_LSN values less than or equal to the lsn parameter are written to disk. If lsn is NULL, all records in the log are flushed.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_flush.html	
void RPDB_LogController_flushLogsToDisk(	RPDB_LogController*		log_controller,
 											RPDB_LogSequenceNumber*	log_sequence_number )	{
	
	DB_ENV*		environment	=	log_controller->parent_environment->wrapped_bdb_environment;

	environment->log_flush(	environment,
							log_sequence_number->wrapped_bdb_log_sequence_number );
}

/*********************
*  appendRecord  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_put.html
void RPDB_LogController_appendLogRecord(	RPDB_LogController*		log_controller,
 											RPDB_Record*				log_record )	{
	
	RPDB_Environment*		environment	=	log_controller->parent_environment;
	
	RPDB_Log*	log	=	RPDB_Log_new( log_controller );
	
	environment->wrapped_bdb_environment->log_put(	environment->wrapped_bdb_environment,
													log->log_sequence_number->wrapped_bdb_log_sequence_number,
													log_record->data->wrapped_bdb_dbt->data,
													RPDB_LogSettingsController_internal_appendRecordFlags( RPDB_SettingsController_logSettingsController( RPDB_Environment_settingsController( environment )) ) );
}

/*************************
*  cursorController  *
*************************/

RPDB_LogCursorController* RPDB_LogController_cursorController( RPDB_LogController* log_controller )	{

	if ( log_controller->cursor_controller == NULL )	{
		log_controller->cursor_controller = RPDB_LogCursorController_new( log_controller );
	}
	
	return log_controller->cursor_controller;
}






