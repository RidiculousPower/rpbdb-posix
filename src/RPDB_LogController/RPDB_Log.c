/*
 *		RPDB::LogController::Log
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_Log.h"

#include "RPDB_Database_internal.h"

#include "RPDB_LogSequenceNumber.h"

#include "RPDB_Environment.h"

#include "RPDB_Record.h"

#include "RPDB_SettingsController.h"
#include "RPDB_LogSettingsController.h"	
#include "RPDB_LogSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_Log* RPDB_Log_new( RPDB_LogController* parent_log_controller )	{
	
	RPDB_Log*		log = calloc( 1, sizeof( RPDB_Log ) );

	if ( parent_log_controller->runtime_storage_database != NULL )	{
		log->runtime_identifier =	RPDB_Database_internal_storeRuntimeAddress(	parent_log_controller->runtime_storage_database,
																																					(void*) log );
	}

	log->parent_log_controller = parent_log_controller;
	
	return log;
}


/***************************
*  free  *
***************************/
void RPDB_Log_free(	RPDB_Log** log )	{

	if ( ( *log )->parent_log_controller->runtime_storage_database != NULL )	{
		RPDB_Database_internal_freeStoredRuntimeAddress(	( *log )->parent_log_controller->runtime_storage_database,
																											( *log )->runtime_identifier );
	}

	if ( ( *log )->log_sequence_number != NULL )	{
		RPDB_LogSequenceNumber_free( & ( ( *log )->log_sequence_number ) );
	}
	if ( ( *log )->record != NULL )	{
		RPDB_Record_free( & ( ( *log )->record ) );
	}
	
	free( *log );
	*log	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_LogSettingsController* RPDB_Log_settingsController(	RPDB_Log* log )	{
	return log->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_Log_parentEnvironment(	RPDB_Log* log )	{
	return log->parent_log_controller->parent_environment;
}

/*****************
*  logRecord  *
*****************/

RPDB_Record* RPDB_Log_logRecord( RPDB_Log* log )	{

	return log->record;
}

/*************************
*  sequenceNumbers  *
*************************/

RPDB_LogSequenceNumber* RPDB_Log_logSequenceNumber( RPDB_Log* log )	{
	
	return log->log_sequence_number;
}


/*************
*  file  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_file.html
char* RPDB_Log_filename( RPDB_Log* log )	{

	RPDB_Environment*		environment	=	log->parent_log_controller->parent_environment;

	environment->wrapped_bdb_environment->log_file(	environment->wrapped_bdb_environment,
							log->log_sequence_number->wrapped_bdb_log_sequence_number,
							log->filename,
							//	The len parameter is the length of the namep buffer in bytes. 
							//	Log filenames are normally quite short, on the order of 10 characters.
							MAX_LOGFILE_FILENAME_LENGTH );
	
	return log->filename;
}


