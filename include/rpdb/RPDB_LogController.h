/*
 *		RPDB::LogController
 *
 *		BDB logging implementation for applications described here: 
 *      http://www.oracle.com/technology/documentation/berkeley-db/db/ref/apprec/def.html
 *
 *		Description of process for full backup with BDB:
 *      http://www.oracle.com/technology/documentation/berkeley-db/db/ref/transapp/archival.html
 *	
 */

#ifndef RPDB_LOG_CONTROLLER
	#define RPDB_LOG_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_LogController*			RPDB_LogController_new(				RPDB_Environment*							parent_environment );

	void							RPDB_LogController_free(	RPDB_LogController** log_controller );
	RPDB_LogSettingsController*	RPDB_LogController_settingsController(	RPDB_LogController* log_controller );
	RPDB_Environment*		RPDB_LogController_parentEnvironment(	RPDB_LogController* log_controller );

	void							RPDB_LogController_appendStringToCurrentLog(		RPDB_LogController*			log_controller,
			  						 										char*							log_string,
			  						 										... );
	void						RPDB_LogController_appendLogRecord(		RPDB_LogController*					log_controller,
				 							   								RPDB_Record*				log_record );
	void							RPDB_LogController_flushLogsToDisk(	RPDB_LogController*			log_controller,
	 								   										RPDB_LogSequenceNumber*		log_sequence_number );
	RPDB_LogCursorController*		RPDB_LogController_cursorController(	RPDB_LogController*			log_controller );


#endif

