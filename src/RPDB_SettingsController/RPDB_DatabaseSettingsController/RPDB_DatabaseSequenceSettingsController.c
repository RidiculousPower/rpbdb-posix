/*
 *		RPDB::SettingsController::SequenceSettingsController
 *		RPDB::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence::DatabaseSequenceSettingsController
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
 
#include "RPDB_DatabaseSequenceSettingsController.h"

	#include "RPDB_TransactionSettingsController.h"
	#include "RPDB_SettingsController.h"
	#include "RPDB_Environment.h"
	#include "RPDB_ThreadSettingsController.h"
	#include "RPDB_FileSettingsController.h"
	#include "RPDB_DatabaseSequenceController.h"

	#include "RPDB_DatabaseSequenceSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_DatabaseSequenceSettingsController* RPDB_DatabaseSequenceSettingsController_new( RPDB_DatabaseSettingsController* settings_controller )	{
	
	RPDB_DatabaseSequenceSettingsController*		sequence_settings_controller = calloc( 1, sizeof( RPDB_DatabaseSequenceSettingsController ) );

	sequence_settings_controller->parent_database_settings_controller = settings_controller;

	return sequence_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseSequenceSettingsController_free(	RPDB_DatabaseSequenceSettingsController** database_sequence_settings_controller )	{

	free( *database_sequence_settings_controller );
	*database_sequence_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseSequenceSettingsController_parentEnvironment(	RPDB_DatabaseSequenceSettingsController* database_sequence_settings_controller )	{
	return database_sequence_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseSequenceSettingsController_parentDatabase(	RPDB_DatabaseSequenceSettingsController* database_sequence_settings_controller )	{
	return database_sequence_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************
*  increasing  *
*****************/

//	DB_SEQ_INC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_flags.html
BOOL RPDB_DatabaseSequenceSettingsController_increasing( RPDB_DatabaseSequenceSettingsController* sequence_settings_controller )	{

	RPDB_DatabaseSequenceSettingsController_internal_getFlags( sequence_settings_controller );

	return sequence_settings_controller->increasing;
}

/*************************
*  setAsIncreasing  *
*************************/

void RPDB_DatabaseSequenceSettingsController_setAsIncreasing( RPDB_DatabaseSequenceSettingsController* sequence_settings_controller )	{

	//	We can only set an actual sequence; otherwise we're setting defaults
	if ( sequence_settings_controller->parent_sequence != NULL )	{
		
		DB_SEQUENCE*	db_sequence	=	sequence_settings_controller->parent_sequence->wrapped_bdb_sequence;
		
		db_sequence->set_flags(	db_sequence,
								DB_SEQ_INC );
	}

	sequence_settings_controller->increasing = TRUE;
	sequence_settings_controller->decreasing = FALSE;
}

/*****************
*  decreasing  *
*****************/

//	DB_SEQ_DEC              http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_flags.html
BOOL RPDB_DatabaseSequenceSettingsController_decreasing( RPDB_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	RPDB_DatabaseSequenceSettingsController_internal_getFlags( sequence_settings_controller );
	
	return sequence_settings_controller->decreasing;
}

/*************************
*  setAsDecreasing  *
*************************/

void RPDB_DatabaseSequenceSettingsController_setAsDecreasing( RPDB_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	//	We can only set an actual sequence; otherwise we're setting defaults
	if ( sequence_settings_controller->parent_sequence != NULL )	{
		
		DB_SEQUENCE*	db_sequence	=	sequence_settings_controller->parent_sequence->wrapped_bdb_sequence;
		
		db_sequence->set_flags(	db_sequence,
								DB_SEQ_DEC );
	}
	
	sequence_settings_controller->increasing = FALSE;
	sequence_settings_controller->decreasing = TRUE;
}

/*************
*  wrap  *
*************/

//	DB_SEQ_WRAP				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_flags.html
BOOL RPDB_DatabaseSequenceSettingsController_wrap( RPDB_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	RPDB_DatabaseSequenceSettingsController_internal_getFlags( sequence_settings_controller );
	
	return sequence_settings_controller->wrapping;
}

/*****************
*  setToWrap  *
*****************/

void RPDB_DatabaseSequenceSettingsController_setToWrap( RPDB_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	//	We can only set an actual sequence; otherwise we're setting defaults
	if ( sequence_settings_controller->parent_sequence != NULL )	{
		
		DB_SEQUENCE*	db_sequence	=	sequence_settings_controller->parent_sequence->wrapped_bdb_sequence;
		
		if ( sequence_settings_controller->wrapping == FALSE )	{
			
			db_sequence->set_flags(	db_sequence,
									DB_SEQ_WRAP );
		}
	}
	
	sequence_settings_controller->wrapping	= TRUE;
}

/*********************
*  rangeMinimum  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_range.html
int RPDB_DatabaseSequenceSettingsController_rangeMinimum( RPDB_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	return sequence_settings_controller->range_minimum;
}

/*************************
*  setRangeMinimum  *
*************************/

void RPDB_DatabaseSequenceSettingsController_setRangeMinimum(	RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller, 
																db_seq_t									range_minimum )	{
	
	sequence_settings_controller->range_minimum = range_minimum;
}

/*********************
*  rangeMaximum  *
*********************/

int RPDB_DatabaseSequenceSettingsController_rangeMaximum( RPDB_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	return sequence_settings_controller->range_maximum;
}

/************************
*  setRangeMaximum  *
************************/

