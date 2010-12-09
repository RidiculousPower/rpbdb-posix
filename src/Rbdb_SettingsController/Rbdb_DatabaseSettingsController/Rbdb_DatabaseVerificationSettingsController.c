/*
 *		Rbdb::Database::DatabaseSettingsController::DatabaseVerificationSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseVerificationSettingsController.h"

#include "Rbdb_ErrorController.h"
#include "Rbdb_Environment.h"

#include "Rbdb_DatabaseVerificationSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_DatabaseVerificationSettingsController* Rbdb_DatabaseVerificationSettingsController_new( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseVerificationSettingsController ) );

	database_verification_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_verification_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseVerificationSettingsController_free(	Rbdb_DatabaseVerificationSettingsController** database_verification_settings_controller )	{

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
Rbdb_Environment* Rbdb_DatabaseVerificationSettingsController_parentEnvironment(	Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
	return database_verification_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseVerificationSettingsController_parentDatabase(	Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
	return database_verification_settings_controller->parent_database_settings_controller->parent_database;
}

/*************
*  file  *
*************/

FILE* Rbdb_DatabaseVerificationSettingsController_file(	Rbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller )	{
	
	return database_verification_settings_controller->file;
}

/*****************
*  setFile  *
*****************/

void Rbdb_DatabaseVerificationSettingsController_setFile(	Rbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller, 
															FILE*											data_output_file )	{
	
	database_verification_settings_controller->file = data_output_file;
}

/*****************
*  filePath  *
*****************/

char* Rbdb_DatabaseVerificationSettingsController_filePath(	Rbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller )	{
	
	return database_verification_settings_controller->file_path;
}

/*********************
*  setFilePath  *
*********************/

void Rbdb_DatabaseVerificationSettingsController_setFilePath(	Rbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller, 
																char*											data_output_file_path )	{
	
	database_verification_settings_controller->file_path = data_output_file_path;
}

/**********************************
*  aggressiveKeyDataPairDump  *
**********************************/

//	DB_AGGRESSIVE						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
BOOL Rbdb_DatabaseVerificationSettingsController_aggressiveKeyDataPairDump( Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	if ( database_verification_settings_controller->aggressive_key_data_pair_dump )	{
		return DB_AGGRESSIVE;
	}
	return FALSE;
}

	/******************************************
	*  turnAggressiveKeyDataPairDumpOn  *
	******************************************/

	void Rbdb_DatabaseVerificationSettingsController_turnAggressiveKeyDataPairDumpOn( Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->aggressive_key_data_pair_dump = TRUE;
	}

	/******************************************
	*  turnAggressiveKeyDataPairDumpOff  *
	******************************************/

	void Rbdb_DatabaseVerificationSettingsController_turnAggressiveKeyDataPairDumpOff( Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->aggressive_key_data_pair_dump = FALSE;
	}

/******************************
*  printableCharacters  *
******************************/

//	DB_PRINTABLE						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
BOOL Rbdb_DatabaseVerificationSettingsController_printableCharacters( Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	if ( database_verification_settings_controller->printable_characters )	{
		return DB_PRINTABLE;
	}
	return FALSE;
}

	/**********************************
	*  turnPrintableCharactersOn  *
	**********************************/

	void Rbdb_DatabaseVerificationSettingsController_turnPrintableCharactersOn( Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->printable_characters = TRUE;
	}

	/**********************************
	*  turnPrintableCharactersOff  *
	**********************************/

	void Rbdb_DatabaseVerificationSettingsController_turnPrintableCharactersOff( Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->printable_characters = FALSE;
	}

/**********************
*  skipOrderCheck  *
**********************/

