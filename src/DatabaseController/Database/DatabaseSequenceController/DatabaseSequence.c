/*
 *		RPbdb::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseSequence.h"
#include "DatabaseSequence_internal.h"

#include "Environment.h"

#include "Database.h"
#include "Database_internal.h"

#include "DatabaseSequence_internal.h"

#include "Record.h"
#include "Key.h"

#include "TransactionController.h"
#include "TransactionController_internal.h"

#include "DatabaseSettingsController.h"
#include "DatabaseSequenceSettingsController.h"
#include "DatabaseSequenceSettingsController_internal.h"
	
#include <string.h>
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*********
*  new  *
*********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_class.html
RPbdb_DatabaseSequence* RPbdb_DatabaseSequence_new( RPbdb_DatabaseSequenceController*	parent_database_sequence_controller,
																									RPbdb_Database*										storage_database,
																									char*															storage_key )	{
	
	RPbdb_DatabaseSequence*	database_sequence	=	calloc( 1, sizeof( RPbdb_DatabaseSequence ) );
	
	//	parent controller and storage db
	database_sequence->parent_database_sequence_controller	=	parent_database_sequence_controller;
	database_sequence->parent_storage_database							=	storage_database;

	//	storage key in storage db
	RPbdb_Key*	storage_key_dbt	=	RPbdb_Key_new( NULL );
	storage_key_dbt->wrapped_bdb_dbt->data	=	storage_key;
	storage_key_dbt->wrapped_bdb_dbt->size	=	strlen( storage_key );
	database_sequence->storage_key			=	storage_key_dbt;
	
	//	since sequences are usually handled by the controller, which passes in an independent sequence database,
	//	but since we also want to allow the independent handling of sequences in whatever database one might like,
	//	we have to handle creation a little differently
	
	if ( parent_database_sequence_controller->runtime_storage_database != NULL )	{
		database_sequence->runtime_identifier =	RPbdb_Database_internal_storeRuntimeAddress(	parent_database_sequence_controller->runtime_storage_database,
																																												(void*) database_sequence );
	}
	
	RPbdb_DatabaseSettingsController*					database_settings_controller					=	RPbdb_Database_settingsController( parent_database_sequence_controller->parent_database );
	RPbdb_DatabaseSequenceSettingsController*	database_sequence_settings_controller	=	RPbdb_DatabaseSettingsController_sequenceSettingsController( database_settings_controller );
	//	Make call to instantiate local settings controller
	database_sequence->settings_controller	=	RPbdb_DatabaseSequenceSettingsController_internal_copyOfSettingsControllerForInstance( database_sequence_settings_controller );
	database_sequence->settings_controller->parent_sequence	=	database_sequence;

	RPbdb_DatabaseSequence_internal_initWrappedSequence( database_sequence );

	return database_sequence;
}

/*********
*  free  *
*********/

void RPbdb_DatabaseSequence_free(	RPbdb_DatabaseSequence** database_sequence )	{

	if ( ( *database_sequence )->parent_database_sequence_controller->runtime_storage_database != NULL )	{
		RPbdb_Database_internal_freeStoredRuntimeAddress(	( *database_sequence )->parent_database_sequence_controller->runtime_storage_database,
																											( *database_sequence )->runtime_identifier );
	}
	RPbdb_DatabaseSequence_internal_freeFromRuntimeStorage( database_sequence );
}

