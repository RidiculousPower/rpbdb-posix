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

#ifndef RBDB_LOG_CONTROLLER
	#define RBDB_LOG_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_LogController*			Rbdb_LogController_new(				Rbdb_Environment*							parent_environment );

	void							Rbdb_LogController_free(	Rbdb_LogController** log_controller );
	Rbdb_LogSettingsController*	Rbdb_LogController_settingsController(	Rbdb_LogController* log_controller );
	Rbdb_Environment*		Rbdb_LogController_parentEnvironment(	Rbdb_LogController* log_controller );

	void							Rbdb_LogController_appendStringToCurrentLog(		Rbdb_LogController*			log_controller,
			  						 										char*							log_string,
			  						 										... );
	void						Rbdb_LogController_appendLogRecord(		Rbdb_LogController*					log_controller,
				 							   								Rbdb_Record*				log_record );
	void							Rbdb_LogController_flushLogsToDisk(	Rbdb_LogController*			log_controller,
	 								   										Rbdb_LogSequenceNumber*		log_sequence_number );
	Rbdb_LogCursorController*		Rbdb_LogController_cursorController(	Rbdb_LogController*			log_controller );


#endif

