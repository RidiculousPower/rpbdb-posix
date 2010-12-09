/*
 *		Rbdb::LogController::Log::LogSequenceNumber
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_LogSequenceNumber.h"

#include "Rbdb_LogCursorController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_LogSequenceNumber* Rbdb_LogSequenceNumber_new( Rbdb_Log* parent_log )	{
	
	Rbdb_LogSequenceNumber*		log_sequence_number = calloc( 1, sizeof( Rbdb_LogSequenceNumber ) );

	log_sequence_number->parent_log = parent_log;

	return log_sequence_number;
}

/***************************
*  free  *
***************************/
void Rbdb_LogSequenceNumber_free(	Rbdb_LogSequenceNumber** log_sequence_number )	{

	free( log_sequence_number );
}

/***************************
*  settingsController  *
***************************/
Rbdb_LogSettingsController* Rbdb_LogSequenceNumber_settingsController(	Rbdb_LogSequenceNumber* log_sequence_number )	{
	return log_sequence_number->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_LogSequenceNumber_parentEnvironment(	Rbdb_LogSequenceNumber* log_sequence_number )	{
	return log_sequence_number->parent_log->parent_log_controller->parent_environment;
}

/****************
*  compare  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_compare.html
Rbdb_SequenceComparison Rbdb_LogSequenceNumber_compare(	Rbdb_LogSequenceNumber*	log_sequence_number_one,
 															Rbdb_LogSequenceNumber*	log_sequence_number_two)	{
	
	switch ( log_compare(	log_sequence_number_one->wrapped_bdb_log_sequence_number,
							log_sequence_number_two->wrapped_bdb_log_sequence_number ) )	{
		
		case -1:
			return RP_SEQUENCE_ONE_IS_LESS;
			break;
		case 1:
			return RP_SEQUENCE_ONE_IS_GREATER;
			break;
		case 0:
			return RP_SEQUENCES_ARE_EQUAL;
			break;
	}
	return RP_SEQUENCES_NO_COMPARISON;
}


