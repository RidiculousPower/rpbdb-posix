/*
 *		Rbdb::LogController::LogCursorController::LogCursor
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_LogCursor.h"
#include "Rbdb_LogCursor_internal.h"

#include "Rbdb_Database_internal.h"

#include "Rbdb_LogCursorController.h"
#include "Rbdb_Log.h"
#include "Rbdb_LogSequenceNumber.h"

#include "Rbdb_Environment.h"

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

Rbdb_LogCursor* Rbdb_LogCursor_new( Rbdb_LogCursorController* parent_log_cursor_controller )	{
	
	Rbdb_LogCursor*	log_cursor = calloc( 1, sizeof( Rbdb_LogCursor ) );

	if ( parent_log_cursor_controller->runtime_storage_database != NULL )	{
		log_cursor->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_log_cursor_controller->runtime_storage_database,
																																									(void*) log_cursor );
	}

	log_cursor->parent_log_cursor_controller = parent_log_cursor_controller;

	//	Make call to instantiate local settings controller
	log_cursor->settings_controller	=	Rbdb_LogSettingsController_internal_copyOfSettingsControllerForInstance( Rbdb_SettingsController_logSettingsController( Rbdb_Environment_settingsController( parent_log_cursor_controller->parent_log_controller->parent_environment ) ) );

	return log_cursor;
}

/***************************
*  free  *
***************************/
void Rbdb_LogCursor_free(	Rbdb_LogCursor** log_cursor )	{

	if ( ( *log_cursor )->parent_log_cursor_controller->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *log_cursor )->parent_log_cursor_controller->runtime_storage_database,
																											( *log_cursor )->runtime_identifier );
	}
	Rbdb_LogCursor_internal_freeFromRuntimeStorage( log_cursor );
}

/***************************
*  free  *
***************************/
void Rbdb_LogCursor_internal_freeFromRuntimeStorage(	Rbdb_LogCursor** log_cursor )	{

	free( log_cursor );
}

/***************************
*  settingsController  *
***************************/
Rbdb_LogSettingsController* Rbdb_LogCursor_settingsController(	Rbdb_LogCursor* log_cursor )	{
	return log_cursor->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_LogCursor_parentEnvironment(	Rbdb_LogCursor* log_cursor )	{
	return log_cursor->parent_log_cursor_controller->parent_log_controller->parent_environment;
}

/*************
*  open  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_cursor.html
Rbdb_LogCursor* Rbdb_LogCursor_open( Rbdb_LogCursor* log_cursor )	{
	
	Rbdb_Environment*		environment	=	log_cursor->parent_log_cursor_controller->parent_log_controller->parent_environment;
	
	environment->wrapped_bdb_environment->log_cursor(	environment->wrapped_bdb_environment,
								&( log_cursor->wrapped_bdb_log_cursor ),
								Rbdb_LogSettingsController_internal_openFlags( Rbdb_SettingsController_logSettingsController( Rbdb_Environment_settingsController( environment ) ) ) );
								
	return log_cursor;
}

/*************
*  close  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/logc_close.html
void Rbdb_LogCursor_close( Rbdb_LogCursor* log_cursor )	{
	
	log_cursor->wrapped_bdb_log_cursor->close(	log_cursor->wrapped_bdb_log_cursor,
												Rbdb_LogSettingsController_internal_closeFlags( Rbdb_SettingsController_logSettingsController( Rbdb_Environment_settingsController( log_cursor->parent_log_cursor_controller->parent_log_controller->parent_environment ) ) ) );
}

/*********************************
*  retrieveCurrentLogRecord  *
*********************************/

Rbdb_Log* Rbdb_LogCursor_retrieveCurrentLogRecord( Rbdb_LogCursor* log_cursor )	{

	return Rbdb_LogCursor_internal_retrieveLogRecord(	log_cursor,
														DB_CURRENT );
}

/*****************************
*  retrieveFirstLogRecord  *
*****************************/

Rbdb_Log* Rbdb_LogCursor_retrieveFirstLogRecord( Rbdb_LogCursor* log_cursor )	{

	return Rbdb_LogCursor_internal_retrieveLogRecord(	log_cursor,
																	DB_FIRST );
}

/*****************************
*  retrieveLastLogRecord  *
*****************************/

Rbdb_Log* Rbdb_LogCursor_retrieveLastLogRecord( Rbdb_LogCursor* log_cursor )	{

	return Rbdb_LogCursor_internal_retrieveLogRecord(	log_cursor,
																	DB_LAST );
}

/*****************************
*  retrieveNextLogRecord  *
*****************************/

Rbdb_Log* Rbdb_LogCursor_retrieveNextLogRecord( Rbdb_LogCursor* log_cursor )	{

	return Rbdb_LogCursor_internal_retrieveLogRecord(	log_cursor,
																	DB_NEXT );
}

/*********************************
*  retrievePreviousLogRecord  *
*********************************/

Rbdb_Log* Rbdb_LogCursor_retrievePreviousLogRecord( Rbdb_LogCursor* log_cursor )	{

	return Rbdb_LogCursor_internal_retrieveLogRecord(	log_cursor,
																	DB_PREV );
}

/*************************
*  retrieveLogRecord  *
*************************/

Rbdb_Log* Rbdb_LogCursor_retrieveLogRecord(	Rbdb_LogCursor*			log_cursor,
 														Rbdb_LogSequenceNumber*	log_sequence_number )	{

	Rbdb_Log*		retrieval_log	=	Rbdb_Log_new( log_cursor->parent_log_cursor_controller->parent_log_controller );

	//	Free our empty LSN in the new log and set the pointer to the one we're retrieving
	Rbdb_LogSequenceNumber_free( & ( retrieval_log->log_sequence_number ) );
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
Rbdb_Log* Rbdb_LogCursor_internal_retrieveLogRecord(	Rbdb_LogCursor*	log_cursor,
														uint32_t			which_record)	{
	
	Rbdb_Log*		retrieval_log	=	Rbdb_Log_new( log_cursor->parent_log_cursor_controller->parent_log_controller );

	//	We want to make the key data (a void*) reference the LSN for this log
	retrieval_log->record->key->wrapped_bdb_dbt->data = retrieval_log->log_sequence_number->wrapped_bdb_log_sequence_number;
	
	log_cursor->wrapped_bdb_log_cursor->get(	log_cursor->wrapped_bdb_log_cursor,
												retrieval_log->log_sequence_number->wrapped_bdb_log_sequence_number,
												retrieval_log->record->data->wrapped_bdb_dbt->data,
												which_record );
	
	return retrieval_log;
}









