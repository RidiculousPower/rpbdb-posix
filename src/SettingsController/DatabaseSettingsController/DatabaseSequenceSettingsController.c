/*
 *		RPbdb::SettingsController::SequenceSettingsController
 *		RPbdb::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence::DatabaseSequenceSettingsController
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
 
#include "DatabaseSequenceSettingsController.h"

	#include "TransactionSettingsController.h"
	#include "SettingsController.h"
	#include "Environment.h"
	#include "ThreadSettingsController.h"
	#include "FileSettingsController.h"
	#include "DatabaseSequenceController.h"

	#include "DatabaseSequenceSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPbdb_DatabaseSequenceSettingsController* RPbdb_DatabaseSequenceSettingsController_new( RPbdb_DatabaseSettingsController* settings_controller )	{
	
	RPbdb_DatabaseSequenceSettingsController*		sequence_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseSequenceSettingsController ) );

	sequence_settings_controller->parent_database_settings_controller = settings_controller;

	return sequence_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseSequenceSettingsController_free(	RPbdb_DatabaseSequenceSettingsController** database_sequence_settings_controller )	{

	free( *database_sequence_settings_controller );
	*database_sequence_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseSequenceSettingsController_parentEnvironment(	RPbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller )	{
	return database_sequence_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseSequenceSettingsController_parentDatabase(	RPbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller )	{
	return database_sequence_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************
*  increasing  *
*****************/

