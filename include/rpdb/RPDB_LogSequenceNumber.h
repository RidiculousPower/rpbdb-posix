/*
 *		RPDB::LogController::Log::LogSequenceNumber
 *
 *	
 */

#ifndef RPDB_LOG_SEQUENCE_NUMBER
	#define RPDB_LOG_SEQUENCE_NUMBER
	
	#include "RPDB_BaseStandardInclude.h"

	/****************
	 *  Constants  *
	 ****************/

	typedef enum RPDB_SequenceComparison_e	{
		
		RP_SEQUENCE_ONE_IS_LESS			=	-1,
		RP_SEQUENCES_ARE_EQUAL			=	0,
		RP_SEQUENCE_ONE_IS_GREATER		=	1,
		RP_SEQUENCES_NO_COMPARISON		=	-2
		
	}	RPDB_SequenceComparison;

	/****************
	*  Prototypes  *
	****************/

	RPDB_LogSequenceNumber*		RPDB_LogSequenceNumber_new(		RPDB_Log*						parent_log );

	void										RPDB_LogSequenceNumber_free(	RPDB_LogSequenceNumber** log_sequence_number );
	RPDB_LogSettingsController*	RPDB_LogSequenceNumber_settingsController(	RPDB_LogSequenceNumber* log_sequence_number );
	RPDB_Environment*					RPDB_LogSequenceNumber_parentEnvironment(	RPDB_LogSequenceNumber* log_sequence_number );

	RPDB_SequenceComparison		RPDB_LogSequenceNumber_compare(	RPDB_LogSequenceNumber*		log_sequence_number_one,
																		RPDB_LogSequenceNumber*		log_sequence_number_two);

#endif

