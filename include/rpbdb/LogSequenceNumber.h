/*
 *		RPbdb::LogController::Log::LogSequenceNumber
 *
 *	
 */

#ifndef RPBDB_LOG_SEQUENCE_NUMBER
	#define RPBDB_LOG_SEQUENCE_NUMBER
	
	#include "BaseStandardInclude.h"

	/****************
	 *  Constants  *
	 ****************/

	typedef enum RPbdb_SequenceComparison_e	{
		
		RP_SEQUENCE_ONE_IS_LESS			=	-1,
		RP_SEQUENCES_ARE_EQUAL			=	0,
		RP_SEQUENCE_ONE_IS_GREATER		=	1,
		RP_SEQUENCES_NO_COMPARISON		=	-2
		
	}	RPbdb_SequenceComparison;

	/****************
	*  Prototypes  *
	****************/

	RPbdb_LogSequenceNumber*		RPbdb_LogSequenceNumber_new(		RPbdb_Log*						parent_log );

	void										RPbdb_LogSequenceNumber_free(	RPbdb_LogSequenceNumber** log_sequence_number );
	RPbdb_LogSettingsController*	RPbdb_LogSequenceNumber_settingsController(	RPbdb_LogSequenceNumber* log_sequence_number );
	RPbdb_Environment*					RPbdb_LogSequenceNumber_parentEnvironment(	RPbdb_LogSequenceNumber* log_sequence_number );

	RPbdb_SequenceComparison		RPbdb_LogSequenceNumber_compare(	RPbdb_LogSequenceNumber*		log_sequence_number_one,
																		RPbdb_LogSequenceNumber*		log_sequence_number_two);

#endif

