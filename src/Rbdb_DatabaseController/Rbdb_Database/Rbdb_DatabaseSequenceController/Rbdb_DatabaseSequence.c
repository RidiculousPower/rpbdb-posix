/*
 *		Rbdb::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseSequence.h"
#include "Rbdb_DatabaseSequence_internal.h"

#include "Rbdb_Environment.h"

#include "Rbdb_Database.h"
#include "Rbdb_Database_internal.h"

#include "Rbdb_DatabaseSequence_internal.h"

#include "Rbdb_Record.h"
#include "Rbdb_Key.h"

#include "Rbdb_TransactionController.h"
#include "Rbdb_TransactionController_internal.h"

#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseSequenceSettingsController.h"
#include "Rbdb_DatabaseSequenceSettingsController_internal.h"
	
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
Rbdb_DatabaseSequence* Rbdb_DatabaseSequence_new( Rbdb_DatabaseSequenceController*	parent_database_sequence_controller,
																									Rbdb_Database*										storage_database,
																									char*															storage_key )	{
	
	Rbdb_DatabaseSequence*	database_sequence	=	calloc( 1, sizeof( Rbdb_DatabaseSequence ) );
	
	//	parent controller and storage db
	database_sequence->parent_database_sequence_controller	=	parent_database_sequence_controller;
	database_sequence->parent_storage_database							=	storage_database;

	//	storage key in storage db
	Rbdb_Key*	storage_key_dbt	=	Rbdb_Key_new( NULL );
	storage_key_dbt->wrapped_bdb_dbt->data	=	storage_key;
	storage_key_dbt->wrapped_bdb_dbt->size	=	strlen( storage_key );
	database_sequence->storage_key			=	storage_key_dbt;
	
	//	since sequences are usually handled by the controller, which passes in an independent sequence database,
	//	but since we also want to allow the independent handling of sequences in whatever database one might like,
	//	we have to handle creation a little differently
	
	if ( parent_database_sequence_controller->runtime_storage_database != NULL )	{
		database_sequence->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_database_sequence_controller->runtime_storage_database,
																																												(void*) database_sequence );
	}
	
	Rbdb_DatabaseSettingsController*					database_settings_controller					=	Rbdb_Database_settingsController( parent_database_sequence_controller->parent_database );
	Rbdb_DatabaseSequenceSettingsController*	database_sequence_settings_controller	=	Rbdb_DatabaseSettingsController_sequenceSettingsController( database_settings_controller );
	//	Make call to instantiate local settings controller
	database_sequence->settings_controller	=	Rbdb_DatabaseSequenceSettingsController_internal_copyOfSettingsControllerForInstance( database_sequence_settings_controller );
	database_sequence->settings_controller->parent_sequence	=	database_sequence;

	Rbdb_DatabaseSequence_internal_initWrappedSequence( database_sequence );

	return database_sequence;
}

/*********
*  free  *
*********/

void Rbdb_DatabaseSequence_free(	Rbdb_DatabaseSequence** database_sequence )	{

	if ( ( *database_sequence )->parent_database_sequence_controller->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *database_sequence )->parent_database_sequence_controller->runtime_storage_database,
																											( *database_sequence )->runtime_identifier );
	}
	Rbdb_DatabaseSequence_internal_freeFromRuntimeStorage( database_sequence );
}

