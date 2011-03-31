/*
 *		RPbdb::LogController::Log
 *
 *	
 */

#ifndef RPBDB_LOG
	#define RPBDB_LOG

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_Log*					RPbdb_Log_new(					RPbdb_LogController*		parent_log_controller );

	void						RPbdb_Log_free(	RPbdb_Log** log );
	RPbdb_LogSettingsController*	RPbdb_Log_settingsController(	RPbdb_Log* log );
	RPbdb_Environment*		RPbdb_Log_parentEnvironment(	RPbdb_Log* log );

	RPbdb_Record*				RPbdb_Log_logRecord(			RPbdb_Log*					log );
	RPbdb_LogSequenceNumber*	RPbdb_Log_logSequenceNumber(	RPbdb_Log*					log );
	char*						RPbdb_Log_filename(				RPbdb_Log*					log );


#endif

