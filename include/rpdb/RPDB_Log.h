/*
 *		RPDB::LogController::Log
 *
 *	
 */

#ifndef RPDB_LOG
	#define RPDB_LOG

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_Log*					RPDB_Log_new(					RPDB_LogController*		parent_log_controller );

	void						RPDB_Log_free(	RPDB_Log** log );
	RPDB_LogSettingsController*	RPDB_Log_settingsController(	RPDB_Log* log );
	RPDB_Environment*		RPDB_Log_parentEnvironment(	RPDB_Log* log );

	RPDB_Record*				RPDB_Log_logRecord(			RPDB_Log*					log );
	RPDB_LogSequenceNumber*	RPDB_Log_logSequenceNumber(	RPDB_Log*					log );
	char*						RPDB_Log_filename(				RPDB_Log*					log );


#endif

