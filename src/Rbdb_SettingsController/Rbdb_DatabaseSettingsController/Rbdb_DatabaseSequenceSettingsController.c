/*
 *		Rbdb::SettingsController::SequenceSettingsController
 *		Rbdb::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence::DatabaseSequenceSettingsController
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
 
#include "Rbdb_DatabaseSequenceSettingsController.h"

	#include "Rbdb_TransactionSettingsController.h"
	#include "Rbdb_SettingsController.h"
	#include "Rbdb_Environment.h"
	#include "Rbdb_ThreadSettingsController.h"
	#include "Rbdb_FileSettingsController.h"
	#include "Rbdb_DatabaseSequenceController.h"

	#include "Rbdb_DatabaseSequenceSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
Rbdb_DatabaseSequenceSettingsController* Rbdb_DatabaseSequenceSettingsController_new( Rbdb_DatabaseSettingsController* settings_controller )	{
	
	Rbdb_DatabaseSequenceSettingsController*		sequence_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseSequenceSettingsController ) );

	sequence_settings_controller->parent_database_settings_controller = settings_controller;

	return sequence_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseSequenceSettingsController_free(	Rbdb_DatabaseSequenceSettingsController** database_sequence_settings_controller )	{

	free( *database_sequence_settings_controller );
	*database_sequence_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseSequenceSettingsController_parentEnvironment(	Rbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller )	{
	return database_sequence_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseSequenceSettingsController_parentDatabase(	Rbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller )	{
	return database_sequence_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************
*  increasing  *
*****************/