/***************************
*  settingsController  *
***************************/
RPbdb_DatabaseSequenceSettingsController* RPbdb_DatabaseSequence_settingsController(	RPbdb_DatabaseSequence* database_sequence )	{
	return database_sequence->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseSequence_parentEnvironment(	RPbdb_DatabaseSequence* database_sequence )	{
	return database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseSequence_parentDatabase(	RPbdb_DatabaseSequence* database_sequence )	{
	return database_sequence->parent_database_sequence_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Opening, Closing, Deleting
*******************************************************************************************************************************************************************************************/

/********************
*  openSequence  *
********************/

BOOL RPbdb_DatabaseSequence_isOpen( RPbdb_DatabaseSequence* database_sequence )	{
	return database_sequence->is_open;
}

/********************
*  openSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_open.html
RPbdb_DatabaseSequence* RPbdb_DatabaseSequence_openSequence(	RPbdb_DatabaseSequence*		database_sequence	)	{
	
	if ( ! database_sequence->is_open )	{

		RPbdb_Environment*	environment	=	database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;
		
		DB_TXN*	transaction_id	=	NULL;
		if ( database_sequence->parent_database_sequence_controller->parent_database->opened_in_transaction )	{
			transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
		}
		
		database_sequence->wrapped_bdb_sequence->open(	database_sequence->wrapped_bdb_sequence,
																										transaction_id,
																										database_sequence->storage_key->wrapped_bdb_dbt,
																										RPbdb_DatabaseSequenceSettingsController_internal_openSequenceFlags( database_sequence->parent_database_sequence_controller ) );

		database_sequence->is_open = TRUE;
	}
	
	return database_sequence;
}

/********************
*  closeSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_close.html
void RPbdb_DatabaseSequence_closeSequence( RPbdb_DatabaseSequence* database_sequence )	{
	
	if ( database_sequence->is_open )	{
		
		RPbdb_Database*														database															=	database_sequence->parent_database_sequence_controller->parent_database;
		RPbdb_DatabaseSettingsController*					database_settings_controller					=	RPbdb_Database_settingsController( database );
		RPbdb_DatabaseSequenceSettingsController*	database_sequence_settings_controller	=	RPbdb_DatabaseSettingsController_sequenceSettingsController( database_settings_controller );
		
		database_sequence->wrapped_bdb_sequence->close(	database_sequence->wrapped_bdb_sequence,
																										RPbdb_DatabaseSequenceSettingsController_internal_closeFlags( database_sequence_settings_controller ) );
		//	create a new sequence in case we desire to "re-open", so the re-creation can be done transparently since BDB doesn't let us re-open its own sequence
		RPbdb_DatabaseSequence_internal_initWrappedSequence( database_sequence );

		database_sequence->is_open = FALSE;
	}
}

/********************
*  renameSequence  *
********************/

void RPbdb_DatabaseSequence_renameSequence(	RPbdb_DatabaseSequence*	database_sequence,
																						char*										new_storage_key )	{
	
	//	get current value
	int32_t	current_value	=	RPbdb_DatabaseSequence_step( database_sequence ) - 1;
	RPbdb_DatabaseSequence_deleteSequence( database_sequence );
	RPbdb_DatabaseSequence_closeSequence( database_sequence );
	database_sequence->storage_key->wrapped_bdb_dbt->data	=	new_storage_key;
	database_sequence->storage_key->wrapped_bdb_dbt->size	=	strlen( new_storage_key );
	RPbdb_DatabaseSequence_internal_initWrappedSequence( database_sequence );
	RPbdb_DatabaseSequence_openSequence( database_sequence );
	//	take to previous value
	RPbdb_DatabaseSequence_stepBy( database_sequence, current_value );
}

/********************
*  deleteSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_remove.html
void RPbdb_DatabaseSequence_deleteSequence( RPbdb_DatabaseSequence* database_sequence )	{
	
	RPbdb_DatabaseSequence_openSequence( database_sequence );

	RPbdb_Environment*	environment	=	database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;
	
	DB_TXN*	transaction_id	=	NULL;
	if ( database_sequence->parent_database_sequence_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	RPbdb_Database*														database															=	database_sequence->parent_database_sequence_controller->parent_database;
	RPbdb_DatabaseSettingsController*					database_settings_controller					=	RPbdb_Database_settingsController( database );
	RPbdb_DatabaseSequenceSettingsController*	database_sequence_settings_controller	=	RPbdb_DatabaseSettingsController_sequenceSettingsController( database_settings_controller );

	database_sequence->wrapped_bdb_sequence->remove(	database_sequence->wrapped_bdb_sequence,
																										transaction_id,
																										RPbdb_DatabaseSequenceSettingsController_internal_deleteFlags( database_sequence_settings_controller ) );

	//	create a new sequence in case we desire to "re-open", so the re-creation can be done transparently since BDB doesn't let us re-open its own sequence
	RPbdb_DatabaseSequence_internal_initWrappedSequence( database_sequence );

	database_sequence->is_open = FALSE;
	RPbdb_DatabaseSequence_openSequence( database_sequence );
}

/*******************************************************************************************************************************************************************************************
																		Stepping
*******************************************************************************************************************************************************************************************/

/*********
*  step  *
*********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_get.html
int32_t RPbdb_DatabaseSequence_step( RPbdb_DatabaseSequence*	database_sequence )	{
	
	RPbdb_DatabaseSequence_openSequence( database_sequence );
	
	RPbdb_Database*														database															=	database_sequence->parent_database_sequence_controller->parent_database;
	RPbdb_DatabaseSettingsController*					database_settings_controller					=	RPbdb_Database_settingsController( database );
	RPbdb_DatabaseSequenceSettingsController*	database_sequence_settings_controller	=	RPbdb_DatabaseSettingsController_sequenceSettingsController( database_settings_controller );
	int32_t	sequence_value	=	RPbdb_DatabaseSequence_stepBy(	database_sequence,
																													database_sequence_settings_controller->default_step_value );
	
	return sequence_value;
}

/************
*  stepBy  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_get.html
int32_t RPbdb_DatabaseSequence_stepBy(	RPbdb_DatabaseSequence*	database_sequence,
																			int32_t									step_value	)	{
	
	RPbdb_DatabaseSequence_openSequence( database_sequence );

	RPbdb_Environment*	environment	=	database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;

	DB_TXN*	transaction_id	=	NULL;
	if ( database_sequence->parent_database_sequence_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	RPbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	RPbdb_Database*														database															=	database_sequence->parent_database_sequence_controller->parent_database;
	RPbdb_DatabaseSettingsController*					database_settings_controller					=	RPbdb_Database_settingsController( database );
	RPbdb_DatabaseSequenceSettingsController*	database_sequence_settings_controller	=	RPbdb_DatabaseSettingsController_sequenceSettingsController( database_settings_controller );
	
	db_seq_t	next_value	=	0;

	int	step_by_flags	=	RPbdb_DatabaseSequenceSettingsController_internal_stepByFlags( database_sequence_settings_controller );
	
	database_sequence->wrapped_bdb_sequence->get(	database_sequence->wrapped_bdb_sequence,
																								transaction_id,
																								step_value,
																								& next_value,
																								step_by_flags );

	return next_value;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/***************************
*  freeFromRuntimeStorage  *
***************************/

void RPbdb_DatabaseSequence_internal_freeFromRuntimeStorage(	RPbdb_DatabaseSequence** database_sequence )	{

	if ( ( *database_sequence )->settings_controller != NULL )	{
		RPbdb_DatabaseSequenceSettingsController_free( & ( ( *database_sequence )->settings_controller ) );
	}

	free( *database_sequence );
}

/************************
*  initWrappedSequence  *
************************/

void RPbdb_DatabaseSequence_internal_initWrappedSequence(	RPbdb_DatabaseSequence* database_sequence )	{
	
	db_sequence_create(	&( database_sequence->wrapped_bdb_sequence ),
											database_sequence->parent_storage_database->wrapped_bdb_database, 
											RPbdb_DatabaseSequenceSettingsController_internal_createSequenceFlags( database_sequence->settings_controller ) );

	RPbdb_DatabaseSequenceSettingsController*	sequence_settings_controller	=	database_sequence->settings_controller;
	
	if (			sequence_settings_controller->increasing )	{
		RPbdb_DatabaseSequenceSettingsController_setAsIncreasing( sequence_settings_controller );
	}
	else if (	sequence_settings_controller->decreasing )	{
		RPbdb_DatabaseSequenceSettingsController_setAsDecreasing( sequence_settings_controller );
	}
	
	if (	sequence_settings_controller->wrapping )	{
		RPbdb_DatabaseSequenceSettingsController_setToWrap( sequence_settings_controller );
	}

	if (	sequence_settings_controller->range_minimum )	{
		RPbdb_DatabaseSequenceSettingsController_setRangeMinimum( sequence_settings_controller, sequence_settings_controller->range_minimum );
	}
	if (	sequence_settings_controller->range_maximum )	{
		RPbdb_DatabaseSequenceSettingsController_setRangeMaximum( sequence_settings_controller, sequence_settings_controller->range_maximum );
	}

	if (	sequence_settings_controller->number_of_cached_elements )	{
		RPbdb_DatabaseSequenceSettingsController_setCacheSize(	sequence_settings_controller, sequence_settings_controller->number_of_cached_elements );
	}

	if (	sequence_settings_controller->initial_value )	{
		RPbdb_DatabaseSequenceSettingsController_setInitialValue( sequence_settings_controller, sequence_settings_controller->initial_value );
	}

	if (	sequence_settings_controller->default_step_value )	{
		RPbdb_DatabaseSequenceSettingsController_setDefaultStepValue( sequence_settings_controller, sequence_settings_controller->default_step_value );
	}
	
}