//	DB_NOORDERCHK						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
BOOL Rbdb_DatabaseVerificationSettingsController_skipOrderCheck( Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	if ( database_verification_settings_controller->skip_order_checking )	{
		return DB_NOORDERCHK;
	}
	return FALSE;
}

	/******************************
	*  turnSkipOrderCheckOn  *
	******************************/

	void Rbdb_DatabaseVerificationSettingsController_turnSkipOrderCheckOn( Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->skip_order_checking = TRUE;

		//	If we are skipping order check then we aren't doing only an order check (although next we will)
		Rbdb_DatabaseVerificationSettingsController_turnOnlyOrderCheckOff( database_verification_settings_controller );
	}

	/******************************
	*  turnSkipOrderCheckOff  *
	******************************/

	void Rbdb_DatabaseVerificationSettingsController_turnSkipOrderCheckOff( Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->skip_order_checking = FALSE;
	}

/**********************
*  onlyOrderCheck  *
**********************/

//	DB_NOORDERCHK						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
BOOL Rbdb_DatabaseVerificationSettingsController_onlyOrderCheck( Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	//	Assumes we have already done a check without order checking
	if ( database_verification_settings_controller->only_order_check )	{
		return DB_ORDERCHKONLY;
	}
	return FALSE;
}

	/******************************
	*  turnOnlyOrderCheckOn  *
	******************************/

	void Rbdb_DatabaseVerificationSettingsController_turnOnlyOrderCheckOn(	Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->only_order_check = TRUE;
	
		//	If we haven't already done an unordered check, don't do an order check unless we are explicitly forcing it. 
		if (	! database_verification_settings_controller->force_order_check 
			&&	! database_verification_settings_controller->has_done_unordered_check )	{
		
			Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController(	database_verification_settings_controller->parent_database_settings_controller->parent_settings_controller->parent_environment ),
																				-1,
																				"Rbdb_DatabaseVerificationSettingsController_onlyOrderCheck",
																				"Must first perform check while skipping order or force ordered check explicitly (may cause corruption)." );
		}
	
		//	Skipping order check can't also be true
		Rbdb_DatabaseVerificationSettingsController_turnSkipOrderCheckOff( database_verification_settings_controller );
	}

	/******************************
	*  turnOnlyOrderCheckOff  *
	******************************/

	void Rbdb_DatabaseVerificationSettingsController_turnOnlyOrderCheckOff( Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
	
		database_verification_settings_controller->only_order_check = FALSE;
	}

/**************************
*  forceOrderCheck  *
**************************/

BOOL Rbdb_DatabaseVerificationSettingsController_forceOrderCheck(	Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	return database_verification_settings_controller->force_order_check;
}

	/******************************
	*  turnForceOrderCheckOn  *
	******************************/

	void Rbdb_DatabaseVerificationSettingsController_turnForceOrderCheckOn(	Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
		database_verification_settings_controller->force_order_check = TRUE;
	}

	/******************************
	*  turnForceOrderCheckOff  *
	******************************/

	void Rbdb_DatabaseVerificationSettingsController_turnForceOrderCheckOff(	Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
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
	
void Rbdb_DatabaseVerificationSettingsController_internal_hasDoneUnorderedCheck( 	Rbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller, 
																					int												on_or_off )	{
	
	database_verification_settings_controller->has_done_unordered_check = on_or_off;
}

/*********************
*  verifyFlags  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
int Rbdb_DatabaseVerificationSettingsController_internal_verifyFlags( Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
	//	Make sure we return DB_SALVAGE if a file exists
	return	( database_verification_settings_controller->file ? DB_SALVAGE : 0 )
			|	Rbdb_DatabaseVerificationSettingsController_aggressiveKeyDataPairDump(			database_verification_settings_controller )
			|	Rbdb_DatabaseVerificationSettingsController_printableCharacters(	database_verification_settings_controller ) 
			|	Rbdb_DatabaseVerificationSettingsController_skipOrderCheck(		database_verification_settings_controller ) 
			|	Rbdb_DatabaseVerificationSettingsController_onlyOrderCheck(		database_verification_settings_controller );
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_DatabaseVerificationSettingsController* Rbdb_DatabaseVerificationSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller_copy	=	Rbdb_DatabaseVerificationSettingsController_new( database_verification_settings_controller->parent_database_settings_controller );

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