/***************************
*  settingsController  *
***************************/
Rbdb_DatabaseSequenceSettingsController* Rbdb_DatabaseSequence_settingsController(	Rbdb_DatabaseSequence* database_sequence )	{
	return database_sequence->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseSequence_parentEnvironment(	Rbdb_DatabaseSequence* database_sequence )	{
	return database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseSequence_parentDatabase(	Rbdb_DatabaseSequence* database_sequence )	{
	return database_sequence->parent_database_sequence_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Opening, Closing, Deleting
*******************************************************************************************************************************************************************************************/

/********************
*  openSequence  *
********************/

BOOL Rbdb_DatabaseSequence_isOpen( Rbdb_DatabaseSequence* database_sequence )	{
	return database_sequence->is_open;
}

/********************
*  openSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_open.html
Rbdb_DatabaseSequence* Rbdb_DatabaseSequence_openSequence(	Rbdb_DatabaseSequence*		database_sequence	)	{
	
	if ( ! database_sequence->is_open )	{

		Rbdb_Environment*	environment	=	database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;
		
		DB_TXN*	transaction_id	=	NULL;
		if ( database_sequence->parent_database_sequence_controller->parent_database->opened_in_transaction )	{
			transaction_id	=	Rbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
		}
		
		database_sequence->wrapped_bdb_sequence->open(	database_sequence->wrapped_bdb_sequence,
																										transaction_id,
																										database_sequence->storage_key->wrapped_bdb_dbt,
																										Rbdb_DatabaseSequenceSettingsController_internal_openSequenceFlags( database_sequence->parent_database_sequence_controller ) );

		database_sequence->is_open = TRUE;
	}
	
	return database_sequence;
}

/********************
*  closeSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_close.html
void Rbdb_DatabaseSequence_closeSequence( Rbdb_DatabaseSequence* database_sequence )	{
	
	if ( database_sequence->is_open )	{
		
		Rbdb_Database*														database															=	database_sequence->parent_database_sequence_controller->parent_database;
		Rbdb_DatabaseSettingsController*					database_settings_controller					=	Rbdb_Database_settingsController( database );
		Rbdb_DatabaseSequenceSettingsController*	database_sequence_settings_controller	=	Rbdb_DatabaseSettingsController_sequenceSettingsController( database_settings_controller );
		
		database_sequence->wrapped_bdb_sequence->close(	database_sequence->wrapped_bdb_sequence,
																										Rbdb_DatabaseSequenceSettingsController_internal_closeFlags( database_sequence_settings_controller ) );
		//	create a new sequence in case we desire to "re-open", so the re-creation can be done transparently since BDB doesn't let us re-open its own sequence
		Rbdb_DatabaseSequence_internal_initWrappedSequence( database_sequence );

		database_sequence->is_open = FALSE;
	}
}

/********************
*  renameSequence  *
********************/

void Rbdb_DatabaseSequence_renameSequence(	Rbdb_DatabaseSequence*	database_sequence,
																						char*										new_storage_key )	{
	
	//	get current value
	int32_t	current_value	=	Rbdb_DatabaseSequence_step( database_sequence ) - 1;
	Rbdb_DatabaseSequence_deleteSequence( database_sequence );
	Rbdb_DatabaseSequence_closeSequence( database_sequence );
	database_sequence->storage_key->wrapped_bdb_dbt->data	=	new_storage_key;
	database_sequence->storage_key->wrapped_bdb_dbt->size	=	strlen( new_storage_key );
	Rbdb_DatabaseSequence_internal_initWrappedSequence( database_sequence );
	Rbdb_DatabaseSequence_openSequence( database_sequence );
	//	take to previous value
	Rbdb_DatabaseSequence_stepBy( database_sequence, current_value );
}

/********************
*  deleteSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_remove.html
void Rbdb_DatabaseSequence_deleteSequence( Rbdb_DatabaseSequence* database_sequence )	{
	
	Rbdb_DatabaseSequence_openSequence( database_sequence );

	Rbdb_Environment*	environment	=	database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;
	
	DB_TXN*	transaction_id	=	NULL;
	if ( database_sequence->parent_database_sequence_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	Rbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	Rbdb_Database*														database															=	database_sequence->parent_database_sequence_controller->parent_database;
	Rbdb_DatabaseSettingsController*					database_settings_controller					=	Rbdb_Database_settingsController( database );
	Rbdb_DatabaseSequenceSettingsController*	database_sequence_settings_controller	=	Rbdb_DatabaseSettingsController_sequenceSettingsController( database_settings_controller );

	database_sequence->wrapped_bdb_sequence->remove(	database_sequence->wrapped_bdb_sequence,
																										transaction_id,
																										Rbdb_DatabaseSequenceSettingsController_internal_deleteFlags( database_sequence_settings_controller ) );

	//	create a new sequence in case we desire to "re-open", so the re-creation can be done transparently since BDB doesn't let us re-open its own sequence
	Rbdb_DatabaseSequence_internal_initWrappedSequence( database_sequence );

	database_sequence->is_open = FALSE;
	Rbdb_DatabaseSequence_openSequence( database_sequence );
}

/*******************************************************************************************************************************************************************************************
																		Stepping
*******************************************************************************************************************************************************************************************/

/*********
*  step  *
*********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_get.html
int32_t Rbdb_DatabaseSequence_step( Rbdb_DatabaseSequence*	database_sequence )	{
	
	Rbdb_DatabaseSequence_openSequence( database_sequence );
	
	Rbdb_Database*														database															=	database_sequence->parent_database_sequence_controller->parent_database;
	Rbdb_DatabaseSettingsController*					database_settings_controller					=	Rbdb_Database_settingsController( database );
	Rbdb_DatabaseSequenceSettingsController*	database_sequence_settings_controller	=	Rbdb_DatabaseSettingsController_sequenceSettingsController( database_settings_controller );
	int32_t	sequence_value	=	Rbdb_DatabaseSequence_stepBy(	database_sequence,
																													database_sequence_settings_controller->default_step_value );
	
	return sequence_value;
}

/************
*  stepBy  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_get.html
int32_t Rbdb_DatabaseSequence_stepBy(	Rbdb_DatabaseSequence*	database_sequence,
																			int32_t									step_value	)	{
	
	Rbdb_DatabaseSequence_openSequence( database_sequence );

	Rbdb_Environment*	environment	=	database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;

	DB_TXN*	transaction_id	=	NULL;
	if ( database_sequence->parent_database_sequence_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	Rbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	Rbdb_Database*														database															=	database_sequence->parent_database_sequence_controller->parent_database;
	Rbdb_DatabaseSettingsController*					database_settings_controller					=	Rbdb_Database_settingsController( database );
	Rbdb_DatabaseSequenceSettingsController*	database_sequence_settings_controller	=	Rbdb_DatabaseSettingsController_sequenceSettingsController( database_settings_controller );
	
	db_seq_t	next_value	=	0;

	int	step_by_flags	=	Rbdb_DatabaseSequenceSettingsController_internal_stepByFlags( database_sequence_settings_controller );
	
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

void Rbdb_DatabaseSequence_internal_freeFromRuntimeStorage(	Rbdb_DatabaseSequence** database_sequence )	{

	if ( ( *database_sequence )->settings_controller != NULL )	{
		Rbdb_DatabaseSequenceSettingsController_free( & ( ( *database_sequence )->settings_controller ) );
	}

	free( *database_sequence );
}

/************************
*  initWrappedSequence  *
************************/

void Rbdb_DatabaseSequence_internal_initWrappedSequence(	Rbdb_DatabaseSequence* database_sequence )	{
	
	db_sequence_create(	&( database_sequence->wrapped_bdb_sequence ),
											database_sequence->parent_storage_database->wrapped_bdb_database, 
											Rbdb_DatabaseSequenceSettingsController_internal_createSequenceFlags( database_sequence->settings_controller ) );

	Rbdb_DatabaseSequenceSettingsController*	sequence_settings_controller	=	database_sequence->settings_controller;
	
	if (			sequence_settings_controller->increasing )	{
		Rbdb_DatabaseSequenceSettingsController_setAsIncreasing( sequence_settings_controller );
	}
	else if (	sequence_settings_controller->decreasing )	{
		Rbdb_DatabaseSequenceSettingsController_setAsDecreasing( sequence_settings_controller );
	}
	
	if (	sequence_settings_controller->wrapping )	{
		Rbdb_DatabaseSequenceSettingsController_setToWrap( sequence_settings_controller );
	}

	if (	sequence_settings_controller->range_minimum )	{
		Rbdb_DatabaseSequenceSettingsController_setRangeMinimum( sequence_settings_controller, sequence_settings_controller->range_minimum );
	}
	if (	sequence_settings_controller->range_maximum )	{
		Rbdb_DatabaseSequenceSettingsController_setRangeMaximum( sequence_settings_controller, sequence_settings_controller->range_maximum );
	}

	if (	sequence_settings_controller->number_of_cached_elements )	{
		Rbdb_DatabaseSequenceSettingsController_setCacheSize(	sequence_settings_controller, sequence_settings_controller->number_of_cached_elements );
	}

	if (	sequence_settings_controller->initial_value )	{
		Rbdb_DatabaseSequenceSettingsController_setInitialValue( sequence_settings_controller, sequence_settings_controller->initial_value );
	}

	if (	sequence_settings_controller->default_step_value )	{
		Rbdb_DatabaseSequenceSettingsController_setDefaultStepValue( sequence_settings_controller, sequence_settings_controller->default_step_value );
	}
	
}
