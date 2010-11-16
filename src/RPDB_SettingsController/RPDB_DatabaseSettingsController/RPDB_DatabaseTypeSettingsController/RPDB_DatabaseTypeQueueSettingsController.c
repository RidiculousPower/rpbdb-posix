/*
 *		RPDB::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeQueueSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseTypeQueueSettingsController.h"

#include "RPDB_Environment.h"
#include "RPDB_ErrorController.h"

#include "RPDB_DatabaseTypeSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseTypeQueueSettingsController* RPDB_DatabaseTypeQueueSettingsController_new( RPDB_DatabaseTypeSettingsController*						parent_database_type_settings_controller )	{

	RPDB_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller = calloc( 1, sizeof( RPDB_DatabaseTypeQueueSettingsController ) );

	database_type_queue_settings_controller->parent_database_type_settings_controller = parent_database_type_settings_controller;

	return database_type_queue_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseTypeQueueSettingsController_free(	RPDB_DatabaseTypeQueueSettingsController** database_type_queue_settings_controller )	{

	free( *database_type_queue_settings_controller );
	*database_type_queue_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseTypeQueueSettingsController_parentEnvironment(	RPDB_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{
	return database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseTypeQueueSettingsController_parentDatabase(	RPDB_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{
	return database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/*********************************
*  returnKeyDataPairsInOrder  *
*********************************/

//	DB_INORDER					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPDB_DatabaseTypeQueueSettingsController_returnKeyDataPairsInOrder( RPDB_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

	if ( database_type_queue_settings_controller->return_key_data_pairs_in_order )	{

		return DB_INORDER;
	}
	return FALSE;
}

	/*****************************************
	*  turnReturnKeyDataPairsInOrderOn  *
	*****************************************/

	void RPDB_DatabaseTypeQueueSettingsController_turnReturnKeyDataPairsInOrderOn( RPDB_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

		database_type_queue_settings_controller->return_key_data_pairs_in_order = TRUE;
	}

	/*****************************************
	*  turnReturnKeyDataPairsInOrderOff  *
	*****************************************/

	void RPDB_DatabaseTypeQueueSettingsController_turnReturnKeyDataPairsInOrderOff( RPDB_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

		database_type_queue_settings_controller->return_key_data_pairs_in_order = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/*****************************************
*  numberOfPagesForUnderlyingData  *
*****************************************/

//	For Queue Databases		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_q_extentsize.html
uint32_t RPDB_DatabaseTypeQueueSettingsController_numberOfPagesForUnderlyingData( RPDB_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

	RPDB_Database*		database	=	database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int		connection_error	= 0;

	if (		! database_type_queue_settings_controller->number_of_pages_for_underlying_data
			&&	database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
			
		if ( ( connection_error = database->wrapped_bdb_database->get_q_extentsize(	database->wrapped_bdb_database,
																																								&( database_type_queue_settings_controller->number_of_pages_for_underlying_data ) ) ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"RPDB_DatabaseTypeQueueSettingsController_numberOfPagesForUnderlyingData" );
		}
	}
	
	return database_type_queue_settings_controller->number_of_pages_for_underlying_data;
}

/*****************************************
*  setNumberOfPagesForUnderlyingData  *
*****************************************/

void RPDB_DatabaseTypeQueueSettingsController_setNumberOfPagesForUnderlyingData(	RPDB_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller, 
																					uint32_t										number_of_pages_for_underlying_data )	{
	
	RPDB_Database*		database = database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	int		connection_error	= 0;
	
	database_type_queue_settings_controller->number_of_pages_for_underlying_data = number_of_pages_for_underlying_data;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->set_q_extentsize(	database->wrapped_bdb_database, 
																					database_type_queue_settings_controller->number_of_pages_for_underlying_data ) ) )	{
		
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"RPDB_DatabaseTypeQueueSettingsController_setNumberOfPagesForUnderlyingData" );
		}
	}
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseTypeQueueSettingsController* RPDB_DatabaseTypeQueueSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

	RPDB_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller_copy	=	RPDB_DatabaseTypeQueueSettingsController_new( database_type_queue_settings_controller->parent_database_type_settings_controller );

	//	Instances and Pointers
	database_type_queue_settings_controller_copy->return_key_data_pairs_in_order	=	database_type_queue_settings_controller->return_key_data_pairs_in_order;
	database_type_queue_settings_controller_copy->number_of_pages_for_underlying_data	=	database_type_queue_settings_controller->number_of_pages_for_underlying_data;

	return database_type_queue_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

void RPDB_DatabaseTypeQueueSettingsController_internal_setFlags(	RPDB_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller )	{
	
	RPDB_Database*			database = database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	database->wrapped_bdb_database->set_flags(	database->wrapped_bdb_database,
												RPDB_DatabaseTypeSettingsController_internal_setFlags( database_type_queue_settings_controller->parent_database_type_settings_controller )
												|	RPDB_DatabaseTypeQueueSettingsController_returnKeyDataPairsInOrder( database_type_queue_settings_controller ) );
}

