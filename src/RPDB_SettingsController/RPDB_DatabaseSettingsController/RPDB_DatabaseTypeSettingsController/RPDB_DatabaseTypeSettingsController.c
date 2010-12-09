/*
 *		Rbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseTypeSettingsController.h"

#include "Rbdb_Environment.h"
#include "Rbdb_ErrorController.h"
#include "Rbdb_Database.h"
#include "Rbdb_DatabaseTypeBtreeSettingsController.h"
#include "Rbdb_DatabaseTypeHashSettingsController.h"
#include "Rbdb_DatabaseTypeQueueSettingsController.h"
#include "Rbdb_DatabaseTypeRecnoSettingsController.h"

#include "Rbdb_DatabaseEncryptionSettingsController.h"
#include "Rbdb_DatabaseSettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_DatabaseTypeSettingsController* Rbdb_DatabaseTypeSettingsController_new( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_DatabaseTypeSettingsController*		database_type_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseTypeSettingsController ) );

	database_type_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_type_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseTypeSettingsController_free(	Rbdb_DatabaseTypeSettingsController** database_type_settings_controller )	{

	if ( ( *database_type_settings_controller )->btree_settings_controller != NULL )	{
		Rbdb_DatabaseTypeBtreeSettingsController_free( & ( ( *database_type_settings_controller )->btree_settings_controller ) );
	}
	if ( ( *database_type_settings_controller )->btree_settings_controller != NULL )	{
		Rbdb_DatabaseTypeHashSettingsController_free( & ( ( *database_type_settings_controller )->hash_settings_controller ) );
	}
	if ( ( *database_type_settings_controller )->btree_settings_controller != NULL )	{
		Rbdb_DatabaseTypeQueueSettingsController_free( & ( ( *database_type_settings_controller )->queue_settings_controller ) );
	}
	if ( ( *database_type_settings_controller )->btree_settings_controller != NULL )	{
		Rbdb_DatabaseTypeRecnoSettingsController_free( & ( ( *database_type_settings_controller )->recno_settings_controller ) );
	}
	
	free( *database_type_settings_controller );
	*database_type_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseTypeSettingsController_parentEnvironment(	Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	return database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseTypeSettingsController_parentDatabase(	Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	return database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Controllers
*******************************************************************************************************************************************************************************************/

/*********************
*  databaseType  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_get_type.html
DBTYPE Rbdb_DatabaseTypeSettingsController_databaseType( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{

	Rbdb_Database*	database = database_type_settings_controller->parent_database_settings_controller->parent_database;

	//	We only have a type already if the settings controller is owned by a parent database
	if (	database != NULL
		&&	database->wrapped_bdb_database != NULL
		&&	database->is_open )	{
				
		int	connection_error	= 0;

		if ( ( connection_error = database->wrapped_bdb_database->get_type(	database->wrapped_bdb_database, 
																			&( database_type_settings_controller->default_database_type ) ) ) )	{
																				
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"Rbdb_DatabaseType" );
			return RP_TYPE_UNKNOWN;
		}
	}
	
	return database_type_settings_controller->default_database_type;
}

/*****************
*  isBTree  *
*****************/

