/*
 *		Rbdb::LogController
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

#include "Rbdb_LogController.h"

#include "Rbdb_Log.h"
#include "Rbdb_LogSequenceNumber.h"
#include "Rbdb_LogCursorController.h"

#include "Rbdb_DatabaseCursorController.h"

#include "Rbdb_Environment.h"

#include "Rbdb_TransactionController.h"
#include "Rbdb_TransactionController_internal.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_LogSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_LogController* Rbdb_LogController_new( Rbdb_Environment* parent_environment )	{
	
	Rbdb_LogController*		log_controller = calloc( 1, sizeof( Rbdb_LogController ) );

	log_controller->parent_environment = parent_environment;
	
	return log_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_LogController_free(	Rbdb_LogController** log_controller )	{

	if ( ( *log_controller )->cursor_controller != NULL )	{
		Rbdb_LogCursorController_free( & ( ( *log_controller )->cursor_controller ) );
	}

	free( *log_controller );
	*log_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_LogSettingsController* Rbdb_LogController_settingsController(	Rbdb_LogController* log_controller )	{
	return log_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_LogController_parentEnvironment(	Rbdb_LogController* log_controller )	{
	return log_controller->parent_environment;
}

/*********************
*  appendString  *
*********************/

//	The DB_ENV->log_printf method appends an informational message to the Berkeley DB database environment log files.
//	The DB_ENV->log_printf method allows applications to include information in the database environment log files, 
//	for later review using the db_printlog utility. This method is intended for debugging and performance tuning.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_printf.html
void Rbdb_LogController_appendStringToCurrentLog(	Rbdb_LogController*		log_controller,
																									char*					log_string,
																									... )	{
	
	Rbdb_Environment*		environment	=	log_controller->parent_environment;
	//	FIX - var args needs to be implemented

	DB_TXN*	transaction_id	=	NULL;
	if ( environment->transaction_controller != NULL )	{
		transaction_id	=	Rbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
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
void Rbdb_LogController_flushLogsToDisk(	Rbdb_LogController*		log_controller,
 											Rbdb_LogSequenceNumber*	log_sequence_number )	{
	
	DB_ENV*		environment	=	log_controller->parent_environment->wrapped_bdb_environment;

	environment->log_flush(	environment,
							log_sequence_number->wrapped_bdb_log_sequence_number );
}

/*********************
*  appendRecord  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_put.html
void Rbdb_LogController_appendLogRecord(	Rbdb_LogController*		log_controller,
 											Rbdb_Record*				log_record )	{
	
	Rbdb_Environment*		environment	=	log_controller->parent_environment;
	
	Rbdb_Log*	log	=	Rbdb_Log_new( log_controller );
	
	environment->wrapped_bdb_environment->log_put(	environment->wrapped_bdb_environment,
													log->log_sequence_number->wrapped_bdb_log_sequence_number,
													log_record->data->wrapped_bdb_dbt->data,
													Rbdb_LogSettingsController_internal_appendRecordFlags( Rbdb_SettingsController_logSettingsController( Rbdb_Environment_settingsController( environment )) ) );
}

/*************************
*  cursorController  *
*************************/

Rbdb_LogCursorController* Rbdb_LogController_cursorController( Rbdb_LogController* log_controller )	{

	if ( log_controller->cursor_controller == NULL )	{
		log_controller->cursor_controller = Rbdb_LogCursorController_new( log_controller );
	}
	
	return log_controller->cursor_controller;
}






