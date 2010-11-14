/*
 *		RPDB::Database::DatabaseSettingsController::DatabaseSettingsEncryptionController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseEncryptionSettingsController.h"

#include "RPDB_Environment.h"
#include "RPDB_ErrorController.h"

#include "RPDB_DatabaseEncryptionSettingsController_internal.h"
#include "RPDB_DatabaseRecordReadWriteSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_DatabaseEncryptionSettingsController* RPDB_DatabaseEncryptionSettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseEncryptionSettingsController*		database_encryption_settings_controller = calloc( 1, sizeof( RPDB_DatabaseEncryptionSettingsController ) );

	database_encryption_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_encryption_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseEncryptionSettingsController_free(	RPDB_DatabaseEncryptionSettingsController** database_encryption_settings_controller )	{

	free( *database_encryption_settings_controller );
	*database_encryption_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseEncryptionSettingsController_parentEnvironment(	RPDB_DatabaseEncryptionSettingsController* database_encryption_settings_controller )	{
	return database_encryption_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseEncryptionSettingsController_parentDatabase(	RPDB_DatabaseEncryptionSettingsController* database_encryption_settings_controller )	{
	return database_encryption_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************
*  encrypted  *
*****************/

//	DB_ENCRYPT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_fileid_reset.html
//	DB_ENCRYPT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
uint32_t RPDB_DatabaseEncryptionSettingsController_encrypted( RPDB_DatabaseEncryptionSettingsController* database_encryption_settings_controller )	{
	
	RPDB_Database*		database	=	database_encryption_settings_controller->parent_database_settings_controller->parent_database;
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
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database->parent_database_controller->parent_environment ), 
															connection_error, 
															"RPDB_DatabaseEncryptionSettingsController_containsEncryption" );			
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
	void RPDB_DatabaseEncryptionSettingsController_turnEncryptionOn(	RPDB_DatabaseEncryptionSettingsController*		database_encryption_settings_controller,
																																		char*											encryption_password )	{

		RPDB_Database*			database	= database_encryption_settings_controller->parent_database_settings_controller->parent_database;
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
		
			RPDB_ErrorController_internal_throwBDBError( RPDB_Environment_errorController( database_encryption_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ), 
																connection_error, 
																"RPDB_DatabaseEncryptionSettingsController_turnEncryptionOn" );
			return;
		}
	
		database_encryption_settings_controller->encrypted = TRUE;
	}

	/*************************
	*  turnEncryptionOff  *
	*************************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_encrypt.html
	void RPDB_DatabaseEncryptionSettingsController_turnEncryptionOff(	RPDB_DatabaseEncryptionSettingsController*		database_encryption_settings_controller, 
																		char*											encryption_password )	{

		RPDB_Database*			database	= database_encryption_settings_controller->parent_database_settings_controller->parent_database;
		int			connection_error	= 0;

		if (		database != NULL
				&&	database->wrapped_bdb_database != NULL )	{
			if ( ( connection_error = database->wrapped_bdb_database->set_encrypt( database->wrapped_bdb_database, encryption_password, FALSE ) ) ) {
				
				RPDB_ErrorController_internal_throwBDBError( RPDB_Environment_errorController( database_encryption_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ), 
															 connection_error, 
															 "RPDB_DatabaseEncryptionSettingsController_turnEncryptionOff" );
				return;
			}
		}

		database_encryption_settings_controller->encrypted = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseEncryptionSettingsController* RPDB_DatabaseEncryptionSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseEncryptionSettingsController* database_encryption_settings_controller )	{

	RPDB_DatabaseEncryptionSettingsController* database_encryption_settings_controller_copy	=	RPDB_DatabaseEncryptionSettingsController_new( database_encryption_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_encryption_settings_controller_copy->encrypted	=	database_encryption_settings_controller->encrypted;

	return database_encryption_settings_controller_copy;
}

