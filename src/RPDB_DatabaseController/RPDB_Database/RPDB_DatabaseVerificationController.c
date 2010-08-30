/*
 *		RPDB::DatabaseController::Database::DatabaseVerificationController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseVerificationController.h"

#include "RPDB_Database.h"

#include "RPDB_Environment.h"

#include "RPDB_ErrorController.h"

#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_DatabaseVerificationSettingsController_internal.h"
#include "RPDB_DatabaseVerificationSettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseVerificationController* RPDB_DatabaseVerificationController_new( RPDB_Database* database )	{

	RPDB_DatabaseVerificationController*		database_verification_controller = calloc( 1, sizeof( RPDB_DatabaseVerificationController ) );

	database_verification_controller->parent_database = database;

	return database_verification_controller;
}



/***************************
*  free  *
***************************/
void RPDB_DatabaseVerificationController_free(	RPDB_DatabaseVerificationController** database_verification_controller )	{
	//	Make sure file is open so we don't close a closed file.
	if ( ( *database_verification_controller )->file_is_open )	{
		fclose( ( *database_verification_controller )->file );
		( *database_verification_controller )->file_is_open	=	FALSE;
		( *database_verification_controller )->file	=	NULL;
	}

	free( *database_verification_controller );
	*database_verification_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_DatabaseVerificationSettingsController* RPDB_DatabaseVerificationController_settingsController(	RPDB_DatabaseVerificationController* database_verification_controller )	{
	return database_verification_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseVerificationController_parentEnvironment(	RPDB_DatabaseVerificationController* database_verification_controller )	{
	return database_verification_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseVerificationController_parentDatabase(	RPDB_DatabaseVerificationController* database_verification_controller )	{
	return database_verification_controller->parent_database;
}

/****************
*  verify  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
RPDB_Database* RPDB_DatabaseVerificationController_verifyDatabase( RPDB_DatabaseVerificationController* database_verification_controller )	{

	int			opened_file_locally = FALSE;
	int			connection_error	= 0;
	
	RPDB_Database*			database = database_verification_controller->parent_database;

	//	If we have a file path but no file, open the file in the local scope and close it when we're done
	if ( !	database_verification_controller->file 
		&&	database_verification_controller->file_path )	{
		
		//	So we know if we should close it later
		opened_file_locally = TRUE;
		
		database_verification_controller->file = fopen( database_verification_controller->file_path, "w");

		if ( database_verification_controller->file == NULL )	{
			RPDB_ErrorController_throwError(	RPDB_Environment_errorController( database_verification_controller->parent_database->parent_database_controller->parent_environment ),
											-1,
											"RPDB_DatabaseVerificationController_verify",
											"Could not open file at path." );
			return NULL;
		}
	}

	if ( ( connection_error = database->wrapped_bdb_database->verify(	database->wrapped_bdb_database,
																		database->filename, 
																		database->name, 
																		database_verification_controller->file, 
																		RPDB_DatabaseVerificationSettingsController_internal_verifyFlags( 
																			RPDB_DatabaseSettingsController_verificationSettingsController(
																				RPDB_Database_settingsController( database ) ) ) ) ) ) {
		
		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database->parent_database_controller->parent_environment ),
												connection_error, 
												"RPDB_DatabaseVerificationController_verify" );
		return NULL;
	}


	//	If we opened the file locally we should close it too
	if ( opened_file_locally )	{
		fclose( database_verification_controller->file );
	}

	//	If we verified the database without ordered check, set the flag so we can do ordered check
	if ( RPDB_DatabaseVerificationSettingsController_skipOrderCheck( RPDB_DatabaseVerificationController_settingsController( database_verification_controller  ) ) )	{
		
		RPDB_DatabaseVerificationSettingsController_internal_hasDoneUnorderedCheck( 
			RPDB_DatabaseVerificationController_settingsController( database_verification_controller  ), TRUE );
	}
	//	And if we complete an ordered check, reset our flag (no reason to do it twice in a row unless we start from the beginning). 
	else if ( RPDB_DatabaseVerificationSettingsController_onlyOrderCheck( RPDB_DatabaseVerificationController_settingsController( database_verification_controller  ) ) )	{
		
		RPDB_DatabaseVerificationSettingsController_internal_hasDoneUnorderedCheck( 
			RPDB_DatabaseVerificationController_settingsController( database_verification_controller  ), FALSE );
	}
	
	return database;		
}

