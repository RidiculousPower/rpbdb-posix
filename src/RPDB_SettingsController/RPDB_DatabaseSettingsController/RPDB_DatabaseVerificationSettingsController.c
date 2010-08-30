/*
 *		RPDB::Database::DatabaseVerificationController::DatabaseVerificationSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseVerificationSettingsController.h"

#include "RPDB_ErrorController.h"
#include "RPDB_Environment.h"

#include "RPDB_DatabaseVerificationSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseVerificationSettingsController* RPDB_DatabaseVerificationSettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller = calloc( 1, sizeof( RPDB_DatabaseVerificationSettingsController ) );

	database_verification_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_verification_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseVerificationSettingsController_free(	RPDB_DatabaseVerificationSettingsController** database_verification_settings_controller )	{

	//	Make sure file is open so we don't close a closed file.
	if ( ( *database_verification_settings_controller )->file_is_open )	{

		fclose( ( *database_verification_settings_controller )->file );
		( *database_verification_settings_controller )->file_is_open	=	FALSE;
		( *database_verification_settings_controller )->file			=	NULL;
	}

	free( *database_verification_settings_controller );
	*database_verification_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseVerificationSettingsController_parentEnvironment(	RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
	return database_verification_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseVerificationSettingsController_parentDatabase(	RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
	return database_verification_settings_controller->parent_database_settings_controller->parent_database;
}

/*************
*  file  *
*************/

FILE* RPDB_DatabaseVerificationSettingsController_file(	RPDB_DatabaseVerificationSettingsController*	database_verification_settings_controller )	{
	
	return database_verification_settings_controller->file;
}

/*****************
*  setFile  *
*****************/

void RPDB_DatabaseVerificationSettingsController_setFile(	RPDB_DatabaseVerificationSettingsController*	database_verification_settings_controller, 
															FILE*											data_output_file )	{
	
	database_verification_settings_controller->file = data_output_file;
}

/*****************
*  filePath  *
*****************/

char* RPDB_DatabaseVerificationSettingsController_filePath(	RPDB_DatabaseVerificationSettingsController*	database_verification_settings_controller )	{
	
	return database_verification_settings_controller->file_path;
}

/*********************
*  setFilePath  *
*********************/

void RPDB_DatabaseVerificationSettingsController_setFilePath(	RPDB_DatabaseVerificationSettingsController*	database_verification_settings_controller, 
																char*											data_output_file_path )	{
	
	database_verification_settings_controller->file_path = data_output_file_path;
}

/**********************************
*  aggressiveKeyDataPairDump  *
**********************************/

//	DB_AGGRESSIVE						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
BOOL RPDB_DatabaseVerificationSettingsController_aggressiveKeyDataPairDump( RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	if ( database_verification_settings_controller->aggressive_key_data_pair_dump )	{
		return DB_AGGRESSIVE;
	}
	return FALSE;
}

	/******************************************
	*  turnAggressiveKeyDataPairDumpOn  *
	******************************************/

	void RPDB_DatabaseVerificationSettingsController_turnAggressiveKeyDataPairDumpOn( RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->aggressive_key_data_pair_dump = TRUE;
	}

	/******************************************
	*  turnAggressiveKeyDataPairDumpOff  *
	******************************************/

	void RPDB_DatabaseVerificationSettingsController_turnAggressiveKeyDataPairDumpOff( RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->aggressive_key_data_pair_dump = FALSE;
	}

/******************************
*  printableCharacters  *
******************************/

//	DB_PRINTABLE						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
BOOL RPDB_DatabaseVerificationSettingsController_printableCharacters( RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	if ( database_verification_settings_controller->printable_characters )	{
		return DB_PRINTABLE;
	}
	return FALSE;
}

	/**********************************
	*  turnPrintableCharactersOn  *
	**********************************/

	void RPDB_DatabaseVerificationSettingsController_turnPrintableCharactersOn( RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->printable_characters = TRUE;
	}

	/**********************************
	*  turnPrintableCharactersOff  *
	**********************************/

	void RPDB_DatabaseVerificationSettingsController_turnPrintableCharactersOff( RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->printable_characters = FALSE;
	}

/**********************
*  skipOrderCheck  *
**********************/

//	DB_NOORDERCHK						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
BOOL RPDB_DatabaseVerificationSettingsController_skipOrderCheck( RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	if ( database_verification_settings_controller->skip_order_checking )	{
		return DB_NOORDERCHK;
	}
	return FALSE;
}

	/******************************
	*  turnSkipOrderCheckOn  *
	******************************/

	void RPDB_DatabaseVerificationSettingsController_turnSkipOrderCheckOn( RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->skip_order_checking = TRUE;

		//	If we are skipping order check then we aren't doing only an order check (although next we will)
		RPDB_DatabaseVerificationSettingsController_turnOnlyOrderCheckOff( database_verification_settings_controller );
	}

	/******************************
	*  turnSkipOrderCheckOff  *
	******************************/

	void RPDB_DatabaseVerificationSettingsController_turnSkipOrderCheckOff( RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->skip_order_checking = FALSE;
	}

