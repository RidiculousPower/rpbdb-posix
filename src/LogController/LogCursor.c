/*
 *		RPbdb::LogController::LogCursorController::LogCursor
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "LogCursor.h"
#include "LogCursor_internal.h"

#include "Database_internal.h"

#include "LogCursorController.h"
#include "Log.h"
#include "LogSequenceNumber.h"

#include "Environment.h"

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

RPbdb_LogCursor* RPbdb_LogCursor_new( RPbdb_LogCursorController* parent_log_cursor_controller )	{
	
	RPbdb_LogCursor*	log_cursor = calloc( 1, sizeof( RPbdb_LogCursor ) );

	if ( parent_log_cursor_controller->runtime_storage_database != NULL )	{
		log_cursor->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_log_cursor_controller->runtime_storage_database,
																																									(void*) log_cursor );
	}

	log_cursor->parent_log_cursor_controller = parent_log_cursor_controller;

	//	Make call to instantiate local settings controller
	log_cursor->settings_controller	=	RPbdb_LogSettingsController_internal_copyOfSettingsControllerForInstance( RPbdb_SettingsController_logSettingsController( RPbdb_Environment_settingsController( parent_log_cursor_controller->parent_log_controller->parent_environment ) ) );

	return log_cursor;
}

/***************************
*  free  *
***************************/
void RPbdb_LogCursor_free(	RPbdb_LogCursor** log_cursor )	{

	if ( ( *log_cursor )->parent_log_cursor_controller->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *log_cursor )->parent_log_cursor_controller->runtime_storage_database,
																											( *log_cursor )->runtime_identifier );
	}
	RPbdb_LogCursor_internal_freeFromRuntimeStorage( log_cursor );
}

/***************************
*  free  *
***************************/
void RPbdb_LogCursor_internal_freeFromRuntimeStorage(	RPbdb_LogCursor** log_cursor )	{

	free( log_cursor );
}

/***************************
*  settingsController  *
***************************/
RPbdb_LogSettingsController* RPbdb_LogCursor_settingsController(	RPbdb_LogCursor* log_cursor )	{
	return log_cursor->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_LogCursor_parentEnvironment(	RPbdb_LogCursor* log_cursor )	{
	return log_cursor->parent_log_cursor_controller->parent_log_controller->parent_environment;
}

/*************
*  open  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_cursor.html
RPbdb_LogCursor* RPbdb_LogCursor_open( RPbdb_LogCursor* log_cursor )	{
	
	RPbdb_Environment*		environment	=	log_cursor->parent_log_cursor_controller->parent_log_controller->parent_environment;
	
	environment->wrapped_bdb_environment->log_cursor(	environment->wrapped_bdb_environment,
								&( log_cursor->wrapped_bdb_log_cursor ),
								RPbdb_LogSettingsController_internal_openFlags( RPbdb_SettingsController_logSettingsController( RPbdb_Environment_settingsController( environment ) ) ) );
								
	return log_cursor;
}

/*************
*  close  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/logc_close.html
void RPbdb_LogCursor_close( RPbdb_LogCursor* log_cursor )	{
	
	log_cursor->wrapped_bdb_log_cursor->close(	log_cursor->wrapped_bdb_log_cursor,
												RPbdb_LogSettingsController_internal_closeFlags( RPbdb_SettingsController_logSettingsController( RPbdb_Environment_settingsController( log_cursor->parent_log_cursor_controller->parent_log_controller->parent_environment ) ) ) );
}

/*********************************
*  retrieveCurrentLogRecord  *
*********************************/

RPbdb_Log* RPbdb_LogCursor_retrieveCurrentLogRecord( RPbdb_LogCursor* log_cursor )	{

	return RPbdb_LogCursor_internal_retrieveLogRecord(	log_cursor,
														DB_CURRENT );
}

/*****************************
*  retrieveFirstLogRecord  *
*****************************/

RPbdb_Log* RPbdb_LogCursor_retrieveFirstLogRecord( RPbdb_LogCursor* log_cursor )	{

	return RPbdb_LogCursor_internal_retrieveLogRecord(	log_cursor,
																	DB_FIRST );
}

/*****************************
*  retrieveLastLogRecord  *
*****************************/

RPbdb_Log* RPbdb_LogCursor_retrieveLastLogRecord( RPbdb_LogCursor* log_cursor )	{

	return RPbdb_LogCursor_internal_retrieveLogRecord(	log_cursor,
																	DB_LAST );
}

/*****************************
*  retrieveNextLogRecord  *
*****************************/

RPbdb_Log* RPbdb_LogCursor_retrieveNextLogRecord( RPbdb_LogCursor* log_cursor )	{

	return RPbdb_LogCursor_internal_retrieveLogRecord(	log_cursor,
																	DB_NEXT );
}

/*********************************
*  retrievePreviousLogRecord  *
*********************************/

RPbdb_Log* RPbdb_LogCursor_retrievePreviousLogRecord( RPbdb_LogCursor* log_cursor )	{

	return RPbdb_LogCursor_internal_retrieveLogRecord(	log_cursor,
																	DB_PREV );
}

/*************************
*  retrieveLogRecord  *
*************************/

RPbdb_Log* RPbdb_LogCursor_retrieveLogRecord(	RPbdb_LogCursor*			log_cursor,
 														RPbdb_LogSequenceNumber*	log_sequence_number )	{

	RPbdb_Log*		retrieval_log	=	RPbdb_Log_new( log_cursor->parent_log_cursor_controller->parent_log_controller );

	//	Free our empty LSN in the new log and set the pointer to the one we're retrieving
	RPbdb_LogSequenceNumber_free( & ( retrieval_log->log_sequence_number ) );
	retrieval_log->log_sequence_number	=	log_sequence_number;

	//	We want to make the key data (a void*) reference the LSN for this log
	retrieval_log->record->key->wrapped_bdb_dbt->data = retrieval_log->log_sequence_number->wrapped_bdb_log_sequence_number;
	
	log_cursor->wrapped_bdb_log_cursor->get(	log_cursor->wrapped_bdb_log_cursor,
												retrieval_log->log_sequence_number->wrapped_bdb_log_sequence_number,
												retrieval_log->record->key->wrapped_bdb_dbt->data,
												DB_SET );

	return retrieval_log;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************************
*  retrieveLogRecord  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/logc_get.html
RPbdb_Log* RPbdb_LogCursor_internal_retrieveLogRecord(	RPbdb_LogCursor*	log_cursor,
														uint32_t			which_record)	{
	
	RPbdb_Log*		retrieval_log	=	RPbdb_Log_new( log_cursor->parent_log_cursor_controller->parent_log_controller );

	//	We want to make the key data (a void*) reference the LSN for this log
	retrieval_log->record->key->wrapped_bdb_dbt->data = retrieval_log->log_sequence_number->wrapped_bdb_log_sequence_number;
	
	log_cursor->wrapped_bdb_log_cursor->get(	log_cursor->wrapped_bdb_log_cursor,
												retrieval_log->log_sequence_number->wrapped_bdb_log_sequence_number,
												retrieval_log->record->data->wrapped_bdb_dbt->data,
												which_record );
	
	return retrieval_log;
}









