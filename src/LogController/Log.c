/*
 *		RPbdb::LogController::Log
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Log.h"
#include "Log_internal.h"

#include "Database_internal.h"

#include "LogSequenceNumber.h"

#include "Environment.h"

#include "Record.h"

#include "SettingsController.h"
#include "LogSettingsController.h"	
#include "LogSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_Log* RPbdb_Log_new( RPbdb_LogController* parent_log_controller )	{
	
	RPbdb_Log*		log = calloc( 1, sizeof( RPbdb_Log ) );

	if ( parent_log_controller->runtime_storage_database != NULL )	{
		log->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_log_controller->runtime_storage_database,
																																					(void*) log );
	}

	log->parent_log_controller = parent_log_controller;
	
	return log;
}


/***************************
*  free  *
***************************/

void RPbdb_Log_free(	RPbdb_Log** log )	{

	if ( ( *log )->parent_log_controller->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *log )->parent_log_controller->runtime_storage_database,
																											( *log )->runtime_identifier );
	}
	RPbdb_Log_internal_freeFromRuntimeStorage( log );
}

/***************************
*  free  *
***************************/

void RPbdb_Log_internal_freeFromRuntimeStorage(	RPbdb_Log** log )	{

	if ( ( *log )->log_sequence_number != NULL )	{
		RPbdb_LogSequenceNumber_free( & ( ( *log )->log_sequence_number ) );
	}
	if ( ( *log )->record != NULL )	{
		RPbdb_Record_free( & ( ( *log )->record ) );
	}
	
	free( *log );
	*log	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPbdb_LogSettingsController* RPbdb_Log_settingsController(	RPbdb_Log* log )	{
	return log->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_Log_parentEnvironment(	RPbdb_Log* log )	{
	return log->parent_log_controller->parent_environment;
}

/*****************
*  logRecord  *
*****************/

RPbdb_Record* RPbdb_Log_logRecord( RPbdb_Log* log )	{

	return log->record;
}

/*************************
*  sequenceNumbers  *
*************************/

RPbdb_LogSequenceNumber* RPbdb_Log_logSequenceNumber( RPbdb_Log* log )	{
	
	return log->log_sequence_number;
}


/*************
*  file  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_file.html
char* RPbdb_Log_filename( RPbdb_Log* log )	{

	RPbdb_Environment*		environment	=	log->parent_log_controller->parent_environment;

	environment->wrapped_bdb_environment->log_file(	environment->wrapped_bdb_environment,
							log->log_sequence_number->wrapped_bdb_log_sequence_number,
							log->filename,
							//	The len parameter is the length of the namep buffer in bytes. 
							//	Log filenames are normally quite short, on the order of 10 characters.
							MAX_LOGFILE_FILENAME_LENGTH );
	
	return log->filename;
}


