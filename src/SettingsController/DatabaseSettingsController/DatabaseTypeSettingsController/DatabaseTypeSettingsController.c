/*
 *		RPbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseTypeSettingsController.h"

#include "Environment.h"
#include "ErrorController.h"
#include "Database.h"
#include "DatabaseTypeBtreeSettingsController.h"
#include "DatabaseTypeHashSettingsController.h"
#include "DatabaseTypeQueueSettingsController.h"
#include "DatabaseTypeRecnoSettingsController.h"

#include "DatabaseEncryptionSettingsController.h"
#include "DatabaseSettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_DatabaseTypeSettingsController* RPbdb_DatabaseTypeSettingsController_new( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_DatabaseTypeSettingsController*		database_type_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseTypeSettingsController ) );

	database_type_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_type_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseTypeSettingsController_free(	RPbdb_DatabaseTypeSettingsController** database_type_settings_controller )	{

	if ( ( *database_type_settings_controller )->btree_settings_controller != NULL )	{
		RPbdb_DatabaseTypeBtreeSettingsController_free( & ( ( *database_type_settings_controller )->btree_settings_controller ) );
	}
	if ( ( *database_type_settings_controller )->btree_settings_controller != NULL )	{
		RPbdb_DatabaseTypeHashSettingsController_free( & ( ( *database_type_settings_controller )->hash_settings_controller ) );
	}
	if ( ( *database_type_settings_controller )->btree_settings_controller != NULL )	{
		RPbdb_DatabaseTypeQueueSettingsController_free( & ( ( *database_type_settings_controller )->queue_settings_controller ) );
	}
	if ( ( *database_type_settings_controller )->btree_settings_controller != NULL )	{
		RPbdb_DatabaseTypeRecnoSettingsController_free( & ( ( *database_type_settings_controller )->recno_settings_controller ) );
	}
	
	free( *database_type_settings_controller );
	*database_type_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseTypeSettingsController_parentEnvironment(	RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	return database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseTypeSettingsController_parentDatabase(	RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	return database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/*********************
*  databaseType  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get_type.html
DBTYPE RPbdb_DatabaseTypeSettingsController_databaseType( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{

	RPbdb_Database*	database = database_type_settings_controller->parent_database_settings_controller->parent_database;

	//	We only have a type already if the settings controller is owned by a parent database
	if (	database != NULL
		&&	database->wrapped_bdb_database != NULL
		&&	database->is_open )	{
				
		int	connection_error	= 0;

		if ( ( connection_error = database->wrapped_bdb_database->get_type(	database->wrapped_bdb_database, 
																			&( database_type_settings_controller->default_database_type ) ) ) )	{
																				
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"DatabaseType" );
			return RP_TYPE_UNKNOWN;
		}
	}
	
	return database_type_settings_controller->default_database_type;
}

/*****************
*  isBTree  *
*****************/

