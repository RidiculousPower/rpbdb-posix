/*
 *		Rbdb::LogController::Log
 *
 *	
 */

#ifndef RBDB_LOG
	#define RBDB_LOG

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_Log*					Rbdb_Log_new(					Rbdb_LogController*		parent_log_controller );

	void						Rbdb_Log_free(	Rbdb_Log** log );
	Rbdb_LogSettingsController*	Rbdb_Log_settingsController(	Rbdb_Log* log );
	Rbdb_Environment*		Rbdb_Log_parentEnvironment(	Rbdb_Log* log );

	Rbdb_Record*				Rbdb_Log_logRecord(			Rbdb_Log*					log );
	Rbdb_LogSequenceNumber*	Rbdb_Log_logSequenceNumber(	Rbdb_Log*					log );
	char*						Rbdb_Log_filename(				Rbdb_Log*					log );


#endif

