/*
 *		RPDB::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseTypeSettingsController.h"

#include "RPDB_Environment.h"
#include "RPDB_ErrorController.h"
#include "RPDB_Database.h"
#include "RPDB_DatabaseTypeBtreeSettingsController.h"
#include "RPDB_DatabaseTypeHashSettingsController.h"
#include "RPDB_DatabaseTypeQueueSettingsController.h"
#include "RPDB_DatabaseTypeRecnoSettingsController.h"

#include "RPDB_DatabaseEncryptionSettingsController.h"
#include "RPDB_DatabaseSettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseTypeSettingsController* RPDB_DatabaseTypeSettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseTypeSettingsController*		database_type_settings_controller = calloc( 1, sizeof( RPDB_DatabaseTypeSettingsController ) );

	database_type_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_type_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseTypeSettingsController_free(	RPDB_DatabaseTypeSettingsController** database_type_settings_controller )	{

	if ( ( *database_type_settings_controller )->btree_settings_controller != NULL )	{
		RPDB_DatabaseTypeBtreeSettingsController_free( & ( ( *database_type_settings_controller )->btree_settings_controller ) );
	}
	if ( ( *database_type_settings_controller )->btree_settings_controller != NULL )	{
		RPDB_DatabaseTypeHashSettingsController_free( & ( ( *database_type_settings_controller )->hash_settings_controller ) );
	}
	if ( ( *database_type_settings_controller )->btree_settings_controller != NULL )	{
		RPDB_DatabaseTypeQueueSettingsController_free( & ( ( *database_type_settings_controller )->queue_settings_controller ) );
	}
	if ( ( *database_type_settings_controller )->btree_settings_controller != NULL )	{
		RPDB_DatabaseTypeRecnoSettingsController_free( & ( ( *database_type_settings_controller )->recno_settings_controller ) );
	}
	
	free( *database_type_settings_controller );
	*database_type_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseTypeSettingsController_parentEnvironment(	RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{
	return database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseTypeSettingsController_parentDatabase(	RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{
	return database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/*********************
*  databaseType  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get_type.html
DBTYPE RPDB_DatabaseTypeSettingsController_databaseType( RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{

	RPDB_Database*	database = database_type_settings_controller->parent_database_settings_controller->parent_database;

	//	We only have a type already if the settings controller is owned by a parent database
	if (	database != NULL
		&&	database->wrapped_bdb_database != NULL
		&&	database->is_open )	{
				
		int	connection_error	= 0;

		if ( ( connection_error = database->wrapped_bdb_database->get_type(	database->wrapped_bdb_database, 
																			&( database_type_settings_controller->default_database_type ) ) ) )	{
																				
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database->parent_database_controller->parent_environment ),
															connection_error, 
															"RPDB_DatabaseType" );
			return RP_TYPE_UNKNOWN;
		}
	}
	
	return database_type_settings_controller->default_database_type;
}

/*****************
*  isBTree  *
*****************/

BOOL RPDB_DatabaseTypeSettingsController_isBTree( RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	if ( database_type_settings_controller->default_database_type == DB_BTREE )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  setToBTree  *
*****************/

void RPDB_DatabaseTypeSettingsController_setTypeToBTree( RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{

	database_type_settings_controller->default_database_type = DB_BTREE;
	
}

/*****************
*  isHash  *
*****************/

BOOL RPDB_DatabaseTypeSettingsController_isHash( RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	if ( database_type_settings_controller->default_database_type == DB_HASH )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  setToHash  *
*****************/

void RPDB_DatabaseTypeSettingsController_setTypeToHash( RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	database_type_settings_controller->default_database_type = DB_HASH;
}

/*****************
*  isRecno  *
*****************/

BOOL RPDB_DatabaseTypeSettingsController_isRecno( RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	if ( database_type_settings_controller->default_database_type == DB_RECNO )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  setToRecno  *
*****************/

void RPDB_DatabaseTypeSettingsController_setTypeToRecno( RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	database_type_settings_controller->default_database_type = DB_RECNO;
}

/*****************
*  isQueue  *
*****************/

BOOL RPDB_DatabaseTypeSettingsController_isQueue( RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	if ( database_type_settings_controller->default_database_type == DB_QUEUE )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  setToQueue  *
*****************/

void RPDB_DatabaseTypeSettingsController_setTypeToQueue( RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	database_type_settings_controller->default_database_type = DB_QUEUE;
}

/*************************
*  btreeController  *
*************************/

RPDB_DatabaseTypeBtreeSettingsController* RPDB_DatabaseTypeSettingsController_btreeController( RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{

	//	If we have a parent database we are a local settings controller, so we only want to set settings for our local type
	if (	database_type_settings_controller->parent_database			!= NULL
		&&	database_type_settings_controller->default_database_type	!= DB_BTREE )	{
		
		RPDB_ErrorController_throwError(	RPDB_Environment_errorController( database_type_settings_controller->parent_database->parent_database_controller->parent_environment ),
											0,
											"RPDB_DatabaseTypeSettingsController_btreeController",
											"Database is not Btree." );
	}
	else if ( database_type_settings_controller->btree_settings_controller == NULL )	{
		
		database_type_settings_controller->btree_settings_controller = RPDB_DatabaseTypeBtreeSettingsController_new( database_type_settings_controller );
	}
	
	return database_type_settings_controller->btree_settings_controller;
}

/*************************
*  hashController  *
*************************/

RPDB_DatabaseTypeHashSettingsController* RPDB_DatabaseTypeSettingsController_hashController( RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	//	If we have a parent database we are a local settings controller, so we only want to set settings for our local type
	if (	database_type_settings_controller->parent_database			!= NULL
		&&	database_type_settings_controller->default_database_type	!= DB_HASH )	{
		
		RPDB_ErrorController_throwError(	RPDB_Environment_errorController( database_type_settings_controller->parent_database->parent_database_controller->parent_environment ),
										 0,
										 "RPDB_DatabaseTypeSettingsController_hashController",
										 "Database is not hash." );
	}
	else if ( database_type_settings_controller->hash_settings_controller == NULL )	{
		
		database_type_settings_controller->hash_settings_controller = RPDB_DatabaseTypeHashSettingsController_new( database_type_settings_controller );
	}
	
	return database_type_settings_controller->hash_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseTypeSettingsController* RPDB_DatabaseTypeSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseTypeSettingsController* database_type_settings_controller )	{

	RPDB_DatabaseTypeSettingsController* database_type_settings_controller_copy	=	RPDB_DatabaseTypeSettingsController_new( database_type_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_type_settings_controller_copy->default_database_type	=	database_type_settings_controller->default_database_type;

	return database_type_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

uint32_t RPDB_DatabaseTypeSettingsController_internal_setFlags(	RPDB_DatabaseTypeSettingsController*		database_type_settings_controller )	{
	
	uint32_t	flags	=	RPDB_DatabaseSettingsController_checksum( database_type_settings_controller->parent_database_settings_controller )
							|	RPDB_DatabaseSettingsController_transactionDurability( database_type_settings_controller->parent_database_settings_controller );
	
	//	only include db encryption flags if not in environment
	//	for now we interpret that as being if there is no database controller or environment
	if (	database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller == NULL
		||	database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment == NULL )	{
		
		flags	|=	RPDB_DatabaseEncryptionSettingsController_encrypted( RPDB_DatabaseSettingsController_encryptionSettingsController( database_type_settings_controller->parent_database_settings_controller ) );
	}
	
	//	we're returning flags used by every type of database - the actual database type settings controller sets the flags on the db
	return flags;
}

