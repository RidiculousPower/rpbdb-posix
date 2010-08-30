/*
 *		RPDB::LogController::Log::LogSequenceNumber
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_LogSequenceNumber.h"

#include "RPDB_LogCursorController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_LogSequenceNumber* RPDB_LogSequenceNumber_new( RPDB_Log* parent_log )	{
	
	RPDB_LogSequenceNumber*		log_sequence_number = calloc( 1, sizeof( RPDB_LogSequenceNumber ) );

	log_sequence_number->parent_log = parent_log;

	return log_sequence_number;
}

/***************************
*  free  *
***************************/
void RPDB_LogSequenceNumber_free(	RPDB_LogSequenceNumber** log_sequence_number )	{

	free( log_sequence_number );
}

/***************************
*  settingsController  *
***************************/
RPDB_LogSettingsController* RPDB_LogSequenceNumber_settingsController(	RPDB_LogSequenceNumber* log_sequence_number )	{
	return log_sequence_number->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_LogSequenceNumber_parentEnvironment(	RPDB_LogSequenceNumber* log_sequence_number )	{
	return log_sequence_number->parent_log->parent_log_controller->parent_environment;
}

/****************
*  compare  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_compare.html
RPDB_SequenceComparison RPDB_LogSequenceNumber_compare(	RPDB_LogSequenceNumber*	log_sequence_number_one,
 															RPDB_LogSequenceNumber*	log_sequence_number_two)	{
	
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


