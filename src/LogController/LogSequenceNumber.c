/*
 *		RPbdb::LogController::Log::LogSequenceNumber
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "LogSequenceNumber.h"

#include "LogCursorController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_LogSequenceNumber* RPbdb_LogSequenceNumber_new( RPbdb_Log* parent_log )	{
	
	RPbdb_LogSequenceNumber*		log_sequence_number = calloc( 1, sizeof( RPbdb_LogSequenceNumber ) );

	log_sequence_number->parent_log = parent_log;

	return log_sequence_number;
}

/***************************
*  free  *
***************************/
void RPbdb_LogSequenceNumber_free(	RPbdb_LogSequenceNumber** log_sequence_number )	{

	free( log_sequence_number );
}

/***************************
*  settingsController  *
***************************/
RPbdb_LogSettingsController* RPbdb_LogSequenceNumber_settingsController(	RPbdb_LogSequenceNumber* log_sequence_number )	{
	return log_sequence_number->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_LogSequenceNumber_parentEnvironment(	RPbdb_LogSequenceNumber* log_sequence_number )	{
	return log_sequence_number->parent_log->parent_log_controller->parent_environment;
}

/****************
*  compare  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_compare.html
RPbdb_SequenceComparison RPbdb_LogSequenceNumber_compare(	RPbdb_LogSequenceNumber*	log_sequence_number_one,
 															RPbdb_LogSequenceNumber*	log_sequence_number_two)	{
	
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


