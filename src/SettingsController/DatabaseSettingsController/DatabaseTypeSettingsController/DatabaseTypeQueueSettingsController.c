/*
 *		RPbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeQueueSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseTypeQueueSettingsController.h"

#include "Environment.h"
#include "ErrorController.h"

#include "DatabaseTypeSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_DatabaseTypeQueueSettingsController* RPbdb_DatabaseTypeQueueSettingsController_new( RPbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller )	{

	RPbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseTypeQueueSettingsController ) );

	database_type_queue_settings_controller->parent_database_type_settings_controller = parent_database_type_settings_controller;

	return database_type_queue_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseTypeQueueSettingsController_free(	RPbdb_DatabaseTypeQueueSettingsController** database_type_queue_settings_controller )	{

	free( *database_type_queue_settings_controller );
	*database_type_queue_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseTypeQueueSettingsController_parentEnvironment(	RPbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{
	return database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseTypeQueueSettingsController_parentDatabase(	RPbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{
	return database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/*********************************
*  returnKeyDataPairsInOrder  *
*********************************/

//	DB_INORDER					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPbdb_DatabaseTypeQueueSettingsController_returnKeyDataPairsInOrder( RPbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

	if ( database_type_queue_settings_controller->return_key_data_pairs_in_order )	{

		return DB_INORDER;
	}
	return FALSE;
}

	/*****************************************
	*  turnReturnKeyDataPairsInOrderOn  *
	*****************************************/

	void RPbdb_DatabaseTypeQueueSettingsController_turnReturnKeyDataPairsInOrderOn( RPbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

		database_type_queue_settings_controller->return_key_data_pairs_in_order = TRUE;
	}

	/*****************************************
	*  turnReturnKeyDataPairsInOrderOff  *
	*****************************************/

	void RPbdb_DatabaseTypeQueueSettingsController_turnReturnKeyDataPairsInOrderOff( RPbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

		database_type_queue_settings_controller->return_key_data_pairs_in_order = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/*****************************************
*  numberOfPagesForUnderlyingData  *
*****************************************/

//	For Queue Databases		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_q_extentsize.html
uint32_t RPbdb_DatabaseTypeQueueSettingsController_numberOfPagesForUnderlyingData( RPbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

	RPbdb_Database*		database	=	database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int		connection_error	= 0;

	if (		! database_type_queue_settings_controller->number_of_pages_for_underlying_data
			&&	database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
			
		if ( ( connection_error = database->wrapped_bdb_database->get_q_extentsize(	database->wrapped_bdb_database,
																																								&( database_type_queue_settings_controller->number_of_pages_for_underlying_data ) ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"DatabaseTypeQueueSettingsController_numberOfPagesForUnderlyingData" );
		}
	}
	
	return database_type_queue_settings_controller->number_of_pages_for_underlying_data;
}

/*****************************************
*  setNumberOfPagesForUnderlyingData  *
*****************************************/

void RPbdb_DatabaseTypeQueueSettingsController_setNumberOfPagesForUnderlyingData(	RPbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller, 
																					uint32_t										number_of_pages_for_underlying_data )	{
	
	RPbdb_Database*		database = database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	int		connection_error	= 0;
	
	database_type_queue_settings_controller->number_of_pages_for_underlying_data = number_of_pages_for_underlying_data;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->set_q_extentsize(	database->wrapped_bdb_database, 
																					database_type_queue_settings_controller->number_of_pages_for_underlying_data ) ) )	{
		
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"DatabaseTypeQueueSettingsController_setNumberOfPagesForUnderlyingData" );
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
RPbdb_DatabaseTypeQueueSettingsController* RPbdb_DatabaseTypeQueueSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

	RPbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller_copy	=	RPbdb_DatabaseTypeQueueSettingsController_new( database_type_queue_settings_controller->parent_database_type_settings_controller );

	//	Instances and Pointers
	database_type_queue_settings_controller_copy->return_key_data_pairs_in_order	=	database_type_queue_settings_controller->return_key_data_pairs_in_order;
	database_type_queue_settings_controller_copy->number_of_pages_for_underlying_data	=	database_type_queue_settings_controller->number_of_pages_for_underlying_data;

	return database_type_queue_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

void RPbdb_DatabaseTypeQueueSettingsController_internal_setFlags(	RPbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller )	{
	
	RPbdb_Database*			database = database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	database->wrapped_bdb_database->set_flags(	database->wrapped_bdb_database,
												RPbdb_DatabaseTypeSettingsController_internal_setFlags( database_type_queue_settings_controller->parent_database_type_settings_controller )
												|	RPbdb_DatabaseTypeQueueSettingsController_returnKeyDataPairsInOrder( database_type_queue_settings_controller ) );
}

