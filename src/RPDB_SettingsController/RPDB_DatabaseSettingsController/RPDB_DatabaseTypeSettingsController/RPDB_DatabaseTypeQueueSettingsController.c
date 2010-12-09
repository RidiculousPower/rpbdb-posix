/*
 *		Rbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeQueueSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseTypeQueueSettingsController.h"

#include "Rbdb_Environment.h"
#include "Rbdb_ErrorController.h"

#include "Rbdb_DatabaseTypeSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_DatabaseTypeQueueSettingsController* Rbdb_DatabaseTypeQueueSettingsController_new( Rbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller )	{

	Rbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseTypeQueueSettingsController ) );

	database_type_queue_settings_controller->parent_database_type_settings_controller = parent_database_type_settings_controller;

	return database_type_queue_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseTypeQueueSettingsController_free(	Rbdb_DatabaseTypeQueueSettingsController** database_type_queue_settings_controller )	{

	free( *database_type_queue_settings_controller );
	*database_type_queue_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseTypeQueueSettingsController_parentEnvironment(	Rbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{
	return database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseTypeQueueSettingsController_parentDatabase(	Rbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{
	return database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/*********************************
*  returnKeyDataPairsInOrder  *
*********************************/

//	DB_INORDER					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL Rbdb_DatabaseTypeQueueSettingsController_returnKeyDataPairsInOrder( Rbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

	if ( database_type_queue_settings_controller->return_key_data_pairs_in_order )	{

		return DB_INORDER;
	}
	return FALSE;
}

	/*****************************************
	*  turnReturnKeyDataPairsInOrderOn  *
	*****************************************/

	void Rbdb_DatabaseTypeQueueSettingsController_turnReturnKeyDataPairsInOrderOn( Rbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

		database_type_queue_settings_controller->return_key_data_pairs_in_order = TRUE;
	}

	/*****************************************
	*  turnReturnKeyDataPairsInOrderOff  *
	*****************************************/

	void Rbdb_DatabaseTypeQueueSettingsController_turnReturnKeyDataPairsInOrderOff( Rbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

		database_type_queue_settings_controller->return_key_data_pairs_in_order = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/*****************************************
*  numberOfPagesForUnderlyingData  *
*****************************************/

//	For Queue Databases		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_q_extentsize.html
uint32_t Rbdb_DatabaseTypeQueueSettingsController_numberOfPagesForUnderlyingData( Rbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

	Rbdb_Database*		database	=	database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int		connection_error	= 0;

	if (		! database_type_queue_settings_controller->number_of_pages_for_underlying_data
			&&	database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
			
		if ( ( connection_error = database->wrapped_bdb_database->get_q_extentsize(	database->wrapped_bdb_database,
																																								&( database_type_queue_settings_controller->number_of_pages_for_underlying_data ) ) ) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"Rbdb_DatabaseTypeQueueSettingsController_numberOfPagesForUnderlyingData" );
		}
	}
	
	return database_type_queue_settings_controller->number_of_pages_for_underlying_data;
}

/*****************************************
*  setNumberOfPagesForUnderlyingData  *
*****************************************/

void Rbdb_DatabaseTypeQueueSettingsController_setNumberOfPagesForUnderlyingData(	Rbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller, 
																					uint32_t										number_of_pages_for_underlying_data )	{
	
	Rbdb_Database*		database = database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	int		connection_error	= 0;
	
	database_type_queue_settings_controller->number_of_pages_for_underlying_data = number_of_pages_for_underlying_data;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->set_q_extentsize(	database->wrapped_bdb_database, 
																					database_type_queue_settings_controller->number_of_pages_for_underlying_data ) ) )	{
		
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"Rbdb_DatabaseTypeQueueSettingsController_setNumberOfPagesForUnderlyingData" );
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
Rbdb_DatabaseTypeQueueSettingsController* Rbdb_DatabaseTypeQueueSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller )	{

	Rbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller_copy	=	Rbdb_DatabaseTypeQueueSettingsController_new( database_type_queue_settings_controller->parent_database_type_settings_controller );

	//	Instances and Pointers
	database_type_queue_settings_controller_copy->return_key_data_pairs_in_order	=	database_type_queue_settings_controller->return_key_data_pairs_in_order;
	database_type_queue_settings_controller_copy->number_of_pages_for_underlying_data	=	database_type_queue_settings_controller->number_of_pages_for_underlying_data;

	return database_type_queue_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

void Rbdb_DatabaseTypeQueueSettingsController_internal_setFlags(	Rbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller )	{
	
	Rbdb_Database*			database = database_type_queue_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	database->wrapped_bdb_database->set_flags(	database->wrapped_bdb_database,
												Rbdb_DatabaseTypeSettingsController_internal_setFlags( database_type_queue_settings_controller->parent_database_type_settings_controller )
												|	Rbdb_DatabaseTypeQueueSettingsController_returnKeyDataPairsInOrder( database_type_queue_settings_controller ) );
}