/**********************
*  onlyOrderCheck  *
**********************/

//	DB_NOORDERCHK						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
BOOL RPDB_DatabaseVerificationSettingsController_onlyOrderCheck( RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	//	Assumes we have already done a check without order checking
	if ( database_verification_settings_controller->only_order_check )	{
		return DB_ORDERCHKONLY;
	}
	return FALSE;
}

	/******************************
	*  turnOnlyOrderCheckOn  *
	******************************/

	void RPDB_DatabaseVerificationSettingsController_turnOnlyOrderCheckOn(	RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->only_order_check = TRUE;
	
		//	If we haven't already done an unordered check, don't do an order check unless we are explicitly forcing it. 
		if (	! database_verification_settings_controller->force_order_check 
			&&	! database_verification_settings_controller->has_done_unordered_check )	{
		
			RPDB_ErrorController_throwError(	
				RPDB_Environment_errorController(	database_verification_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
										-1,
										"RPDB_DatabaseVerificationSettingsController_onlyOrderCheck",
										"Must first perform check while skipping order or force ordered check explicitly (may cause corruption)." );
		}
	
		//	Skipping order check can't also be true
		RPDB_DatabaseVerificationSettingsController_turnSkipOrderCheckOff( database_verification_settings_controller );
	}

	/******************************
	*  turnOnlyOrderCheckOff  *
	******************************/

	void RPDB_DatabaseVerificationSettingsController_turnOnlyOrderCheckOff( RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
	
		database_verification_settings_controller->only_order_check = FALSE;
	}

/**************************
*  forceOrderCheck  *
**************************/

BOOL RPDB_DatabaseVerificationSettingsController_forceOrderCheck(	RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	return database_verification_settings_controller->force_order_check;
}

	/******************************
	*  turnForceOrderCheckOn  *
	******************************/

	void RPDB_DatabaseVerificationSettingsController_turnForceOrderCheckOn(	RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
		database_verification_settings_controller->force_order_check = TRUE;
	}

	/******************************
	*  turnForceOrderCheckOff  *
	******************************/

	void RPDB_DatabaseVerificationSettingsController_turnForceOrderCheckOff(	RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
		database_verification_settings_controller->force_order_check = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************
*  hasDoneUnorderedCheck  *
*******************************/
	
void RPDB_DatabaseVerificationSettingsController_internal_hasDoneUnorderedCheck( 	RPDB_DatabaseVerificationSettingsController*	database_verification_settings_controller, 
																					int												on_or_off )	{
	
	database_verification_settings_controller->has_done_unordered_check = on_or_off;
}

/*********************
*  verifyFlags  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
int RPDB_DatabaseVerificationSettingsController_internal_verifyFlags( RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
	//	Make sure we return DB_SALVAGE if a file exists
	return	( database_verification_settings_controller->file ? DB_SALVAGE : 0 )
			|	RPDB_DatabaseVerificationSettingsController_aggressiveKeyDataPairDump(			database_verification_settings_controller )
			|	RPDB_DatabaseVerificationSettingsController_printableCharacters(	database_verification_settings_controller ) 
			|	RPDB_DatabaseVerificationSettingsController_skipOrderCheck(		database_verification_settings_controller ) 
			|	RPDB_DatabaseVerificationSettingsController_onlyOrderCheck(		database_verification_settings_controller );
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseVerificationSettingsController* RPDB_DatabaseVerificationSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller_copy	=	RPDB_DatabaseVerificationSettingsController_new( database_verification_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_verification_settings_controller_copy->aggressive_key_data_pair_dump	=	database_verification_settings_controller->aggressive_key_data_pair_dump;
	database_verification_settings_controller_copy->file_path	=	database_verification_settings_controller->file_path;
	database_verification_settings_controller_copy->force_order_check	=	database_verification_settings_controller->force_order_check;
	database_verification_settings_controller_copy->only_order_check	=	database_verification_settings_controller->only_order_check;
	database_verification_settings_controller_copy->skip_order_checking	=	database_verification_settings_controller->skip_order_checking;
	database_verification_settings_controller_copy->printable_characters	=	database_verification_settings_controller->printable_characters;
	database_verification_settings_controller_copy->has_done_unordered_check	=	database_verification_settings_controller->has_done_unordered_check;
	database_verification_settings_controller_copy->file_is_open	=	database_verification_settings_controller->file_is_open;
	database_verification_settings_controller_copy->file	=	database_verification_settings_controller->file;

	return database_verification_settings_controller_copy;
}