BOOL RPbdb_DatabaseTypeSettingsController_isBTree( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	if ( database_type_settings_controller->default_database_type == DB_BTREE )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  setToBTree  *
*****************/

void RPbdb_DatabaseTypeSettingsController_setTypeToBTree( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{

	database_type_settings_controller->default_database_type = DB_BTREE;
	
}

/*****************
*  isHash  *
*****************/

BOOL RPbdb_DatabaseTypeSettingsController_isHash( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	if ( database_type_settings_controller->default_database_type == DB_HASH )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  setToHash  *
*****************/

void RPbdb_DatabaseTypeSettingsController_setTypeToHash( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	database_type_settings_controller->default_database_type = DB_HASH;
}

/*****************
*  isRecno  *
*****************/

BOOL RPbdb_DatabaseTypeSettingsController_isRecno( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	if ( database_type_settings_controller->default_database_type == DB_RECNO )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  setToRecno  *
*****************/

void RPbdb_DatabaseTypeSettingsController_setTypeToRecno( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	database_type_settings_controller->default_database_type = DB_RECNO;
}

/*****************
*  isQueue  *
*****************/

BOOL RPbdb_DatabaseTypeSettingsController_isQueue( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	if ( database_type_settings_controller->default_database_type == DB_QUEUE )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  setToQueue  *
*****************/

void RPbdb_DatabaseTypeSettingsController_setTypeToQueue( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	database_type_settings_controller->default_database_type = DB_QUEUE;
}

/*************************
*  btreeController  *
*************************/

RPbdb_DatabaseTypeBtreeSettingsController* RPbdb_DatabaseTypeSettingsController_btreeController( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{

	//	If we have a parent database we are a local settings controller, so we only want to set settings for our local type
	if (	database_type_settings_controller->parent_database			!= NULL
		&&	database_type_settings_controller->default_database_type	!= DB_BTREE )	{
		
		RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( database_type_settings_controller->parent_database->parent_database_controller->parent_environment ),
											0,
											"DatabaseTypeSettingsController_btreeController",
											"Database is not Btree." );
	}
	else if ( database_type_settings_controller->btree_settings_controller == NULL )	{
		
		database_type_settings_controller->btree_settings_controller = RPbdb_DatabaseTypeBtreeSettingsController_new( database_type_settings_controller );
	}
	
	return database_type_settings_controller->btree_settings_controller;
}

/*************************
*  hashController  *
*************************/

RPbdb_DatabaseTypeHashSettingsController* RPbdb_DatabaseTypeSettingsController_hashController( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	//	If we have a parent database we are a local settings controller, so we only want to set settings for our local type
	if (	database_type_settings_controller->parent_database			!= NULL
		&&	database_type_settings_controller->default_database_type	!= DB_HASH )	{
		
		RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( database_type_settings_controller->parent_database->parent_database_controller->parent_environment ),
										 0,
										 "DatabaseTypeSettingsController_hashController",
										 "Database is not hash." );
	}
	else if ( database_type_settings_controller->hash_settings_controller == NULL )	{
		
		database_type_settings_controller->hash_settings_controller = RPbdb_DatabaseTypeHashSettingsController_new( database_type_settings_controller );
	}
	
	return database_type_settings_controller->hash_settings_controller;
}

/*************************
*  queueController  *
*************************/

RPbdb_DatabaseTypeQueueSettingsController* RPbdb_DatabaseTypeSettingsController_queueController( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	//	If we have a parent database we are a local settings controller, so we only want to set settings for our local type
	if (	database_type_settings_controller->parent_database			!= NULL
		&&	database_type_settings_controller->default_database_type	!= DB_HASH )	{
		
		RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( database_type_settings_controller->parent_database->parent_database_controller->parent_environment ),
										 0,
										 "DatabaseTypeSettingsController_queueController",
										 "Database is not queue." );
	}
	else if ( database_type_settings_controller->queue_settings_controller == NULL )	{
		
		database_type_settings_controller->queue_settings_controller = RPbdb_DatabaseTypeQueueSettingsController_new( database_type_settings_controller );
	}
	
	return database_type_settings_controller->queue_settings_controller;
}

/*************************
*  recnoController  *
*************************/

RPbdb_DatabaseTypeRecnoSettingsController* RPbdb_DatabaseTypeSettingsController_recnoController( RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	//	If we have a parent database we are a local settings controller, so we only want to set settings for our local type
	if (	database_type_settings_controller->parent_database			!= NULL
		&&	database_type_settings_controller->default_database_type	!= DB_HASH )	{
		
		RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( database_type_settings_controller->parent_database->parent_database_controller->parent_environment ),
										 0,
										 "DatabaseTypeSettingsController_recnoController",
										 "Database is not recno." );
	}
	else if ( database_type_settings_controller->recno_settings_controller == NULL )	{
		
		database_type_settings_controller->recno_settings_controller = RPbdb_DatabaseTypeRecnoSettingsController_new( database_type_settings_controller );
	}
	
	return database_type_settings_controller->recno_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseTypeSettingsController* RPbdb_DatabaseTypeSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{

	RPbdb_DatabaseTypeSettingsController* database_type_settings_controller_copy	=	RPbdb_DatabaseTypeSettingsController_new( database_type_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_type_settings_controller_copy->default_database_type	=	database_type_settings_controller->default_database_type;

	return database_type_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

uint32_t RPbdb_DatabaseTypeSettingsController_internal_setFlags(	RPbdb_DatabaseTypeSettingsController*		database_type_settings_controller )	{
	
	uint32_t	flags	=	RPbdb_DatabaseSettingsController_checksum( database_type_settings_controller->parent_database_settings_controller )
							|	RPbdb_DatabaseSettingsController_transactionDurability( database_type_settings_controller->parent_database_settings_controller );
	
	//	only include db encryption flags if not in environment
	//	for now we interpret that as being if there is no database controller or environment
	if (	database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller == NULL
		||	database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment == NULL )	{
		
		flags	|=	RPbdb_DatabaseEncryptionSettingsController_encrypted( RPbdb_DatabaseSettingsController_encryptionSettingsController( database_type_settings_controller->parent_database_settings_controller ) );
	}
	
	//	we're returning flags used by every type of database - the actual database type settings controller sets the flags on the db
	return flags;
}

