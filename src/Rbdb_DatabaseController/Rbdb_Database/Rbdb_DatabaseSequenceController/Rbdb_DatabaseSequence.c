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

#include "Rbdb_TransactionController.h"
#include "Rbdb_TransactionController_internal.h"

#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_DatabaseSequenceSettingsController.h"
#include "Rbdb_DatabaseSequenceSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*********
*  new  *
*********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_class.html
Rbdb_DatabaseSequence* Rbdb_DatabaseSequence_new( Rbdb_DatabaseSequenceController* parent_database_sequence_controller )	{
	
	Rbdb_DatabaseSequence*		database_sequence = calloc( 1, sizeof( Rbdb_DatabaseSequence ) );
	
	if ( parent_database_sequence_controller->runtime_storage_database != NULL )	{
		database_sequence->runtime_identifier =	Rbdb_Database_internal_storeRuntimeAddress(	parent_database_sequence_controller->runtime_storage_database,
																																												(void*) database_sequence );
	}
	
	database_sequence->parent_database_sequence_controller = parent_database_sequence_controller;
	
	db_sequence_create(	&( database_sequence->wrapped_bdb_sequence ),
						database_sequence->parent_database_sequence_controller->parent_database->wrapped_bdb_database, 
						Rbdb_DatabaseSequenceSettingsController_internal_createSequenceFlags( parent_database_sequence_controller ) );

	return database_sequence;
}

/***************************
*  free  *
***************************/

void Rbdb_DatabaseSequence_free(	Rbdb_DatabaseSequence** database_sequence )	{

	if ( ( *database_sequence )->parent_database_sequence_controller->runtime_storage_database != NULL )	{
		Rbdb_Database_internal_freeStoredRuntimeAddress(	( *database_sequence )->parent_database_sequence_controller->runtime_storage_database,
																											( *database_sequence )->runtime_identifier );
	}
	Rbdb_DatabaseSequence_internal_freeFromRuntimeStorage( database_sequence );
}

/***************************
*  freeFromRuntimeStorage  *
***************************/

void Rbdb_DatabaseSequence_internal_freeFromRuntimeStorage(	Rbdb_DatabaseSequence** database_sequence )	{

	if ( ( *database_sequence )->settings_controller != NULL )	{
		Rbdb_DatabaseSequenceSettingsController_free( & ( ( *database_sequence )->settings_controller ) );
	}

	free( *database_sequence );
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

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_open.html
Rbdb_DatabaseSequence* Rbdb_DatabaseSequence_openSequence(	Rbdb_DatabaseSequence*		database_sequence,
 																Rbdb_Record*				stored_at_key	)	{
	
	Rbdb_Environment*	environment	=	database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;
	
	DB_TXN*	transaction_id	=	NULL;
	if ( database_sequence->parent_database_sequence_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	Rbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	database_sequence->wrapped_bdb_sequence->open(	database_sequence->wrapped_bdb_sequence,
													transaction_id,
												stored_at_key->key->wrapped_bdb_dbt,
												Rbdb_DatabaseSequenceSettingsController_internal_openSequenceFlags( database_sequence->parent_database_sequence_controller ) );
	
	return database_sequence;
}

/********************
*  closeSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_close.html
void Rbdb_DatabaseSequence_closeSequence( Rbdb_DatabaseSequence* database_sequence )	{
	
	database_sequence->wrapped_bdb_sequence->close(	database_sequence->wrapped_bdb_sequence,
													Rbdb_DatabaseSequenceSettingsController_internal_closeFlags( Rbdb_DatabaseSettingsController_sequenceSettingsController( Rbdb_Database_settingsController( database_sequence->parent_database_sequence_controller->parent_database ) ) ) );
}

/********************
*  deleteSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_remove.html
void Rbdb_DatabaseSequence_deleteSequence( Rbdb_DatabaseSequence* database_sequence )	{
	
	Rbdb_Environment*	environment	=	database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;
	
	DB_TXN*	transaction_id	=	NULL;
	if ( database_sequence->parent_database_sequence_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	Rbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	database_sequence->wrapped_bdb_sequence->remove(	database_sequence->wrapped_bdb_sequence,
														transaction_id,
														Rbdb_DatabaseSequenceSettingsController_internal_deleteFlags( Rbdb_DatabaseSettingsController_sequenceSettingsController( Rbdb_Database_settingsController( database_sequence->parent_database_sequence_controller->parent_database ) ) ) );
}

/*******************************************************************************************************************************************************************************************
																		Stepping
*******************************************************************************************************************************************************************************************/

/*********
*  step  *
*********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_get.html
int32_t Rbdb_DatabaseSequence_step( Rbdb_DatabaseSequence*	database_sequence )	{

	return Rbdb_DatabaseSequence_stepBy(	database_sequence,
																				database_sequence->settings_controller->default_step_value );
}

/*****************
*  stepBackward  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_get.html
int32_t Rbdb_DatabaseSequence_stepBackward( Rbdb_DatabaseSequence*	database_sequence )	{

	return Rbdb_DatabaseSequence_stepBy(	database_sequence,
																				-database_sequence->settings_controller->default_step_value );
}

/************
*  stepBy  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_get.html
int32_t Rbdb_DatabaseSequence_stepBy(	Rbdb_DatabaseSequence*	database_sequence,
																			int32_t									step_value	)	{
	
	Rbdb_Environment*	environment	=	database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;

	DB_TXN*	transaction_id	=	NULL;
	if ( database_sequence->parent_database_sequence_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	Rbdb_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	database_sequence->wrapped_bdb_sequence->get(	database_sequence->wrapped_bdb_sequence,
																								transaction_id,
																								step_value,
																								&( database_sequence->current_value ),
																								Rbdb_DatabaseSequenceSettingsController_internal_stepByFlags( Rbdb_DatabaseSettingsController_sequenceSettingsController( Rbdb_Database_settingsController( database_sequence->parent_database_sequence_controller->parent_database ) ) ) );

	return database_sequence->current_value;
}

/*******************
*  stepBackwardBy  *
*******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_get.html
int32_t Rbdb_DatabaseSequence_stepBackwardBy(	Rbdb_DatabaseSequence*	database_sequence,
																							int32_t									step_value	)	{

	return Rbdb_DatabaseSequence_stepBy(	database_sequence,
																				-step_value );
}