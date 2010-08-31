/*
 *		RPDB::DatabaseController::Database::DatabaseSequenceController::DatabaseSequence
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseSequence.h"
#include "RPDB_DatabaseSequence_internal.h"

#include "RPDB_Environment.h"

#include "RPDB_Database.h"
#include "RPDB_Database_internal.h"

#include "RPDB_Record.h"

#include "RPDB_TransactionController.h"
#include "RPDB_TransactionController_internal.h"

#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_DatabaseSequenceSettingsController.h"
#include "RPDB_DatabaseSequenceSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*********
*  new  *
*********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_class.html
RPDB_DatabaseSequence* RPDB_DatabaseSequence_new( RPDB_DatabaseSequenceController* parent_database_sequence_controller )	{
	
	RPDB_DatabaseSequence*		database_sequence = calloc( 1, sizeof( RPDB_DatabaseSequence ) );
	
	if ( parent_database_sequence_controller->runtime_storage_database != NULL )	{
		database_sequence->runtime_identifier =	RPDB_Database_internal_storeRuntimeAddress(	parent_database_sequence_controller->runtime_storage_database,
																																												(void*) database_sequence );
	}
	
	database_sequence->parent_database_sequence_controller = parent_database_sequence_controller;
	
	db_sequence_create(	&( database_sequence->wrapped_bdb_sequence ),
						database_sequence->parent_database_sequence_controller->parent_database->wrapped_bdb_database, 
						RPDB_DatabaseSequenceSettingsController_internal_createSequenceFlags( parent_database_sequence_controller ) );

	return database_sequence;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseSequence_free(	RPDB_DatabaseSequence** database_sequence )	{

	if ( ( *database_sequence )->parent_database_sequence_controller->runtime_storage_database != NULL )	{
		RPDB_Database_internal_freeStoredRuntimeAddress(	( *database_sequence )->parent_database_sequence_controller->runtime_storage_database,
																											( *database_sequence )->runtime_identifier );
	}

	if ( ( *database_sequence )->settings_controller != NULL )	{
		RPDB_DatabaseSequenceSettingsController_free( & ( ( *database_sequence )->settings_controller ) );
	}

	free( *database_sequence );
}

/***************************
*  settingsController  *
***************************/
RPDB_DatabaseSequenceSettingsController* RPDB_DatabaseSequence_settingsController(	RPDB_DatabaseSequence* database_sequence )	{
	return database_sequence->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseSequence_parentEnvironment(	RPDB_DatabaseSequence* database_sequence )	{
	return database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseSequence_parentDatabase(	RPDB_DatabaseSequence* database_sequence )	{
	return database_sequence->parent_database_sequence_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Opening, Closing, Deleting
*******************************************************************************************************************************************************************************************/

/********************
*  openSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_open.html
RPDB_DatabaseSequence* RPDB_DatabaseSequence_openSequence(	RPDB_DatabaseSequence*		database_sequence,
 																RPDB_Record*				stored_at_key	)	{
	
	RPDB_Environment*	environment	=	database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;
	
	DB_TXN*	transaction_id	=	NULL;
	if ( database_sequence->parent_database_sequence_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	RPDB_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	database_sequence->wrapped_bdb_sequence->open(	database_sequence->wrapped_bdb_sequence,
													transaction_id,
												stored_at_key->key->wrapped_bdb_dbt,
												RPDB_DatabaseSequenceSettingsController_internal_openSequenceFlags( database_sequence->parent_database_sequence_controller ) );
	
	return database_sequence;
}

/********************
*  closeSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_close.html
void RPDB_DatabaseSequence_closeSequence( RPDB_DatabaseSequence* database_sequence )	{
	
	database_sequence->wrapped_bdb_sequence->close(	database_sequence->wrapped_bdb_sequence,
													RPDB_DatabaseSequenceSettingsController_internal_closeFlags( RPDB_DatabaseSettingsController_sequenceSettingsController( RPDB_Database_settingsController( database_sequence->parent_database_sequence_controller->parent_database ) ) ) );
}

/********************
*  deleteSequence  *
********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_remove.html
void RPDB_DatabaseSequence_deleteSequence( RPDB_DatabaseSequence* database_sequence )	{
	
	RPDB_Environment*	environment	=	database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;
	
	DB_TXN*	transaction_id	=	NULL;
	if ( database_sequence->parent_database_sequence_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	RPDB_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	database_sequence->wrapped_bdb_sequence->remove(	database_sequence->wrapped_bdb_sequence,
														transaction_id,
														RPDB_DatabaseSequenceSettingsController_internal_deleteFlags( RPDB_DatabaseSettingsController_sequenceSettingsController( RPDB_Database_settingsController( database_sequence->parent_database_sequence_controller->parent_database ) ) ) );
}

/*******************************************************************************************************************************************************************************************
																		Stepping
*******************************************************************************************************************************************************************************************/

/*********
*  step  *
*********/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_get.html
int32_t RPDB_DatabaseSequence_step( RPDB_DatabaseSequence*	database_sequence )	{

	return RPDB_DatabaseSequence_stepBy(	database_sequence,
																				database_sequence->settings_controller->default_step_value );
}

/*****************
*  stepBackward  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_get.html
int32_t RPDB_DatabaseSequence_stepBackward( RPDB_DatabaseSequence*	database_sequence )	{

	return RPDB_DatabaseSequence_stepBy(	database_sequence,
																				-database_sequence->settings_controller->default_step_value );
}

/************
*  stepBy  *
************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_get.html
int32_t RPDB_DatabaseSequence_stepBy(	RPDB_DatabaseSequence*	database_sequence,
																			int32_t									step_value	)	{
	
	RPDB_Environment*	environment	=	database_sequence->parent_database_sequence_controller->parent_database->parent_database_controller->parent_environment;

	DB_TXN*	transaction_id	=	NULL;
	if ( database_sequence->parent_database_sequence_controller->parent_database->opened_in_transaction )	{
		transaction_id	=	RPDB_TransactionController_internal_currentTransactionID( environment->transaction_controller );
	}
	
	database_sequence->wrapped_bdb_sequence->get(	database_sequence->wrapped_bdb_sequence,
																								transaction_id,
																								step_value,
																								&( database_sequence->current_value ),
																								RPDB_DatabaseSequenceSettingsController_internal_stepByFlags( RPDB_DatabaseSettingsController_sequenceSettingsController( RPDB_Database_settingsController( database_sequence->parent_database_sequence_controller->parent_database ) ) ) );

	return database_sequence->current_value;
}

/*******************
*  stepBackwardBy  *
*******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/seq_get.html
int32_t RPDB_DatabaseSequence_stepBackwardBy(	RPDB_DatabaseSequence*	database_sequence,
																							int32_t									step_value	)	{

	return RPDB_DatabaseSequence_stepBy(	database_sequence,
																				-step_value );
}