/*
 *		Rbdb::Database::DatabaseSettingsController::DatabaseSettingsEncryptionController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseEncryptionSettingsController.h"

#include "Rbdb_Environment.h"
#include "Rbdb_ErrorController.h"

#include "Rbdb_DatabaseEncryptionSettingsController_internal.h"
#include "Rbdb_DatabaseRecordReadWriteSettingsController_internal.h"
	
#include <string.h>
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
Rbdb_DatabaseEncryptionSettingsController* Rbdb_DatabaseEncryptionSettingsController_new( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseEncryptionSettingsController ) );

	database_encryption_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_encryption_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseEncryptionSettingsController_free(	Rbdb_DatabaseEncryptionSettingsController** database_encryption_settings_controller )	{

	free( *database_encryption_settings_controller );
	*database_encryption_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseEncryptionSettingsController_parentEnvironment(	Rbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller )	{
	return database_encryption_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseEncryptionSettingsController_parentDatabase(	Rbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller )	{
	return database_encryption_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************
*  encrypted  *
*****************/

//	DB_ENCRYPT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_fileid_reset.html
//	DB_ENCRYPT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
uint32_t Rbdb_DatabaseEncryptionSettingsController_encrypted( Rbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller )	{
	
	Rbdb_Database*		database	=	database_encryption_settings_controller->parent_database_settings_controller->parent_database;
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
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database->parent_database_controller->parent_environment ), 
															connection_error, 
															"Rbdb_DatabaseEncryptionSettingsController_containsEncryption" );			
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
	void Rbdb_DatabaseEncryptionSettingsController_turnEncryptionOn(	Rbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller,
																																		char*											encryption_password )	{

		Rbdb_Database*			database	= database_encryption_settings_controller->parent_database_settings_controller->parent_database;
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
		
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_encryption_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ), 
																										connection_error, 
																										"Rbdb_DatabaseEncryptionSettingsController_turnEncryptionOn" );
			return;
		}
	
		database_encryption_settings_controller->encrypted = TRUE;
	}

	/*************************
	*  turnEncryptionOff  *
	*************************/

	//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_encrypt.html
	void Rbdb_DatabaseEncryptionSettingsController_turnEncryptionOff(	Rbdb_DatabaseEncryptionSettingsController*		database_encryption_settings_controller, 
																																		char*											encryption_password )	{

		Rbdb_Database*			database	= database_encryption_settings_controller->parent_database_settings_controller->parent_database;

		if (		database != NULL
				&&	database->wrapped_bdb_database != NULL )	{

			int		connection_error	= 0;
			if ( ( connection_error = database->wrapped_bdb_database->set_encrypt(	database->wrapped_bdb_database, 
																																							encryption_password, 
																																							FALSE ) ) ) {
				
				Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database->parent_database_controller->parent_environment ), 
																											connection_error, 
																											"Rbdb_DatabaseEncryptionSettingsController_turnEncryptionOff" );
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
Rbdb_DatabaseEncryptionSettingsController* Rbdb_DatabaseEncryptionSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller )	{

	Rbdb_DatabaseEncryptionSettingsController* database_encryption_settings_controller_copy	=	Rbdb_DatabaseEncryptionSettingsController_new( database_encryption_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_encryption_settings_controller_copy->encrypted	=	database_encryption_settings_controller->encrypted;

	return database_encryption_settings_controller_copy;
}