//	DB_SEQ_INC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_flags.html
BOOL Rbdb_DatabaseSequenceSettingsController_increasing( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{

	Rbdb_DatabaseSequenceSettingsController_internal_getFlags( sequence_settings_controller );

	return sequence_settings_controller->increasing;
}

/*************************
*  setAsIncreasing  *
*************************/

void Rbdb_DatabaseSequenceSettingsController_setAsIncreasing( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{

	//	We can only set an actual sequence; otherwise we're setting defaults
	if ( sequence_settings_controller->parent_sequence != NULL )	{
		
		Rbdb_DatabaseSequence*	sequence	=	sequence_settings_controller->parent_sequence;
		
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
BOOL Rbdb_DatabaseSequenceSettingsController_decreasing( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	Rbdb_DatabaseSequenceSettingsController_internal_getFlags( sequence_settings_controller );
	
	return sequence_settings_controller->decreasing;
}

/*************************
*  setAsDecreasing  *
*************************/

void Rbdb_DatabaseSequenceSettingsController_setAsDecreasing( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	//	We can only set an actual sequence; otherwise we're setting defaults
	if ( sequence_settings_controller->parent_sequence != NULL )	{
		
		Rbdb_DatabaseSequence*	sequence	=	sequence_settings_controller->parent_sequence;
		
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
BOOL Rbdb_DatabaseSequenceSettingsController_wrap( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	Rbdb_DatabaseSequenceSettingsController_internal_getFlags( sequence_settings_controller );
	
	return sequence_settings_controller->wrapping;
}

/*****************
*  setToWrap  *
*****************/

void Rbdb_DatabaseSequenceSettingsController_setToWrap( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	//	We can only set an actual sequence; otherwise we're setting defaults
	if ( sequence_settings_controller->parent_sequence != NULL )	{
		
		Rbdb_DatabaseSequence*	sequence	=	sequence_settings_controller->parent_sequence;
		
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
int Rbdb_DatabaseSequenceSettingsController_rangeMinimum( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	return sequence_settings_controller->range_minimum;
}

/*************************
*  setRangeMinimum  *
*************************/

void Rbdb_DatabaseSequenceSettingsController_setRangeMinimum(	Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller, 
																db_seq_t									range_minimum )	{
	
	sequence_settings_controller->range_minimum = range_minimum;
}

/*********************
*  rangeMaximum  *
*********************/

int Rbdb_DatabaseSequenceSettingsController_rangeMaximum( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	return sequence_settings_controller->range_maximum;
}

/************************
*  setRangeMaximum  *
************************/

void Rbdb_DatabaseSequenceSettingsController_setRangeMaximum(	Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																															db_seq_t									range_maximum )	{
	
	sequence_settings_controller->range_maximum = range_maximum;
}

/****************
*  cacheSize  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_cachesize.html
int Rbdb_DatabaseSequenceSettingsController_cacheSize( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	//	If we have a local settings controller we can set the cachesize; otherwise we are returning a default
	if ( sequence_settings_controller->parent_sequence != NULL )	{		

		if ( sequence_settings_controller->number_of_cached_elements == RBDB_UNITIALIZED )	{

			Rbdb_DatabaseSequence*	sequence	=	sequence_settings_controller->parent_sequence;

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
void Rbdb_DatabaseSequenceSettingsController_setCacheSize(	Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
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

db_seq_t Rbdb_DatabaseSequenceSettingsController_initialValue( Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller )	{

	return sequence_settings_controller->initial_value;
}

/**********************
*  setInitialValue  *
**********************/

//	The DB_SEQUENCE->initial_value method may not be called after the DB_SEQUENCE->open method is called.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_initial_value.html
void Rbdb_DatabaseSequenceSettingsController_setInitialValue(	Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
																															db_seq_t																	initial_value )	{

	//	We can only set an initial value on an instance - otherwise we are setting a default
	if ( sequence_settings_controller->parent_sequence != NULL )	{		

		Rbdb_DatabaseSequence*	sequence	=	sequence_settings_controller->parent_sequence;

		sequence->wrapped_bdb_sequence->initial_value(	sequence->wrapped_bdb_sequence,
																										initial_value );
	}

	sequence_settings_controller->initial_value = initial_value;
}

/************************
*  defaultStepValue  *
************************/

int32_t Rbdb_DatabaseSequenceSettingsController_defaultStepValue( Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller )	{

	return sequence_settings_controller->default_step_value;
}

/************************
*  setDefaultStepValue  *
************************/

void Rbdb_DatabaseSequenceSettingsController_setDefaultStepValue(	Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller,
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
void Rbdb_DatabaseSequenceSettingsController_internal_getFlags( Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller )	{

	//	We can only get from an actual sequence
	if ( sequence_settings_controller->parent_sequence != NULL )	{
		
		Rbdb_DatabaseSequence*	sequence	=	sequence_settings_controller->parent_sequence;
		
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

int Rbdb_DatabaseSequenceSettingsController_internal_closeFlags( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller __attribute__((unused)) )	{

	//	Currently unused; returns 0
	return RBDB_NO_FLAGS;
}

/******************
*  stepByFlags  *
******************/

int Rbdb_DatabaseSequenceSettingsController_internal_stepByFlags( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{

	Rbdb_Environment*										parent_environment							=	sequence_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
	Rbdb_SettingsController*						settings_controller							=	Rbdb_Environment_settingsController( parent_environment );
	Rbdb_TransactionSettingsController*	transaction_settings_controller	=	Rbdb_SettingsController_transactionSettingsController( settings_controller );

	return Rbdb_TransactionSettingsController_prohibitSyncOnCommit( transaction_settings_controller );

}

/*****************
*  deleteFlags  *
*****************/

int Rbdb_DatabaseSequenceSettingsController_internal_deleteFlags( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller )	{

	Rbdb_Environment*										parent_environment							=	sequence_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
	Rbdb_SettingsController*						settings_controller							=	Rbdb_Environment_settingsController( parent_environment );
	Rbdb_TransactionSettingsController*	transaction_settings_controller	=	Rbdb_SettingsController_transactionSettingsController( settings_controller );

	return Rbdb_TransactionSettingsController_prohibitSyncOnCommit( transaction_settings_controller );
}

/*************************
*  createSequenceFlags  *
*************************/

int Rbdb_DatabaseSequenceSettingsController_internal_createSequenceFlags( Rbdb_DatabaseSequenceSettingsController* sequence_settings_controller __attribute__((unused)) )	{

	//	Currently unused - returns 0
	return RBDB_NO_FLAGS;
}

/*************************
*  openSequenceFlags  *
*************************/

int Rbdb_DatabaseSequenceSettingsController_internal_openSequenceFlags( Rbdb_DatabaseSequenceController* database_sequence_controller )	{

	Rbdb_Environment*	environment = database_sequence_controller->parent_database->parent_database_controller->parent_environment;
	
	return	Rbdb_ThreadSettingsController_on( Rbdb_SettingsController_threadSettingsController( Rbdb_Environment_settingsController( environment ) ) )
			|	Rbdb_FileSettingsController_createIfNecessary( Rbdb_SettingsController_fileSettingsController( Rbdb_Environment_settingsController( environment ) ) )
			|	Rbdb_FileSettingsController_isErrorIfDBExistsBeforeCreate( Rbdb_SettingsController_fileSettingsController( Rbdb_Environment_settingsController( environment ) ) );
	
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_DatabaseSequenceSettingsController* Rbdb_DatabaseSequenceSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller )	{

	Rbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller_copy	=	Rbdb_DatabaseSequenceSettingsController_new( database_sequence_settings_controller->parent_database_settings_controller );

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

