/*
 *		RPbdb::LogController
 *
 *		BDB logging implementation for applications described here: 
 *      http://www.oracle.com/technology/documentation/berkeley-db/db/ref/apprec/def.html
 *
 *		Description of process for full backup with BDB:
 *      http://www.oracle.com/technology/documentation/berkeley-db/db/ref/transapp/archival.html
 *	
 */

#ifndef RPBDB_LOG_CONTROLLER
	#define RPBDB_LOG_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_LogController*			RPbdb_LogController_new(				RPbdb_Environment*							parent_environment );

	void							RPbdb_LogController_free(	RPbdb_LogController** log_controller );
	RPbdb_LogSettingsController*	RPbdb_LogController_settingsController(	RPbdb_LogController* log_controller );
	RPbdb_Environment*		RPbdb_LogController_parentEnvironment(	RPbdb_LogController* log_controller );

	void							RPbdb_LogController_appendStringToCurrentLog(		RPbdb_LogController*			log_controller,
			  						 										char*							log_string,
			  						 										... );
	void						RPbdb_LogController_appendLogRecord(		RPbdb_LogController*					log_controller,
				 							   								RPbdb_Record*				log_record );
	void							RPbdb_LogController_flushLogsToDisk(	RPbdb_LogController*			log_controller,
	 								   										RPbdb_LogSequenceNumber*		log_sequence_number );
	RPbdb_LogCursorController*		RPbdb_LogController_cursorController(	RPbdb_LogController*			log_controller );


#endif

