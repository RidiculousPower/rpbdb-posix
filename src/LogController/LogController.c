/*
 *		RPbdb::LogController
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

#include "LogController.h"

#include "Log.h"
#include "LogSequenceNumber.h"
#include "LogCursorController.h"

#include "DatabaseCursorController.h"

#include "Environment.h"

#include "TransactionController.h"
#include "TransactionController_internal.h"

#include "SettingsController.h"
#include "LogSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_LogController* RPbdb_LogController_new( RPbdb_Environment* parent_environment )	{
	
	RPbdb_LogController*		log_controller = calloc( 1, sizeof( RPbdb_LogController ) );

	log_controller->parent_environment = parent_environment;
	
	return log_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_LogController_free(	RPbdb_LogController** log_controller )	{

	if ( ( *log_controller )->cursor_controller != NULL )	{
		RPbdb_LogCursorController_free( & ( ( *log_controller )->cursor_controller ) );
	}

	free( *log_controller );
	*log_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_LogSettingsController* RPbdb_LogController_settingsController(	RPbdb_LogController* log_controller )	{
	return log_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_LogController_parentEnvironment(	RPbdb_LogController* log_controller )	{
	return log_controller->parent_environment;
}

/*********************
*  appendString  *
*********************/

//	The DB_ENV->log_printf method appends an informational message to the Berkeley DB database environment log files.
//	The DB_ENV->log_printf method allows applications to include information in the database environment log files, 
//	for later review using the db_printlog utility. This method is intended for debugging and performance tuning.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_printf.html
void RPbdb_LogController_appendStringToCurrentLog(	RPbdb_LogController*		log_controller,
																									char*					log_string,
																									... )	{
	
	RPbdb_Environment*		environment	=	log_controller->parent_environment;
	//	FIX - var args needs to be implemented

	DB_TXN*	transaction_id	=	NULL;
	if ( environment->transaction_controller != NULL )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
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
void RPbdb_LogController_flushLogsToDisk(	RPbdb_LogController*		log_controller,
 											RPbdb_LogSequenceNumber*	log_sequence_number )	{
	
	DB_ENV*		environment	=	log_controller->parent_environment->wrapped_bdb_environment;

	environment->log_flush(	environment,
							log_sequence_number->wrapped_bdb_log_sequence_number );
}

/*********************
*  appendRecord  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_put.html
void RPbdb_LogController_appendLogRecord(	RPbdb_LogController*		log_controller,
 											RPbdb_Record*				log_record )	{
	
	RPbdb_Environment*		environment	=	log_controller->parent_environment;
	
	RPbdb_Log*	log	=	RPbdb_Log_new( log_controller );
	
	environment->wrapped_bdb_environment->log_put(	environment->wrapped_bdb_environment,
													log->log_sequence_number->wrapped_bdb_log_sequence_number,
													log_record->data->wrapped_bdb_dbt->data,
													RPbdb_LogSettingsController_internal_appendRecordFlags( RPbdb_SettingsController_logSettingsController( RPbdb_Environment_settingsController( environment )) ) );
}

/*************************
*  cursorController  *
*************************/

RPbdb_LogCursorController* RPbdb_LogController_cursorController( RPbdb_LogController* log_controller )	{

	if ( log_controller->cursor_controller == NULL )	{
		log_controller->cursor_controller = RPbdb_LogCursorController_new( log_controller );
	}
	
	return log_controller->cursor_controller;
}






