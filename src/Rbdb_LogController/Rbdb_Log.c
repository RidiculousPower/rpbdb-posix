/*
 *		Rbdb::LogController::Log
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_Log.h"
#include "Rbdb_Log_internal.h"

#include "Rbdb_Database_internal.h"

#include "Rbdb_LogSequenceNumber.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Record.h"

#include "Rbdb_SettingsController.h"
#include "Rbdb_LogSettingsController.h"	
#include "Rbdb_LogSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_Log* Rbdb_Log_new( Rbdb_LogController* parent_log_controller )	{
	
	Rbdb_Log*		log = calloc( 1, sizeof( Rbdb_Log ) );

	if ( parent_log_controller->runtime_storage_database != NULL )	{
		log->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_log_controller->runtime_storage_database,
																																					(void*) log );
	}

	log->parent_log_controller = parent_log_controller;
	
	return log;
}


/***************************
*  free  *
***************************/

void Rbdb_Log_free(	Rbdb_Log** log )	{

	if ( ( *log )->parent_log_controller->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *log )->parent_log_controller->runtime_storage_database,
																											( *log )->runtime_identifier );
	}
	Rbdb_Log_internal_freeFromRuntimeStorage( log );
}

/***************************
*  free  *
***************************/

void Rbdb_Log_internal_freeFromRuntimeStorage(	Rbdb_Log** log )	{

	if ( ( *log )->log_sequence_number != NULL )	{
		Rbdb_LogSequenceNumber_free( & ( ( *log )->log_sequence_number ) );
	}
	if ( ( *log )->record != NULL )	{
		Rbdb_Record_free( & ( ( *log )->record ) );
	}
	
	free( *log );
	*log	=	NULL;
}

/***************************
*  settingsController  *
***************************/
Rbdb_LogSettingsController* Rbdb_Log_settingsController(	Rbdb_Log* log )	{
	return log->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_Log_parentEnvironment(	Rbdb_Log* log )	{
	return log->parent_log_controller->parent_environment;
}

/*****************
*  logRecord  *
*****************/

Rbdb_Record* Rbdb_Log_logRecord( Rbdb_Log* log )	{

	return log->record;
}

/*************************
*  sequenceNumbers  *
*************************/

Rbdb_LogSequenceNumber* Rbdb_Log_logSequenceNumber( Rbdb_Log* log )	{
	
	return log->log_sequence_number;
}


/*************
*  file  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_file.html
char* Rbdb_Log_filename( Rbdb_Log* log )	{

	Rbdb_Environment*		environment	=	log->parent_log_controller->parent_environment;

	environment->wrapped_bdb_environment->log_file(	environment->wrapped_bdb_environment,
							log->log_sequence_number->wrapped_bdb_log_sequence_number,
							log->filename,
							//	The len parameter is the length of the namep buffer in bytes. 
							//	Log filenames are normally quite short, on the order of 10 characters.
							MAX_LOGFILE_FILENAME_LENGTH );
	
	return log->filename;
}


