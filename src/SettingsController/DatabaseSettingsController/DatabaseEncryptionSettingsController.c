/*
 *		RPbdb::Database::DatabaseSettingsController::DatabaseSettingsEncryptionController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseEncryptionSettingsController.h"

#include "Environment.h"
#include "ErrorController.h"

#include "DatabaseEncryptionSettingsController_internal.h"
#include "DatabaseRecordReadWriteSettingsController_internal.h"
	
#include <string.h>
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPbdb_DatabaseEncryptionSettingsController* RPbdb_DatabaseEncryptionSettingsController_new( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseEncryptionSettingsController ) );

	database_encryption_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_encryption_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseEncryptionSettingsController_free(	RPbdb_DatabaseEncryptionSettingsController** database_encryption_settings_controller )	{

	free( *database_encryption_settings_controller );
	*database_encryption_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseEncryptionSettingsController_parentEnvironment(	RPbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller )	{
	return database_encryption_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseEncryptionSettingsController_parentDatabase(	RPbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller )	{
	return database_encryption_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************
*  encrypted  *
*****************/

//	DB_ENCRYPT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_fileid_reset.html
//	DB_ENCRYPT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
uint32_t RPbdb_DatabaseEncryptionSettingsController_encrypted( RPbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller )	{
	
	RPbdb_Database*		database	=	database_encryption_settings_controller->parent_database_settings_controller->parent_database;
	uint32_t		flags;
	int				connection_error	= 0;

	if ( database_encryption_settings_controller->encrypted == TRUE )	{
		return DB_ENCRYPT;
	}
	else if (		database != NULL
					&&	database->wrapped_bdb_database != NULL )	{

		connection_error = database->wrapped_bdb_database->get_encrypt_flags(	database->wrapped_bdb_database, 
																				& flags );

		if ( connection_error )	{
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ), 
															connection_error, 
															"DatabaseEncryptionSettingsController_containsEncryption" );			
		}

		if ( flags == DB_ENCRYPT )	{
			database_encryption_settings_controller->encrypted = TRUE;
			return DB_ENCRYPT;
		}
	}
	return FALSE;
}

	/*************************
	*  turnEncryptionOn  *
	*************************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_encrypt.html
	void RPbdb_DatabaseEncryptionSettingsController_turnEncryptionOn(	RPbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller,
																																		char*											encryption_password )	{

		RPbdb_Database*			database	= database_encryption_settings_controller->parent_database_settings_controller->parent_database;
		int			connection_error	= 0;
		
		database_encryption_settings_controller->password	=	encryption_password;
	
		if (		database != NULL
				&&	database->wrapped_bdb_database != NULL )	{

			connection_error = database->wrapped_bdb_database->set_encrypt(	database->wrapped_bdb_database, 
																																			encryption_password, 
																																			DB_ENCRYPT_AES );
		}
		
		//	FIX - do we also need to call set_flags here? i think so, to turn DB_ENCRYPT on
		//	this can only be done when the database isn't yet open
		//	also only when database isn't in an environment

		if ( connection_error ) {
		
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_encryption_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ), 
																										connection_error, 
																										"DatabaseEncryptionSettingsController_turnEncryptionOn" );
			return;
		}
	
		database_encryption_settings_controller->encrypted = TRUE;
	}

	/*************************
	*  turnEncryptionOff  *
	*************************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_encrypt.html
	void RPbdb_DatabaseEncryptionSettingsController_turnEncryptionOff(	RPbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller, 
																																		char*											encryption_password )	{

		RPbdb_Database*			database	= database_encryption_settings_controller->parent_database_settings_controller->parent_database;

		if (		database != NULL
				&&	database->wrapped_bdb_database != NULL )	{

			int		connection_error	= 0;
			if ( ( connection_error = database->wrapped_bdb_database->set_encrypt(	database->wrapped_bdb_database, 
																																							encryption_password, 
																																							FALSE ) ) ) {
				
				RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database->parent_database_controller->parent_environment ), 
																											connection_error, 
																											"DatabaseEncryptionSettingsController_turnEncryptionOff" );
				return;
			}
		}
		
		if ( strcmp( encryption_password, database_encryption_settings_controller->password ) == 0 )	{
			database_encryption_settings_controller->encrypted = FALSE;
		}
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseEncryptionSettingsController* RPbdb_DatabaseEncryptionSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller )	{

	RPbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller_copy	=	RPbdb_DatabaseEncryptionSettingsController_new( database_encryption_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_encryption_settings_controller_copy->encrypted	=	database_encryption_settings_controller->encrypted;

	return database_encryption_settings_controller_copy;
}

