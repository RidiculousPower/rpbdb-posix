/*
 *		Rbdb::LogController::Log::LogSequenceNumber
 *
 *	
 */

#ifndef Rbdb_LOG_SEQUENCE_NUMBER
	#define Rbdb_LOG_SEQUENCE_NUMBER
	
	#include "Rbdb_BaseStandardInclude.h"

	/****************
	 *  Constants  *
	 ****************/

	typedef enum Rbdb_SequenceComparison_e	{
		
		RP_SEQUENCE_ONE_IS_LESS			=	-1,
		RP_SEQUENCES_ARE_EQUAL			=	0,
		RP_SEQUENCE_ONE_IS_GREATER		=	1,
		RP_SEQUENCES_NO_COMPARISON		=	-2
		
	}	Rbdb_SequenceComparison;

	/****************
	*  Prototypes  *
	****************/

	Rbdb_LogSequenceNumber*		Rbdb_LogSequenceNumber_new(		Rbdb_Log*						parent_log );

	void										Rbdb_LogSequenceNumber_free(	Rbdb_LogSequenceNumber** log_sequence_number );
	Rbdb_LogSettingsController*	Rbdb_LogSequenceNumber_settingsController(	Rbdb_LogSequenceNumber* log_sequence_number );
	Rbdb_Environment*					Rbdb_LogSequenceNumber_parentEnvironment(	Rbdb_LogSequenceNumber* log_sequence_number );

	Rbdb_SequenceComparison		Rbdb_LogSequenceNumber_compare(	Rbdb_LogSequenceNumber*		log_sequence_number_one,
																		Rbdb_LogSequenceNumber*		log_sequence_number_two);

#endif