BOOL Rbdb_DatabaseTypeSettingsController_isBTree( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	if ( database_type_settings_controller->default_database_type == DB_BTREE )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  setToBTree  *
*****************/

void Rbdb_DatabaseTypeSettingsController_setTypeToBTree( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{

	database_type_settings_controller->default_database_type = DB_BTREE;
	
}

/*****************
*  isHash  *
*****************/

BOOL Rbdb_DatabaseTypeSettingsController_isHash( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	if ( database_type_settings_controller->default_database_type == DB_HASH )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  setToHash  *
*****************/

void Rbdb_DatabaseTypeSettingsController_setTypeToHash( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	database_type_settings_controller->default_database_type = DB_HASH;
}

/*****************
*  isRecno  *
*****************/

BOOL Rbdb_DatabaseTypeSettingsController_isRecno( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	if ( database_type_settings_controller->default_database_type == DB_RECNO )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  setToRecno  *
*****************/

void Rbdb_DatabaseTypeSettingsController_setTypeToRecno( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	database_type_settings_controller->default_database_type = DB_RECNO;
}

/*****************
*  isQueue  *
*****************/

BOOL Rbdb_DatabaseTypeSettingsController_isQueue( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	if ( database_type_settings_controller->default_database_type == DB_QUEUE )	{
		return TRUE;
	}
	return FALSE;
}

/*****************
*  setToQueue  *
*****************/

void Rbdb_DatabaseTypeSettingsController_setTypeToQueue( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	database_type_settings_controller->default_database_type = DB_QUEUE;
}

/*************************
*  btreeController  *
*************************/

Rbdb_DatabaseTypeBtreeSettingsController* Rbdb_DatabaseTypeSettingsController_btreeController( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{

	//	If we have a parent database we are a local settings controller, so we only want to set settings for our local type
	if (	database_type_settings_controller->parent_database			!= NULL
		&&	database_type_settings_controller->default_database_type	!= DB_BTREE )	{
		
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( database_type_settings_controller->parent_database->parent_database_controller->parent_environment ),
											0,
											"Rbdb_DatabaseTypeSettingsController_btreeController",
											"Database is not Btree." );
	}
	else if ( database_type_settings_controller->btree_settings_controller == NULL )	{
		
		database_type_settings_controller->btree_settings_controller = Rbdb_DatabaseTypeBtreeSettingsController_new( database_type_settings_controller );
	}
	
	return database_type_settings_controller->btree_settings_controller;
}

/*************************
*  hashController  *
*************************/

Rbdb_DatabaseTypeHashSettingsController* Rbdb_DatabaseTypeSettingsController_hashController( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	//	If we have a parent database we are a local settings controller, so we only want to set settings for our local type
	if (	database_type_settings_controller->parent_database			!= NULL
		&&	database_type_settings_controller->default_database_type	!= DB_HASH )	{
		
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( database_type_settings_controller->parent_database->parent_database_controller->parent_environment ),
										 0,
										 "Rbdb_DatabaseTypeSettingsController_hashController",
										 "Database is not hash." );
	}
	else if ( database_type_settings_controller->hash_settings_controller == NULL )	{
		
		database_type_settings_controller->hash_settings_controller = Rbdb_DatabaseTypeHashSettingsController_new( database_type_settings_controller );
	}
	
	return database_type_settings_controller->hash_settings_controller;
}

/*************************
*  queueController  *
*************************/

Rbdb_DatabaseTypeQueueSettingsController* Rbdb_DatabaseTypeSettingsController_queueController( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	//	If we have a parent database we are a local settings controller, so we only want to set settings for our local type
	if (	database_type_settings_controller->parent_database			!= NULL
		&&	database_type_settings_controller->default_database_type	!= DB_HASH )	{
		
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( database_type_settings_controller->parent_database->parent_database_controller->parent_environment ),
										 0,
										 "Rbdb_DatabaseTypeSettingsController_queueController",
										 "Database is not queue." );
	}
	else if ( database_type_settings_controller->queue_settings_controller == NULL )	{
		
		database_type_settings_controller->queue_settings_controller = Rbdb_DatabaseTypeQueueSettingsController_new( database_type_settings_controller );
	}
	
	return database_type_settings_controller->queue_settings_controller;
}

/*************************
*  recnoController  *
*************************/

Rbdb_DatabaseTypeRecnoSettingsController* Rbdb_DatabaseTypeSettingsController_recnoController( Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{
	
	//	If we have a parent database we are a local settings controller, so we only want to set settings for our local type
	if (	database_type_settings_controller->parent_database			!= NULL
		&&	database_type_settings_controller->default_database_type	!= DB_HASH )	{
		
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( database_type_settings_controller->parent_database->parent_database_controller->parent_environment ),
										 0,
										 "Rbdb_DatabaseTypeSettingsController_recnoController",
										 "Database is not recno." );
	}
	else if ( database_type_settings_controller->recno_settings_controller == NULL )	{
		
		database_type_settings_controller->recno_settings_controller = Rbdb_DatabaseTypeRecnoSettingsController_new( database_type_settings_controller );
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
Rbdb_DatabaseTypeSettingsController* Rbdb_DatabaseTypeSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseTypeSettingsController* database_type_settings_controller )	{

	Rbdb_DatabaseTypeSettingsController* database_type_settings_controller_copy	=	Rbdb_DatabaseTypeSettingsController_new( database_type_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_type_settings_controller_copy->default_database_type	=	database_type_settings_controller->default_database_type;

	return database_type_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

uint32_t Rbdb_DatabaseTypeSettingsController_internal_setFlags(	Rbdb_DatabaseTypeSettingsController*		database_type_settings_controller )	{
	
	uint32_t	flags	=	Rbdb_DatabaseSettingsController_checksum( database_type_settings_controller->parent_database_settings_controller )
							|	Rbdb_DatabaseSettingsController_transactionDurability( database_type_settings_controller->parent_database_settings_controller );
	
	//	only include db encryption flags if not in environment
	//	for now we interpret that as being if there is no database controller or environment
	if (	database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller == NULL
		||	database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment == NULL )	{
		
		flags	|=	Rbdb_DatabaseEncryptionSettingsController_encrypted( Rbdb_DatabaseSettingsController_encryptionSettingsController( database_type_settings_controller->parent_database_settings_controller ) );
	}
	
	//	we're returning flags used by every type of database - the actual database type settings controller sets the flags on the db
	return flags;
}

