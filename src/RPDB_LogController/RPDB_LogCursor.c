/*
 *		RPDB::LogController::LogCursorController::LogCursor
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_LogCursor.h"
#include "RPDB_LogCursor_internal.h"

#include "RPDB_LogCursorController.h"
#include "RPDB_Log.h"
#include "RPDB_LogSequenceNumber.h"

#include "RPDB_Environment.h"

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

RPDB_LogCursor* RPDB_LogCursor_new( RPDB_LogCursorController* parent_log_cursor_controller )	{
	
	RPDB_LogCursor*	log_cursor = calloc( 1, sizeof( RPDB_LogCursor ) );

	log_cursor->parent_log_cursor_controller = parent_log_cursor_controller;

	//	Make call to instantiate local settings controller
	log_cursor->settings_controller	=	RPDB_LogSettingsController_internal_copyOfSettingsControllerForInstance( RPDB_SettingsController_logSettingsController( RPDB_Environment_settingsController( parent_log_cursor_controller->parent_log_controller->parent_environment ) ) );

	return log_cursor;
}

/***************************
*  free  *
***************************/
void RPDB_LogCursor_free(	RPDB_LogCursor** log_cursor )	{

	free( log_cursor );
}

/***************************
*  settingsController  *
***************************/
RPDB_LogSettingsController* RPDB_LogCursor_settingsController(	RPDB_LogCursor* log_cursor )	{
	return log_cursor->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_LogCursor_parentEnvironment(	RPDB_LogCursor* log_cursor )	{
	return log_cursor->parent_log_cursor_controller->parent_log_controller->parent_environment;
}

/*************
*  open  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_cursor.html
RPDB_LogCursor* RPDB_LogCursor_open( RPDB_LogCursor* log_cursor )	{
	
	RPDB_Environment*		environment	=	log_cursor->parent_log_cursor_controller->parent_log_controller->parent_environment;
	
	environment->wrapped_bdb_environment->log_cursor(	environment->wrapped_bdb_environment,
								&( log_cursor->wrapped_bdb_log_cursor ),
								RPDB_LogSettingsController_internal_openFlags( RPDB_SettingsController_logSettingsController( RPDB_Environment_settingsController( environment ) ) ) );
								
	return log_cursor;
}

/*************
*  close  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/logc_close.html
void RPDB_LogCursor_close( RPDB_LogCursor* log_cursor )	{
	
	log_cursor->wrapped_bdb_log_cursor->close(	log_cursor->wrapped_bdb_log_cursor,
												RPDB_LogSettingsController_internal_closeFlags( RPDB_SettingsController_logSettingsController( RPDB_Environment_settingsController( log_cursor->parent_log_cursor_controller->parent_log_controller->parent_environment ) ) ) );
}

/*********************************
*  retrieveCurrentLogRecord  *
*********************************/

RPDB_Log* RPDB_LogCursor_retrieveCurrentLogRecord( RPDB_LogCursor* log_cursor )	{

	return RPDB_LogCursor_internal_retrieveLogRecord(	log_cursor,
														DB_CURRENT );
}

/*****************************
*  retrieveFirstLogRecord  *
*****************************/

RPDB_Log* RPDB_LogCursor_retrieveFirstLogRecord( RPDB_LogCursor* log_cursor )	{

	return RPDB_LogCursor_internal_retrieveLogRecord(	log_cursor,
																	DB_FIRST );
}

/*****************************
*  retrieveLastLogRecord  *
*****************************/

RPDB_Log* RPDB_LogCursor_retrieveLastLogRecord( RPDB_LogCursor* log_cursor )	{

	return RPDB_LogCursor_internal_retrieveLogRecord(	log_cursor,
																	DB_LAST );
}

/*****************************
*  retrieveNextLogRecord  *
*****************************/

RPDB_Log* RPDB_LogCursor_retrieveNextLogRecord( RPDB_LogCursor* log_cursor )	{

	return RPDB_LogCursor_internal_retrieveLogRecord(	log_cursor,
																	DB_NEXT );
}

/*********************************
*  retrievePreviousLogRecord  *
*********************************/

RPDB_Log* RPDB_LogCursor_retrievePreviousLogRecord( RPDB_LogCursor* log_cursor )	{

	return RPDB_LogCursor_internal_retrieveLogRecord(	log_cursor,
																	DB_PREV );
}

/*************************
*  retrieveLogRecord  *
*************************/

RPDB_Log* RPDB_LogCursor_retrieveLogRecord(	RPDB_LogCursor*			log_cursor,
 														RPDB_LogSequenceNumber*	log_sequence_number )	{

	RPDB_Log*		retrieval_log	=	RPDB_Log_new( log_cursor->parent_log_cursor_controller->parent_log_controller );

	//	Free our empty LSN in the new log and set the pointer to the one we're retrieving
	RPDB_LogSequenceNumber_free( & ( retrieval_log->log_sequence_number ) );
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
RPDB_Log* RPDB_LogCursor_internal_retrieveLogRecord(	RPDB_LogCursor*	log_cursor,
														uint32_t			which_record)	{
	
	RPDB_Log*		retrieval_log	=	RPDB_Log_new( log_cursor->parent_log_cursor_controller->parent_log_controller );

	//	We want to make the key data (a void*) reference the LSN for this log
	retrieval_log->record->key->wrapped_bdb_dbt->data = retrieval_log->log_sequence_number->wrapped_bdb_log_sequence_number;
	
	log_cursor->wrapped_bdb_log_cursor->get(	log_cursor->wrapped_bdb_log_cursor,
												retrieval_log->log_sequence_number->wrapped_bdb_log_sequence_number,
												retrieval_log->record->data->wrapped_bdb_dbt->data,
												which_record );
	
	return retrieval_log;
}