//	DB_SEQ_INC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_flags.html
BOOL RPbdb_DatabaseSequenceSettingsController_increasing( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{

	RPbdb_DatabaseSequenceSettingsController_internal_getFlags( sequence_settings_controller );

	return sequence_settings_controller->increasing;
}

/*************************
*  setAsIncreasing  *
*************************/

void RPbdb_DatabaseSequenceSettingsController_setAsIncreasing( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{

	//	We can only set an actual sequence; otherwise we're setting defaults
	if ( sequence_settings_controller->parent_sequence != NULL )	{
		
		RPbdb_DatabaseSequence*	sequence	=	sequence_settings_controller->parent_sequence;
		
		sequence->wrapped_bdb_sequence->set_flags(	sequence->wrapped_bdb_sequence,
																								DB_SEQ_INC );
	}

	sequence_settings_controller->increasing = TRUE;
	sequence_settings_controller->decreasing = FALSE;
}

/*****************
*  decreasing  *
*****************/

//	DB_SEQ_DEC              http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_flags.html
BOOL RPbdb_DatabaseSequenceSettingsController_decreasing( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	RPbdb_DatabaseSequenceSettingsController_internal_getFlags( sequence_settings_controller );
	
	return sequence_settings_controller->decreasing;
}

/*************************
*  setAsDecreasing  *
*************************/

void RPbdb_DatabaseSequenceSettingsController_setAsDecreasing( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	//	We can only set an actual sequence; otherwise we're setting defaults
	if ( sequence_settings_controller->parent_sequence != NULL )	{
		
		RPbdb_DatabaseSequence*	sequence	=	sequence_settings_controller->parent_sequence;
		
		sequence->wrapped_bdb_sequence->set_flags(	sequence->wrapped_bdb_sequence,
																								DB_SEQ_DEC );
	}
	
	sequence_settings_controller->increasing = FALSE;
	sequence_settings_controller->decreasing = TRUE;
}

/*************
*  wrap  *
*************/

//	DB_SEQ_WRAP				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_flags.html
BOOL RPbdb_DatabaseSequenceSettingsController_wrap( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	RPbdb_DatabaseSequenceSettingsController_internal_getFlags( sequence_settings_controller );
	
	return sequence_settings_controller->wrapping;
}

/*****************
*  setToWrap  *
*****************/

void RPbdb_DatabaseSequenceSettingsController_setToWrap( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	//	We can only set an actual sequence; otherwise we're setting defaults
	if ( sequence_settings_controller->parent_sequence != NULL )	{
		
		RPbdb_DatabaseSequence*	sequence	=	sequence_settings_controller->parent_sequence;
		
		if ( sequence_settings_controller->wrapping == FALSE )	{
			
			sequence->wrapped_bdb_sequence->set_flags(	sequence->wrapped_bdb_sequence,
																									DB_SEQ_WRAP );
		}
	}
	
	sequence_settings_controller->wrapping	= TRUE;
}

/*********************
*  rangeMinimum  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_range.html
int RPbdb_DatabaseSequenceSettingsController_rangeMinimum( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	return sequence_settings_controller->range_minimum;
}

/*************************
*  setRangeMinimum  *
*************************/

void RPbdb_DatabaseSequenceSettingsController_setRangeMinimum(	RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller, 
																db_seq_t									range_minimum )	{
	
	sequence_settings_controller->range_minimum = range_minimum;
}

/*********************
*  rangeMaximum  *
*********************/

int RPbdb_DatabaseSequenceSettingsController_rangeMaximum( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	return sequence_settings_controller->range_maximum;
}

/************************
*  setRangeMaximum  *
************************/

void RPbdb_DatabaseSequenceSettingsController_setRangeMaximum(	RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																															db_seq_t									range_maximum )	{
	
	sequence_settings_controller->range_maximum = range_maximum;
}

/****************
*  cacheSize  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_cachesize.html
int RPbdb_DatabaseSequenceSettingsController_cacheSize( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	//	If we have a local settings controller we can set the cachesize; otherwise we are returning a default
	if ( sequence_settings_controller->parent_sequence != NULL )	{		

		if ( sequence_settings_controller->number_of_cached_elements == RPBDB_UNITIALIZED )	{

			RPbdb_DatabaseSequence*	sequence	=	sequence_settings_controller->parent_sequence;

			sequence->wrapped_bdb_sequence->get_cachesize(	sequence->wrapped_bdb_sequence,
																											&( sequence_settings_controller->number_of_cached_elements ) );
		}	
	}

	return sequence_settings_controller->number_of_cached_elements;
}

/********************
*  setCacheSize  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_cachesize.html
void RPbdb_DatabaseSequenceSettingsController_setCacheSize(	RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																														uint32_t										number_of_cached_elements	)	{
	
	//	If we have a local settings controller we can set the cachesize; otherwise we are setting a default
	if ( sequence_settings_controller->parent_sequence != NULL )	{		

		sequence_settings_controller->number_of_cached_elements = number_of_cached_elements;

		sequence_settings_controller->parent_sequence->wrapped_bdb_sequence->set_cachesize(	sequence_settings_controller->parent_sequence->wrapped_bdb_sequence,
																						   number_of_cached_elements );	
	}
	else	{		
		
		sequence_settings_controller->number_of_cached_elements = number_of_cached_elements;
	}
	
}

/********************
*  initialValue  *
********************/

db_seq_t RPbdb_DatabaseSequenceSettingsController_initialValue( RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller )	{

	return sequence_settings_controller->initial_value;
}

/**********************
*  setInitialValue  *
**********************/

//	The DB_SEQUENCE->initial_value method may not be called after the DB_SEQUENCE->open method is called.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_initial_value.html
void RPbdb_DatabaseSequenceSettingsController_setInitialValue(	RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																															db_seq_t																	initial_value )	{

	//	We can only set an initial value on an instance - otherwise we are setting a default
	if ( sequence_settings_controller->parent_sequence != NULL )	{		

		RPbdb_DatabaseSequence*	sequence	=	sequence_settings_controller->parent_sequence;

		sequence->wrapped_bdb_sequence->initial_value(	sequence->wrapped_bdb_sequence,
																										initial_value );
	}

	sequence_settings_controller->initial_value = initial_value;
}

/************************
*  defaultStepValue  *
************************/

int32_t RPbdb_DatabaseSequenceSettingsController_defaultStepValue( RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller )	{

	return sequence_settings_controller->default_step_value;
}

/************************
*  setDefaultStepValue  *
************************/

void RPbdb_DatabaseSequenceSettingsController_setDefaultStepValue(	RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																																	int32_t										default_step_value	)	{

	sequence_settings_controller->default_step_value = default_step_value;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/****************
*  getFlags  *
****************/

//	We don't need to return anything here - we just need to get the conglomerate flag and figure out what we started with
//	This needs to be tested
void RPbdb_DatabaseSequenceSettingsController_internal_getFlags( RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller )	{

	//	We can only get from an actual sequence
	if ( sequence_settings_controller->parent_sequence != NULL )	{
		
		RPbdb_DatabaseSequence*	sequence	=	sequence_settings_controller->parent_sequence;
		
		uint32_t		flags;
		
		sequence->wrapped_bdb_sequence->get_flags(	sequence->wrapped_bdb_sequence,
																								& flags );
		
		//	Are we wrapping?
		if (	flags - DB_SEQ_WRAP == DB_SEQ_DEC
			||	flags - DB_SEQ_WRAP == DB_SEQ_INC )	{
								
				sequence_settings_controller->wrapping = TRUE;
				
				if ( flags - DB_SEQ_DEC == 0 )	{

					sequence_settings_controller->decreasing = FALSE;
					sequence_settings_controller->increasing = TRUE;
				}
				else if ( flags - DB_SEQ_INC == 0 )	{
					
					sequence_settings_controller->increasing = TRUE;
					sequence_settings_controller->decreasing = FALSE;
				}
		}
		else if ( flags - DB_SEQ_WRAP == 0 )	{
		
			sequence_settings_controller->wrapping = TRUE;			
		}
		else	{

			sequence_settings_controller->wrapping = FALSE;

			if ( flags - DB_SEQ_DEC == 0 )	{
				
			}
			else if ( flags - DB_SEQ_INC == 0 )	{
				
			}
		}
	}
	
}

/****************
*  closeFlags  *
****************/

int RPbdb_DatabaseSequenceSettingsController_internal_closeFlags( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller __attribute__((unused)) )	{

	//	Currently unused; returns 0
	return RPBDB_NO_FLAGS;
}

/******************
*  stepByFlags  *
******************/

int RPbdb_DatabaseSequenceSettingsController_internal_stepByFlags( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{

	RPbdb_Environment*										parent_environment							=	sequence_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
	RPbdb_SettingsController*						settings_controller							=	RPbdb_Environment_settingsController( parent_environment );
	RPbdb_TransactionSettingsController*	transaction_settings_controller	=	RPbdb_SettingsController_transactionSettingsController( settings_controller );

	return RPbdb_TransactionSettingsController_prohibitSyncOnCommit( transaction_settings_controller );

}

/*****************
*  deleteFlags  *
*****************/

int RPbdb_DatabaseSequenceSettingsController_internal_deleteFlags( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{

	RPbdb_Environment*										parent_environment							=	sequence_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
	RPbdb_SettingsController*						settings_controller							=	RPbdb_Environment_settingsController( parent_environment );
	RPbdb_TransactionSettingsController*	transaction_settings_controller	=	RPbdb_SettingsController_transactionSettingsController( settings_controller );

	return RPbdb_TransactionSettingsController_prohibitSyncOnCommit( transaction_settings_controller );
}

/*************************
*  createSequenceFlags  *
*************************/

int RPbdb_DatabaseSequenceSettingsController_internal_createSequenceFlags( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller __attribute__((unused)) )	{

	//	Currently unused - returns 0
	return RPBDB_NO_FLAGS;
}

/*************************
*  openSequenceFlags  *
*************************/

int RPbdb_DatabaseSequenceSettingsController_internal_openSequenceFlags( RPbdb_DatabaseSequenceController* database_sequence_controller )	{

	RPbdb_Environment*	environment = database_sequence_controller->parent_database->parent_database_controller->parent_environment;
	
	return	RPbdb_ThreadSettingsController_on( RPbdb_SettingsController_threadSettingsController( RPbdb_Environment_settingsController( environment ) ) )
			|	RPbdb_FileSettingsController_createIfNecessary( RPbdb_SettingsController_fileSettingsController( RPbdb_Environment_settingsController( environment ) ) )
			|	RPbdb_FileSettingsController_isErrorIfDBExistsBeforeCreate( RPbdb_SettingsController_fileSettingsController( RPbdb_Environment_settingsController( environment ) ) );
	
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseSequenceSettingsController* RPbdb_DatabaseSequenceSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller )	{

	RPbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller_copy	=	RPbdb_DatabaseSequenceSettingsController_new( database_sequence_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_sequence_settings_controller_copy->initial_value	=	database_sequence_settings_controller->initial_value;
	database_sequence_settings_controller_copy->increasing	=	database_sequence_settings_controller->increasing;
	database_sequence_settings_controller_copy->range_minimum	=	database_sequence_settings_controller->range_minimum;
	database_sequence_settings_controller_copy->number_of_cached_elements	=	database_sequence_settings_controller->number_of_cached_elements;
	database_sequence_settings_controller_copy->decreasing	=	database_sequence_settings_controller->decreasing;
	database_sequence_settings_controller_copy->default_step_value	=	database_sequence_settings_controller->default_step_value;
	database_sequence_settings_controller_copy->range_maximum	=	database_sequence_settings_controller->range_maximum;
	database_sequence_settings_controller_copy->wrapping	=	database_sequence_settings_controller->wrapping;

	return database_sequence_settings_controller_copy;
}