void RPDB_DatabaseSequenceSettingsController_setRangeMaximum(	RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller,
																															db_seq_t									range_maximum )	{
	
	sequence_settings_controller->range_maximum = range_maximum;
}

/****************
*  cacheSize  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_cachesize.html
int RPDB_DatabaseSequenceSettingsController_cacheSize( RPDB_DatabaseSequenceSettingsController* sequence_settings_controller )	{
	
	//	If we have a local settings controller we can set the cachesize; otherwise we are returning a default
	if ( sequence_settings_controller->parent_sequence != NULL )	{		

		if ( sequence_settings_controller->number_of_cached_elements == RPDB_UNITIALIZED )	{

			DB_SEQUENCE*	bdb_sequence = sequence_settings_controller->parent_sequence->wrapped_bdb_sequence;

			bdb_sequence->get_cachesize(	bdb_sequence,
											&( sequence_settings_controller->number_of_cached_elements ) );
		}
	}

	return sequence_settings_controller->number_of_cached_elements;
}

/********************
*  setCacheSize  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_set_cachesize.html
void RPDB_DatabaseSequenceSettingsController_setCacheSize(	RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller,
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

db_seq_t RPDB_DatabaseSequenceSettingsController_initialValue( RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller )	{

	return sequence_settings_controller->initial_value;
}

/**********************
*  setInitialValue  *
**********************/

//	The DB_SEQUENCE->initial_value method may not be called after the DB_SEQUENCE->open method is called.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_initial_value.html
void RPDB_DatabaseSequenceSettingsController_setInitialValue(	RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller,
 												db_seq_t									initial_value )	{

	//	We can only set an initial value on an instance - otherwise we are setting a default
	if ( sequence_settings_controller->parent_sequence != NULL )	{		

		DB_SEQUENCE*	bdb_sequence = sequence_settings_controller->parent_sequence->wrapped_bdb_sequence;

		bdb_sequence->initial_value(	bdb_sequence,
										initial_value );
	}

	sequence_settings_controller->initial_value = initial_value;
}

/************************
*  defaultStepValue  *
************************/

int32_t RPDB_DatabaseSequenceSettingsController_defaultStepValue( RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller )	{

	return sequence_settings_controller->default_step_value;
}

/************************
*  setDefaultStepValue  *
************************/

void RPDB_DatabaseSequenceSettingsController_setDefaultStepValue(	RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller,
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
void RPDB_DatabaseSequenceSettingsController_internal_getFlags( RPDB_DatabaseSequenceSettingsController*	sequence_settings_controller )	{

	//	We can only get from an actual sequence
	if ( sequence_settings_controller->parent_sequence != NULL )	{
		
		DB_SEQUENCE*	db_sequence	=	sequence_settings_controller->parent_sequence->wrapped_bdb_sequence;
		
		uint32_t		flags;
		
		db_sequence->get_flags(	db_sequence,
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

int RPDB_DatabaseSequenceSettingsController_internal_closeFlags( RPDB_DatabaseSequenceSettingsController* sequence_settings_controller __attribute__((unused)) )	{

	//	Currently unused; returns 0
	return RPDB_NO_FLAGS;
}

/******************
*  stepByFlags  *
******************/

int RPDB_DatabaseSequenceSettingsController_internal_stepByFlags( RPDB_DatabaseSequenceSettingsController* sequence_settings_controller )	{

	return RPDB_TransactionSettingsController_prohibitSyncOnCommit( 
				RPDB_SettingsController_transactionSettingsController( 
					RPDB_Environment_settingsController( sequence_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ) ) );

}

/*****************
*  deleteFlags  *
*****************/

int RPDB_DatabaseSequenceSettingsController_internal_deleteFlags( RPDB_DatabaseSequenceSettingsController* sequence_settings_controller )	{

	return RPDB_TransactionSettingsController_prohibitSyncOnCommit( 
				RPDB_SettingsController_transactionSettingsController( 
					RPDB_Environment_settingsController( sequence_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ) ) );
}

/*************************
*  createSequenceFlags  *
*************************/

int RPDB_DatabaseSequenceSettingsController_internal_createSequenceFlags( RPDB_DatabaseSequenceController* database_sequence_controller __attribute__((unused)) )	{

	//	Currently unused - returns 0
	return RPDB_NO_FLAGS;
}

/*************************
*  openSequenceFlags  *
*************************/

int RPDB_DatabaseSequenceSettingsController_internal_openSequenceFlags( RPDB_DatabaseSequenceController* database_sequence_controller )	{

	RPDB_Environment*	environment = database_sequence_controller->parent_database->parent_database_controller->parent_environment;
	
	return	RPDB_ThreadSettingsController_on( RPDB_SettingsController_threadSettingsController( RPDB_Environment_settingsController( environment ) ) )
			|	RPDB_FileSettingsController_createIfNecessary( RPDB_SettingsController_fileSettingsController( RPDB_Environment_settingsController( environment ) ) )
			|	RPDB_FileSettingsController_isErrorIfDBExistsBeforeCreate( RPDB_SettingsController_fileSettingsController( RPDB_Environment_settingsController( environment ) ) );
	
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseSequenceSettingsController* RPDB_DatabaseSequenceSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseSequenceSettingsController* database_sequence_settings_controller )	{

	RPDB_DatabaseSequenceSettingsController* database_sequence_settings_controller_copy	=	RPDB_DatabaseSequenceSettingsController_new( database_sequence_settings_controller->parent_database_settings_controller );

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

